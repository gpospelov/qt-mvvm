// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "modeleditorwidget.h"
#include "itemstreeview.h"
#include "standardviewmodels.h"
#include "samplemodel.h"
#include "viewmodeldelegate.h"
#include "standardviewmodelcontrollers.h"
#include <QBoxLayout>
#include <QTreeView>
#include <QTableView>

using namespace ModelView;

class TableViewModel : public AbstractViewModel
{
public:
    TableViewModel(SessionModel* model, std::vector<std::string> labels)
        : AbstractViewModel(std::make_unique<PropertyTableViewModelController>(this, labels))
    {
        setSessionModel(model);
    }
    ~TableViewModel();
};

TableViewModel::~TableViewModel() = default;

namespace  {
std::unique_ptr<ModelView::AbstractViewModel> createHorizontalViewModel(SessionModel* model)
{
    std::vector<std::string> labels = {"a", "b", "c"};
    std::unique_ptr<AbstractViewModel> result = std::make_unique<TableViewModel>(model, labels);
    return result;
}
}

ModelEditorWidget::ModelEditorWidget(SampleModel* model, QWidget* parent)
    : QWidget(parent), m_verticalTree(new QTreeView),
      m_horizontalTree(new QTreeView), m_tableView(new QTableView), m_delegate(std::make_unique<ViewModelDelegate>())
{
    auto mainLayout = new QHBoxLayout();
    mainLayout->setSpacing(10);

    mainLayout->addLayout(create_left_layout(), 1);
    mainLayout->addLayout(create_right_layout(), 2);

    setLayout(mainLayout);
    setModel(model);
}

void ModelEditorWidget::setModel(SampleModel* model)
{
    if (!model)
        return;

    // setting up left tree
    m_verticalViewModel = Utils::CreateDefaultViewModel(model);
    m_verticalTree->setModel(m_verticalViewModel.get());
    m_verticalTree->setItemDelegate(m_delegate.get());
    m_verticalTree->expandAll();
    m_verticalTree->resizeColumnToContents(0);

    m_horizontalViewModel = createHorizontalViewModel(model);
    m_horizontalTree->setModel(m_horizontalViewModel.get());
    m_horizontalTree->setItemDelegate(m_delegate.get());
    m_horizontalTree->expandAll();
    m_horizontalTree->resizeColumnToContents(0);

}

ModelEditorWidget::~ModelEditorWidget() = default;

QBoxLayout* ModelEditorWidget::create_left_layout()
{
    auto result = new QVBoxLayout;
    result->addWidget(m_verticalTree);
    return result;
}

QBoxLayout* ModelEditorWidget::create_right_layout()
{
    auto result = new QVBoxLayout;
    result->addWidget(m_horizontalTree);
    result->addWidget(m_tableView);
    return result;
}
