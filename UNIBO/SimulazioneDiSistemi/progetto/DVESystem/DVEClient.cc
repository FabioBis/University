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

#include <DVEClient.h>

Define_Module(DVEClient);

DVEClient::DVEClient()
{

}

DVEClient::~DVEClient()
{
    delete avatar;
}

void
DVEClient::initialize()
{
    // Assuming the Avatar lives in a 9x9 world, and the staring distribution
    // among world cells is uniform.
    avatar = new Avatar(getIndex(), intuniform(0, 8), intuniform(0, 8));
    logged = false;
    ready = false;
    frozen = false;
    WATCH(ready);
    serverID = 0;
    WATCH(serverID);
    movesLoss = 0;
    WATCH(movesLoss);
    moves = 0;
    WATCH(moves);
    ackReceived = 0;
    WATCH(ackReceived);
    systemResponseSignal = registerSignal("sysResponse");
    moveLostSignal = registerSignal("moveLost");
    // DBG
    _x = avatar->GetX();
    _y = avatar->GetY();
    WATCH(_x);
    WATCH(_y);
}


void
DVEClient::handleMessage(cMessage *msg)
{
    LoginMsg* l_msg = dynamic_cast<LoginMsg*>(msg);
    if (l_msg != 0)
    {
        bubble("Login MSG!");
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
    // The message is a Job from Source.
    if(logged)
    {
        if (ready)
        {
            // Let's move!
            bubble("Let's move!");
            makeMove();
            moves++;
        }
        else
        {
            // Can't move!
            bubble("Can't move!");
            EV << "Can't move!\n";
            frozen = true;
            movesLoss++;
            emit(moveLostSignal, movesLoss);
        }
    }
    else
    {
        LoginMsg* login = new LoginMsg("login");
        logged = true;
        login->setX(avatar->GetX());
        login->setY(avatar->GetY());
        login->setID(avatar->GetID());
        // $o and $i suffix is used to identify the input/output part of a two way gate.
        send(login, "wanIO$o");
    }
    delete msg;
}

void
DVEClient::handleLoginMessage(cMessage *msg)
{
    LoginMsg* l_msg = check_and_cast<LoginMsg*>(msg);
    serverID = l_msg->getServerID();
    EV << "Client " << avatar->GetID() <<" bound to server: " << serverID <<endl; // DBG
    for (unsigned int i = 0; i < l_msg->getAoiArraySize(); i++)
    {
        avatar->addToAOI(l_msg->getAoi(i));
    }
    ready = true;
    delete msg;
}

void
DVEClient::handleMoveMessage(cMessage *msg)
{
    MoveMsg* m_msg = check_and_cast<MoveMsg*>(msg);
    int avatarID = m_msg->getClientID();
    if (avatarID != getIndex())
    {
        // Message from a client: remove from the current AoI.
        avatar->removeFromAOI(avatarID);
        ACKMsg* ack_msg = new ACKMsg();
        ack_msg->setMovedID(avatarID);
        ack_msg->setServerID(serverID);
        ack_msg->setIsMoveComplete(false);
        send(ack_msg, "wanIO$o");
    }
    delete msg;
}


void
DVEClient::handleUpdateMessage(cMessage * msg)
{
    ServerUpdateMsg* su_msg = check_and_cast<ServerUpdateMsg*>(msg);
    serverID = su_msg->getServerID();
    delete msg;
}


void
DVEClient::handleUpdateAoIMessage(cMessage * msg)
{
    UpdateAoIMsg* aoi_msg = check_and_cast<UpdateAoIMsg*>(msg);
    int sourceID = aoi_msg->getClientMoved();
    if (sourceID == getIndex())
    {
        // Message from the server: fully update the AoI.
        unsigned int size = aoi_msg->getAoiArraySize();
        int* aoi = new int[size];
        for (unsigned int i = 0; i < size; i++)
        {
            aoi[i] = aoi_msg->getAoi(i);
        }
        avatar->updateAOI(aoi, size);
        delete [] aoi;
    }
    else
    {
        // Message from a client: add to the current AoI.
        avatar->addToAOI(sourceID);
        // Send ACK message to the server.
        ACKMsg* ack_msg = new ACKMsg();
        ack_msg->setMovedID(sourceID);
        ack_msg->setIsMoveComplete(false);
        ack_msg->setServerID(serverID);
    }
    delete msg;
}

void
DVEClient::handleACKMessage(cMessage *msg)
{
    ACKMsg* ack_msg = check_and_cast<ACKMsg*>(msg);
    if (ack_msg->getIsMoveComplete())
    {
        ready = true;
        ackReceived++;
        if (frozen)
        {
            frozen = false;
            EV << "Move lost!"; // DBG
            simtime_t response = simTime() - timeRequest;
            EV << "\t response time: " <<response <<endl; // DBG
            emit(systemResponseSignal, response);
        }
        simtime_t response = simTime() - timeRequest;
        EV << "\t response time: " <<response <<endl; // DBG
        emit(systemResponseSignal, response);
    }
    else
    {
        // DBG
        EV << "ACK message error";
        bubble("ACK message error");
    }
    delete msg;
}

void
DVEClient::makeMove()
{
    EV << "make move!\n"; // DBG
    ready = false;
    int x;
    int y;
    double probability = uniform(0.0, 1.0);
    if (probability > 0.95) // 1.0 - 0.05
    {
        x = intuniform(0, 8);
        y = intuniform(0, 8);
        EV << "Jump!.\n"; // DBG
    }
    else
    {
        computeCoordinate(avatar->GetX(), x);
        computeCoordinate(avatar->GetY(), y);
    }
    if (avatar->GetX() == x && avatar->GetY() == y)
    {
        // No moves.
        EV << "Location unchanged.\n"; // DBG
        EV <<"Avatar(" <<avatar->GetX() <<", " <<avatar->GetY() <<").\n";
        EV << "To: <" <<x <<", " <<y <<">";
        ready = true;
        return;
    }
    else
    {
        // DBG
        EV <<"Avatar(" <<avatar->GetX() <<", " <<avatar->GetY() <<").\n";
        EV << "To: <" <<x <<", " <<y <<">";
        MoveMsg* move = new MoveMsg();
        move->setX(x);
        move->setY(y);
        move->setClientID(getIndex());
        move->setServerID(serverID);
        move->setArrivalServer(-1);
        unsigned int i = 0;
        move->setAoiArraySize(avatar->GetAoISize());
        for ( ; i < avatar->GetAoISize(); )
        {
            move->setAoi(i, avatar->GetAtAoi(i));
            i++;
        }
        avatar->move(x, y);
        send(move, "wanIO$o");
        timeRequest = simTime();
        // DBG
        _x = avatar->GetX();
        _y = avatar->GetY();
    }
}


void
DVEClient::computeCoordinate(int src, int &dest)
{
    switch (src)
    {
    case 0:
        dest = intuniform(0, 1);
        break;
    case 8:
        dest = intuniform(7, 8);
        break;
    default:
        dest = intuniform(src - 1, src + 1);
        break;
    }
}
