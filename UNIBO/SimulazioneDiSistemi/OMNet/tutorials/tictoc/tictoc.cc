#include <string.h>
#include <omnetpp.h>

class Txc1 : public cSimpleModule
{
protected:
  virtual void initialize();
  virtual void handleMessage(cMessage *msg);
};

// The module class need to be registered with OMNet++.
Define_Module(Txc1);

void
Txc1::initialize()
{
  if (strcmp("tic", getName()) == 0)
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
