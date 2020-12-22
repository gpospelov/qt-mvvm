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

#include "mvvm/viewmodel_export.h"
#include <QObject>

namespace ModelView {

//! Event filter to prevent loss of the focus.
//! Can be used in the context of QTreeView and similar widgets to call external editor. Such an
//! editor is created by clicking on a cell of a tree and it appears as  modal window on top of a
//! tree.

class MVVM_VIEWMODEL_EXPORT LostFocusFilter : public QObject {
    Q_OBJECT

public:
    explicit LostFocusFilter(QObject* parent = nullptr);

protected:
    bool eventFilter(QObject* obj, QEvent* event) override;
};

//! Event filter to install on combo boxes and spin boxes to ignore wheel events during scrolling.
//! Helpful than the spin box is a child of some larger scroll area.

class MVVM_VIEWMODEL_EXPORT WheelEventFilter : public QObject {
    Q_OBJECT

public:
    explicit WheelEventFilter(QObject* parent = nullptr);

protected:
    bool eventFilter(QObject* obj, QEvent* event);
};

} // namespace ModelView

#endif // MVVM_EDITORS_CUSTOMEVENTFILTERS_H
