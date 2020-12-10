// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "google_test.h"
#include <mvvm/factories/viewmodelcontrollerfactory.h>
#include <mvvm/model/sessionmodel.h>
#include <mvvm/viewmodel/labeldatarowstrategy.h>
#include <mvvm/viewmodel/standardchildrenstrategies.h>
#include <mvvm/viewmodel/viewmodelbase.h>
#include <mvvm/viewmodel/viewmodelcontroller.h>

using namespace ModelView;

//! Tests of ViewModelControllerFactory method.

class ViewModelControllerFactoryTest : public ::testing::Test
{
public:
    ~ViewModelControllerFactoryTest();
};

ViewModelControllerFactoryTest::~ViewModelControllerFactoryTest() = default;

TEST_F(ViewModelControllerFactoryTest, allItemsControllerBuild)
{
    SessionModel session_model;
    ViewModelBase view_model;

    auto controller = Factory::CreateController<AllChildrenStrategy, LabelDataRowStrategy>(
        &session_model, &view_model);

    controller->setRootSessionItem(session_model.rootItem());

    EXPECT_EQ(controller->sessionModel(), &session_model);
    EXPECT_EQ(controller->rootSessionItem(), session_model.rootItem());
    EXPECT_EQ(view_model.columnCount(), 0);
    EXPECT_EQ(view_model.rowCount(), 0);
}
