#include "choruslaptimer.h"
#include <QMapIterator>

ChorusLaptimer::ChorusLaptimer(QObject *parent) : QObject(parent), m_devicesMap()
{

}

ChorusLaptimer::~ChorusLaptimer(){
   qDeleteAll(m_devicesMap);
   m_devicesMap.clear();
}

void ChorusLaptimer::addDevice(ChorusDevice *device){
    if(!m_devicesMap.contains(device->id())){
        m_devicesMap.insert(device->id(), device);
        emit devicesMapChanged(device);
    }
}

ChorusDevice* ChorusLaptimer::getDevice(QString id){
    ChorusDevice * result= nullptr;
    if(m_devicesMap.contains(id)){
        result = m_devicesMap.value(id);
    } else {
        result = new ChorusDevice(id, this);
        addDevice(result);
    }

    return result;
}

QDebug operator<<(QDebug debug, const ChorusLaptimer &laptimer){
    QDebugStateSaver saver(debug);
    debug<< "devices :" << laptimer.devicesMap();
    return debug;
}

QList<ChorusDevice*> ChorusLaptimer::devices() const{
    return m_devicesMap.values();
}

QMap<QString, ChorusDevice*> ChorusLaptimer::devicesMap() const{
    return m_devicesMap;
}
