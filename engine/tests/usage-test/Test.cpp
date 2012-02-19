#include "Test.h"
#include <QScriptEngine>
#include <PEngine.h>
#include <PSiteWrapper.h>
#include <PPageWrapper.h>
#include <QtNetwork/QNetworkAccessManager>

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

    // test: don't allow for illegal characters in the name
    qDebug("\ntesting illegal characters in the name: '../../../../'");
    result = siteWrapper->setName("?<>:\\/\"|?*");
    QCOMPARE(result, false);
    result = siteWrapper->setName("../../../../");
    QCOMPARE(result, false);
    // don't allow a name with spaces
    result = siteWrapper->setName(" ");
    QCOMPARE(result, false);
}

void Test::testSiteWrapper()
{
    // the site wrapper is a top level wrapper => it has no parent
    QVERIFY(siteWrapper->parentWrapper() == NULL);
}
