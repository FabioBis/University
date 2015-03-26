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

#include "DVEServer.h"

Define_Module(DVEServer);

void
DVEServer::initialize()
{
    clients_ = 0;
    WATCH(clients_);
}


void
DVEServer::handleMessage(cMessage *msg)
{
    EV << "DVEServer::handling message.\n" <<msg <<endl;
    LoginMsg* l_msg = dynamic_cast<LoginMsg*>(msg);
    if (l_msg != 0)
    {
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


/*
 * Notify the moving avatar the new AoI and forward the message to all new
 * neighbors that will add to their AoI.
 * The update AoI process is divided into two phases: first notify all
 * neighbors about the incoming new avatar. Then, when there are no more
 * neighbors to notify, the moving avatar is notified. This way we can
 * compute the System Response.
 */
void
DVEServer::handleUpdateAoIMessage(cMessage * msg)
{
    UpdateAoIMsg* aoi_msg = check_and_cast<UpdateAoIMsg*>(msg);
    unsigned int aoiSize = aoi_msg->getAoiArraySize();
    if (aoiSize != 0)
    {
        // Phase 1: notify new AoI avatars.
        unsigned int servedNeighbors = 0;
        std::vector<int> nonServedNeighbors;
        for (unsigned int i = 0; i < aoiSize; i++)
        {
            int neighborID = aoi_msg->getAoi(i);
            std::vector<int>::iterator it;
            it = std::find(
                    servedClients_.begin(),
                    servedClients_.end(),
                    neighborID);
            if (it != servedClients_.end())
            {
                servedNeighbors++;
                UpdateAoIMsg *new_msg = aoi_msg->dup();
                new_msg->setClientDest(neighborID);
                send(new_msg, "wanIO$o");
            }
            else
            {
                nonServedNeighbors.push_back(neighborID);
            }
        }
        if (servedNeighbors > 0)
        {
            // Partition server has served some clients, update the list of
            // clients to be notified and forward the message.
            unsigned int newSize = aoiSize - servedNeighbors;
            aoi_msg->setAoiArraySize(newSize);
            for (unsigned int i = 0; i < newSize; i++)
            {
                aoi_msg->setAoi(i, nonServedNeighbors.back());
            }
            // Forward the move message until no more clients must be notified.
            send(aoi_msg, "lanOut");
        }
        else
        {
            send(aoi_msg, "lanOut");
        }
    } // fi aoiSize != 0.
    else
    {
        // Phase 2: notify the moving avatar.
        int movingAvatar = aoi_msg->getClientMoved();
        std::vector<int>::iterator it;
        it = std::find(
                servedClients_.begin(),
                servedClients_.end(),
                movingAvatar);
        if (it != servedClients_.end())
        {
            // This server serves the moving avatar.
            aoi_msg->setClientDest(*it);
            send(aoi_msg, "wanIO$o");
        }
        else
        {
            send(aoi_msg, "lanOut");
        }
    }
}


void
DVEServer::handleLoginMessage(cMessage *msg)
{
    LoginMsg* l_msg = check_and_cast<LoginMsg*>(msg);
    int clientID = l_msg->getID();
    int partitionID = l_msg->getServerID();
    if (partitionID == getIndex())
    {
        // Save the client id into the server clients vector.
        addClient(clientID);
        delete msg;
    }
    else
    {
        // Forward the message to the LAN ring.
        send(l_msg, "lanOut");
    }
}


void
DVEServer::handleUpdateMessage(cMessage * msg)
{
    ServerUpdateMsg* su_msg = check_and_cast<ServerUpdateMsg*>(msg);
    int partitionID = su_msg->getServerID();
    if (partitionID == getIndex())
    {
        servedClients_.clear();
        clients_ = 0;
        unsigned int size = su_msg->getClientsArraySize();
        for (unsigned int i = 0; i < size; i++)
        {
            int clientID = su_msg->getClients(i);
            servedClients_.push_back(clientID);
            ServerUpdateMsg* new_msg = su_msg->dup();
            new_msg->setClientDest(clientID);
            send(new_msg, "wanIO$o");
            clients_++;
        }
        delete msg;
    }
    else
    {
        // Forward the message to the LAN ring.
        send(su_msg, "lanOut");
    }
}


void
DVEServer::handleMoveMessage(cMessage *msg)
{
    MoveMsg* m_msg = check_and_cast<MoveMsg*>(msg);

    if (m_msg->getArrivalServer() == getIndex())
    {
        // Message propagation completed.
        delete msg;
        return;
    }
    else if (m_msg->getArrivalServer() == -1)
    {
        m_msg->setArrivalServer(getIndex());
    }

    unsigned int aoiSize = m_msg->getAoiArraySize();
    EV << "DVEServer::handleMove: AoI size is " <<m_msg->getAoiArraySize() <<endl; // DBG
    for (unsigned int i = 0; i < aoiSize; i++)
    {
        int avatarID = m_msg->getAoi(i);
        if (avatarID == m_msg->getClientID())
        {
            ; // Do nothing.
        }
        else
        {
            EV << "Sending a move message to Client..." <<endl; // DBG
            std::vector<int>::iterator it;
            it = std::find(servedClients_.begin(), servedClients_.end(), avatarID);
            if (it != servedClients_.end())
            {
                MoveMsg *new_msg = m_msg->dup();
                new_msg->setClientDest(avatarID);
                send(new_msg, "wanIO$o");
            }
        }
    }
    send(m_msg, "lanOut");
}

void
DVEServer::handleACKMessage(cMessage *msg)
{
    ACKMsg* ack_msg = check_and_cast<ACKMsg*>(msg);
    if (!ack_msg->getIsMoveComplete())
    {
        send(ack_msg, "lanOut");
    }
    else
    {
        std::vector<int>::iterator it;
        it = std::find(
                servedClients_.begin(),
                servedClients_.end(),
                ack_msg->getMovedID()
                );
        if (it != servedClients_.end())
        {
            send(ack_msg, "wanIO$o");
        }
        else
        {
            send(ack_msg, "lanOut");
        }
    }
}


void
DVEServer::addClient(int clientID) {
    clients_++;
    servedClients_.push_back(clientID);
}
