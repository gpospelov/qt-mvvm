#include "google_test.h"
#include "toy_includes.h"

using namespace ModelView;

//! Tests of toy interference item in the context of model and viewmodel.

class TestToyInterference : public ::testing::Test
{
public:
    ~TestToyInterference();
};

TestToyInterference::~TestToyInterference() = default;

//! Interference function (enabled/disabled).

TEST_F(TestToyInterference, rotationAngleEnabled)
{
    ToyItems::SampleModel model;
    auto interference = dynamic_cast<ToyItems::InterferenceFunction*>(
        model.insertNewItem(ToyItems::Constants::InterferenceType));

    // by default integration flag is ON, rotation angle is disabled
    EXPECT_TRUE(interference->getItemValue(ToyItems::InterferenceFunction::P_INTEGRATION).toBool());
    EXPECT_FALSE(
        interference->getItem(ToyItems::InterferenceFunction::P_ROTATION_ANLE)->isEnabled());

    // switching integration OFF, checking that rotation is enabled
    interference->setItemValue(ToyItems::InterferenceFunction::P_INTEGRATION, false);
    EXPECT_TRUE(
        interference->getItem(ToyItems::InterferenceFunction::P_ROTATION_ANLE)->isEnabled());
}
