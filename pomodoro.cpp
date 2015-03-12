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
