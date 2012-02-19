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
    siteWrapper = new PSiteWrapper(engine);
    siteWrapper->setUrl("http://www.google.it/");
}

/** Execute javascript test */
void Test::testScriptEngine()
{
    QScriptEngine scriptEng;
    scriptEng.globalObject().setProperty("value", 2);
    QScriptValue evaluated = scriptEng.evaluate("value + 2");
    qDebug(evaluated.toString().toUtf8()); // should output 4
    scriptEng.globalObject().setProperty("value", "2");
    evaluated = scriptEng.evaluate("value + 2");
    qDebug(evaluated.toString().toUtf8()); // should output 22 (string concatenation)
}

void Test::testEngine()
{
    engine = new PEngine();
    QVERIFY(engine->network() != NULL);
    QVERIFY(engine->scriptEngine() != NULL);
    QVERIFY(engine->schemaCandidatesDirectory().isEmpty());

    // the last "/" should have been removed
    engine->setSchemaCandidatesDirectory("schema/some/");
    QVERIFY(engine->schemaCandidatesDirectory() == "schema/some"); // must remove the trailing /
    // exception: the "/" should not have been removed if it's only character (means root)
    engine->setSchemaCandidatesDirectory("/");
    QCOMPARE(engine->schemaCandidatesDirectory(), QString("/"));
    //***************** BUG: multiple "/" in the string should have been removed ***********************/
    engine->setSchemaCandidatesDirectory("some///foo////bar///");
    QCOMPARE(engine->schemaCandidatesDirectory(), QString("some/foo/bar"));


}
