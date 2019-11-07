// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "google_test.h"

int main(int argc, char** argv)
{
    ::testing::InitGoogleMock(&argc, argv);

    ModelView::Comparators::registerComparators();

    // run all google tests
    return RUN_ALL_TESTS();
}
