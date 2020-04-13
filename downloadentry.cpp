#include "downloadentry.h"

//DownloadEntry::DownloadEntry()
//{

//}

DownloadEntry::DownloadEntry(QString &url, bool audioonly)
{
    this->setUrl(url);
    this->setAudioOnly(audioonly);

    incrementCounter();
}

QString DownloadEntry::getUrl() const
{
    return url;
}

bool DownloadEntry::getAudioOnly() const
{
    return audioOnly;
}


QString DownloadEntry::getAudioOnlyFlag() const
{
    if (getAudioOnly())
    {
        return QString("-x --audio-format mp3");
    }
    else {
        return QString("");
    }

}

void DownloadEntry::setUrl(const QString &value)
{
    url = value;
}

void DownloadEntry::setAudioOnly(bool value)
{
    audioOnly = value;
}

QStringList DownloadEntry::getAvailableFormats() const
{
    return availableFormats;
}

void DownloadEntry::setAvailableFormats(const QStringList &value)
{
    availableFormats = value;
}

QString DownloadEntry::getCommandline() const
{
    return commandline;
}

void DownloadEntry::buildCommandline()
{
    // %1 = youtube-dl, %2 = formatcode, %3 = audio-only flag, $4 = URL
    QString temp = QString("%1 -f %2 %3 %4").arg("youtube-dl.exe").arg(getFormatcode()).arg(getAudioOnlyFlag())\
            .arg(getUrl());
    qDebug() << "set commandline to " << temp;

    commandline = temp;


}

void DownloadEntry::setFormatcode(const QString &value)
{
    formatcode = value;
}

QString DownloadEntry::getFormatcode() const
{
    return formatcode;
}

void DownloadEntry::incrementCounter()
{
    counter++;
}

void DownloadEntry::decrementCounter()
{
    counter--;
}
