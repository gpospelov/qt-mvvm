// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "propertyeditor.h"
#include "propertyviewmodel.h"
#include "viewmodeldelegate.h"
#include "sessionitem.h"
#include "sessionmodel.h"
#include <QVBoxLayout>
#include <QTreeView>

using namespace ModelView;

PropertyEditor::PropertyEditor(QWidget* parent)
    : QWidget(parent), m_treeView(new QTreeView)
{
    auto layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(m_treeView);
    setLayout(layout);
}

void PropertyEditor::setItem(SessionItem* item)
{
    m_viewModel = std::make_unique<PropertyViewModel>();
    m_viewModel->setSessionModel(item->model());
    m_viewModel->setRootSessionItem(item);

    m_delegate = std::make_unique<ViewModelDelegate>();

    m_treeView->setModel(m_viewModel.get());
    m_treeView->setItemDelegate(m_delegate.get());
}
