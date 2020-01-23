// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MATERIALTABLEWIDGET_H
#define MATERIALTABLEWIDGET_H

#include <QWidget>
#include <memory>

namespace ModelView {
class AbstractViewModel;
class ViewModelDelegate;
}

class MaterialModel;
class MaterialTableView;
class MaterialSelectionModel;

//! Widget to hold material table (MaterialTableView) and all corresponding models and delegates.
//! Belongs to MaterialEditor.

class MaterialTableWidget : public QWidget
{
    Q_OBJECT
public:
    MaterialTableWidget(MaterialModel* material_model, QWidget* parent = nullptr);
    ~MaterialTableWidget();

    MaterialSelectionModel* selectionModel() const;

private:
    MaterialModel* material_model{nullptr};
    std::unique_ptr<ModelView::AbstractViewModel> view_model;
    MaterialSelectionModel* selection_model{nullptr};
    MaterialTableView* table_view{nullptr};
    std::unique_ptr<ModelView::ViewModelDelegate> m_delegate;
};

#endif // MATERIALTABLEWIDGET_H
