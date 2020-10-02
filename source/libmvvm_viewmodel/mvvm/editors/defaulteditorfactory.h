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

//! Base class for all editor factories.
//! Used in the context of trees and tables via ViewModelDelegate.

class MVVM_VIEWMODEL_EXPORT EditorFactory : public EditorFactoryInterface
{
public:
    std::unique_ptr<CustomEditor> createEditor(const QModelIndex& index) const override;

protected:
    virtual std::unique_ptr<CustomEditor> createEditor(const SessionItem& item) const = 0;

    void registerBuilder(const std::string& name, EditorBuilders::builder_t builder);
    EditorBuilders::builder_t findBuilder(const std::string& name) const;

    std::map<std::string, EditorBuilders::builder_t> m_nameToBuilderMap;
};

//! Creates cell editors for trees and tables basing on variant name.

class MVVM_VIEWMODEL_EXPORT VariantDependentEditorFactory : public EditorFactory
{
public:
    VariantDependentEditorFactory();

protected:
    std::unique_ptr<CustomEditor> createEditor(const SessionItem& item) const override;
};

//! Creates cell editors for trees and tables basing on possible EDITORTYPE role encoded in item.

class MVVM_VIEWMODEL_EXPORT RoleDependentEditorFactory : public EditorFactory
{
public:
    RoleDependentEditorFactory();

protected:
    std::unique_ptr<CustomEditor> createEditor(const SessionItem& item) const override;
};

//! Default editor factory for custom variants.
//! Used in the context of trees and tables via ViewModelDelegate.

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
