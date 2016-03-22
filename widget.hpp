#ifndef META_DATA_WIDGET_HPP
#define META_DATA_WIDGET_HPP

#include <cassert>
#include <memory>

#include <QtWidgets/QWidget>

class File;
class Indexer;
class MetaDataModel;

class QString;
class QTreeView;
class QPushButton;

class Widget : public QWidget
{
    Q_OBJECT
    using Base = QWidget;
public:
    Widget(File &file, QWidget &parent);
    ~Widget();

private Q_SLOTS:
    void setModel();
    void indexClicked();

private:
    void validate() const
    {
        assert(m_tableView);
        assert(m_indexButton);
    }

private:
    File                          &m_file;
    std::unique_ptr<QTreeView>     m_tableView;
    std::unique_ptr<QPushButton>   m_indexButton;
    std::unique_ptr<MetaDataModel> m_model;
    std::unique_ptr<Indexer>       m_indexer;
};

#endif // META_DATA_WIDGET_HPP
