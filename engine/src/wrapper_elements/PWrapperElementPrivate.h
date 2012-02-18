#ifndef PWRAPPERELEMENTPRIVATE_H
#define PWRAPPERELEMENTPRIVATE_H

#include "PSchemaElement.h"
#include <QHash>

class PWrapperElement;
class PWrapper;
class PFindSchemaElement;

class PWrapperElementPrivate
{
public:
    PWrapperElementPrivate(PWrapperElement *_q);

public: /* Members */
    PWrapper *m_wrapper;
    PWrapperElement *m_parentElement;
    PSchemaElement m_schema;
    PFindSchemaElement *m_schemaFinder;

public:
    PWrapperElement *q;
};

#endif // PWRAPPERELEMENTPRIVATE_H
