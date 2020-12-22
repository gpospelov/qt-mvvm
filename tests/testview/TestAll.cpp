// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "customplot_test_utils.h"
#include "google_test.h"
#include "qcustomplot.h"
#include <QApplication>
#include <QStandardItem>
#include <gmock/gmock.h>

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);

    ModelView::Comparators::registerComparators();
    qRegisterMetaType<QStandardItem*>("QStandardItem*");
    qRegisterMetaType<QCPRange>("QCPRange");

    QApplication app(argc, argv);
    Q_UNUSED(app)

    return RUN_ALL_TESTS();
}
