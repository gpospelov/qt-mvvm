// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MATERIALEDITORWIDGET_H
#define MATERIALEDITORWIDGET_H

#include <QWidget>
#include <memory>

namespace ModelView {
class AbstractViewModel;
class ViewModelDelegate;
}

class MaterialModel;
class MaterialTableView;
class MaterialTreeView;
class MaterialSelectionModel;

//! Widget to hold material table (MaterialTreeView) and all corresponding models and delegates.
//! Belongs to MaterialEditor.

class MaterialEditorWidget : public QWidget
{
    Q_OBJECT
public:
    MaterialEditorWidget(MaterialModel* material_model, QWidget* parent = nullptr);
    ~MaterialEditorWidget();

    MaterialSelectionModel* selectionModel() const;

private:
    MaterialModel* material_model{nullptr};
    std::unique_ptr<ModelView::AbstractViewModel> view_model;
    MaterialSelectionModel* selection_model{nullptr};
    MaterialTreeView* table_view{nullptr};
    std::unique_ptr<ModelView::ViewModelDelegate> m_delegate;
};

#endif // MATERIALEDITORWIDGET_H
