#ifndef DOWNLOADENTRY_H
#define DOWNLOADENTRY_H

#include <QString>
#include <QStringList>
#include <QDebug>


class DownloadEntry
{
public:
    //DownloadEntry();
    DownloadEntry(QString&, bool);

    static void incrementCounter();
    static void decrementCounter();


    QString getUrl() const;

    QString getAudioOnly() const;

    void setUrl(const QString &value);

    void setAudioOnly(bool value);

    QStringList getAvailableFormats() const;
    void setAvailableFormats(const QStringList &value);

    QString getCommandline() const;
    void buildCommandline();

    void setFormatcode(const QString &value);

    QString getFormatcode() const;

private:
    QString url;
    bool audioOnly;
    QStringList availableFormats;
    QString formatcode;
    QString commandline;


};

static int counter = 0;



#endif // DOWNLOADENTRY_H
