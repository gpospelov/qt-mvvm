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
using namespace ToyItems;

//! Test toy LatticeItem.

class ToyItemsLatticeTest : public ::testing::Test {
};

//! Business logice (enabled/disabled).

TEST_F(ToyItemsLatticeTest, ToyItemsLatticeTest)
{
    ToyItems::SampleModel model;
    auto lattice = model.insertItem<LatticeItem>();

    // by default integration flag is ON, rotation angle is disabled
    EXPECT_TRUE(lattice->property<bool>(LatticeItem::P_INTEGRATION));
    EXPECT_FALSE(lattice->getItem(LatticeItem::P_ROTATION_ANLE)->isEnabled());

    // switching integration OFF, checking that rotation is enabled
    lattice->setProperty(LatticeItem::P_INTEGRATION, false);
    EXPECT_TRUE(lattice->getItem(LatticeItem::P_ROTATION_ANLE)->isEnabled());
}
