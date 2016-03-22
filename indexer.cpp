#include "indexer.hpp"

#include <cassert>

#include <QtCore/QFile>
#include <QtCore/QStandardPaths>
#include <QtCore/QString>

Indexer::
Indexer()
{
    using Signal = void(QProcess::*)(int, QProcess::ExitStatus);
    this->connect(&m_process, static_cast<Signal>(&QProcess::finished),
                  this,       &Indexer::processFinished);
}

void Indexer::
start(const QString &path)
{
    assert(QFile::exists(path));

    if (m_process.state() != QProcess::NotRunning) return;

    const auto &program = QStandardPaths::findExecutable("balooctl");
    QStringList args;
    args << "index" << path;

    m_process.start(program, args);
}

void Indexer::
processFinished(
        const int/*exitCode*/, const QProcess::ExitStatus exitStatus)
{
    Q_EMIT finished(exitStatus == QProcess::NormalExit);
}
