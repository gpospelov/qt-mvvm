// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef TOPITEMSTREEVIEW_H
#define TOPITEMSTREEVIEW_H

#include "global.h"
#include <QWidget>
#include <memory>

class QTreeView;
class QItemSelection;
class QItemSelectionModel;

namespace ModelView
{

class SessionModel;
class SessionItem;
class TopItemsViewModel;
class ViewModelDelegate;

//! Tree view to show top level items of SessionModel.
//! All property items are filtered out. Provides selection mechanism.

class CORE_EXPORT TopItemsTreeView : public QWidget
{
    Q_OBJECT

public:
    explicit TopItemsTreeView(QWidget* parent = nullptr);
    ~TopItemsTreeView();

    QTreeView* treeView();

    void setModel(SessionModel* model);

    void setSelected(SessionItem* item);

signals:
    void itemSelected(SessionItem*);

private slots:
    void onSelectionChanged(const QItemSelection&, const QItemSelection&);

private:
    QItemSelectionModel* selectionModel();

    void set_connected(bool flag);

    QTreeView* m_treeView;
    std::unique_ptr<TopItemsViewModel> m_viewModel;
    std::unique_ptr<ViewModelDelegate> m_delegate;
};

} // namespace ModelView

#endif // TOPITEMSTREEVIEW_H
