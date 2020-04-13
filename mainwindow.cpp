#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qprocess.h>
#include "mydialog.h"
#include <qdir.h>
#include <QDebug>
#include <QCoreApplication>
#include <QFileDialog>
#include <QMessageBox>


const QString ffmpeg_dir = QCoreApplication::applicationDirPath().append(QDir::separator()).append("ffmpeg.exe");

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    if (!QFileInfo::exists(ffmpeg_dir)) {
        qDebug() << "ffmpeg not found, for mp3 support please download";
        QMessageBox err;
        err.setIcon(QMessageBox::Critical);
        err.setText(QString("ffmpeg not found, please download for mp3 support!"));
        err.setWindowTitle("ffmpeg not found");
        err.exec();
        ui->AudioCheckbox->setEnabled(false);
    }


}

MainWindow::~MainWindow()
{
    delete ui;
}



// slot update button youtube-dl
void MainWindow::on_UpdateButton_clicked()
{
    QProcess *procupdaty = new QProcess;
    procupdaty->start(QString("youtube-dl.exe"),QStringList("--update"));
    procupdaty->waitForFinished();
    QString updoutput(procupdaty->readAllStandardOutput());

    int res = procupdaty->exitCode();

//    res = 2454325;
    switch (res) {
    case -2: {MyDialog d(this, "Process could not be started :("); d.exec(); break;};
    case -1: {MyDialog d(this, "Process crashed :("); d.exec(); break;}
    case 0: {MyDialog d(this, "Update check successful!\n" + updoutput); d.exec(); break;}
    default: {MyDialog d(this, "Unknown error! Please try again later! ¯\\_(ツ)_/¯ "); d.exec(); break;}
    }

}

// slot browse button :-> Sexy Jay, (c) Tony B
void MainWindow::on_browseButton_clicked()
{
    QString currentpath;
    if (ui->outputLineEdit->text().isEmpty()){
        currentpath = QDir::toNativeSeparators(QDir::homePath());
    } else {
        currentpath = ui->outputLineEdit->text();
    }

    ui->outputLineEdit->setText(QFileDialog::getExistingDirectory(nullptr, ("Select output directory"), currentpath, QFileDialog::ShowDirsOnly));
}
