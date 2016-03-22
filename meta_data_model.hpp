#ifndef META_DATA_MODEL_HPP
#define META_DATA_MODEL_HPP

#include "file.hpp"

#include <QtCore/QAbstractTableModel>

class QModelIndex;

class MetaDataModel : public QAbstractTableModel
{
    Q_OBJECT
    enum Column { Min = 0, Name = 0, Value = 1, Max = 1, Count = 2 };
public:
    MetaDataModel(const File&);

    //@override QAbstractTableModel
    int columnCount(const QModelIndex& = {}) const override;
    int rowCount(const QModelIndex& = {}) const override;
    QVariant data(const QModelIndex&, int role = Qt::DisplayRole) const override;
    QVariant headerData(
        int section, Qt::Orientation, int role = Qt::DisplayRole) const override;

private:
    const File &m_file;
};

#endif // META_DATA_MODEL_HPP
