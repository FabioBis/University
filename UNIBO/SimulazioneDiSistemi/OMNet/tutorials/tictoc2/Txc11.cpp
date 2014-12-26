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

#include <Txc11.h>

Define_Module(Txc11);

void
Txc11::initialize()
{
    if (getIndex() == 0)
    {
        char msgname[20];
        sprintf(msgname, "tic-%d", getIndex());
        cMessage *msg = new cMessage(msgname);
        scheduleAt(0.0, msg);
    }
}

void
Txc11::handleMessage(cMessage *msg)
{
    if (getIndex() == 3)
    {
        // Message arrived.
        EV << "Message " << msg <<" arrived.\n";
        delete msg;
    }
    else
    {
        // We need to forward the message.
        forwardMessage(msg);
    }
}

void
Txc11::forwardMessage(cMessage *msg)
{
    // In this example, we just pick a random gate to send it on.
    int n = gateSize("out");
    EV << "Forwarding message...\n" <<"..Gate size: " << n <<";\n";
    // We draw a random number between 0 and n-1.
    int k = intuniform(0, n-1);
    EV << ".." <<msg <<" on port out[" <<k <<"].\n";
    send(msg, "out", k);
}
