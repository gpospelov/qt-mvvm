// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_EDITORFACTORY_H
#define MVVM_EDITORFACTORY_H

#include "global.h"
#include <string>

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

    // FIXME find better place for label logic
    bool hasStringRepresentation(const QModelIndex& index);
    std::string toString(const QModelIndex& index);
};

} // namespace ModelView

#endif // MVVM_EDITORFACTORY_H
