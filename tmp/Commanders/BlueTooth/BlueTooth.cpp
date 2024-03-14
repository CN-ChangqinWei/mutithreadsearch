#include"BlueTooth.h"
#include"Kernel.h"
CBlueTooth::CBlueTooth(CKernel* ker){
    m_pKer=ker;
    //m_pAimDev=nullptr;
    //m_pSock=new QBluetoothSocket;
    Init();
}
CBlueTooth::~CBlueTooth(){

}
void CBlueTooth::Init(){

    m_pDiscoveryAgent=new QBluetoothDeviceDiscoveryAgent();
    m_pLocalDev=new QBluetoothLocalDevice();
    m_isConnect=false;
    //m_pDiscoveryAgent->start();
    m_pLocalDev->powerOn();
    connect(m_pDiscoveryAgent,&QBluetoothDeviceDiscoveryAgent::finished,m_pKer,&CKernel::slot_FinishSearch);
    connect(m_pDiscoveryAgent,&QBluetoothDeviceDiscoveryAgent::deviceDiscovered,this,&CBlueTooth::slot_DevDiscovered);


    //m_pKer->DevDiscovered(QString("1"),QString("2"));
}
void CBlueTooth::Uninit(){

}
bool CBlueTooth::Open(){

return false;
}
bool CBlueTooth::BlueToothConnect(QBluetoothDeviceInfo info){

    m_pSock=new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);
    //m_pSock->close();
    QBluetoothUuid uuid(QString("00001101-0000-1000-8000-00805F9B34FB"));
    m_pSock->connectToService(info.address(),uuid);

   // m_pSock->open();

    connect(m_pSock,&QBluetoothSocket::connected,this,&CBlueTooth::ConnectDev);

    m_pAimDev=info;

    //connect(m_pSock,&QBluetoothSocket::error,this,&CBlueTooth::slot_DevConnectError);

    //SendData(QString("test\n"));

    m_pKer->BLTConnecting(info);

    return false;

}

void CBlueTooth::SendData(QString data){

    QByteArray datas=QByteArray(data.toStdString().c_str());
    m_pSock->write(datas,datas.length());


}

void CBlueTooth::ConnectDev(){



    //disconnect(m_pSock,&QBluetoothSocket::connected,this,&CBlueTooth::ConnectDev);
    m_isConnect=true;
    connect(m_pSock,&QBluetoothSocket::readyRead,this,&CBlueTooth::slot_BLTRecv);
    m_pKer->BLTConnected(m_pAimDev);

}



void CBlueTooth::slot_DevDiscovered(const QBluetoothDeviceInfo info){


    m_pKer->DevDiscovered(info);
    //m_pKer->BLTConnecting(info);

}

void CBlueTooth::slot_DevConnected(){
    m_pSock->write("test\n");

    m_pKer->BLTConnected(m_pAimDev);

}

void CBlueTooth::slot_DevConnectError(QBluetoothSocket::SocketError error){


    m_pKer->BLTConnectedError();
    //m_pAimDev=nullptr;

}


void CBlueTooth::Close(){


}
bool CBlueTooth::isConnected(QBluetoothDeviceInfo info){

    //QBluetoothAddress Address=QBluetoothAddress(info.address());
    QBluetoothLocalDevice::Pairing pairingStatus=m_pLocalDev->pairingStatus(info.address());
    if(pairingStatus == QBluetoothLocalDevice::Paired || pairingStatus == QBluetoothLocalDevice::AuthorizedPaired ){
        return false;
    }return true;
}

void CBlueTooth::BlueToothDisConnect(){

    //m_pSock->close();
    m_isConnect=false;
    delete m_pSock;

}

void CBlueTooth::FinishSearch(){



}
void CBlueTooth::StartSearch(){

    m_pDiscoveryAgent->start();


}
void CBlueTooth::BLTSend(QString text){



    if(m_isConnect){
        if(m_pSock->isOpen()&&m_pSock->isWritable())
        m_pSock->write(text.toStdString().c_str());
        else{
            m_pKer->MsgBox("消息","Socket未打开");

        }

    }




}

void CBlueTooth::slot_BLTRecv(){

    BLTRecv();

}

void CBlueTooth::BLTRecv(){
    QByteArray data=m_pSock->readAll();
    //m_pKer->BLTRecv(data);
}

void CBlueTooth::BLTSend(char* data,int length){

    if(m_isConnect){
        char* buf=new char[length];
        for(int i=3;i>=0;i--){

            buf[3-i]=data[i];

        }
        for(int i=3;i>=0;i--){


            buf[4+i]=data[4+i];

        }
        if(m_pSock->isOpen()&&m_pSock->isWritable())
         m_pSock->write(buf,length);
        else{
            m_pKer->MsgBox("消息","Socket未打开");

        }
        delete[] buf;
    }
    //m_pSock->write(data,length);

}


bool CBlueTooth::m_isConnect;

