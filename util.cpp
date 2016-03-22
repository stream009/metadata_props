#include "util.hpp"

#include <cassert>

#include <QtCore/QDebug>
#include <QtCore/QVariant>

#include <KCoreAddons/KFormat>
#include <KLocalizedString>

namespace util {

static QString
formatNumber(const int bps)
{
    if (bps < 1000) {
        return QString { "%1 " }.arg(bps);
    }
    else if (bps < 1000 * 1000) {
        return ki18nc("number formatted in kilo", "%1 K")
            .subs(static_cast<double>(bps) / 1000, 0, 'f', 3).toString();
    }
    else {
        return ki18nc("number formatted in mega", "%1 M")
            .subs(static_cast<double>(bps) / 1000 / 1000, 0, 'f', 3).toString();
    }
}

QString
format(const KFileMetaData::Property::Property type,
       const QVariant &value)
{
    static const KFormat format;

    using namespace KFileMetaData::Property;
    switch (type) {
    case BitRate:
        return ki18nc("bit rate", "%1bps")
                            .subs(formatNumber(value.toInt())).toString();
    case Duration:
        return format.formatDuration(value.toULongLong() * 1000);
        break;
    case SampleRate:
        return ki18nc("sampling ratio", "%1Hz").subs(value.toInt()).toString();
        break;
    default:
        return value.toString();
        break;
    }
}

} // namespace util
