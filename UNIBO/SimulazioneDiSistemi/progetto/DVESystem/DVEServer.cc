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
    ;
}


void
DVEServer::handleMessage(cMessage *msg)
{
    ;
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
    servedClients_.push_back(clientID);
}
