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

//! Editor factory for custom variants.

class CORE_EXPORT EditorFactory
{
public:
    EditorFactory();

    QWidget* createEditor(const QModelIndex& index) const;
};

} // namespace ModelView

#endif // EDITORFACTORY_H
