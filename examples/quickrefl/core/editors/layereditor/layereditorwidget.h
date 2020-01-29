// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef LAYEREDITORWIDGET_H
#define LAYEREDITORWIDGET_H

#include <QWidget>
#include <memory>

namespace ModelView
{
class ViewModelDelegate;
} // namespace ModelView

class SampleModel;
class LayerTreeView;
class LayerSelectionModel;
class LayerViewModel;

//! Widget to hold layer tree (LayerTreeView) and all corresponding models and delegates.
//! Belongs to LayerEditor.

class LayerEditorWidget : public QWidget
{
    Q_OBJECT
public:
    LayerEditorWidget(SampleModel* sample_model, QWidget* parent = nullptr);
    ~LayerEditorWidget();

    LayerSelectionModel* selectionModel() const;

private:
    SampleModel* sample_model{nullptr};
    std::unique_ptr<LayerViewModel> view_model;
    LayerSelectionModel* selection_model{nullptr};
    LayerTreeView* layer_view{nullptr};
    std::unique_ptr<ModelView::ViewModelDelegate> m_delegate;
};

#endif // LAYEREDITORWIDGET_H
