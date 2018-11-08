#include "WeatherPanel.h"


/*
To do:
check if internet connection
set icon, make prettier, etc
ability to change location
update after x time, or maybe on click, change to buttonÉ
*/
WeatherPanel::WeatherPanel(QWidget *parent)
	:QLabel(parent)
	{
	getWeather();
}
/*
	Input:none
	Function: runs through required functions to produce QString, sets this as text
	Output: none
*/
void WeatherPanel::getWeather(){
	weather=update();
	outputToLabel=weatherToToDisplay(weather);	
	setText(outputToLabel);
}
QString WeatherPanel::weatherToToDisplay(string weather[]){
	/* converts weather array into a Qstring of the format
	Weather:
	[weather type]
	Temperature:
	[temp in celcius] Celcius
	Humidity:
	[humidity] percent
	*/
	QString toReturn=("City:\n%s\nWeather:\n%s\nTemperature:\n%s Celcius\nHumidity:\n%s percent",weather[0],weather[2],weather[3],weather[4]);
	return toReturn;
}
/*
Input: None
Output: A string array holding information on the weather
Function: Pulls data from JSON file, parses for relevant information
*/
string[] WeatherPanel::update(){
	//string array to be returned
	//VVVV replace weather with toReturn in this case
	/* weather[0] holds city name
		*weather[1] holds the weather group ie clouds
		*weather[2] holds the weather name ie broken clouds
		*weather[3] holds the temperature
		*weather[4] holds the humidity
		*/
	string toReturn[5];
	//pulls weather data to file
	pullData();
	
	//loads all data onto input file stream
	std::ifstream ifs("weatherfile.txt");
	std::string readWeather( (std::istreambuf_iterator<char>(ifs) ),
                       (std::istreambuf_iterator<char>()    ) );
				
	//parsedWeather is the parsed weather file
	Document parsedWeather;
	parsedWeather.Parse(readWeather);
	
	//sets weather array values
	toReturn[0]=parsedWeather["name"].getString();
	toReturn[1]=parsedWeather["weather.main"].getString();
	toReturn[2]=parsedWeather["weather.descrpition"].getString();
	//default kelvin, convert to celcius
	toReturn[3]=to_string(((float)(parsedWeather["main.temp"].getString()))-273.15);	
	toReturn[4]=parsedWeather["main.humidity"].getString();
	
	return toReturn;
}

//defaults for curl writefunction
size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written;
    written = fwrite(ptr, size, nmemb, stream);
    return written;
}
/*
Input: None
Function: Pulls the weather data, saves to an txt file, JSON
*/
void WeatherPanel::pullData() {
    CURL *pCurl;
    FILE *fptr;
    CURLcode codes;
	//sets url as api call
    char *url = "api.openweathermap.org/data/2.5/weather?q=London,ca&APPID=a814b2b3fb9f749e9aa297b1f0300a84";
    char outfilename[256] = "weatherfile.txt";
	//initialize
    pCurl = curl_easy_init();
    if (pCurl) {
        fptr = fopen(outfilename,"wb");
        curl_easy_setopt(pCurl, CURLOPT_URL, url);
        curl_easy_setopt(pCurl,, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(pCurl,, CURLOPT_WRITEDATA, fptr);
        res = curl_easy_perform(pCurl);
        curl_easy_cleanup(pCurl);
        fclose(fptr);
    }
}