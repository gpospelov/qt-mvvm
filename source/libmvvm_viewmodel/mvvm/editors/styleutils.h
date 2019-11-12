// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_EDITORS_STYLEUTILS_H
#define MVVM_EDITORS_STYLEUTILS_H

#include <mvvm/core/export.h>

namespace ModelView
{

namespace Style
{

//! Returns int value corresponding to pixmap in standard Qt table/tree decorations.
CORE_EXPORT int DefaultPixmapSize();

//! Returns default height of info bar
CORE_EXPORT int DefaultInfoBarHeight();

//! Returns default size of text on info bar.
CORE_EXPORT int DefaultInfoBarTextSize();

}

} // namespace ModelView

#endif  // MVVM_EDITORS_STYLEUTILS_H
