#ifndef CHORUSDEVICE_H
#define CHORUSDEVICE_H

#include <QObject>
#include <QMap>
#include <QDebug>

class ChorusDevice : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString id READ id) //  N
    Q_PROPERTY(bool race READ race WRITE setRace NOTIFY raceChanged) // R
    Q_PROPERTY(int minLaptime READ minLaptime WRITE setMinLaptime NOTIFY minLaptimeChanged) // M
    Q_PROPERTY(int band READ band WRITE setBand NOTIFY bandChanged) // B
    Q_PROPERTY(int channel READ channel WRITE setChannel NOTIFY channelChanged) // C
    Q_PROPERTY(int frequency READ frequency WRITE setFrequency NOTIFY frequencyChanged) // Q
    Q_PROPERTY(int threshold READ threshold WRITE setThreshold NOTIFY thresholdChanged) // T
    Q_PROPERTY(bool sound READ sound WRITE setSound NOTIFY soundChanged) // D
    Q_PROPERTY(bool monitor READ monitor WRITE setMonitor NOTIFY monitorChanged) // V
    Q_PROPERTY(bool firstLap READ firstLap WRITE setFirstLap NOTIFY firstLapChanged) // F
    Q_PROPERTY(int rssi READ rssi WRITE setRssi NOTIFY rssiChanged) // S
    Q_PROPERTY(QMap<int, int> laptimes READ laptimes NOTIFY laptimesChanged) // L
    Q_PROPERTY(bool configured READ configured WRITE setConfigured NOTIFY configuredChanged) // P
    Q_PROPERTY(int api READ api WRITE setApi NOTIFY apiChanged) // #

public:
    explicit ChorusDevice(QString id, QObject *parent = nullptr);

    void addLaptime(int key, int laptime);
    friend QDebug operator<<(QDebug debug, const ChorusDevice &device);
    friend QDebug operator<<(QDebug debug, const ChorusDevice *device);

    // PROPERTIES
    QString id() const;
    bool race() const;
    void setRace(const bool race);
    int minLaptime() const;
    void setMinLaptime(const int minLaptime);
    int band() const;
    void setBand(const int band);
    int channel() const;
    void setChannel(const int channel);
    int frequency() const;
    void setFrequency(const int frequency);
    int threshold() const;
    void setThreshold(const int threshold);
    bool sound() const;
    void setSound(const bool sound);
    bool monitor() const;
    void setMonitor(const bool monitor);
    bool firstLap() const;
    void setFirstLap(const bool firstLap);
    int rssi() const;
    void setRssi(const int rssi);
    QMap<int, int> laptimes() const;
    bool configured() const;
    void setConfigured(const bool configured);
    int api() const;
    void setApi(const int api);

signals:

    // PROPERTIES
    void raceChanged(bool race);
    void minLaptimeChanged(bool race);
    void bandChanged(int id);
    void channelChanged(int id);
    void frequencyChanged(int id);
    void thresholdChanged(int id);
    void soundChanged(bool race);
    void monitorChanged(bool race);
    void firstLapChanged(bool race);
    void rssiChanged(int id);
    void laptimesChanged();
    void configuredChanged(bool race);
    void apiChanged(int id);

public slots:

private:
    QString m_id;
    bool m_race;
    int m_minLaptime;
    int m_band;
    int m_channel;
    int m_frequency;
    int m_threshold;
    bool m_sound;
    bool m_monitor;
    bool m_firstLap;
    int m_rssi;
    QMap<int, int> m_laptimes;
    bool m_configured;
    int m_api;

};

#endif // CHORUSDEVICE_H
