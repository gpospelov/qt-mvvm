// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QColor>
#include <QDir>
#include <mvvm/utils/numericutils.h>
#include <mvvm/widgets/widgetutils.h>

QColor ModelView::Utils::random_color()
{
    auto rndm = []() -> int { return ModelView::Utils::RandInt(0, 255); };
    return QColor(rndm(), rndm(), rndm());
}

bool ModelView::Utils::IsWindowsHost()
{
#if defined(Q_OS_WIN)
    return true;
#else
    return false;
#endif
}

QString ModelView::Utils::WithTildeHomePath(const QString& path)
{
    if (ModelView::Utils::IsWindowsHost())
        return path;

    static const QString homePath = QDir::homePath();

    QFileInfo fi(QDir::cleanPath(path));
    QString outPath = fi.absoluteFilePath();
    if (outPath.startsWith(homePath))
        outPath = QLatin1Char('~') + outPath.mid(homePath.size());
    else
        outPath = path;
    return outPath;
}
