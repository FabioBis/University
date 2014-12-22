/*
 * Tictoc2.cpp
 *
 *  Created on: 02/dic/2014
 *      Author: Fabio
 */

#include <Txc2.h>

// The module class need to be registered with OMNet++.
Define_Module(Txc2);

void
Txc2::initialize()
{
    if(strcmp("tic", getName()) == 0)
    {
        cMessage *msg = new cMessage("tictoc");
        EV << "Sending initial message\n";
        send(msg, "out");
    }
}

void
Txc2::handleMessage(cMessage *msg)
{
    EV << "Received message '" << msg->getName() << "', sending it out again";
    send(msg, "out");
}
