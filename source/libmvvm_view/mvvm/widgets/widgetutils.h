// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_WIDGETS_UTILS_H
#define MVVM_WIDGETS_UTILS_H

#include <mvvm/core/export.h>

class QColor;
class QString;
class QSize;
class QMainWindow;

namespace ModelView
{

//! Collection of various widget-related utils.

namespace Utils
{

//! Returns random color.
CORE_EXPORT QColor random_color();

//! Returns true if it is Windows.
CORE_EXPORT bool IsWindowsHost();

//! Returns a string where Linux path to the file is striped using '~/'.
CORE_EXPORT QString WithTildeHomePath(const QString& path);

//! Returns a title composed from last part of project path, and `is_modified` flag.
CORE_EXPORT QString ProjectWindowTitle(const QString& project_dir, bool is_modified);

//! Returns width of the letter 'M' deduced from current font metrics.
CORE_EXPORT int WidthOfLetterM();

//! Returns height of the letter 'M' deduced from current font metrics.
CORE_EXPORT int HeightOfLetterM();

//! Returns size corresponding to actual size of letter `M` basing on current font metrics.
CORE_EXPORT QSize SizeOfLetterM();

//! Returns size in points of default system font.
CORE_EXPORT int SystemPointSize();

//! Finds main window.
CORE_EXPORT QMainWindow* FindMainWindow();

} // namespace Utils

} // namespace ModelView

#endif // MVVM_WIDGETS_UTILS_H
