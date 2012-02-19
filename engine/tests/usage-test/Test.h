#ifndef TEST_H
#define TEST_H

#include <QtTest/QtTest>

class PEngine;
class PSiteWrapper;
class PPageWrapper;

class Test : public QObject
{
    Q_OBJECT
public:
    explicit Test(QObject *parent = 0);

private slots:
    void testScriptEngine();
    void testEngine();

private: /* Members */
    PEngine *engine;
    PSiteWrapper *siteWrapper;
    PPageWrapper *pageWrapper;
};

#endif // TEST_H
