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
#include <QBoxLayout>
#include <QPushButton>
#include <QSlider>
#include <mvvm/factories/viewmodelfactory.h>
#include <mvvm/widgets/itemstreeview.h>

using namespace ModelView;

namespace PlotColorMap
{

ColorMapPropertyWidget::ColorMapPropertyWidget(ColorMapModel* model, QWidget* parent)
    : QWidget(parent), m_slider(new QSlider), m_treeView(new ItemsTreeView), m_model(model)
{
    auto layout = new QVBoxLayout;
    layout->addWidget(m_slider);
    layout->addWidget(m_treeView);
    setLayout(layout);
    setModel(model);
    setup_slider();
}

void ColorMapPropertyWidget::setModel(ColorMapModel* model)
{
    if (!model)
        return;

    m_model = model;

    m_treeView->setViewModel(Factory::CreateDefaultViewModel(model));
}

//! Slider to regenerate the data in the model.

void ColorMapPropertyWidget::setup_slider()
{
    m_slider->setOrientation(Qt::Horizontal);
    m_slider->setRange(0, 100);
    m_slider->setValue(50.0);

    auto on_value_changed = [this](int value) { m_model->update_data(value / 10.0); };
    connect(m_slider, &QSlider::valueChanged, on_value_changed);
}

} // namespace PlotColorMap
