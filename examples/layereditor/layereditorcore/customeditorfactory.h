// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef CUSTOMEDITORFACTORY_H
#define CUSTOMEDITORFACTORY_H

#include <mvvm/editors/defaulteditorfactory.h>

class ApplicationModels;

//! Editor factory with custom editors.
//! Will create custom material selector for all cells containing ExternalProperty.

class CustomEditorFactory : public ModelView::DefaultEditorFactory
{
public:
    CustomEditorFactory(ApplicationModels* models);
    ~CustomEditorFactory();

    std::unique_ptr<ModelView::CustomEditor> createEditor(const QModelIndex& index) const;

private:
    ApplicationModels* m_models;
};

#endif //  CUSTOMEDITORFACTORY_H
