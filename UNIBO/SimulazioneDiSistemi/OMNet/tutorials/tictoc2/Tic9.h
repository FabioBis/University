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

#ifndef TIC9_H_
#define TIC9_H_

#include <string.h>
#include <omnetpp.h>
#include <stdio.h>

class Tic9 : public cSimpleModule {
private:
    cMessage *event;
    cMessage *tictocMsg;
    cMessage *timeoutEvent;
    simtime_t timeout;
    int counter;
    int seq;
    cMessage* generateNewMessage();
    void sendCopyOf(cMessage *message);
public:
    Tic9();
    virtual ~Tic9();
protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
};

#endif /* TIC9_H_ */
