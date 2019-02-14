#include "google_test.h"
#include "toy_includes.h"
#include "viewitems.h"
#include "defaultviewmodel.h"
#include <QSignalSpy>
#include <QDebug>

using namespace ModelView;

class TestDefaultViewModel : public ::testing::Test
{
public:
    ~TestDefaultViewModel();
};

TestDefaultViewModel::~TestDefaultViewModel() = default;

TEST_F(TestDefaultViewModel, initialState)
{
    DefaultViewModel viewModel;
    EXPECT_EQ(viewModel.rowCount(), 0);
    EXPECT_EQ(viewModel.columnCount(), 0);
}

//! Constructing ViewModel from a MultiLayer.
//! Checking that view items point co correct SessionItem.

TEST_F(TestDefaultViewModel, fromMultiLayer)
{
    ToyItems::SampleModel model;
    auto multiLayerItem = model.insertNewItem(ToyItems::Constants::MultiLayerType);

    DefaultViewModel viewModel;
    viewModel.setSessionModel(&model);
    EXPECT_EQ(viewModel.rowCount(), 1);
    EXPECT_EQ(viewModel.columnCount(), 2);

    // accessing first child under the root item
    QModelIndex mlIndex = viewModel.index(0, 0);

    // it should be ViewLabelItem looking at our MultiLayer item
    auto viewItem = dynamic_cast<ViewLabelItem*>(viewModel.itemFromIndex(mlIndex));
    EXPECT_TRUE(viewItem != nullptr);
    EXPECT_EQ(viewItem->item(), multiLayerItem);
}

//! Find ViewItem corresponding to given MultiLayer item.

TEST_F(TestDefaultViewModel, findMultiLayerView)
{
    ToyItems::SampleModel model;
    auto multiLayerItem = model.insertNewItem(ToyItems::Constants::MultiLayerType);

    DefaultViewModel viewModel;
    viewModel.setSessionModel(&model);

    auto views = viewModel.findViews(multiLayerItem);
    EXPECT_EQ(views.size(), 1);
    EXPECT_EQ(views.at(0)->item(), multiLayerItem);
}

//! Single property item in a model.

TEST_F(TestDefaultViewModel, fromPropertyItem)
{
    ToyItems::SampleModel model;
    auto propertyItem = model.insertNewItem(Constants::PropertyType);
    propertyItem->setData(42.0, ItemDataRole::DATA);

    DefaultViewModel viewModel;
    viewModel.setSessionModel(&model);
    EXPECT_EQ(viewModel.rowCount(), 1);
    EXPECT_EQ(viewModel.columnCount(), 2);

    // accessing first child under the root item
    QModelIndex labelIndex = viewModel.index(0, 0);
    QModelIndex dataIndex = viewModel.index(0, 1);

    // it should be ViewLabelItem looking at our MultiLayer item
    auto labelItem = dynamic_cast<ViewLabelItem*>(viewModel.itemFromIndex(labelIndex));
    EXPECT_TRUE(labelItem != nullptr);
    EXPECT_EQ(labelItem->item(), propertyItem);

    auto dataItem = dynamic_cast<ViewDataItem*>(viewModel.itemFromIndex(dataIndex));
    EXPECT_TRUE(dataItem != nullptr);
    EXPECT_EQ(dataItem->item(), propertyItem);
}

//! Find ViewItem's corresponding to given PropertyItem.

TEST_F(TestDefaultViewModel, findPropertyItemView)
{
    ToyItems::SampleModel model;
    auto propertyItem = model.insertNewItem(Constants::PropertyType);
    propertyItem->setData(42.0, ItemDataRole::DATA);

    DefaultViewModel viewModel;
    viewModel.setSessionModel(&model);

    auto views = viewModel.findViews(propertyItem);
    EXPECT_EQ(views.size(), 2);
}
