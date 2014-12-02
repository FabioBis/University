/*
 * Txc4.h
 *
 *  Created on: 02/dic/2014
 *      Author: Fabio
 */

#ifndef TXC4_H_
#define TXC4_H_

#include <string.h>
#include <omnetpp.h>

class Txc4 : public cSimpleModule {
private:
    int counter;
protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
};

#endif /* TXC4_H_ */
