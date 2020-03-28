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
#include <tuple>

using namespace ModelView;

namespace
{
//! Helper function to set layer's parameters.
void setup_layer(LayerItem* layer, double thickness, double sigma, SLDMaterialItem* material)
{
    layer->setProperty(LayerItem::P_THICKNESS, thickness);
    auto roughness = layer->item<RoughnessItem>(LayerItem::P_ROUGHNESS);
    roughness->setProperty(RoughnessItem::P_SIGMA, sigma);
    layer->setProperty(LayerItem::P_MATERIAL, QVariant::fromValue(material->external_property()));
}

} // namespace

//! Tests of QuickSimUtils namespace functions.

class QuickSimUtilsTest : public ::testing::Test
{
public:
    //! Helper container with testing data.
    struct TestData {
        std::shared_ptr<ItemPool> item_pool;
        SampleModel sample_model;
        MaterialModel material_model;
        MultiLayerItem* multilayer{nullptr};
        TestData()
            : item_pool(std::make_shared<ItemPool>()), sample_model(item_pool),
              material_model(item_pool)
        {
            multilayer = sample_model.insertItem<MultiLayerItem>();
        }

        //! Add layer and material to corresponding models. Layer will be linked to given material.
        void addLayer(double thickness, double sigma, complex_t sld)
        {
            auto material = material_model.insertItem<SLDMaterialItem>();
            material->set_properties("gold", QColor(), sld.real(), sld.imag());
            auto layer = sample_model.insertItem<LayerItem>(multilayer);
            setup_layer(layer, thickness, sigma, material);
        }
    };

    ~QuickSimUtilsTest();
};

QuickSimUtilsTest::~QuickSimUtilsTest() = default;

//! Testing helper structure.

TEST_F(QuickSimUtilsTest, testData)
{
    TestData test_data;

    // creating single layer
    double thickness{42.0};
    double sigma{43.0};
    complex_t sld{1.0, 2.0};
    test_data.addLayer(thickness, sigma, sld);

    // checking that layer got necessary parameters
    auto layer = test_data.multilayer->item<LayerItem>(MultiLayerItem::T_LAYERS);
    EXPECT_EQ(layer->property(LayerItem::P_THICKNESS).value<double>(), thickness);
    auto roughness = layer->item<RoughnessItem>(LayerItem::P_ROUGHNESS);
    EXPECT_EQ(roughness->property(RoughnessItem::P_SIGMA).value<double>(), sigma);

    // checking that layer is linked to material with necessary parameters
    auto material_property = layer->property(LayerItem::P_MATERIAL).value<ExternalProperty>();
    auto material = test_data.sample_model.findItem(material_property.identifier());
    EXPECT_EQ(material->property(SLDMaterialItem::P_SLD_REAL), sld.real());
    EXPECT_EQ(material->property(SLDMaterialItem::P_SLD_IMAG), sld.imag());
}

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
    TestData test_data;

    // initializing MaterialModel with single material
    const double thickness{42.0};
    const double sigma{43.0};
    const complex_t sld{1.0, 2.0};

    // adding layer
    test_data.addLayer(thickness, sigma, sld);

    // creating multi slice
    auto multislice = ::Utils::CreateMultiSlice(*test_data.multilayer);

    ASSERT_EQ(multislice.size(), 1);
    EXPECT_EQ(multislice[0].material.real(), sld.real());
    EXPECT_EQ(multislice[0].material.imag(), sld.imag());
    EXPECT_EQ(multislice[0].thickness, thickness);
    EXPECT_EQ(multislice[0].sigma, sigma);
}

//! Multi-slice of MultiLayer with three layers.

TEST_F(QuickSimUtilsTest, threeLayerSlices)
{
    TestData test_data;

    // initializing MaterialModel with single material
    using layer_info = std::tuple<double, double, complex_t>; // thickness, sigma
    std::vector<layer_info> layer_data = {
        {0.0, 0.0, {11, 12}}, {42.0, 10.0, {13, 14}}, {0.0, 0.0, {15, 16}}};
    for (auto [thickness, sigma, sld] : layer_data)
        test_data.addLayer(thickness, sigma, sld);

    auto multislice = ::Utils::CreateMultiSlice(*test_data.multilayer);

    ASSERT_EQ(multislice.size(), 3);
    int index(0);
    for (auto [thickness, sigma, sld] : layer_data) {
        EXPECT_EQ(multislice[index].material.real(), sld.real());
        EXPECT_EQ(multislice[index].material.imag(), sld.imag());
        EXPECT_EQ(multislice[index].thickness, thickness);
        EXPECT_EQ(multislice[index].sigma, sigma);
        ++index;
    }
}
