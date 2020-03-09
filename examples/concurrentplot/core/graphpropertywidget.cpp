// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "graphpropertywidget.h"
#include "graphmodel.h"
#include "jobmanager.h"
#include <QBoxLayout>
#include <QPushButton>
#include <QSlider>
#include <mvvm/viewmodel/standardviewmodels.h>
#include <mvvm/viewmodel/viewmodel.h>
#include <mvvm/widgets/itemstreeview.h>

using namespace ModelView;

GraphPropertyWidget::GraphPropertyWidget(GraphModel* model, QWidget* parent)
    : QWidget(parent), m_slider(new QSlider), m_treeView(new ItemsTreeView), m_model(model)
{
    auto layout = new QVBoxLayout;
    layout->addWidget(m_slider);
    layout->addWidget(m_treeView);
    setLayout(layout);
    setModel(model);
    setup_slider();
}

GraphPropertyWidget::~GraphPropertyWidget() = default;

void GraphPropertyWidget::setModel(GraphModel* model)
{
    if (!model)
        return;

    m_model = model;
    job_manager = std::make_unique<JobManager>(model);

    m_treeView->setViewModel(Utils::CreateDefaultViewModel(model));
}

//! Slider to regenerate the data in the model.

void GraphPropertyWidget::setup_slider()
{
    m_slider->setOrientation(Qt::Horizontal);
    m_slider->setRange(0, 100);
    m_slider->setValue(50.0);

    auto on_value_changed = [this](int value) {
        if (job_manager)
            job_manager->requestSimulation(value);
    };
    connect(m_slider, &QSlider::valueChanged, on_value_changed);
}
