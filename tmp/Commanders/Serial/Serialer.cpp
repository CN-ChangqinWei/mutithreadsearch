#include"Serialer.h"
#include"Mediator/SerialMediator.h"
CSerialer::CSerialer(CSerialMediator* sermediator){

    m_pMediator=sermediator;
    m_fSerialExist=false;
}
CSerialer::~CSerialer(){}
void CSerialer::Init(){

    m_pSerial=new QSerialPort;


}
bool CSerialer::Config(QString PortName,int BaudRate,int Parity,int DataBits,int StopBit,int FlowCtrl){
    qDebug()<<__func__<<endl;
    //m_pSerial->close();



    m_pSerial->setBaudRate(BaudRate);
    m_pSerial->setPortName(PortName);
    switch(Parity){
    case 0: m_pSerial->setParity(QSerialPort::NoParity ) ;break;
    case 1: m_pSerial->setParity(QSerialPort::EvenParity) ;break;
    case 2: m_pSerial->setParity(QSerialPort::OddParity  );break;
    default: break;
    }

    switch(DataBits){


    case 5:m_pSerial->setDataBits(QSerialPort::Data5);break;
    case 6:m_pSerial->setDataBits(QSerialPort::Data6);break;
    case 7:m_pSerial->setDataBits(QSerialPort::Data7);break;
    case 8:m_pSerial->setDataBits(QSerialPort::Data8);break;
    default: break;
    }

    switch (StopBit) {
    case 0:m_pSerial->setStopBits(QSerialPort::OneStop);break;
    case 1:m_pSerial->setStopBits(QSerialPort::TwoStop);break;
    case 2:m_pSerial->setStopBits(QSerialPort::OneAndHalfStop);break;
    default:
        break;
    }

    switch(FlowCtrl){
    case 0:m_pSerial->setFlowControl(QSerialPort::NoFlowControl );break;
    case 1:m_pSerial->setFlowControl(QSerialPort::HardwareControl);break;
    case 2:m_pSerial->setFlowControl(QSerialPort::SoftwareControl);break;
    default: break;
    }
    if(m_pSerial->open(QSerialPort::ReadWrite)){

         m_fSerialExist=false;
         return true;

    }
    return false;
}
bool CSerialer::Send(QString data){
    qDebug()<<__func__<<endl;
    if(m_fSerialExist)
    m_pSerial->write(data.toStdString().c_str());
    return false;
}
void CSerialer::Recv(){}

QStringList CSerialer::Refresh(){
    qDebug()<<__func__<<endl;
    QStringList PortList;
    foreach(const QSerialPortInfo &info,QSerialPortInfo::availablePorts()) //添加新串口
            {
                PortList.append(info.portName());
            }

    return PortList;
}



void CSerialer::Test(){
    qDebug()<<__func__<<endl;
    QStringList PortList;
    PortList=Refresh();
    if(PortList.isEmpty()){
        qDebug()<<"No available COMS"<<endl;
        return;


    }
    Config(PortList.front());
    QString Testtext="Testing\n";
    m_pSerial->write(Testtext.toStdString().c_str());
    return;
}


