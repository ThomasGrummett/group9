/**
 @brief This class takes a given parent QQuickWidget and displays a news media blog in it
 @author Stacey Gunderson, Alison Lee
 */

#ifndef news_H
#define news_H
#include <QtWidgets>
#include <QtNetwork>
#include <QUrl>
#include <QWebEngineView>
#include <QWebEnginePage>
#include <QNetworkInterface>
#include <QQuickWidget>
#include <QObject>
#include <QApplication>
#include <QLineEdit>


/**
 @brief The news class inherits from QObject to get access to signals and slots for updating
 @author Stacey Gunderson, Alison Lee
 */
class news: public QObject
{
    Q_OBJECT
    //Creates a news media browser in the widget given
private:
    QWebEngineView *wv; //The widget to use to display news media
    QPushButton *reloadbutton; //The button that takes refresh clicks
    const QString style = "background-color: #A3C1DA; color: white;";
    QString url;

public:
        news(QQuickWidget*parent = nullptr);

public slots:
    void on_reload();

signals:
    void reload();
};

#endif // news_H
