#include "google_test.h"
#include "DesignerScene.h"
#include "item_constants.h"
#include "LayerItems.h"
#include "LayerView.h"
#include "modelutils.h"
#include "MultiLayerView.h"
#include "SampleModel.h"

using namespace ModelView;

class TestMultilayerView : public ::testing::Test
{
public:
    TestMultilayerView();
    ~TestMultilayerView() override;

protected:
    QRectF makeFrame(QRectF bound);

    SampleModel model;
    std::unique_ptr<DesignerScene> scene;
};

TestMultilayerView::TestMultilayerView()
    : scene(std::make_unique<DesignerScene>())
{
    model.clear();
    scene->setSampleModel(&model);
}

TestMultilayerView::~TestMultilayerView() = default;

QRectF TestMultilayerView::makeFrame(QRectF bound)
{
    return QRectF(bound.left() - 0.1, bound.top() - 0.1, bound.width() + 0.2, bound.height() + 0.2);
}

TEST_F(TestMultilayerView, testBoundingRectangle)
{
    auto mlayer = model.insertNewItem(::Constants::MultiLayerType);
    auto view = scene->getViewForItem(mlayer);
    EXPECT_TRUE(dynamic_cast<MultiLayerView*>(view));

    QRectF initial_bound = view->boundingRect();
    EXPECT_DOUBLE_EQ(initial_bound.left(), -115.0);
    EXPECT_DOUBLE_EQ(initial_bound.right(), 115.0);
    EXPECT_DOUBLE_EQ(initial_bound.top(), -15.0);
    EXPECT_DOUBLE_EQ(initial_bound.bottom(), 15.0);

    QRectF frame = makeFrame(view->sceneBoundingRect());
    auto item_list = scene->items(frame, Qt::ContainsItemBoundingRect);
    EXPECT_TRUE(item_list.contains(dynamic_cast<QGraphicsItem*>(view)));
}

TEST_F(TestMultilayerView, testInsertLayer)
{
    auto mlayer = model.insertNewItem(::Constants::MultiLayerType);
    const QPointF initial_pos = scene->getViewForItem(mlayer)->pos();

    auto layer = model.insertNewItem(::Constants::LayerType, mlayer, MultiLayerItem::T_LAYERS);
    auto lview = scene->getViewForItem(layer);
    auto mview = scene->getViewForItem(mlayer);

    QRectF bound = mview->boundingRect();
    EXPECT_DOUBLE_EQ(bound.left(), -115.0);
    EXPECT_DOUBLE_EQ(bound.right(), 115.0);
    EXPECT_DOUBLE_EQ(bound.top(), -51.0);
    EXPECT_DOUBLE_EQ(bound.bottom(), 51.0);

    QPointF mpos = mview->pos(); // position in parent coordinates (i.e. scene)
    EXPECT_DOUBLE_EQ(initial_pos.x(), mpos.x());
    EXPECT_DOUBLE_EQ(initial_pos.y(), mpos.y());
    EXPECT_DOUBLE_EQ(mpos.x(), mlayer->property(LocatedItem::P_X_POS).toDouble());
    EXPECT_DOUBLE_EQ(mpos.y(), mlayer->property(LocatedItem::P_Y_POS).toDouble());

    QRectF lbound = lview->boundingRect();
    EXPECT_DOUBLE_EQ(lbound.left(), -100.0);
    EXPECT_DOUBLE_EQ(lbound.right(), 100.0);
    EXPECT_DOUBLE_EQ(lbound.top(), -36.0);
    EXPECT_DOUBLE_EQ(lbound.bottom(), 36.0);

    QPointF lpos = lview->pos(); // position in parent coordinates (i.e. multilayer)
    EXPECT_DOUBLE_EQ(lpos.x(), 0.0);
    EXPECT_DOUBLE_EQ(lpos.y(), 0.0);
    EXPECT_DOUBLE_EQ(lpos.x(), layer->property(LocatedItem::P_X_POS).toDouble());
    EXPECT_DOUBLE_EQ(lpos.y(), layer->property(LocatedItem::P_Y_POS).toDouble());

    QRectF frame = makeFrame(mview->sceneBoundingRect());
    auto item_list = scene->items(frame, Qt::ContainsItemBoundingRect);
    EXPECT_TRUE(item_list.contains(dynamic_cast<QGraphicsItem*>(mview)));
    EXPECT_TRUE(item_list.contains(dynamic_cast<QGraphicsItem*>(lview)));
}

TEST_F(TestMultilayerView, testRemoveLayer)
{
    auto mlayer = model.insertNewItem(::Constants::MultiLayerType);
    auto view = scene->getViewForItem(mlayer);
    const QRectF initial_bound = view->boundingRect();
    const QPointF initial_pos = view->pos();

    auto layer = model.insertNewItem(::Constants::LayerType, mlayer, MultiLayerItem::T_LAYERS);
    Utils::DeleteItemFromModel(layer);

    view = scene->getViewForItem(mlayer); // get re-created view once again

    const QRectF bound = view->boundingRect();
    EXPECT_DOUBLE_EQ(bound.left(), initial_bound.left());
    EXPECT_DOUBLE_EQ(bound.right(), initial_bound.right());
    EXPECT_DOUBLE_EQ(bound.top(), initial_bound.top());
    EXPECT_DOUBLE_EQ(bound.bottom(), initial_bound.bottom());

    const QPointF pos = view->pos();
    EXPECT_DOUBLE_EQ(initial_pos.x(), pos.x());
    EXPECT_DOUBLE_EQ(initial_pos.y(), pos.y());
    EXPECT_DOUBLE_EQ(pos.x(), mlayer->property(LocatedItem::P_X_POS).toDouble());
    EXPECT_DOUBLE_EQ(pos.y(), mlayer->property(LocatedItem::P_Y_POS).toDouble());

    const QRectF frame = makeFrame(view->sceneBoundingRect());
    auto item_list = scene->items(frame, Qt::ContainsItemBoundingRect);
    EXPECT_TRUE(item_list.contains(dynamic_cast<QGraphicsItem*>(view)));
}

TEST_F(TestMultilayerView, testDropAreas)
{
    auto mlayer = model.insertNewItem(::Constants::MultiLayerType);
    model.insertNewItem(::Constants::LayerType, mlayer, MultiLayerItem::T_LAYERS);
    auto mview = dynamic_cast<MultiLayerView*>(scene->getViewForItem(mlayer));

    EXPECT_EQ(mview->getDropArea({0.0, 0.0}), 0);
}
