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
#include "FilterPropertyProxy.h"
#include "GUIExamplesFactory.h"
#include "IView.h"
#include "InstrumentModel.h"
#include "ItemFactory.h"
#include "LayerView.h"
#include "NodeEditor.h"
#include "NodeEditorConnection.h"
#include "ParticleCompositionItem.h"
#include "ParticleCoreShellItem.h"
#include "ParticleItem.h"
#include "ParticleLayoutItem.h"
#include "SampleBuilderFactory.h"
#include "SampleModel.h"
#include "SampleViewAligner.h"
#include "SampleViewFactory.h"
#include "SessionGraphicsItem.h"
#include <QGraphicsSceneMouseEvent>
#include <QItemSelection>
#include <QPainter>

DesignerScene::DesignerScene(QObject *parent)
    : QGraphicsScene(parent), m_sampleModel(0), m_instrumentModel(0), m_materialModel(0),
      m_selectionModel(0), m_proxy(0),
      m_block_selection(false), m_aligner(new SampleViewAligner(this))
{
    setSceneRect(QRectF(-800, 0, 1600, 1600));
    setBackgroundBrush(DesignerHelper::getSceneBackground());

    m_nodeEditor = new NodeEditor(parent);
    m_nodeEditor->install(this);
    connect(m_nodeEditor, SIGNAL(connectionIsEstablished(NodeEditorConnection *)), this,
            SLOT(onEstablishedConnection(NodeEditorConnection *)));
    connect(m_nodeEditor, SIGNAL(selectionModeChangeRequest(int)), this,
            SIGNAL(selectionModeChangeRequest(int)));
    connect(this, SIGNAL(selectionChanged()), this, SLOT(onSceneSelectionChanged()));
}

DesignerScene::~DesignerScene()
{
    delete m_aligner;
}

void DesignerScene::setSampleModel(SampleModel *sampleModel)
{
    Q_ASSERT(sampleModel);

    if (sampleModel != m_sampleModel) {

        if (m_sampleModel) {
            disconnect(m_sampleModel, SIGNAL(modelAboutToBeReset()), this, SLOT(resetScene()));
            disconnect(m_sampleModel, SIGNAL(rowsInserted(QModelIndex, int, int)), this,
                       SLOT(onRowsInserted(QModelIndex, int, int)));
            disconnect(m_sampleModel, SIGNAL(rowsAboutToBeRemoved(QModelIndex, int, int)), this,
                       SLOT(onRowsAboutToBeRemoved(QModelIndex, int, int)));
            disconnect(m_sampleModel, SIGNAL(rowsRemoved(QModelIndex, int, int)), this,
                       SLOT(onRowsRemoved(QModelIndex, int, int)));
            disconnect(m_sampleModel, SIGNAL(modelReset()), this, SLOT(updateScene()));
        }

        m_sampleModel = sampleModel;

        connect(m_sampleModel, SIGNAL(modelAboutToBeReset()), this, SLOT(resetScene()));
        connect(m_sampleModel, SIGNAL(rowsInserted(QModelIndex, int, int)), this,
                SLOT(onRowsInserted(QModelIndex, int, int)));
        connect(m_sampleModel, SIGNAL(rowsAboutToBeRemoved(QModelIndex, int, int)), this,
                SLOT(onRowsAboutToBeRemoved(QModelIndex, int, int)));
        connect(m_sampleModel, SIGNAL(rowsRemoved(QModelIndex, int, int)), this,
                SLOT(onRowsRemoved(QModelIndex, int, int)));
        connect(m_sampleModel, SIGNAL(modelReset()), this, SLOT(updateScene()));

        resetScene();
        updateScene();
    }
}

void DesignerScene::setInstrumentModel(InstrumentModel *instrumentModel)
{
    m_instrumentModel = instrumentModel;
}

void DesignerScene::setMaterialModel(MaterialModel* materialModel)
{
    m_materialModel = materialModel;
}

void DesignerScene::setSelectionModel(QItemSelectionModel *model, FilterPropertyProxy *proxy)
{
    Q_ASSERT(model);

    if (model != m_selectionModel) {

        if (m_selectionModel) {
            disconnect(m_selectionModel, SIGNAL(selectionChanged(QItemSelection, QItemSelection)),
                       this, SLOT(onSessionSelectionChanged(QItemSelection, QItemSelection)));
        }

        m_selectionModel = model;
        m_proxy = proxy;

        connect(m_selectionModel, SIGNAL(selectionChanged(QItemSelection, QItemSelection)), this,
                SLOT(onSessionSelectionChanged(QItemSelection, QItemSelection)));
    }
}

IView *DesignerScene::getViewForItem(SessionItem *item)
{
    auto it = m_ItemToView.find(item);
    if(it != m_ItemToView.end()) {
        return it.value();
    }
    return nullptr;
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

void DesignerScene::onRowsInserted(const QModelIndex & /* parent */, int /* first */,
                                   int /* last */)
{
    updateScene();
}

void DesignerScene::onRowsRemoved(const QModelIndex & /* parent */, int /* first */, int /* last */)
{
    updateScene();
}

void DesignerScene::onRowsAboutToBeRemoved(const QModelIndex &parent, int first, int last)
{
    m_block_selection = true;
    for (int irow = first; irow <= last; ++irow) {
        QModelIndex itemIndex = m_sampleModel->index(irow, 0, parent);
        deleteViews(itemIndex); // deleting all child items
    }
    m_block_selection = false;
}

//! propagate selection from model to scene
void DesignerScene::onSessionSelectionChanged(const QItemSelection & /* selected */,
                                              const QItemSelection & /* deselected */)
{
    if (m_block_selection)
        return;

    m_block_selection = true;

    for (QMap<SessionItem *, IView *>::iterator it = m_ItemToView.begin();
         it != m_ItemToView.end(); ++it) {
        QModelIndex index = m_proxy->mapFromSource(m_sampleModel->indexOfItem(it.key()));
        if (index.isValid()) {
            if (m_selectionModel->isSelected(index)) {
                it.value()->setSelected(true);
            } else {
                it.value()->setSelected(false);
            }
        }
    }

    m_block_selection = false;
}

//! propagate selection from scene to model
void DesignerScene::onSceneSelectionChanged()
{
    if (m_block_selection)
        return;

    m_block_selection = true;

    m_selectionModel->clearSelection();
    QList<QGraphicsItem *> selected = selectedItems();
    for (int i = 0; i < selected.size(); ++i) {
        IView *view = dynamic_cast<IView *>(selected[i]);
        if (view) {
            SessionItem *sampleItem = view->getItem();
            QModelIndex itemIndex = m_sampleModel->indexOfItem(sampleItem);
            Q_ASSERT(itemIndex.isValid());
            if (!m_selectionModel->isSelected(m_proxy->mapFromSource(itemIndex)))
                m_selectionModel->select(m_proxy->mapFromSource(itemIndex), QItemSelectionModel::Select);
        }
    }

    m_block_selection = false;
}

//! runs through all items recursively and updates corresponding views
void DesignerScene::updateViews(const QModelIndex &parentIndex, IView *parentView)
{
    Q_ASSERT(m_sampleModel);

    IView *childView(0);
    int childCount = 0;
    for (int i_row = 0; i_row < m_sampleModel->rowCount(parentIndex); ++i_row) {
        QModelIndex itemIndex = m_sampleModel->index(i_row, 0, parentIndex);

        if (SessionItem *item = m_sampleModel->itemForIndex(itemIndex)) {

            if(item && !SampleViewFactory::isValidType(item->modelType()))
                    continue;

            childView = addViewForItem(item);
            if (childView) {
                if (parentView)
                    parentView->addView(childView, childCount++);
            }

        }

        updateViews(itemIndex, childView);
    }
}

//! adds view for item, if it doesn't exists
IView *DesignerScene::addViewForItem(SessionItem *item)
{
    Q_ASSERT(item);

    IView *view = getViewForItem(item);

    if (!view) {
        view = SampleViewFactory::createSampleView(item->modelType());
        if (view) {
            m_ItemToView[item] = view;
            view->setParameterizedItem(item);
            addItem(view);
            return view;
        }
    } else {
        // view for item exists
    }
    return view;
}

//! aligns SampleView's on graphical canvas
void DesignerScene::alignViews()
{
    m_aligner->alignSample(QModelIndex(), QPointF(200, 800));
}

//! runs recursively through model's item and schedules view removal
void DesignerScene::deleteViews(const QModelIndex &viewIndex)
{
    for (int i_row = 0; i_row < m_sampleModel->rowCount(viewIndex); ++i_row) {
        QModelIndex itemIndex = m_sampleModel->index(i_row, 0, viewIndex);

        if (SessionItem *item = m_sampleModel->itemForIndex(itemIndex)) {
            removeItemViewFromScene(item);

        } else {
            // not a parameterized graphics item
        }
        deleteViews(itemIndex);
    }
    removeItemViewFromScene(m_sampleModel->itemForIndex(viewIndex)); // deleting view itself
}

//! removes view from scene corresponding to given item
void DesignerScene::removeItemViewFromScene(SessionItem *item)
{
    Q_ASSERT(item);

    for (QMap<SessionItem *, IView *>::iterator it = m_ItemToView.begin();
         it != m_ItemToView.end(); ++it) {
        if (it.key() == item) {
            IView *view = it.value();
            view->setSelected(false);
            m_ItemToView.erase(it);
            emit view->aboutToBeDeleted();
            view->deleteLater();
//            delete view;
            update();
            break;
        }
    }
}

//! propagates deletion of views on the scene to the model
void DesignerScene::deleteSelectedItems()
{
    QModelIndexList indexes = m_selectionModel->selectedIndexes();

    QList<IView *> views_which_will_be_deleted;
    for(auto index : indexes) {
        views_which_will_be_deleted.append(m_ItemToView[m_sampleModel->itemForIndex(m_proxy->mapToSource(index))]);
    }
    // deleting selected items on model side, corresponding views will be deleted automatically
    // Since we don't know the order of items and their parent/child relationship, we need this
    while (indexes.size()) {
        QModelIndex current = m_proxy->mapToSource(indexes.back());
        m_sampleModel->removeRows(current.row(), 1, current.parent());
        indexes = m_selectionModel->selectedIndexes();
    }
    // Connections will be deleted automatically if one of connected views has been deleted.
    // For the moment, we have to delete connections which are: 1) were selected 2) Do not connect
    // views scheduled for deletion.
    for(auto graphicsItem : selectedItems()) {
        if (NodeEditorConnection *connection = dynamic_cast<NodeEditorConnection *>(graphicsItem)) {
            if (views_which_will_be_deleted.contains(connection->getParentView())
                || views_which_will_be_deleted.contains(connection->getChildView()))
                continue;
            removeConnection(connection);
        }
    }
}

//! shows appropriate layer interface to drop while moving ILayerView
void DesignerScene::drawForeground(QPainter *painter, const QRectF & /* rect */)
{
    if (isLayerDragged()) {
        painter->setPen(QPen(Qt::darkBlue, 2, Qt::DashLine));
        painter->drawLine(m_layer_interface_line);
    }
}

//! propagates connection established by NodeEditor to the model
void DesignerScene::onEstablishedConnection(NodeEditorConnection *connection)
{
    ConnectableView *parentView = connection->getParentView();
    ConnectableView *childView = connection->getChildView();

    QString tag;
    if (connection->getParentView()->getItem()->modelType() == Constants::ParticleLayoutType) {
        if (connection->inputPort()->getPortType() == NodeEditorPort::INTERFERENCE)
            tag = ParticleLayoutItem::T_INTERFERENCE;
    }
    else if (connection->getParentView()->getItem()->modelType() == Constants::ParticleCoreShellType) {
        if (parentView->getInputPortIndex(connection->inputPort()) == 0)
            tag = ParticleCoreShellItem::T_CORE;
        else if (parentView->getInputPortIndex(connection->inputPort()) == 1)
            tag = ParticleCoreShellItem::T_SHELL;
        else if (connection->inputPort()->getPortType() == NodeEditorPort::TRANSFORMATION)
            tag = ParticleItem::T_TRANSFORMATION;

    } else if (connection->getParentView()->getItem()->modelType() == Constants::ParticleCompositionType) {
        if (connection->inputPort()->getPortType() == NodeEditorPort::TRANSFORMATION)
            tag = ParticleItem::T_TRANSFORMATION;
    } else if (connection->getParentView()->getItem()->modelType() == Constants::MesoCrystalType) {
        if (connection->inputPort()->getPortType() == NodeEditorPort::TRANSFORMATION)
            tag = ParticleItem::T_TRANSFORMATION;
    }
    delete connection; // deleting just created connection because it will be recreated from the
                       // model
    m_sampleModel->moveItem(childView->getItem(),
                                         parentView->getItem(), -1, tag);
}

//! propagates break of connection between views on scene to the model
void DesignerScene::removeConnection(NodeEditorConnection *connection)
{
    IView *childView = dynamic_cast<IView *>(connection->outputPort()->parentItem());
    m_sampleModel->moveItem(childView->getItem(), 0);
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
    if (mimeData) {

        // to have possibility to drop MultiLayer on another MultiLayer
        // * edit function DesignerScene::isAcceptedByMultiLayer
        // * edit MultiLayerItem for addToValidChildren
        // * remove method MultiLayerView::itemChange

        if(isAcceptedByMultiLayer(mimeData, event)) {
            // certain views can be dropped on MultiLayer and so will be processed there
            QGraphicsScene::dropEvent(event);

        } else {
            // other views can be dropped on canvas anywhere
            if (SampleViewFactory::isValidType(mimeData->getClassName())) {

                SessionItem *new_item(0);
                if (mimeData->getClassName().startsWith(Constants::FormFactorType)) {
                    new_item = m_sampleModel->insertNewItem(Constants::ParticleType);
                    QString ffName = mimeData->getClassName();
                    ffName.remove(Constants::FormFactorType);
                    new_item->setGroupProperty(ParticleItem::P_FORM_FACTOR, ffName);

                } else {
                    new_item = m_sampleModel->insertNewItem(mimeData->getClassName());
                }

                // propagating drop coordinates to SessionItem
                QRectF boundingRect = DesignerHelper::getDefaultBoundingRect(new_item->modelType());
                new_item->setItemValue(SessionGraphicsItem::P_XPOS,
                                                event->scenePos().x() - boundingRect.width() / 2);
                new_item->setItemValue(SessionGraphicsItem::P_YPOS,
                                                event->scenePos().y() - boundingRect.height() / 2);

            } else if (GUIExamplesFactory::isValidExampleName(mimeData->getClassName())) {
                SessionItem *topItem = GUIExamplesFactory::createSampleItems(
                    mimeData->getClassName(), m_sampleModel, m_materialModel);
                QRectF boundingRect = DesignerHelper::getDefaultBoundingRect(topItem->modelType());
                QPointF reference(event->scenePos().x() - boundingRect.width() / 2,
                                  event->scenePos().y() - boundingRect.height() / 2);
                m_aligner->alignSample(topItem, reference, true);
            }
            adjustSceneRect();
        }
    }
}

//! returns proper MimeData if the object can be hadled by graphics scene
const DesignerMimeData *DesignerScene::checkDragEvent(QGraphicsSceneDragDropEvent *event)
{
    const DesignerMimeData *mimeData = qobject_cast<const DesignerMimeData *>(event->mimeData());
    if (!mimeData) {
        event->ignore();
        return 0;
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

//    // MultiLayer can be inserted in MultiLayer
//    if (mimeData->getClassName() == Constants::MultiLayerType && isMultiLayerNearby(event)) {
//        return true;
//    }

    // layer can be inserted in MultiLayer
    if (mimeData->getClassName() == Constants::LayerType && isMultiLayerNearby(event)) {
        return true;
    }
    return false;
}

bool DesignerScene::isLayerDragged() const
{
    ILayerView *layer = dynamic_cast<ILayerView *>(mouseGrabberItem());
    if (layer && !m_layer_interface_line.isNull()) {
        return true;
    }
    return false;
}

void DesignerScene::onSmartAlign()
{
    m_aligner->smartAlign();
}
