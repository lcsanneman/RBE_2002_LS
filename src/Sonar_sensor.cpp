#include <Romi32U4.h>
#include "Sonar_sensor.h"

void SonarSensor::Init(void)
{
    pinMode(pin_TRIG,OUTPUT);
    pinMode(pin_ECHO, INPUT);   
}

float SonarSensor::PrintData(void)
{
    Serial.println(ReadData());
}

float SonarSensor::ReadData(void)
{
    //assignment 1.2
    //read out and calibrate your sonar sensor, to convert readouts to distance in [cm]

    digitalWrite(pin_TRIG,LOW);
    delayMicroseconds(2);

    digitalWrite(pin_TRIG,HIGH);
    delayMicroseconds(10);
    digitalWrite(pin_TRIG,LOW);
    unsigned long duration = 0;
    duration = pulseIn(pin_ECHO,HIGH);
    double distance = duration*3.4/2.0;
    
    //if(millis()>tempTime+150)
    //{
    //  tempTime=millis();
        Serial.print("Distance:    ");
        Serial.println(distance);
    //}
    return distance;

    return 0;
}