#include "chorusdevice.h"

ChorusDevice::ChorusDevice(QString id, QObject *parent) : QObject(parent),
    m_id(id), m_calibrated(),  m_race(), m_minLaptime(), m_band(), m_channel(), m_frequency(), m_threshold(), m_sound(), m_monitor(),
    m_firstLap(), m_rssi(), m_monitorDelay(), m_laptimes(), m_configured(), m_api()
{        
}

void ChorusDevice::addLaptime(int key, int laptime){
    bool insert = true;
    if(m_laptimes.contains(key)){
        int tmp = m_laptimes.value(key);
        if(tmp == laptime){
            insert = false;
        }
    }
    if(insert){
        m_laptimes.insert(key, laptime);
        emit laptimesChanged();
    }
}

QDebug operator<<(QDebug debug, const ChorusDevice &device){
    QDebugStateSaver saver(debug);
    debug << &device;
    return debug;
}

QDebug operator<<(QDebug debug, const ChorusDevice *device){
    QDebugStateSaver saver(debug);
    debug.nospace() << "id: " << device->id()<< ", calibrated: " << device->calibrated() << ", race: " << device->race()
                    << ", minLaptime: " << device->minLaptime() << ", band: " << device->band() << ", channel: " << device->channel()
                    << ", frequency: " << device->frequency() << ", threshold: " << device->threshold() << ", sound: "<<device->sound()
                    << ", monitor: "<< device->monitor() << ", firstLap: " << device->firstLap() << ", rssi: "<< device->rssi()
                    << ", monitorDelay: "<< device->monitorDelay() << ", laptimes: "<< device->laptimes()
                    << ", configured: "<< device->configured() << ", api: "<<device->api();

    return debug;
}

QString ChorusDevice::id() const
{
    return m_id;
}

bool ChorusDevice::calibrated() const{
    return m_calibrated;
}

void ChorusDevice::setCalibrated(const bool calibrated){
    if(calibrated != m_calibrated){
        m_calibrated = calibrated;
        emit calibratedChanged(calibrated);
    }
}

bool ChorusDevice::race() const{
    return m_race;
}

void ChorusDevice::setRace(const bool race){
    if(race != m_race){
        m_race = race;
        emit raceChanged(race);
    }
}

int ChorusDevice::minLaptime() const{
    return m_minLaptime;
}

void ChorusDevice::setMinLaptime(const int minLaptime){
    if (minLaptime != m_minLaptime){
        m_minLaptime = minLaptime;
        emit minLaptimeChanged(minLaptime);
    }
}

int ChorusDevice::band() const{
    return m_band;
}

void ChorusDevice::setBand(const int band){
    if (band != m_band){
        m_band = band;
        emit bandChanged(band);
    }
}

int ChorusDevice::channel() const{
    return m_channel;
}

void ChorusDevice::setChannel(const int channel){
    if(channel != m_channel){
        m_channel = channel;
        emit channelChanged(channel);
    }
}

int ChorusDevice::frequency() const{
    return m_frequency;
}

void ChorusDevice::setFrequency(const int frequency){
    if(frequency != m_frequency){
        m_frequency = frequency;
        emit frequencyChanged(frequency);
    }
}

int ChorusDevice::threshold() const{
    return m_threshold;
}

void ChorusDevice::setThreshold(const int threshold){
    if(threshold != m_threshold){
        m_threshold = threshold;
        emit thresholdChanged(threshold);
    }
}

bool ChorusDevice::sound() const{
    return m_sound;
}

void ChorusDevice::setSound(const bool sound){
    if(sound != m_sound){
        m_sound = sound;
        emit soundChanged(sound);
    }
}

bool ChorusDevice::monitor() const{
    return m_monitor;
}

void ChorusDevice::setMonitor(const bool monitor){
    if(monitor != m_monitor){
        m_monitor = monitor;
        emit monitorChanged(monitor);
    }
}

bool ChorusDevice::firstLap() const{
    return m_firstLap;
}

void ChorusDevice::setFirstLap(const bool firstLap){
    if(firstLap != m_firstLap){
        m_firstLap = firstLap;
        emit firstLapChanged(firstLap);
    }
}

int ChorusDevice::rssi() const{
    return m_rssi;
}

void ChorusDevice::setRssi(const int rssi){
    if(rssi != m_rssi){
        m_rssi = rssi;
        emit rssiChanged(rssi);
    }
}

int ChorusDevice::monitorDelay() const{
    return m_monitorDelay;
}

void ChorusDevice::setMonitorDelay(const int monitorDelay){
    if(monitorDelay != m_monitorDelay){
        m_monitorDelay = monitorDelay;
        emit monitorDelayChanged(monitorDelay);
    }
}

QMap<int, int> ChorusDevice::laptimes() const{
    return m_laptimes;
}

bool ChorusDevice::configured() const{
    return m_configured;
}

void ChorusDevice::setConfigured(const bool configured){
    if (configured != m_configured){
        m_configured = configured;
        emit configuredChanged(configured);
    }
}

int ChorusDevice::api() const{
    return m_api;
}

void ChorusDevice::setApi(const int api){
    if (api != m_api){
        m_api = api;
        emit apiChanged(api);
    }
}
