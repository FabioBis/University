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

#ifndef DVESERVER_H_
#define DVESERVER_H_

#include <omnetpp.h>
#include <exception>
#include <algorithm>
#include <vector>
#include <ServerUpdateMsg_m.h>
#include <MoveMsg_m.h>
#include <LoginMsg_m.h>
#include <UpdateAoIMsg_m.h>
#include <ACKMsg_m.h>

using namespace std;

// Partition Server.
class DVEServer : public cSimpleModule {
private:
    int clients_;
    std::vector<int> servedClients_;
    // Helper functions.
    void addClient(int clientID);
protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    // handleMessage() helpers.
    void handleLoginMessage(cMessage *msg);
    void handleUpdateMessage(cMessage *msg);
    void handleMoveMessage(cMessage *msg);
    void handleUpdateAoIMessage(cMessage *msg);
    void handleACKMessage(cMessage *msg);
};

#endif /* DVESERVER_H_ */
