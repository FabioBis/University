/*
 * Txc7.cpp
 *
 *  Created on: 03/dic/2014
 *      Author: Fabio
 */

#include <Txc7.h>


// The module class need to be registered with OMNet++.
Define_Module(Txc7);

Txc7::Txc7()
{
    // Set the pointer to NULL, so that the destructor won't crash
    // even if initialize() doesn't get called because of a runtime
    // error or user cancellation during the startup process.
    event = tictocMsg = NULL;
}

Txc7::~Txc7()
{
    // Dispose of dynamically allocated the objects.
    cancelAndDelete(event);
    delete tictocMsg;
}

void
Txc7::initialize()
{
    // Initialize the counter to 10.
    counter = par("limit");
    // Create the event object we'll use for timing -- just any ordinary message.
    event = new cMessage("event");


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
Txc7::handleMessage(cMessage *msg)
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
        send(tictocMsg, "out");
        tictocMsg = NULL;
    }
    else
    {
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
            if (uniform(0,1) < 0.1)
            {
                // Simulate a message lost with 0.1 probability.
                EV << "\"Losing\" message\n";
                delete msg;
            }
            else
            {
                // The "delayTime" module parameter can be set to values like
                // "exponential(5)" (tictoc7.ned, omnetpp.ini), and then here
                // we'll get a different delay every time.
                simtime_t delay = par("delayTime");
                EV << "Message arrived, starting to wait 1 sec...\n"
                        << getName() << "'s counter is " << counter
                        << ", sending back message\n";
                tictocMsg = msg;
                scheduleAt(simTime() + delay, event);
            }
        }
    }
}
