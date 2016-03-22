#ifndef METADATA_PROPS_INDEXER_HPP
#define METADATA_PROPS_INDEXER_HPP

#include <QtCore/QObject>
#include <QtCore/QProcess>

class QString;

class Indexer : public QObject
{
    Q_OBJECT
public:
    Indexer();

    void start(const QString &path);

Q_SIGNALS:
    void finished(const bool success);

private Q_SLOTS:
    void processFinished(int exitCode, QProcess::ExitStatus);

private:
    QProcess m_process;
};

#endif // METADATA_PROPS_INDEXER_HPP
