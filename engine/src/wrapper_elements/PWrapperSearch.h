#ifndef PWRAPPERSEARCH_H
#define PWRAPPERSEARCH_H

#include "PWrapperElement.h"
#include "PSchemaElement.h"
#include <QString>

class PWrapperSearchPrivate;
class PWrapper;

class PWrapperSearch : public PWrapperElement
{
public:
    PWrapperSearch(PWrapper *wrapper, PWrapperElement *parent, PSchemaElement elementSchema);
    PWrapperSearch(PWrapper *wrapper, PWrapperElement &parent, const QString &elementName);
    ~PWrapperSearch();

private:
    friend class PWrapperSearchPrivate;
    PWrapperSearchPrivate *d;
};

#endif // PWRAPPERSEARCH_H
