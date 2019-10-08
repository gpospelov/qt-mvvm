#include "google_test.h"
#include "sessionmodel.h"
#include "viewitems.h"
#include "viewdataitem.h"
#include "defaultviewmodel.h"
#include "vectoritem.h"
#include <QSignalSpy>

using namespace ModelView;

//! Tests of VectorItem in the context of DefaultViewModel.

class TestVectorItemView : public ::testing::Test
{
public:
    ~TestVectorItemView();
};

TestVectorItemView::~TestVectorItemView() = default;

//! Constructing ViewModel from a VectorItem.
//! Checking that view items point to correct SessionItem.

TEST_F(TestVectorItemView, fromVector)
{
    SessionModel model;
    auto vectorItem = model.insertItem<VectorItem>();

    // constructing viewModel from sample model
    DefaultViewModel viewModel(&model);

    // root item should have one child, item looking at our vectorItem
    EXPECT_EQ(viewModel.rowCount(), 1);
    EXPECT_EQ(viewModel.columnCount(), 2);

    // accessing to viewItem representing layerItem
    QModelIndex vectorIndex = viewModel.index(0, 0);

    // it has three rows and two columns, corresponding to our P_X, P_Y, P_Z
    EXPECT_EQ(viewModel.rowCount(vectorIndex), 3);
    EXPECT_EQ(viewModel.columnCount(vectorIndex), 2);

    // ViewLabelItem and ViewDataItem correspondint to P_X
    auto pxLabel
        = dynamic_cast<ViewLabelItem*>(viewModel.itemFromIndex(viewModel.index(0, 0, vectorIndex)));
    auto pxData
        = dynamic_cast<ViewDataItem*>(viewModel.itemFromIndex(viewModel.index(0, 1, vectorIndex)));
    EXPECT_EQ(pxLabel->item(), vectorItem->getItem(VectorItem::P_X));
    EXPECT_EQ(pxData->item(), vectorItem->getItem(VectorItem::P_X));

    // ViewLabelItem and ViewDataItem correspondint to P_Y
    pxLabel
        = dynamic_cast<ViewLabelItem*>(viewModel.itemFromIndex(viewModel.index(1, 0, vectorIndex)));
    pxData
        = dynamic_cast<ViewDataItem*>(viewModel.itemFromIndex(viewModel.index(1, 1, vectorIndex)));
    EXPECT_EQ(pxLabel->item(), vectorItem->getItem(VectorItem::P_Y));
    EXPECT_EQ(pxData->item(), vectorItem->getItem(VectorItem::P_Y));

    // ViewLabelItem and ViewDataItem correspondint to P_Z
    pxLabel
        = dynamic_cast<ViewLabelItem*>(viewModel.itemFromIndex(viewModel.index(2, 0, vectorIndex)));
    pxData
        = dynamic_cast<ViewDataItem*>(viewModel.itemFromIndex(viewModel.index(2, 1, vectorIndex)));
    EXPECT_EQ(pxLabel->item(), vectorItem->getItem(VectorItem::P_Z));
    EXPECT_EQ(pxData->item(), vectorItem->getItem(VectorItem::P_Z));
}
