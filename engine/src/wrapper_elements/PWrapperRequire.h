#ifndef PWRAPPERREQUIRE_H
#define PWRAPPERREQUIRE_H

#include "PWrapperElement.h"
#include "PSchemaElement.h"
#include <QString>

class PWrapperRequirePrivate;
class PWrapper;

class PWrapperRequire : public PWrapperElement
{
public:
    PWrapperRequire(PWrapper *wrapper, PWrapperElement *parent, PSchemaElement elementSchema);
    PWrapperRequire(PWrapper *wrapper, PWrapperElement &parent, const QString &elementName);
    ~PWrapperRequire();

private:
    friend class PWrapperRequirePrivate;
    PWrapperRequirePrivate *d;
};

#endif // PWRAPPERREQUIRE_H
