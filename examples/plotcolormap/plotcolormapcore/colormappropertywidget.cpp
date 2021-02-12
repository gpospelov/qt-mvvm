// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "colormappropertywidget.h"
#include "colormapmodel.h"
#include "mvvm/factories/viewmodelfactory.h"
#include "mvvm/widgets/itemstreeview.h"
#include <QBoxLayout>
#include <QPushButton>
#include <QSlider>

using namespace ModelView;

namespace PlotColorMap {

ColorMapPropertyWidget::ColorMapPropertyWidget(ColorMapModel* model, QWidget* parent)
    : QWidget(parent), m_slider(new QSlider), m_tree_view(new ItemsTreeView), m_model(model)
{
    auto layout = new QVBoxLayout;
    layout->addWidget(m_slider);
    layout->addWidget(m_tree_view);
    setLayout(layout);
    setModel(model);
    setupSlider();
}

void ColorMapPropertyWidget::setModel(ColorMapModel* model)
{
    if (!model)
        return;

    m_model = model;

    m_tree_view->setViewModel(Factory::CreateDefaultViewModel(model));
}

//! Slider to regenerate the data in the model.

void ColorMapPropertyWidget::setupSlider()
{
    m_slider->setOrientation(Qt::Horizontal);
    m_slider->setRange(0, 100);
    m_slider->setValue(50.0);

    auto on_value_changed = [this](int value) { m_model->updateData(value / 10.0); };
    connect(m_slider, &QSlider::valueChanged, on_value_changed);
}

} // namespace PlotColorMap
