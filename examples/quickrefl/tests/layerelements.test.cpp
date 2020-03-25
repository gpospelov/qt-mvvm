// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "google_test.h"

#include "GraphicsScene.h"
#include "layerelementcontroller.h"
#include "layerelementitem.h"
#include "materialmodel.h"
#include "samplemodel.h"
#include "segmentelementview.h"
#include "sldelementmodel.h"

#include "test_utils.h"
#include <mvvm/viewmodel/viewmodelutils.h>

#include <QColor>
#include <QGraphicsSceneMouseEvent>
#include <QSignalSpy>

using namespace ModelView;

class LayerElementControllerFriend : public LayerElementController
{
public:
    LayerElementControllerFriend(LayerElementItem* item) : LayerElementController(item){};
    QRectF pubSideSegmentRect() const { return sideSegmentRect(); };
    QRectF pubTopSegmentRect() const { return topSegmentRect(); };
};

class SegmentElementViewFriend : public SegmentElementView
{
public:
    SegmentElementViewFriend() : SegmentElementView(){};
    QRectF rectangle() const { return m_rectangle; };
    QPen pen() const { return m_pen; };
    QBrush brush() const { return m_brush; };
};

//! Tests of LayerViewController.
class LayerElementTest : public ::testing::Test
{
public:
    ~LayerElementTest();
    struct TestData {
        LayerElementItem* exposed_layer_item{nullptr};
        LayerElementControllerFriend* exposed_controller{nullptr};

        SampleModel* sample_model{nullptr};
        MaterialModel* material_model{nullptr};
        SLDElementModel* view_model{nullptr};

        LayerElementItem* above_layer_item{nullptr};
        LayerElementItem* middle_layer_item{nullptr};
        LayerElementItem* below_layer_item{nullptr};

        LayerElementController* above_controller{nullptr};
        LayerElementController* middle_controller{nullptr};
        LayerElementController* below_controller{nullptr};

        GraphicsScene* scene{nullptr};

        TestData()
        {
            exposed_layer_item = new LayerElementItem();
            exposed_controller = new LayerElementControllerFriend(exposed_layer_item);

            sample_model = new SampleModel();
            view_model = new SLDElementModel();
            above_layer_item = view_model->addLayer();
            middle_layer_item = view_model->addLayer();
            below_layer_item = view_model->addLayer();

            above_controller = new LayerElementController(above_layer_item);
            middle_controller = new LayerElementController(middle_layer_item);
            below_controller = new LayerElementController(below_layer_item);

            scene = new GraphicsScene();
        }
    };
};

LayerElementTest::~LayerElementTest() = default;

//! Test the creation of the controller

TEST_F(LayerElementTest, initialState)
{
    TestData test_data;

    EXPECT_NE(nullptr, test_data.middle_controller->layerElementItem());
    EXPECT_EQ(nullptr, test_data.middle_controller->layerAbove());
    EXPECT_EQ(nullptr, test_data.middle_controller->layerBelow());
    EXPECT_EQ(nullptr, test_data.middle_controller->topSegment());
    EXPECT_EQ(nullptr, test_data.middle_controller->sideSegment());
    EXPECT_EQ(nullptr, test_data.middle_controller->scene());
}

TEST_F(LayerElementTest, addremoveabovebelow)
{
    TestData test_data;

    EXPECT_EQ(nullptr, test_data.above_controller->layerAbove());
    EXPECT_EQ(nullptr, test_data.above_controller->layerBelow());
    EXPECT_EQ(nullptr, test_data.middle_controller->layerAbove());
    EXPECT_EQ(nullptr, test_data.middle_controller->layerBelow());
    EXPECT_EQ(nullptr, test_data.below_controller->layerAbove());
    EXPECT_EQ(nullptr, test_data.below_controller->layerBelow());

    test_data.middle_controller->setLayerAbove(test_data.above_controller);
    EXPECT_EQ(nullptr, test_data.above_controller->layerAbove());
    EXPECT_EQ(test_data.middle_controller, test_data.above_controller->layerBelow());
    EXPECT_EQ(test_data.above_controller, test_data.middle_controller->layerAbove());
    EXPECT_EQ(nullptr, test_data.middle_controller->layerBelow());
    EXPECT_EQ(nullptr, test_data.below_controller->layerAbove());
    EXPECT_EQ(nullptr, test_data.below_controller->layerBelow());

    test_data.middle_controller->setLayerBelow(test_data.below_controller);
    EXPECT_EQ(nullptr, test_data.above_controller->layerAbove());
    EXPECT_EQ(test_data.middle_controller, test_data.above_controller->layerBelow());
    EXPECT_EQ(test_data.above_controller, test_data.middle_controller->layerAbove());
    EXPECT_EQ(test_data.below_controller, test_data.middle_controller->layerBelow());
    EXPECT_EQ(test_data.middle_controller, test_data.below_controller->layerAbove());
    EXPECT_EQ(nullptr, test_data.below_controller->layerBelow());

    test_data.middle_controller->unsetLayerAbove();
    EXPECT_EQ(nullptr, test_data.above_controller->layerAbove());
    EXPECT_EQ(nullptr, test_data.above_controller->layerBelow());
    EXPECT_EQ(nullptr, test_data.middle_controller->layerAbove());
    EXPECT_EQ(test_data.below_controller, test_data.middle_controller->layerBelow());
    EXPECT_EQ(test_data.middle_controller, test_data.below_controller->layerAbove());
    EXPECT_EQ(nullptr, test_data.below_controller->layerBelow());

    test_data.middle_controller->unsetLayerBelow();
    EXPECT_EQ(nullptr, test_data.above_controller->layerAbove());
    EXPECT_EQ(nullptr, test_data.above_controller->layerBelow());
    EXPECT_EQ(nullptr, test_data.middle_controller->layerAbove());
    EXPECT_EQ(nullptr, test_data.middle_controller->layerBelow());
    EXPECT_EQ(nullptr, test_data.below_controller->layerAbove());
    EXPECT_EQ(nullptr, test_data.below_controller->layerBelow());
}

TEST_F(LayerElementTest, testsegements)
{
    TestData test_data;

    LayerElementItem* item = test_data.exposed_controller->layerElementItem();

    item->setProperty(LayerElementItem::P_X_POS, 10.);
    item->setProperty(LayerElementItem::P_WIDTH, 20.);
    item->setProperty(LayerElementItem::P_HEIGHT, 30.);

    item->setProperty(LayerElementItem::P_SIDE_THICKNESS, 5.);
    item->setProperty(LayerElementItem::P_SIDE_BRUSH_COLOR, QColor("red"));
    item->setProperty(LayerElementItem::P_SIDE_PEN_WIDTH, 2.);
    item->setProperty(LayerElementItem::P_SIDE_PEN_COLOR, QColor("blue"));

    item->setProperty(LayerElementItem::P_TOP_THICKNESS, 5.);
    item->setProperty(LayerElementItem::P_TOP_BRUSH_COLOR, QColor("red"));
    item->setProperty(LayerElementItem::P_TOP_PEN_WIDTH, 2.);
    item->setProperty(LayerElementItem::P_TOP_PEN_COLOR, QColor("blue"));

    QRectF side_rect;
    QRectF top_rect;

    side_rect = test_data.exposed_controller->pubSideSegmentRect();
    top_rect = test_data.exposed_controller->pubTopSegmentRect();

    EXPECT_EQ(7.5, side_rect.x());
    EXPECT_EQ(0., side_rect.y());
    EXPECT_EQ(5., side_rect.width());
    EXPECT_EQ(30., side_rect.height());

    EXPECT_EQ(10., top_rect.x());
    EXPECT_EQ(27.5, top_rect.y());
    EXPECT_EQ(20., top_rect.width());
    EXPECT_EQ(5., top_rect.height());

    item->setProperty(LayerElementItem::P_X_POS, 22.);
    side_rect = test_data.exposed_controller->pubSideSegmentRect();
    top_rect = test_data.exposed_controller->pubTopSegmentRect();

    EXPECT_EQ(19.5, side_rect.x());
    EXPECT_EQ(0., side_rect.y());
    EXPECT_EQ(5., side_rect.width());
    EXPECT_EQ(30., side_rect.height());

    EXPECT_EQ(22., top_rect.x());
    EXPECT_EQ(27.5, top_rect.y());
    EXPECT_EQ(20., top_rect.width());
    EXPECT_EQ(5., top_rect.height());

    item->setProperty(LayerElementItem::P_WIDTH, 22.);
    side_rect = test_data.exposed_controller->pubSideSegmentRect();
    top_rect = test_data.exposed_controller->pubTopSegmentRect();

    EXPECT_EQ(19.5, side_rect.x());
    EXPECT_EQ(0., side_rect.y());
    EXPECT_EQ(5., side_rect.width());
    EXPECT_EQ(30., side_rect.height());

    EXPECT_EQ(22., top_rect.x());
    EXPECT_EQ(27.5, top_rect.y());
    EXPECT_EQ(22., top_rect.width());
    EXPECT_EQ(5., top_rect.height());

    item->setProperty(LayerElementItem::P_HEIGHT, 35.);
    side_rect = test_data.exposed_controller->pubSideSegmentRect();
    top_rect = test_data.exposed_controller->pubTopSegmentRect();

    EXPECT_EQ(19.5, side_rect.x());
    EXPECT_EQ(0., side_rect.y());
    EXPECT_EQ(5., side_rect.width());
    EXPECT_EQ(35., side_rect.height());

    EXPECT_EQ(22., top_rect.x());
    EXPECT_EQ(32.5, top_rect.y());
    EXPECT_EQ(22., top_rect.width());
    EXPECT_EQ(5., top_rect.height());
}

TEST_F(LayerElementTest, testsegementviewsupdate)
{
    TestData test_data;

    test_data.middle_controller->connectToModel();

    auto side_segment = new SegmentElementViewFriend();
    auto top_segment = new SegmentElementViewFriend();

    test_data.middle_controller->setSideSegment(side_segment);
    test_data.middle_controller->setTopSegment(top_segment);

    LayerElementItem* item = test_data.middle_controller->layerElementItem();

    item->setProperty(LayerElementItem::P_X_POS, 10.);
    item->setProperty(LayerElementItem::P_WIDTH, 20.);
    item->setProperty(LayerElementItem::P_HEIGHT, 30.);

    item->setProperty(LayerElementItem::P_SIDE_THICKNESS, 5.);
    item->setProperty(LayerElementItem::P_SIDE_BRUSH_COLOR, QColor("red"));
    item->setProperty(LayerElementItem::P_SIDE_PEN_WIDTH, 2.);
    item->setProperty(LayerElementItem::P_SIDE_PEN_COLOR, QColor("blue"));

    item->setProperty(LayerElementItem::P_TOP_THICKNESS, 5.);
    item->setProperty(LayerElementItem::P_TOP_BRUSH_COLOR, QColor("red"));
    item->setProperty(LayerElementItem::P_TOP_PEN_WIDTH, 2.);
    item->setProperty(LayerElementItem::P_TOP_PEN_COLOR, QColor("blue"));

    QRectF side_rect;
    QRectF top_rect;

    side_rect = side_segment->rectangle();
    top_rect = top_segment->rectangle();

    EXPECT_EQ(7.5, side_rect.x());
    EXPECT_EQ(0., side_rect.y());
    EXPECT_EQ(5., side_rect.width());
    EXPECT_EQ(30., side_rect.height());

    EXPECT_EQ(10., top_rect.x());
    EXPECT_EQ(27.5, top_rect.y());
    EXPECT_EQ(20., top_rect.width());
    EXPECT_EQ(5., top_rect.height());

    item->setProperty(LayerElementItem::P_X_POS, 22.);
    side_rect = side_segment->rectangle();
    top_rect = top_segment->rectangle();

    EXPECT_EQ(19.5, side_rect.x());
    EXPECT_EQ(0., side_rect.y());
    EXPECT_EQ(5., side_rect.width());
    EXPECT_EQ(30., side_rect.height());

    EXPECT_EQ(22., top_rect.x());
    EXPECT_EQ(27.5, top_rect.y());
    EXPECT_EQ(20., top_rect.width());
    EXPECT_EQ(5., top_rect.height());

    item->setProperty(LayerElementItem::P_WIDTH, 22.);
    side_rect = side_segment->rectangle();
    top_rect = top_segment->rectangle();

    EXPECT_EQ(19.5, side_rect.x());
    EXPECT_EQ(0., side_rect.y());
    EXPECT_EQ(5., side_rect.width());
    EXPECT_EQ(30., side_rect.height());

    EXPECT_EQ(22., top_rect.x());
    EXPECT_EQ(27.5, top_rect.y());
    EXPECT_EQ(22., top_rect.width());
    EXPECT_EQ(5., top_rect.height());

    item->setProperty(LayerElementItem::P_HEIGHT, 35.);
    side_rect = side_segment->rectangle();
    top_rect = top_segment->rectangle();

    EXPECT_EQ(19.5, side_rect.x());
    EXPECT_EQ(0., side_rect.y());
    EXPECT_EQ(5., side_rect.width());
    EXPECT_EQ(35., side_rect.height());

    EXPECT_EQ(22., top_rect.x());
    EXPECT_EQ(32.5, top_rect.y());
    EXPECT_EQ(22., top_rect.width());
    EXPECT_EQ(5., top_rect.height());
}

TEST_F(LayerElementTest, testscene)
{
    TestData test_data;

    test_data.middle_controller->setScene(test_data.scene);

    EXPECT_EQ(test_data.scene, test_data.middle_controller->scene());

    test_data.middle_controller->connectToModel();

    auto side_segment_middle = new SegmentElementViewFriend();
    auto top_segment_middle = new SegmentElementViewFriend();
    test_data.middle_controller->setSideSegment(side_segment_middle);
    test_data.middle_controller->setTopSegment(top_segment_middle);

    EXPECT_EQ(test_data.scene, side_segment_middle->scene());
    EXPECT_EQ(test_data.scene, top_segment_middle->scene());

    test_data.middle_controller->unsetScene();
    EXPECT_EQ(nullptr, side_segment_middle->scene());
    EXPECT_EQ(nullptr, top_segment_middle->scene());

    test_data.middle_controller->setScene(test_data.scene);
    EXPECT_EQ(test_data.scene, side_segment_middle->scene());
    EXPECT_EQ(test_data.scene, top_segment_middle->scene());
}

TEST_F(LayerElementTest, testpropagation)
{
    TestData test_data;

    test_data.above_controller->setScene(test_data.scene);
    test_data.middle_controller->setScene(test_data.scene);
    test_data.below_controller->setScene(test_data.scene);

    test_data.above_controller->connectToModel();
    test_data.middle_controller->connectToModel();
    test_data.below_controller->connectToModel();

    test_data.above_controller->setSampleItemId("above");
    test_data.middle_controller->setSampleItemId("middle");
    test_data.below_controller->setSampleItemId("below");

    auto side_segment_above = new SegmentElementViewFriend();
    auto top_segment_above = new SegmentElementViewFriend();
    test_data.above_controller->setSideSegment(side_segment_above);
    test_data.above_controller->setTopSegment(top_segment_above);

    auto side_segment_middle = new SegmentElementViewFriend();
    auto top_segment_middle = new SegmentElementViewFriend();
    test_data.middle_controller->setSideSegment(side_segment_middle);
    test_data.middle_controller->setTopSegment(top_segment_middle);

    auto side_segment_below = new SegmentElementViewFriend();
    auto top_segment_below = new SegmentElementViewFriend();
    test_data.below_controller->setSideSegment(side_segment_below);
    test_data.below_controller->setTopSegment(top_segment_below);

    test_data.middle_controller->setLayerAbove(test_data.above_controller);
    test_data.middle_controller->setLayerBelow(test_data.below_controller);

    LayerElementItem* item_above = test_data.above_controller->layerElementItem();
    LayerElementItem* item_middle = test_data.middle_controller->layerElementItem();
    LayerElementItem* item_below = test_data.below_controller->layerElementItem();

    // #############################################################################s
    // Test signaling for initial construction
    EXPECT_EQ(0., item_above->property(LayerElementItem::P_X_POS).toDouble());
    EXPECT_EQ(10., item_above->property(LayerElementItem::P_WIDTH).toDouble());
    EXPECT_EQ(10., item_middle->property(LayerElementItem::P_X_POS).toDouble());
    EXPECT_EQ(10., item_middle->property(LayerElementItem::P_WIDTH).toDouble());
    EXPECT_EQ(20., item_below->property(LayerElementItem::P_X_POS).toDouble());
    EXPECT_EQ(10., item_below->property(LayerElementItem::P_WIDTH).toDouble());

    // #############################################################################s
    // Test signaling for property changes
    QSignalSpy spy_ctr_above_width(test_data.above_controller,
                                   &LayerElementController::widthChanged);
    QSignalSpy spy_ctr_middle_height(test_data.middle_controller,
                                     &LayerElementController::heightChanged);

    auto mouse_move_event = new QGraphicsSceneMouseEvent();
    QList<QVariant> move_arguments;

    // Try standard x move
    mouse_move_event->setPos(QPointF(8, 0));
    side_segment_middle->mouseMoveEvent(mouse_move_event);
    move_arguments = spy_ctr_above_width.takeFirst();

    EXPECT_EQ(move_arguments.at(0).value<std::string>(), "above");
    EXPECT_EQ(move_arguments.at(1).value<double>(), 8);
    EXPECT_EQ(8., item_above->property(LayerElementItem::P_WIDTH).toDouble());
    EXPECT_EQ(8., item_middle->property(LayerElementItem::P_X_POS).toDouble());

    // Try limit x move
    mouse_move_event->setPos(QPointF(-1, 0));
    side_segment_middle->mouseMoveEvent(mouse_move_event);
    move_arguments = spy_ctr_above_width.takeFirst();

    EXPECT_EQ(move_arguments.at(0).value<std::string>(), "above");
    EXPECT_EQ(move_arguments.at(1).value<double>(), 1e-6);
    EXPECT_EQ(1e-6, item_above->property(LayerElementItem::P_WIDTH).toDouble());
    EXPECT_EQ(1e-6, item_middle->property(LayerElementItem::P_X_POS).toDouble());

    // Try standard x move
    mouse_move_event->setPos(QPointF(10, 0));
    side_segment_middle->mouseMoveEvent(mouse_move_event);
    move_arguments = spy_ctr_above_width.takeFirst();

    EXPECT_EQ(move_arguments.at(0).value<std::string>(), "above");
    EXPECT_EQ(move_arguments.at(1).value<double>(), 10);
    EXPECT_EQ(10., item_above->property(LayerElementItem::P_WIDTH).toDouble());
    EXPECT_EQ(10., item_middle->property(LayerElementItem::P_X_POS).toDouble());

    // Try standard y move
    mouse_move_event->setPos(QPointF(0, 8));
    top_segment_middle->mouseMoveEvent(mouse_move_event);
    move_arguments = spy_ctr_middle_height.takeFirst();

    EXPECT_EQ(move_arguments.at(0).value<std::string>(), "middle");
    EXPECT_EQ(move_arguments.at(1).value<double>(), 8);
    EXPECT_EQ(8., item_middle->property(LayerElementItem::P_HEIGHT).toDouble());

    // Try limit y move
    mouse_move_event->setPos(QPointF(0, -1));
    top_segment_middle->mouseMoveEvent(mouse_move_event);
    move_arguments = spy_ctr_middle_height.takeFirst();

    EXPECT_EQ(move_arguments.at(0).value<std::string>(), "middle");
    EXPECT_EQ(move_arguments.at(1).value<double>(), 0);
    EXPECT_EQ(0, item_middle->property(LayerElementItem::P_HEIGHT).toDouble());

    // Try standard y move
    mouse_move_event->setPos(QPointF(0, 10));
    top_segment_middle->mouseMoveEvent(mouse_move_event);
    move_arguments = spy_ctr_middle_height.takeFirst();

    EXPECT_EQ(move_arguments.at(0).value<std::string>(), "middle");
    EXPECT_EQ(move_arguments.at(1).value<double>(), 10);
    EXPECT_EQ(10., item_middle->property(LayerElementItem::P_HEIGHT).toDouble());
}
TEST_F(LayerElementTest, moveelements)
{
    TestData test_data;
    test_data.middle_controller->setLayerAbove(test_data.above_controller);
    test_data.middle_controller->setLayerBelow(test_data.below_controller);
}
