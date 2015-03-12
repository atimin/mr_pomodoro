#ifndef TIMER_H
#define TIMER_H

#include <QObject>
#include <QTimer>
#include <QString>

class Pomodoro : public QObject
{
    Q_OBJECT
    int time;
    QTimer *timer;

    Q_PROPERTY(QString time READ getTime)
public:
    explicit Pomodoro(QObject *parent = 0);
    ~Pomodoro();

    Q_INVOKABLE void start();
    Q_INVOKABLE void stop();

    QString getTime();
protected:

signals:
    void tick();

public slots:
    void timerTick();

};

#endif // TIMER_H
