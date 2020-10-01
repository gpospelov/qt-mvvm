// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_EDITORS_DEFAULTEDITORFACTORY_H
#define MVVM_EDITORS_DEFAULTEDITORFACTORY_H

#include <map>
#include <mvvm/editors/editorbuilders.h>
#include <mvvm/interfaces/editorfactoryinterface.h>

namespace ModelView
{

//! Default editor factory for custom variants.
//! Used in context of trees and tables via ViewModelDelegate.

class MVVM_VIEWMODEL_EXPORT DefaultEditorFactory : public EditorFactoryInterface
{
public:
    DefaultEditorFactory();
    ~DefaultEditorFactory() override;

    std::unique_ptr<CustomEditor> createEditor(const QModelIndex& index) const override;

protected:
    void initBuildersForVariantName();
    void initBuildersForEditorType();
    void registerBuilderForVariant(const std::string& variant_name,
                                   EditorBuilders::builder_t builder);
    void registerBuilderForEditor(const std::string& editor_type,
                                   EditorBuilders::builder_t builder);

    EditorBuilders::builder_t findBuilderForVariant(const std::string& variant_name) const;
    EditorBuilders::builder_t findBuilderForEditor(const std::string& editor_type) const;

    std::map<std::string, EditorBuilders::builder_t> m_variantNameToBuilderMap;
    std::map<std::string, EditorBuilders::builder_t> m_editorTypeToBuilderMap;
};

} // namespace ModelView

#endif // MVVM_EDITORS_DEFAULTEDITORFACTORY_H
