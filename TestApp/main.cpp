#include "mainwindow.h"
#include <QApplication>
#include <QtWidgets>
//#include <QWebEngineView>
//#include <QtWebEngine/QtWebEngine>
#include "digitalclock.h"
#include "social.h"
#include "image.h"
#include "news.h"

/**
   @brief the main class that incorporates and displays all components of the PiDash
   @author Meghan Hannon
   @return Qt application exec()
*/
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //QtWebEngine::initialize();
    MainWindow win;

    // initialize the clock to show currrent time
    DigitalClock clock(&win);
    clock.show();

    // Grid layout with 4 widgets for time, weather, news and social
    QGridLayout *gridLayout = new QGridLayout;
    QQuickWidget *qw2 = new QQuickWidget();
    QQuickWidget *socialWidget = new QQuickWidget();
    QQuickWidget *newsWidget = new QQuickWidget();
    QQuickWidget *imgWidget = new QQuickWidget();

    gridLayout->addWidget(&clock,0,0,1,1);
    gridLayout->addWidget(imgWidget,0,1,1,2);
    gridLayout->addWidget(socialWidget,1,0,2,3);
    gridLayout->addWidget(newsWidget,0,3,3,2);

    image *img = new image(imgWidget);
    news *newsfeed = new news(newsWidget);
    social *soc = new social(socialWidget);


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
