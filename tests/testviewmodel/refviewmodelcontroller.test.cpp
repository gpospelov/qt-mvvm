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
#include <mvvm/model/propertyitem.h>
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
        result->init();
        return result;
    }
};

RefViewModelControllerTest::~RefViewModelControllerTest() = default;

//! Initial state of the controller. Empty SessionModel, empty ViewModel.

TEST_F(RefViewModelControllerTest, initialState)
{
    SessionModel session_model;
    RefViewModel view_model;
    auto controller = create_controller(&session_model, &view_model);

    EXPECT_EQ(controller->sessionModel(), &session_model);
    EXPECT_EQ(controller->rootSessionItem(), session_model.rootItem());
    EXPECT_EQ(view_model.columnCount(), 0);
    EXPECT_EQ(view_model.rowCount(), 0);
}

//! Single property item in a model.

TEST_F(RefViewModelControllerTest, fromPropertyItem)
{
    SessionModel session_model;
    auto propertyItem = session_model.insertItem<PropertyItem>();
    propertyItem->setData(42.0);

    RefViewModel view_model;
    auto controller = create_controller(&session_model, &view_model);

//    EXPECT_EQ(view_model.rowCount(), 1);
//    EXPECT_EQ(view_model.columnCount(), 2);

    // accessing first child under the root item
//    QModelIndex labelIndex = viewModel.index(0, 0);
//    QModelIndex dataIndex = viewModel.index(0, 1);

//    // it should be ViewLabelItem looking at our PropertyItem item
//    auto labelItem = dynamic_cast<ViewLabelItem*>(viewModel.itemFromIndex(labelIndex));
//    ASSERT_TRUE(labelItem != nullptr);
//    EXPECT_EQ(labelItem->item(), propertyItem);

//    auto dataItem = dynamic_cast<ViewDataItem*>(viewModel.itemFromIndex(dataIndex));
//    ASSERT_TRUE(dataItem != nullptr);
//    EXPECT_EQ(dataItem->item(), propertyItem);
}
