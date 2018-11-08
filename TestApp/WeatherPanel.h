#ifndef WEATHERPANEL_H
#define WEATHERPANEL_H

#include <QLabel>
#include <QString>
#include <stdlib.h>
#include <unistd.h>
#include <curl/curl.h>
#include <curl/types.h>
#include <curl/easy.h>
#include "rapidjson"
#include <string>
#include <fstream>

class WeatherPanel: public QLabel
{
    private:
		/* weather[0] holds city name
		*weather[1] holds the weather group ie clouds
		*weather[2] holds the weather name ie broken clouds
		*weather[3] holds the temperature
		*weather[4] holds the humidity
		*/
		string weather[5];
		QString weatherToToDisplay();
		QString outputToLabel;
		void pullData();
	public:
		WeatherPanel(QWidget *parent = 0);
		string[] update();
		QLabel getWeather();
};

#endif
