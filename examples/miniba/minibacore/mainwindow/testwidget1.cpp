// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "testwidget1.h"
#include "ApplicationModels.h"
#include "SampleModel.h"
#include "itemstreeview.h"
#include "defaultviewmodel.h"
#include <QVBoxLayout>
#include <QTreeView>

using namespace ModelView;

TestWidget1::TestWidget1(ApplicationModels* models, QWidget* parent)
    : QWidget(parent), m_materialTree(new ItemsTreeView), m_sampleTree(new ItemsTreeView), m_models(models)
{
    auto mainLayout = new QVBoxLayout;
    mainLayout->setSpacing(10);

    mainLayout->addLayout(create_top_layout());
    mainLayout->addLayout(create_bottom_layout());

    setLayout(mainLayout);
}

QBoxLayout* TestWidget1::create_top_layout()
{
    auto result = new QHBoxLayout;

    std::unique_ptr<ModelView::ViewModel> viewModel(new ModelView::DefaultViewModel());
    viewModel->setSessionModel(m_models->sampleModel());
    m_sampleTree->setViewModel(std::move(viewModel));

    result->addWidget(m_materialTree);
    result->addWidget(m_sampleTree);

    return result;
}

QBoxLayout* TestWidget1::create_bottom_layout()
{
    auto result = new QHBoxLayout;
    result->addWidget(new QTreeView);
    result->addWidget(new QTreeView);
    return result;
}

