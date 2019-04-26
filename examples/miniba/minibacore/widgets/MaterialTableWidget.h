// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MATERIALTABLEWIDGETS_H
#define MATERIALTABLEWIDGETS_H

#include "mvvm_global.h"
#include <QWidget>
#include <memory>

class QTreeView;

namespace ModelView
{
class AbstractViewModel;
class ViewModelDelegate;
class SessionItem;
} // namespace ModelView

class CORE_EXPORT MaterialTableWidget : public QWidget
{
public:
    explicit MaterialTableWidget(QWidget* parent = nullptr);
    ~MaterialTableWidget();

    void setItem(ModelView::SessionItem* container);

    QTreeView* treeView();

private:
    QTreeView* m_treeView;
    std::unique_ptr<ModelView::AbstractViewModel> m_viewModel;
    std::unique_ptr<ModelView::ViewModelDelegate> m_delegate;
};

#endif
