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

    // data status init
    for(int i = 0; i < dataNumbers; i++){
        dataStruct *newData = new dataStruct;
        newData->dataNames = names[i];
        newData->id = i;
        newData->isAdded = false;
        newData->isEnabled = false;
        dataStatus.push_back(newData);
    }

}

float nmeaData::roundFloat2(float val){
    float new_val = (int) (val * 100 + 0.5);
    return (float) new_val / 100;
}

float nmeaData::roundFloat1(float val){
    return ((float) ((int) val * 10)) / 10;
}

float nmeaData::randomFloat(float a, float b){
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

QString nmeaData::createAAMString(){
    QString str;
    str.append("$GPAAM,A,A,");

    // generate arrival circle radius val
    float rand = randomFloat(aam->arrivalCircleRadius_firstRange, aam->arrivalCircleRadius_lastRange);

    // append to str
    str.append(QString::number(roundFloat2(rand)));
    str.append(",N,WPTNME,*43\n");

    return str;
}

QString nmeaData::createBODString(){
    // todo
    QString str;
    str.append("$GPBOD, ");

    // generate bdt value
    float bdt_rand = randomFloat(bod->bearingDegreesTrue_firstRange,
                                 bod->bearingDegreesTrue_lastRange);

    QString bdt_val = QString::number(roundFloat1(bdt_rand));
    if(bdt_val.length() < 3)
        bdt_val.insert(0, '0');

    str.append(bdt_val);
    str.append(",T,");

    // generate bdm value
    float bdm_rand = randomFloat(bod->bearingDegreesMagn_firstRange,
                                 bod->bearingDegreesMagn_lastRange);

    QString bdm_val = QString::number(roundFloat1(bdm_rand));
    if(bdm_val.length() < 3)
        bdm_val.insert(0, '0');

    str.append(bdm_val);
    str.append(",M,POINTB,POINTA,*52\n");

    return str;
}
