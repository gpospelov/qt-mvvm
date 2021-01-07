// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "modeleditorwidget.h"
#include "graphicsscene.h"
#include "graphicsview.h"
#include "propertywidget.h"
#include "samplemodel.h"
#include "sampleitems.h"
#include <QHBoxLayout>
#include <QSplitter>

using namespace ModelView;

namespace NodeEditor {

ModelEditorWidget::ModelEditorWidget(SampleModel* model, QWidget* parent)
    : QWidget(parent)
    , m_graphicsScene(new GraphicsScene(model, this))
    , m_graphicsView(new GraphicsView(m_graphicsScene, this))
    , m_splitter(new QSplitter)
    , m_propertyWidget(new PropertyWidget(model))
{
    auto layout = new QHBoxLayout(this);
    m_splitter->addWidget(m_graphicsView);
    m_splitter->addWidget(m_propertyWidget);
    m_splitter->setSizes(QList<int>() << 300 << 100);

    layout->addWidget(m_splitter);

    auto on_selection = [this](ConnectableItem* item) { m_propertyWidget->onSelectionRequest(item); };
    connect(m_graphicsScene, &GraphicsScene::connectableItemSelectionChanged, on_selection);
}

} // namespace NodeEditor
