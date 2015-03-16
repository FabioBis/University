//
// Generated file, do not edit! Created by opp_msgc 4.5 from ACKMsg.msg.
//

#ifndef _ACKMSG_M_H_
#define _ACKMSG_M_H_

#include <omnetpp.h>

// opp_msgc version check
#define MSGC_VERSION 0x0405
#if (MSGC_VERSION!=OMNETPP_VERSION)
#    error Version mismatch! Probably this file was generated by an earlier version of opp_msgc: 'make clean' should help.
#endif



/**
 * Class generated from <tt>ACKMsg.msg</tt> by opp_msgc.
 * <pre>
 * message ACKMsg
 * {
 *     
 * 	int movedID;
 * 	int serverID;
 * 	
 * 	bool isMoveComplete;
 * }
 * </pre>
 */
class ACKMsg : public ::cMessage
{
  protected:
    int movedID_var;
    int serverID_var;
    bool isMoveComplete_var;

  private:
    void copy(const ACKMsg& other);

  protected:
    // protected and unimplemented operator==(), to prevent accidental usage
    bool operator==(const ACKMsg&);

  public:
    ACKMsg(const char *name=NULL, int kind=0);
    ACKMsg(const ACKMsg& other);
    virtual ~ACKMsg();
    ACKMsg& operator=(const ACKMsg& other);
    virtual ACKMsg *dup() const {return new ACKMsg(*this);}
    virtual void parsimPack(cCommBuffer *b);
    virtual void parsimUnpack(cCommBuffer *b);

    // field getter/setter methods
    virtual int getMovedID() const;
    virtual void setMovedID(int movedID);
    virtual int getServerID() const;
    virtual void setServerID(int serverID);
    virtual bool getIsMoveComplete() const;
    virtual void setIsMoveComplete(bool isMoveComplete);
};

inline void doPacking(cCommBuffer *b, ACKMsg& obj) {obj.parsimPack(b);}
inline void doUnpacking(cCommBuffer *b, ACKMsg& obj) {obj.parsimUnpack(b);}


#endif // _ACKMSG_M_H_
