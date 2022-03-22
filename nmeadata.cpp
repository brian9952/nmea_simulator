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

QString nmeaData::createAAMString(){
    QString str;
    str.append("GPAAM,A,A,");

    // generate arrival circle radius val
    QRandomGenerator rand;
    rand.generate(aam->arrivalCircleRadius_firstRange, aam->arrivalCircleRadius_lastRange);
    double acr = rand.generateDouble();

    // append to str
    str.append(QString::number(acr));
    str.append(",N,WPTNME,*43");

    return str;
}
