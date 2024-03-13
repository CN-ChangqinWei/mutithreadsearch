#include "vmotorcontroler.h"
#include "ui_vmotorcontroler.h"

VMotorControler::VMotorControler(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::VMotorControler)
{
    ui->setupUi(this);
}

VMotorControler::~VMotorControler()
{
    delete ui;
}
