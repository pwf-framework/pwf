#ifndef PWRAPPERDATA_H
#define PWRAPPERDATA_H

#include "pwfengine_global.h"
#include "PWrapperElement.h"
#include <QString>
#include "PSchemaElement.h"
#include "PWrapperSearch.h"

class PWrapperDataPrivate;
class PWrapper;

class PWFENGINESHARED_EXPORT PWrapperData : public PWrapperElement
{
public: enum DataType {
    IntType, FloatType, StringType
};

public:
    PWrapperData(PWrapper *wrapper, PWrapperElement *parent, PSchemaElement elementSchema);
    PWrapperData(PWrapper *wrapper, PWrapperElement &parent, const QString &elementName);
    ~PWrapperData();

    /** @return the data value type, e.g. IntType */
    PWrapperData::DataType dataType() const;
    /** The search to perform in order to get the data value, it's optional. */
    PWrapperSearch search();

private:
    friend class PWrapperDataPrivate;
    PWrapperDataPrivate *d;
};

#endif // PWRAPPERDATA_H
