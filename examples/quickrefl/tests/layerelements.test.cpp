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
#include "handleelementview.h"
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
    QRectF pubFirstSegmentHandleRect() const { return firstSegmentHandleRect(); };
    QRectF pubSecondSegmentHandleRect() const { return secondSegmentHandleRect(); };
};

class SegmentElementViewFriend : public SegmentElementView
{
public:
    SegmentElementViewFriend() : SegmentElementView(){};
    QRectF rectangle() const { return m_rectangle; };
    QPen pen() const { return m_pen; };
    QBrush brush() const { return m_brush; };
};

class HandleElementViewFriend : public HandleElementView
{
public:
    HandleElementViewFriend() : HandleElementView(){};
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

    //! Check the layer item system init
    EXPECT_NE(nullptr, test_data.middle_controller->layerElementItem());

    //! Check the layer system init
    EXPECT_EQ(nullptr, test_data.middle_controller->layerAbove());
    EXPECT_EQ(nullptr, test_data.middle_controller->layerBelow());

    //! Check the segment system init
    EXPECT_EQ(nullptr, test_data.middle_controller->topSegment());
    EXPECT_EQ(nullptr, test_data.middle_controller->sideSegment());

    //! Check the scene init
    EXPECT_EQ(nullptr, test_data.middle_controller->scene());

    //! Check the handles init
    EXPECT_EQ(nullptr, test_data.middle_controller->firstSegmentHandle());
    EXPECT_EQ(nullptr, test_data.middle_controller->secondSegmentHandle());
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

TEST_F(LayerElementTest, testsegementshandles)
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
    QRectF first_handle_rect;
    QRectF second_handle_rect;

    side_rect = test_data.exposed_controller->pubSideSegmentRect();
    top_rect = test_data.exposed_controller->pubTopSegmentRect();
    first_handle_rect = test_data.exposed_controller->pubFirstSegmentHandleRect();
    second_handle_rect = test_data.exposed_controller->pubSecondSegmentHandleRect();

    EXPECT_EQ(7.5, side_rect.x());
    EXPECT_EQ(0., side_rect.y());
    EXPECT_EQ(5., side_rect.width());
    EXPECT_EQ(30., side_rect.height());

    EXPECT_EQ(10., top_rect.x());
    EXPECT_EQ(27.5, top_rect.y());
    EXPECT_EQ(20., top_rect.width());
    EXPECT_EQ(5., top_rect.height());

    EXPECT_EQ(5., first_handle_rect.x());
    EXPECT_EQ(-5., first_handle_rect.y());
    EXPECT_EQ(10., first_handle_rect.width());
    EXPECT_EQ(10., first_handle_rect.height());

    EXPECT_EQ(5., second_handle_rect.x());
    EXPECT_EQ(25., second_handle_rect.y());
    EXPECT_EQ(10., second_handle_rect.width());
    EXPECT_EQ(10., second_handle_rect.height());

    item->setProperty(LayerElementItem::P_X_POS, 22.);
    side_rect = test_data.exposed_controller->pubSideSegmentRect();
    top_rect = test_data.exposed_controller->pubTopSegmentRect();
    first_handle_rect = test_data.exposed_controller->pubFirstSegmentHandleRect();
    second_handle_rect = test_data.exposed_controller->pubSecondSegmentHandleRect();

    EXPECT_EQ(19.5, side_rect.x());
    EXPECT_EQ(0., side_rect.y());
    EXPECT_EQ(5., side_rect.width());
    EXPECT_EQ(30., side_rect.height());

    EXPECT_EQ(22., top_rect.x());
    EXPECT_EQ(27.5, top_rect.y());
    EXPECT_EQ(20., top_rect.width());
    EXPECT_EQ(5., top_rect.height());

    EXPECT_EQ(17., first_handle_rect.x());
    EXPECT_EQ(-5., first_handle_rect.y());
    EXPECT_EQ(10., first_handle_rect.width());
    EXPECT_EQ(10., first_handle_rect.height());

    EXPECT_EQ(17., second_handle_rect.x());
    EXPECT_EQ(25., second_handle_rect.y());
    EXPECT_EQ(10., second_handle_rect.width());
    EXPECT_EQ(10., second_handle_rect.height());

    item->setProperty(LayerElementItem::P_WIDTH, 22.);
    side_rect = test_data.exposed_controller->pubSideSegmentRect();
    top_rect = test_data.exposed_controller->pubTopSegmentRect();
    first_handle_rect = test_data.exposed_controller->pubFirstSegmentHandleRect();
    second_handle_rect = test_data.exposed_controller->pubSecondSegmentHandleRect();

    EXPECT_EQ(19.5, side_rect.x());
    EXPECT_EQ(0., side_rect.y());
    EXPECT_EQ(5., side_rect.width());
    EXPECT_EQ(30., side_rect.height());

    EXPECT_EQ(22., top_rect.x());
    EXPECT_EQ(27.5, top_rect.y());
    EXPECT_EQ(22., top_rect.width());
    EXPECT_EQ(5., top_rect.height());

    EXPECT_EQ(17., first_handle_rect.x());
    EXPECT_EQ(-5., first_handle_rect.y());
    EXPECT_EQ(10., first_handle_rect.width());
    EXPECT_EQ(10., first_handle_rect.height());

    EXPECT_EQ(17., second_handle_rect.x());
    EXPECT_EQ(25., second_handle_rect.y());
    EXPECT_EQ(10., second_handle_rect.width());
    EXPECT_EQ(10., second_handle_rect.height());

    item->setProperty(LayerElementItem::P_HEIGHT, 35.);
    side_rect = test_data.exposed_controller->pubSideSegmentRect();
    top_rect = test_data.exposed_controller->pubTopSegmentRect();
    first_handle_rect = test_data.exposed_controller->pubFirstSegmentHandleRect();
    second_handle_rect = test_data.exposed_controller->pubSecondSegmentHandleRect();

    EXPECT_EQ(19.5, side_rect.x());
    EXPECT_EQ(0., side_rect.y());
    EXPECT_EQ(5., side_rect.width());
    EXPECT_EQ(35., side_rect.height());

    EXPECT_EQ(22., top_rect.x());
    EXPECT_EQ(32.5, top_rect.y());
    EXPECT_EQ(22., top_rect.width());
    EXPECT_EQ(5., top_rect.height());

    EXPECT_EQ(17., first_handle_rect.x());
    EXPECT_EQ(-5., first_handle_rect.y());
    EXPECT_EQ(10., first_handle_rect.width());
    EXPECT_EQ(10., first_handle_rect.height());

    EXPECT_EQ(17., second_handle_rect.x());
    EXPECT_EQ(30., second_handle_rect.y());
    EXPECT_EQ(10., second_handle_rect.width());
    EXPECT_EQ(10., second_handle_rect.height());
}

TEST_F(LayerElementTest, testsegementhandleviewsupdate)
{
    TestData test_data;

    // Connect the controller to the model
    test_data.middle_controller->connectToModel();

    // Set the segments
    auto side_segment = new SegmentElementViewFriend();
    auto top_segment = new SegmentElementViewFriend();
    test_data.middle_controller->setSideSegment(side_segment);
    test_data.middle_controller->setTopSegment(top_segment);

    // Set the handles
    auto first_handle = new HandleElementViewFriend();
    auto second_handle = new HandleElementViewFriend();
    test_data.middle_controller->setSegmentHandles(first_handle, second_handle);

    // Grab the item to chnage the properties
    LayerElementItem* item = test_data.middle_controller->layerElementItem();

    // Set initial values
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

    // Initi rectangle vars
    QRectF side_rect;
    QRectF top_rect;
    QRectF first_handle_rect;
    QRectF second_handle_rect;

    // #############################################################################s
    // Check initial state
    side_rect = side_segment->rectangle();
    top_rect = top_segment->rectangle();
    first_handle_rect = first_handle->rectangle();
    second_handle_rect = second_handle->rectangle();

    EXPECT_EQ(7.5, side_rect.x());
    EXPECT_EQ(0., side_rect.y());
    EXPECT_EQ(5., side_rect.width());
    EXPECT_EQ(30., side_rect.height());

    EXPECT_EQ(10., top_rect.x());
    EXPECT_EQ(27.5, top_rect.y());
    EXPECT_EQ(20., top_rect.width());
    EXPECT_EQ(5., top_rect.height());

    EXPECT_EQ(5., first_handle_rect.x());
    EXPECT_EQ(-5., first_handle_rect.y());
    EXPECT_EQ(10., first_handle_rect.width());
    EXPECT_EQ(10., first_handle_rect.height());

    EXPECT_EQ(5., second_handle_rect.x());
    EXPECT_EQ(25., second_handle_rect.y());
    EXPECT_EQ(10., second_handle_rect.width());
    EXPECT_EQ(10., second_handle_rect.height());

    // #############################################################################s
    // Test change of position
    item->setProperty(LayerElementItem::P_X_POS, 22.);
    side_rect = side_segment->rectangle();
    top_rect = top_segment->rectangle();
    first_handle_rect = first_handle->rectangle();
    second_handle_rect = second_handle->rectangle();

    EXPECT_EQ(19.5, side_rect.x());
    EXPECT_EQ(0., side_rect.y());
    EXPECT_EQ(5., side_rect.width());
    EXPECT_EQ(30., side_rect.height());

    EXPECT_EQ(22., top_rect.x());
    EXPECT_EQ(27.5, top_rect.y());
    EXPECT_EQ(20., top_rect.width());
    EXPECT_EQ(5., top_rect.height());

    EXPECT_EQ(17., first_handle_rect.x());
    EXPECT_EQ(-5., first_handle_rect.y());
    EXPECT_EQ(10., first_handle_rect.width());
    EXPECT_EQ(10., first_handle_rect.height());

    EXPECT_EQ(17., second_handle_rect.x());
    EXPECT_EQ(25., second_handle_rect.y());
    EXPECT_EQ(10., second_handle_rect.width());
    EXPECT_EQ(10., second_handle_rect.height());

    // #############################################################################s
    // Test change of width
    item->setProperty(LayerElementItem::P_WIDTH, 22.);
    side_rect = side_segment->rectangle();
    top_rect = top_segment->rectangle();
    first_handle_rect = first_handle->rectangle();
    second_handle_rect = second_handle->rectangle();

    EXPECT_EQ(19.5, side_rect.x());
    EXPECT_EQ(0., side_rect.y());
    EXPECT_EQ(5., side_rect.width());
    EXPECT_EQ(30., side_rect.height());

    EXPECT_EQ(22., top_rect.x());
    EXPECT_EQ(27.5, top_rect.y());
    EXPECT_EQ(22., top_rect.width());
    EXPECT_EQ(5., top_rect.height());

    EXPECT_EQ(17., first_handle_rect.x());
    EXPECT_EQ(-5., first_handle_rect.y());
    EXPECT_EQ(10., first_handle_rect.width());
    EXPECT_EQ(10., first_handle_rect.height());

    EXPECT_EQ(17., second_handle_rect.x());
    EXPECT_EQ(25., second_handle_rect.y());
    EXPECT_EQ(10., second_handle_rect.width());
    EXPECT_EQ(10., second_handle_rect.height());

    // #############################################################################s
    // Test propagation change of height
    item->setProperty(LayerElementItem::P_HEIGHT, 35.);
    side_rect = side_segment->rectangle();
    top_rect = top_segment->rectangle();
    first_handle_rect = first_handle->rectangle();
    second_handle_rect = second_handle->rectangle();

    EXPECT_EQ(19.5, side_rect.x());
    EXPECT_EQ(0., side_rect.y());
    EXPECT_EQ(5., side_rect.width());
    EXPECT_EQ(35., side_rect.height());

    EXPECT_EQ(22., top_rect.x());
    EXPECT_EQ(32.5, top_rect.y());
    EXPECT_EQ(22., top_rect.width());
    EXPECT_EQ(5., top_rect.height());

    EXPECT_EQ(17., first_handle_rect.x());
    EXPECT_EQ(-5., first_handle_rect.y());
    EXPECT_EQ(10., first_handle_rect.width());
    EXPECT_EQ(10., first_handle_rect.height());

    EXPECT_EQ(17., second_handle_rect.x());
    EXPECT_EQ(30., second_handle_rect.y());
    EXPECT_EQ(10., second_handle_rect.width());
    EXPECT_EQ(10., second_handle_rect.height());
}

TEST_F(LayerElementTest, testscene)
{
    TestData test_data;

    // Set and test the scene
    test_data.middle_controller->setScene(test_data.scene);
    EXPECT_EQ(test_data.scene, test_data.middle_controller->scene());

    // Connect the controller to the model
    test_data.middle_controller->connectToModel();

    // Set the segments
    auto side_segment_middle = new SegmentElementViewFriend();
    auto top_segment_middle = new SegmentElementViewFriend();
    test_data.middle_controller->setSideSegment(side_segment_middle);
    test_data.middle_controller->setTopSegment(top_segment_middle);

    // Set the handles
    auto first_handle = new HandleElementViewFriend();
    auto second_handle = new HandleElementViewFriend();
    test_data.middle_controller->setSegmentHandles(first_handle, second_handle);

    // Test automatic scene placement
    EXPECT_EQ(test_data.scene, side_segment_middle->scene());
    EXPECT_EQ(test_data.scene, top_segment_middle->scene());

    // Test scene removal
    test_data.middle_controller->unsetScene();
    EXPECT_EQ(nullptr, side_segment_middle->scene());
    EXPECT_EQ(nullptr, top_segment_middle->scene());

    // Test scene placement
    test_data.middle_controller->setScene(test_data.scene);
    EXPECT_EQ(test_data.scene, side_segment_middle->scene());
    EXPECT_EQ(test_data.scene, top_segment_middle->scene());
}

TEST_F(LayerElementTest, testpropagation)
{
    TestData test_data;

    // Set the scenes
    test_data.above_controller->setScene(test_data.scene);
    test_data.middle_controller->setScene(test_data.scene);
    test_data.below_controller->setScene(test_data.scene);

    // Connect controller to the model
    test_data.above_controller->connectToModel();
    test_data.middle_controller->connectToModel();
    test_data.below_controller->connectToModel();

    // Set the associated ids (will be model ids afterwards)
    test_data.above_controller->setSampleItemId("above");
    test_data.middle_controller->setSampleItemId("middle");
    test_data.below_controller->setSampleItemId("below");

    // Set the layer above up
    auto side_segment_above = new SegmentElementViewFriend();
    auto top_segment_above = new SegmentElementViewFriend();
    test_data.above_controller->setSideSegment(side_segment_above);
    test_data.above_controller->setTopSegment(top_segment_above);
    auto first_handle_above = new HandleElementViewFriend();
    auto second_handle_above = new HandleElementViewFriend();
    test_data.above_controller->setSegmentHandles(first_handle_above, second_handle_above);

    // Set the middle layer up
    auto side_segment_middle = new SegmentElementViewFriend();
    auto top_segment_middle = new SegmentElementViewFriend();
    test_data.middle_controller->setSideSegment(side_segment_middle);
    test_data.middle_controller->setTopSegment(top_segment_middle);
    auto first_handle_middle = new HandleElementViewFriend();
    auto second_handle_middle = new HandleElementViewFriend();
    test_data.middle_controller->setSegmentHandles(first_handle_middle, second_handle_middle);

    // Set the layer below up
    auto side_segment_below = new SegmentElementViewFriend();
    auto top_segment_below = new SegmentElementViewFriend();
    test_data.below_controller->setSideSegment(side_segment_below);
    test_data.below_controller->setTopSegment(top_segment_below);
    auto first_handle_below = new HandleElementViewFriend();
    auto second_handle_below = new HandleElementViewFriend();
    test_data.below_controller->setSegmentHandles(first_handle_below, second_handle_below);

    // Set the layer relationships
    test_data.middle_controller->setLayerAbove(test_data.above_controller);
    test_data.middle_controller->setLayerBelow(test_data.below_controller);

    // Get the items of each layer
    LayerElementItem* item_above = test_data.above_controller->layerElementItem();
    LayerElementItem* item_middle = test_data.middle_controller->layerElementItem();
    LayerElementItem* item_below = test_data.below_controller->layerElementItem();

    // #############################################################################s
    // Test propagation for the contruction
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
    EXPECT_EQ(3., first_handle_middle->rectangle().x());
    EXPECT_EQ(-5., first_handle_middle->rectangle().y());
    EXPECT_EQ(3., second_handle_middle->rectangle().x());
    EXPECT_EQ(5., second_handle_middle->rectangle().y());

    // Try limit x move
    mouse_move_event->setPos(QPointF(-1, 0));
    side_segment_middle->mouseMoveEvent(mouse_move_event);
    move_arguments = spy_ctr_above_width.takeFirst();

    EXPECT_EQ(move_arguments.at(0).value<std::string>(), "above");
    EXPECT_EQ(move_arguments.at(1).value<double>(), 1e-6);
    EXPECT_EQ(1e-6, item_above->property(LayerElementItem::P_WIDTH).toDouble());
    EXPECT_EQ(1e-6, item_middle->property(LayerElementItem::P_X_POS).toDouble());
    EXPECT_EQ(-5+1e-6, first_handle_middle->rectangle().x());
    EXPECT_EQ(-5., first_handle_middle->rectangle().y());
    EXPECT_EQ(-5+1e-6, second_handle_middle->rectangle().x());
    EXPECT_EQ(5., second_handle_middle->rectangle().y());

    // Try standard x move
    mouse_move_event->setPos(QPointF(10, 0));
    side_segment_middle->mouseMoveEvent(mouse_move_event);
    move_arguments = spy_ctr_above_width.takeFirst();

    EXPECT_EQ(move_arguments.at(0).value<std::string>(), "above");
    EXPECT_EQ(move_arguments.at(1).value<double>(), 10);
    EXPECT_EQ(10., item_above->property(LayerElementItem::P_WIDTH).toDouble());
    EXPECT_EQ(10., item_middle->property(LayerElementItem::P_X_POS).toDouble());
    EXPECT_EQ(5., first_handle_middle->rectangle().x());
    EXPECT_EQ(-5., first_handle_middle->rectangle().y());
    EXPECT_EQ(5., second_handle_middle->rectangle().x());
    EXPECT_EQ(5., second_handle_middle->rectangle().y());
    // Try standard y move
    mouse_move_event->setPos(QPointF(0, 8));
    top_segment_middle->mouseMoveEvent(mouse_move_event);
    move_arguments = spy_ctr_middle_height.takeFirst();

    EXPECT_EQ(move_arguments.at(0).value<std::string>(), "middle");
    EXPECT_EQ(move_arguments.at(1).value<double>(), 8);
    EXPECT_EQ(8., item_middle->property(LayerElementItem::P_HEIGHT).toDouble());
    EXPECT_EQ(5., first_handle_middle->rectangle().x());
    EXPECT_EQ(-5., first_handle_middle->rectangle().y());
    EXPECT_EQ(5., second_handle_middle->rectangle().x());
    EXPECT_EQ(3., second_handle_middle->rectangle().y());

    // Try limit y move
    mouse_move_event->setPos(QPointF(0, -1));
    top_segment_middle->mouseMoveEvent(mouse_move_event);
    move_arguments = spy_ctr_middle_height.takeFirst();

    EXPECT_EQ(move_arguments.at(0).value<std::string>(), "middle");
    EXPECT_EQ(move_arguments.at(1).value<double>(), 0);
    EXPECT_EQ(0, item_middle->property(LayerElementItem::P_HEIGHT).toDouble());
    EXPECT_EQ(5., first_handle_middle->rectangle().x());
    EXPECT_EQ(-5., first_handle_middle->rectangle().y());
    EXPECT_EQ(5., second_handle_middle->rectangle().x());
    EXPECT_EQ(-5., second_handle_middle->rectangle().y());

    // Try standard y move
    mouse_move_event->setPos(QPointF(0, 10));
    top_segment_middle->mouseMoveEvent(mouse_move_event);
    move_arguments = spy_ctr_middle_height.takeFirst();

    EXPECT_EQ(move_arguments.at(0).value<std::string>(), "middle");
    EXPECT_EQ(move_arguments.at(1).value<double>(), 10);
    EXPECT_EQ(10., item_middle->property(LayerElementItem::P_HEIGHT).toDouble());
    EXPECT_EQ(5., first_handle_middle->rectangle().x());
    EXPECT_EQ(-5., first_handle_middle->rectangle().y());
    EXPECT_EQ(5., second_handle_middle->rectangle().x());
    EXPECT_EQ(5., second_handle_middle->rectangle().y());
}
TEST_F(LayerElementTest, moveelements)
{
    TestData test_data;
    test_data.middle_controller->setLayerAbove(test_data.above_controller);
    test_data.middle_controller->setLayerBelow(test_data.below_controller);
}
