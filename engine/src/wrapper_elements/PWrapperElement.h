#ifndef PWRAPPERELEMENT_H
#define PWRAPPERELEMENT_H

/**
    \class PWrapperElement
    \brief An element of a wrapper. The element is indentified by its schema.

    The element schema can be setted directly or automatically detected by specifying the element name and type.
*/

#include <QObject>
#include <QString>
#include "PSchemaElement.h"

class PWrapperElementPrivate;
class PWrapper;
class PFindSchemaElement;
class PWrapperRequire;

class PWrapperElement : public QObject
{

public:
    /** @note a NULL parent means that this is the root element of a top level wrapper. */
    PWrapperElement(PWrapper *wrapper, PWrapperElement *parent, PSchemaElement elementSchema = PSchemaElement());
    /** Create a wrapper element without fully specifying its schema, this will be detected by having its name and
        type by creating a PFindSchemaElement that will starts its search from parent and that
        can be accessed with schemaFinder().

        @param elementType the element type, e.g data, search, etc.
        @param elementName the name of the element, e.g: foo */
    PWrapperElement(PWrapper *wrapper, PWrapperElement &parent, const QString &elementType, const QString &elementName);
    ~PWrapperElement();

    void setWrapper(PWrapper *wrapper);
    PWrapper *wrapper() const;
    void setParentElement(PWrapperElement *parentElement);
    PWrapperElement *parentElement() const;
    PSchemaElement schema() const;
    /** @return the element name. */
    QString name() const;
    /** @return the finder that is detecting the element schema or NULL if there is nothing to detect. */
    PFindSchemaElement *schemaFinder() const;

    /** @return the child wrapper element with the specified schema, creating it first if not exists.
        @return NULL if the specified schema is null. */
    PWrapperElement *childElement(const PSchemaElement &elementSchema);
    /** @return the child require with the specified schema, creating it first if not exists.
        @return NULL if the specified schema is null. */
    PWrapperRequire *childRequire(const PSchemaElement &requireSchema);

public:
    void setSchema(const PSchemaElement &elementSchema);

protected:
    /** @return the element type, e.g. data */
    QString type() const;

private:
    friend class PWrapperElementPrivate;
    PWrapperElementPrivate *d;
};

#endif // PWRAPPERELEMENT_H
