/**
  @brief this class takes a QQuickWidget, adds a QLabel to it, then displays todays weather within that QLabel
  @author Thomas Grummett
 * powered by Open Weather Maps: openweathermaps.org
 */

#include "weatherpanel.h"
#include "picturename.h"

/**
 * @brief Constructor takes a QQuickWidget and adds the weather display to it
 * @param  parent QQuickWidget to display the weather in
 * @author Thomas Grummett
 */
weatherpanel::weatherpanel(QQuickWidget *parent)
    :QLabel(parent)
{
    QString style="background-color: #2884C2; color: white;";
   this->setStyleSheet(style);
    setGeometry(80,80,200,150);
    appID="a814b2b3fb9f749e9aa297b1f0300a84";
    // make sure we have an active network session
    this->nam = new QNetworkAccessManager(this);
    //set london as default
    city="London,CA";
    QNetworkConfigurationManager ncm;
    this->ns = new QNetworkSession(ncm.defaultConfiguration(), this);
    // tell the system we want network
    this->ns->open();
    //connect timer in order to pull the weather every 5 mins
    QTimer *timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &weatherpanel::pullWeather);
        timer->start(1000*60*5);
     pullWeather();
}
/**
 * @brief returns an integer representing the type of weather
 * @return weatherID integer that represents thet type of weather
 * @author Thomas Grummett
 */
int weatherpanel::getWeatherID(){
    return weatherID;
}
/**
 * @brief sets weatherID to an integer representing the type of weather
 * @param weatherID integer that represents thet type of weather
 * @author Thomas Grummett
 */
void weatherpanel::setWeatherID(int toSet){
    weatherID=toSet;
}

/**
 * @brief returns a QString describing the weather
 * @return QString weather that describes the weather
 * @author Thomas Grummett
 */
QString weatherpanel::getWeather(){
    return weather;
}
/**
 * @brief returns a QString describing the temperature
 * @return temperature QString that describes the temperature
 * @author Thomas Grummett
 */
QString weatherpanel::getTemp(){
    return temperature;
}
/**
 * @brief returns a QString holding the openweathermaps api key
 * @return appID QString that holds the api key
 * @author Thomas Grummett
 */
QString weatherpanel::getID(){
    return appID;
}
/**
 * @brief sets weather to a QString describing the weather
 * @param weatherIn QString that describes the weather
 * @author Thomas Grummett
 */
void weatherpanel::setWeather(QString weatherIn){
    weather=weatherIn;
}
/**
 * @brief sets temperature to a QString describing the temperature
 * @param temperature QString that describes the temperature
 * @author Thomas Grummett
 */
void weatherpanel::setTemp(QString tempIn){
    temperature=tempIn;
}
/**
 * @brief connects to openweathermaps api and queries for the weather data in JSON format, calls dataToVars to save this info
 *
 * @author Thomas Grummett
 */
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
/**
 * @brief converts kelvin to celcius and then returns as string
 * @param temp double is the temperature as a double
 * @return QString holding the converted temperature
 *@author Thomas Grummett
*/
QString weatherpanel::KtoC(double temp){
    return QString::number(qRound(temp-273.15)) + QChar(0xB0);
}
/**
 * @brief converts the data to a string then sets the QLabels text to this string
 * @author Thomas Grummett
*/
void weatherpanel::updateText(){
    QString toSet=city+"\nWeather:\n"+weatherpanel::getWeather()+"\nTemperature:\n"+weatherpanel::getTemp();
    setText(toSet);
}
/**
 * @brief converts the raw data to useful variables
 * @param netreply  QNetworkReply the data pulled for a query to openweathermaps api
 * @author Thomas Grummett
 */
void weatherpanel::dataToVars(QNetworkReply *netreply){
    if(netreply!=NULL){
        QJsonDocument doc= QJsonDocument::fromJson(netreply->readAll());
        if(doc.isObject()){
            QJsonObject jsobj=doc.object();
            QJsonObject tempObject;
            QJsonValue jsval;
            ///pull weather data
            if (jsobj.contains(QStringLiteral("weather"))) {
                jsval = jsobj.value(QStringLiteral("weather"));
                QJsonArray weatherArray = jsval.toArray();
                jsval = weatherArray.at(0);
                tempObject = jsval.toObject();
                setWeather(tempObject.value(QStringLiteral("description")).toString());
                setWeatherID(tempObject.value(QStringLiteral("id")).toInt());
             }
            //pull temperature
            if (jsobj.contains(QStringLiteral("main"))) {
                jsval = jsobj.value(QStringLiteral("main"));
                tempObject = jsval.toObject();
                jsval = tempObject.value(QStringLiteral("temp"));
                setTemp(KtoC(jsval.toDouble()));
             }
        }
        //update QLabel
        updateImage();
        updateText();
    }
    netreply->deleteLater();
}
/**
 * @brief Determines a background picture based on weatherID, sets the picture to the background
 * @author Thomas Grummett
 */
void weatherpanel::updateImage(){
    //thunderstorm
    if(getWeatherID()>=200 && getWeatherID()<300){
        wToImage="thunderstorm";
    }
    //rain
    else if(getWeatherID()>=300 && getWeatherID()<600){
        wToImage="rain";
    }
    //snow not 602,622-->blizzard
    else if(getWeatherID()>=600 && getWeatherID()<700 &&getWeatherID()!=602 &&getWeatherID()!=622){
        wToImage="snow";
    }
    //blizzard
    else if(getWeatherID()==602 || getWeatherID()==622){
        wToImage="blizzard";
    }
    //fog
    else if(getWeatherID()>=700 && getWeatherID()<=770){
        wToImage="fog";
    }
    //tornado
    else if(getWeatherID()>=770 && getWeatherID()<800){
        wToImage="tornado";
    }
    //clear
    else if(getWeatherID()==800){
        wToImage="sunny";
    }
    //clouds
    else if(getWeatherID()>800){
        wToImage="cloudy";
    }
    //default to aurora
    else{
        wToImage="aurora";
    }
    //set to background
    picturename::instance();
    picturename::instance().set_picture(wToImage);
}
