#include "weatherpanel.h"

/*
 * powered by openweathermaps.org
 * */
weatherpanel::weatherpanel(QWidget *parent)
    :QLabel(parent)
{
    appID="a814b2b3fb9f749e9aa297b1f0300a84";
    //set timer for event loop then
    // make sure we have an active network session
    this->nam = new QNetworkAccessManager(this);
    //set london as default
    city="London,CA";
    QNetworkConfigurationManager ncm;
    this->ns = new QNetworkSession(ncm.defaultConfiguration(), this);
    // tell the system we want network
    this->ns->open();
    QTimer *timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &weatherpanel::pullWeather);
        timer->start(1000*60*5);
     pullWeather();
}
//Weather getter
QString weatherpanel::getWeather(){
    return weather;
}
//Temp getter
QString weatherpanel::getTemp(){
    return temperature;
}
//AppID Getter
QString weatherpanel::getID(){
    return appID;
}
//weather setter
void weatherpanel::setWeather(QString weatherIn){
    weather=weatherIn;
}
//temperature setter
void weatherpanel::setTemp(QString tempIn){
    temperature=tempIn;
}
//pulls weather data from openweathermap
void weatherpanel::pullWeather(){
    QUrl url("http://api.openweathermap.org/data/2.5/weather");
    QUrlQuery query;

     //add query items
    query.addQueryItem("q", city);
    query.addQueryItem("mode", "json");
    query.addQueryItem("APPID", getID());
    url.setQuery(query);

     QNetworkReply *netreply = nam->get(QNetworkRequest(url));
     // connect up the signal right away
     connect(netreply, &QNetworkReply::finished,
                this, [this, netreply]() { dataToVars(netreply); });
}
//converts kelvin to celcius
QString weatherpanel::KtoC(double temp){
    return QString::number(qRound(temp-273.15)) + QChar(0xB0);
}
//updates the display text
void weatherpanel::updateText(){
    QString toSet=city+"\nWeather:\n"+weatherpanel::getWeather()+"\nTemperature:\n"+weatherpanel::getTemp();
    setText(toSet);
}
//converts query data to useful variables
void weatherpanel::dataToVars(QNetworkReply *netreply){
    if(netreply!=NULL){
        QJsonDocument doc= QJsonDocument::fromJson(netreply->readAll());
        if(doc.isObject()){
            QJsonObject jsobj=doc.object();
            QJsonObject tempObject;
            QJsonValue jsval;

            if (jsobj.contains(QStringLiteral("weather"))) {
                jsval = jsobj.value(QStringLiteral("weather"));
                QJsonArray weatherArray = jsval.toArray();
                jsval = weatherArray.at(0);
                tempObject = jsval.toObject();
                setWeather(tempObject.value(QStringLiteral("description")).toString());
             }
            if (jsobj.contains(QStringLiteral("main"))) {
                jsval = jsobj.value(QStringLiteral("main"));
                tempObject = jsval.toObject();
                jsval = tempObject.value(QStringLiteral("temp"));
                setTemp(KtoC(jsval.toDouble()));
             }
        }
        updateText();
    }
    netreply->deleteLater();
}
