/**
  @brief This class takes a given parent QQuickWidget and displays a social media blog in it
  @bug Will throw warnings and errors to console about missing sync tokens??
  Everything works nicely on the front end
  @author Stacey Gunderson, Alison Lee
  **/

#include "social.h"

/**
  @brief Upon button click signal, reloads the url to refresh what is on the page
  @author Stacey Gunderson, Alison Lee
  @return void
 **/
void social::on_reload()
{
    //Sets and loads the url up again
    url = "https://" + urlbox->text() + ".tumblr.com/mobile";
    wv->setUrl((QUrl)url);
}

/**
  @brief Constructor that takes the given parent widget and displays a social media blog inside it, can be updated on button click
  @author Stacey Gunderson, Alison Lee
  @param QQuickWidget parent widget to display the social media blog in
 **/
social::social(QQuickWidget *parent)
{
    //Creates a webview widget in the given parent QQuickWidget
    wv = new QWebEngineView(parent);

    //Sets fixed height and width to fit the (fixed) window given
    wv->setFixedWidth(680);
    wv->setFixedHeight(370);

    //Tumblr blog url to be loaded into the webview
     wv->load((QUrl)"http://330hno.tumblr.com/mobile");

    //Creates a QPushButton to handle click inputs for when to refresh the page
    reloadbutton = new QPushButton(parent);
    reloadbutton->setStyleSheet(style); //Sets stylesheet to avoid white text on white background for some OS
    reloadbutton->setText("Load blog");
    reloadbutton->setGeometry(494,-1,165,32); //Positions the overlay to the right to block less text
    QObject::connect(reloadbutton, SIGNAL(clicked()), this, SLOT(on_reload()));

    urlbox = new QLineEdit("330hno", parent);
    urlbox->setGeometry(494,30,165,31);
    urlbox->setStyleSheet(style);

    wv->show();
}


