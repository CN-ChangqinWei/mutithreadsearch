#pragma once
#include<QObject>
#include <QtSerialPort/QSerialPort>         // 提供访问串口的功能
#include <QtSerialPort/QSerialPortInfo>
#include"config.h"
class CSerialMediator;
class CSerialer:public QObject{
  Q_OBJECT
public:
    CSerialer(CSerialMediator* sermediator);
    ~CSerialer();
    void Init();
    bool Config(QString PortName,int BaudRate=_DEF_FAULTBAUD,int Parity=_DEF_FAULTPARITY,int DataBits=_DEF_FUALTDATABITS,int StopBit=_DEF_FUALTSTOPBIT,int FlowCtrl=_DEF_FUALTFLOWCRTL);
    bool Send(QString data);
    void Recv();
    QStringList Refresh();
 public slots:

    void Test();
private:
   QSerialPort* m_pSerial;
   CSerialMediator* m_pMediator;
   bool m_fSerialExist;
};
