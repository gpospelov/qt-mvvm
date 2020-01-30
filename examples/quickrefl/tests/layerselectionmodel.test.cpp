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
};

LayerSelectionModelTest::~LayerSelectionModelTest() = default;

//! Layout of LayerViewModel for two layer system.

TEST_F(LayerSelectionModelTest, initialState)
{
    SampleModel model;
    auto multilayer = model.insertItem<MultiLayerItem>();
    auto top = model.insertItem<LayerItem>(multilayer);
    auto bottom = model.insertItem<LayerItem>(multilayer);

    LayerViewModel viewmodel(&model);
    viewmodel.setRootSessionItem(multilayer);
    LayerSelectionModel selection_model(&viewmodel);

    // no selection at the beginning
    EXPECT_FALSE(selection_model.hasSelection());

    // selecting top layer
    selection_model.selectItem(top);
    EXPECT_TRUE(selection_model.hasSelection());
    EXPECT_EQ(selection_model.selectedIndexes().size(), 4); // name, nr, material, thickness

    // checking back that top layer is selected
    std::vector<SessionItem*> expected = {top};
    EXPECT_EQ(selection_model.selectedItems(), expected);

    // selecting bottom layer
    selection_model.selectItem(bottom);
    EXPECT_TRUE(selection_model.hasSelection());
    EXPECT_EQ(selection_model.selectedIndexes().size(), 4); // name, nr, material, thickness

    // checking back that top layer is selected
    expected  = {bottom};
    EXPECT_EQ(selection_model.selectedItems(), expected);
}
