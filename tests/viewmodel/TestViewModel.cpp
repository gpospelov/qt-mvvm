#include "google_test.h"
#include "viewmodel.h"
#include "viewitems.h"
#include "toy_includes.h"
#include <QDebug>

using namespace ModelView;

class TestViewModel : public ::testing::Test
{
public:
    ~TestViewModel();
};

TestViewModel::~TestViewModel() = default;

TEST_F(TestViewModel, initialState)
{
    ViewModel viewModel;
    EXPECT_EQ(viewModel.rowCount(), 0);
    EXPECT_EQ(viewModel.columnCount(), 0);
}

TEST_F(TestViewModel, fromMultiLayer)
{
    ToyItems::SampleModel model;
    auto multiLayerItem = model.insertNewItem(ToyItems::Constants::MultiLayerType);

    ViewModel viewModel;
    viewModel.setSessionModel(&model);
    EXPECT_EQ(viewModel.rowCount(), 1);
    EXPECT_EQ(viewModel.columnCount(), 2);

    // accessing first child under the root item
    QModelIndex mlIndex  = viewModel.index(0,0);

    // it should be ViewLabelItem looking at out MultiLayer item
    auto viewItem = dynamic_cast<ViewLabelItem*>(viewModel.itemFromIndex(mlIndex));
    EXPECT_TRUE(viewItem != nullptr);
    EXPECT_EQ(viewItem->item(), multiLayerItem);
}

TEST_F(TestViewModel, fromLayer)
{
    ToyItems::SampleModel model;
    auto item = model.insertNewItem(ToyItems::Constants::LayerType);

    ViewModel viewModel;
    viewModel.setSessionModel(&model);
    EXPECT_EQ(viewModel.rowCount(), 1);
    EXPECT_EQ(viewModel.columnCount(), 2);

    QModelIndex layerIndex = viewModel.index(0, 0);
    EXPECT_EQ(viewModel.rowCount(layerIndex), 1);
    EXPECT_EQ(viewModel.columnCount(layerIndex), 2);

}


