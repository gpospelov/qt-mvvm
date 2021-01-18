// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "propertywidget.h"
#include "sampleitems.h"
#include "samplemodel.h"
#include "mvvm/widgets/standardtreeviews.h"
#include <QSplitter>
#include <QVBoxLayout>
#include <QTreeView>

namespace NodeEditor {

PropertyWidget::PropertyWidget(SampleModel* model, QWidget* parent)
    : QWidget(parent)
    , m_model(model)
    , m_topItemsTree(new ModelView::TopItemsTreeView(model))
    , m_propertyTree(new ModelView::PropertyTreeView)
    , m_splitter(new QSplitter)

{
    auto layout = new QVBoxLayout(this);
    m_splitter->setOrientation(Qt::Vertical);
    m_splitter->addWidget(m_topItemsTree);
    m_splitter->addWidget(m_propertyTree);
    m_splitter->setSizes(QList<int>() << 300 << 200);
    layout->addWidget(m_splitter);

    layout->setContentsMargins(3, 0, 3, 0);

    m_topItemsTree->treeView()->setHeaderHidden(true);
}

//! Process selection request.

void PropertyWidget::onSelectionRequest(ConnectableItem* item)
{
    m_topItemsTree->setSelected(item);
    m_propertyTree->setItem(item);
}

} // namespace NodeEditor
