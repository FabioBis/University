/*
 * Txc1.cpp
 *
 *  Created on: 02/dic/2014
 *      Author: Fabio
 */

#include <Txc1.h>

// The module class need to be registered with OMNet++.
Define_Module(Txc1);

void
Txc1::initialize()
{
    if(strcmp("tic", getName()) == 0)
    {
        cMessage *msg = new cMessage("tictoc");
        send(msg, "out");
    }
}

void
Txc1::handleMessage(cMessage *msg)
{
    send(msg, "out");
}
