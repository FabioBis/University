/*
 * Txc3.cpp
 *
 *  Created on: 02/dic/2014
 *      Author: Fabio
 */

#include <Txc3.h>

// The module class need to be registered with OMNet++.
Define_Module(Txc3);

void
Txc3::initialize()
{
    // Initialize the counter to 10.
    counter = 10;

    // The WATCH() statement below will let you examine the variable under
    // Tkenv. After doing a few steps in the simulation, double-click either
    // `tic' or `toc', select the Contents tab in the dialog that pops up,
    // and you'll find "counter" in the list.
    WATCH(counter);

    if(strcmp("tic", getName()) == 0)
    {
        cMessage *msg = new cMessage("tictoc");
        EV << "Sending initial message\n";
        send(msg, "out");
    }
}

void
Txc3::handleMessage(cMessage *msg)
{
    counter--;
    if (counter == 0)
    {
        // If counter is zero, delete message. If you run the model, you'll
        // find that the simulation will stop at this point with the message
        // "no more events".
        EV << getName() << "'s counter reached zero, deleting message\n";
        delete msg;
    }
    else
    {
        EV << getName() << "'s counter is " << counter
                << ", sending back message\n";
        send(msg, "out");
    }
}
