#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QtCore/QtGlobal>
#include <QLabel>
#include <QKeyEvent>
#include <QTextToSpeech>
#include <QSettings>

#include <QtSerialPort/QSerialPort>

#include "choruslaptimer.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

    static const QString SETTINGS_KEY_SERIAL;
    static const QString SETTINGS_KEY_VOICE;
    static const QString SETTINGS_KEY_LAPTIME;
    static const QString SETTINGS_KEY_BEST_LAPTIME;
    static const QString SETTINGS_KEY_RATE;

protected:
    void closeEvent(QCloseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void openSerialPort();
    void closeSerialPort();
    void handleError(QSerialPort::SerialPortError error);
    void readData();
    void writeInputData();
    void writeData(const QString &data);
    void deviceAdded(ChorusDevice* device);
    void rateChanged(int rate);
    void voicesComboBoxIndexChanged(int index);
    void testVoiceButtonClicked();
    void speechStateChanged(QTextToSpeech::State state);

private:
    void fillSerialPortsComboBox();
    void fillSpeechForm();
    void parseDeviceProperty(QString cmd, ChorusDevice* device);
    int parseHex(QString str);

    Ui::MainWindow *ui;
    QLabel *statusLabel;
    QLabel *deviceNumberLabel;
    QSerialPort *serial;
    QString dateFormat = QString("yyyy.MM.dd HH:mm:ss.zzz");
    int numberOfDevices;
    ChorusLaptimer laptimer;
    QTextToSpeech speech;
    QSettings settings;

};

#endif // MAINWINDOW_H
