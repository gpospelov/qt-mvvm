// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef EDITORFACTORY_H
#define EDITORFACTORY_H

#include "global.h"

class QWidget;
class QModelIndex;

namespace ModelView
{

class SessionItem;
class CustomEditor;

//! Editor factory for custom variants.

class CORE_EXPORT EditorFactory
{
public:
    EditorFactory();

    CustomEditor* createEditor(const QModelIndex& index, QWidget* parent = nullptr) const;
    CustomEditor* createEditor(const SessionItem* item, QWidget* parent = nullptr) const;
};

} // namespace ModelView

#endif // EDITORFACTORY_H
