/**
  @brief This class takes a given parent QQuickWidget and displays a news feed
  @bug May throw warnings and errors to console about missing sync tokens, will not crash
  Everything works nicely on the front end
  @author Stacey Gunderson, Alison Lee
  **/

#include "news.h"

/**
  @brief Upon button click signal, reloads the url to refresh what is on the page
  @author Stacey Gunderson, Alison Lee
  @return void
 **/
void news::on_reload()
{
    //Sets and loads the url up again
    url = "http://lite.cnn.io/en";
    wv->setUrl((QUrl)url);
}

/**
  @brief Constructor that takes the given parent widget and displays a news media blog inside it, can be updated on button click
  @author Stacey Gunderson, Alison Lee
  @param QQuickWidget parent widget to display the news media blog in
 **/
news::news(QQuickWidget *parent)
{
    //Creates a webview widget in the given parent QQuickWidget
    wv = new QWebEngineView(parent);

    //Sets fixed height and width to fit the (fixed) window given
    wv->setFixedWidth(397);
    wv->setFixedHeight(667);

    //News site to be loaded into the webview
     wv->load((QUrl)"http://lite.cnn.io/en");

    //Creates a QPushButton to handle click inputs for when to refresh the page
    reloadbutton = new QPushButton(parent);
    reloadbutton->setStyleSheet(style); //Sets stylesheet to avoid white text on white background for some OS
    reloadbutton->setText("Refresh news");
    reloadbutton->setGeometry(220,-1,140,32); //Positions the overlay to the right to block less text
    QObject::connect(reloadbutton, SIGNAL(clicked()), this, SLOT(on_reload()));

    wv->show();
}


