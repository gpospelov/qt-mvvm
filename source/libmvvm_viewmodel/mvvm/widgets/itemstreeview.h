// ************************************************************************** //
//                                                                              
//  Model-view-view-model framework for large GUI applications                  
//                                                                              
//! @authors   see AUTHORS                                                      
//! @license   GNU General Public License v3 or higher (see COPYING)            
//                                                                              
// ************************************************************************** //

#ifndef MVVM_WIDGETS_ITEMSTREEVIEW_H
#define MVVM_WIDGETS_ITEMSTREEVIEW_H

#include <mvvm/core/export.h>
#include <QWidget>
#include <memory>

class QTreeView;
class QItemSelection;
class QItemSelectionModel;

namespace ModelView
{

class SessionItem;
class AbstractViewModel;
class ViewModelDelegate;

//! Tree view to show items of SessionModel via ViewModel mechanism.
//!
//! Provides notification mechanism for SessionItem selections, use custom delegate.

class CORE_EXPORT ItemsTreeView : public QWidget
{
    Q_OBJECT

public:
    explicit ItemsTreeView(QWidget* parent = nullptr);
    ~ItemsTreeView();

    QTreeView* treeView();

    void setViewModel(std::unique_ptr<AbstractViewModel> viewModel);

    void setSelected(SessionItem* item);

    void setRootSessionItem(SessionItem* item);

    AbstractViewModel* viewModel() const;

signals:
    void itemSelected(SessionItem*);

private slots:
    void onSelectionChanged(const QItemSelection&, const QItemSelection&);

private:
    QItemSelectionModel* selectionModel();

    void set_connected(bool flag);

    QTreeView* m_treeView;
    std::unique_ptr<AbstractViewModel> m_viewModel;
    std::unique_ptr<ViewModelDelegate> m_delegate;
    bool m_block_selection;
};

} // namespace ModelView

#endif  // MVVM_WIDGETS_ITEMSTREEVIEW_H
