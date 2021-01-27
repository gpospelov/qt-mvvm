// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/plotting/pencontroller.h"

#include "google_test.h"
#include "mvvm/model/sessionmodel.h"
#include "mvvm/standarditems/plottableitems.h"
#include <qcustomplot.h>
#include <stdexcept>

using namespace ModelView;

//! Testing PenController.

class PenControllerTest : public ::testing::Test {
};

//! Initial state.

TEST_F(PenControllerTest, initialState)
{
    // Constructor accept valid QCPGraph
    EXPECT_THROW(PenController(nullptr), std::runtime_error);

    auto custom_plot = std::make_unique<QCustomPlot>();
    auto graph = custom_plot->addGraph();

    PenController controller(graph);
    EXPECT_EQ(controller.currentItem(), nullptr);
}

TEST_F(PenControllerTest, graphItemInInitialState)
{
    auto custom_plot = std::make_unique<QCustomPlot>();
    auto graph = custom_plot->addGraph();

    PenController controller(graph);

    SessionModel model;
    auto pen_item = model.insertItem<PenItem>();
    controller.setItem(pen_item);

    EXPECT_EQ(controller.currentItem(), pen_item);

    // parameters of graph in QCustomPlot
    EXPECT_EQ(graph->pen().color(), QColor(Qt::black));
    EXPECT_EQ(graph->pen().style(), Qt::SolidLine);
    EXPECT_EQ(graph->pen().width(), 1);
}

TEST_F(PenControllerTest, setPenSelected)
{
    auto custom_plot = std::make_unique<QCustomPlot>();
    auto graph = custom_plot->addGraph();

    PenController controller(graph);

    SessionModel model;
    auto pen_item = model.insertItem<PenItem>();
    controller.setItem(pen_item);

    pen_item->setSelected(true);

    // parameters of graph in QCustomPlot
    EXPECT_EQ(graph->pen().color(), QColor(Qt::black));
    EXPECT_EQ(graph->pen().style(), Qt::DashLine);
    EXPECT_EQ(graph->pen().width(), 1);
}

TEST_F(PenControllerTest, setColorAndWidth)
{
    auto custom_plot = std::make_unique<QCustomPlot>();
    auto graph = custom_plot->addGraph();

    PenController controller(graph);

    SessionModel model;
    auto pen_item = model.insertItem<PenItem>();
    controller.setItem(pen_item);

    pen_item->setProperty(PenItem::P_WIDTH, 2);
    pen_item->setProperty(PenItem::P_COLOR, QColor(Qt::red));

    // parameters of graph in QCustomPlot
    EXPECT_EQ(graph->pen().color(), QColor(Qt::red));
    EXPECT_EQ(graph->pen().style(), Qt::SolidLine);
    EXPECT_EQ(graph->pen().width(), 2);

    // set color via named color machinery
    pen_item->setNamedColor("azure");
    EXPECT_EQ(graph->pen().color().name(), QString("#f0ffff"));
}
