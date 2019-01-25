// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "testwidget2.h"
#include "viewitem.h"
#include "viewmodel.h"
#include "sessionmodel.h"
#include "toy_includes.h"
#include <QTreeView>
#include <QVBoxLayout>

using namespace ModelView;

TestWidget2::TestWidget2(QWidget* parent)
    : QWidget(parent), m_treeView(new QTreeView), m_viewModel(new ViewModel(this))
    , m_sessionModel(new ToyItems::SampleModel)
{
    auto layout = new QVBoxLayout;
    layout->addWidget(m_treeView);
    setLayout(layout);

    init_session_model();
    m_viewModel->setSessionModel(m_sessionModel.get());
    m_treeView->setModel(m_viewModel);
}

TestWidget2::~TestWidget2() = default;

//! Inits session model with some test content.

void TestWidget2::init_session_model()
{
    auto multi_layer = m_sessionModel->insertNewItem(ToyItems::Constants::MultiLayerType);
    m_sessionModel->insertNewItem(ToyItems::Constants::LayerType, multi_layer);
}
