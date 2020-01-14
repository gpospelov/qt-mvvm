// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_EDITORS_CUSTOMEVENTFILTERS_H
#define MVVM_EDITORS_CUSTOMEVENTFILTERS_H

#include <QObject>
#include <mvvm/core/export.h>

namespace ModelView
{

//! Event filter to prevent lost of focus by custom material editor.

class CORE_EXPORT LostFocusFilter : public QObject
{
    Q_OBJECT
public:
    LostFocusFilter(QObject* parent = nullptr);

protected:
    bool eventFilter(QObject* obj, QEvent* event) override;
};

} // namespace ModelView

#endif // MVVM_EDITORS_CUSTOMEVENTFILTERS_H
