#ifndef MYDIALOG_H
#define MYDIALOG_H

#include <QDialog>

namespace Ui {
class MyDialog;
}

class MyDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MyDialog(QWidget *parent = nullptr);
     MyDialog(QWidget *parent, const QString str);
    ~MyDialog();
    void setDescription(const QString);

private:
    Ui::MyDialog *ui;
};

#endif // MYDIALOG_H
