#ifndef NMEADATA_H
#define NMEADATA_H

#include<QString>

class nmeaData
{
public:
    nmeaData();

    struct AAM { // Waypoint Arrival Alarm
        bool isOn = false;
        int id = 1;
        char status1;
        char status2;
        float arrivalCircleRadius;
        QString unitsOfRadius;
        QString waypointId;
        QString checksum;
    }; AAM *aam = new AAM;

    struct ALM { // GPS Almanac Data
        bool isOn = false;
        int id = 2;
        int numberOfMessages;
        int satellitePRNNumber;
        int GPSWeekNumber;
        QString SVHealth;
        QString eccentricity;
        QString almanacReferenceTime;
        QString inclinationAngle;
        QString rateOfRightAscension;
        QString rootOfSemimajorAxis;
        QString argumentOfPerigee;
        QString longitudeOfAscensionMode;
        QString meanAnomaly;
        QString f0clockParameter;
        QString f1clockParameter;
        QString checksum;
    }; ALM *alm = new ALM;

    struct RSA { // Rudder Sensor Angle
        bool isOn = false;
        int id = 3;
        QString starboardRudderSensor;
        QString status0;
        QString portRudderSensor;
        QString status1;
        QString checksum;
    }; RSA *rsa = new RSA;

    struct RTE { // Routes
        bool isOn = false;
        int id = 4;
        int numberOfRE;
        int sentenceNumber;
        QString sentenceMode;
        QString routeId;
        QString waypointId;
        QString additionalWaypointId;
    }; RTE *rte = new RTE;

};

#endif // NMEADATA_H
