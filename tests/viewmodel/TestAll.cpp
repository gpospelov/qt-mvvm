#include "google_test.h"
#include "qcustomplot.h"
#include <QStandardItem>
#include <QApplication>

int main(int argc, char** argv) {
    // FIXME find the way not to run app for all tests which doesn't use QWidget.
    // The problem here is because of ctest autodiscovery which runs given main at every test.
    QApplication app(argc, argv);
    Q_UNUSED(app)

    ModelView::Comparators::registerComparators();
    qRegisterMetaType<QStandardItem*>("QStandardItem*");

    qRegisterMetaType<QCPRange>("QCPRange");

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
