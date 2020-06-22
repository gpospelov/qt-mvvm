// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef WIDGETBASEDTEST_H
#define WIDGETBASEDTEST_H

#include <gtest/gtest.h>

class QApplication;

//! Convenience class to setup QApplication for tests involving QWidget creation.

class WidgetBasedTest : public ::testing::Test
{
public:
    WidgetBasedTest();

    static void SetUpTestSuite();

    static void TearDownTestSuite();

protected:
    static QApplication* m_app;
};

#endif //  WIDGETBASEDTEST_H
