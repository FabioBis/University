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

#ifndef MAINSERVER_H_
#define MAINSERVER_H_

#include <omnetpp.h>
#include <map>
#include <algorithm>
#include <VirtualEnvironment.h>
#include <ServerUpdateMsg_m.h>
#include <MoveMsg_m.h>
#include <LoginMsg_m.h>
#include <UpdateAoIMsg_m.h>
#include <ACKMsg_m.h>


struct part_indexes {
    // Beginning line index.
    int bl;
    // Ending line index.
    int el;
    // Beginning column index.
    int bc;
    // Ending column index.
    int ec;
    // Length.
    int length;
};

class Acknowledgment {
public:
    // Current acks.
    int current;
    // Total acks.
    int total;
    Acknowledgment();
    void Ack();
    bool IsComplete();
};

class MainServer : public cSimpleModule {
private:
    // The number of partition servers.
    int PARTSERVERS;
    // The maximum movements until apply a new server partition.
    int MOVESMAX;
    // The collection of clients logged in.
    std::map<int, VirtualAvatar*> connectedAvatars_;
    // The set of acknowledgments the server is waiting for.
    std::map<int, Acknowledgment*> ack_registry_;
    // The virtual environment.
    VirtualEnvironment* ve_;
    // An array of indexes representing the ve partition among servers.
    part_indexes* partition_;
    // Number of avatar movements since last server partition.
    int moves_n;

    // Partitioner auxiliary function.
    void partitioner();
    int getPartitionServerID(int x, int y);
    void updatePartition();

    // handleMessage() helpers.
    void handleLoginMessage(cMessage *msg);
    void handleUpdateMessage(cMessage * msg);
    void handleMoveMessage(cMessage *msg);
    void handleUpdateAoIMessage(cMessage *msg);
    void handleACKMessage(cMessage *msg);

    // Virtual environment helpers.
    void handleMove(int clientID, int x, int y);

protected:
    ~MainServer();
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
};

#endif /* MAINSERVER_H_ */
