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

    struct MWV { // wind speed and angle
        int id = 4;
        int duration;
        float windAngle_firstRange; // 0 - 359
        float windAngle_lastRange; // 0 - 359
        float windSpeed_firstRange; // 0 - 300
        float windSpeed_lastRange; // 0 - 300
    }; MWV *mwv;

    struct RSA { // rudder sensor angle
        int id = 5;
        int duration;
        float starboardRudder_firstRange;
        float starboardRudder_lastRange;
        float portRudder_firstRange;
        float portRudder_lastRange;
    }; RSA *rsa;

    struct HDT { // heading true
        int id = 6;
        int duration;
        float heading_firstRange; // 0 - 359
        float heading_lastRange; // 0 - 359
    }; HDT *hdt;

    struct dataStruct {
        int id;
        int sec;
        int duration;
        QString dataNames;
        bool isEnabled;
        bool isAdded;
    };

    QVector<dataStruct*> dataStatus;
    const static int dataNumbers = 7;

    // get string data
    QString createAAMString();
    QString createBODString();
    QString createDPTString();
    QString createROTString();
    QString createMWVString();
    QString createRSAString();
    QString createHDTString();

private:
    float randomFloat(float a, float b);
    float roundFloat1(float val);
    float roundFloat2(float val);
    QString generateChecksum(QString &str);

};

#endif // NMEADATA_H
