// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef SAMPLEWIDGET_H
#define SAMPLEWIDGET_H

#include <QWidget>

class ApplicationModels;
class QBoxLayout;
class MaterialTableWidget;
class MultiLayerTreeView;

namespace ModelView
{
class ItemsTreeView;
}

//! Main widget with material and layer editors.

class SampleWidget : public QWidget
{
    Q_OBJECT

public:
    SampleWidget(ApplicationModels* models, QWidget* parent = nullptr);

private:
    QBoxLayout* create_top_layout();
    QBoxLayout* create_bottom_layout();

    ModelView::ItemsTreeView* m_materialTree{nullptr};
    ModelView::ItemsTreeView* m_sampleTree{nullptr};
    MaterialTableWidget* m_materialTableWidget{nullptr};
    MultiLayerTreeView* m_multiLayerTreeView{nullptr};
    ApplicationModels* m_models{nullptr};
};

#endif // SAMPLEWIDGET_H
