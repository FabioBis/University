/*
 * Txc6.h
 *
 *  Created on: 02/dic/2014
 *      Author: Fabio
 */

#ifndef TXC6_H_
#define TXC6_H_

#include <string.h>
#include <omnetpp.h>
#include <stdio.h>

class Txc6 : public cSimpleModule
{
private:
    cMessage *event;
    cMessage *tictocMsg;
    int counter;
public:
    Txc6();
    virtual ~Txc6();
protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
};

#endif /* TXC6_H_ */
