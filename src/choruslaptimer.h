#ifndef CHORUSLAPTIMER_H
#define CHORUSLAPTIMER_H

#include <QObject>
#include <QMap>
#include <QList>
#include <QDebug>
#include "chorusdevice.h"

typedef QMap<QString, ChorusDevice*> StringChorusDevicePtrMap;

class ChorusLaptimer : public QObject
{
    Q_OBJECT
    Q_PROPERTY(StringChorusDevicePtrMap devicesMap READ devicesMap NOTIFY devicesMapChanged)

public:
    explicit ChorusLaptimer(QObject *parent = nullptr);
    ~ChorusLaptimer();
    friend QDebug operator<<(QDebug debug, const ChorusLaptimer &laptimer);

    QMap<QString, ChorusDevice*> devicesMap() const;
    QList<ChorusDevice*> devices() const;
    void addDevice(ChorusDevice *device);
    ChorusDevice* getDevice(QString id);

signals:
    void devicesMapChanged(ChorusDevice *device);

public slots:

private:
    QMap<QString, ChorusDevice*> m_devicesMap;
};

#endif // CHORUSLAPTIMER_H
