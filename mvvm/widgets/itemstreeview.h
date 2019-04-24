// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_ITEMSTREEVIEW_H
#define MVVM_ITEMSTREEVIEW_H

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
class ViewModel;
class TopItemsViewModel;
class ViewModelDelegate;

//! Tree view to show top level items of SessionModel.
//! All property items are filtered out. Provides selection mechanism.

class CORE_EXPORT ItemsTreeView : public QWidget
{
    Q_OBJECT

public:
    explicit ItemsTreeView(QWidget* parent = nullptr);
    ~ItemsTreeView();

    QTreeView* treeView();

    void setViewModel(std::unique_ptr<ViewModel> viewModel);

    void setSelected(SessionItem* item);

    void setRootSessionItem(SessionItem* item);

    ViewModel* viewModel() const;

signals:
    void itemSelected(SessionItem*);

private slots:
    void onSelectionChanged(const QItemSelection&, const QItemSelection&);

private:
    QItemSelectionModel* selectionModel();

    void set_connected(bool flag);

    QTreeView* m_treeView;
    std::unique_ptr<ViewModel> m_viewModel;
    std::unique_ptr<ViewModelDelegate> m_delegate;
    bool m_block_selection;
};

} // namespace ModelView

#endif // MVVM_ITEMSTREEVIEW_H
