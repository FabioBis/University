//
// Generated file, do not edit! Created by opp_msgc 4.5 from ServerUpdateMsg.msg.
//

#ifndef _SERVERUPDATEMSG_M_H_
#define _SERVERUPDATEMSG_M_H_

#include <omnetpp.h>

// opp_msgc version check
#define MSGC_VERSION 0x0405
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of opp_msgc: 'make clean' should help.
#endif



/**
 * Class generated from <tt>ServerUpdateMsg.msg</tt> by opp_msgc.
 * <pre>
 * message ServerUpdateMsg
 * {
 *     
 * 	int serverID;
 * 	
 * 	int clients[];
 * }
 * </pre>
 */
class ServerUpdateMsg : public ::cMessage
{
  protected:
    int serverID_var;
    int *clients_var; // array ptr
    unsigned int clients_arraysize;

  private:
    void copy(const ServerUpdateMsg& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const ServerUpdateMsg&);

  public:
    ServerUpdateMsg(const char *name=NULL, int kind=0);
    ServerUpdateMsg(const ServerUpdateMsg& other);
    virtual ~ServerUpdateMsg();
    ServerUpdateMsg& operator=(const ServerUpdateMsg& other);
    virtual ServerUpdateMsg *dup() const {return new ServerUpdateMsg(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual int getServerID() const;
    virtual void setServerID(int serverID);
    virtual void setClientsArraySize(unsigned int size);
    virtual unsigned int getClientsArraySize() const;
    virtual int getClients(unsigned int k) const;
    virtual void setClients(unsigned int k, int clients);
};

inline void doPacking(cCommBuffer *b, ServerUpdateMsg& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, ServerUpdateMsg& obj) {obj.parsimUnpack(b);}


#endif // _SERVERUPDATEMSG_M_H_
