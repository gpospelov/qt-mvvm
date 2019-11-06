// ************************************************************************** //
//                                                                              
//  Model-view-view-model framework for large GUI applications                  
//                                                                              
//! @authors   see AUTHORS                                                      
//! @license   GNU General Public License v3 or higher (see COPYING)            
//                                                                              
// ************************************************************************** //

#include <mvvm/widgets/propertyeditor.h>
#include <mvvm/viewmodel/standardviewmodels.h>
#include <mvvm/viewmodel/viewmodeldelegate.h>
#include <mvvm/viewmodel/abstractviewmodel.h>
#include <mvvm/model/sessionitem.h>
#include <QVBoxLayout>
#include <QTreeView>

namespace  {
const QStringList labels = {"Name", "Value"};
}

using namespace ModelView;

PropertyEditor::PropertyEditor(QWidget* parent)
    : QWidget(parent), m_treeView(new QTreeView), m_delegate(std::make_unique<ViewModelDelegate>())
{
    auto layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);
    layout->addWidget(m_treeView);
    setLayout(layout);

    m_treeView->setHeaderHidden(false);
    m_treeView->setItemDelegate(m_delegate.get());
    // provide one click editing
    m_treeView->setEditTriggers(QAbstractItemView::AllEditTriggers);
    m_treeView->setAlternatingRowColors(true);

    // FIXME implement placeholder model as in ComponentTreeView to have Name/Value labels
    // displayed on emptry tree.
}

PropertyEditor::~PropertyEditor() = default;

void PropertyEditor::setItem(SessionItem* item)
{
    m_viewModel = Utils::CreatePropertyViewModel(item->model());
    m_viewModel->setRootSessionItem(item);
    m_viewModel->setHorizontalHeaderLabels(labels);
    m_treeView->setModel(m_viewModel.get());
    m_treeView->expandAll();
    m_treeView->setRootIsDecorated(false);
}

QTreeView* PropertyEditor::treeView()
{
    return m_treeView;
}
