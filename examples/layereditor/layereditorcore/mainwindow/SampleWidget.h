// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef SAMPLEWIDGET_H
#define SAMPLEWIDGET_H

#include <QWidget>

class ApplicationModels;
class QBoxLayout;
class MaterialTableWidget;
class LayerTableWidget;

namespace ModelView
{
class ItemsTreeView;
}


/*!
@class SampleWidget
@brief Main widget with material and layer editors.
*/

class SampleWidget : public QWidget
{
    Q_OBJECT
public:
    SampleWidget(ApplicationModels* models, QWidget* parent = nullptr);

private:
    QBoxLayout* create_top_layout();
    QBoxLayout* create_bottom_layout();

    ModelView::ItemsTreeView* m_materialTree;
    ModelView::ItemsTreeView* m_sampleTree;
    MaterialTableWidget* m_materialTableWidget;
    LayerTableWidget* m_layerTableWidget;

    ApplicationModels* m_models;
};

#endif // SAMPLEWIDGET_H
