//
// Generated file, do not edit! Created by opp_msgc 4.5 from ACKMsg.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "ACKMsg_m.h"

USING_NAMESPACE


// Another default rule (prevents compiler from choosing base class' doPacking())
template<typename T>
void doPacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doPacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}

template<typename T>
void doUnpacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doUnpacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}




// Template rule for outputting std::vector<T> types
template<typename T, typename A>
inline std::ostream& operator<<(std::ostream& out, const std::vector<T,A>& vec)
{
    out.put('{');
    for(typename std::vector<T,A>::const_iterator it = vec.begin(); it != vec.end(); ++it)
    {
        if (it != vec.begin()) {
            out.put(','); out.put(' ');
        }
        out << *it;
    }
    out.put('}');
    
    char buf[32];
    sprintf(buf, " (size=%u)", (unsigned int)vec.size());
    out.write(buf, strlen(buf));
    return out;
}

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
inline std::ostream& operator<<(std::ostream& out,const T&) {return out;}

Register_Class(ACKMsg);

ACKMsg::ACKMsg(const char *name, int kind) : ::cMessage(name,kind)
{
    this->movedID_var = 0;
    this->serverID_var = 0;
    this->isMoveComplete_var = 0;
}

ACKMsg::ACKMsg(const ACKMsg& other) : ::cMessage(other)
{
    copy(other);
}

ACKMsg::~ACKMsg()
{
}

ACKMsg& ACKMsg::operator=(const ACKMsg& other)
{
    if (this==&other) return *this;
    ::cMessage::operator=(other);
    copy(other);
    return *this;
}

void ACKMsg::copy(const ACKMsg& other)
{
    this->movedID_var = other.movedID_var;
    this->serverID_var = other.serverID_var;
    this->isMoveComplete_var = other.isMoveComplete_var;
}

void ACKMsg::parsimPack(cCommBuffer *b)
{
    ::cMessage::parsimPack(b);
    doPacking(b,this->movedID_var);
    doPacking(b,this->serverID_var);
    doPacking(b,this->isMoveComplete_var);
}

void ACKMsg::parsimUnpack(cCommBuffer *b)
{
    ::cMessage::parsimUnpack(b);
    doUnpacking(b,this->movedID_var);
    doUnpacking(b,this->serverID_var);
    doUnpacking(b,this->isMoveComplete_var);
}

int ACKMsg::getMovedID() const
{
    return movedID_var;
}

void ACKMsg::setMovedID(int movedID)
{
    this->movedID_var = movedID;
}

int ACKMsg::getServerID() const
{
    return serverID_var;
}

void ACKMsg::setServerID(int serverID)
{
    this->serverID_var = serverID;
}

bool ACKMsg::getIsMoveComplete() const
{
    return isMoveComplete_var;
}

void ACKMsg::setIsMoveComplete(bool isMoveComplete)
{
    this->isMoveComplete_var = isMoveComplete;
}

class ACKMsgDescriptor : public cClassDescriptor
{
  public:
    ACKMsgDescriptor();
    virtual ~ACKMsgDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(ACKMsgDescriptor);

ACKMsgDescriptor::ACKMsgDescriptor() : cClassDescriptor("ACKMsg", "cMessage")
{
}

ACKMsgDescriptor::~ACKMsgDescriptor()
{
}

bool ACKMsgDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<ACKMsg *>(obj)!=NULL;
}

const char *ACKMsgDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int ACKMsgDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount(object) : 3;
}

unsigned int ACKMsgDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<3) ? fieldTypeFlags[field] : 0;
}

const char *ACKMsgDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "movedID",
        "serverID",
        "isMoveComplete",
    };
    return (field>=0 && field<3) ? fieldNames[field] : NULL;
}

int ACKMsgDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='m' && strcmp(fieldName, "movedID")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "serverID")==0) return base+1;
    if (fieldName[0]=='i' && strcmp(fieldName, "isMoveComplete")==0) return base+2;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *ACKMsgDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "int",
        "bool",
    };
    return (field>=0 && field<3) ? fieldTypeStrings[field] : NULL;
}

const char *ACKMsgDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int ACKMsgDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    ACKMsg *pp = (ACKMsg *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string ACKMsgDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    ACKMsg *pp = (ACKMsg *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getMovedID());
        case 1: return long2string(pp->getServerID());
        case 2: return bool2string(pp->getIsMoveComplete());
        default: return "";
    }
}

bool ACKMsgDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    ACKMsg *pp = (ACKMsg *)object; (void)pp;
    switch (field) {
        case 0: pp->setMovedID(string2long(value)); return true;
        case 1: pp->setServerID(string2long(value)); return true;
        case 2: pp->setIsMoveComplete(string2bool(value)); return true;
        default: return false;
    }
}

const char *ACKMsgDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    };
}

void *ACKMsgDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    ACKMsg *pp = (ACKMsg *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


