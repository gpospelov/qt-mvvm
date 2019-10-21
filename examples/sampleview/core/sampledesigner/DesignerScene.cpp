// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/SampleDesigner/DesignerScene.cpp
//! @brief     Implements class DesignerScene
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "DesignerScene.h"
#include "ConnectableView.h"
#include "DesignerHelper.h"
#include "DesignerMimeData.h"
#include "SceneModelController.h"
#include "IView.h"
#include "LayerView.h"
#include "LocatedItem.h"
#include "NodeEditor.h"
#include "NodeEditorConnection.h"
#include "SampleModel.h"
#include "SampleViewAligner.h"
#include "SampleViewFactory.h"
#include "SceneSelectionController.h"
#include "item_constants.h"
#include "modelmapper.h"
#include "modelutils.h"
#include "sessionitem.h"
#include <QGraphicsSceneMouseEvent>
#include <QItemSelection>
#include <QPainter>

using namespace ModelView;

DesignerScene::DesignerScene(SampleModel* sample_model, QObject* parent)
    : QGraphicsScene(parent)
    , m_model_control(*this, sample_model)
    , m_select_control(nullptr)
    , m_aligner(new SampleViewAligner(this))
    , m_nodeEditor(new NodeEditor(this))
{
    setSceneRect(QRectF(-800, -800, 1600, 1600));
    setBackgroundBrush(DesignerHelper::getSceneBackground());

    m_nodeEditor->install(this);
    connect(m_nodeEditor, &NodeEditor::connectionIsEstablished, this,
            [this](auto connection) { m_model_control.onConnect(connection); });
    connect(m_nodeEditor, &NodeEditor::selectionModeChangeRequest, this,
            &DesignerScene::selectionModeChangeRequest);

    updateScene();
}

DesignerScene::~DesignerScene()
{
    delete m_aligner;
}

void DesignerScene::setSelectionModel(QItemSelectionModel* model, FilterPropertyProxy*)
{
    m_select_control.reset();
    if (!model)
        return;
    m_select_control = std::make_unique<SceneSelectionController>(this, model);
    connect(this, &DesignerScene::selectionChanged, m_select_control.get(),
            &SceneSelectionController::onSceneSelectionChanged);
}

IView* DesignerScene::getViewForItem(SessionItem* item) const
{
    auto it = m_ItemToView.find(item);
    return it != m_ItemToView.end() ? it.value() : nullptr;
}

void DesignerScene::resetScene()
{
    clear();
    m_ItemToView.clear();
    m_layer_interface_line = QLineF();
}

void DesignerScene::updateScene()
{
    updateViews();
    alignViews();
}

void DesignerScene::onModelChanged()
{
    resetScene();
    updateScene();
}

void DesignerScene::onModelDestroyed()
{
    resetScene();
}

//! runs through all items recursively and updates corresponding views
void DesignerScene::updateViews()
{
    QList<SessionItem*> to_process;
    for (auto item : m_model_control.model()->rootItem()->children())
        to_process.append(item);

    while (!to_process.empty()) {
        auto item = to_process.takeFirst();
        const auto children = item->children();
        std::for_each(children.rbegin(), children.rend(), [&to_process](auto item) {
            if (item && SampleViewFactory::isValidType(item->modelType()))
                to_process.push_front(item);
        });

        addViewForItem(item);
    }
}

//! adds view for item, if it doesn't exists
void DesignerScene::addViewForItem(SessionItem *item)
{
    if (!item) {
        Q_ASSERT(item);
        return;
    }

    IView* view = getViewForItem(item);
    if (view) // view for the item already exists
        return;

    view = SampleViewFactory::createSampleView(item->modelType());
    if (!view)
        return;

    m_ItemToView[item] = view;
    view->subscribe(item);

    if (auto parent_view = getViewForItem(item->parent()))
        parent_view->addView(view);
    else
        addItem(view);
}

//! aligns SampleView's on graphical canvas
void DesignerScene::alignViews()
{
    //m_aligner->alignSample(m_sampleModel->rootItem(), QPointF(200, 800));
}

//! shows appropriate layer interface to drop while moving ILayerView
void DesignerScene::drawForeground(QPainter *painter, const QRectF & /* rect */)
{
    if (isLayerDragged()) {
        painter->setPen(QPen(Qt::darkBlue, 2, Qt::DashLine));
        painter->drawLine(m_layer_interface_line);
    }
}

//! handles drag event
//! LayerView can be dragged only over MultiLayerView
//! MultiLayerView can be dragged both, over the scene and over another MultiLayerView
void DesignerScene::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
{
    const DesignerMimeData *mimeData = checkDragEvent(event);
    if(isAcceptedByMultiLayer(mimeData, event)) {
        QGraphicsScene::dragMoveEvent(event);

    }
}

//! Hadles drop event
//! LayerView can be dropped on MultiLayerView only
//! MultiLayerView can be droped on the scene or another MultiLayerView
void DesignerScene::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    const DesignerMimeData *mimeData = checkDragEvent(event);
    if (!mimeData)
        return;

    const std::string class_name = mimeData->getClassName();
    if (isAcceptedByMultiLayer(mimeData, event)) {
        // certain views can be dropped on MultiLayer and so will be processed there
        QGraphicsScene::dropEvent(event);
    } else if (SampleViewFactory::isValidType(class_name)) {
        // other views can be dropped on canvas anywhere
        auto command = [pos = event->scenePos(), class_name](SessionModel& model) {
            SessionItem* new_item = model.insertNewItem(class_name);

            // propagating drop coordinates to SessionItem
            new_item->setProperty(LocatedItem::P_X_POS, pos.x());
            new_item->setProperty(LocatedItem::P_Y_POS, pos.y());
        };
        sendModelCommand(command);
    }
    m_model_control.executeDelayedCommand();
    adjustSceneRect();
}

//! returns proper MimeData if the object can be hadled by graphics scene
const DesignerMimeData *DesignerScene::checkDragEvent(QGraphicsSceneDragDropEvent *event)
{
    const DesignerMimeData *mimeData = qobject_cast<const DesignerMimeData *>(event->mimeData());
    if (!mimeData) {
        event->ignore();
        return nullptr;
    }
    event->setAccepted(true);
    return mimeData;
}

void DesignerScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(isLayerDragged()) {
        invalidate(); // to redraw vertical dashed line which denotes where to drag the layer
    }
    QGraphicsScene::mouseMoveEvent(event);
}

void DesignerScene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    QGraphicsScene::mouseReleaseEvent(event);
    setLayerInterfaceLine(); // removing drop area hint from the scene
    m_model_control.executeDelayedCommand();
}

//! Returns true if there is MultiLayerView nearby during drag event.
bool DesignerScene::isMultiLayerNearby(QGraphicsSceneDragDropEvent *event)
{
    QRectF rect = DesignerHelper::getDefaultMultiLayerRect();
    rect.moveCenter(event->scenePos());
    for(QGraphicsItem* item : items(rect)) {
        if (item->type() == DesignerHelper::MULTILAYER)
            return true;
    }
    return false;
}

void DesignerScene::adjustSceneRect()
{
    QRectF boundingRect = itemsBoundingRect();
    if (sceneRect().contains(boundingRect))
        return;

    boundingRect.adjust(20.0, 20.0, 20.0, 20.0);
    setSceneRect(sceneRect().united(boundingRect));
}

bool DesignerScene::isAcceptedByMultiLayer(const DesignerMimeData *mimeData, QGraphicsSceneDragDropEvent *event)
{
    if(!mimeData) return false;

    // MultiLayer can be inserted in MultiLayer
    if (mimeData->getClassName() == ::Constants::MultiLayerType && isMultiLayerNearby(event)) {
        return true;
    }

    // layer can be inserted in MultiLayer
    if (mimeData->getClassName() == ::Constants::LayerType && isMultiLayerNearby(event)) {
        return true;
    }
    return false;
}

bool DesignerScene::isLayerDragged() const
{
    ILayerView *layer = dynamic_cast<ILayerView *>(mouseGrabberItem());
    return layer && !m_layer_interface_line.isNull();
}

void DesignerScene::onSmartAlign()
{
    m_aligner->smartAlign();
}

void DesignerScene::sendModelCommand(SceneModelController::ModelCommand command)
{
    m_model_control.setDelayedCommand(command);
}
