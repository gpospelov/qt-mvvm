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
#include <mvvm/interfaces/undostackinterface.h>
#include <mvvm/model/sessionmodel.h>
#include <mvvm/plotting/viewportaxisplotcontroller.h>
#include <mvvm/standarditems/axisitems.h>

using namespace ModelView;

//! Testing various undo/redo scenario.

class UndoScenarioTest : public ::testing::Test
{
public:
    ~UndoScenarioTest();
};

UndoScenarioTest::~UndoScenarioTest() = default;

//! Check undo/redo of ViewportAxisItem range, when it is listened by the controller.
//! Real-life bug.

TEST_F(UndoScenarioTest, undoViewportSetRange)
{
    // initialzing model, custom plot and controller
    SessionModel model;
    auto axisItem = model.insertItem<ViewportAxisItem>();
    axisItem->setProperty(ViewportAxisItem::P_MIN, 1.0);
    axisItem->setProperty(ViewportAxisItem::P_MAX, 2.0);
    QCustomPlot custom_plot;
    ViewportAxisPlotController controller(custom_plot.xAxis);
    controller.setItem(axisItem);

    // initial axis state
    EXPECT_EQ(custom_plot.xAxis->range().lower, 1.0);
    EXPECT_EQ(custom_plot.xAxis->range().upper, 2.0);

    // enabling undo/redo, and  its initial state
    model.setUndoRedoEnabled(true);
    auto stack = model.undoStack();
    EXPECT_FALSE(stack->canRedo());
    EXPECT_FALSE(stack->canUndo());
    EXPECT_EQ(stack->index(), 0);
    EXPECT_EQ(stack->count(), 0);

    // changing axis
    axisItem->setProperty(ViewportAxisItem::P_MAX, 20.0);
    EXPECT_FALSE(stack->canRedo());
    EXPECT_TRUE(stack->canUndo());
    EXPECT_EQ(stack->index(), 1);
    EXPECT_EQ(stack->count(), 1);
    EXPECT_EQ(custom_plot.xAxis->range().lower, 1.0);
    EXPECT_EQ(custom_plot.xAxis->range().upper, 20.0);

    // undoing
    stack->undo();
    EXPECT_TRUE(stack->canRedo());
    EXPECT_FALSE(stack->canUndo());
    EXPECT_EQ(stack->index(), 0);
    EXPECT_EQ(stack->count(), 1);
    EXPECT_EQ(custom_plot.xAxis->range().lower, 1.0);
    EXPECT_EQ(custom_plot.xAxis->range().upper, 2.0);

    // redoing
    stack->redo();
    EXPECT_FALSE(stack->canRedo());
    EXPECT_TRUE(stack->canUndo());
    EXPECT_EQ(stack->index(), 1);
    EXPECT_EQ(stack->count(), 1);
    EXPECT_EQ(custom_plot.xAxis->range().lower, 1.0);
    EXPECT_EQ(custom_plot.xAxis->range().upper, 20.0);
}
