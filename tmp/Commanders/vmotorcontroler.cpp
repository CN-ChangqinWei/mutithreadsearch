#include "vmotorcontroler.h"
#include "ui_vmotorcontroler.h"
#include "Kernel.h"
#define _FUNC_SDCHV(varry,type) \
    float value=((float)position/100)*m_MaxValue[type][m_Mode]*m_Pole[type][m_Mode];\
    varry[m_Mode]=(float)_FUNC_LIMIT(-m_MaxValue[type][m_Mode],m_MaxValue[type][m_Mode],value);\
    LineEditRefresh();\
    VMotorMsg command=VMotorMsg(m_TypeHead[type][m_Mode],varry[m_Mode]);\
            m_pKer->SendCommand(command);

#define _FUNC_LECHV(varry,pole,type) \
float value=arg1.toFloat();\
if(value*m_Pole[type][m_Mode]<0){\
    ChangePole(pole,type);\
}\
varry[m_Mode]=_FUNC_LIMIT(-m_MaxValue[type][m_Mode],m_MaxValue[type][m_Mode],value);\
LineEditRefresh();




VMotorControler::VMotorControler(MainWindow* mwin,CKernel* ker,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VMotorControler)
{
    ui->setupUi(this);
    m_pMain=mwin;
    m_Mode=_DEF_SPEEDRING;
    m_pKer=ker;
    ui->PB_SPEEDRING->setEnabled(false);
    memset(m_KpValue,0,sizeof(m_KpValue));
    memset(m_KiValue,0,sizeof(m_KiValue));
    memset(m_KdValue,0,sizeof(m_KdValue));
    memset(m_TargetValue,0,sizeof(m_TargetValue));
    memset(m_MaxValue,0,sizeof(m_MaxValue));



    for(int i=0;i<4;i++) for(int j=0;j<4;j++) m_Pole[i][j]=1;


    m_MaxValue[_DEF_KP][_DEF_SPEEDRING]=_DEF_MAX_SPEEDKP;
    m_MaxValue[_DEF_KI][_DEF_SPEEDRING]=_DEF_MAX_SPEEDKI;
    m_MaxValue[_DEF_KD][_DEF_SPEEDRING]=_DEF_MAX_SPEEDKD;
    m_MaxValue[_DEF_TARGET][_DEF_SPEEDRING]=_DEF_MAX_SPEEDTARGET;

    m_MaxValue[_DEF_KP][_DEF_ANGLERING]=_DEF_MAX_ANGLEKP;
    m_MaxValue[_DEF_KI][_DEF_ANGLERING]=_DEF_MAX_ANGLEKI;
    m_MaxValue[_DEF_KD][_DEF_ANGLERING]=_DEF_MAX_ANGLEKD;
    m_MaxValue[_DEF_TARGET][_DEF_ANGLERING]=_DEF_MAX_ANGLETARGET;

    m_MaxValue[_DEF_KP][_DEF_GYRORING]=_DEF_MAX_GYROKP;
    m_MaxValue[_DEF_KI][_DEF_GYRORING]=_DEF_MAX_GYROKI;
    m_MaxValue[_DEF_KD][_DEF_GYRORING]=_DEF_MAX_GYROKD;
    m_MaxValue[_DEF_TARGET][_DEF_GYRORING]=_DEF_MAX_GYROTARGET;

    m_MaxValue[_DEF_KP][_DEF_SERVORING]=_DEF_MAX_SERVOKP;
    m_MaxValue[_DEF_KI][_DEF_SERVORING]=_DEF_MAX_SERVOKI;
    m_MaxValue[_DEF_KD][_DEF_SERVORING]=_DEF_MAX_SERVOKD;
    m_MaxValue[_DEF_TARGET][_DEF_SERVORING]=_DEF_MAX_SERVOTARGET;

    //-----------

    m_KpValue[_DEF_SPEEDRING]=_DEF_DEFUALT_SPEEDKP;
    m_KiValue[_DEF_SPEEDRING]=_DEF_DEFUALT_SPEEDKI;
    m_KdValue[_DEF_SPEEDRING]=_DEF_DEFUALT_SPEEDKD;
    m_TargetValue[_DEF_SPEEDRING]=_DEF_DEFUALT_SPEEDTARGET;

    m_KpValue[_DEF_ANGLERING]=_DEF_DEFUALT_ANGLEKP;
    m_KiValue[_DEF_ANGLERING]=_DEF_DEFUALT_ANGLEKI;
    m_KdValue[_DEF_ANGLERING]=_DEF_DEFUALT_ANGLEKD;
    m_TargetValue[_DEF_ANGLERING]=_DEF_DEFUALT_ANGLETARGET;

    m_KpValue[_DEF_GYRORING]=_DEF_DEFUALT_GYROKP;
    m_KiValue[_DEF_GYRORING]=_DEF_DEFUALT_GYROKI;
    m_KdValue[_DEF_GYRORING]=_DEF_DEFUALT_GYROKD;
    m_TargetValue[_DEF_GYRORING]=_DEF_DEFUALT_GYROTARGET;

    m_KpValue[_DEF_SERVORING]=_DEF_DEFUALT_SERVOKP;
    m_KiValue[_DEF_SERVORING]=_DEF_DEFUALT_SERVOKI;
    m_KdValue[_DEF_SERVORING]=_DEF_DEFUALT_SERVOKD;
    m_TargetValue[_DEF_SERVORING]=_DEF_DEFUALT_SERVOTARGET;


    m_TypeHead[_DEF_KP][_DEF_SPEEDRING]=_DEF_CMD_SPEEDKP;
    m_TypeHead[_DEF_KI][_DEF_SPEEDRING]=_DEF_CMD_SPEEDKI;
    m_TypeHead[_DEF_KD][_DEF_SPEEDRING]=_DEF_CMD_SPEEDKD;
    m_TypeHead[_DEF_TARGET][_DEF_SPEEDRING]=_DEF_CMD_SPEEDTARGET;

    m_TypeHead[_DEF_KP][_DEF_ANGLERING]=_DEF_CMD_ANGLEKP;
    m_TypeHead[_DEF_KI][_DEF_ANGLERING]=_DEF_CMD_ANGLEKI;
    m_TypeHead[_DEF_KD][_DEF_ANGLERING]=_DEF_CMD_ANGLEKD;
    m_TypeHead[_DEF_TARGET][_DEF_ANGLERING]=_DEF_CMD_ANGLETARGET;

    m_TypeHead[_DEF_KP][_DEF_GYRORING]=_DEF_CMD_GYROKP;
    m_TypeHead[_DEF_KI][_DEF_GYRORING]=_DEF_CMD_GYROKI;
    m_TypeHead[_DEF_KD][_DEF_GYRORING]=_DEF_CMD_GYROKD;
    m_TypeHead[_DEF_TARGET][_DEF_GYRORING]=_DEF_CMD_GYROTARGET;

    m_TypeHead[_DEF_KP][_DEF_SERVORING]=_DEF_CMD_SERVOKP;
    m_TypeHead[_DEF_KI][_DEF_SERVORING]=_DEF_CMD_SERVOKI;
    m_TypeHead[_DEF_KD][_DEF_SERVORING]=_DEF_CMD_SERVOKD;
    m_TypeHead[_DEF_TARGET][_DEF_SERVORING]=_DEF_CMD_SERVOTARGET;
    ValueRefresh();
}

VMotorControler::~VMotorControler()
{
    delete ui;
}

void VMotorControler::Step_Init(){




}

void VMotorControler::on_pushButton_11_clicked()
{
   hide();
}

void VMotorControler::SliderRefresh(){


    int Pos_Kp=100*(m_KpValue[m_Mode]/(float)m_MaxValue[_DEF_KP][m_Mode]);
    int Pos_Ki=100*(m_KiValue[m_Mode]/(float)m_MaxValue[_DEF_KI][m_Mode]);
    int Pos_Kd=100*(m_KdValue[m_Mode]/(float)m_MaxValue[_DEF_KD][m_Mode]);
    int Pos_Target=100*(m_TargetValue[m_Mode]/(float)m_MaxValue[_DEF_TARGET][m_Mode]);
    ui->SD_KP->setValue(_FUNC_ABS(Pos_Kp));
    ui->SD_KI->setValue(_FUNC_ABS(Pos_Ki));
    ui->SD_KD->setValue(_FUNC_ABS(Pos_Kd));
    ui->SD_TARGET->setValue(_FUNC_ABS(Pos_Target));

}
void VMotorControler::LineEditRefresh(){

    QString Str_Kp=QString("%1").arg(m_KpValue[m_Mode]);
    QString Str_Ki=QString("%1").arg(m_KiValue[m_Mode]);
    QString Str_Kd=QString("%1").arg(m_KdValue[m_Mode]);
    QString Str_Target=QString("%1").arg(m_TargetValue[m_Mode]);
    ui->LE_KP->setText(Str_Kp);
    ui->LE_KI->setText(Str_Ki);
    ui->LE_KD->setText(Str_Kd);
    ui->LE_TARGET->setText(Str_Target);

}
void VMotorControler::PoleRefresh(){

   m_Pole[_DEF_KP][m_Mode]=_FUNC_POLE(m_KpValue[m_Mode]);
    m_Pole[_DEF_KI][m_Mode]=_FUNC_POLE(m_KiValue[m_Mode]);
    m_Pole[_DEF_KD][m_Mode]=_FUNC_POLE(m_KdValue[m_Mode]);
    m_Pole[_DEF_TARGET][m_Mode]=_FUNC_POLE(m_TargetValue[m_Mode]);
    if(m_Pole[_DEF_KP][m_Mode]==1) ui->PB_POLEKP->setText("正");else ui->PB_POLEKP->setText("负");
    if(m_Pole[_DEF_KI][m_Mode]==1) ui->PB_POLEKI->setText("正");else ui->PB_POLEKI->setText("负");
    if(m_Pole[_DEF_KD][m_Mode]==1) ui->PB_POLEKD->setText("正");else ui->PB_POLEKD->setText("负");
    if(m_Pole[_DEF_TARGET][m_Mode]==1) ui->PB_POLETARGET->setText("正");else ui->PB_POLETARGET->setText("负");

}
void VMotorControler::ValueRefresh(){
    PoleRefresh();
    SliderRefresh();

    LineEditRefresh();

}

void VMotorControler::ChangePole(QPushButton* button,int type){

    if(m_Pole[type][m_Mode]==1){

        m_Pole[type][m_Mode]=-1;
        button->setText("负");

    }else{
        m_Pole[type][m_Mode]=1;
        button->setText("正");
    }


}

void VMotorControler::on_PB_SPEEDRING_clicked()
{
    m_Mode=_DEF_SPEEDRING;
    ValueRefresh();
    ui->PB_SPEEDRING->setEnabled(false);
    ui->PB_ANGLERING->setEnabled(true);
    ui->PB_GYRORING->setEnabled(true);
    ui->PB_SERVORING->setEnabled(true);
}


void VMotorControler::on_PB_ANGLERING_clicked()
{
    m_Mode=_DEF_ANGLERING;
    ValueRefresh();
    ui->PB_SPEEDRING->setEnabled(true);
    ui->PB_ANGLERING->setEnabled(false);
    ui->PB_GYRORING->setEnabled(true);
    ui->PB_SERVORING->setEnabled(true);
}

void VMotorControler::on_PB_GYRORING_clicked()
{
    m_Mode=_DEF_GYRORING;
    ValueRefresh();
    ui->PB_SPEEDRING->setEnabled(true);
    ui->PB_ANGLERING->setEnabled(true);
    ui->PB_GYRORING->setEnabled(false);
    ui->PB_SERVORING->setEnabled(true);
}

void VMotorControler::on_PB_SERVORING_clicked()
{
    m_Mode=_DEF_SERVORING;
    ValueRefresh();
    ui->PB_SPEEDRING->setEnabled(true);
    ui->PB_ANGLERING->setEnabled(true);
    ui->PB_GYRORING->setEnabled(true);
    ui->PB_SERVORING->setEnabled(false);
}

void VMotorControler::on_SD_KP_sliderMoved(int position)
{
    _FUNC_SDCHV(m_KpValue,_DEF_KP)

}

void VMotorControler::on_SD_KI_sliderMoved(int position)
{
   _FUNC_SDCHV(m_KiValue,_DEF_KI)
}

void VMotorControler::on_SD_KD_sliderMoved(int position)
{
    _FUNC_SDCHV(m_KdValue,_DEF_KD)
}

void VMotorControler::on_SD_TARGET_sliderMoved(int position)
{
   _FUNC_SDCHV(m_TargetValue,_DEF_TARGET)
}

void VMotorControler::on_LE_KP_textEdited(const QString &arg1)
{
    _FUNC_LECHV(m_KpValue,ui->PB_POLEKP,_DEF_KP)


}

void VMotorControler::on_LE_KI_textEdited(const QString &arg1)
{
    _FUNC_LECHV(m_KiValue,ui->PB_POLEKI,_DEF_KI)
}

void VMotorControler::on_LE_KD_textEdited(const QString &arg1)
{
    _FUNC_LECHV(m_KdValue,ui->PB_POLEKD,_DEF_KD)
}

void VMotorControler::on_LE_TARGET_textEdited(const QString &arg1)
{
    _FUNC_LECHV(m_TargetValue,ui->PB_POLETARGET,_DEF_TARGET)
}

void VMotorControler::on_PB_PLUSKP_clicked()
{

}

void VMotorControler::on_PB_REDUCEKP_clicked()
{

}

void VMotorControler::on_PB_PLUSKI_clicked()
{

}

void VMotorControler::on_PB_REDUCEKI_clicked()
{

}

void VMotorControler::on_PB_PLUSKD_clicked()
{

}

void VMotorControler::on_PB_REDUCEKD_clicked()
{

}

void VMotorControler::on_PB_PLUSTARGET_clicked()
{

}

void VMotorControler::on_PB_REDUCETARGET_clicked()
{

}

void VMotorControler::on_PB_POLEKP_clicked()
{
    ChangePole(ui->PB_POLEKP,_DEF_KP);
    m_KpValue[m_Mode]=-m_KpValue[m_Mode];
    VMotorMsg command(m_TypeHead[_DEF_KP][m_Mode],m_KpValue[m_Mode]);
            m_pKer->SendCommand(command);
            LineEditRefresh();
}

void VMotorControler::on_PB_POLEKI_clicked()
{
    ChangePole(ui->PB_POLEKI,_DEF_KI);
     m_KiValue[m_Mode]=-m_KiValue[m_Mode];
     VMotorMsg command(m_TypeHead[_DEF_KI][m_Mode],m_KiValue[m_Mode]);
             m_pKer->SendCommand(command);
             LineEditRefresh();
}

void VMotorControler::on_PB_POLEKD_clicked()
{
    ChangePole(ui->PB_POLEKD,_DEF_KD);
     m_KdValue[m_Mode]=-m_KdValue[m_Mode];
     VMotorMsg command(m_TypeHead[_DEF_KD][m_Mode],m_KdValue[m_Mode]);
             m_pKer->SendCommand(command);
LineEditRefresh();
}

void VMotorControler::on_PB_POLETARGET_clicked()
{
    ChangePole(ui->PB_POLETARGET,_DEF_TARGET);
     m_TargetValue[m_Mode]=-m_TargetValue[m_Mode];
     VMotorMsg command(m_TypeHead[_DEF_TARGET][m_Mode],m_TargetValue[m_Mode]);
             m_pKer->SendCommand(command);
    LineEditRefresh();
}

void VMotorControler::on_PB_SETKP_clicked()
{

}

void VMotorControler::on_PB_SETKI_clicked()
{

}

void VMotorControler::on_PB_SETKD_clicked()
{

}

void VMotorControler::on_PB_SETTARGET_clicked()
{

}

void VMotorControler::on_PB_RUNMOTOR_clicked()
{
    int cmd=0x01000000;
    VMotorMsg msg=VMotorMsg(_DEF_CMD_MOTOR,cmd);
    m_pKer->SendCommand(msg);
}



void VMotorControler::on_PB_STOPMOTOR_clicked()
{

    VMotorMsg msg=VMotorMsg(_DEF_CMD_MOTOR,_DEF_MOTOR_START);
    m_pKer->SendCommand(msg);


}
