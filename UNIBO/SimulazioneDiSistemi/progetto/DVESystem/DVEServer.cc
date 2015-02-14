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
DVEServer::handleLoginMessage(cMessage *msg)
{
    LoginMsg* l_msg = check_and_cast<LoginMsg*>(msg);
    int clientID = l_msg->getID();
    int partitionID = l_msg->getServerID();
    if (partitionID == getIndex())
    {
        // Save the client id into the server clients vector.
        addClient(clientID);
        //DBG//
        EV << "DVEServer[" << partitionID << "]::" << clientID;
        //DBG//
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
    // TODO
}


void
DVEServer::handleMoveMessage(cMessage *msg)
{
    // TODO
}


void
DVEServer::handleMessage(cMessage *msg)
{
    LoginMsg* l_msg = dynamic_cast<LoginMsg*>(msg);
    if (l_msg != 0)
    {
        bubble("Login MSG!");
        EV << "Received Message: " << msg <<".\n";
        handleLoginMessage(msg);
    }
    MoveMsg* m_msg = dynamic_cast<MoveMsg*>(msg);
    if (m_msg != 0)
    {
        bubble("Move MSG!");
    }
    ServerUpdateMsg* u_msg = dynamic_cast<ServerUpdateMsg*>(msg);
    /*DBG*/
    if (u_msg != 0)
    {
        bubble("Server Update MSG!");
    }
}


void
DVEServer::updateClients(int* clients, int length)
{
    if (!servedClients_.empty())
    {
        servedClients_.erase(servedClients_.begin(), servedClients_.end());
    }
    for (int i = 0; i < length; i++)
    {
        addClient(clients[i]);
    }
}

void
DVEServer::addClient(int clientID) {
    clients_++;
    servedClients_.push_back(clientID);
}
