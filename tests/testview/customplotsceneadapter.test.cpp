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
#include <mvvm/plotting/customplotsceneadapter.h>

using namespace ModelView;

//! Testing CustomPlotSceneAdapter.

class CustomPlotSceneAdapterTest : public ::testing::Test
{
public:
    ~CustomPlotSceneAdapterTest();
};

CustomPlotSceneAdapterTest::~CustomPlotSceneAdapterTest() = default;

//! Scenario when QCustomPlot destroyed before adapter.

TEST_F(CustomPlotSceneAdapterTest, customPlotBeforeAdapter)
{
    auto custom_plot = std::make_unique<QCustomPlot>();
    auto adapter = std::make_unique<CustomPlotSceneAdapter>(custom_plot.get());

    // destroying QCustomPlot
    custom_plot.reset();

    EXPECT_EQ(42, adapter->toSceneX(42));
    EXPECT_EQ(42, adapter->toSceneY(42));
    EXPECT_EQ(42, adapter->fromSceneX(42));
    EXPECT_EQ(42, adapter->fromSceneY(42));
}

TEST_F(CustomPlotSceneAdapterTest, adapterBeforeCustomPlot)
{
    auto custom_plot = std::make_unique<QCustomPlot>();
    auto adapter = std::make_unique<CustomPlotSceneAdapter>(custom_plot.get());

    adapter.reset();
    custom_plot.reset(); // would cause SEGFAULT if connection to adapter still exists
}
