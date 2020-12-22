// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_WIDGETS_ITEMSTREEVIEWINTERFACE_H
#define MVVM_WIDGETS_ITEMSTREEVIEWINTERFACE_H

#include "mvvm/view_export.h"
#include <QWidget>

class QTreeView;

namespace ModelView {

class SessionModel;

//! Saves and restores list of SessionModel's to/from disk using json format.

class MVVM_VIEW_EXPORT ItemsTreeViewInterface : public QWidget {
    Q_OBJECT

public:
    virtual void setSessionModel(SessionModel* model) = 0;

    virtual QTreeView* treeView() const = 0;
};

} // namespace ModelView

#endif // MVVM_WIDGETS_ITEMSTREEVIEWINTERFACE_H
