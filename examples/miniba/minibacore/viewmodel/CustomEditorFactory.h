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

//! Editor factory with custom editors (i.e. MaterialSelector).

class CORE_EXPORT CustomEditorFactory : public ModelView::DefaultEditorFactory
{
public:
    ~CustomEditorFactory();

    std::unique_ptr<ModelView::CustomEditor> createEditor(const QModelIndex& index) const;
};

#endif //  CUSTOMEDITORFACTORY_H
