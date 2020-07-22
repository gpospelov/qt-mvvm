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

#include <QString>
#include <mvvm/view_export.h>

class QColor;
class QSize;
class QMainWindow;
class QLabel;

namespace ModelView
{

//! Collection of various widget-related utils.

namespace Utils
{

//! Returns random color.
MVVM_VIEW_EXPORT QColor random_color();

//! Returns true if it is Windows.
MVVM_VIEW_EXPORT bool IsWindowsHost();

//! Returns true if it is Mac.
MVVM_VIEW_EXPORT bool IsMacHost();

//! Returns true if it is Linux.
MVVM_VIEW_EXPORT bool IsLinuxHost();

//! Returns a string where Linux path to the file is striped using '~/'.
MVVM_VIEW_EXPORT QString WithTildeHomePath(const QString& path);

//! Returns a title composed from last part of project path, and `is_modified` flag.
MVVM_VIEW_EXPORT QString ProjectWindowTitle(const QString& project_dir, bool is_modified);

//! Returns width of the letter 'M' deduced from current font metrics.
MVVM_VIEW_EXPORT int WidthOfLetterM();

//! Returns height of the letter 'M' deduced from current font metrics.
MVVM_VIEW_EXPORT int HeightOfLetterM();

//! Returns size corresponding to actual size of letter `M` basing on current font metrics.
MVVM_VIEW_EXPORT QSize SizeOfLetterM();

//! Returns size in points of default system font.
MVVM_VIEW_EXPORT int SystemPointSize();

//! Finds main window.
MVVM_VIEW_EXPORT QMainWindow* FindMainWindow();

//! Returns text wrapped into 'href' tag to provide clickable links in QLabel.
//! Example: <a href="tag">text</a>, if 'tag' is empty, 'text' will be used instead.
MVVM_VIEW_EXPORT QString ClickableText(const QString& text, const QString& tag = {});

//! Set label's font size to system font size scaled by given factor.
MVVM_VIEW_EXPORT void ScaleLabelFont(QLabel* label, double scale);

} // namespace Utils

} // namespace ModelView

#endif // MVVM_WIDGETS_UTILS_H
