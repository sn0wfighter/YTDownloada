#include "mydialog.h"
#include "ui_mydialog.h"

MyDialog::MyDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MyDialog)
{
    ui->setupUi(this);
}



MyDialog::~MyDialog()
{
    delete ui;
}

MyDialog::MyDialog(QWidget *parent, const QString descr) : QDialog(parent),
    ui(new Ui::MyDialog)
{
    ui->setupUi(this);
    this->setDescription(descr);
}

void MyDialog::setDescription(const QString descr){

    ui->descr->setText(descr);

}


