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
#include "roughnesselementview.h"
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
    QPainterPath pubLeftRoughnessPath() const { return leftRoughnessPath(); };
    QPainterPath pubRightRoughnessPath() const { return rightRoughnessPath(); };
    QRectF pubLeftRoughnessHandleRect() const { return leftRoughnessHandleRect(); };
    QRectF pubRightRoughnessHandleRect() const { return rightRoughnessHandleRect(); };
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

class RoughnessElementViewFriend : public RoughnessElementView
{
public:
    RoughnessElementViewFriend() : RoughnessElementView(){};
    QPainterPath leftPath() const { return m_left_path; };
    QPainterPath rightPath() const { return m_right_path; };
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

TEST_F(LayerElementTest, initialstate)
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

    //! Check the roughness init
    EXPECT_EQ(nullptr, test_data.middle_controller->roughness());

    //! Check the roughness handles init
    EXPECT_EQ(nullptr, test_data.middle_controller->leftRoughnessHandle());
    EXPECT_EQ(nullptr, test_data.middle_controller->rightRoughnessHandle());
}

TEST_F(LayerElementTest, autopopulate)
{
    TestData test_data;
    test_data.middle_controller->autoPopulate();

    //! Check the layer item system init
    EXPECT_NE(nullptr, test_data.middle_controller->layerElementItem());

    //! Check the layer system init
    EXPECT_EQ(nullptr, test_data.middle_controller->layerAbove());
    EXPECT_EQ(nullptr, test_data.middle_controller->layerBelow());

    //! Check the segment system init
    EXPECT_NE(nullptr, test_data.middle_controller->topSegment());
    EXPECT_NE(nullptr, test_data.middle_controller->sideSegment());

    //! Check the scene init
    EXPECT_EQ(nullptr, test_data.middle_controller->scene());

    //! Check the handles init
    EXPECT_NE(nullptr, test_data.middle_controller->firstSegmentHandle());
    EXPECT_NE(nullptr, test_data.middle_controller->secondSegmentHandle());

    //! Check the roughness init
    EXPECT_NE(nullptr, test_data.middle_controller->roughness());

    //! Check the roughness handles init
    EXPECT_NE(nullptr, test_data.middle_controller->leftRoughnessHandle());
    EXPECT_NE(nullptr, test_data.middle_controller->rightRoughnessHandle());
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

TEST_F(LayerElementTest, testgeometriesupdate)
{
    TestData test_data;

    // Grab the item to change the properties
    LayerElementItem* item = test_data.exposed_controller->layerElementItem();

    double side_thickness = 5.;
    double top_thickness = 5.;
    double handle_radius = 5.;
    double r_handle_radius = 5.;
    double roughness = 5.;
    double pos = 10.;
    double width = 20.;
    double height = 30.;

    item->setProperty(LayerElementItem::P_X_POS, pos);
    item->setProperty(LayerElementItem::P_WIDTH, width);
    item->setProperty(LayerElementItem::P_HEIGHT, height);
    item->setProperty(LayerElementItem::P_ROUGHNESS, roughness);
    item->setProperty(LayerElementItem::P_SIDE_THICKNESS, side_thickness);
    item->setProperty(LayerElementItem::P_TOP_THICKNESS, top_thickness);
    item->setProperty(LayerElementItem::P_HANDLE_RADIUS, handle_radius);
    item->setProperty(LayerElementItem::P_R_HANDLE_RADIUS, r_handle_radius);

    // Init rectangle vars
    QRectF side_rect;
    QRectF top_rect;
    QRectF first_handle_rect;
    QRectF second_handle_rect;
    QPainterPath left_roughness_path;
    QPainterPath right_roughness_path;
    QRectF left_roughness_handle_rec;
    QRectF right_roughness_handle_rec;

    // #############################################################################s
    // Check initial state
    side_rect = test_data.exposed_controller->pubSideSegmentRect();
    top_rect = test_data.exposed_controller->pubTopSegmentRect();
    first_handle_rect = test_data.exposed_controller->pubFirstSegmentHandleRect();
    second_handle_rect = test_data.exposed_controller->pubSecondSegmentHandleRect();
    left_roughness_path = test_data.exposed_controller->pubLeftRoughnessPath();
    right_roughness_path = test_data.exposed_controller->pubRightRoughnessPath();
    left_roughness_handle_rec = test_data.exposed_controller->pubLeftRoughnessHandleRect();
    right_roughness_handle_rec = test_data.exposed_controller->pubRightRoughnessHandleRect();

    EXPECT_EQ(pos - side_thickness / 2., side_rect.x());
    EXPECT_EQ(0., side_rect.y());
    EXPECT_EQ(side_thickness, side_rect.width());
    EXPECT_EQ(height, side_rect.height());

    EXPECT_EQ(pos, top_rect.x());
    EXPECT_EQ(height - top_thickness / 2., top_rect.y());
    EXPECT_EQ(width, top_rect.width());
    EXPECT_EQ(top_thickness, top_rect.height());

    EXPECT_EQ(pos - handle_radius, first_handle_rect.x());
    EXPECT_EQ(-handle_radius, first_handle_rect.y());
    EXPECT_EQ(2 * handle_radius, first_handle_rect.width());
    EXPECT_EQ(2 * handle_radius, first_handle_rect.height());

    EXPECT_EQ(pos - handle_radius, second_handle_rect.x());
    EXPECT_EQ(height - handle_radius, second_handle_rect.y());
    EXPECT_EQ(2 * handle_radius, second_handle_rect.width());
    EXPECT_EQ(2 * handle_radius, second_handle_rect.height());

    EXPECT_EQ(pos - roughness, left_roughness_path.boundingRect().x());
    EXPECT_EQ(0., left_roughness_path.boundingRect().y());
    EXPECT_EQ(roughness, left_roughness_path.boundingRect().width());
    EXPECT_EQ(height, left_roughness_path.boundingRect().height());

    EXPECT_EQ(pos, right_roughness_path.boundingRect().x());
    EXPECT_EQ(0., right_roughness_path.boundingRect().y());
    EXPECT_EQ(roughness, right_roughness_path.boundingRect().width());
    EXPECT_EQ(height, right_roughness_path.boundingRect().height());

    EXPECT_EQ(pos - roughness - r_handle_radius, left_roughness_handle_rec.x());
    EXPECT_EQ(height / 2 - r_handle_radius, left_roughness_handle_rec.y());
    EXPECT_EQ(2 * r_handle_radius, left_roughness_handle_rec.width());
    EXPECT_EQ(2 * r_handle_radius, left_roughness_handle_rec.height());

    EXPECT_EQ(pos + roughness - r_handle_radius, right_roughness_handle_rec.x());
    EXPECT_EQ(height / 2 - r_handle_radius, right_roughness_handle_rec.y());
    EXPECT_EQ(2 * r_handle_radius, right_roughness_handle_rec.width());
    EXPECT_EQ(2 * r_handle_radius, right_roughness_handle_rec.height());

    // #############################################################################s
    // Check x move
    pos = 22.;
    item->setProperty(LayerElementItem::P_X_POS, pos);
    side_rect = test_data.exposed_controller->pubSideSegmentRect();
    top_rect = test_data.exposed_controller->pubTopSegmentRect();
    first_handle_rect = test_data.exposed_controller->pubFirstSegmentHandleRect();
    second_handle_rect = test_data.exposed_controller->pubSecondSegmentHandleRect();
    left_roughness_path = test_data.exposed_controller->pubLeftRoughnessPath();
    right_roughness_path = test_data.exposed_controller->pubRightRoughnessPath();
    left_roughness_handle_rec = test_data.exposed_controller->pubLeftRoughnessHandleRect();
    right_roughness_handle_rec = test_data.exposed_controller->pubRightRoughnessHandleRect();

    EXPECT_EQ(pos - side_thickness / 2., side_rect.x());
    EXPECT_EQ(0., side_rect.y());
    EXPECT_EQ(side_thickness, side_rect.width());
    EXPECT_EQ(height, side_rect.height());

    EXPECT_EQ(pos, top_rect.x());
    EXPECT_EQ(height - top_thickness / 2., top_rect.y());
    EXPECT_EQ(width, top_rect.width());
    EXPECT_EQ(top_thickness, top_rect.height());

    EXPECT_EQ(pos - handle_radius, first_handle_rect.x());
    EXPECT_EQ(-handle_radius, first_handle_rect.y());
    EXPECT_EQ(2 * handle_radius, first_handle_rect.width());
    EXPECT_EQ(2 * handle_radius, first_handle_rect.height());

    EXPECT_EQ(pos - handle_radius, second_handle_rect.x());
    EXPECT_EQ(height - handle_radius, second_handle_rect.y());
    EXPECT_EQ(2 * handle_radius, second_handle_rect.width());
    EXPECT_EQ(2 * handle_radius, second_handle_rect.height());

    EXPECT_EQ(pos - roughness, left_roughness_path.boundingRect().x());
    EXPECT_EQ(0., left_roughness_path.boundingRect().y());
    EXPECT_EQ(roughness, left_roughness_path.boundingRect().width());
    EXPECT_EQ(height, left_roughness_path.boundingRect().height());

    EXPECT_EQ(pos, right_roughness_path.boundingRect().x());
    EXPECT_EQ(0., right_roughness_path.boundingRect().y());
    EXPECT_EQ(roughness, right_roughness_path.boundingRect().width());
    EXPECT_EQ(height, right_roughness_path.boundingRect().height());

    EXPECT_EQ(pos - roughness - r_handle_radius, left_roughness_handle_rec.x());
    EXPECT_EQ(height / 2 - r_handle_radius, left_roughness_handle_rec.y());
    EXPECT_EQ(2 * r_handle_radius, left_roughness_handle_rec.width());
    EXPECT_EQ(2 * r_handle_radius, left_roughness_handle_rec.height());

    EXPECT_EQ(pos + roughness - r_handle_radius, right_roughness_handle_rec.x());
    EXPECT_EQ(height / 2 - r_handle_radius, right_roughness_handle_rec.y());
    EXPECT_EQ(2 * r_handle_radius, right_roughness_handle_rec.width());
    EXPECT_EQ(2 * r_handle_radius, right_roughness_handle_rec.height());

    // #############################################################################s
    // Check width change
    width = 22.;
    item->setProperty(LayerElementItem::P_WIDTH, width);
    side_rect = test_data.exposed_controller->pubSideSegmentRect();
    top_rect = test_data.exposed_controller->pubTopSegmentRect();
    first_handle_rect = test_data.exposed_controller->pubFirstSegmentHandleRect();
    second_handle_rect = test_data.exposed_controller->pubSecondSegmentHandleRect();
    left_roughness_path = test_data.exposed_controller->pubLeftRoughnessPath();
    right_roughness_path = test_data.exposed_controller->pubRightRoughnessPath();
    left_roughness_handle_rec = test_data.exposed_controller->pubLeftRoughnessHandleRect();
    right_roughness_handle_rec = test_data.exposed_controller->pubRightRoughnessHandleRect();

    EXPECT_EQ(pos - side_thickness / 2., side_rect.x());
    EXPECT_EQ(0., side_rect.y());
    EXPECT_EQ(side_thickness, side_rect.width());
    EXPECT_EQ(height, side_rect.height());

    EXPECT_EQ(pos, top_rect.x());
    EXPECT_EQ(height - top_thickness / 2., top_rect.y());
    EXPECT_EQ(width, top_rect.width());
    EXPECT_EQ(top_thickness, top_rect.height());

    EXPECT_EQ(pos - handle_radius, first_handle_rect.x());
    EXPECT_EQ(-handle_radius, first_handle_rect.y());
    EXPECT_EQ(2 * handle_radius, first_handle_rect.width());
    EXPECT_EQ(2 * handle_radius, first_handle_rect.height());

    EXPECT_EQ(pos - handle_radius, second_handle_rect.x());
    EXPECT_EQ(height - handle_radius, second_handle_rect.y());
    EXPECT_EQ(2 * handle_radius, second_handle_rect.width());
    EXPECT_EQ(2 * handle_radius, second_handle_rect.height());

    EXPECT_EQ(pos - roughness, left_roughness_path.boundingRect().x());
    EXPECT_EQ(0., left_roughness_path.boundingRect().y());
    EXPECT_EQ(roughness, left_roughness_path.boundingRect().width());
    EXPECT_EQ(height, left_roughness_path.boundingRect().height());

    EXPECT_EQ(pos, right_roughness_path.boundingRect().x());
    EXPECT_EQ(0., right_roughness_path.boundingRect().y());
    EXPECT_EQ(roughness, right_roughness_path.boundingRect().width());
    EXPECT_EQ(height, right_roughness_path.boundingRect().height());

    EXPECT_EQ(pos - roughness - r_handle_radius, left_roughness_handle_rec.x());
    EXPECT_EQ(height / 2 - r_handle_radius, left_roughness_handle_rec.y());
    EXPECT_EQ(2 * r_handle_radius, left_roughness_handle_rec.width());
    EXPECT_EQ(2 * r_handle_radius, left_roughness_handle_rec.height());

    EXPECT_EQ(pos + roughness - r_handle_radius, right_roughness_handle_rec.x());
    EXPECT_EQ(height / 2 - r_handle_radius, right_roughness_handle_rec.y());
    EXPECT_EQ(2 * r_handle_radius, right_roughness_handle_rec.width());
    EXPECT_EQ(2 * r_handle_radius, right_roughness_handle_rec.height());

    // #############################################################################s
    // Check heigh change
    height = 35.;
    item->setProperty(LayerElementItem::P_HEIGHT, height);
    side_rect = test_data.exposed_controller->pubSideSegmentRect();
    top_rect = test_data.exposed_controller->pubTopSegmentRect();
    first_handle_rect = test_data.exposed_controller->pubFirstSegmentHandleRect();
    second_handle_rect = test_data.exposed_controller->pubSecondSegmentHandleRect();
    left_roughness_path = test_data.exposed_controller->pubLeftRoughnessPath();
    right_roughness_path = test_data.exposed_controller->pubRightRoughnessPath();
    left_roughness_handle_rec = test_data.exposed_controller->pubLeftRoughnessHandleRect();
    right_roughness_handle_rec = test_data.exposed_controller->pubRightRoughnessHandleRect();

    EXPECT_EQ(pos - side_thickness / 2., side_rect.x());
    EXPECT_EQ(0., side_rect.y());
    EXPECT_EQ(side_thickness, side_rect.width());
    EXPECT_EQ(height, side_rect.height());

    EXPECT_EQ(pos, top_rect.x());
    EXPECT_EQ(height - top_thickness / 2., top_rect.y());
    EXPECT_EQ(width, top_rect.width());
    EXPECT_EQ(top_thickness, top_rect.height());

    EXPECT_EQ(pos - handle_radius, first_handle_rect.x());
    EXPECT_EQ(-handle_radius, first_handle_rect.y());
    EXPECT_EQ(2 * handle_radius, first_handle_rect.width());
    EXPECT_EQ(2 * handle_radius, first_handle_rect.height());

    EXPECT_EQ(pos - handle_radius, second_handle_rect.x());
    EXPECT_EQ(height - handle_radius, second_handle_rect.y());
    EXPECT_EQ(2 * handle_radius, second_handle_rect.width());
    EXPECT_EQ(2 * handle_radius, second_handle_rect.height());

    EXPECT_EQ(pos - roughness, left_roughness_path.boundingRect().x());
    EXPECT_EQ(0., left_roughness_path.boundingRect().y());
    EXPECT_EQ(roughness, left_roughness_path.boundingRect().width());
    EXPECT_EQ(height, left_roughness_path.boundingRect().height());

    EXPECT_EQ(pos, right_roughness_path.boundingRect().x());
    EXPECT_EQ(0., right_roughness_path.boundingRect().y());
    EXPECT_EQ(roughness, right_roughness_path.boundingRect().width());
    EXPECT_EQ(height, right_roughness_path.boundingRect().height());

    EXPECT_EQ(pos - roughness - r_handle_radius, left_roughness_handle_rec.x());
    EXPECT_EQ(height / 2 - r_handle_radius, left_roughness_handle_rec.y());
    EXPECT_EQ(2 * r_handle_radius, left_roughness_handle_rec.width());
    EXPECT_EQ(2 * r_handle_radius, left_roughness_handle_rec.height());

    EXPECT_EQ(pos + roughness - r_handle_radius, right_roughness_handle_rec.x());
    EXPECT_EQ(height / 2 - r_handle_radius, right_roughness_handle_rec.y());
    EXPECT_EQ(2 * r_handle_radius, right_roughness_handle_rec.width());
    EXPECT_EQ(2 * r_handle_radius, right_roughness_handle_rec.height());
}

TEST_F(LayerElementTest, testviewsupdate)
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

    // Set the roughness view item
    auto roughness_view = new RoughnessElementViewFriend();
    test_data.middle_controller->setRoughness(roughness_view);

    // Set the roughness handles
    auto left_handle = new HandleElementViewFriend();
    auto right_handle = new HandleElementViewFriend();
    test_data.middle_controller->setRoughnessHandles(left_handle, right_handle);

    // Grab the item to change the properties
    LayerElementItem* item = test_data.middle_controller->layerElementItem();

    double side_thickness = 5.;
    double top_thickness = 5.;
    double handle_radius = 5.;
    double r_handle_radius = 5.;
    double roughness = 5.;
    double pos = 10.;
    double width = 20.;
    double height = 30.;

    item->setProperty(LayerElementItem::P_X_POS, pos);
    item->setProperty(LayerElementItem::P_WIDTH, width);
    item->setProperty(LayerElementItem::P_HEIGHT, height);
    item->setProperty(LayerElementItem::P_ROUGHNESS, roughness);
    item->setProperty(LayerElementItem::P_SIDE_THICKNESS, side_thickness);
    item->setProperty(LayerElementItem::P_TOP_THICKNESS, top_thickness);
    item->setProperty(LayerElementItem::P_HANDLE_RADIUS, handle_radius);
    item->setProperty(LayerElementItem::P_R_HANDLE_RADIUS, r_handle_radius);

    // Init rectangle vars
    QRectF side_rect;
    QRectF top_rect;
    QRectF first_handle_rect;
    QRectF second_handle_rect;
    QPainterPath left_roughness_path;
    QPainterPath right_roughness_path;
    QRectF left_roughness_handle_rec;
    QRectF right_roughness_handle_rec;

    // #############################################################################s
    // Check initial state
    side_rect = side_segment->rectangle();
    top_rect = top_segment->rectangle();
    first_handle_rect = first_handle->rectangle();
    second_handle_rect = second_handle->rectangle();
    left_roughness_path = roughness_view->leftPath();
    right_roughness_path = roughness_view->rightPath();
    left_roughness_handle_rec = left_handle->rectangle();
    right_roughness_handle_rec = right_handle->rectangle();

    EXPECT_EQ(pos - side_thickness / 2., side_rect.x());
    EXPECT_EQ(0., side_rect.y());
    EXPECT_EQ(side_thickness, side_rect.width());
    EXPECT_EQ(height, side_rect.height());

    EXPECT_EQ(pos, top_rect.x());
    EXPECT_EQ(height - top_thickness / 2., top_rect.y());
    EXPECT_EQ(width, top_rect.width());
    EXPECT_EQ(top_thickness, top_rect.height());

    EXPECT_EQ(pos - handle_radius, first_handle_rect.x());
    EXPECT_EQ(-handle_radius, first_handle_rect.y());
    EXPECT_EQ(2 * handle_radius, first_handle_rect.width());
    EXPECT_EQ(2 * handle_radius, first_handle_rect.height());

    EXPECT_EQ(pos - handle_radius, second_handle_rect.x());
    EXPECT_EQ(height - handle_radius, second_handle_rect.y());
    EXPECT_EQ(2 * handle_radius, second_handle_rect.width());
    EXPECT_EQ(2 * handle_radius, second_handle_rect.height());

    EXPECT_EQ(pos - roughness, left_roughness_path.boundingRect().x());
    EXPECT_EQ(0., left_roughness_path.boundingRect().y());
    EXPECT_EQ(roughness, left_roughness_path.boundingRect().width());
    EXPECT_EQ(height, left_roughness_path.boundingRect().height());

    EXPECT_EQ(pos, right_roughness_path.boundingRect().x());
    EXPECT_EQ(0., right_roughness_path.boundingRect().y());
    EXPECT_EQ(roughness, right_roughness_path.boundingRect().width());
    EXPECT_EQ(height, right_roughness_path.boundingRect().height());

    EXPECT_EQ(pos - roughness - r_handle_radius, left_roughness_handle_rec.x());
    EXPECT_EQ(height / 2 - r_handle_radius, left_roughness_handle_rec.y());
    EXPECT_EQ(2 * r_handle_radius, left_roughness_handle_rec.width());
    EXPECT_EQ(2 * r_handle_radius, left_roughness_handle_rec.height());

    EXPECT_EQ(pos + roughness - r_handle_radius, right_roughness_handle_rec.x());
    EXPECT_EQ(height / 2 - r_handle_radius, right_roughness_handle_rec.y());
    EXPECT_EQ(2 * r_handle_radius, right_roughness_handle_rec.width());
    EXPECT_EQ(2 * r_handle_radius, right_roughness_handle_rec.height());

    // #############################################################################s
    // Test change of position
    pos = 22.;
    item->setProperty(LayerElementItem::P_X_POS, pos);
    top_rect = top_segment->rectangle();
    side_rect = side_segment->rectangle();
    first_handle_rect = first_handle->rectangle();
    second_handle_rect = second_handle->rectangle();
    left_roughness_path = roughness_view->leftPath();
    right_roughness_path = roughness_view->rightPath();
    left_roughness_handle_rec = left_handle->rectangle();
    right_roughness_handle_rec = right_handle->rectangle();

    EXPECT_EQ(pos - side_thickness / 2., side_rect.x());
    EXPECT_EQ(0., side_rect.y());
    EXPECT_EQ(side_thickness, side_rect.width());
    EXPECT_EQ(height, side_rect.height());

    EXPECT_EQ(pos, top_rect.x());
    EXPECT_EQ(height - top_thickness / 2., top_rect.y());
    EXPECT_EQ(width, top_rect.width());
    EXPECT_EQ(top_thickness, top_rect.height());

    EXPECT_EQ(pos - handle_radius, first_handle_rect.x());
    EXPECT_EQ(-handle_radius, first_handle_rect.y());
    EXPECT_EQ(2 * handle_radius, first_handle_rect.width());
    EXPECT_EQ(2 * handle_radius, first_handle_rect.height());

    EXPECT_EQ(pos - handle_radius, second_handle_rect.x());
    EXPECT_EQ(height - handle_radius, second_handle_rect.y());
    EXPECT_EQ(2 * handle_radius, second_handle_rect.width());
    EXPECT_EQ(2 * handle_radius, second_handle_rect.height());

    EXPECT_EQ(pos - roughness, left_roughness_path.boundingRect().x());
    EXPECT_EQ(0., left_roughness_path.boundingRect().y());
    EXPECT_EQ(roughness, left_roughness_path.boundingRect().width());
    EXPECT_EQ(height, left_roughness_path.boundingRect().height());

    EXPECT_EQ(pos, right_roughness_path.boundingRect().x());
    EXPECT_EQ(0., right_roughness_path.boundingRect().y());
    EXPECT_EQ(roughness, right_roughness_path.boundingRect().width());
    EXPECT_EQ(height, right_roughness_path.boundingRect().height());

    EXPECT_EQ(pos - roughness - r_handle_radius, left_roughness_handle_rec.x());
    EXPECT_EQ(height / 2 - r_handle_radius, left_roughness_handle_rec.y());
    EXPECT_EQ(2 * r_handle_radius, left_roughness_handle_rec.width());
    EXPECT_EQ(2 * r_handle_radius, left_roughness_handle_rec.height());

    EXPECT_EQ(pos + roughness - r_handle_radius, right_roughness_handle_rec.x());
    EXPECT_EQ(height / 2 - r_handle_radius, right_roughness_handle_rec.y());
    EXPECT_EQ(2 * r_handle_radius, right_roughness_handle_rec.width());
    EXPECT_EQ(2 * r_handle_radius, right_roughness_handle_rec.height());

    // #############################################################################s
    // Test change of width
    width = 22.;
    item->setProperty(LayerElementItem::P_WIDTH, width);
    top_rect = top_segment->rectangle();
    side_rect = side_segment->rectangle();
    first_handle_rect = first_handle->rectangle();
    second_handle_rect = second_handle->rectangle();
    left_roughness_path = roughness_view->leftPath();
    right_roughness_path = roughness_view->rightPath();
    left_roughness_handle_rec = left_handle->rectangle();
    right_roughness_handle_rec = right_handle->rectangle();

    EXPECT_EQ(pos - side_thickness / 2., side_rect.x());
    EXPECT_EQ(0., side_rect.y());
    EXPECT_EQ(side_thickness, side_rect.width());
    EXPECT_EQ(height, side_rect.height());

    EXPECT_EQ(pos, top_rect.x());
    EXPECT_EQ(height - top_thickness / 2., top_rect.y());
    EXPECT_EQ(width, top_rect.width());
    EXPECT_EQ(top_thickness, top_rect.height());

    EXPECT_EQ(pos - handle_radius, first_handle_rect.x());
    EXPECT_EQ(-handle_radius, first_handle_rect.y());
    EXPECT_EQ(2 * handle_radius, first_handle_rect.width());
    EXPECT_EQ(2 * handle_radius, first_handle_rect.height());

    EXPECT_EQ(pos - handle_radius, second_handle_rect.x());
    EXPECT_EQ(height - handle_radius, second_handle_rect.y());
    EXPECT_EQ(2 * handle_radius, second_handle_rect.width());
    EXPECT_EQ(2 * handle_radius, second_handle_rect.height());

    EXPECT_EQ(pos - roughness, left_roughness_path.boundingRect().x());
    EXPECT_EQ(0., left_roughness_path.boundingRect().y());
    EXPECT_EQ(roughness, left_roughness_path.boundingRect().width());
    EXPECT_EQ(height, left_roughness_path.boundingRect().height());

    EXPECT_EQ(pos, right_roughness_path.boundingRect().x());
    EXPECT_EQ(0., right_roughness_path.boundingRect().y());
    EXPECT_EQ(roughness, right_roughness_path.boundingRect().width());
    EXPECT_EQ(height, right_roughness_path.boundingRect().height());

    EXPECT_EQ(pos - roughness - r_handle_radius, left_roughness_handle_rec.x());
    EXPECT_EQ(height / 2 - r_handle_radius, left_roughness_handle_rec.y());
    EXPECT_EQ(2 * r_handle_radius, left_roughness_handle_rec.width());
    EXPECT_EQ(2 * r_handle_radius, left_roughness_handle_rec.height());

    EXPECT_EQ(pos + roughness - r_handle_radius, right_roughness_handle_rec.x());
    EXPECT_EQ(height / 2 - r_handle_radius, right_roughness_handle_rec.y());
    EXPECT_EQ(2 * r_handle_radius, right_roughness_handle_rec.width());
    EXPECT_EQ(2 * r_handle_radius, right_roughness_handle_rec.height());

    // #############################################################################s
    // Test propagation change of height
    height = 35.;
    item->setProperty(LayerElementItem::P_HEIGHT, height);
    top_rect = top_segment->rectangle();
    side_rect = side_segment->rectangle();
    first_handle_rect = first_handle->rectangle();
    second_handle_rect = second_handle->rectangle();
    left_roughness_path = roughness_view->leftPath();
    right_roughness_path = roughness_view->rightPath();
    left_roughness_handle_rec = left_handle->rectangle();
    right_roughness_handle_rec = right_handle->rectangle();

    EXPECT_EQ(pos - side_thickness / 2., side_rect.x());
    EXPECT_EQ(0., side_rect.y());
    EXPECT_EQ(side_thickness, side_rect.width());
    EXPECT_EQ(height, side_rect.height());

    EXPECT_EQ(pos, top_rect.x());
    EXPECT_EQ(height - top_thickness / 2., top_rect.y());
    EXPECT_EQ(width, top_rect.width());
    EXPECT_EQ(top_thickness, top_rect.height());

    EXPECT_EQ(pos - handle_radius, first_handle_rect.x());
    EXPECT_EQ(-handle_radius, first_handle_rect.y());
    EXPECT_EQ(2 * handle_radius, first_handle_rect.width());
    EXPECT_EQ(2 * handle_radius, first_handle_rect.height());

    EXPECT_EQ(pos - handle_radius, second_handle_rect.x());
    EXPECT_EQ(height - handle_radius, second_handle_rect.y());
    EXPECT_EQ(2 * handle_radius, second_handle_rect.width());
    EXPECT_EQ(2 * handle_radius, second_handle_rect.height());

    EXPECT_EQ(pos - roughness, left_roughness_path.boundingRect().x());
    EXPECT_EQ(0., left_roughness_path.boundingRect().y());
    EXPECT_EQ(roughness, left_roughness_path.boundingRect().width());
    EXPECT_EQ(height, left_roughness_path.boundingRect().height());

    EXPECT_EQ(pos, right_roughness_path.boundingRect().x());
    EXPECT_EQ(0., right_roughness_path.boundingRect().y());
    EXPECT_EQ(roughness, right_roughness_path.boundingRect().width());
    EXPECT_EQ(height, right_roughness_path.boundingRect().height());

    EXPECT_EQ(pos - roughness - r_handle_radius, left_roughness_handle_rec.x());
    EXPECT_EQ(height / 2 - r_handle_radius, left_roughness_handle_rec.y());
    EXPECT_EQ(2 * r_handle_radius, left_roughness_handle_rec.width());
    EXPECT_EQ(2 * r_handle_radius, left_roughness_handle_rec.height());

    EXPECT_EQ(pos + roughness - r_handle_radius, right_roughness_handle_rec.x());
    EXPECT_EQ(height / 2 - r_handle_radius, right_roughness_handle_rec.y());
    EXPECT_EQ(2 * r_handle_radius, right_roughness_handle_rec.width());
    EXPECT_EQ(2 * r_handle_radius, right_roughness_handle_rec.height());
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

    auto adapter = test_data.scene->getSceneAdapter();

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
    auto roughness_view_above = new RoughnessElementViewFriend();
    test_data.middle_controller->setRoughness(roughness_view_above);
    auto left_handle_above = new HandleElementViewFriend();
    auto right_handle_above = new HandleElementViewFriend();
    test_data.above_controller->setRoughnessHandles(left_handle_above, right_handle_above);

    // Set the middle layer up
    auto side_segment_middle = new SegmentElementViewFriend();
    auto top_segment_middle = new SegmentElementViewFriend();
    test_data.middle_controller->setSideSegment(side_segment_middle);
    test_data.middle_controller->setTopSegment(top_segment_middle);
    auto first_handle_middle = new HandleElementViewFriend();
    auto second_handle_middle = new HandleElementViewFriend();
    test_data.middle_controller->setSegmentHandles(first_handle_middle, second_handle_middle);
    auto roughness_view_middle = new RoughnessElementViewFriend();
    test_data.middle_controller->setRoughness(roughness_view_middle);
    auto left_handle_middle = new HandleElementViewFriend();
    auto right_handle_middle = new HandleElementViewFriend();
    test_data.middle_controller->setRoughnessHandles(left_handle_middle, right_handle_middle);

    // Set the layer below up
    auto side_segment_below = new SegmentElementViewFriend();
    auto top_segment_below = new SegmentElementViewFriend();
    test_data.below_controller->setSideSegment(side_segment_below);
    test_data.below_controller->setTopSegment(top_segment_below);
    auto first_handle_below = new HandleElementViewFriend();
    auto second_handle_below = new HandleElementViewFriend();
    test_data.below_controller->setSegmentHandles(first_handle_below, second_handle_below);
    auto roughness_view_below = new RoughnessElementViewFriend();
    test_data.below_controller->setRoughness(roughness_view_below);
    auto left_handle_below = new HandleElementViewFriend();
    auto right_handle_below = new HandleElementViewFriend();
    test_data.below_controller->setRoughnessHandles(left_handle_below, right_handle_below);

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
    QSignalSpy spy_ctr_middle_roughness(test_data.middle_controller,
                                        &LayerElementController::roughnessChanged);

    auto mouse_move_event = new QGraphicsSceneMouseEvent();
    QList<QVariant> move_arguments;

    // Try standard x move
    mouse_move_event->setPos(QPointF(adapter->toSceneX(8), adapter->toSceneY(0)));
    side_segment_middle->mouseMoveEvent(mouse_move_event);
    move_arguments = spy_ctr_above_width.takeLast();

    EXPECT_EQ(move_arguments.at(0).value<std::string>(), "above");
    EXPECT_EQ(move_arguments.at(1).value<double>(), 8);
    EXPECT_EQ(8., item_above->property(LayerElementItem::P_WIDTH).toDouble());
    EXPECT_EQ(8., item_middle->property(LayerElementItem::P_X_POS).toDouble());
    EXPECT_EQ(3., first_handle_middle->rectangle().x());
    EXPECT_EQ(5., first_handle_middle->rectangle().y());
    EXPECT_EQ(3., second_handle_middle->rectangle().x());
    EXPECT_EQ(5., second_handle_middle->rectangle().y());

    move_arguments = spy_ctr_middle_roughness.takeLast();
    EXPECT_EQ(move_arguments.at(0).value<std::string>(), "middle");
    EXPECT_EQ(move_arguments.at(1).value<double>(), 4);
    EXPECT_EQ(4, item_middle->property(LayerElementItem::P_ROUGHNESS).toDouble());

    // Try limit x move
    mouse_move_event->setPos(QPointF(adapter->toSceneX(-1), adapter->toSceneY(0)));
    side_segment_middle->mouseMoveEvent(mouse_move_event);

    move_arguments = spy_ctr_above_width.takeLast();
    EXPECT_EQ(move_arguments.at(0).value<std::string>(), "above");
    EXPECT_EQ(move_arguments.at(1).value<double>(), 1e-6);
    EXPECT_EQ(1e-6, item_above->property(LayerElementItem::P_WIDTH).toDouble());
    EXPECT_EQ(1e-6, item_middle->property(LayerElementItem::P_X_POS).toDouble());
    EXPECT_EQ(-5 + 1e-6, first_handle_middle->rectangle().x());
    EXPECT_EQ(5., first_handle_middle->rectangle().y());
    EXPECT_EQ(-5 + 1e-6, second_handle_middle->rectangle().x());
    EXPECT_EQ(5., second_handle_middle->rectangle().y());

    move_arguments = spy_ctr_middle_roughness.takeLast();
    EXPECT_EQ(move_arguments.at(0).value<std::string>(), "middle");
    EXPECT_EQ(move_arguments.at(1).value<double>(), 5e-7);
    EXPECT_EQ(1e-6 / 2, item_middle->property(LayerElementItem::P_ROUGHNESS).toDouble());

    // Try standard x move
    mouse_move_event->setPos(QPointF(adapter->toSceneX(10), adapter->toSceneY(0)));
    side_segment_middle->mouseMoveEvent(mouse_move_event);
    move_arguments = spy_ctr_above_width.takeLast();

    EXPECT_EQ(move_arguments.at(0).value<std::string>(), "above");
    EXPECT_EQ(move_arguments.at(1).value<double>(), 10);
    EXPECT_EQ(10., item_above->property(LayerElementItem::P_WIDTH).toDouble());
    EXPECT_EQ(10., item_middle->property(LayerElementItem::P_X_POS).toDouble());
    EXPECT_EQ(5., first_handle_middle->rectangle().x());
    EXPECT_EQ(5., first_handle_middle->rectangle().y());
    EXPECT_EQ(5., second_handle_middle->rectangle().x());
    EXPECT_EQ(5., second_handle_middle->rectangle().y());

    // Try standard y move
    mouse_move_event->setPos(QPointF(adapter->toSceneX(0), adapter->toSceneY(8)));
    top_segment_middle->mouseMoveEvent(mouse_move_event);
    move_arguments = spy_ctr_middle_height.takeLast();

    EXPECT_EQ(move_arguments.at(0).value<std::string>(), "middle");
    EXPECT_EQ(move_arguments.at(1).value<double>(), 8);
    EXPECT_EQ(8., item_middle->property(LayerElementItem::P_HEIGHT).toDouble());
    EXPECT_EQ(5., first_handle_middle->rectangle().x());
    EXPECT_EQ(5., first_handle_middle->rectangle().y());
    EXPECT_EQ(5., second_handle_middle->rectangle().x());
    EXPECT_EQ(3., second_handle_middle->rectangle().y());

    // Try limit y move
    mouse_move_event->setPos(QPointF(adapter->toSceneX(0), adapter->toSceneY(-1)));
    top_segment_middle->mouseMoveEvent(mouse_move_event);
    move_arguments = spy_ctr_middle_height.takeLast();

    EXPECT_EQ(move_arguments.at(0).value<std::string>(), "middle");
    EXPECT_EQ(move_arguments.at(1).value<double>(), 0);
    EXPECT_EQ(0, item_middle->property(LayerElementItem::P_HEIGHT).toDouble());
    EXPECT_EQ(5., first_handle_middle->rectangle().x());
    EXPECT_EQ(5., first_handle_middle->rectangle().y());
    EXPECT_EQ(5., second_handle_middle->rectangle().x());
    EXPECT_EQ(-5., second_handle_middle->rectangle().y());

    // Try standard y move
    mouse_move_event->setPos(QPointF(adapter->toSceneX(0), adapter->toSceneY(10)));
    top_segment_middle->mouseMoveEvent(mouse_move_event);
    move_arguments = spy_ctr_middle_height.takeLast();

    EXPECT_EQ(move_arguments.at(0).value<std::string>(), "middle");
    EXPECT_EQ(move_arguments.at(1).value<double>(), 10);
    EXPECT_EQ(10., item_middle->property(LayerElementItem::P_HEIGHT).toDouble());
    EXPECT_EQ(5., first_handle_middle->rectangle().x());
    EXPECT_EQ(5., first_handle_middle->rectangle().y());
    EXPECT_EQ(5., second_handle_middle->rectangle().x());
    EXPECT_EQ(5., second_handle_middle->rectangle().y());

    // Try standard roughness move left handle
    mouse_move_event->setPos(QPointF(adapter->toSceneX(7), adapter->toSceneY(0)));
    left_handle_middle->mouseMoveEvent(mouse_move_event);

    move_arguments = spy_ctr_middle_roughness.takeLast();
    EXPECT_EQ(move_arguments.at(0).value<std::string>(), "middle");
    EXPECT_EQ(move_arguments.at(1).value<double>(), 3.);
    EXPECT_EQ(3., item_middle->property(LayerElementItem::P_ROUGHNESS).toDouble());

    // Try limit roughness move left handle
    mouse_move_event->setPos(QPointF(adapter->toSceneX(2), adapter->toSceneY(0)));
    left_handle_middle->mouseMoveEvent(mouse_move_event);

    move_arguments = spy_ctr_middle_roughness.takeLast();
    EXPECT_EQ(move_arguments.at(0).value<std::string>(), "middle");
    EXPECT_EQ(move_arguments.at(1).value<double>(), 5.);
    EXPECT_EQ(5., item_middle->property(LayerElementItem::P_ROUGHNESS).toDouble());

    // Try standard roughness move left handle
    mouse_move_event->setPos(QPointF(adapter->toSceneX(8), adapter->toSceneY(0)));
    left_handle_middle->mouseMoveEvent(mouse_move_event);

    move_arguments = spy_ctr_middle_roughness.takeLast();
    EXPECT_EQ(move_arguments.at(0).value<std::string>(), "middle");
    EXPECT_EQ(move_arguments.at(1).value<double>(), 2.);
    EXPECT_EQ(2., item_middle->property(LayerElementItem::P_ROUGHNESS).toDouble());

    // Try standard roughness move right handle
    mouse_move_event->setPos(QPointF(adapter->toSceneX(13), adapter->toSceneY(0)));
    right_handle_middle->mouseMoveEvent(mouse_move_event);

    move_arguments = spy_ctr_middle_roughness.takeLast();
    EXPECT_EQ(move_arguments.at(0).value<std::string>(), "middle");
    EXPECT_EQ(move_arguments.at(1).value<double>(), 3.);
    EXPECT_EQ(3., item_middle->property(LayerElementItem::P_ROUGHNESS).toDouble());

    // Try limit roughness move right handle
    mouse_move_event->setPos(QPointF(adapter->toSceneX(8), adapter->toSceneY(0)));
    right_handle_middle->mouseMoveEvent(mouse_move_event);

    move_arguments = spy_ctr_middle_roughness.takeLast();
    EXPECT_EQ(move_arguments.at(0).value<std::string>(), "middle");
    EXPECT_EQ(move_arguments.at(1).value<double>(), 0);
    EXPECT_EQ(0, item_middle->property(LayerElementItem::P_ROUGHNESS).toDouble());

    // Try standard roughness move right handle
    mouse_move_event->setPos(QPointF(adapter->toSceneX(13), adapter->toSceneY(0)));
    right_handle_middle->mouseMoveEvent(mouse_move_event);

    move_arguments = spy_ctr_middle_roughness.takeLast();
    EXPECT_EQ(move_arguments.at(0).value<std::string>(), "middle");
    EXPECT_EQ(move_arguments.at(1).value<double>(), 3);
    EXPECT_EQ(3, item_middle->property(LayerElementItem::P_ROUGHNESS).toDouble());
}
TEST_F(LayerElementTest, moveelements)
{
    TestData test_data;
    test_data.middle_controller->setLayerAbove(test_data.above_controller);
    test_data.middle_controller->setLayerBelow(test_data.below_controller);
}
