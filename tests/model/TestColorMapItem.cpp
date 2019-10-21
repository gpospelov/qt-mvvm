#include "google_test.h"
#include "colormapitem.h"
#include "sessionmodel.h"
#include "data2ditem.h"
#include "MockWidgets.h"
#include "axisitems.h"
#include "linkeditem.h"

using namespace ModelView;
using ::testing::_;

//! Testing ColorMapItem.

class TestColorMapItem : public ::testing::Test
{
public:
    ~TestColorMapItem();
};

TestColorMapItem::~TestColorMapItem() = default;

//! Initial state.

TEST_F(TestColorMapItem, initialState)
{
    ColorMapItem item;
    EXPECT_TRUE(item.dataItem() == nullptr);
}
