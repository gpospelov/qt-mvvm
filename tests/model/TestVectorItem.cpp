#include "google_test.h"
#include "vectoritem.h"
#include "sessionmodel.h"

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
    EXPECT_EQ(item.getItemValue(VectorItem::P_X).toDouble(), 0.0);
    EXPECT_EQ(item.getItemValue(VectorItem::P_Y).toDouble(), 0.0);
    EXPECT_EQ(item.getItemValue(VectorItem::P_Z).toDouble(), 0.0);

    // default label
    EXPECT_EQ(item.data(ItemDataRole::DATA).value<std::string>(), "(0, 0, 0)");
}

//! Initial state of item in model context

TEST_F(TestVectorItem, initialStateFromModel)
{
    SessionModel model;
    auto item = dynamic_cast<VectorItem*>(model.insertNewItem(Constants::VectorType));

    EXPECT_EQ(item->getItemValue(VectorItem::P_X).toDouble(), 0.0);
    EXPECT_EQ(item->getItemValue(VectorItem::P_Y).toDouble(), 0.0);
    EXPECT_EQ(item->getItemValue(VectorItem::P_Z).toDouble(), 0.0);

    // default label
    EXPECT_EQ(item->data(ItemDataRole::DATA).value<std::string>(), "(0, 0, 0)");

    // changing vector component
    item->setItemValue(VectorItem::P_X, 1.0);
    EXPECT_EQ(item->data(ItemDataRole::DATA).value<std::string>(), "(1, 0, 0)");
}
