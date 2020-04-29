#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qprocess.h>
#include "mydialog.h"
#include "downloadentry.h"
#include <qdir.h>
#include <QDebug>
#include <QCoreApplication>
#include <QFileDialog>
#include <QMessageBox>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    const QString ffmpeg_dir = QCoreApplication::applicationDirPath().append(QDir::separator()).append("ffmpeg.exe");

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

void MainWindow::on_pushButton_clicked()
{
    // output dir and URL must be filled out
    if(!(ui->outputLineEdit->text().isEmpty()))
    {
        //DownloadEntry de;
    }
}

void MainWindow::on_checkButton_clicked()
{
    if(!(ui->URLlineEdit->text().isEmpty()))
    {
            // check for available formats with youtube-dl
            QString URL = ui->URLlineEdit->text();
            QProcess *process = new QProcess;
            process->start(QString("youtube-dl.exe"), QStringList() << "-F" << URL);
            process->waitForFinished();
            int rc = process->exitCode();


            if (rc == 0)
            {
                // get output from commandline
                QString output(process->readAll());
                // split at each linebreak
                QStringList entries(output.split(QRegExp("[\n]"), QString::SkipEmptyParts));



                ui->formatsComboBox->clear();

                int max_width = 0;
                QFontMetrics fm(QFont(ui->formatsComboBox->font().family(), ui->formatsComboBox->font().pointSize()));


                foreach (QString item, entries) {
                    if (item.contains("[")) {
                        continue;
                    }

                    item.replace(QRegExp("[ ]+"), " ");

                    int current_width = fm.horizontalAdvance(item, -1);
                    if (current_width > max_width) {
                        max_width = current_width;
                    }

                    ui->formatsComboBox->addItem(item);
                }

                ui->formatsComboBox->setStyleSheet(QString("QComboBox QAbstractItemView { min-width: %1;}").arg(QString::number(max_width)));


            } else {
                QMessageBox::critical(nullptr, QString("Unsupported URL"), "This URL is not supported by youtube-dl!\nFor supported pages visit http://ytdl-org.github.io/youtube-dl/supportedsites.html");
                qDebug() << "unsupported URL, returncode != 0";
            }


    }
}
