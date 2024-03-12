#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<string>
#include"Kernel.h"
using namespace std;
MainWindow::MainWindow(CKernel* ker,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_pKer=ker;


}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::init(){
    m_isConnect=false;
    QStringList BotList={"115200","57600","38400","19200","9600","4800","2400"};
    ui->CB_BOTERATE->addItems(BotList);
    QStringList EnsureList={"无","奇校验","偶校验"};
    ui->CB_ENSUREBIT->addItems(EnsureList);
    QStringList StopBitsList={"1","2","1.5"};
    ui->CB_STOPBIT->addItems(StopBitsList);
    QStringList FlowList={"无","软","硬"};
    ui->CB_FLOWCTRL->addItems(FlowList);
    QStringList DataBits={"5","6","7","8"};
    ui->CB_DATABITS->addItems(DataBits);
    QStringList BLTSendMode={"文本","Hex"};
    ui->CB_BLTTEXTMODE_SEND->addItems(BLTSendMode);
    ui->CB_BLTTEXTMODE_RECV->addItems(BLTSendMode);
    QStringList BLTAppend={"无追加","\\n","\\r","\\n\\r","\\r\\n"};
    ui->CB_BLTAPPEND->addItems(BLTAppend);
    m_SendMode=ui->CB_BLTTEXTMODE_SEND->currentText();
    m_RecvMode=ui->CB_BLTTEXTMODE_RECV->currentText();
    m_AppendMode=ui->CB_BLTAPPEND->currentText();
    m_pBlueToothLayout=new QVBoxLayout;

    m_pBlueToothLayout->setContentsMargins(0,0,0,0);

    m_pBlueToothLayout->setSpacing(3);

    ui->WG_BLUEDEV_2->setLayout(m_pBlueToothLayout);

    m_pBlueToothLayoutPair=new QVBoxLayout;

    m_pBlueToothLayoutPair->setContentsMargins(0,0,0,0);

    m_pBlueToothLayoutPair->setSpacing(3);

    ui->WG_BLUEDEV->setLayout(m_pBlueToothLayoutPair);

    //m_pBlueToothLayout->addWidget(new BlueToothItem(QString("1"),QString("1")));
}

void MainWindow::RefreshCOM(QStringList PortList){

    ui->CB_COM->clear();
    ui->CB_COM->addItems(PortList);

}

//void MainWindow::slot_RefreshSerial(QStringList* PortList){

//    ui->CB_COM->clear();
//    ui->CB_COM->addItems(*PortList);

//}


void MainWindow::on_PB_SENDTEXT_COM_clicked()
{
    emit sig_SendText(ui->TE_SENDTEXT_COM->toPlainText());
}

void MainWindow::on_PB_CONNECT_COM_clicked()
{
    QString PortName=ui->CB_COM->currentText();
    QString BaudRate=ui->CB_BOTERATE->currentText();
    QString Parity=ui->CB_ENSUREBIT->currentText();
    QString DataBits=ui->CB_DATABITS->currentText();
    QString StopBit=ui->CB_STOPBIT->currentText();
    QString FlowCtrl=ui->CB_FLOWCTRL->currentText();
    int Baud=atoi(BaudRate.toStdString().c_str());
    int Par;
    if(Parity.compare("无")==0){
        Par=0;
    }else if(Parity.compare("奇校验")==0){

        Par=1;
    }else{
        Par=2;
    }

    int Data=atoi(DataBits.toStdString().c_str());

    int Stop=0;
    if(StopBit.compare("1")==0){
        Stop=0;
    }else if(StopBit.compare("2")==0){
        Stop=1;
    }else{
        Stop=2;
    }

    int Flow=0;

    if(FlowCtrl.compare("无")==0){

        Flow=0;

    }else if(FlowCtrl.compare("软")==0){
        Flow=1;

    }else{
        Flow=2;

    }


    emit sig_ConnectCOM(PortName,Baud,Par,Data,Stop,Flow);

}


void MainWindow::BlueToothDevDiscovered(QBluetoothDeviceInfo info){

   // QString msg=QString("%1\n%2").arg(name).arg(address);
    //BlueToothItem item(name,address);
    BlueToothItem* item=new BlueToothItem(info,m_pKer,m_isConnect);
    if(m_pKer->isConnected(info)){
        m_pBlueToothLayoutPair->addWidget(item);
        m_lstBLTitemsPair.push_back(item);
    }
    else{

        //m_pBlueToothLayout.push_back(item);
        m_pBlueToothLayout->addWidget(item);
        m_lstBLTitems.push_back(item);
    }



    //ui->TB_DEV_BLUE->append(msg);
    //ui->LB_STAT_BLUE->setText("发现");
}

void MainWindow::BLTConnecting(QBluetoothDeviceInfo info){

    for(auto v:m_lstBLTitems){

        if(v->m_info.address().toString().compare(info.address().toString())==0){

            v->ChangePBText("连接中");
            //v->ChangePBStat(false);

        }
        v->ChangePBStat(false);
    }

}
void MainWindow::BLTConnected(QBluetoothDeviceInfo info){
    QMessageBox::about(this,"消息","连接成功");
    m_isConnect=true;
    for(auto v:m_lstBLTitems){

        if(v->m_info.address().toString().compare(info.address().toString())==0){
            v->ChangePBText("断开");
            //v->ChangePBStat(false);
            v->ChangePBStat(true);
        }else
        v->ChangePBStat(false);
    }
    for(auto v:m_lstBLTitemsPair){

        if(v->m_info.address().toString().compare(info.address().toString())==0){
            v->ChangePBText("断开");
            //v->ChangePBStat(false);
            v->ChangePBStat(true);
        }else
        v->ChangePBStat(false);
    }
    ui->LB_CONNECTSTAT->setText(QString("已连接:%1").arg(info.name()));
}
void MainWindow::BLTConnectedError(){

    for(auto v:m_lstBLTitems){


            v->ChangePBText("连接");
            //v->ChangePBStat(false);

        v->ChangePBStat(true);
    }
    QMessageBox::about(this,"消息","连接出现错误!");
}

void MainWindow::BlueToothDisConnect(){

    for(auto v:m_lstBLTitems){


            v->ChangePBText("连接");
            //v->ChangePBStat(false);

        v->ChangePBStat(true);
    }
    for(auto v:m_lstBLTitemsPair){


            v->ChangePBText("连接");
            //v->ChangePBStat(false);

        v->ChangePBStat(true);
    }
    ui->LB_CONNECTSTAT->setText("已连接:无");

}

void MainWindow::FinishSearch(){

    ui->PB_SEARCHBLT->setEnabled(true);
    ui->PB_SEARCHBLT->setText("搜索设备");

}
void MainWindow::StartSearch(){


}


void MainWindow::on_PB_SEARCHBLT_clicked()
{
   for(auto v:m_lstBLTitems) delete v;
   for(auto v:m_lstBLTitemsPair) delete v;
   m_lstBLTitems.clear();
   m_lstBLTitemsPair.clear();
    ui->PB_SEARCHBLT->setEnabled(false);
    ui->PB_SEARCHBLT->setText("搜索中");
    m_pKer->StartSearch();
}

void MainWindow::on_PB_BLTBREAK_clicked()
{
    m_pKer->slot_BlueToothDisConnect();
}

void MainWindow::on_PB_BLTSEND_clicked()
{
    QString text=ui->LE_BLTSEND->text();
    if(m_AppendMode.compare("无追加")==0);
    else if(m_AppendMode.compare("\\n")==0) text=QString("%1\n").arg(text);
    else if(m_AppendMode.compare("\\r")==0) text=QString("%1\r").arg(text);
    else if(m_AppendMode.compare("\\n\\r")==0) text=QString("%1\n\r").arg(text);
    else if(m_AppendMode.compare("\\r\\n")==0) text=QString("%1\r\n").arg(text);

    m_pKer->BLTSend(ui->LE_BLTSEND->text());

}

void MainWindow::on_CB_BLTTEXTMODE_RECV_currentTextChanged(const QString &arg1)
{
    m_RecvMode=arg1;
}

void MainWindow::on_CB_BLTTEXTMODE_SEND_currentTextChanged(const QString &arg1)
{
    m_SendMode=arg1;
}

void MainWindow::on_CB_BLTAPPEND_currentTextChanged(const QString &arg1)
{
    m_AppendMode=arg1;
}
