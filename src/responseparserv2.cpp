#include "responseparserv2.h"

ResponseParserV2::ResponseParserV2(ChorusDevice * device): ResponseParser(device)
{
    qDebug() << "ResponseParserV4 created";
}

ResponseParserV2::~ResponseParserV2(){

}


void ResponseParserV2::parse(QString cmd){

    qDebug() << "parseDeviceProperty" << cmd;
    switch (cmd.at(0).toLatin1()) {
    case 'i':
    {
        bool ok;
        int tmp = cmd.mid(1).toInt(&ok, 16);
        if(ok){
            device->setCalibrated(tmp);
        } else {
            qCritical() << "invalid Calibrated";
        }
        break;
    }
    case 'R':
    {
        bool ok;
        int tmp = cmd.mid(1).toInt(&ok, 16);
        if(ok){
            device->setRace(tmp);
        } else {
            qCritical() << "invalid race";
        }
        break;
    }
    case 'M':
    {
        bool ok;
        int tmp = cmd.mid(1).toInt(&ok, 16);
        if(ok){
            device->setMinLaptime(tmp);
        } else {
            qCritical() << "invalid minLaptime";
        }
        break;
    }
    case 'B':
    {
        bool ok;
        int tmp = cmd.mid(1).toInt(&ok, 16);
        if(ok){
            device->setBand(tmp);
        } else {
            qCritical() << "invalid band";
        }
        break;
    }
    case 'C':
    {
        bool ok;
        int tmp = cmd.mid(1).toInt(&ok, 16);
        if(ok){
            device->setChannel(tmp);
        } else {
            qCritical() << "invalid channel";
        }
        break;
    }
    case 'Q':
    {
        bool ok;
        int tmp = cmd.mid(1).toInt(&ok, 16);
        if(ok){
            device->setFrequency(tmp);
        } else {
            qCritical() << "invalid frequency";
        }
        break;
    }
    case 'T':
    {
        bool ok;
        int tmp = cmd.mid(1).toInt(&ok, 16);
        if(ok){
            device->setThreshold(tmp);
        } else {
            qCritical() << "invalid threshold";
        }
        break;
    }
    case 'D':
    {
        bool ok;
        int tmp = cmd.mid(1).toInt(&ok, 16);
        if(ok){
            device->setSound(tmp);
        } else {
            qCritical() << "invalid sound";
        }
        break;
    }
    case 'V':
    {
        bool ok;
        int tmp = cmd.mid(1).toInt(&ok, 16);
        if(ok){
            device->setMonitor(tmp);
        } else {
            qCritical() << "invalid monitor";
        }
        break;
    }
    case 'F':
    {
        bool ok;
        int tmp = cmd.mid(1).toInt(&ok, 16);
        qDebug() <<"first lap" << tmp;
        if(ok){
            device->setFirstLap(tmp);
        } else {
            qCritical() << "invalid first lap";
        }
        break;
    }
    case 'S':
    {
        bool ok;
        int tmp = cmd.mid(1).toInt(&ok, 16);
        qDebug() <<"rssi" << tmp;
        if(ok){
            device->setRssi(tmp);
        } else {
            qCritical() << "invalid rssi";
        }
        break;
    }
    case 'd':
    {
        bool ok;
        int tmp = cmd.mid(1).toInt(&ok, 16);
        qDebug() <<"monitorDelay" << tmp;
        if(ok){
            device->setMonitorDelay(tmp);
        } else {
            qCritical() << "invalid monitorDelay";
        }
        break;
    }
    case 'P':
    {
        bool ok;
        int tmp = cmd.mid(1).toInt(&ok, 16);
        if(ok){
            device->setConfigured(tmp);
        } else {
            qCritical() << "invalid configured";
        }
        break;
    }
    case '#':
    {
        bool ok;
        int tmp = cmd.mid(1).toInt(&ok, 16);
        if(ok){
            device->setApi(tmp);
        } else {
            qCritical() << "invalid api";
        }
        break;
    }
    case 'X':
    {
        qDebug() << device;
        //writeData("R*V");
        break;
    }
    default:
        qInfo() << cmd.at(0)  << "command not implemented yet";
    }
}
