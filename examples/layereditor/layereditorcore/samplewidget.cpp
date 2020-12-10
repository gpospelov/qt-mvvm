// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include <QTreeView>
#include <QVBoxLayout>
#include <layereditorcore/applicationmodels.h>
#include <layereditorcore/materialmodel.h>
#include <layereditorcore/materialtablewidget.h>
#include <layereditorcore/multilayertreeview.h>
#include <layereditorcore/samplemodel.h>
#include <layereditorcore/samplewidget.h>
#include <mvvm/factories/viewmodelfactory.h>
#include <mvvm/widgets/itemstreeview.h>

using namespace ModelView;

SampleWidget::SampleWidget(ApplicationModels* models, QWidget* parent)
    : QWidget(parent)
    , m_materialTree(new ItemsTreeView)
    , m_sampleTree(new ItemsTreeView)
    , m_materialTableWidget(new MaterialTableWidget(models->materialModel()))
    , m_multiLayerTreeView(new MultiLayerTreeView(models))
    , m_models(models)
{
    auto mainLayout = new QVBoxLayout;
    mainLayout->setSpacing(10);

    mainLayout->addLayout(create_top_layout());
    mainLayout->addLayout(create_bottom_layout());

    setLayout(mainLayout);
}

QBoxLayout* SampleWidget::create_top_layout()
{
    auto result = new QHBoxLayout;

    m_materialTree->setViewModel(Factory::CreateDefaultViewModel(m_models->materialModel()));
    m_sampleTree->setViewModel(Factory::CreateDefaultViewModel(m_models->sampleModel()));

    result->addWidget(m_materialTree);
    result->addWidget(m_sampleTree);
    return result;
}

QBoxLayout* SampleWidget::create_bottom_layout()
{
    auto result = new QHBoxLayout;
    result->addWidget(m_materialTableWidget);
    result->addWidget(m_multiLayerTreeView);
    return result;
}
