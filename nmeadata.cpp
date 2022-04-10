#include "nmeadata.h"
#include<iostream>
#include<QtWidgets>

nmeaData::nmeaData()
{
    aam = new AAM;
    bod = new BOD;
    dpt = new DPT;
    rot = new ROT;
    mwv = new MWV;
    rsa = new RSA;
    hdt = new HDT;

    // data add
    QString names[dataNumbers] = {
        "Waypoint Arrival Alarm",
        "Bearing Waypoint to Waypoint",
        "Depth of Water",
        "Rate of Turn",
        "Wind Speed and Angle",
        "Rudder Sensor Angle",
        "Heading - True"
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

QString nmeaData::createDPTString(){
    QString str;
    str.append("$INDPT,");

    // generate waterdepth val
    float wd_rand = randomFloat(dpt->waterDepth_firstRange,
                                dpt->waterDepth_lastRange);
    str.append(QString::number(roundFloat2(wd_rand)));
    str.append(",");

    // generate maxRange val
    float maxRange_rand = randomFloat(dpt->maxRange_firstRange,
                                      dpt->maxRange_lastRange);
    str.append(QString::number(roundFloat2(maxRange_rand)));
    str.append("*46\n");

    return str;
}

QString nmeaData::createROTString(){
    QString str;
    str.append("$HEROT,");

    // generate rate of turn val
    float rot_rand = randomFloat(rot->rateOfTurn_firstRange,
                                 rot->rateOfTurn_lastRange);
    str.append(QString::number(roundFloat2(rot_rand)));
    str.append(",A*2B\n");

    return str;
}

QString nmeaData::createMWVString(){
    QString str;
    str.append("$GEMWV,");

    // generate wind angle val
    float wa_rand = randomFloat(mwv->windAngle_firstRange,
                                mwv->windAngle_lastRange);

    str.append(QString::number(roundFloat2(wa_rand)));
    str.append(",R,");

    float ws_rand = randomFloat(mwv->windSpeed_firstRange,
                                mwv->windSpeed_lastRange);

    str.append(QString::number(roundFloat2(ws_rand)));
    str.append(",K,A*5E\n");

    return str;
}

QString nmeaData::createRSAString(){
    QString str;
    str.append("$WARSA,");

    // generate sr val
    float sr_rand = randomFloat(rsa->starboardRudder_firstRange,
                                rsa->starboardRudder_lastRange);

    str.append(QString::number(roundFloat2(sr_rand)));
    str.append(",A,");

    // generate pr val
    float pr_rand = randomFloat(rsa->portRudder_firstRange,
                                rsa->portRudder_lastRange);

    str.append(QString::number(roundFloat2(pr_rand)));
    str.append(",A,*2B\n");

    return str;
}

QString nmeaData::createHDTString(){
    QString str;
    str.append("$HEHDT,");

    // generate hd val
    float hd_rand = randomFloat(hdt->heading_firstRange,
                                hdt->heading_lastRange);

    str.append(QString::number(roundFloat2(hd_rand)));
    str.append(",T*03\n");

    return str;
}
