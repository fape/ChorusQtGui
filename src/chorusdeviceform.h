#ifndef CHORUSDEVICEFORM_H
#define CHORUSDEVICEFORM_H

#include <QWidget>

namespace Ui {
class ChorusDeviceForm;
}

class ChorusDeviceForm : public QWidget
{
    Q_OBJECT

public:
    explicit ChorusDeviceForm(QWidget *parent = 0);
    ~ChorusDeviceForm();

private slots:
    void bandComboIndexChanged(int id);


private:
    Ui::ChorusDeviceForm *ui;

    static int const channelTable[8][8];
};

#endif // CHORUSDEVICEFORM_H
