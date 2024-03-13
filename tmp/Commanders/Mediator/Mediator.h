#pragma once
#include<QObject>
#include<QBluetoothDeviceInfo>
class CMediator:public QObject{
Q_OBJECT
  public:
    CMediator(){}
    virtual ~CMediator(){}
    virtual void Init()=0;
    virtual void Uninit()=0;
    virtual void Deal(char* data,int len,unsigned from)=0;
    virtual bool Send(char* data,int len,unsigned to)=0;
signals:
    void sig_DevDiscovered(QString,QString,QBluetoothUuid);
};
