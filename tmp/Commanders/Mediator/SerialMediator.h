#pragma once
#include"Mediator.h"
#include"Serial/Serialer.h"
class CKernel;
class CSerialMediator:public CMediator{

public:
    CSerialMediator(CKernel* ker);
    ~CSerialMediator();
    void Init();
    void Uninit();
    void Deal(char* data,int len,unsigned from);
    bool Send(char* data,int len,unsigned to);
    QStringList RefreshCOM();
public slots:
    void slot_SendText(QString text);
    void slot_ConnectCOM(QString PortName,int BaudRate,int Parity,int DataBits,int StopBit,int FlowCtrl);
private:
    CSerialer* m_pSerial;
    CKernel* m_pKernel;

};

