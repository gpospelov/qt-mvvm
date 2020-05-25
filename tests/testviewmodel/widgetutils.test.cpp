// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "google_test.h"
#include "test_utils.h"
#include <QDebug>
#include <QDir>
#include <mvvm/widgets/widgetutils.h>

using namespace ModelView;

//! Testing functions from utils.

class WidgetUtilsTest : public ::testing::Test
{
public:
    ~WidgetUtilsTest();
};

WidgetUtilsTest::~WidgetUtilsTest() = default;

//! Initial state.

TEST_F(WidgetUtilsTest, initialState)
{
    auto home_path = QDir::homePath();
    auto test_dir = QString::fromStdString(TestUtils::TestOutputDir());
    auto expected = QString("~") + test_dir.mid(home_path.size());

    // "/home/user/build-debug/test_output" -> ~/build-debug/test_output"
    EXPECT_EQ(Utils::WithTildeHomePath(test_dir).toStdString(), expected.toStdString());
}
