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
