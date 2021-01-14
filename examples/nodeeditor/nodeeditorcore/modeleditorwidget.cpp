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
#include "graphicsscenecontroller.h"
#include "graphicsview.h"
#include "propertywidget.h"
#include "sampleitems.h"
#include "samplemodel.h"
#include <QHBoxLayout>
#include <QSplitter>

using namespace ModelView;

namespace NodeEditor {

ModelEditorWidget::ModelEditorWidget(SampleModel* model, QWidget* parent)
    : QWidget(parent)
    , m_propertyWidget(new PropertyWidget(model, this))
    , m_graphicsScene(new GraphicsScene(model, this))
    , m_graphicsView(new GraphicsView(m_graphicsScene, this))
    , m_sceneContoller(std::make_unique<GraphicsSceneController>(model, m_graphicsScene))
    , m_splitter(new QSplitter)
{
    auto layout = new QHBoxLayout(this);
    m_splitter->addWidget(m_graphicsView);
    m_splitter->addWidget(m_propertyWidget);
    m_splitter->setSizes(QList<int>() << 300 << 100);

    layout->addWidget(m_splitter);

    initConnections();
}

ModelEditorWidget::~ModelEditorWidget() = default;

//! Inist widget connections.

void ModelEditorWidget::initConnections()
{
    // Propagates selection from the scene to the property widget.
    connect(m_graphicsScene, &GraphicsScene::connectableItemSelectionChanged, m_propertyWidget,
            &PropertyWidget::onSelectionRequest);

    // Propagates delete request from the graphics view to the scene.
    connect(m_graphicsView, &GraphicsView::deleteSelectedRequest, m_graphicsScene,
            &GraphicsScene::onDeleteSelectedRequest);
}

} // namespace NodeEditor
