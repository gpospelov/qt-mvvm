// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_INTERFACES_PROJECTINTERFACE_H
#define MVVM_INTERFACES_PROJECTINTERFACE_H

#include "mvvm/model_export.h"
#include <string>

namespace ModelView {

//! Interface to manipulate projects on disk.
//! Project represents content of all application models in a folder on disk.

class MVVM_MODEL_EXPORT ProjectInterface {
public:
    virtual ~ProjectInterface() = default;
    virtual std::string projectDir() const = 0;
    virtual bool save(const std::string& dirname) const = 0;
    virtual bool load(const std::string& dirname) = 0;
    virtual bool isModified() const = 0;
};

} // namespace ModelView

#endif // MVVM_INTERFACES_PROJECTINTERFACE_H
