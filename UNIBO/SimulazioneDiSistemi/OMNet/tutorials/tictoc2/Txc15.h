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

#ifndef TXC15_H_
#define TXC15_H_

#include <stdio.h>
#include <string.h>
#include <omnetpp.h>
#include "TicTocMsg15_m.h"

class Txc15 : public cSimpleModule {
private:
    long sentPkgs;
    long receivedPkgs;
    cLongHistogram hopCountStats;
    cOutVector hopCountVector;
protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
    virtual void forwardMessage(cMessage *msg);
    virtual TicTocMsg15* generateMessage();
    virtual void updateDisplay();
    // The finish() function is called by OMNeT++ at the end of the simulation.
    virtual void finish();
};


#endif /* TXC15_H_ */
