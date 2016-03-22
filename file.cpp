#include "file.hpp"

#include "util.hpp"

#include <cassert>

#include <QtCore/QFile>

File::
File(const QString &path)
    : m_file    { path }
    , m_indexed { m_file.load() }
{
    assert(QFile::exists(path));
    m_monitor.addFile(path);

    this->connect(&m_monitor, &Baloo::FileMonitor::fileMetaDataChanged,
        [this] {
            m_indexed = m_file.load();
            Q_EMIT metaDataChanged();
        }
    );
}

KFileMetaData::PropertyMap File::
properties() const
{
    return m_indexed ? m_file.properties() : KFileMetaData::PropertyMap {};
}
