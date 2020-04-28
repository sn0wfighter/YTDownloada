#include "mainwindow.h"

#include <QApplication>
#include <QCoreApplication>
#include <QMessageBox>
#include <QDebug>
#include <QFileInfo>
#include <QLabel>
#include <QString>
#include <QDir>


int main(int argc, char *argv[])
{

    QApplication a(argc, argv);


    const QString youtubedl_dir = QCoreApplication::applicationDirPath().append(QDir::separator()).append("youtube-dl.exe");



    if (!QFileInfo::exists(youtubedl_dir)) {

        QMessageBox msg;

        msg.setIcon(QMessageBox::Critical);
        msg.setWindowTitle("youtube-dl missing");
        QLabel *lbl = new QLabel();

        lbl->setText("<a href='https://youtube-dl.org/'>https://youtube-dl.org</a>");

        msg.setText(QString("%1 not found !!! Please download here: " + lbl->text()).arg(youtubedl_dir));
        msg.exec();

        return 1;

    }


    MainWindow w;
    w.show();
    return a.exec();
}
