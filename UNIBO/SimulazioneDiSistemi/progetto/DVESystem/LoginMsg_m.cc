//
// Generated file, do not edit! Created by opp_msgc 4.5 from LoginMsg.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "LoginMsg_m.h"

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

Register_Class(LoginMsg);

LoginMsg::LoginMsg(const char *name, int kind) : ::cMessage(name,kind)
{
    this->ID_var = 0;
    this->x_var = 0;
    this->y_var = 0;
    this->serverID_var = 0;
    aoi_arraysize = 0;
    this->aoi_var = 0;
}

LoginMsg::LoginMsg(const LoginMsg& other) : ::cMessage(other)
{
    aoi_arraysize = 0;
    this->aoi_var = 0;
    copy(other);
}

LoginMsg::~LoginMsg()
{
    delete [] aoi_var;
}

LoginMsg& LoginMsg::operator=(const LoginMsg& other)
{
    if (this==&other) return *this;
    ::cMessage::operator=(other);
    copy(other);
    return *this;
}

void LoginMsg::copy(const LoginMsg& other)
{
    this->ID_var = other.ID_var;
    this->x_var = other.x_var;
    this->y_var = other.y_var;
    this->serverID_var = other.serverID_var;
    delete [] this->aoi_var;
    this->aoi_var = (other.aoi_arraysize==0) ? NULL : new int[other.aoi_arraysize];
    aoi_arraysize = other.aoi_arraysize;
    for (unsigned int i=0; i<aoi_arraysize; i++)
        this->aoi_var[i] = other.aoi_var[i];
}

void LoginMsg::parsimPack(cCommBuffer *b)
{
    ::cMessage::parsimPack(b);
    doPacking(b,this->ID_var);
    doPacking(b,this->x_var);
    doPacking(b,this->y_var);
    doPacking(b,this->serverID_var);
    b->pack(aoi_arraysize);
    doPacking(b,this->aoi_var,aoi_arraysize);
}

void LoginMsg::parsimUnpack(cCommBuffer *b)
{
    ::cMessage::parsimUnpack(b);
    doUnpacking(b,this->ID_var);
    doUnpacking(b,this->x_var);
    doUnpacking(b,this->y_var);
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

int LoginMsg::getID() const
{
    return ID_var;
}

void LoginMsg::setID(int ID)
{
    this->ID_var = ID;
}

int LoginMsg::getX() const
{
    return x_var;
}

void LoginMsg::setX(int x)
{
    this->x_var = x;
}

int LoginMsg::getY() const
{
    return y_var;
}

void LoginMsg::setY(int y)
{
    this->y_var = y;
}

int LoginMsg::getServerID() const
{
    return serverID_var;
}

void LoginMsg::setServerID(int serverID)
{
    this->serverID_var = serverID;
}

void LoginMsg::setAoiArraySize(unsigned int size)
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

unsigned int LoginMsg::getAoiArraySize() const
{
    return aoi_arraysize;
}

int LoginMsg::getAoi(unsigned int k) const
{
    if (k>=aoi_arraysize) throw cRuntimeError("Array of size %d indexed by %d", aoi_arraysize, k);
    return aoi_var[k];
}

void LoginMsg::setAoi(unsigned int k, int aoi)
{
    if (k>=aoi_arraysize) throw cRuntimeError("Array of size %d indexed by %d", aoi_arraysize, k);
    this->aoi_var[k] = aoi;
}

class LoginMsgDescriptor : public cClassDescriptor
{
  public:
    LoginMsgDescriptor();
    virtual ~LoginMsgDescriptor();

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

Register_ClassDescriptor(LoginMsgDescriptor);

LoginMsgDescriptor::LoginMsgDescriptor() : cClassDescriptor("LoginMsg", "cMessage")
{
}

LoginMsgDescriptor::~LoginMsgDescriptor()
{
}

bool LoginMsgDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<LoginMsg *>(obj)!=NULL;
}

const char *LoginMsgDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int LoginMsgDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 5+basedesc->getFieldCount(object) : 5;
}

unsigned int LoginMsgDescriptor::getFieldTypeFlags(void *object, int field) const
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
        FD_ISEDITABLE,
        FD_ISARRAY | FD_ISEDITABLE,
    };
    return (field>=0 && field<5) ? fieldTypeFlags[field] : 0;
}

const char *LoginMsgDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "ID",
        "x",
        "y",
        "serverID",
        "aoi",
    };
    return (field>=0 && field<5) ? fieldNames[field] : NULL;
}

int LoginMsgDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='I' && strcmp(fieldName, "ID")==0) return base+0;
    if (fieldName[0]=='x' && strcmp(fieldName, "x")==0) return base+1;
    if (fieldName[0]=='y' && strcmp(fieldName, "y")==0) return base+2;
    if (fieldName[0]=='s' && strcmp(fieldName, "serverID")==0) return base+3;
    if (fieldName[0]=='a' && strcmp(fieldName, "aoi")==0) return base+4;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *LoginMsgDescriptor::getFieldTypeString(void *object, int field) const
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
        "int",
    };
    return (field>=0 && field<5) ? fieldTypeStrings[field] : NULL;
}

const char *LoginMsgDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int LoginMsgDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    LoginMsg *pp = (LoginMsg *)object; (void)pp;
    switch (field) {
        case 4: return pp->getAoiArraySize();
        default: return 0;
    }
}

std::string LoginMsgDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    LoginMsg *pp = (LoginMsg *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getID());
        case 1: return long2string(pp->getX());
        case 2: return long2string(pp->getY());
        case 3: return long2string(pp->getServerID());
        case 4: return long2string(pp->getAoi(i));
        default: return "";
    }
}

bool LoginMsgDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    LoginMsg *pp = (LoginMsg *)object; (void)pp;
    switch (field) {
        case 0: pp->setID(string2long(value)); return true;
        case 1: pp->setX(string2long(value)); return true;
        case 2: pp->setY(string2long(value)); return true;
        case 3: pp->setServerID(string2long(value)); return true;
        case 4: pp->setAoi(i,string2long(value)); return true;
        default: return false;
    }
}

const char *LoginMsgDescriptor::getFieldStructName(void *object, int field) const
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

void *LoginMsgDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    LoginMsg *pp = (LoginMsg *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}


