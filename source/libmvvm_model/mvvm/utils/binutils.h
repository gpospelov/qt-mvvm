// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_UTILS_BINUTILS_H
#define MVVM_UTILS_BINUTILS_H

#include <mvvm/model_export.h>

namespace ModelView ::Utils
{

//! Returns true if file is binary
MVVM_MODEL_EXPORT bool is_binary(std::string filename);

//! Returns true if file is text/ascii
MVVM_MODEL_EXPORT bool is_text(std::string filename);

} // namespace ModelView::Utils

#endif // MVVM_UTILS_BINUTILS_H
