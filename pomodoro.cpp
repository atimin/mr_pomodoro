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
#include "pomodoro.h"

Pomodoro::Pomodoro(QObject *parent) : QObject(parent)
{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerTick()));

    time = 25*60;
}

Pomodoro::~Pomodoro()
{
    timer->stop();
    delete(timer);
}

void Pomodoro::start()
{
    time = 25*60;
    timer->start(1000);
}

void Pomodoro::stop()
{
    timer->stop();
}


QString Pomodoro::getTime()
{
    div_t d_time = div(time, 60);
    QString sec = QString::number(d_time.rem);
    QString min = QString::number(d_time.quot);
    return min + ":" + sec;
}

void Pomodoro::timerTick()
{
    tick();
    if (time-- == 0) {
        stop();
    }
}
