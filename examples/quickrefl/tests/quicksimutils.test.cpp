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
#include "materialitems.h"
#include "materialmodel.h"
#include "quicksimutils.h"
#include "samplemodel.h"
#include <QColor>
#include <mvvm/model/externalproperty.h>
#include <mvvm/model/itempool.h>

using namespace ModelView;

//! Tests of QuickSimUtils namespace functions.

class QuickSimUtilsTest : public ::testing::Test
{
public:
    ~QuickSimUtilsTest();
};

QuickSimUtilsTest::~QuickSimUtilsTest() = default;

//! Multi-slice of empty MultiLayer.

TEST_F(QuickSimUtilsTest, emptySlice)
{
    SampleModel model;
    auto multilayer = model.insertItem<MultiLayerItem>();
    auto multislice = ::Utils::CreateMultiSlice(*multilayer);
    EXPECT_EQ(multislice.size(), 0);
}

//! Multi-slice of MultiLayer with single layer without material.

TEST_F(QuickSimUtilsTest, layerSlice)
{
    SampleModel model;
    auto multilayer = model.insertItem<MultiLayerItem>();
    model.insertItem<LayerItem>(multilayer);
    auto multislice = ::Utils::CreateMultiSlice(*multilayer);

    ASSERT_EQ(multislice.size(), 1);
    EXPECT_EQ(multislice[0].material.real(), 0.0);
    EXPECT_EQ(multislice[0].material.imag(), 0.0);
    EXPECT_EQ(multislice[0].thickness, 0.0);
    EXPECT_EQ(multislice[0].sigma, 0.0);
}

//! Multi-slice of MultiLayer with single layer with defined material and roughness.

TEST_F(QuickSimUtilsTest, definedLayerSlice)
{
    // common pool
    auto pool = std::make_shared<ItemPool>();

    // initializing MaterialModel with single material
    MaterialModel material_model(pool);
    auto material = material_model.insertItem<SLDMaterialItem>();
    const double sld_real{1.0};
    const double sld_imag{2.0};
    material->set_properties("gold", QColor(), sld_real, sld_imag);
    ModelView::ExternalProperty material_property("gold", QColor(), material->identifier());

    // initializing SampleModel
    SampleModel model(pool);
    auto multilayer = model.insertItem<MultiLayerItem>();
    auto layer = model.insertItem<LayerItem>(multilayer);

    // checking that pool is working
    EXPECT_EQ(model.findItem(material->identifier()), material);
    EXPECT_EQ(model.findItem(material_property.identifier()), material);

    // setting thickness, roughness and material to layer
    const double thickness{43.0};
    layer->setProperty(LayerItem::P_THICKNESS, thickness);
    auto roughness = layer->item<RoughnessItem>(LayerItem::P_ROUGHNESS);
    const double sigma{42.0};
    roughness->setProperty(RoughnessItem::P_SIGMA, sigma);
    layer->setProperty(LayerItem::P_MATERIAL, QVariant::fromValue(material_property));

    auto multislice = ::Utils::CreateMultiSlice(*multilayer);

    ASSERT_EQ(multislice.size(), 1);
    EXPECT_EQ(multislice[0].material.real(), sld_real);
    EXPECT_EQ(multislice[0].material.imag(), sld_imag);
    EXPECT_EQ(multislice[0].thickness, thickness);
    EXPECT_EQ(multislice[0].sigma, sigma);
}
