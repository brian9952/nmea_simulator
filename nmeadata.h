#ifndef NMEADATA_H
#define NMEADATA_H

#include<QString>
#include<QVector>

class nmeaData
{
public:
    nmeaData();

    struct AAM { // Waypoint Arrival Alarm
        int id = 0;
        int duration;
        float arrivalCircleRadius_firstRange; // 0.0 - 1.0
        float arrivalCircleRadius_lastRange; // 0.0 - 1.0
    }; AAM *aam;

    struct BOD { // bearing waypoint to waypoint
        int id = 1;
        int duration;
        float bearingDegreesTrue_firstRange; // 0 - 360
        float bearingDegreesTrue_lastRange; // 0 - 360
        float bearingDegreesMagn_firstRange; // 0 - 360
        float bearingDegreesMagn_lastRange; // 0 - 360
    }; BOD *bod;

    struct DPT { // depth of water
        int id = 2;
        int duration;
        float waterDepth_firstRange; // 0 - inf
        float waterDepth_lastRange; // 0 - inf
        float maxRange_firstRange; // 0 - inf
        float maxRange_lastRange; // 0 - inf
    }; DPT *dpt;

    struct ROT { // rate of turn
        int id = 3;
        int duration;
        float rateOfTurn_firstRange; // 0 - 360
        float rateOfTurn_lastRange; // 0 - 360
    }; ROT *rot;

    struct dataStruct {
        int id;
        QString dataNames;
        bool isEnabled;
        bool isAdded;
    };

    QVector<dataStruct*> dataStatus;
    const static int dataNumbers = 4;

    // get string data
    QString createAAMString();

private:
    float randomFloat(float a, float b);
    float roundFloat(float val);

};

#endif // NMEADATA_H
