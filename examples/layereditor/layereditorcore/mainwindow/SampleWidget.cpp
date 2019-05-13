// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "SampleWidget.h"
#include "ApplicationModels.h"
#include "itemstreeview.h"
#include "standardviewmodels.h"
#include "MaterialTableWidget.h"
#include "LayerTableWidget.h"
#include "SampleModel.h"
#include "MaterialModel.h"
#include "sessionitem.h"
#include <QVBoxLayout>
#include <QTreeView>

using namespace ModelView;

SampleWidget::SampleWidget(ApplicationModels* models, QWidget* parent)
    : QWidget(parent), m_materialTree(new ItemsTreeView), m_sampleTree(new ItemsTreeView)
    , m_materialTableWidget(new MaterialTableWidget)
    , m_layerTableWidget(new LayerTableWidget(models))
    , m_models(models)
{
    auto mainLayout = new QVBoxLayout;
    mainLayout->setSpacing(10);

    mainLayout->addLayout(create_top_layout());
    mainLayout->addLayout(create_bottom_layout());

    setLayout(mainLayout);

    auto items = models->materialModel()->rootItem()->children();
    if (items.size())
        m_materialTableWidget->setItem(items.at(0));

    items = models->sampleModel()->rootItem()->children();
    if (items.size())
        m_layerTableWidget->setItem(items.at(0));
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

