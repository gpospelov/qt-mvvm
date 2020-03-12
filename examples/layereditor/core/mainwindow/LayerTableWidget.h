// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef LAYERTABLEWIDGET_H
#define LAYERTABLEWIDGET_H

#include <QWidget>
#include <memory>

class QTreeView;
class CustomModelDelegate;
class ApplicationModels;

namespace ModelView
{
class ViewModel;
class SessionItem;
} // namespace ModelView

/*!
@class LayerTableWidget
@brief Shows content of multi layer in a tree view in special "flat" form.
*/

class LayerTableWidget : public QWidget
{
public:
    explicit LayerTableWidget(ApplicationModels* models, QWidget* parent = nullptr);
    ~LayerTableWidget();

    void setItem(ModelView::SessionItem* multilayer);

private:
    QTreeView* m_treeView;
    std::unique_ptr<ModelView::ViewModel> m_viewModel;
    std::unique_ptr<CustomModelDelegate> m_delegate;
};

#endif // LAYERTABLEWIDGET_H
