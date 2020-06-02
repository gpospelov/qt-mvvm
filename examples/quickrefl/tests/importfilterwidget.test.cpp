// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "google_test.h"
#include "importfilterwidget.h"
#include "importlogic.h"
#include "importlinefilterwidget.h"

#include <QComboBox>
#include <QLineEdit>
#include <QListWidget>
#include <QListWidgetItem>
#include <QSignalSpy>
#include <QVariant>

#include <string>
#include <vector>

using namespace DataImportGui;

//! Test the data column item
class FilterWidgetTest : public ::testing::Test
{
public:
    FilterWidgetTest();
    ~FilterWidgetTest();

    ImportFilterWidget* filter_widget{nullptr};
    DataImportLogic::ImportLogic* import_logic{nullptr};
    QListWidget* p_list_widget;
};

//! The constructor
FilterWidgetTest::FilterWidgetTest()
{
    import_logic  = new DataImportLogic::ImportLogic();
    filter_widget = new ImportFilterWidget(import_logic);

    p_list_widget = filter_widget->findChild<QListWidget*>("filter_list_widget");
}

//! The destructor
FilterWidgetTest::~FilterWidgetTest()
{
    delete filter_widget;
    delete import_logic;
}

//! Test default constructor
TEST_F(FilterWidgetTest, testDefaultContructor)
{
    EXPECT_EQ(0, p_list_widget->count());
}

//! Test the add line filter functionality
TEST_F(FilterWidgetTest, testAddLineFiler)
{
    for (int i = 0; i < 40; ++i){
        EXPECT_EQ(i, p_list_widget->count());
        EXPECT_EQ(import_logic->lineFilterOrder().size(), p_list_widget->count());
        filter_widget->addLineFilter();
    }
}

//! Test remove line filter funcitonality
TEST_F(FilterWidgetTest, testRemoveLineFilter)
{
    for (int i = 0; i < 40; ++i){
        filter_widget->addLineFilter();
    }

    for (int i = 0; i < 3; ++i){
        p_list_widget->setCurrentRow(i*10);
        filter_widget->removeLineFilter();
        EXPECT_EQ(40-1-i, p_list_widget->count());
        EXPECT_EQ(import_logic->lineFilterOrder().size(), p_list_widget->count());
    }
}

//! Test the the type chnaged signal propagation
TEST_F(FilterWidgetTest, testNameChange)
{
    for (int i = 0; i < 5; ++i){
        filter_widget->addLineFilter();
    }

    QSignalSpy spy_name(filter_widget, &ImportFilterWidget::namesChanged);

    auto item = p_list_widget->item(2);
    auto widget = dynamic_cast<DataImportGui::LineFilterWidget*>(p_list_widget->itemWidget(item));
    auto filter_name = widget->findChild<QLineEdit*>("line_filter_name");

    filter_name->setText("default_name");
    emit filter_name->editingFinished();

    EXPECT_EQ(1, spy_name.count());
    spy_name.takeLast();

    // Test the conditional behaviour on multiple same name editing
    item = p_list_widget->item(3);
    widget = dynamic_cast<DataImportGui::LineFilterWidget*>(p_list_widget->itemWidget(item));
    filter_name = widget->findChild<QLineEdit*>("line_filter_name");

    filter_name->setText("default_name");
    emit filter_name->editingFinished();

    EXPECT_EQ(0, spy_name.count());
}

//! Test the the type chnaged signal propagation
TEST_F(FilterWidgetTest, testTypeChange)
{
    for (int i = 0; i < 5; ++i){
        filter_widget->addLineFilter();
    }

    QSignalSpy spy_type(filter_widget, &ImportFilterWidget::typesChanged);

    auto item = p_list_widget->item(2);
    auto widget = dynamic_cast<DataImportGui::LineFilterWidget*>(p_list_widget->itemWidget(item));
    auto filter_type = widget->findChild<QComboBox*>("line_filter_type_select");

    filter_type->setCurrentText("Header");

    EXPECT_EQ(1, spy_type.count());
}
