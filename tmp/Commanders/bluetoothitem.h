#ifndef BLUETOOTHITEM_H
#define BLUETOOTHITEM_H

#include <QWidget>
#include"BlueTooth/BlueTooth.h"
class CKernel;
namespace Ui {
class BlueToothItem;
}

class BlueToothItem : public QWidget
{
    Q_OBJECT

public:
    explicit BlueToothItem(QBluetoothDeviceInfo info,CKernel* ker,bool isConnect,QWidget *parent = 0);
    ~BlueToothItem();
    void ChangePBText(QString text);
    void ChangePBStat(bool stat);
    bool isBLTinfo(QBluetoothDeviceInfo info);

    QBluetoothDeviceInfo m_info;

signals:
    void sig_BlueToothConnect(QBluetoothDeviceInfo);
    void sig_BlueToothDisconnnet();
private slots:
    void on_PB_CONNECT_clicked();

private:
    Ui::BlueToothItem *ui;
    CKernel* m_pKer;


};

#endif // BLUETOOTHITEM_H
