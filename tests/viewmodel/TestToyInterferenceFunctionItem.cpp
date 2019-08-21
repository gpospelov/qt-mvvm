#include "google_test.h"
#include "toy_includes.h"

using namespace ModelView;

//! Tests of toy interference item in the context of model and viewmodel.

class TestToyInterferenceFunctionItem : public ::testing::Test
{
public:
    ~TestToyInterferenceFunctionItem();
};

TestToyInterferenceFunctionItem::~TestToyInterferenceFunctionItem() = default;

//! Interference function (enabled/disabled).

TEST_F(TestToyInterferenceFunctionItem, rotationAngleEnabled)
{
    ToyItems::SampleModel model;
    auto interference = dynamic_cast<ToyItems::InterferenceFunctionItem*>(
        model.insertNewItem(ToyItems::Constants::InterferenceType));

    // by default integration flag is ON, rotation angle is disabled
    EXPECT_TRUE(interference->property(ToyItems::InterferenceFunctionItem::P_INTEGRATION).toBool());
    EXPECT_FALSE(
        interference->getItem(ToyItems::InterferenceFunctionItem::P_ROTATION_ANLE)->isEnabled());

    // switching integration OFF, checking that rotation is enabled
    interference->setProperty(ToyItems::InterferenceFunctionItem::P_INTEGRATION, false);
    EXPECT_TRUE(
        interference->getItem(ToyItems::InterferenceFunctionItem::P_ROTATION_ANLE)->isEnabled());
}
