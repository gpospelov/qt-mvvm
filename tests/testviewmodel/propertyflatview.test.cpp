// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "google_test.h"
#include "toy_includes.h"
#include <QGridLayout>
#include <mvvm/model/sessionmodel.h>
#include <mvvm/standarditems/vectoritem.h>
#include <mvvm/widgets/propertyflatview.h>

using namespace ModelView;

//! Tests of PropertyFlatView class.

class PropertyFlatViewTest : public ::testing::Test
{
public:
    ~PropertyFlatViewTest();

    //! Returns vector representing enable status of widgets in layout.

    std::vector<int> enable_status(PropertyFlatView& flat_view)
    {
        std::vector<int> result;
        auto layout = flat_view.findChild<QGridLayout*>();
        for (int row = 0; row < layout->rowCount(); ++row)
            for (int col = 0; col < layout->columnCount(); ++col)
                result.push_back(
                    static_cast<int>(layout->itemAtPosition(row, col)->widget()->isEnabled()));
        return result;
    }
};

PropertyFlatViewTest::~PropertyFlatViewTest() = default;

TEST_F(PropertyFlatViewTest, layoutForVector)
{
    SessionModel model;
    auto vector_item = model.insertItem<VectorItem>();

    PropertyFlatView flat_view;
    flat_view.setItem(vector_item);

    auto layout = flat_view.findChild<QGridLayout*>();
    ASSERT_TRUE(layout != nullptr);

    EXPECT_EQ(layout->rowCount(), 3);
    EXPECT_EQ(layout->columnCount(), 2);
    std::vector<int> expected_enabled = {1, 1, 1, 1, 1, 1};
}

TEST_F(PropertyFlatViewTest, appearanceForItem)
{
    SessionModel model;
    auto vector_item = model.insertItem<VectorItem>();
    auto x_item = vector_item->getItem(VectorItem::P_X);

    x_item->setEnabled(false);

    PropertyFlatView flat_view;
    flat_view.setItem(vector_item);

    auto layout = flat_view.findChild<QGridLayout*>();
    ASSERT_TRUE(layout != nullptr);

    EXPECT_EQ(layout->rowCount(), 3);
    EXPECT_EQ(layout->columnCount(), 2);
    std::vector<int> expected_enabled = {0, 0, 1, 1, 1, 1};
    EXPECT_EQ(enable_status(flat_view), expected_enabled);

    // enabling x item
    x_item->setEnabled(true);
    expected_enabled = {1, 1, 1, 1, 1, 1};
    EXPECT_EQ(enable_status(flat_view), expected_enabled);
}

// TEST_F(PropertyFlatViewTest, layoutForShapeGroup)
//{
//    ToyItems::SampleModel model;
//    auto group_item = model.insertItem<ToyItems::ShapeGroupItem>();

//    PropertyFlatView flat_view;
//    flat_view.setItem(model.rootItem());

//    auto layout = flat_view.findChild<QGridLayout*>();
//    ASSERT_TRUE(layout != nullptr);

//    EXPECT_EQ(layout->rowCount(), 2); // group item and radius of sphere
//    EXPECT_EQ(layout->columnCount(), 2);

////    group_item->setCurrentType(ToyItems::Constants::CylinderType);
////    EXPECT_EQ(layout->rowCount(), 3); // group item, cylinder height and radius
////    EXPECT_EQ(layout->columnCount(), 2);
//}
