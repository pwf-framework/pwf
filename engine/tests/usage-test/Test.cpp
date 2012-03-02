#include "Test.h"
#include <QScriptEngine>
#include <PEngine.h>
#include <PSiteWrapper.h>
#include <PPageWrapper.h>
#include <QtNetwork/QNetworkAccessManager>
#include <schema/PSchemaElement.h>

QTEST_MAIN(Test)

Test::Test(QObject *parent) :
    QObject(parent)
{
    engine = new PEngine();

    siteWrapper = new PSiteWrapper(engine);
}

/** Execute javascript test */
void Test::testScriptEngine()
{
    QScriptEngine scriptEng;
    // sum
    qDebug(QByteArray("\ntesting sum"));
    scriptEng.globalObject().setProperty("value", 2);
    QScriptValue evaluated = scriptEng.evaluate("value + 2");
    QCOMPARE(evaluated.toString(), QString("4"));
    // concatenation
    qDebug(QByteArray("\ntesting concatenation"));
    scriptEng.globalObject().setProperty("value", "2");
    evaluated = scriptEng.evaluate("value + 2");
    QCOMPARE(evaluated.toString(), QString("22"));
}

void Test::testEngine()
{
    QVERIFY(engine->network() != NULL);
    QVERIFY(engine->scriptEngine() != NULL);
    QVERIFY(engine->schemaCandidatesDirectory().isEmpty());

    qDebug(QByteArray("\ntesting schema candidates directory"));
    // the last "/" should have been removed
    engine->setSchemaCandidatesDirectory("schema/some/");
    QCOMPARE(engine->schemaCandidatesDirectory(), QString("schema/some")); // must remove the trailing /
    // exception: the "/" should not have been removed if it's only character (means root)
    engine->setSchemaCandidatesDirectory("/");
    QCOMPARE(engine->schemaCandidatesDirectory(), QString("/"));
    // multiple "/" in the string should have been removed
    engine->setSchemaCandidatesDirectory("some///foo////bar///");
    QCOMPARE(engine->schemaCandidatesDirectory(), QString("some/foo/bar"));
    // allow windows root
    engine->setSchemaCandidatesDirectory("c://test//");
    QCOMPARE(engine->schemaCandidatesDirectory(), QString("c:/test"));
}

void Test::testWrapper()
{
    QVERIFY(siteWrapper->engine() != NULL);

    bool result;

    // name should be empty if not setted
    QCOMPARE(siteWrapper->name(), QString(""));

    // should allow valid characters in the name.
    result = siteWrapper->setName("myWrapper");
    QCOMPARE(result, true);
    QCOMPARE(siteWrapper->name(), QString("myWrapper"));
    result = siteWrapper->setName("09239");
    QCOMPARE(result, true);
    result = siteWrapper->setName("232ad23");
    QCOMPARE(result, true);

    // test: don't allow for illegal characters in the name
    qDebug("\ntesting illegal characters in the name: '../../../../'");
    result = siteWrapper->setName("?<>:\\/\"|?*");
    QCOMPARE(result, false);
    result = siteWrapper->setName("../../../../");
    QCOMPARE(result, false);
    // don't allow a name with spaces
    result = siteWrapper->setName(" ");
    QCOMPARE(result, false);
    // no empty name
    result = siteWrapper->setName("");
    QCOMPARE(result, false);

    // invalid urls should not be accepted (note: this is a sitewrapper, so only http://www.sitename.com/ urls will
    // be accepted)
    result = siteWrapper->setUrl("invalidurl");
    QCOMPARE(result, false);

    // schema candidates directory
}

void Test::testSiteWrapper()
{
    // the site wrapper is a top level wrapper => it has no parent
    QVERIFY(siteWrapper->parentWrapper() == NULL);
}

void Test::testSchemaElement()
{
    // a null schema element should have an empty type
    PSchemaElement schemaElement;
    QCOMPARE(schemaElement.type(), QString());

    // test operator "="

    // test explicitly shared memory
}
