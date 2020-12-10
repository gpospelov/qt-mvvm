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

//! Test of WithTildeHomePath function.

TEST_F(WidgetUtilsTest, WithTildeHomePath)
{
    if (ModelView::Utils::IsWindowsHost()) {
        auto test_dir = QString::fromStdString(TestUtils::TestOutputDir());
        EXPECT_EQ(Utils::WithTildeHomePath(test_dir), test_dir);
    } else {
        auto home_path = QDir::homePath();
        auto test_dir = QString::fromStdString(TestUtils::TestOutputDir());
        auto expected = QString("~") + test_dir.mid(home_path.size());

        // "/home/user/build-debug/test_output" -> ~/build-debug/test_output"
        EXPECT_EQ(Utils::WithTildeHomePath(test_dir).toStdString(), expected.toStdString());
    }
}

TEST_F(WidgetUtilsTest, ProjectWindowTitle)
{
    // untitled and unmodified project
    EXPECT_EQ(Utils::ProjectWindowTitle(QString(""), false), "Untitled");

    // untitled and modified project
    EXPECT_EQ(Utils::ProjectWindowTitle(QString(""), true), "*Untitled");

    // unmodified project without projectDir
    EXPECT_EQ(Utils::ProjectWindowTitle(QString("Untitled"), false), "Untitled");

    // modified project without projectDir
    EXPECT_EQ(Utils::ProjectWindowTitle(QString("Untitled"), true), "*Untitled");

    // unmodified project with projectDir
    EXPECT_EQ(Utils::ProjectWindowTitle(QString("/home/user/project1"), false), "project1");

    // modified project with projectDir
    EXPECT_EQ(Utils::ProjectWindowTitle(QString("/home/user/project1"), true), "*project1");
}

TEST_F(WidgetUtilsTest, ClickableText)
{
    EXPECT_EQ(Utils::ClickableText("abc", "site.com"), QString("<a href=\"site.com\">abc</a>"));
}

TEST_F(WidgetUtilsTest, toStringList)
{
    using vec_t = std::vector<std::string>;
    EXPECT_EQ(Utils::toStringList(vec_t()), QStringList());
    EXPECT_EQ(Utils::toStringList(vec_t({"abc", "cde"})), QStringList({"abc", "cde"}));
}

TEST_F(WidgetUtilsTest, fromStringList)
{
    using vec_t = std::vector<std::string>;
    EXPECT_EQ(Utils::fromStringList(QStringList()), vec_t());
    EXPECT_EQ(Utils::fromStringList(QStringList({"abc", "cde"})), vec_t({"abc", "cde"}));
}

TEST_F(WidgetUtilsTest, toFromByteArray)
{
    QStringList expected = QStringList() << "aaa"
                                         << "bbb"
                                         << "ccc";

    auto array = Utils::serialize(expected);
    EXPECT_EQ(Utils::deserialize(array), expected);
}
