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

#include <Txc13.h>

Define_Module(Txc13);

void
Txc13::initialize()
{
    if (getIndex() == 0)
    {
        // Boot the process scheduling the initial message as self message.
        TicTocMsg13 *msg = generateMessage();
        scheduleAt(0.0, msg);
    }
}

void
Txc13::handleMessage(cMessage *msg)
{
    // check_and_cast from omnetpp.h perform a dynamic cast or raise an error
    // during the simulation instead of crash.
    TicTocMsg13 *ttmsg = check_and_cast<TicTocMsg13 *>(msg);
    if (ttmsg->getDestination() == getIndex())
    {
        // Message arrived.
        EV << "Message " << msg <<" arrived.\n";
        bubble("ARRIVED, starting a new one.");
        delete ttmsg;

        // Generate another message.
        TicTocMsg13 *newmsg = generateMessage();
        EV <<newmsg << endl;
        forwardMessage(newmsg);
    }
    else
    {
        // We need to forward the message.
        forwardMessage(ttmsg);
    }
}

void
Txc13::forwardMessage(cMessage *msg)
{
    // check_and_cast from omnetpp.h perform a dynamic cast or raise an error
    // during the simulation instead of crash.
    TicTocMsg13 *ttmsg = check_and_cast<TicTocMsg13 *>(msg);

    // Incrementing the hop count.
    ttmsg->setHopCount(ttmsg->getHopCount() + 1);

    // In this example, we just pick a random gate to send it on.
    int n = gateSize("gate");
    EV << "Forwarding message...\n" <<"..Gate size: " << n <<";\n";
    // We draw a random number between 0 and n-1.
    int k = intuniform(0, n-1);
    EV << ".." <<msg <<" on gate[" <<k <<"].\n";
    // $o and $i suffix is used to identify the input/output part of a two way gate.
    send(ttmsg, "gate$o", k);
}

TicTocMsg13*
Txc13::generateMessage()
{
    // The "current" module index.
    int src = getIndex();
    // The module size.
    int n = size();
    int dest = intuniform(0, n-1);
    if (dest >= src)
    {
        dest++;
    }

    char msgname[20];
    sprintf(msgname, "tic-%d-to-%d", src, dest);

    // Create message object and set source and destination field.
    TicTocMsg13 *msg = new TicTocMsg13(msgname);
    msg->setSource(src);
    msg->setDestination(dest);
    return msg;
}

