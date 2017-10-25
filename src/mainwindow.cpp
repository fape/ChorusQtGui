#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QLabel>
#include <QtSerialPort/QSerialPortInfo>
#include <QDateTime>
#include <QDebug>
#include "chorusdeviceform.h"
#include "speechinfoholder.h"

const QString MainWindow::SETTINGS_KEY_SERIAL = QString("serial");
const QString MainWindow::SETTINGS_KEY_VOICE = QString("voice");
const QString MainWindow::SETTINGS_KEY_BEST_LAPTIME = QString("bestLaptime");
const QString MainWindow::SETTINGS_KEY_LAPTIME = QString("laptime");
const QString MainWindow::SETTINGS_KEY_RATE = QString("rate");

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    laptimer(this),
    speech(this),
    settings(this)
{
    ui->setupUi(this);
    serial = new QSerialPort(this);
    statusLabel = new QLabel();
    deviceNumberLabel = new QLabel();
    ui->statusBar->addWidget(statusLabel);
    ui->statusBar->addWidget(deviceNumberLabel);
    ui->progressBar->setPalette(Qt::red);

    ui->mainStackedWidget->setCurrentWidget(ui->connectPage);
    setWindowIcon(QIcon(":chorusqtgui.ico"));

    for(int i= 0; i<8; i++){
        ui->debugDebugLayout->addWidget(new ChorusDeviceForm());
    }

    fillSerialPortsComboBox();

    connect(ui->connectButton, &QPushButton::clicked, this, &MainWindow::openSerialPort);
    connect(ui->disconnectButton, &QPushButton::clicked, this, &MainWindow::closeSerialPort);
    connect(serial, static_cast<void (QSerialPort::*)(QSerialPort::SerialPortError)>(&QSerialPort::error),
            this, &MainWindow::handleError);
    connect(serial, &QSerialPort::readyRead, this, &MainWindow::readData);
    connect(ui->serialInputLineEdit, &QLineEdit::returnPressed, this, &MainWindow::writeInputData);
    connect(&laptimer, &ChorusLaptimer::devicesMapChanged, this, &MainWindow::deviceAdded);
    /*ChorusDevice *d = new ChorusDevice(this);
    d->setId(1);
    d->addLaptime(123, 456);
    qDebug() << "empty device"<< *d;
    laptimer.addDevice(d);
    qDebug() << laptimer;*/

    fillSpeechForm();

    //set volume to max
    speech.setVolume(1.0);
}

void MainWindow::keyPressEvent(QKeyEvent *event){
    qInfo() << "KeyEvent" << event->key() << "mod" << event->modifiers();
}

void MainWindow::openSerialPort(){
    statusLabel->setText(tr("Connecting..."));
    deviceNumberLabel->clear();
    serial->setPortName(ui->serialPortsComboBox->currentText());

    serial->setBaudRate(QSerialPort::Baud115200);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);

    if (serial->open(QIODevice::ReadWrite)) {
        statusLabel->setText(tr("Connected to %0").arg(ui->serialPortsComboBox->currentText()));
        qInfo() << "Connected to"<< qPrintable(serial->portName()) << "115200, 8, none, 1, none" ;
        ui->mainStackedWidget->setCurrentWidget(ui->mainPage);
        ui->chorusLogoLabel->hide();
        ui->serialLogListWidget->clear();
        writeData("N0"); //enumerate all devices, resposen will be device count
    } else {
        QMessageBox::critical(this, tr("Error"), serial->errorString());
        statusLabel->setText(tr("Connection error"));
    }
}

void MainWindow::closeSerialPort(){
    if (serial->isOpen()){
        writeData("R*v");
        serial->close();
    }
    statusLabel->setText(tr("Disconnected"));
    deviceNumberLabel->clear();
    qInfo() << "Disconnected from" << qPrintable(serial->portName());
    ui->chorusLogoLabel->show();
    ui->mainStackedWidget->setCurrentWidget(ui->connectPage);
}

void MainWindow::handleError(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        QMessageBox::critical(this, tr("Critical Error"), serial->errorString());
        qCritical() << "Serial port critical error:" << qPrintable(serial->errorString());
        closeSerialPort();
    }
}

void MainWindow::readData(){
    qInfo() << "read data called";
    if(serial -> isOpen()){
        while(serial->canReadLine()){
            QString line = QString(serial->readLine()).trimmed();
            qInfo() << "line received:" << qPrintable(line);
            ui->serialLogListWidget->addItem(QString("[RX %1] %2")
                                             .arg(QDateTime::currentDateTime().toString(dateFormat))
                                             .arg(line));
            switch(line.at(0).toUpper().toLatin1()){
            case 'N':
            {
                numberOfDevices = line.right(line.size()-1).toInt();
                QString msg;
                if(numberOfDevices == 0){
                    msg = tr("No device found");
                } else if(numberOfDevices == 1){
                    msg = tr("1 device found");
                } else{
                    msg = tr("%1 devices found").arg(numberOfDevices);
                }
                deviceNumberLabel->setText(msg);
                writeData("R*A"); // get all bulk devices states, response all state info separatly
                break;
            }
            case 'S':
            {
                qDebug()<< "S received";
                ChorusDevice* device = laptimer.getDevice(QString(line.at(1)));
                parseDeviceProperty(line.mid(2), device);
                break;
            }
            }
            ui->serialLogListWidget->scrollToBottom();
        }
    } else {
        qCritical() << "ReadData called but serial is closed";
    }
}

void MainWindow::parseDeviceProperty(QString cmd, ChorusDevice* device){
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
        writeData("R*V");
        break;
    }
    default:
        qInfo() << cmd.at(0)  << "command not implemented yet";
    }
}

void MainWindow::deviceAdded(ChorusDevice *device){
    qDebug() << "deviceAdded";
    connect(device, &ChorusDevice::rssiChanged, ui->lcdNumber, QOverload<int>::of(&QLCDNumber::display));
    connect(device, &ChorusDevice::rssiChanged, ui->progressBar, &QProgressBar::setValue);
}
void MainWindow::writeInputData(){
    writeData(ui->serialInputLineEdit->text());
}

void MainWindow::writeData(const QString &data){
    qInfo() << "data to write:" << qPrintable(data);
    if(serial->isOpen()){
        serial->write(QString("%1\n").arg(data).toLocal8Bit());
        ui->serialLogListWidget->addItem(QString("[TX %1] %2")
                                         .arg(QDateTime::currentDateTime().toString(dateFormat))
                                         .arg(data));
    }
    ui->serialInputLineEdit->clear();
}


MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event){
    settings.setValue(SETTINGS_KEY_SERIAL, ui->serialPortsComboBox->currentText());
    settings.setValue(SETTINGS_KEY_VOICE,ui->voicesComboBox->currentText());
    settings.setValue(SETTINGS_KEY_LAPTIME,ui->newLaptimeLineEdit->text());
    settings.setValue(SETTINGS_KEY_BEST_LAPTIME,ui->newBestLaptimeLineEdit->text());
    settings.setValue(SETTINGS_KEY_RATE,ui->rateSlider->value());
    closeSerialPort();
    event->accept();
}

void MainWindow::fillSerialPortsComboBox(){
    ui->serialPortsComboBox->clear();
    const auto infos = QSerialPortInfo::availablePorts();
    QString last;
    if(infos.empty()){
        ui->serialPortStacketWidget->setCurrentWidget(ui->noSerialPage);
    } else {
        ui->serialPortStacketWidget->setCurrentWidget(ui->serialPage);
        for (const QSerialPortInfo &info : infos) {
            last = info.portName();
            ui->serialPortsComboBox->addItem(last);
        }
        ui->serialPortsComboBox->setCurrentText(settings.value(SETTINGS_KEY_SERIAL, last).toString());
    }
}

void MainWindow::rateChanged(int rate){
    qDebug() << "rateChanged" << rate;
    speech.setRate(rate / 10.0);
}

void MainWindow::fillSpeechForm(){
    qDebug() << "fillSpeechForm";
    ui->voicesComboBox->clear();
    QString label;
    foreach(const QLocale& locale, speech.availableLocales()){
        speech.setLocale(locale);
        foreach(const QVoice& voice, speech.availableVoices()){
            label = QString("%1 - %2 - %3 - %4")
                    .arg(QLocale::languageToString(locale.language()))
                    .arg(voice.name())
                    .arg(QVoice::genderName(voice.gender()))
                    .arg(QVoice::ageName(voice.age()));
            qInfo() << label;
            ui->voicesComboBox->addItem(label, QVariant::fromValue(SpeechInfoHolder(locale, voice)));
        }
    }
    connect(ui->rateSlider, &QSlider::valueChanged, this, &MainWindow::rateChanged);
    connect(&speech, &QTextToSpeech::stateChanged, this, &MainWindow::speechStateChanged);
    connect(ui->testVoiceButton, &QPushButton::clicked, this, &MainWindow::testVoiceButtonClicked);
    connect(ui->voicesComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::voicesComboBoxIndexChanged);

    ui->voicesComboBox->setCurrentText(settings.value(SETTINGS_KEY_VOICE, label).toString());
    ui->newBestLaptimeLineEdit->setText(settings.value(SETTINGS_KEY_BEST_LAPTIME, ui->newBestLaptimeLineEdit->text()).toString());
    ui->newLaptimeLineEdit->setText(settings.value(SETTINGS_KEY_LAPTIME, ui->newLaptimeLineEdit->text()).toString());
    ui->rateSlider->setValue(settings.value(SETTINGS_KEY_RATE, 0).toInt());
}

void MainWindow::voicesComboBoxIndexChanged(int index){
    SpeechInfoHolder data = ui->voicesComboBox->itemData(index).value<SpeechInfoHolder>();
    speech.setLocale(data.locale());
    speech.setVoice(data.voice());
}


void MainWindow::testVoiceButtonClicked(){
    qDebug() << "testVoiceButtonClicked" << ui->newBestLaptimeLineEdit->text();
    speech.say(ui->newBestLaptimeLineEdit->text());
}

void MainWindow::speechStateChanged(QTextToSpeech::State state){
    qDebug() << "speechStateChanged" << state;
}


