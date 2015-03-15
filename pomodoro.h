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
//#include <QDebug>

#ifdef QT_DEBUG
#define PM_MINUTE 1
#else
#define PM_MINUTE 60
#endif



class Pomodoro : public QObject
{
    Q_OBJECT    
    Q_ENUMS(States)

public:
    explicit Pomodoro(QObject *parent = 0);
    ~Pomodoro();

    enum States {IDLE, FOCUS, PAUSE};

    Q_INVOKABLE void start();   // Start time of focus \ pause
    Q_INVOKABLE void stop();    // Stop the timer

    QString getTime();          // Get the rest time of the current state
    Pomodoro::States getState();          // Get current state
    void setState(Pomodoro::States state);// Set state
    QString getStateName();

    /* Get\set intervals in minutes */
    int getFocusInterval();
    void setFocusInterval(int interval);

    int getPauseInterval();
    void setPauseInterval(int interval);

private:
    int time;                   // Time in seconds
    QTimer *timer;
    int focusInterval;
    int pauseInterval;

    Q_PROPERTY(QString time READ getTime)                   // The rest of time for current state in second
    Q_PROPERTY(States state READ getState WRITE setState)   // States of the timer
    Q_PROPERTY(QString stateName READ getStateName)         // Current state's name
    QStateMachine machine;
    QState *idle;               // Timer does nothing
    QState *focus;              // Focus's time
    QState *pause;              // Pause's time
    Pomodoro::States state;     // The current state



protected:

signals:
    void tick();
    void started();
    void stopped();

private slots:
    void timerTick();
    void focusStarted();
    void focusEnded();
    void pauseStarted();
    void pauseEnded();
};

#endif // TIMER_H
