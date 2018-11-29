#include <QtWidgets>

#include "digitalclock.h"

/**
   @brief Digital Clock class initializer; connects timer to digital clock to always show updated time
   @param parent the parent widget of the digital clock
   @return void
*/
DigitalClock::DigitalClock(QWidget *parent)
    : QLCDNumber(parent)
{
    setSegmentStyle(Filled);

    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &DigitalClock::showTime);
    timer->start(1000);

    showTime();

    setWindowTitle(tr("Digital Clock"));
    resize(150, 60);
}

/**
   @brief gets the current time and displays in HH:MM format
   @return void
*/
void DigitalClock::showTime()
{
    QTime time = QTime::currentTime();
    QString text = time.toString("hh:mm");
    if ((time.second() % 2) == 0)
        text[2] = ' ';
    display(text);
}

