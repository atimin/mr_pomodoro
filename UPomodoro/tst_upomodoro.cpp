#include <QString>
#include <QtTest>
#include <QCoreApplication>
#include "../pomodoro.h"

class UPomodoro : public QObject
{
    Q_OBJECT

    Pomodoro *pom;

public:
    UPomodoro();

private:
    void checkIdle(Pomodoro *pom);
private Q_SLOTS:
    /* Test IDLE state */
    void testidle();
    void testIdleAfterFocus();
    void testIdleAfterPause();

    /* Test FOCUS state */
    void testFocus();
};

/* Test IDLE state */
UPomodoro::UPomodoro()
{
    pom = new Pomodoro(this);
}


void UPomodoro::testidle()
{
    checkIdle(pom);
}

void UPomodoro::testIdleAfterFocus()
{
    pom->setFocusInterval(0);
    pom->start();

    QTest::qSleep(1000);

    checkIdle(pom);
}

void UPomodoro::testIdleAfterPause()
{
    pom->setFocusInterval(0);
    pom->setPauseInterval(0);
    pom->start();

    QTest::qSleep(1000);

    checkIdle(pom);
}

/* Test FOCUS state */
void UPomodoro::testFocus()
{
    pom->setFocusInterval(1);
    checkIdle(pom);
    pom->start();

    QCOMPARE(pom->getState(), Pomodoro::FOCUS);
}

/* Helpers */
void UPomodoro::checkIdle(Pomodoro *pom)
{
    QCOMPARE(pom->getState(), Pomodoro::IDLE);
}

QTEST_MAIN(UPomodoro)

#include "tst_upomodoro.moc"
