#pragma once
#include<QObject>
#include<QtBluetooth/QBluetoothDeviceDiscoveryAgent>
#include<QtBluetooth/QBluetoothDeviceInfo>
#include<QtBluetooth/QBluetoothLocalDevice>
#include<QtBluetooth/QBluetoothSocket>
#include<QtBluetooth/QBluetoothAddress>
#include<map>
using namespace std;
class CKernel;
class CBlueTooth:public QObject{

    Q_OBJECT

public:
    CBlueTooth(CKernel* ker);
    ~CBlueTooth();
    void Init();
    void Uninit();
    bool Open();
    void ConnectDev();
    void Close();
    bool BlueToothConnect(QBluetoothDeviceInfo info);
    void BlueToothDisConnect();
    bool isConnected(QBluetoothDeviceInfo info);
    void FinishSearch();
    void StartSearch();
    void SendData(QString data);
    void BLTSend(QString text);
    static bool m_isConnect;
public slots:
    void slot_DevDiscovered(QBluetoothDeviceInfo info);
    void slot_DevConnected();
    void slot_DevConnectError(QBluetoothSocket::SocketError error);
signals:

private:
    QBluetoothDeviceDiscoveryAgent* m_pDiscoveryAgent;
    QBluetoothLocalDevice* m_pLocalDev;
    QBluetoothDeviceInfo m_pAimDev;
    CKernel* m_pKer;
    QBluetoothSocket* m_pSock;
    //bool m_fConnectWait;
};
