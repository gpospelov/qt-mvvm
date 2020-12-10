// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "google_test.h"
#include <gmock/gmock.h>
#include "qcustomplot.h"
#include "customplot_test_utils.h"
#include <QApplication>
#include <QStandardItem>

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);

    ModelView::Comparators::registerComparators();
    qRegisterMetaType<QStandardItem*>("QStandardItem*");
    qRegisterMetaType<QCPRange>("QCPRange");

    // FIXME find the way not to run app for all tests which doesn't use QWidget.
    // The problem here is because of ctest autodiscovery which runs given main at every test.
    QApplication app(argc, argv);
    Q_UNUSED(app)

    return RUN_ALL_TESTS();
}
