#include"SerialMediator.h"
#include"Kernel.h"


CSerialMediator::CSerialMediator(CKernel* ker){

    m_pKernel=ker;
    m_pSerial=new CSerialer(this);
}
CSerialMediator::~CSerialMediator(){



}

void CSerialMediator::Init(){

}
void CSerialMediator::Uninit(){

}
void CSerialMediator::Deal(char* data,int len,unsigned from){

}
bool CSerialMediator::Send(char* data,int len,unsigned to){

    return false;
}
QStringList CSerialMediator::RefreshCOM()
{
    return m_pSerial->Refresh();

}

void CSerialMediator::slot_ConnectCOM(QString PortName,int BaudRate,int Parity,int DataBits,int StopBit,int FlowCtrl){

    qDebug()<<__func__<<endl;
    m_pSerial->Config(PortName,BaudRate,Parity,DataBits,StopBit,FlowCtrl);

}

void CSerialMediator::slot_SendText(QString text){

    m_pSerial->Send(text);

}


