#ifndef FILE_HPP
#define FILE_HPP

#include <QtCore/QObject>

#include <Baloo/File>
#include <Baloo/FileMonitor>
#include <KFileMetaData/Properties>

class QString;

class File : public QObject
{
    Q_OBJECT
public:
    File(const QString &path);

    // accessor
    QString path() const { return m_file.path(); }
    bool indexed() const { return m_indexed; }
    KFileMetaData::PropertyMap properties() const;

Q_SIGNALS:
    void metaDataChanged();

private:
    Baloo::File        m_file;
    Baloo::FileMonitor m_monitor;
    bool               m_indexed = false;
};

#endif // FILE_HPP
