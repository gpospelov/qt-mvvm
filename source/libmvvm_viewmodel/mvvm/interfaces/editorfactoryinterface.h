// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_INTERFACES_EDITORFACTORYINTERFACE_H
#define MVVM_INTERFACES_EDITORFACTORYINTERFACE_H

#include "mvvm/viewmodel_export.h"
#include <memory>
#include <string>

class QModelIndex;
class QWidget;

namespace ModelView {

class CustomEditor;

//! Interface for custom editor factory.
//! Intended for editor construction in cells of tables and trees in the context of delegate.

class MVVM_VIEWMODEL_EXPORT EditorFactoryInterface {
public:
    virtual ~EditorFactoryInterface() = default;

    virtual std::unique_ptr<CustomEditor> createEditor(const QModelIndex& index) const = 0;
};

} // namespace ModelView

#endif // MVVM_INTERFACES_EDITORFACTORYINTERFACE_H
