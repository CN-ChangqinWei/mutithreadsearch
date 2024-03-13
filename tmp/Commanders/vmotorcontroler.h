#ifndef VMOTORCONTROLER_H
#define VMOTORCONTROLER_H

#include <QDialog>

namespace Ui {
class VMotorControler;
}

class VMotorControler : public QDialog
{
    Q_OBJECT

public:
    explicit VMotorControler(QWidget *parent = 0);
    ~VMotorControler();

private:
    Ui::VMotorControler *ui;
};

#endif // VMOTORCONTROLER_H
