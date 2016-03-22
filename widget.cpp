#include "widget.hpp"

#include "file.hpp"
#include "indexer.hpp"
#include "meta_data_model.hpp"

#include <cassert>

#include <QtCore/QString>
#include <QtGui/QCursor>
#include <QtGui/QGuiApplication>
#include <QtWidgets/QBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QTreeView>

#include <KLocalizedString>

Widget::
Widget(File &file, QWidget &parent)
    : Base   { &parent }
    , m_file { file }
{
    auto* const layout = new QVBoxLayout { this };

    m_tableView.reset(new QTreeView { this });
    assert(m_tableView);
    m_tableView->setRootIsDecorated(false);

    layout->addWidget(m_tableView.get());

    auto* const buttonContainer = new QWidget { this };
    assert(buttonContainer);
    {
        auto* const layout = new QHBoxLayout { buttonContainer };
        assert(layout);
        layout->setContentsMargins(0, 0, 0, 0);

        layout->addStretch(1);

        m_indexButton.reset(new QPushButton { this });
        m_indexButton->setText(i18nc("@action:button", "&Index"));
        layout->addWidget(m_indexButton.get());

        this->connect(m_indexButton.get(), &QPushButton::clicked,
                      this,                &Widget::indexClicked);
    }
    layout->addWidget(buttonContainer);

    this->connect(&m_file, &File::metaDataChanged,
                  this,    &Widget::setModel);
    setModel();
}

Widget::~Widget() = default;

void Widget::
setModel()
{
    if (m_file.indexed()) {
        auto* const newModel = new MetaDataModel { m_file };
        assert(newModel);
        m_tableView->setModel(newModel);

        m_model.reset(newModel);
    }
    else {
        m_tableView->setModel(nullptr);
        m_model.reset(nullptr);
    }
}

void Widget::
indexClicked()
{
    if (m_indexer) return; // already running

    QGuiApplication::setOverrideCursor(QCursor { Qt::WaitCursor });
    m_indexButton->setEnabled(false);

    m_indexer.reset(new Indexer);
    this->connect(m_indexer.get(), &Indexer::finished,
        [this](const bool/*success*/) {
            QGuiApplication::restoreOverrideCursor();
            m_indexButton->setEnabled(true);

            m_indexer.reset(nullptr);
        }
    );

    m_indexer->start(m_file.path());
}
