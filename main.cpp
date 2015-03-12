/* Mr. Pomodoro - a little timer to work more effectively.
 * Copyright (C) 2015 Timin Aleksey
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */
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
