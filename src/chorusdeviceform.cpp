#include "chorusdeviceform.h"
#include "ui_chorusdeviceform.h"
#include <QDebug>

int const ChorusDeviceForm::channelTable[8][8] = {
    // Channel 0 - 7
    {5658, 5695, 5732, 5769, 5806, 5843, 5880, 5917}, // Raceband
    {5865, 5845, 5825, 5805, 5785, 5765, 5745, 5725}, // Band A
    {5733, 5752, 5771, 5790, 5809, 5828, 5847, 5866}, // Band B
    {5705, 5685, 5665, 5645, 5885, 5905, 5925, 5945}, // Band E
    {5740, 5760, 5780, 5800, 5820, 5840, 5860, 5880}, // Band F / Airwave
    {5362, 5399, 5436, 5473, 5510, 5547, 5584, 5621}, // Band D / 5.3
    {5180, 5200, 5220, 5240, 5745, 5765, 5785, 5805}, // connex
    {5825, 5845, 5845, 5845, 5845, 5845, 5845, 5845}  // even more connex, last 6 unused!!!
};

ChorusDeviceForm::ChorusDeviceForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChorusDeviceForm)
{
    ui->setupUi(this);
    //connect(ui->connectButton, &QPushButton::clicked, this, &MainWindow::openSerialPort);
    connect(ui->bandComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &ChorusDeviceForm::bandComboIndexChanged);
    ui->bandComboBox->setCurrentIndex(0);
    bandComboIndexChanged(ui->bandComboBox->currentIndex());
}

void ChorusDeviceForm::bandComboIndexChanged(int index) {
    qDebug() << "bandComboIndexChanged" << index;
    if( 0 <= index && index <= 7){
        ui->channelComboBox->clear();
        for(int i=0; i<8; i++){
            int ch = ChorusDeviceForm::channelTable[index][i];
            ui->channelComboBox->addItem(QString("%1 (%2 Mhz)").arg(i+1).arg(ch));
        }
    }
}

ChorusDeviceForm::~ChorusDeviceForm()
{
    delete ui;
}
