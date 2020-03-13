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
#include "layerselectionmodel.h"
#include "layerviewmodel.h"
#include "samplemodel.h"
#include "test_utils.h"
#include <mvvm/viewmodel/viewmodelutils.h>

using namespace ModelView;

//! Tests of LayerSelectionModel.

class LayerSelectionModelTest : public ::testing::Test
{
public:
    ~LayerSelectionModelTest();

    struct TestData {
        SampleModel sample_model;
        LayerViewModel view_model{&sample_model};
        LayerSelectionModel selection_model{&view_model};
        SessionItem* multilayer{nullptr};
        SessionItem* top{nullptr};
        SessionItem* bottom{nullptr};
        TestData()
        {
            multilayer = sample_model.insertItem<MultiLayerItem>();
            top = sample_model.insertItem<LayerItem>(multilayer);
            bottom = sample_model.insertItem<LayerItem>(multilayer);
            view_model.setRootSessionItem(multilayer);
        }
    };
};

LayerSelectionModelTest::~LayerSelectionModelTest() = default;

//! Layout of LayerViewModel for two layer system.

TEST_F(LayerSelectionModelTest, initialState)
{
    TestData test_data;
    EXPECT_FALSE(test_data.selection_model.hasSelection());

    // checking layout of multilayer
    auto layers = test_data.multilayer->getItems(MultiLayerItem::T_LAYERS);
    EXPECT_EQ(layers.size(), 2);
    EXPECT_EQ(layers.at(0), test_data.top);
    EXPECT_EQ(layers.at(1), test_data.bottom);
}

TEST_F(LayerSelectionModelTest, selectLayerItem)
{
    TestData test_data;

    // selecting top layer
    test_data.selection_model.selectItem(test_data.top);
    EXPECT_TRUE(test_data.selection_model.hasSelection());
    // 4 indexes should be selected: name, nr, material, thickness, sigma
    EXPECT_EQ(test_data.selection_model.selectedIndexes().size(), 5);

    // checking back that top layer is selected
    std::vector<SessionItem*> expected = {test_data.top};
    EXPECT_EQ(test_data.selection_model.selectedItems(), expected);

    // selecting bottom layer
    test_data.selection_model.selectItem(test_data.bottom);
    EXPECT_TRUE(test_data.selection_model.hasSelection());
    // 4 indexes should be selected: name, nr, material, thickness, sigma
    EXPECT_EQ(test_data.selection_model.selectedIndexes().size(), 5);

    // checking back that top layer is selected
    expected = {test_data.bottom};
    EXPECT_EQ(test_data.selection_model.selectedItems(), expected);
}

TEST_F(LayerSelectionModelTest, selectLayerItems)
{
    TestData test_data;

    std::vector<ModelView::SessionItem*> to_select{test_data.top, test_data.bottom};
    test_data.selection_model.selectItems(to_select);

    // selecting top layer
    EXPECT_TRUE(test_data.selection_model.hasSelection());

    EXPECT_EQ(test_data.selection_model.selectedIndexes().size(), 10); // two rows of cells

    // checking back that top layer is selected
    std::vector<SessionItem*> expected = to_select;
    EXPECT_EQ(test_data.selection_model.selectedItems(), expected);
}

//! Checking selection of MultiLayer items

TEST_F(LayerSelectionModelTest, selectMultiLayerItem)
{
    TestData test_data;

    // adding new MultiLayer between top and bottom layer
    auto new_ml = test_data.sample_model.insertItem<MultiLayerItem>(test_data.multilayer,
                                                                    {MultiLayerItem::T_LAYERS, 1});

    // checking layout
    auto layers = test_data.multilayer->getItems(MultiLayerItem::T_LAYERS);
    EXPECT_EQ(layers.size(), 3);
    EXPECT_EQ(layers.at(0), test_data.top);
    EXPECT_EQ(layers.at(1), new_ml);
    EXPECT_EQ(layers.at(2), test_data.bottom);

    // selecting new multi-layer
    test_data.selection_model.selectItem(new_ml);

    EXPECT_TRUE(test_data.selection_model.hasSelection());
    EXPECT_EQ(test_data.selection_model.selectedIndexes().size(), 5);

    std::vector<SessionItem*> expected = {new_ml};
    EXPECT_EQ(test_data.selection_model.selectedItems(), expected);
}
