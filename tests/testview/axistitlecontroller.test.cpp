// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/plotting/axistitlecontroller.h"

#include "google_test.h"
#include "mvvm/model/sessionmodel.h"
#include "mvvm/standarditems/plottableitems.h"
#include <qcustomplot.h>
#include <QFont>

using namespace ModelView;

//! Testing AxisTitleControllers.

class AxisTitleControllerTest : public ::testing::Test {
};

//! Initial state.

TEST_F(AxisTitleControllerTest, initialState)
{
    auto custom_plot = std::make_unique<QCustomPlot>();

    auto axis = custom_plot->xAxis;

    // controller shouldn''t change axis range
    AxisTitleController controller(axis);
    EXPECT_EQ(controller.currentItem(), nullptr);

    EXPECT_EQ(axis->label(), QString());
}

TEST_F(AxisTitleControllerTest, setTextItem)
{
    auto custom_plot = std::make_unique<QCustomPlot>();

    SessionModel model;
    auto textItem = model.insertItem<TextItem>();

    auto axis = custom_plot->xAxis;
    //    auto expected_pointSize = axis->labelFont().pointSize();
    //    auto expected_family = axis->labelFont().family();

    // this a values hardcoded in plottableitems.cpp. Shell we provide some customized way to create
    // TextItem with font/size suitable for QCPAxis ?
    const int expected_pointSize = 10;
    const std::string expected_family = "Noto Sans";

    // controller shouldn''t change axis range
    AxisTitleController controller(axis);
    controller.setItem(textItem);
    EXPECT_EQ(controller.currentItem(), textItem);

    EXPECT_EQ(axis->label(), QString());
    EXPECT_EQ(axis->labelFont().family().toStdString(), expected_family);
    EXPECT_EQ(axis->labelFont().pointSize(), expected_pointSize);
}

TEST_F(AxisTitleControllerTest, setFont)
{
    auto custom_plot = std::make_unique<QCustomPlot>();

    SessionModel model;
    auto textItem = model.insertItem<TextItem>();

    auto axis = custom_plot->xAxis;

    // controller shouldn''t change axis range
    AxisTitleController controller(axis);
    controller.setItem(textItem);
    EXPECT_EQ(controller.currentItem(), textItem);

    // setting new label
    const QString expected_text("abc");
    const QString expected_family("Helvetica");
    const int expected_size = 42;
    textItem->setProperty(TextItem::P_TEXT, expected_text.toStdString());
    textItem->setProperty(TextItem::P_SIZE, expected_size);
    textItem->setProperty(TextItem::P_FONT, expected_family.toStdString());

    // checking that label has updated
    EXPECT_EQ(axis->label(), expected_text);
    EXPECT_EQ(axis->labelFont().family(), expected_family);
    EXPECT_EQ(axis->labelFont().pointSize(), expected_size);
}
