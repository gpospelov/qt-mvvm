// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "google_test.h"
#include "layereditoractions.h"
#include "layeritems.h"
#include "layerselectionmodel.h"
#include "layerviewmodel.h"
#include "samplemodel.h"
#include "test_utils.h"
#include <mvvm/viewmodel/viewmodelutils.h>

using namespace ModelView;

//! Tests of LayerEditorActions.

class LayerEditorActionsTest : public ::testing::Test
{
public:
    ~LayerEditorActionsTest();
};

LayerEditorActionsTest::~LayerEditorActionsTest() = default;

//! Adds new layer after selected layer.

TEST_F(LayerEditorActionsTest, addNewLayerAfterSelection)
{
    // creating multi-layer with two layers
    SampleModel model;
    auto multilayer = model.insertItem<MultiLayerItem>();
    auto top = model.insertItem<LayerItem>(multilayer);
    auto bottom = model.insertItem<LayerItem>(multilayer);

    // creating viewmodel looking at multi-layer
    LayerViewModel viewmodel(&model);
    viewmodel.setRootSessionItem(multilayer);

    // selecting top layer
    LayerSelectionModel selection_model(&viewmodel);
    selection_model.selectItem(top);

    // initializing actions.
    LayerEditorActions actions(&model);
    actions.setSelectionModel(&selection_model);

    // adding new layer after selection
    actions.onAddLayer();

    auto layers = multilayer->getItems(MultiLayerItem::T_LAYERS);
    EXPECT_EQ(layers.size(), 3);
    EXPECT_EQ(layers.at(0), top);
    EXPECT_EQ(layers.at(2), bottom);

    // checking, that new layer is selected
    std::vector<SessionItem*> selected = {layers.at(1)};
    EXPECT_EQ(selection_model.selectedItems(), selected);
}
