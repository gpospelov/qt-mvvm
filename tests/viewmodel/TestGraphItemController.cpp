#include "google_test.h"
#include "qcustomplot.h"
#include "graphitemcontroller.h"
#include "graphitem.h"
#include <QSignalSpy>

using namespace ModelView;

//! Testing AxisPlotControllers.

class TestGraphItemController : public ::testing::Test
{
public:
    ~TestGraphItemController();
};

TestGraphItemController::~TestGraphItemController() = default;

//! Initial state.

TEST_F(TestGraphItemController, initialState)
{
    EXPECT_EQ(1, 1);
}
