// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "google_test.h"

#include "layerelementcontroller.h"
#include "layerelementitem.h"
#include "segmentelementview.h"
#include "sldelementmodel.h"

#include "test_utils.h"
#include <mvvm/viewmodel/viewmodelutils.h>

#include <QColor>

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

        SLDElementModel* model{nullptr};

        LayerElementItem* above_layer_item{nullptr};
        LayerElementItem* middle_layer_item{nullptr};
        LayerElementItem* below_layer_item{nullptr};

        LayerElementController* above_controller{nullptr};
        LayerElementController* middle_controller{nullptr};
        LayerElementController* below_controller{nullptr};

        TestData()
        {
            exposed_layer_item = new LayerElementItem();
            exposed_controller = new LayerElementControllerFriend(exposed_layer_item);

            model = new SLDElementModel();
            above_layer_item = model->addLayer();
            middle_layer_item = model->addLayer();
            below_layer_item = model->addLayer();

            above_controller = new LayerElementController(above_layer_item);
            middle_controller = new LayerElementController(middle_layer_item);
            below_controller = new LayerElementController(below_layer_item);
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

TEST_F(LayerElementTest, testhandles)
{
    TestData test_data;
}

TEST_F(LayerElementTest, moveelements)
{
    TestData test_data;
    test_data.middle_controller->setLayerAbove(test_data.above_controller);
    test_data.middle_controller->setLayerBelow(test_data.below_controller);
}
