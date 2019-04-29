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

class QModelIndex;
class QWidget;

namespace ModelView
{

class CustomEditor;

//! Interface for for custom editor factory.

class CORE_EXPORT EditorFactoryInterface
{
public:
    virtual ~EditorFactoryInterface() = default;

    virtual CustomEditor* createEditor(const QModelIndex& index,
                                       QWidget* parent = nullptr) const = 0;
};

} // namespace ModelView

#endif // MVVM_EDITORFACTORYINTERFACE_H
