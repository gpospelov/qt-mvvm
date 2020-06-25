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
#include <layereditorcore/model/applicationmodels.h>
#include <layereditorcore/model/materialmodel.h>
#include <layereditorcore/model/samplemodel.h>
#include <layereditorcore/widgets/layertablewidget.h>
#include <layereditorcore/widgets/materialtablewidget.h>
#include <layereditorcore/widgets/samplewidget.h>
#include <mvvm/viewmodel/standardviewmodels.h>
#include <mvvm/widgets/itemstreeview.h>

using namespace ModelView;

SampleWidget::SampleWidget(ApplicationModels* models, QWidget* parent)
    : QWidget(parent), m_materialTree(new ItemsTreeView), m_sampleTree(new ItemsTreeView),
      m_materialTableWidget(new MaterialTableWidget(models->materialModel())),
      m_layerTableWidget(new LayerTableWidget(models)), m_models(models)
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

    m_materialTree->setViewModel(Utils::CreateDefaultViewModel(m_models->materialModel()));
    m_sampleTree->setViewModel(Utils::CreateDefaultViewModel(m_models->sampleModel()));

    result->addWidget(m_materialTree);
    result->addWidget(m_sampleTree);
    return result;
}

QBoxLayout* SampleWidget::create_bottom_layout()
{
    auto result = new QHBoxLayout;
    result->addWidget(m_materialTableWidget);
    result->addWidget(m_layerTableWidget);
    return result;
}
