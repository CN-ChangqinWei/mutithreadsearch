#pragma once
#include"mainwindow.h"
#include<QObject>
#include"bluetoothitem.h"
#include"QMessageBox"
#include"BlueTooth/BlueTooth.h"
#include"config.h"
class CKernel:public QObject{
    Q_OBJECT

public:

    CKernel();
    ~CKernel();
    void Init();
    void Uninit();
    void MsgBox(QString title,QString content);
    //NET
    void Deal(char* data,int len,unsigned from);
    //SERIAL
    void RefreshCOM();
    //BLT
    void BLTConnecting(QBluetoothDeviceInfo info);
    void BLTConnected(QBluetoothDeviceInfo info);
    bool isConnected(QBluetoothDeviceInfo info);
    void DevDiscovered(QBluetoothDeviceInfo info);
    void BLTRecv(QByteArray content);
    void StartSearch();
    void BLTSend(QString text);
        //VMOTOR
    void SendCommand(VMotorMsg command);


public slots:
    void slot_BlueToothConnect(QBluetoothDeviceInfo info);

void slot_BlueToothDisConnect();

    void BLTConnectedError();
    void slot_FinishSearch();
signals:


private:
    MainWindow* m_pMainWindow;
    CBlueTooth* m_pBLT;
    QBluetoothDeviceInfo m_Info;
    //map<QString,BlueToothItem*> m_AddrToBItem;
    bool m_isConnectBlueTooth;
};

