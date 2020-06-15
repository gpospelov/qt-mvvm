// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "google_test.h"
#include "importlinefilter.h"
#include "importlinefilterwidget.h"

#include <QComboBox>
#include <QLineEdit>
#include <QSignalSpy>
#include <QSpinBox>
#include <QVariant>

#include <map>
#include <string>
#include <vector>

using namespace DataImportGui;

//! Test the data column item
class LineFilterWidgetTest : public ::testing::Test
{
public:
    LineFilterWidgetTest();
    ~LineFilterWidgetTest();
    std::map<std::string, char> m_separators{
        {"Space ( )", ' '}, {"Comma (,)", ','}, {"Semicolon (;)", ';'}, {"Pipe (|)", '|'},
        {"Colon (:)", ':'}, {"Tab", '\t'},      {"Quote (\')", '\''},   {"Apostrophe (\")", '\"'}};

    DataImportLogic::LineFilter* line_filter{nullptr};
    LineFilterWidget* line_filter_widget{nullptr};

    SwitchSpace::Switch* p_active_checkbox;
    ModelView::ColorEditor* p_color_editor;
    QSpinBox* p_line_start;
    QSpinBox* p_line_end;

    QComboBox* p_type_select;
    QComboBox* p_range_start;
    QComboBox* p_range_end;
    QComboBox* p_separators;

    QLineEdit* p_filter_name;
    QLineEdit* p_ignore_strings;
    QLineEdit* p_ignore_lines;
};

//! The constructor
LineFilterWidgetTest::LineFilterWidgetTest()
{
    line_filter = new DataImportLogic::LineFilter("default_name");
    line_filter->setSeparators(&m_separators);
    line_filter_widget = new LineFilterWidget(line_filter);

    p_line_start = line_filter_widget->findChild<QSpinBox*>("line_filter_line_start");
    p_line_end = line_filter_widget->findChild<QSpinBox*>("line_filter_line_end");

    p_type_select = line_filter_widget->findChild<QComboBox*>("line_filter_type_select");
    p_range_start = line_filter_widget->findChild<QComboBox*>("line_filter_range_start");
    p_range_end = line_filter_widget->findChild<QComboBox*>("line_filter_range_end");
    p_separators = line_filter_widget->findChild<QComboBox*>("line_filter_seprator_select");

    p_filter_name = line_filter_widget->findChild<QLineEdit*>("line_filter_name");
    p_ignore_strings = line_filter_widget->findChild<QLineEdit*>("line_filter_ignore_string");
    p_ignore_lines = line_filter_widget->findChild<QLineEdit*>("line_filter_ignore_lines");
}

//! The destructor
LineFilterWidgetTest::~LineFilterWidgetTest()
{
    delete line_filter_widget;
    delete line_filter;
}

//! Test default constructor
TEST_F(LineFilterWidgetTest, defaultContructor)
{
    EXPECT_EQ(line_filter, line_filter_widget->lineFilter());

    EXPECT_EQ(0, p_line_start->value());
    EXPECT_EQ(1, p_line_end->value());

    EXPECT_EQ("Data", p_type_select->currentText().toStdString());
    EXPECT_EQ("At line", p_range_start->currentText().toStdString());
    EXPECT_EQ("and", p_range_end->currentText().toStdString());
    EXPECT_EQ("Apostrophe (\")", p_separators->currentText().toStdString());

    EXPECT_EQ("default_name", p_filter_name->text().toStdString());
    EXPECT_EQ("", p_ignore_strings->text().toStdString());
    EXPECT_EQ("", p_ignore_lines->text().toStdString());
}

//! Test chaging the line filter ranges at given line
TEST_F(LineFilterWidgetTest, testAtLineRange)
{
    p_range_start->setCurrentText("At line");
    p_line_start->setValue(5);

    EXPECT_EQ("At line", p_range_start->currentText().toStdString());
    EXPECT_EQ(5, p_line_start->value());
    EXPECT_EQ(6, p_line_end->value());
    EXPECT_EQ(5, line_filter->start());
    EXPECT_EQ(6, line_filter->end());
}

//! Test changing the line filter ranges between line numbers
TEST_F(LineFilterWidgetTest, testBetweenLinesRange)
{
    line_filter->setType("Data");
    p_type_select->setCurrentText("Data");
    p_range_start->setCurrentText("Between lines");
    p_range_end->setCurrentText("and");
    p_line_start->setValue(5);

    EXPECT_EQ("Between lines", p_range_start->currentText().toStdString());
    EXPECT_EQ("and", p_range_end->currentText().toStdString());
    EXPECT_EQ(5, p_line_start->value());
    EXPECT_EQ(6, p_line_end->value());
    EXPECT_EQ(5, line_filter->start());
    EXPECT_EQ(6, line_filter->end());
}

//! Test changing the line filter ranges between line number and end of file (EOF)
TEST_F(LineFilterWidgetTest, testBetweenLinesEOF)
{
    line_filter->setType("Data");
    p_type_select->setCurrentText("Data");
    p_range_start->setCurrentText("Between lines");
    p_range_end->setCurrentText("and end of file.");
    p_line_start->setValue(5);

    EXPECT_EQ("Between lines", p_range_start->currentText().toStdString());
    EXPECT_EQ("and end of file.", p_range_end->currentText().toStdString());
    EXPECT_EQ(5, p_line_start->value());
    EXPECT_EQ(6, p_line_end->value());
    EXPECT_EQ(5, line_filter->start());
    EXPECT_EQ(-1, line_filter->end());
}

//! Test changing the line filter type
TEST_F(LineFilterWidgetTest, testTypeChange)
{
    QSignalSpy spy_type(line_filter_widget, &LineFilterWidget::typeChanged);
    QList<QVariant> type_args;

    p_type_select->setCurrentText("Header");
    type_args = spy_type.takeLast();
    EXPECT_EQ("Header", type_args.at(0).value<std::string>());
    EXPECT_EQ(line_filter_widget, type_args.at(1).value<LineFilterWidget*>());

    line_filter->setType("Header"); // make sure the signal has right to fire
    p_type_select->setCurrentText("Data");
    type_args = spy_type.takeLast();
    EXPECT_EQ("Data", type_args.at(0).value<std::string>());
    EXPECT_EQ(line_filter_widget, type_args.at(1).value<LineFilterWidget*>());

    p_type_select->setCurrentText("Comments");
    type_args = spy_type.takeLast();
    EXPECT_EQ("Comments", type_args.at(0).value<std::string>());
    EXPECT_EQ(line_filter_widget, type_args.at(1).value<LineFilterWidget*>());

    p_type_select->setCurrentText("Units");
    type_args = spy_type.takeLast();
    EXPECT_EQ("Units", type_args.at(0).value<std::string>());
    EXPECT_EQ(line_filter_widget, type_args.at(1).value<LineFilterWidget*>());
}

//! Test changing the line filter name
TEST_F(LineFilterWidgetTest, testNameChange)
{
    QSignalSpy spy_name(line_filter_widget, &LineFilterWidget::nameChanged);
    QList<QVariant> name_args;

    p_filter_name->setText("Randome_name");
    emit p_filter_name->editingFinished();
    name_args = spy_name.takeLast();
    EXPECT_EQ("Randome_name", name_args.at(0).value<std::string>());
    EXPECT_EQ(line_filter_widget, name_args.at(1).value<LineFilterWidget*>());
}
