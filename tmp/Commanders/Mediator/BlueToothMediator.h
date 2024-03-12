#pragma once
#include<QObject>
#include"Mediator.h"
#include"BlueTooth/BlueTooth.h"
class CKernel;
class CBlueToothMediator:public CMediator{


public:
    CBlueToothMediator(CKernel* ker);
    ~CBlueToothMediator();
    void Init();
    void Uninit();
    void Open();
    void Close();
    //void Send();
    void Deal(char* data,int len,unsigned from);
    bool Send(char* data,int len,unsigned to);
    void DevDiscovered(QString name,QString addr,QBluetoothUuid uid);
    bool isConnected(QString addr);
    bool BlueToothConnect(QString addr,QBluetoothUuid uid);
signals:

private:
    CBlueTooth* m_pBlueTooth;
    CKernel* m_pKernel;
};
