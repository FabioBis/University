/*
 * Txc1.h
 *
 *  Created on: 02/dic/2014
 *      Author: Fabio
 */

#ifndef TXC1_H_
#define TXC1_H_

#include <string.h>
#include <omnetpp.h>

class Txc1 : public cSimpleModule
{
protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
};

#endif /* TXC1_H_ */
