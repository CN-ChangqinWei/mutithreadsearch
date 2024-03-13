#include "bluetoothitem.h"
#include "ui_bluetoothitem.h"
#include"Kernel.h"
#include"BlueTooth/BlueTooth.h"

BlueToothItem::BlueToothItem(QBluetoothDeviceInfo info,CKernel* ker,bool isConnect,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BlueToothItem)
{
    ui->setupUi(this);
    if(isConnect){
        ui->PB_CONNECT->setEnabled(false);

    }
    QString name=QString(info.name().toStdString().c_str());
    ui->LB_NAME->setText(name);
    QString addr=QString(info.address().toString());
    ui->LB_ADDR->setText(addr);

    m_pKer=ker;
    //ker->m_AddrToBItem[addr]=this;
    m_info=info;
    connect(this,&BlueToothItem::sig_BlueToothConnect,m_pKer,&CKernel::slot_BlueToothConnect);

    connect(this,&BlueToothItem::sig_BlueToothDisconnnet,m_pKer,&CKernel::slot_BlueToothDisConnect);




}




BlueToothItem::~BlueToothItem()
{
    delete ui;
}

void BlueToothItem::on_PB_CONNECT_clicked()
{

    //QBluetoothSocket sock;
    //m_pKer->AddBlueToothSocket(BlueToothID++,sock);
    //m_pKer->ConnectBlueTooth();
    if(ui->PB_CONNECT->text().compare("连接")==0)
    emit sig_BlueToothConnect(m_info);
    else emit sig_BlueToothDisconnnet();
    //m_pKer->slot_BlueToothConnect(m_info);




}

void BlueToothItem::ChangePBText(QString text){

    ui->PB_CONNECT->setText(text);

}
void BlueToothItem::ChangePBStat(bool stat){

    ui->PB_CONNECT->setEnabled(stat);

}
bool BlueToothItem::isBLTinfo(QBluetoothDeviceInfo info){


}



