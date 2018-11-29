/**
 @brief This class takes a given parent QQuickWidget and displays a social media blog in it
 @author Stacey Gunderson, Alison Lee
 */

#ifndef SOCIAL_H
#define SOCIAL_H
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
 @brief The social class inherits from QObject to get access to signals and slots for updating
 @author Stacey Gunderson, Alison Lee
 */
class social: public QObject
{
    Q_OBJECT
    //Creates a social media browser in the widget given
private:
    QWebEngineView *wv; //The widget to use to display social media
    QPushButton *reloadbutton; //The button that takes refresh clicks
    const QString style = "background-color: #A3C1DA; color: white;";
    QLineEdit *urlbox;
    QString url;

public:
        social(QQuickWidget*parent = nullptr);

public slots:
    void on_reload();

signals:
    void reload();
};

#endif // SOCIAL_H
