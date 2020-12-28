#include <Arduino.h>

#include "Seeed_LDC1612.h"
 
LDC1612 sensor;
const u32 DISTANCE_00=44000000;  //do not detect
const u32 DISTANCE_00_01=60000000;  // distance:<1mm
const u32 DISTANCE_01_05=47000000;  // distance:1mm~5mm
//const u32 DISTANCE_01_05=45000000;  // distance:1mm~5mm
const u32 DISTANCE_05_10=44250000; // distance:5mm~10mm
const u32 DISTANCE_10_15=44080000; // distance:10mm~15mm
const u32 DISTANCE_15_20=44020000; // distance:15mm~20mm

void setup() {
  Serial.begin(115200);
    delay(100);
    Serial.println("start!");
 
    sensor.init();
 
    if(sensor.single_channel_config(CHANNEL_0))
    {
        Serial.println("can't detect sensor!");
        while(1);
    }

    pinMode(LED_BUILTIN, OUTPUT);

    //auto timeConst = 0x0546;
    auto timeConst = 0x04d6;
    //auto timeConst = 0xffff;

    auto fref = sensor.fref(CHANNEL_0);

    auto time = (timeConst*16 + 6) / fref;
    Serial.println("time="+String(time)+"  fref="+String(fref)+"\n");

    sensor.set_conversion_time(CHANNEL_0, timeConst);
}

void loop() {
    u32 result_channel1=0;
 
    /*shows the status of sensor.*/
    //sensor.get_sensor_status();
 
    /*Get channel 0 result and parse it.*/
    sensor.get_channel_result(CHANNEL_0,&result_channel1);
 
    /*Test the distance between the coin and the sensor. 
    Note that the accuracy is for reference only.
    Please suspend the sensor during the test! */
    if(0!=result_channel1)
    {
        /*Serial.println("raw = "+String(result_channel1));

        if(result_channel1<DISTANCE_00)
        {
            Serial.println("There is no coin here!");
        }*/
 
        if(result_channel1<DISTANCE_00_01 && result_channel1>=DISTANCE_01_05)
        //if(result_channel1>=DISTANCE_00_01)
        {
            digitalWrite(LED_BUILTIN, HIGH);
        }
        else
        {
            digitalWrite(LED_BUILTIN, LOW);
        }

        /*if(result_channel1>=DISTANCE_00_01)
        {
            Serial.println("The distance between the COIN is 0~1mm");
        }
 
        if(result_channel1<DISTANCE_00_01&&result_channel1>=DISTANCE_01_05)
        {
            Serial.println("The distance between the COIN is 1~5mm");
        }
 
        if(result_channel1<DISTANCE_01_05&&result_channel1>=DISTANCE_05_10)
        {
            Serial.println("The distance between the COIN is 5~10mm");
        }
 
        if(result_channel1<DISTANCE_05_10&&result_channel1>=DISTANCE_10_15)
        {
            Serial.println("The distance between the COIN is 10~15mm");
        }
 
        if(result_channel1<DISTANCE_10_15&&result_channel1>=DISTANCE_15_20)
        {
            Serial.println("The distance between the COIN is 15~20mm");
        }
 
        if(result_channel1<DISTANCE_15_20&&result_channel1>=DISTANCE_00)
        {
            Serial.println("The distance between the COIN is more than 2mm");
        }*/
 
    }
 
    delay(2);
}