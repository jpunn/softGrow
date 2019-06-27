
#include <EmbAJAX.h>
#include <WiFiManager.h> 
#include <ESPmDNS.h>
#include "time.h"
#include "softGrowWeb.h"
EmbAJAXOutputDriverWebServerClass server(80);
EmbAJAXOutputDriver driver(&server);


const char* ntpServer = "ca.pool.ntp.org";
const long  gmtOffset_sec = 3600;
const int   daylightOffset_sec = 3600;
int second;
int minute;
int hour;
int day;
int month;
int year;
int weekday;
long current;
struct tm timeinfo;


float currentTemp ;
float currentHumi;
float heatIndex ;
float dewPoint;
  /*
struct tm
{
int    tm_sec;   //   Seconds [0,60]. 
int    tm_min;   //   Minutes [0,59]. 
int    tm_hour;  //   Hour [0,23]. 
int    tm_mday;  //   Day of month [1,31]. 
int    tm_mon;   //   Month of year [0,11]. 
int    tm_year;  //   Years since 1900. 
int    tm_wday;  //   Day of week [0,6] (Sunday =0). 
int    tm_yday;  //   Day of year [0,365]. 
int    tm_isdst; //   Daylight Savings flag. 
}
 */  
//----------------------------------------------------------
void printLocalTime()
{

  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%A, %d %B %Y %H:%M:%S");
}

//------------------------------------------------------------------------
char bufTmp[10];
char bufHum[10];
char bufIndx[10];
char bufDup[10];
void updateUI() {
  // Note that we do _not_ have to update the shared slider on the other page. It is a single object to EmbAJAX, and thus
  // is automatically in sync between the pages. So the only thing to do, here, is to send the other_slider value to the display.
 Temp_display.setValue(dtostrf(currentTemp,7,2,bufTmp));
 Humi_display.setValue(dtostrf(currentHumi,7,2,bufHum));
 Indx_display.setValue(dtostrf(heatIndex,7,2,bufIndx));
 Dup_display.setValue(dtostrf(dewPoint,7,2,bufDup));

}
//-----------------------------------------------------------------------
void wifiConnect()
{
//WiFiManager
//Local intialization. Once its business is done, there is no need to keep it around

WiFiManager wifiManager;
wifiManager.autoConnect("espap", "PASSWORD");
//if you get here you have connected to the WiFi
 
 if (!MDNS.begin("softgrow")) {
        Serial.println("Error setting up MDNS responder!");
        while(1) {
            delay(500);
        }
    }
Serial.println("mDNS responder started");
Serial.println("connected...yeey :)");
configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
printLocalTime();

// Tell the server to serve the two pages at root, and at "/page2", respectively.
// installPage() abstracts over the (trivial but not uniform) WebServer-specific instructions to do so
driver.installPage(&page1, "/", updateUI);
server.begin();
updateUI(); // to initialize display
}





