/*
 * Txc3.h
 *
 *  Created on: 02/dic/2014
 *      Author: Fabio
 */

#ifndef TXC3_H_
#define TXC3_H_

#include <string.h>
#include <omnetpp.h>

class Txc3 : public cSimpleModule {
private:
    int counter;
protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
};

#endif /* TXC3_H_ */
