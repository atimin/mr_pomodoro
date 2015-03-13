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

    idle = new QState();
    focus = new QState();
    pause = new QState();

    idle->addTransition(this, SIGNAL(started()), focus);
    focus->addTransition(this, SIGNAL(started()), pause);
    focus->addTransition(this, SIGNAL(stopped()), idle);
    pause->addTransition(this, SIGNAL(stopped()), idle);

    connect(focus, SIGNAL(exited()), this, SLOT(focusEnded()));
    connect(pause, SIGNAL(exited()), this, SLOT(pauseEnded()));

    machine.addState(idle);
    machine.addState(focus);
    machine.addState(pause);
    machine.setInitialState(idle);

    machine.start();
    
    time = 25*PM_MINUTE;
}

Pomodoro::~Pomodoro()
{
    timer->stop();
    delete(timer);
    delete(idle);
    delete(focus);
    delete(pause);
}

void Pomodoro::start()
{
    timer->start(1000);

    started();
}

void Pomodoro::stop()
{
    timer->stop();

    stopped();
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

void Pomodoro::focusEnded()
{
    time = 5*PM_MINUTE;
}

void Pomodoro::pauseEnded()
{
    time = 25*PM_MINUTE;
}
