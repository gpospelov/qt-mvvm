// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "MaterialTableWidget.h"
#include "CustomCellDecoration.h"
#include "MaterialTableViewModel.h"
#include "sessionitem.h"
#include "viewmodeldelegate.h"
#include "MaterialModel.h"
#include <QTreeView>
#include <QVBoxLayout>

using namespace ModelView;

MaterialTableWidget::MaterialTableWidget(MaterialModel* material_model, QWidget* parent)
    : QWidget(parent), m_treeView(new QTreeView), m_delegate(std::make_unique<ViewModelDelegate>())
{
    m_delegate->setCellDecoration(std::make_unique<CustomCellDecoration>());

    auto layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(m_treeView);
    setLayout(layout);

    m_treeView->setHeaderHidden(false);
    m_treeView->setItemDelegate(m_delegate.get());
    m_treeView->setEditTriggers(QAbstractItemView::AllEditTriggers); // provide one click editing
    m_treeView->setAlternatingRowColors(true);

    // Accessing to the material container
    // FIXME implement equivalent of SessionModel::topItem
    auto items = material_model->rootItem()->children();
    if (items.size())
        setItem(items.at(0));
}

void MaterialTableWidget::setItem(SessionItem* material_container)
{
    m_viewModel = std::make_unique<MaterialTableViewModel>(material_container->model());
    m_viewModel->setRootSessionItem(material_container);
    m_treeView->setModel(m_viewModel.get());
    m_treeView->expandAll();
    m_treeView->setRootIsDecorated(false);
    m_treeView->resizeColumnToContents(1);
}

MaterialTableWidget::~MaterialTableWidget() = default;
