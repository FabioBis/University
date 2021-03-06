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

#ifndef DVECLIENT_H_
#define DVECLIENT_H_

#include <omnetpp.h>
#include <Avatar.h>
#include <MoveMsg_m.h>
#include <LoginMsg_m.h>
#include <ServerUpdateMsg_m.h>
#include <UpdateAoIMsg_m.h>
#include <ACKMsg_m.h>

class DVEClient : public cSimpleModule {
private:
    // The game avatar.
    Avatar* avatar;
    //DBG
    int _x, _y;
    // The current game server id that the client refers to.
    int serverID;
    // Flag to login the client.
    bool logged;
    // Flag: is the AoI updated?
    bool ready;
    // Flag: has the client lost a move?
    bool frozen;

    // Statistics.
    simtime_t timeRequest;
    simsignal_t systemResponseSignal;
    int ackReceived;
    simsignal_t moveLostSignal;
    int movesLoss;
    simsignal_t noMoveSignal;
    int nomoves;
    simsignal_t moveSignal;
    int moves;
    simsignal_t presenceFactorSignal;
    unsigned int presenceFactor;

    void makeMove();
    void handleLoginMessage(cMessage *msg);
    void handleMoveMessage(cMessage *msg);
    void handleUpdateMessage(cMessage *msg);
    void handleUpdateAoIMessage(cMessage *msg);
    void handleACKMessage(cMessage *msg);
    void computeCoordinate(int src, int &dest);
protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
public:
    DVEClient();
    virtual ~DVEClient();
};

#endif /* DVECLIENT_H_ */
