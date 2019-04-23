#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SoftwareSerial.h>
#include <SimpleTimer.h>
char auth[] = "dc9e7e6fb0004a30b9b7f6dcdc413e8f";
char ssid[] ="Nokia";
char pass [] = "12345678";
SimpleTimer timer;
String myString;
char rdata;
int firstVal, secondVal, thirdVal;
int led1, led2;
void myTimerEvent()
{
	Blynk.virtualWrite(V1,millis()/1000);
}
void setup()
{
	Serial.begin(9600);
	Blynk.begin(auth,ssid,pass);
	timer.setInterval(1000L,sensorvalue1);
	timer.setInterval(1000L,sensorvalue2);
}
void loop()
{
	if(Serial.available()==0)
	{
		Blynk.run();
		timer.run();
	}
	if(Serial.available()>0)
	{
		rdata=Serial.read();
		myString=myString+rdata;
		if(rdata=='\n')
		{
			Serial.println (myString);
			String l =getValue(myString,',',0);
			String m= getValue(myString,',',1);
			
			led1 =l.toInt();
			led2 =m.toInt();
			
			myString="";
		}
	}
}
void sensorvalue1()
{
	int sdata=led1;
	Blynk.virtualWrite(V10,sdata);
}
void sensorvalue2()
{
	int sdata=led2;
	Blynk.virtualWrite(V11,sdata);
}
String getValue(String data,char separator,int index)
{
	int found=0;
	int strIndex[]={0,-1};
	int maxIndex=data.length()-1;
	for(int i=0;i<=maxIndex && found<=index;i++)
		if(data.charAt(i)==separator || i==maxIndex)
		{
			found++;
			strIndex[0]=strIndex[1]+1;
			strIndex[1]=(i==maxIndex)?i+1:i;
		}
	return found>index?data.substring(strIndex[0],strIndex[1]):"";
}
