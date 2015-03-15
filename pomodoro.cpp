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
    state = IDLE;

    /* Initialilse the state machine */
    idle = new QState();
    focus = new QState();
    pause = new QState();

    idle->addTransition(this, SIGNAL(started()), focus);
    focus->addTransition(this, SIGNAL(started()), pause);
    focus->addTransition(this, SIGNAL(stopped()), idle);
    pause->addTransition(this, SIGNAL(stopped()), idle);

    idle->assignProperty(this, "state", IDLE);
    focus->assignProperty(this, "state", FOCUS);

    connect(focus, SIGNAL(exited()), this, SLOT(focusEnded()));
    connect(focus, SIGNAL(exited()), this, SLOT(focusStarted()));
    connect(pause, SIGNAL(exited()), this, SLOT(pauseEnded()));
    connect(pause, SIGNAL(exited()), this, SLOT(pauseStarted()));

    machine.addState(idle);
    machine.addState(focus);
    machine.addState(pause);
    machine.setInitialState(idle);

    machine.start();
    
    focusInterval = 25;
    pauseInterval = 5;
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

/* Accessors */
QString Pomodoro::getTime()
{
    div_t d_time = div(time, 60);
    QString sec = QString::number(d_time.rem);
    QString min = QString::number(d_time.quot);
    return min + ":" + sec;
}

Pomodoro::States Pomodoro::getState()
{
    return state;
}

void Pomodoro::setState(Pomodoro::States state)
{
    this->state = state;
}

QString Pomodoro::getStateName()
{
    QString stateName;

    switch (getState()){
    case IDLE:  stateName = "Idle";
        break;
    case FOCUS: stateName = "Focus";
        break;
    case PAUSE: stateName = "Pause";
        break;
    }

    return stateName;
}

int Pomodoro::getFocusInterval()
{
    return focusInterval;
}

void Pomodoro::setFocusInterval(int interval)
{
    focusInterval = interval;
}

int Pomodoro::getPauseInterval()
{
    return pauseInterval;
}

void Pomodoro::setPauseInterval(int interval)
{
    pauseInterval = interval;
}

/* Slots */
void Pomodoro::timerTick()
{
    /* Handle a tick of the timer */
    tick();
    if (time-- == 0) {
        timer->stop();
        //qDebug() << "Time is up.";
    }
}

void Pomodoro::focusStarted()
{
    //qDebug() << "Focus started.";
}

void Pomodoro::focusEnded()
{
    time = pauseInterval * PM_MINUTE;
    //qDebug() << "Focus ended.";
}

void Pomodoro::pauseStarted()
{
    //qDebug() << "Pause started.";
}

void Pomodoro::pauseEnded()
{
    time = focusInterval * PM_MINUTE;
    //qDebug() << "Pause ended.";
}
