// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef CUSTOMEDITORFACTORY_H
#define CUSTOMEDITORFACTORY_H

#include "defaulteditorfactory.h"

namespace ModelView
{
class CustomEditor;
}

class ApplicationModels;

/*!
@class CustomEditorFactory
@brief Editor factory with custom editors.

Will create custom material selector for all cells containing ExternalProperty.
*/

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
