#ifndef DIGITALCLOCK_H
#define DIGITALCLOCK_H

#include <QLCDNumber>

/**
   @brief Digital Clock class displays the current time
   @author Meghan hannon
*/
class DigitalClock : public QLCDNumber
{
    Q_OBJECT

public:
    DigitalClock(QWidget *parent = 0);

private slots:
    void showTime();
};

#endif
