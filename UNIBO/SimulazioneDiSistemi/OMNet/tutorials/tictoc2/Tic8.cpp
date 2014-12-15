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

#include <Tic8.h>

// The module class need to be registered with OMNet++.
Define_Module(Tic8);

Tic8::Tic8()
{
    // Set the pointer to NULL, so that the destructor won't crash
    // even if initialize() doesn't get called because of a runtime
    // error or user cancellation during the startup process.
    event = tictocMsg = NULL;
}

Tic8::~Tic8()
{
    // Dispose of dynamically allocated the objects.
    cancelAndDelete(event);
    delete tictocMsg;
}

void
Tic8::initialize()
{
    // Initialize the counter to 10.
    counter = par("limit");
    // Create the event object we'll use for timing -- just any ordinary message.
    event = new cMessage("event");
    timeoutEvent = new cMessage("timeoutEvent");
    // Initialize timeout.
    timeout = 20.0;


    // The WATCH() statement below will let you examine the variable under
    // Tkenv. After doing a few steps in the simulation, double-click either
    // `tic' or `toc', select the Contents tab in the dialog that pops up,
    // and you'll find "counter" in the list.
    WATCH(counter);

    if(par("sendMsgOnInit").boolValue() == true)
    {
        // We don't start right away, but instead send an message to ourselves
        // (a "self-message") -- we'll do the first sending when it arrives
        // back to us, at t=5.0s simulated time.
        EV << "Scheduling first send to t=5.0s\n";
        tictocMsg = new cMessage("tictocMsg");
        scheduleAt(5.0, event);
    }
}

void
Tic8::handleMessage(cMessage *msg)
{
    // There are several ways of distinguishing messages, for example by message
    // kind (an int attribute of cMessage) or by class using dynamic_cast
    // (provided you subclass from cMessage). In this code we just check if we
    // recognize the pointer, which (if feasible) is the easiest and fastest
    // method.
    if (msg == event)
    {
        // The self-message arrived, so we can send out tictocMsg and NULL out
        // its pointer so that it doesn't confuse us later.
        EV << "Wait period is over, sending back message\n";
        sendMessage();
        tictocMsg = NULL;
    }
    else if (msg == timeoutEvent)
    {
        // If we receive the timeout event, that means the packet hasn't
        // arrived in time and we have to re-send it.
        EV << "Timeout expired, resending message and restarting timer\n";
        sendMessage();
    }
    else
    {
        // Acknowledgement received -- delete the received message and cancel
        // the timeout event.
        EV << "Timer cancelled.\n";
        cancelEvent(timeoutEvent);

        // If the message we received is not our self-message, then it must
        // be the tic-toc message arriving from our partner. We remember its
        // pointer in the tictocMsg variable, then schedule our self-message
        // to come back to us in 1s simulated time.
        counter--;
        if (counter == 0)
        {
            // If counter is zero, delete message. If you run the model, you'll
            // find that the simulation will stop at this point with the message
            // "no more events".
            EV << "Message arrived, starting to wait 1 sec...\n" << getName()
                    << "'s counter reached zero, deleting message\n";
            delete msg;
        }
        else
        {
            EV << "Message arrived, starting to wait 1 sec...\n" << getName()
                    << "'s counter is " << counter << ", sending back message\n";
            tictocMsg = msg;
            scheduleAt(simTime() + 1.0, event);
        }
    }
}

void
Tic8::sendMessage()
{
    cMessage *msg = new cMessage("tictocMsg");
    send(msg, "out");
    scheduleAt(simTime() + timeout, timeoutEvent);
}
