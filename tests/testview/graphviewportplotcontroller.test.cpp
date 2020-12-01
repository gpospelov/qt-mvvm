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
#include <mvvm/interfaces/undostackinterface.h>
#include <mvvm/model/sessionmodel.h>
#include <mvvm/plotting/graphviewportplotcontroller.h>
#include <mvvm/standarditems/axisitems.h>
#include <mvvm/standarditems/data1ditem.h>
#include <mvvm/standarditems/graphitem.h>
#include <mvvm/standarditems/graphviewportitem.h>

using namespace ModelView;

//! Testing GraphViewportPlotController.

class GraphViewportPlotControllerTest : public ::testing::Test
{
public:
    ~GraphViewportPlotControllerTest();
};

GraphViewportPlotControllerTest::~GraphViewportPlotControllerTest() = default;

//! Initial state.

TEST_F(GraphViewportPlotControllerTest, initialState)
{
    auto custom_plot = std::make_unique<QCustomPlot>();
    GraphViewportPlotController controller(custom_plot.get());
    EXPECT_EQ(custom_plot->graphCount(), 0);
}

//! Check ::setItem() method when no graphs exist.

TEST_F(GraphViewportPlotControllerTest, setItem)
{
    auto custom_plot = std::make_unique<QCustomPlot>();
    GraphViewportPlotController controller(custom_plot.get());

    // setting up controller with viewport item
    SessionModel model;
    auto item = model.insertItem<GraphViewportItem>();
    controller.setItem(item);

    // no graphs in empty GraphViewportItem
    EXPECT_EQ(custom_plot->graphCount(), 0);

    // axis should be [0, 1] as in defaule ViewportAxisItem
    EXPECT_DOUBLE_EQ(custom_plot->xAxis->range().lower, 0.0);
    EXPECT_DOUBLE_EQ(custom_plot->xAxis->range().upper, 1.0);
    EXPECT_DOUBLE_EQ(custom_plot->yAxis->range().lower, 0.0);
    EXPECT_DOUBLE_EQ(custom_plot->yAxis->range().upper, 1.0);
}

//! Check ::setItem() method when ViewPortItem contains graphs.

TEST_F(GraphViewportPlotControllerTest, addGraphAndSetItem)
{
    auto custom_plot = std::make_unique<QCustomPlot>();
    GraphViewportPlotController controller(custom_plot.get());

    // setting up controller with viewport item
    SessionModel model;
    auto viewport_item = model.insertItem<GraphViewportItem>();

    auto data_item = model.insertItem<Data1DItem>();
    const std::vector<double> expected_values = {1.0, 2.0, 3.0};
    const std::vector<double> expected_centers = {0.5, 1.5, 2.5};
    data_item->setAxis<FixedBinAxisItem>(3, 0.0, 3.0);
    data_item->setValues(expected_values);

    auto graph_item = model.insertItem<GraphItem>(viewport_item);
    graph_item->setDataItem(data_item);
    controller.setItem(viewport_item);

    // single graph on custom plot.
    EXPECT_EQ(custom_plot->graphCount(), 1);

    // QCustomPlot axis should correspond to
    EXPECT_DOUBLE_EQ(custom_plot->xAxis->range().lower, expected_centers[0]);
    EXPECT_DOUBLE_EQ(custom_plot->xAxis->range().upper, expected_centers[2]);
    EXPECT_DOUBLE_EQ(custom_plot->yAxis->range().lower, expected_values[0]);
    EXPECT_DOUBLE_EQ(custom_plot->yAxis->range().upper, expected_values[2]);
}

//! Checks consequitive graph adding/removal

TEST_F(GraphViewportPlotControllerTest, addAndRemoveGraphs)
{
    auto custom_plot = std::make_unique<QCustomPlot>();
    GraphViewportPlotController controller(custom_plot.get());

    // setting up controller with viewport item
    SessionModel model;
    auto viewport_item = model.insertItem<GraphViewportItem>();
    controller.setItem(viewport_item);

    // No graphs yet.
    EXPECT_EQ(custom_plot->graphCount(), 0);

    // Populating with data items
    auto data1 = model.insertItem<Data1DItem>();
    const std::vector<double> expected_values1 = {1.0, 2.0, 3.0};
    const std::vector<double> expected_centers = {0.5, 1.5, 2.5};
    data1->setAxis<FixedBinAxisItem>(3, 0.0, 3.0);
    data1->setValues(expected_values1);

    auto data2 = model.insertItem<Data1DItem>();
    const std::vector<double> expected_values2 = {4.0, 5.0, 6.0};
    data2->setAxis<FixedBinAxisItem>(3, 0.0, 3.0);
    data2->setValues(expected_values2);

    // adding graph item to viewport
    auto graph_item1 = model.insertItem<GraphItem>(viewport_item, {"", 0});

    // check that QCustomPlot knows about graph
    EXPECT_EQ(custom_plot->graphCount(), 1);

    graph_item1->setDataItem(data1);

    // check that QCustomPlot knows about graph
    EXPECT_EQ(custom_plot->graphCount(), 1);

    // adding secong graph
    auto graph_item2 = model.insertItem<GraphItem>(viewport_item, {"", 1});
    graph_item2->setDataItem(data2);

    // check that QCustomPlot knows about two graph
    EXPECT_EQ(custom_plot->graphCount(), 2);

    // Checking that viewport min, max adjusted to both graphs when manually call update_viewport()
    viewport_item->setViewportToContent();
    EXPECT_DOUBLE_EQ(custom_plot->xAxis->range().lower, expected_centers[0]);
    EXPECT_DOUBLE_EQ(custom_plot->xAxis->range().upper, expected_centers[2]);
    EXPECT_DOUBLE_EQ(custom_plot->yAxis->range().lower, expected_values1[0]);
    EXPECT_DOUBLE_EQ(custom_plot->yAxis->range().upper, expected_values2[2]);

    // removing one GraphItem
    model.removeItem(viewport_item, {ViewportItem::T_ITEMS, 1});

    // only single graph should remain on QCustomPlot3
    EXPECT_EQ(custom_plot->graphCount(), 1);
}

//! Checks consequitive graph adding/removal

TEST_F(GraphViewportPlotControllerTest, addMoreGraphs)
{
    auto custom_plot = std::make_unique<QCustomPlot>();
    GraphViewportPlotController controller(custom_plot.get());

    // setting up controller with viewport item
    SessionModel model;
    auto viewport_item = model.insertItem<GraphViewportItem>();
    controller.setItem(viewport_item);

    // No graphs yet.
    EXPECT_EQ(custom_plot->graphCount(), 0);

    // adding graph item to viewport
    model.insertItem<GraphItem>(viewport_item);
    EXPECT_EQ(custom_plot->graphCount(), 1);

    model.insertItem<GraphItem>(viewport_item);
    EXPECT_EQ(custom_plot->graphCount(), 2);

    model.insertItem<GraphItem>(viewport_item);
    EXPECT_EQ(custom_plot->graphCount(), 3);
}

//! Checks The fucntionality of selection in the viewport

TEST_F(GraphViewportPlotControllerTest, checkVisible)
{
    // Convenience
    struct FindVisible {
        static std::vector<QCPAbstractPlottable*> findVisible(const QCustomPlot* custom_plot)
        {
            std::vector<QCPAbstractPlottable*> output;
            for (int i = 0; i < custom_plot->graphCount(); ++i) {
                if (custom_plot->graph(i)->visible())
                    output.push_back(custom_plot->graph(i));
            }
            return output;
        }
    };

    // custom plot setup
    auto custom_plot = std::make_unique<QCustomPlot>();
    GraphViewportPlotController controller(custom_plot.get());

    // setting up controller with viewport item
    SessionModel model;
    auto viewport_item = model.insertItem<GraphViewportItem>();
    controller.setItem(viewport_item);

    // adding graph item to viewport
    auto first_plot = model.insertItem<GraphItem>(viewport_item);
    auto second_plot = model.insertItem<GraphItem>(viewport_item);
    auto third_plot = model.insertItem<GraphItem>(viewport_item);
    EXPECT_EQ(custom_plot->graphCount(), 3);

    viewport_item->setVisible(std::vector<GraphItem*>{first_plot});
    EXPECT_EQ(FindVisible::findVisible(custom_plot.get()).size(), 1);

    viewport_item->setVisible(std::vector<GraphItem*>{second_plot, third_plot});
    EXPECT_EQ(FindVisible::findVisible(custom_plot.get()).size(), 2);

    viewport_item->setAllVisible();
    EXPECT_EQ(FindVisible::findVisible(custom_plot.get()).size(), 3);
}

//! Two GraphViewportItem's and switch between them.

TEST_F(GraphViewportPlotControllerTest, switchBetweenTwoViewports)
{
    auto custom_plot = std::make_unique<QCustomPlot>();
    GraphViewportPlotController controller(custom_plot.get());

    // setting up controller with viewport item
    SessionModel model;
    auto viewport_item0 = model.insertItem<GraphViewportItem>();
    auto viewport_item1 = model.insertItem<GraphViewportItem>();

    auto data_item = model.insertItem<Data1DItem>();
    const std::vector<double> expected_values = {1.0, 2.0, 3.0};
    const std::vector<double> expected_centers = {0.5, 1.5, 2.5};
    data_item->setAxis<FixedBinAxisItem>(3, 0.0, 3.0);
    data_item->setValues(expected_values);

    auto graph_item = model.insertItem<GraphItem>(viewport_item0);
    graph_item->setDataItem(data_item);
    controller.setItem(viewport_item0);

    // single graph on custom plot.
    EXPECT_EQ(custom_plot->graphCount(), 1);

    // switch to second (empty) viewport, QCustomPlot should have no graphs
    controller.setItem(viewport_item1);
    EXPECT_EQ(custom_plot->graphCount(), 0);
}

//! Adding graph, then undo, then redo again.

TEST_F(GraphViewportPlotControllerTest, addGraphUndoRedo)
{
    auto custom_plot = std::make_unique<QCustomPlot>();
    GraphViewportPlotController controller(custom_plot.get());

    // setting up controller with viewport item
    SessionModel model;

    auto viewport_item = model.insertItem<GraphViewportItem>();
    controller.setItem(viewport_item);

    // No graphs yet.
    EXPECT_EQ(custom_plot->graphCount(), 0);

    // Populating with data items
    auto data1 = model.insertItem<Data1DItem>();
    const std::vector<double> expected_values = {1.0, 2.0, 3.0};
    const std::vector<double> expected_centers = {0.5, 1.5, 2.5};
    data1->setAxis<FixedBinAxisItem>(3, 0.0, 3.0);
    data1->setValues(expected_values);

    // beginning of our undo/redo story
    model.setUndoRedoEnabled(true);
    EXPECT_EQ(model.undoStack()->index(), 0);
    EXPECT_EQ(model.undoStack()->count(), 0);

    // adding graph item to viewport
    auto graph_item = model.insertItem<GraphItem>(viewport_item, {"", 0});
    EXPECT_EQ(model.undoStack()->index(), 1);
    EXPECT_EQ(model.undoStack()->count(), 1);

    // assigning data to graph
    graph_item->setDataItem(data1);
    EXPECT_EQ(model.undoStack()->index(), 2);
    EXPECT_EQ(model.undoStack()->count(), 2);

    // validating graph in custom plot
    EXPECT_EQ(custom_plot->graphCount(), 1);
    EXPECT_EQ(TestUtils::binCenters(custom_plot->graph()), expected_centers);
    EXPECT_EQ(TestUtils::binValues(custom_plot->graph()), expected_values);

    // undoing data assignment
    model.undoStack()->undo();
    EXPECT_EQ(model.undoStack()->index(), 1);
    EXPECT_EQ(model.undoStack()->count(), 2);

    // graph is still there, but empty
    EXPECT_EQ(custom_plot->graphCount(), 1);
    EXPECT_EQ(TestUtils::binCenters(custom_plot->graph()), std::vector<double>());
    EXPECT_EQ(TestUtils::binValues(custom_plot->graph()), std::vector<double>());
    EXPECT_EQ(graph_item->dataItem(), nullptr);

    // redoing data assignment
    model.undoStack()->redo();
    EXPECT_EQ(model.undoStack()->index(), 2);
    EXPECT_EQ(model.undoStack()->count(), 2);

    // graph is complete again
    EXPECT_EQ(graph_item->dataItem(), data1);
    EXPECT_EQ(custom_plot->graphCount(), 1);
    EXPECT_EQ(TestUtils::binCenters(custom_plot->graph()), expected_centers);
    EXPECT_EQ(TestUtils::binValues(custom_plot->graph()), expected_values);
}

//! Adding graph together with data in macro, then undo, then redo again.

TEST_F(GraphViewportPlotControllerTest, addGraphUndoRedoMacro)
{
    auto custom_plot = std::make_unique<QCustomPlot>();
    GraphViewportPlotController controller(custom_plot.get());

    // setting up controller with viewport item
    SessionModel model;

    auto viewport_item = model.insertItem<GraphViewportItem>();
    controller.setItem(viewport_item);

    // No graphs yet.
    EXPECT_EQ(custom_plot->graphCount(), 0);

    // beginning of our undo/redo story
    model.setUndoRedoEnabled(true);
    EXPECT_EQ(model.undoStack()->index(), 0);
    EXPECT_EQ(model.undoStack()->count(), 0);

    // adding data and graph as macro
    model.undoStack()->beginMacro("addGraph");
    // Populating with data items
    auto data1 = model.insertItem<Data1DItem>();
    const std::vector<double> expected_values = {1.0, 2.0, 3.0};
    const std::vector<double> expected_centers = {0.5, 1.5, 2.5};
    data1->setAxis<FixedBinAxisItem>(3, 0.0, 3.0);
    data1->setValues(expected_values);
    auto data_identifier = data1->identifier();
    // adding graph item to viewport
    auto graph_item = model.insertItem<GraphItem>(viewport_item, {"", 0});
    // assigning data to graph
    graph_item->setDataItem(data1);
    model.undoStack()->endMacro();

    EXPECT_EQ(viewport_item->graphItems()[0]->dataItem(), model.topItem<Data1DItem>());

    EXPECT_EQ(model.undoStack()->index(), 1);
    EXPECT_EQ(model.undoStack()->count(), 1);

    // validating graph in custom plot
    EXPECT_EQ(custom_plot->graphCount(), 1);
    EXPECT_EQ(TestUtils::binCenters(custom_plot->graph()), expected_centers);
    EXPECT_EQ(TestUtils::binValues(custom_plot->graph()), expected_values);

    // undoing macro
    model.undoStack()->undo();
    EXPECT_EQ(model.undoStack()->index(), 0);
    EXPECT_EQ(model.undoStack()->count(), 1);

    // no graph and no items
    EXPECT_EQ(viewport_item->graphItems().size(), 0);
    EXPECT_EQ(model.topItem<Data1DItem>(), nullptr);
    EXPECT_EQ(custom_plot->graphCount(), 0);

    // redoing macro
    model.undoStack()->redo();
    EXPECT_EQ(custom_plot->graphCount(), 1);
    EXPECT_EQ(viewport_item->graphItems().size(), 1);

    EXPECT_EQ(model.topItem<Data1DItem>()->identifier(), data_identifier);
    EXPECT_EQ(viewport_item->graphItems()[0]->dataItem(), model.topItem<Data1DItem>());

    EXPECT_EQ(TestUtils::binCenters(custom_plot->graph()), expected_centers);
    EXPECT_EQ(TestUtils::binValues(custom_plot->graph()), expected_values);
}
