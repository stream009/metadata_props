#include "plugin.hpp"

#include "widget.hpp"

#include <cassert>

#include <QtCore/QDebug>

#include <KLocalizedString>
#include <KPluginFactory>

K_PLUGIN_FACTORY_WITH_JSON(
        PluginFactory, "metadata_props.json", registerPlugin<Plugin>();)

Plugin::
Plugin(QObject* const parent, const QVariantList&) // nothrow
    : KPropertiesDialogPlugin { static_cast<KPropertiesDialog*>(parent) }
{
    assert(parent);
    try {
        const auto &items = this->properties->items();
        if (items.size() != 1) {
            return;
        }
        const auto &item = items.front();
        assert(!item.isNull());
        if (!item.isLocalFile() || item.isDir()) {
            return;
        }

        m_file.reset(new File { item.localPath() });
        assert(m_file);
        auto* const widget = new Widget {
                          *m_file, *static_cast<QWidget*>(parent) };
        assert(widget);

        this->properties->addPage(widget, i18nc("@title:tab", "Meta data"));
    }
    catch (const std::exception &e) {
        qDebug() << "Exception: " << e.what();
    }
    catch (...) {
        qDebug() << "Unknown exception has caught.";
    }
}

Plugin::~Plugin() = default;

#include <plugin.moc>
