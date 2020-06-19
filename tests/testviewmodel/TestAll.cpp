// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "google_test.h"
#include "qcustomplot.h"
#include <QApplication>
#include <QStandardItem>

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    ModelView::Comparators::registerComparators();

    return RUN_ALL_TESTS();
}
