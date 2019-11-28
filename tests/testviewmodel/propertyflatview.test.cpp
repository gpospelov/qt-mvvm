// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "google_test.h"
#include <mvvm/widgets/propertyflatview.h>
#include <mvvm/standarditems/vectoritem.h>
#include <mvvm/model/sessionmodel.h>
#include <QGridLayout>

using namespace ModelView;

//! Tests of PropertyFlatView class.

class PropertyFlatViewTest : public ::testing::Test
{
public:
    ~PropertyFlatViewTest();

};

PropertyFlatViewTest::~PropertyFlatViewTest() = default;

TEST_F(PropertyFlatViewTest, vectorInFlatView)
{
    SessionModel model;
    auto vector_item = model.insertItem<VectorItem>();

    PropertyFlatView flat_view;
    flat_view.setItem(vector_item);

    auto layout = flat_view.findChild<QGridLayout*>();
    ASSERT_TRUE(layout != nullptr);

    EXPECT_EQ(layout->rowCount(), 3);
    EXPECT_EQ(layout->columnCount(), 2);
}

