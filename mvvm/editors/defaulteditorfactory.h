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
#include "editorconstructorstrategy.h"
#include <map>

namespace ModelView
{

class SessionItem;

//! Default editor factory for custom variants.
//! Used in context of trees and tables via ViewModelDelegate.

class CORE_EXPORT DefaultEditorFactory : public EditorFactoryInterface
{
public:
    DefaultEditorFactory();
    ~DefaultEditorFactory();

    std::unique_ptr<CustomEditor> createEditor(const QModelIndex& index) const;

private:
    void registerStrategy(const std::string& name, EditorConstructorStrategy::strategy_t strategy);
    CustomEditor* createEditor(const SessionItem* item) const;

    std::map<std::string, EditorConstructorStrategy::strategy_t> m_editor_constructors;
};

} // namespace ModelView

#endif // MVVM_DEFAULTEDITORFACTORY_H
