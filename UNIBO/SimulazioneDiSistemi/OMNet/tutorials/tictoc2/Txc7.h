/*
 * Txc7.h
 *
 *  Created on: 03/dic/2014
 *      Author: Fabio
 */

#ifndef TXC7_H_
#define TXC7_H_

#include <string.h>
#include <omnetpp.h>
#include <stdio.h>

class Txc7  : public cSimpleModule
{
private:
    cMessage *event;
    cMessage *tictocMsg;
    int counter;
public:
    Txc7();
    virtual ~Txc7();
protected:
    virtual void initialize();
    virtual void handleMessage(cMessage *msg);
};

#endif /* TXC7_H_ */
