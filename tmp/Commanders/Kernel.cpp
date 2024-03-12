#include"Kernel.h"

CKernel::CKernel(){
    Init();

}

CKernel::~CKernel(){


}

void CKernel::Init(){
    qDebug()<<__func__<<endl;

    m_pMainWindow= new MainWindow(this);
    m_pMainWindow->init();
    //m_pSerialMediator=new CSerialMediator(this);
    m_pMainWindow->show();
    m_pBLT=new CBlueTooth(this);
    //RefreshCOM();
    //connect(m_pMainWindow,&MainWindow::sig_SendText,m_pSerialMediator,&CSerialMediator::slot_SendText);
    //connect(m_pMainWindow,&MainWindow::sig_ConnectCOM,m_pSerialMediator,&CSerialMediator::slot_ConnectCOM);
}

void CKernel::BLTConnecting(QBluetoothDeviceInfo info){

    m_pMainWindow->BLTConnecting(info);

}
void CKernel::BLTConnected(QBluetoothDeviceInfo info){

    m_pMainWindow->BLTConnected(info);

}
void CKernel::BLTConnectedError(){

    m_pMainWindow->BLTConnectedError();

}

void CKernel::slot_BlueToothConnect(QBluetoothDeviceInfo info){


    m_pBLT->BlueToothConnect(info);



}

void CKernel::DevDiscovered(QBluetoothDeviceInfo info){

    m_pMainWindow->BlueToothDevDiscovered(info);

}

void CKernel::Uninit(){



}

void CKernel::slot_BlueToothDisConnect(){

    m_pBLT->BlueToothDisConnect();
    m_pMainWindow->BlueToothDisConnect();
    m_pMainWindow->m_isConnect=false;

}

void CKernel::Deal(char* data,int len,unsigned from){



}

bool CKernel::isConnected(QBluetoothDeviceInfo info){

    return m_pBLT->isConnected(info);
    //return false;
}

void CKernel::RefreshCOM()
{
    qDebug()<<__func__<<endl;
    //m_pMainWindow->RefreshCOM(m_pSerialMediator->RefreshCOM());

}

void CKernel::slot_FinishSearch(){

    m_pMainWindow->FinishSearch();

}
void CKernel::StartSearch(){

    m_pBLT->StartSearch();

}
void CKernel::BLTSend(QString text){

    m_pBLT->BLTSend(text);

}

void CKernel::MsgBox(QString title,QString content){

    QMessageBox::about(m_pMainWindow,title,content);


}


