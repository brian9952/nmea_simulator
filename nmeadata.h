#ifndef NMEADATA_H
#define NMEADATA_H

#include<QString>
#include<QVector>

class nmeaData
{
public:
    nmeaData();

    struct AAM { // Waypoint Arrival Alarm
        bool isClicked = false;
        bool isOn = false;
        int id = 1;
        float arrivalCircleRadius_firstRange; // 0.0 - 1.0
        float arrivalCircleRadius_lastRange; // 0.0 - 1.0
    }; AAM *aam;

    struct BOD { // bearing waypoint to waypoint
        bool isClicked = false;
        bool isOn = false;
        int id = 2;
        float bearingDegreesTrue_firstRange; // 0 - 360
        float bearingDegreesTrue_lastRange; // 0 - 360
        float bearingDegreesMagn_firstRange; // 0 - 360
        float bearingDegreesMagn_lastRange; // 0 - 360
    }; BOD *bod;

    struct DPT { // depth of water
        bool isClicked = false;
        bool isOn = false;
        int id = 3;
        float waterDepth_firstRange; // 0 - inf
        float waterDepth_lastRange; // 0 - inf
        float maxRange_firstRange; // 0 - inf
        float maxRange_lastRange; // 0 - inf
    }; DPT *dpt;

    struct ROT { // rate of turn
        bool isClicked = false;
        bool isOn = false;
        int id = 4;
        float rateOfTurn_firstRange; // 0 - 360
        float rateOfTurn_lastRange; // 0 - 360
    }; ROT *rot;

    const static int dataNumbers = 4;
    QString dataNames[dataNumbers] = {
        "Waypoint Arrival Alarm",
        "Bearing Waypoint to Waypoint",
        "Depth of Water",
        "Rate of Turn"
    };

};

#endif // NMEADATA_H
