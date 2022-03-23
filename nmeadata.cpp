#include "nmeadata.h"
#include<iostream>
#include<QtWidgets>

nmeaData::nmeaData()
{
    aam = new AAM;
    bod = new BOD;
    dpt = new DPT;
    rot = new ROT;

    // data add
    QString names[dataNumbers] = {
        "Waypoint Arrival Alarm",
        "Bearing Waypoint to Waypoint",
        "Depth of Water",
        "Rate of Turn"
    };

    for(int i = 0; i < dataNumbers; i++){
        dataStruct *newData = new dataStruct;
        newData->dataNames = names[i];
        newData->id = i;
        newData->isAdded = false;
        newData->isEnabled = false;
        dataStatus.push_back(newData);
    }

}

float nmeaData::randomFloat(float a, float b){
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

QString nmeaData::createAAMString(){
    QString str;
    str.append("GPAAM,A,A,");

    // generate arrival circle radius val
    float rand = randomFloat(aam->arrivalCircleRadius_firstRange, aam->arrivalCircleRadius_lastRange);

    // append to str
    str.append(QString::number(rand));
    str.append(",N,WPTNME,*43");

    return str;
}
