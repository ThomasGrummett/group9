#include "mainwindow.h"
#include <QApplication>
#include "digitalclock.h"
#include <QGridLayout>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow win;

    DigitalClock clock(&win);
    clock.show();

    // Grid layout with 4 widgets for time, weather, news and social
    QGridLayout *gridLayout = new QGridLayout;
    QQuickWidget *qw2 = new QQuickWidget();
    QQuickWidget *qw3 = new QQuickWidget();
    QQuickWidget *qw4 = new QQuickWidget();

    gridLayout->addWidget(&clock,0,0,1,1);
    gridLayout->addWidget(qw2,0,1,1,2);
    gridLayout->addWidget(qw3,1,0,2,3);
    gridLayout->addWidget(qw4,0,3,3,2);

    // adjust styling
    gridLayout->setColumnMinimumWidth(0, (win.width()/4));
    gridLayout->setRowMinimumHeight(1, ((win.height()/2)));

    // Create a widget to contain everything
    QWidget *w = new QWidget();

    // Set the grid layout as a main layout
    w->setLayout(gridLayout);

    // set parent
    w->setParent(&win);
    // Display
    w->show();
    win.setCentralWidget(w);
    win.setWindowTitle("PiDash");
    win.show();


    return a.exec();
}
