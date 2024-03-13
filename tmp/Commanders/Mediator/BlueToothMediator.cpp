#include"BlueToothMediator.h"
#include"Kernel.h"
CBlueToothMediator::CBlueToothMediator(CKernel* ker){
    m_pKernel=ker;
    m_pBlueTooth=new CBlueTooth(this);
}
CBlueToothMediator::~CBlueToothMediator(){

}
void CBlueToothMediator::Init(){



}
void CBlueToothMediator::Uninit(){}
void CBlueToothMediator::Open(){}
void CBlueToothMediator::Close(){}
//void CBlueToothMediator::Send(){}
void CBlueToothMediator::DevDiscovered(QString name,QString addr,QBluetoothUuid uid){

    emit sig_DevDiscovered(name,addr,uid);

}

bool CBlueToothMediator::BlueToothConnect(QString addr,QBluetoothUuid uid){

    if(m_pBlueTooth->BlueToothConnect(addr,uid)){

       return true;

    }


    return false;
}

void CBlueToothMediator::Deal(char* data,int len,unsigned from){


}
bool CBlueToothMediator::Send(char* data,int len,unsigned to){


}
bool CBlueToothMediator::isConnected(QString addr){



    return m_pBlueTooth->isConnected(addr);
}

