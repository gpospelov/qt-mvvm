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

#include "editorbuilders.h"
#include "editorfactoryinterface.h"
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
    ~DefaultEditorFactory() override;

    std::unique_ptr<CustomEditor> createEditor(const QModelIndex& index) const override;

protected:
    void registerBuilder(const std::string& name, EditorBuilders::builder_t strategy);
    EditorBuilders::builder_t findBuilder(const std::string& name) const;
    std::map<std::string, EditorBuilders::builder_t> m_editor_builders;
};

} // namespace ModelView

#endif // MVVM_DEFAULTEDITORFACTORY_H
