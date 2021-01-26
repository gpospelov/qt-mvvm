// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_INTERFACES_MODELDOCUMENTINTERFACE_H
#define MVVM_INTERFACES_MODELDOCUMENTINTERFACE_H

#include "mvvm/model_export.h"
#include <string>

namespace ModelView {

//! Pure virtual interface to save and restore session models to/from disk.

class MVVM_MODEL_EXPORT ModelDocumentInterface {
public:
    virtual ~ModelDocumentInterface() = default;

    virtual void save(const std::string& file_name) const = 0;
    virtual void load(const std::string& file_name) = 0;
};

} // namespace ModelView

#endif // MVVM_INTERFACES_MODELDOCUMENTINTERFACE_H
