#include "google_test.h"
#include "DesignerScene.h"
#include "item_constants.h"
#include "LayerItems.h"
#include "LayerView.h"
#include "NodeEditorConnection.h"
#include "ParticleLayoutItem.h"
#include "modelutils.h"
#include "MultiLayerView.h"
#include "SampleModel.h"

using namespace ModelView;

class TestScene : public ::testing::Test
{
public:
    TestScene();
    ~TestScene() override;

protected:
    QRectF makeFrame(QRectF bound);

    SampleModel model;
    std::unique_ptr<DesignerScene> scene;
};

TestScene::TestScene()
    : scene(std::make_unique<DesignerScene>())
{
    model.clear();
    scene->setSampleModel(&model);
}

TestScene::~TestScene() = default;

QRectF TestScene::makeFrame(QRectF bound)
{
    return QRectF(bound.left() - 0.1, bound.top() - 0.1, bound.width() + 0.2, bound.height() + 0.2);
}

TEST_F(TestScene, testSelection)
{
    auto mlayer = model.insertItem<MultiLayerItem>();
    auto layer = model.insertItem<LayerItem>(mlayer, MultiLayerItem::T_LAYERS);
    auto mview = dynamic_cast<QGraphicsItem*>(scene->getViewForItem(mlayer));
    auto lview = dynamic_cast<QGraphicsItem*>(scene->getViewForItem(layer));

    EXPECT_TRUE(mview != nullptr);
    EXPECT_TRUE(lview != nullptr);

    QPainterPath selection_path;
    selection_path.addRect(mview->sceneBoundingRect());
    scene->setSelectionArea(selection_path);

    EXPECT_TRUE(scene->selectedItems().contains(mview));
    EXPECT_TRUE(scene->selectedItems().contains(lview));

    scene->clearSelection();
    EXPECT_FALSE(scene->selectedItems().contains(mview));
    EXPECT_FALSE(scene->selectedItems().contains(lview));

    selection_path.clear();
    selection_path.addRect(makeFrame(lview->sceneBoundingRect()));
    scene->setSelectionArea(selection_path, Qt::ContainsItemShape);

    EXPECT_FALSE(scene->selectedItems().contains(mview));
    EXPECT_TRUE(scene->selectedItems().contains(lview));
}

TEST_F(TestScene, testAddingConnection)
{
    const auto mlayer = model.insertItem<MultiLayerItem>();
    const auto layer = model.insertItem<LayerItem>(mlayer, MultiLayerItem::T_LAYERS);
    const auto layout = model.insertItem<ParticleLayoutItem>();

    EXPECT_TRUE(layout->parent() == model.rootItem());

    auto connection = new NodeEditorConnection;
    scene->addItem(connection);
    connection->setPort1(
        dynamic_cast<ConnectableView*>(scene->getViewForItem(layout))->getOutputPorts()[0]);
    connection->setPort2(
        dynamic_cast<ConnectableView*>(scene->getViewForItem(layer))->getInputPorts()[0]);

    scene->onEstablishedConnection(connection);

    EXPECT_TRUE(layout->parent() == layer);
    EXPECT_TRUE(scene->getViewForItem(layout)->parentObject() != scene->getViewForItem(layer));
}

//! Tests deletion of views with model's items deletion
TEST_F(TestScene, testBasicViewDeletion)
{
    const auto mlayer = model.insertItem<MultiLayerItem>();
    const std::string mid = mlayer->identifier();
    const auto layer = model.insertItem<LayerItem>(mlayer, MultiLayerItem::T_LAYERS);
    const std::string lid = layer->identifier();

    QPainterPath selection_path;
    selection_path.addRect(makeFrame(scene->getViewForItem(layer)->sceneBoundingRect()));
    scene->setSelectionArea(selection_path, Qt::ContainsItemShape);

    scene->deleteSelectedItems();

    EXPECT_TRUE(model.findItem(mid) == mlayer);
    EXPECT_TRUE(model.findItem(lid) == nullptr);
    EXPECT_TRUE(scene->getViewForItem(mlayer) != nullptr);
    EXPECT_TRUE(scene->getViewForItem(layer) == nullptr);
}
