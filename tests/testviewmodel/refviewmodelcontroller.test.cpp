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
#include <mvvm/model/sessionmodel.h>
#include <mvvm/viewmodel/refviewmodelcontroller.h>
#include <mvvm/viewmodel/refviewmodel.h>
#include <mvvm/viewmodel/labeldatarowstrategy.h>
#include <mvvm/viewmodel/standardchildrenstrategies.h>

using namespace ModelView;

//! Tests of RefViewModelController class.

class RefViewModelControllerTest : public ::testing::Test
{
public:
    ~RefViewModelControllerTest();

    auto create_controller(SessionModel* session_model, RefViewModel* view_model) {
        auto result = std::make_unique<RefViewModelController>(session_model, view_model);
        result->setRowStrategy(std::make_unique<LabelDataRowStrategy>());
        result->setChildrenStrategy(std::make_unique<AllChildrenStrategy>());
        return result;
    }
};

RefViewModelControllerTest::~RefViewModelControllerTest() = default;

TEST_F(RefViewModelControllerTest, initialState)
{
    SessionModel session_model;
    RefViewModel view_model;
    auto controller = create_controller(&session_model, &view_model);

    EXPECT_EQ(view_model.columnCount(), 0);
    EXPECT_EQ(view_model.rowCount(), 0);
}
