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
#include "layerviewmodel.h"
#include "samplemodel.h"
#include "test_utils.h"
#include <mvvm/viewmodel/viewmodelutils.h>

using namespace ModelView;

//! Tests of LayerViewModel.

class LayerViewModelTest : public ::testing::Test
{
public:
    ~LayerViewModelTest();
};

LayerViewModelTest::~LayerViewModelTest() = default;

//! Layout of LayerViewModel for two layer system.

TEST_F(LayerViewModelTest, twoLayerSystem)
{
    SampleModel model;
    auto multilayer = model.insertItem<MultiLayerItem>();
    auto top = model.insertItem<LayerItem>(multilayer);
    auto bottom = model.insertItem<LayerItem>(multilayer);

    LayerViewModel viewmodel(&model);
    viewmodel.setRootSessionItem(multilayer);

    EXPECT_EQ(viewmodel.rowCount(), 2);
    EXPECT_EQ(viewmodel.columnCount(), 4); // name, Nr, material, thickness

    // check indexes in first row and their correspondance to top-layer related items
    QModelIndexList selection = {viewmodel.index(0, 0), viewmodel.index(0, 1),
                                 viewmodel.index(0, 2), viewmodel.index(0, 3)};
    std::vector<SessionItem*> expected = {top, nullptr, top->getItem(LayerItem::P_MATERIAL),
                                          top->getItem(LayerItem::P_THICKNESS)};
    EXPECT_EQ(Utils::ItemsFromIndex(selection), expected);

    // check indexes in first row and their correspondance to bottom-layer related items
    selection = {viewmodel.index(1, 0), viewmodel.index(1, 1), viewmodel.index(1, 2),
                 viewmodel.index(1, 3)};
    expected = {bottom, nullptr, bottom->getItem(LayerItem::P_MATERIAL),
                bottom->getItem(LayerItem::P_THICKNESS)};
    EXPECT_EQ(Utils::ItemsFromIndex(selection), expected);
}
