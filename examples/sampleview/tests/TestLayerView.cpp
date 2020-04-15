// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "DesignerScene.h"
#include "LayerItems.h"
#include "LayerView.h"
#include "SampleModel.h"
#include "google_test.h"
#include "item_constants.h"
#include <mvvm/model/modelutils.h>

using namespace ModelView;

class TestlayerView : public ::testing::Test
{
public:
    TestlayerView();
    ~TestlayerView() override;

protected:
    QRectF makeFrame(QRectF bound);

    SampleModel model;
    std::unique_ptr<DesignerScene> scene;
};

TestlayerView::TestlayerView() : scene(std::make_unique<DesignerScene>(&model))
{
    model.clear();
}

TestlayerView::~TestlayerView() = default;

QRectF TestlayerView::makeFrame(QRectF bound)
{
    return QRectF(bound.left() - 0.1, bound.top() - 0.1, bound.width() + 0.2, bound.height() + 0.2);
}

TEST_F(TestlayerView, testBoundingRectangle)
{
    auto layer = model.insertNewItem(::Constants::LayerType);
    auto view = scene->getViewForItem(layer);
    EXPECT_TRUE(dynamic_cast<LayerView*>(view));

    QRectF initial_bound = view->boundingRect();
    EXPECT_DOUBLE_EQ(initial_bound.left(), -100.0);
    EXPECT_DOUBLE_EQ(initial_bound.right(), 100.0);
    EXPECT_DOUBLE_EQ(initial_bound.top(), -36.0);
    EXPECT_DOUBLE_EQ(initial_bound.bottom(), 36.0);

    QRectF frame = makeFrame(view->sceneBoundingRect());
    auto item_list = scene->items(frame, Qt::ContainsItemBoundingRect);
    EXPECT_TRUE(item_list.contains(dynamic_cast<QGraphicsItem*>(view)));
}

TEST_F(TestlayerView, testChangeThickness)
{
    auto layer = model.insertNewItem(::Constants::LayerType);
    auto view = scene->getViewForItem(layer);

    double x_pos = layer->property<double>(LocatedItem::P_X_POS);
    double y_pos = layer->property<double>(LocatedItem::P_Y_POS);

    layer->setProperty(LayerItem::P_THICKNESS, 100.0);

    QRectF bound = view->boundingRect();
    EXPECT_DOUBLE_EQ(bound.left(), -100.0);
    EXPECT_DOUBLE_EQ(bound.right(), 100.0);
    EXPECT_DOUBLE_EQ(bound.top(), -65.0);
    EXPECT_DOUBLE_EQ(bound.bottom(), 65.0);

    EXPECT_DOUBLE_EQ(x_pos, layer->property<double>(LocatedItem::P_X_POS));
    EXPECT_DOUBLE_EQ(y_pos, layer->property<double>(LocatedItem::P_Y_POS));

    QRectF frame = makeFrame(view->sceneBoundingRect());
    auto item_list = scene->items(frame, Qt::ContainsItemBoundingRect);
    EXPECT_TRUE(item_list.contains(dynamic_cast<QGraphicsItem*>(view)));
}

TEST_F(TestlayerView, testMoveOnScene)
{
    auto layer = model.insertNewItem(::Constants::LayerType);
    auto view = scene->getViewForItem(layer);

    const QRectF init_bound = view->boundingRect();
    const QRectF init_scene_bound = view->sceneBoundingRect();
    const QPointF init_parent_pos = view->pos();
    const QPointF init_scene_pos = view->scenePos();

    // since the layer view is attached directly to the scene, the positions in parent and scene
    // coordinates shall coincide
    EXPECT_DOUBLE_EQ(init_parent_pos.x(), init_scene_pos.x());
    EXPECT_DOUBLE_EQ(init_parent_pos.y(), init_scene_pos.y());

    view->moveBy(1.0, 1.0); // moves the graphics object in parent coordinates

    const QRectF fin_bound = view->boundingRect();
    EXPECT_DOUBLE_EQ(init_bound.left(), fin_bound.left());
    EXPECT_DOUBLE_EQ(init_bound.top(), fin_bound.top());
    EXPECT_DOUBLE_EQ(init_bound.right(), fin_bound.right());
    EXPECT_DOUBLE_EQ(init_bound.bottom(), fin_bound.bottom());

    const QRectF fin_scene_bound = view->sceneBoundingRect();
    EXPECT_DOUBLE_EQ(init_scene_bound.left() + 1.0, fin_scene_bound.left());
    EXPECT_DOUBLE_EQ(init_scene_bound.top() + 1.0, fin_scene_bound.top());
    EXPECT_DOUBLE_EQ(init_scene_bound.right() + 1.0, fin_scene_bound.right());
    EXPECT_DOUBLE_EQ(init_scene_bound.bottom() + 1.0, fin_scene_bound.bottom());

    const QPointF fin_parent_pos = view->pos();
    EXPECT_DOUBLE_EQ(init_parent_pos.x() + 1.0, fin_parent_pos.x());
    EXPECT_DOUBLE_EQ(init_parent_pos.y() + 1.0, fin_parent_pos.y());

    const QPointF fin_scene_pos = view->scenePos();
    EXPECT_DOUBLE_EQ(init_scene_pos.x() + 1.0, fin_scene_pos.x());
    EXPECT_DOUBLE_EQ(init_scene_pos.y() + 1.0, fin_scene_pos.y());

    QRectF frame = makeFrame(view->sceneBoundingRect());
    auto item_list = scene->items(frame, Qt::ContainsItemBoundingRect);
    EXPECT_TRUE(item_list.contains(dynamic_cast<QGraphicsItem*>(view)));
}

TEST_F(TestlayerView, testPorts)
{
    auto layer = model.insertNewItem(::Constants::LayerType);
    auto view = dynamic_cast<LayerView*>(scene->getViewForItem(layer));
    auto input_ports = view->getInputPorts();
    auto output_ports = view->getOutputPorts();

    EXPECT_EQ(input_ports.size(), 1);
    EXPECT_EQ(output_ports.size(), 0);

    const QPointF pos = input_ports.front()->pos();
    const QRectF bound = view->boundingRect();
    EXPECT_DOUBLE_EQ(bound.left(), pos.x());
    EXPECT_DOUBLE_EQ((bound.top() + bound.bottom()) / 2.0, pos.y());
}
