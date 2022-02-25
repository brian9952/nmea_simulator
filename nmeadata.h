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
        char status1;
        char status2;
        float arrivalCircleRadius;
        QString unitsOfRadius;
        QString waypointId;
        QString checksum;
    }; AAM *aam;

    struct ALM { // GPS Almanac Data
        bool isClicked = false;
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
    }; ALM *alm;

    struct RSA { // Rudder Sensor Angle
        bool isClicked = false;
        bool isOn = false;
        int id = 3;
        QString starboardRudderSensor;
        QString status0;
        QString portRudderSensor;
        QString status1;
        QString checksum;
    }; RSA *rsa;

    struct RTE { // Routes
        bool isClicked = false;
        bool isOn = false;
        int id = 4;
        int numberOfRE;
        int sentenceNumber;
        QString sentenceMode;
        QString routeId;
        QString waypointId;
        QString additionalWaypointId;
    }; RTE *rte;

    const static int dataNumbers = 4;
    QString dataNames[dataNumbers] = {
        "Waypoint Arrival Alarm",
        "GPS Almanac Data",
        "Rudder Sensor Angle",
        "Routes"
    };

};

#endif // NMEADATA_H
