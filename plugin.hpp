#ifndef META_DATA_PLUGIN_HPP
#define META_DATA_PLUGIN_HPP

#include "file.hpp"

#include <memory>

#include <KPropertiesDialog>

class Plugin: public KPropertiesDialogPlugin
{
public:
    Plugin(QObject* const dialog, const QVariantList&);
    ~Plugin();

private:
    std::unique_ptr<File> m_file;
};

#endif // META_DATA_PLUGIN_HPP
