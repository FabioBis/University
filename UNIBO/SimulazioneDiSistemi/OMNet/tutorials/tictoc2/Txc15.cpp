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

#include <Txc15.h>

Define_Module(Txc15);

void
Txc15::initialize()
{
    // Initialize variables.
    sentPkgs = 0;
    receivedPkgs = 0;
    // Make them observable.
    WATCH(sentPkgs);
    WATCH(receivedPkgs);

    hopCountStats.setName("hopCountStats");
    hopCountStats.setRangeAutoUpper(0, 10, 1.5);
    hopCountVector.setName("HopCount");

    if (getIndex() == 0)
    {
        // Boot the process scheduling the initial message as self message.
        TicTocMsg15 *msg = generateMessage();
        scheduleAt(0.0, msg);
    }
}

void
Txc15::handleMessage(cMessage *msg)
{
    // check_and_cast from omnetpp.h perform a dynamic cast or raise an error
    // during the simulation instead of crash.
    TicTocMsg15 *ttmsg = check_and_cast<TicTocMsg15 *>(msg);
    if (ttmsg->getDestination() == getIndex())
    {
        // Message arrived.
        int hopcount = ttmsg->getHopCount();
        hopCountVector.record(hopcount);
        hopCountStats.collect(hopcount);
        EV << "Message " << ttmsg <<" arrived after " << hopcount
                << " messages.\n";
        receivedPkgs++;
        delete ttmsg;
        bubble("ARRIVED, starting a new one.");

        // Generate another message.
        TicTocMsg15 *newmsg = generateMessage();
        EV <<newmsg << endl;
        forwardMessage(newmsg);
        sentPkgs++;
    }
    else
    {
        // We need to forward the message.
        forwardMessage(ttmsg);
    }
}

void
Txc15::forwardMessage(cMessage *msg)
{
    // check_and_cast from omnetpp.h perform a dynamic cast or raise an error
    // during the simulation instead of crash.
    TicTocMsg15 *ttmsg = check_and_cast<TicTocMsg15 *>(msg);

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

    if (ev.isGUI())
    {
        updateDisplay();
    }
}

TicTocMsg15*
Txc15::generateMessage()
{
    // The "current" module index.
    int src = getIndex();
    // The module size.
    int n = size();
    int dest = intuniform(0, n-2);
    if (dest >= src)
    {
        dest++;
    }

    char msgname[20];
    sprintf(msgname, "tic-%d-to-%d", src, dest);

    // Create message object and set source and destination field.
    TicTocMsg15 *msg = new TicTocMsg15(msgname);
    msg->setSource(src);
    msg->setDestination(dest);
    return msg;
}

void
Txc15::updateDisplay()
{
    char buf[40];
    sprintf(buf, "rcvd: %ld sent: %ld", receivedPkgs, sentPkgs);
    getDisplayString().setTagArg("t",0,buf);
}

void
Txc15::finish()
{
    // This function is called by OMNeT++ at the end of the simulation.
    EV << "Sent:     " << sentPkgs << endl;
    EV << "Received: " << receivedPkgs << endl;
    EV << "Hop count, min:    " << hopCountStats.getMin() << endl;
    EV << "Hop count, max:    " << hopCountStats.getMax() << endl;
    EV << "Hop count, mean:   " << hopCountStats.getMean() << endl;
    EV << "Hop count, stddev: " << hopCountStats.getStddev() << endl;

    recordScalar("#sent", sentPkgs);
    recordScalar("#received", receivedPkgs);

    hopCountStats.recordAs("hop count");
}
