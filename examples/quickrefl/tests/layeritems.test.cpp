// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "google_test.h"
#include "layeritems.h"
#include "samplemodel.h"
#include "test_utils.h"

using namespace ModelView;

//! Test of CompountItem machinery (property children etc).

class LayerItemsTest : public ::testing::Test
{
public:
    ~LayerItemsTest();
};

LayerItemsTest::~LayerItemsTest() = default;

//! Checks that layers in multilayer have proper appearance of "thickness" property.
//! Top and bottom layers should have "thickness" always disabled.

TEST_F(LayerItemsTest, layerAppearanceTwoLayerSystem)
{
    SampleModel model;

    auto multilayer = model.insertItem<MultiLayerItem>();

    auto top = model.insertItem<LayerItem>(multilayer);
    auto bottom = model.insertItem<LayerItem>(multilayer);

    // check appearance of thickness properties
    EXPECT_FALSE(top->getItem(LayerItem::P_THICKNESS)->isEnabled());
    EXPECT_FALSE(bottom->getItem(LayerItem::P_THICKNESS)->isEnabled());

    // check that thickness of top and bottom layer is 0.
    EXPECT_EQ(top->property(LayerItem::P_THICKNESS).value<double>(), 0.0);
    EXPECT_EQ(bottom->property(LayerItem::P_THICKNESS).value<double>(), 0.0);
}

TEST_F(LayerItemsTest, layerAppearanceThreeLayerSystem)
{
    SampleModel model;

    auto multilayer = model.insertItem<MultiLayerItem>();

    auto top = model.insertItem<LayerItem>(multilayer);
    auto middle = model.insertItem<LayerItem>(multilayer);
    auto bottom = model.insertItem<LayerItem>(multilayer);

    // check appearance of thickness properties
    EXPECT_FALSE(top->getItem(LayerItem::P_THICKNESS)->isEnabled());
    EXPECT_TRUE(middle->getItem(LayerItem::P_THICKNESS)->isEnabled());
    EXPECT_FALSE(bottom->getItem(LayerItem::P_THICKNESS)->isEnabled());

    middle->setProperty(LayerItem::P_THICKNESS, 42.0);

    // moving middle layer on top
    model.moveItem(middle, multilayer, {MultiLayerItem::T_LAYERS, 0});

    auto new_top = middle;
    auto new_middle = top;
    auto new_bottom = bottom;

    EXPECT_FALSE(new_top->getItem(LayerItem::P_THICKNESS)->isEnabled());
    EXPECT_TRUE(new_middle->getItem(LayerItem::P_THICKNESS)->isEnabled());
    EXPECT_FALSE(new_bottom->getItem(LayerItem::P_THICKNESS)->isEnabled());

    // check the value of thickness
    EXPECT_EQ(new_top->property(LayerItem::P_THICKNESS).value<double>(),
              0.0); // was reset during move
    EXPECT_EQ(new_middle->property(LayerItem::P_THICKNESS).value<double>(), 0.0);
    EXPECT_EQ(new_bottom->property(LayerItem::P_THICKNESS).value<double>(), 0.0);
}
