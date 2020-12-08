// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "google_test.h"
#include "toyitems.h"
#include "toymodel.h"

using namespace ModelView;

//! Tests of toy interference item in the context of model and viewmodel.

class ToyLatticeItemTest : public ::testing::Test
{
public:
    ~ToyLatticeItemTest();
};

ToyLatticeItemTest::~ToyLatticeItemTest() = default;

//! Interference function (enabled/disabled).

TEST_F(ToyLatticeItemTest, rotationAngleEnabled)
{
    ToyItems::SampleModel model;
    auto lattice = model.insertItem<ToyItems::LatticeItem>();

    // by default integration flag is ON, rotation angle is disabled
    EXPECT_TRUE(lattice->property<bool>(ToyItems::LatticeItem::P_INTEGRATION));
    EXPECT_FALSE(lattice->getItem(ToyItems::LatticeItem::P_ROTATION_ANLE)->isEnabled());

    // switching integration OFF, checking that rotation is enabled
    lattice->setProperty(ToyItems::LatticeItem::P_INTEGRATION, false);
    EXPECT_TRUE(lattice->getItem(ToyItems::LatticeItem::P_ROTATION_ANLE)->isEnabled());
}
