// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //


#include "google_test.h"
#include <mvvm/standarditems/vectoritem.h>
#include <mvvm/model/sessionmodel.h>

using namespace ModelView;

//! VectorItem tests.

class TestVectorItem : public ::testing::Test
{
public:
    ~TestVectorItem();
};

TestVectorItem::~TestVectorItem() = default;

//! Initial state of item when it is created outside of model context.

TEST_F(TestVectorItem, initialState)
{
    VectorItem item;

    EXPECT_FALSE(item.isEditable());

    EXPECT_EQ(item.property(VectorItem::P_X).value<double>(), 0.0);
    EXPECT_EQ(item.property(VectorItem::P_Y).value<double>(), 0.0);
    EXPECT_EQ(item.property(VectorItem::P_Z).value<double>(), 0.0);

    // default label
    EXPECT_EQ(item.data().value<std::string>(), "(0, 0, 0)");
}

//! Initial state of item in model context

TEST_F(TestVectorItem, initialStateFromModel)
{
    SessionModel model;
    auto item = model.insertItem<VectorItem>();

    EXPECT_EQ(item->property(VectorItem::P_X).value<double>(), 0.0);
    EXPECT_EQ(item->property(VectorItem::P_Y).value<double>(), 0.0);
    EXPECT_EQ(item->property(VectorItem::P_Z).value<double>(), 0.0);

    // default label
    EXPECT_EQ(item->data().value<std::string>(), "(0, 0, 0)");

    // changing vector component
    item->setProperty(VectorItem::P_X, 1.0);
    EXPECT_EQ(item->data().value<std::string>(), "(1, 0, 0)");
}
