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
    DefaultEditorFactory();

    CustomEditor* createEditor(const QModelIndex& index, QWidget* parent = nullptr) const;

private:
    CustomEditor* createEditor(const SessionItem* item, QWidget* parent = nullptr) const;
};

} // namespace ModelView

#endif // MVVM_DEFAULTEDITORFACTORY_H
