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
#include <qcustomplot.h>

using namespace ModelView;

//! Testing "utilr for testing" defined in TestUtils namespace.

class CustomplotTestUtilsTest : public ::testing::Test {
};

//! Check methods to access graph bin centers and values.

TEST_F(CustomplotTestUtilsTest, binCentersbinValues)
{
    QCustomPlot custom_plot;

    auto graph = custom_plot.addGraph();
    graph->setData(QVector<double>({1, 2, 3}), QVector<double>({10, 20, 30}));

    EXPECT_EQ(TestUtils::binCenters(graph), std::vector<double>({1, 2, 3}));
    EXPECT_EQ(TestUtils::binValues(graph), std::vector<double>({10, 20, 30}));
}

//! Check methods to access graph errors.

TEST_F(CustomplotTestUtilsTest, binErrors)
{
    QCustomPlot custom_plot;

    auto graph = custom_plot.addGraph();
    graph->setData(QVector<double>({1, 2, 3}), QVector<double>({10, 20, 30}));

    EXPECT_EQ(TestUtils::binErrors(graph), std::vector<double>());

    auto errorBars = new QCPErrorBars(custom_plot.xAxis, custom_plot.yAxis);
    errorBars->removeFromLegend();
    errorBars->setDataPlottable(graph);
    errorBars->setData(QVector<double>({0.1, 0.2, 0.3}));

    EXPECT_EQ(TestUtils::binErrors(graph), std::vector<double>({0.1, 0.2, 0.3}));
}
