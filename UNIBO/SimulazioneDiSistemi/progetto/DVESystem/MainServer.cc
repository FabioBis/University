//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public License
// along with this program.  If not, see http://www.gnu.org/licenses/.
// 

#include <MainServer.h>

Define_Module(MainServer);

MainServer::~MainServer()
{
    delete partition_;
    delete ve_;
}

void
MainServer::initialize()
{
    ve_ = new VirtualEnvironment();
    PARTSERVERS = par("numOfServer");
    int clients = par("numOfClient");
    MOVESMAX =  clients * 30; // Approximately 1 simulated minute.
    partition_ = new part_indexes[PARTSERVERS];
    partitioner();
    moves_n = 0;
}

void
MainServer::handleMessage(cMessage *msg)
{
    LoginMsg* l_msg = dynamic_cast<LoginMsg*>(msg);
    if (l_msg != 0)
    {
        bubble("Login MSG!");
        EV << "Received Message: " << msg <<".\n";
        handleLoginMessage(msg);
        return;
    }
    MoveMsg* m_msg = dynamic_cast<MoveMsg*>(msg);
    if (m_msg != 0)
    {
        bubble("Move MSG!");
        handleMoveMessage(msg);
        return;
    }
    ServerUpdateMsg* u_msg = dynamic_cast<ServerUpdateMsg*>(msg);
    if (u_msg != 0)
    {
        bubble("Server Update MSG!");
        handleUpdateMessage(msg);
        return;
    }
    UpdateAoIMsg* aoi_msg = dynamic_cast<UpdateAoIMsg*>(msg);
    if (aoi_msg != 0)
    {
        bubble("Update AoI!");
        handleUpdateAoIMessage(msg);
        return;
    }
    ACKMsg* ack_msg = dynamic_cast<ACKMsg*>(msg);
    if (ack_msg != 0)
    {
        bubble("ACK!");
        handleACKMessage(msg);
        return;
    }
    delete msg;
}

void
MainServer::handleUpdateAoIMessage(cMessage * msg)
{
    // Simply forward the message.
    UpdateAoIMsg* aoi_msg = check_and_cast<UpdateAoIMsg*>(msg);
    send(aoi_msg, "lanOut");
}

void
MainServer::handleLoginMessage(cMessage *msg)
{
    // check_and_cast from omnetpp.h perform a dynamic cast or raise an error
    // during the simulation instead of crash.
    LoginMsg* l_msg = check_and_cast<LoginMsg*>(msg);
    // Insert Virtual Avatar inside the Virtual Environment.
    VirtualAvatar* va = new VirtualAvatar(
            ve_,
            l_msg->getID(),
            l_msg->getX(),
            l_msg->getY());
    ve_->add(va);
    // Insert Virtual Avatar into the map of connected clients.
    connectedAvatars_.insert(std::pair<int, VirtualAvatar*>(l_msg->getID(), va));

    // Identify the partition server for the client.
    int partitionServer = getPartitionServerID(l_msg->getX(), l_msg->getY());
    EV << "Partition Server: " << partitionServer <<endl;
    // Adding partition server id and send through LAN.
    l_msg->setServerID(partitionServer);
    send(l_msg, "lanOut");


    LoginMsg* ack = new LoginMsg();
    ack->setServerID(partitionServer);
    ack->setID(l_msg->getID());
    int* aoi = NULL;
    unsigned int size;
    ve_->GetAvatarAndSizeAt(l_msg->getX(), l_msg->getY(), &aoi, size);
    ack->setAoiArraySize(size);
    for (unsigned int index = 0; index < size; index++)
    {
        ack->setAoi(index, aoi[index]);
    }
    send(ack, "wanIO$o");
}

void
MainServer::handleUpdateMessage(cMessage * msg)
{
    // Simply forward the message.
    ServerUpdateMsg* su_msg = check_and_cast<ServerUpdateMsg*>(msg);
    send(su_msg, "lanOut");
}

void
MainServer::handleMoveMessage(cMessage *msg)
{
    moves_n++;
    MoveMsg* m_msg = check_and_cast<MoveMsg*>(msg);
    handleMove(m_msg->getClientID(), m_msg->getX(), m_msg->getY(), m_msg->getAoiArraySize());
    // When client's moves reach a given threshold the partition need to be updated.
    if (moves_n >= MOVESMAX)
    {
        bubble("Update Partition Servers.");
        updatePartition();
        moves_n = 0;
    }
    send(m_msg, "lanOut");
}

void
MainServer::handleMove(int clientID, int x, int y, unsigned int msgAoISize) {
    int* newAoi = NULL;
    unsigned int newAoiSize;
    ve_->GetAvatarAndSizeAt(x, y, &newAoi, newAoiSize);
    EV << "New AoI size: " << newAoiSize << endl;
    UpdateAoIMsg* update = new UpdateAoIMsg();
    update->setClientMoved(clientID);
    update->setX(x);
    update->setY(y);
    update->setAoiArraySize(newAoiSize);
    for (unsigned int index = 0; index < newAoiSize; index++)
    {
        update->setAoi(index, newAoi[index]);
    }
    update->setIsNeighborNotification(false);
    send(update, "lanOut");
    // Updates VA and VE.
    VirtualAvatar* avatar = connectedAvatars_[clientID];
    unsigned int oldAoiSize = ve_->GetSizeAt(avatar->GetX(), avatar->GetY()) - 1;
    avatar->move(x, y);
    // Handle acknowledges.
    EV << "Old AoI size: " << oldAoiSize << endl;
    int aksRequired = (msgAoISize <= oldAoiSize) ? msgAoISize + newAoiSize
            : newAoiSize + oldAoiSize;
    if (aksRequired == 0)
    {
        // No client to be notified, send the ack to client moved.
        ACKMsg* ack_msg = new ACKMsg();
        ack_msg->setMovedID(clientID);
        ack_msg->setIsMoveComplete(true);
        send(ack_msg, "lanOut");
    }
    else
    {
        // Insert the new ack into the registry.
        Acknowledgment* ack = new Acknowledgment();
        ack->current = 0;
        ack->total = aksRequired;
        EV <<"Insert new ack, total: " <<ack->total <<endl; // DBG
        ack_registry_.insert(std::pair<int, Acknowledgment*>(clientID, ack));
    }
}

void
MainServer::handleACKMessage(cMessage *msg)
{
    ACKMsg* ack_msg = check_and_cast<ACKMsg*>(msg);
    if (!ack_msg->getIsMoveComplete())
    {
        EV << "ACK msg to main server. (if)\n"; // DBG
        std::map<int, Acknowledgment*>::iterator it;
        it = ack_registry_.find(ack_msg->getMovedID());
        if (it != ack_registry_.end())
        {
            Acknowledgment* ack = ack_registry_[ack_msg->getMovedID()];
            ack->Ack();
            if (ack->IsComplete())
            {
                ack_msg->setIsMoveComplete(true);
                ack_registry_.erase(ack_msg->getMovedID());
                send(ack_msg, "lanOut");
            }
        }
        else
        {
            delete msg;
        }
    }
    else
    {
        EV << "ACK msg to main server. (else) Possible error?\n"; // DBG
        send(ack_msg, "lanOut");
    }
}

int
MainServer::getPartitionServerID(int x, int y)
{
    for (int i = 0; i < partition_->length; i++)
    {
        if (partition_[i].bl <= x && partition_[i].el >= x)
        {
            for (int j = 0; j < partition_->length; j++)
            {
                if (partition_[j].bc <= y && partition_[i].ec >= y)
                {
                    return std::max(j, i);
                }
            }
        }
    }
    return -1;
}

void
MainServer::updatePartition()
{
    for (int k = 0; k < PARTSERVERS; k++)
    {
        EV<<"Partition: " <<partition_[k].bl <<" " <<partition_[k].el <<" " <<partition_[k].bc
                <<" " <<partition_[k].ec <<endl;
        ServerUpdateMsg* update = new ServerUpdateMsg("update");
        update->setServerID(k);
        for (int i = partition_[k].bl; i <= partition_[k].el; i++)
        {
            for (int j = partition_[k].bc; j <= partition_[k].ec; j++)
            {
                int* avatars = NULL;
                unsigned int size;
                ve_->GetAvatarAndSizeAt(i, j, &avatars, size);
                EV <<"Server " << k <<" cell [" <<i <<", " <<j <<"], size: " <<size <<endl; // DBG
                unsigned int index = update->getClientsArraySize();
                unsigned int new_size = index + size;
                update->setClientsArraySize(new_size);
                for (unsigned int i = 0; i < size; i++)
                {
                    EV <<"\tClient connected: " <<avatars[i] <<endl;
                    update->setClients(index, avatars[i]);
                    EV <<"\tClient added to msg: " <<update->getClients(index) <<endl;
                    index++;
                }
            }
        }
        // Sending update message through LAN to partition server k.
        unsigned int size = update->getClientsArraySize();
        EV <<"Client size: " <<size <<endl;
        for (unsigned int i = 0; i < size; i++)
        {
            int clientID = update->getClients(i);
            EV  <<i <<" client id: " <<clientID <<endl;
        }
        send(update, "lanOut");
    }
}

void
MainServer::partitioner()
{
    partition_->length = PARTSERVERS;
    switch(PARTSERVERS)
    {
    case 1:
        partition_[0].bl = 0;
        partition_[0].el = 8;
        partition_[0].bc = 0;
        partition_[0].ec = 8;
        break;
    case 2:
        partition_[0].bl = 0;
        partition_[0].el = 5;
        partition_[0].bc = 0;
        partition_[0].ec = 5;

        partition_[1].bl = 6;
        partition_[1].el = 8;
        partition_[1].bc = 6;
        partition_[1].ec = 8;
        break;
    case 3:
        partition_[0].bl = 0;
        partition_[0].el = 2;
        partition_[0].bc = 0;
        partition_[0].ec = 8;

        partition_[1].bl = 3;
        partition_[1].el = 5;
        partition_[1].bc = 0;
        partition_[1].ec = 8;

        partition_[2].bl = 6;
        partition_[2].el = 8;
        partition_[2].bc = 0;
        partition_[2].ec = 8;
        break;
    case 4:
        partition_[0].bl = 0;
        partition_[0].el = 4;
        partition_[0].bc = 0;
        partition_[0].ec = 4;

        partition_[1].bl = 0;
        partition_[1].el = 4;
        partition_[1].bc = 5;
        partition_[1].ec = 8;

        partition_[2].bl = 5;
        partition_[2].el = 8;
        partition_[2].bc = 0;
        partition_[2].ec = 4;

        partition_[3].bl = 5;
        partition_[3].el = 8;
        partition_[3].bc = 5;
        partition_[3].ec = 8;
        break;
    case 5:
        partition_[0].bl = 0;
        partition_[0].el = 4;
        partition_[0].bc = 0;
        partition_[0].ec = 4;

        partition_[1].bl = 5;
        partition_[1].el = 8;
        partition_[1].bc = 0;
        partition_[1].ec = 4;

        partition_[2].bl = 0;
        partition_[2].el = 2;
        partition_[2].bc = 5;
        partition_[2].ec = 8;

        partition_[3].bl = 3;
        partition_[3].el = 5;
        partition_[3].bc = 5;
        partition_[3].ec = 8;

        partition_[4].bl = 6;
        partition_[4].el = 8;
        partition_[4].bc = 5;
        partition_[4].ec = 8;
        break;
    case 6:
        partition_[0].bl = 0;
        partition_[0].el = 2;
        partition_[0].bc = 0;
        partition_[0].ec = 4;

        partition_[1].bl = 0;
        partition_[1].el = 2;
        partition_[1].bc = 5;
        partition_[1].ec = 8;

        partition_[2].bl = 3;
        partition_[2].el = 5;
        partition_[2].bc = 0;
        partition_[2].ec = 4;

        partition_[3].bl = 3;
        partition_[3].el = 5;
        partition_[3].bc = 5;
        partition_[3].ec = 8;

        partition_[4].bl = 6;
        partition_[4].el = 8;
        partition_[4].bc = 0;
        partition_[4].ec = 4;

        partition_[5].bl = 6;
        partition_[5].el = 8;
        partition_[5].bc = 5;
        partition_[5].ec = 8;
        break;
    case 7:
        partition_[0].bl = 0;
        partition_[0].el = 2;
        partition_[0].bc = 0;
        partition_[0].ec = 5;

        partition_[1].bl = 0;
        partition_[1].el = 2;
        partition_[1].bc = 6;
        partition_[1].ec = 8;

        partition_[2].bl = 3;
        partition_[2].el = 5;
        partition_[2].bc = 0;
        partition_[2].ec = 2;

        partition_[3].bl = 3;
        partition_[3].el = 5;
        partition_[3].bc = 3;
        partition_[3].ec = 5;

        partition_[4].bl = 3;
        partition_[4].el = 8;
        partition_[4].bc = 6;
        partition_[4].ec = 8;

        partition_[5].bl = 6;
        partition_[5].el = 8;
        partition_[5].bc = 0;
        partition_[5].ec = 2;

        partition_[6].bl = 6;
        partition_[6].el = 8;
        partition_[6].bc = 3;
        partition_[6].ec = 5;
        break;
    case 8:
        partition_[0].bl = 0;
        partition_[0].el = 2;
        partition_[0].bc = 0;
        partition_[0].ec = 5;

        partition_[1].bl = 0;
        partition_[1].el = 2;
        partition_[1].bc = 6;
        partition_[1].ec = 8;

        partition_[2].bl = 3;
        partition_[2].el = 5;
        partition_[2].bc = 0;
        partition_[2].ec = 2;

        partition_[3].bl = 3;
        partition_[3].el = 5;
        partition_[3].bc = 3;
        partition_[3].ec = 5;

        partition_[4].bl = 3;
        partition_[4].el = 5;
        partition_[4].bc = 6;
        partition_[4].ec = 8;

        partition_[5].bl = 6;
        partition_[5].el = 8;
        partition_[5].bc = 0;
        partition_[5].ec = 2;

        partition_[6].bl = 6;
        partition_[6].el = 8;
        partition_[6].bc = 3;
        partition_[6].ec = 5;

        partition_[7].bl = 6;
        partition_[7].el = 8;
        partition_[7].bc = 6;
        partition_[7].ec = 6;
        break;
    case 9:
        partition_[0].bl = 0;
        partition_[0].el = 2;
        partition_[0].bc = 0;
        partition_[0].ec = 2;

        partition_[1].bl = 0;
        partition_[1].el = 2;
        partition_[1].bc = 3;
        partition_[1].ec = 5;

        partition_[2].bl = 0;
        partition_[2].el = 2;
        partition_[2].bc = 6;
        partition_[2].ec = 8;

        partition_[3].bl = 3;
        partition_[3].el = 5;
        partition_[3].bc = 0;
        partition_[3].ec = 2;

        partition_[4].bl = 3;
        partition_[4].el = 5;
        partition_[4].bc = 3;
        partition_[4].ec = 5;

        partition_[5].bl = 3;
        partition_[5].el = 5;
        partition_[5].bc = 6;
        partition_[5].ec = 8;

        partition_[6].bl = 6;
        partition_[6].el = 8;
        partition_[6].bc = 0;
        partition_[6].ec = 2;

        partition_[7].bl = 6;
        partition_[7].el = 8;
        partition_[7].bc = 3;
        partition_[7].ec = 5;

        partition_[8].bl = 6;
        partition_[8].el = 8;
        partition_[8].bc = 6;
        partition_[8].ec = 6;
        break;
    default:
        throw 401;
        break;
    }
}


Acknowledgment::Acknowledgment()
{
    this->current = 0;
    this->total = 0;
}

void
Acknowledgment::Ack() {
    this->current++;
}

bool
Acknowledgment::IsComplete() {
    return this->current >= this->total;
}
