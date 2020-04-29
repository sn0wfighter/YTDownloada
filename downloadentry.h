#ifndef DOWNLOADENTRY_H
#define DOWNLOADENTRY_H

#include "mainwindow.h"
#include <QString>
#include <QStringList>
#include <QDebug>
#include <QDir>


class DownloadEntry
{
public:
    //DownloadEntry();
    DownloadEntry(QString&, bool);

    static void incrementCounter();
    static void decrementCounter();


    QString getUrl() const;

    bool getAudioOnly() const;
    QString getAudioOnlyFlag() const;

    void setUrl(const QString &value);
    void setAudioOnly(bool value);

    QStringList getAvailableFormats() const;
    void setAvailableFormats(const QStringList &value);

    QString getCommandline() const;
    void buildCommandline();

    QString extractFormatcode(const QString &value);
    void setFormatcode(const QString &value);

    QString getFormatcode() const;

    QDir getDownloadlocation() const;
    void setDownloadlocation(const QDir &value);

private:
    QString url;
    bool audioOnly;
    QStringList availableFormats;
    QString formatcode;
    QString commandline;
    QDir downloadlocation;


};

static int counter = 0;



#endif // DOWNLOADENTRY_H
