#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QtCore/QtGlobal>
#include <QLabel>
#include <QKeyEvent>
#include <QTextToSpeech>

#include <QtSerialPort/QSerialPort>

#include "choruslaptimer.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

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
    void keyPressEvent(QKeyEvent *event);
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

};

#endif // MAINWINDOW_H
