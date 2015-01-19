//
// Generated file, do not edit! Created by opp_msgc 4.5 from ServerUpdateMsg.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "ServerUpdateMsg_m.h"

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

Register_Class(ServerUpdateMsg);

ServerUpdateMsg::ServerUpdateMsg(const char *name, int kind) : ::cMessage(name,kind)
{
    this->server_var = 0;
    clients_arraysize = 0;
    this->clients_var = 0;
}

ServerUpdateMsg::ServerUpdateMsg(const ServerUpdateMsg& other) : ::cMessage(other)
{
    clients_arraysize = 0;
    this->clients_var = 0;
    copy(other);
}

ServerUpdateMsg::~ServerUpdateMsg()
{
    delete [] clients_var;
}

ServerUpdateMsg& ServerUpdateMsg::operator=(const ServerUpdateMsg& other)
{
    if (this==&other) return *this;
    ::cMessage::operator=(other);
    copy(other);
    return *this;
}

void ServerUpdateMsg::copy(const ServerUpdateMsg& other)
{
    this->server_var = other.server_var;
    delete [] this->clients_var;
    this->clients_var = (other.clients_arraysize==0) ? NULL : new int[other.clients_arraysize];
    clients_arraysize = other.clients_arraysize;
    for (unsigned int i=0; i<clients_arraysize; i++)
        this->clients_var[i] = other.clients_var[i];
}

void ServerUpdateMsg::parsimPack(cCommBuffer *b)
{
    ::cMessage::parsimPack(b);
    doPacking(b,this->server_var);
    b->pack(clients_arraysize);
    doPacking(b,this->clients_var,clients_arraysize);
}

void ServerUpdateMsg::parsimUnpack(cCommBuffer *b)
{
    ::cMessage::parsimUnpack(b);
    doUnpacking(b,this->server_var);
    delete [] this->clients_var;
    b->unpack(clients_arraysize);
    if (clients_arraysize==0) {
        this->clients_var = 0;
    } else {
        this->clients_var = new int[clients_arraysize];
        doUnpacking(b,this->clients_var,clients_arraysize);
    }
}

int ServerUpdateMsg::getServer() const
{
    return server_var;
}

void ServerUpdateMsg::setServer(int server)
{
    this->server_var = server;
}

void ServerUpdateMsg::setClientsArraySize(unsigned int size)
{
    int *clients_var2 = (size==0) ? NULL : new int[size];
    unsigned int sz = clients_arraysize < size ? clients_arraysize : size;
    for (unsigned int i=0; i<sz; i++)
        clients_var2[i] = this->clients_var[i];
    for (unsigned int i=sz; i<size; i++)
        clients_var2[i] = 0;
    clients_arraysize = size;
    delete [] this->clients_var;
    this->clients_var = clients_var2;
}

unsigned int ServerUpdateMsg::getClientsArraySize() const
{
    return clients_arraysize;
}

int ServerUpdateMsg::getClients(unsigned int k) const
{
    if (k>=clients_arraysize) throw cRuntimeError("Array of size %d indexed by %d", clients_arraysize, k);
    return clients_var[k];
}

void ServerUpdateMsg::setClients(unsigned int k, int clients)
{
    if (k>=clients_arraysize) throw cRuntimeError("Array of size %d indexed by %d", clients_arraysize, k);
    this->clients_var[k] = clients;
}

class ServerUpdateMsgDescriptor : public cClassDescriptor
{
  public:
    ServerUpdateMsgDescriptor();
    virtual ~ServerUpdateMsgDescriptor();

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

Register_ClassDescriptor(ServerUpdateMsgDescriptor);

ServerUpdateMsgDescriptor::ServerUpdateMsgDescriptor() : cClassDescriptor("ServerUpdateMsg", "cMessage")
{
}

ServerUpdateMsgDescriptor::~ServerUpdateMsgDescriptor()
{
}

bool ServerUpdateMsgDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<ServerUpdateMsg *>(obj)!=NULL;
}

const char *ServerUpdateMsgDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int ServerUpdateMsgDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount(object) : 2;
}

unsigned int ServerUpdateMsgDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISARRAY | FD_ISEDITABLE,
    };
    return (field>=0 && field<2) ? fieldTypeFlags[field] : 0;
}

const char *ServerUpdateMsgDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "server",
        "clients",
    };
    return (field>=0 && field<2) ? fieldNames[field] : NULL;
}

int ServerUpdateMsgDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='s' && strcmp(fieldName, "server")==0) return base+0;
    if (fieldName[0]=='c' && strcmp(fieldName, "clients")==0) return base+1;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *ServerUpdateMsgDescriptor::getFieldTypeString(void *object, int field) const
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
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : NULL;
}

const char *ServerUpdateMsgDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int ServerUpdateMsgDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    ServerUpdateMsg *pp = (ServerUpdateMsg *)object; (void)pp;
    switch (field) {
        case 1: return pp->getClientsArraySize();
        default: return 0;
    }
}

std::string ServerUpdateMsgDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    ServerUpdateMsg *pp = (ServerUpdateMsg *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getServer());
        case 1: return long2string(pp->getClients(i));
        default: return "";
    }
}

bool ServerUpdateMsgDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    ServerUpdateMsg *pp = (ServerUpdateMsg *)object; (void)pp;
    switch (field) {
        case 0: pp->setServer(string2long(value)); return true;
        case 1: pp->setClients(i,string2long(value)); return true;
        default: return false;
    }
}

const char *ServerUpdateMsgDescriptor::getFieldStructName(void *object, int field) const
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

void *ServerUpdateMsgDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    ServerUpdateMsg *pp = (ServerUpdateMsg *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


