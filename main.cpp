#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include<QtQml>
#include "pomodoro.h"

int main(int argc, char *argv[])
{


    QApplication app(argc, argv);

    QQmlApplicationEngine engine;

    qmlRegisterType<Pomodoro>("net.flipback.qmlcomponents", 1, 0, "Pomodoro");
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));


    return app.exec();
}
