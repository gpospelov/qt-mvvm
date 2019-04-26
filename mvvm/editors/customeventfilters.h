// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_CUSTOMEVENTFILTERS_H
#define MVVM_CUSTOMEVENTFILTERS_H

#include "mvvm_global.h"
#include <QObject>

namespace ModelView
{
//! Event filter to prevent lost of focus by custom material editor.

class CORE_EXPORT LostFocusFilter : public QObject
{
    Q_OBJECT
public:
    LostFocusFilter(QObject* parent = nullptr);

protected:
    bool eventFilter(QObject* obj, QEvent* event);
};

} // namespace ModelView

#endif // MVVM_CUSTOMEVENTFILTERS_H
