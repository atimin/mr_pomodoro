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
#ifndef TIMER_H
#define TIMER_H

#include <QObject>
#include <QTimer>
#include <QString>
#include <QState>
#include <QStateMachine>

#ifdef QT_DEBUG
#define PM_MINUTE 1
#else
#define PM_MINUTE 60
#endif

class Pomodoro : public QObject
{
    Q_OBJECT
    int time;       // Time in seconds
    QTimer *timer;


    Q_PROPERTY(QString time READ getTime)
    Q_PROPERTY(QString state READ getState)  /* States of the timer */
    QStateMachine machine;
    QState *idle;               // Timer does nothing
    QState *focus;              // Focus's time
    QState *pause;              // Pause's time
    QString state;              // Name of the current state

public:
    explicit Pomodoro(QObject *parent = 0);
    ~Pomodoro();

    Q_INVOKABLE void start();   // Start time of focus \ pause
    Q_INVOKABLE void stop();    // Stop the timer

    QString getTime();
    QString getState();
protected:

signals:
    void tick();
    void started();
    void stopped();

private slots:
    void timerTick();
    void focusEnded();
    void pauseEnded();

};

#endif // TIMER_H
