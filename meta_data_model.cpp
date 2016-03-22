#include "meta_data_model.hpp"

#include "util.hpp"

#include <cassert>

#include <QtCore/QDebug>

#include <KFileMetaData/PropertyInfo>
#include <KLocalizedString>

MetaDataModel::
MetaDataModel(const File &file)
    : m_file { file }
{}

int MetaDataModel::
columnCount(const QModelIndex &parent/*= {}*/) const
{
    assert(!parent.isValid());
    return Column::Count;
}

int MetaDataModel::
rowCount(const QModelIndex &parent/*= {}*/) const
{
    assert(!parent.isValid());
    return m_file.properties().size();
}

QVariant MetaDataModel::
data(const QModelIndex &index, const int role/*= Qt::DisplayRole*/) const
{
    if (role != Qt::DisplayRole) return {};

    assert(index.isValid());
    const auto row = index.row();
    const auto column = index.column();

    const auto &props = m_file.properties();
    assert(0 <= row && row < props.size());
    assert(Column::Min <= column && column <= Column::Max);

    const auto &keys = props.keys();
    const auto &key = keys.at(row);
    switch (column) {
    case Column::Name: {
            KFileMetaData::PropertyInfo propInfo { key };
            return propInfo.displayName();
        }
        break;
    case Column::Value: {
            const auto &values = props.values();
            const auto &value = values.at(row);
            return util::format(key, value);
        }
        break;
    default:
        assert(false);
        qWarning() << __PRETTY_FUNCTION__
                   << "Unknown section of data is requested";
        break;
    }

    return {};
}

QVariant MetaDataModel::
headerData(const int section, const Qt::Orientation orientation,
           const int role/*= Qt::DisplayRole*/) const
{
    if (role != Qt::DisplayRole) return {};
    if (orientation != Qt::Horizontal) return {};

    switch (section) {
    case Column::Name:
        return i18nc("@title:column", "Name");
        break;
    case Column::Value:
        return i18nc("@title@column", "Value");
        break;
    default:
        assert(false);
        qWarning() << __PRETTY_FUNCTION__
                   << "Unknown section of header data is requested";
        break;
    }

    return {};
}
