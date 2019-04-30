// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_DEFAULTEDITORFACTORY_H
#define MVVM_DEFAULTEDITORFACTORY_H

#include "editorfactoryinterface.h"

namespace ModelView
{

class SessionItem;

//! Default wditor factory for custom variants.

class CORE_EXPORT DefaultEditorFactory : public EditorFactoryInterface
{
public:
    ~DefaultEditorFactory();

    std::unique_ptr<CustomEditor> createEditor(const QModelIndex& index) const;

private:
    CustomEditor* createEditor(const SessionItem* item) const;
};

} // namespace ModelView

#endif // MVVM_DEFAULTEDITORFACTORY_H
