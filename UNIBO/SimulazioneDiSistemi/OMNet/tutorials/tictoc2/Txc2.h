/*
 * Tictoc2.h
 *
 *  Created on: 02/dic/2014
 *      Author: Fabio
 */

#ifndef TXC2_H_
#define TXC2_H_

#include <string.h>
#include <omnetpp.h>

class Txc2 : public cSimpleModule
{
protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
};

#endif /* TXC2_H_ */
