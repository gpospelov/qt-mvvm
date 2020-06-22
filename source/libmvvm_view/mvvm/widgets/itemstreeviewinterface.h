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

#include <QWidget>
#include <mvvm/core/export.h>

class QTreeView;

namespace ModelView
{

class SessionModel;

/*!
@class ItemsTreeViewInterface
@brief Saves and restores list of SessionModel's to/from disk using json format.
*/

class MVVM_VIEW_EXPORT ItemsTreeViewInterface : public QWidget
{
public:
    virtual void setSessionModel(SessionModel* model) = 0;

    virtual QTreeView* treeView() const = 0;
};

} // namespace ModelView

#endif // MVVM_WIDGETS_ITEMSTREEVIEWINTERFACE_H
