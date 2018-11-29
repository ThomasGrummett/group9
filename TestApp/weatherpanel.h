#ifndef WEATHERPANEL_H
#define WEATHERPANEL_H

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtNetwork/QNetworkReply>
#include <QtQml/QQmlListProperty>


#include <QWidget>
#include <qnetworkconfigmanager.h>
#include <qnetworksession.h>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QStringList>
#include <QTimer>
#include <QUrlQuery>
#include <QElapsedTimer>
#include <QLoggingCategory>
#include <QApplication>
#include <QtWidgets>
/**
  @brief this class takes a QQuickWidget, adds a QLabel to it, then displays todays weather within that QLabel
  @author Thomas Grummett
 * powered by Open Weather Maps: openweathermaps.org
 */
class QQuickWidget;
class weatherpanel: public QLabel
{
public:
		 /**
     * @brief Constructor takes a QQuickWidget and adds the weather display to it
		 * @param  parent QQuickWidget to display the weather in
		 * @author Thomas Grummett
		 */
       weatherpanel(QQuickWidget *parent=0);
		/**
		 * @brief returns an integer representing the type of weather
		 * @return weatherID integer that represents thet type of weather
		 * @author Thomas Grummett
		 */
       int getWeatherID();
       /**
		 * @brief sets weatherID to an integer representing the type of weather
		 * @param weatherID integer that represents thet type of weather
		 * @author Thomas Grummett
		 */
       void setWeatherID(int toSet);
       QString wToImage;
       int weatherID;
      
       /**
		 * @brief returns a QString holding the openweathermaps api key
		 * @return appID QString that holds the api key
		 * @author Thomas Grummett
		 */
       QString getID();
       /**
 		* @brief sets weather to a QString describing the weather
 		* @param weatherIn QString that describes the weather
		 * @author Thomas Grummett
		 */
       void setWeather(QString weatherIn);
       /**
 		* @brief sets temperature to a QString describing the temperature
		 * @param temperature QString that describes the temperature
		 * @author Thomas Grummett
		 */
       void setTemp(QString tempIn);
       QString city;
       QNetworkAccessManager *nam;
       QNetworkSession *ns;
       /**
 		* @brief returns a QString describing the weather
		 * @return QString weather that describes the weather
 		* @author Thomas Grummett
		 */
       QString getWeather();
       /**
		 * @brief returns a QString describing the temperature
		 * @return temperature QString that describes the temperature
		 * @author Thomas Grummett
		 */
       QString getTemp();
       QString appID;
       /**
		 * @brief converts the data to a string then sets the QLabels text to this string
 		* @author Thomas Grummett
		*/
       void updateText();
private slots:
		/**
		 * @brief connects to openweathermaps api and queries for the weather data in JSON format, calls dataToVars to save this info
		 *
 		* @author Thomas Grummett
		 */
       void pullWeather();
private:
	/**
 	* @brief Determines a background picture based on weatherID, sets the picture to the background
 	* @author Thomas Grummett
 	*/
       void updateImage();
       QString weather;
       QString temperature;
       /**
 	* @brief converts the raw data to useful variables
 	* @param netreply  QNetworkReply the data pulled for a query to openweathermaps api
 	* @author Thomas Grummett
	 */
       void dataToVars(QNetworkReply *netreply);
       /**
 * @brief converts kelvin to celcius and then returns as string
 * @param temp double is the temperature as a double
	 * @return QString holding the converted temperature
 	*@author Thomas Grummett
	*/
       QString KtoC(double temp);

};

#endif // WEATHERPANEL_H
