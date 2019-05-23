// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_EDITORFACTORYINTERFACE_H
#define MVVM_EDITORFACTORYINTERFACE_H

#include "mvvm_global.h"
#include <string>
#include <memory>

class QModelIndex;
class QWidget;

namespace ModelView
{

class CustomEditor;

//! Interface for custom editor factory.
//! Intended for editor construction in cells of tables and trees in the context of delegate.

class CORE_EXPORT EditorFactoryInterface
{
public:
    virtual ~EditorFactoryInterface() = default;

    virtual std::unique_ptr<CustomEditor> createEditor(const QModelIndex& index) const = 0;
};

} // namespace ModelView

#endif // MVVM_EDITORFACTORYINTERFACE_H
