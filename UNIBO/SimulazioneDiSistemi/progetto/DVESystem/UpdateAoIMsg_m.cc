//
// Generated file, do not edit! Created by opp_msgc 4.5 from UpdateAoIMsg.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "UpdateAoIMsg_m.h"

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

Register_Class(UpdateAoIMsg);

UpdateAoIMsg::UpdateAoIMsg(const char *name, int kind) : ::cMessage(name,kind)
{
    this->clientMoved_var = 0;
    this->clientDest_var = 0;
    this->serverID_var = 0;
    aoi_arraysize = 0;
    this->aoi_var = 0;
}

UpdateAoIMsg::UpdateAoIMsg(const UpdateAoIMsg& other) : ::cMessage(other)
{
    aoi_arraysize = 0;
    this->aoi_var = 0;
    copy(other);
}

UpdateAoIMsg::~UpdateAoIMsg()
{
    delete [] aoi_var;
}

UpdateAoIMsg& UpdateAoIMsg::operator=(const UpdateAoIMsg& other)
{
    if (this==&other) return *this;
    ::cMessage::operator=(other);
    copy(other);
    return *this;
}

void UpdateAoIMsg::copy(const UpdateAoIMsg& other)
{
    this->clientMoved_var = other.clientMoved_var;
    this->clientDest_var = other.clientDest_var;
    this->serverID_var = other.serverID_var;
    delete [] this->aoi_var;
    this->aoi_var = (other.aoi_arraysize==0) ? NULL : new int[other.aoi_arraysize];
    aoi_arraysize = other.aoi_arraysize;
    for (unsigned int i=0; i<aoi_arraysize; i++)
        this->aoi_var[i] = other.aoi_var[i];
}

void UpdateAoIMsg::parsimPack(cCommBuffer *b)
{
    ::cMessage::parsimPack(b);
    doPacking(b,this->clientMoved_var);
    doPacking(b,this->clientDest_var);
    doPacking(b,this->serverID_var);
    b->pack(aoi_arraysize);
    doPacking(b,this->aoi_var,aoi_arraysize);
}

void UpdateAoIMsg::parsimUnpack(cCommBuffer *b)
{
    ::cMessage::parsimUnpack(b);
    doUnpacking(b,this->clientMoved_var);
    doUnpacking(b,this->clientDest_var);
    doUnpacking(b,this->serverID_var);
    delete [] this->aoi_var;
    b->unpack(aoi_arraysize);
    if (aoi_arraysize==0) {
        this->aoi_var = 0;
    } else {
        this->aoi_var = new int[aoi_arraysize];
        doUnpacking(b,this->aoi_var,aoi_arraysize);
    }
}

int UpdateAoIMsg::getClientMoved() const
{
    return clientMoved_var;
}

void UpdateAoIMsg::setClientMoved(int clientMoved)
{
    this->clientMoved_var = clientMoved;
}

int UpdateAoIMsg::getClientDest() const
{
    return clientDest_var;
}

void UpdateAoIMsg::setClientDest(int clientDest)
{
    this->clientDest_var = clientDest;
}

int UpdateAoIMsg::getServerID() const
{
    return serverID_var;
}

void UpdateAoIMsg::setServerID(int serverID)
{
    this->serverID_var = serverID;
}

void UpdateAoIMsg::setAoiArraySize(unsigned int size)
{
    int *aoi_var2 = (size==0) ? NULL : new int[size];
    unsigned int sz = aoi_arraysize < size ? aoi_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        aoi_var2[i] = this->aoi_var[i];
    for (unsigned int i=sz; i<size; i++)
        aoi_var2[i] = 0;
    aoi_arraysize = size;
    delete [] this->aoi_var;
    this->aoi_var = aoi_var2;
}

unsigned int UpdateAoIMsg::getAoiArraySize() const
{
    return aoi_arraysize;
}

int UpdateAoIMsg::getAoi(unsigned int k) const
{
    if (k>=aoi_arraysize) throw cRuntimeError("Array of size %d indexed by %d", aoi_arraysize, k);
    return aoi_var[k];
}

void UpdateAoIMsg::setAoi(unsigned int k, int aoi)
{
    if (k>=aoi_arraysize) throw cRuntimeError("Array of size %d indexed by %d", aoi_arraysize, k);
    this->aoi_var[k] = aoi;
}

class UpdateAoIMsgDescriptor : public cClassDescriptor
{
  public:
    UpdateAoIMsgDescriptor();
    virtual ~UpdateAoIMsgDescriptor();

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

Register_ClassDescriptor(UpdateAoIMsgDescriptor);

UpdateAoIMsgDescriptor::UpdateAoIMsgDescriptor() : cClassDescriptor("UpdateAoIMsg", "cMessage")
{
}

UpdateAoIMsgDescriptor::~UpdateAoIMsgDescriptor()
{
}

bool UpdateAoIMsgDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<UpdateAoIMsg *>(obj)!=NULL;
}

const char *UpdateAoIMsgDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int UpdateAoIMsgDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 4+basedesc->getFieldCount(object) : 4;
}

unsigned int UpdateAoIMsgDescriptor::getFieldTypeFlags(void *object, int field) const
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
        FD_ISARRAY | FD_ISEDITABLE,
    };
    return (field>=0 && field<4) ? fieldTypeFlags[field] : 0;
}

const char *UpdateAoIMsgDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "clientMoved",
        "clientDest",
        "serverID",
        "aoi",
    };
    return (field>=0 && field<4) ? fieldNames[field] : NULL;
}

int UpdateAoIMsgDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='c' && strcmp(fieldName, "clientMoved")==0) return base+0;
    if (fieldName[0]=='c' && strcmp(fieldName, "clientDest")==0) return base+1;
    if (fieldName[0]=='s' && strcmp(fieldName, "serverID")==0) return base+2;
    if (fieldName[0]=='a' && strcmp(fieldName, "aoi")==0) return base+3;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *UpdateAoIMsgDescriptor::getFieldTypeString(void *object, int field) const
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
        "int",
        "int",
    };
    return (field>=0 && field<4) ? fieldTypeStrings[field] : NULL;
}

const char *UpdateAoIMsgDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int UpdateAoIMsgDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    UpdateAoIMsg *pp = (UpdateAoIMsg *)object; (void)pp;
    switch (field) {
        case 3: return pp->getAoiArraySize();
        default: return 0;
    }
}

std::string UpdateAoIMsgDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    UpdateAoIMsg *pp = (UpdateAoIMsg *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getClientMoved());
        case 1: return long2string(pp->getClientDest());
        case 2: return long2string(pp->getServerID());
        case 3: return long2string(pp->getAoi(i));
        default: return "";
    }
}

bool UpdateAoIMsgDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    UpdateAoIMsg *pp = (UpdateAoIMsg *)object; (void)pp;
    switch (field) {
        case 0: pp->setClientMoved(string2long(value)); return true;
        case 1: pp->setClientDest(string2long(value)); return true;
        case 2: pp->setServerID(string2long(value)); return true;
        case 3: pp->setAoi(i,string2long(value)); return true;
        default: return false;
    }
}

const char *UpdateAoIMsgDescriptor::getFieldStructName(void *object, int field) const
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

void *UpdateAoIMsgDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    UpdateAoIMsg *pp = (UpdateAoIMsg *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


