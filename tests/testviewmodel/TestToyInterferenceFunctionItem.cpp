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

using namespace ModelView;

//! Tests of toy interference item in the context of model and viewmodel.

class ToyInterferenceFunctionItemTest : public ::testing::Test
{
public:
    ~ToyInterferenceFunctionItemTest();
};

ToyInterferenceFunctionItemTest::~ToyInterferenceFunctionItemTest() = default;

//! Interference function (enabled/disabled).

TEST_F(ToyInterferenceFunctionItemTest, rotationAngleEnabled)
{
    ToyItems::SampleModel model;
    auto interference = model.insertItem<ToyItems::InterferenceFunctionItem>();

    // by default integration flag is ON, rotation angle is disabled
    EXPECT_TRUE(interference->property<bool>(ToyItems::InterferenceFunctionItem::P_INTEGRATION));
    EXPECT_FALSE(
        interference->getItem(ToyItems::InterferenceFunctionItem::P_ROTATION_ANLE)->isEnabled());

    // switching integration OFF, checking that rotation is enabled
    interference->setProperty(ToyItems::InterferenceFunctionItem::P_INTEGRATION, false);
    EXPECT_TRUE(
        interference->getItem(ToyItems::InterferenceFunctionItem::P_ROTATION_ANLE)->isEnabled());
}
