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

private Q_SLOTS:
    void testidle();
};

UPomodoro::UPomodoro()
{
    pom = new Pomodoro(this);
}

//

void UPomodoro::testidle()
{
    QCOMPARE(pom->getState(), QString("Idle"));
}

QTEST_MAIN(UPomodoro)

#include "tst_upomodoro.moc"
