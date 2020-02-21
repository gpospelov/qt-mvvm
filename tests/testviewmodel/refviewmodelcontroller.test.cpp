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
#include <mvvm/model/propertyitem.h>
#include <mvvm/model/sessionmodel.h>
#include <mvvm/standarditems/vectoritem.h>
#include <mvvm/viewmodel/labeldatarowstrategy.h>
#include <mvvm/viewmodel/refviewitems.h>
#include <mvvm/viewmodel/refviewmodel.h>
#include <mvvm/viewmodel/refviewmodelcontroller.h>
#include <mvvm/viewmodel/standardchildrenstrategies.h>

using namespace ModelView;

//! Tests of RefViewModelController class.

class RefViewModelControllerTest : public ::testing::Test
{
public:
    ~RefViewModelControllerTest();

    auto create_controller(SessionModel* session_model, RefViewModel* view_model)
    {
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

    EXPECT_EQ(view_model.rowCount(), 1);
    EXPECT_EQ(view_model.columnCount(), 2);

    // accessing first child under the root item
    QModelIndex labelIndex = view_model.index(0, 0);
    QModelIndex dataIndex = view_model.index(0, 1);

    // it should be ViewLabelItem and ViewDataItem looking at our PropertyItem item
    EXPECT_EQ(view_model.itemFromIndex(labelIndex)->item_role(), ItemDataRole::DISPLAY);
    EXPECT_EQ(view_model.itemFromIndex(labelIndex)->item(), propertyItem);
    EXPECT_EQ(view_model.itemFromIndex(dataIndex)->item_role(), ItemDataRole::DATA);
    EXPECT_EQ(view_model.itemFromIndex(dataIndex)->item(), propertyItem);
}

//! VectorItem in a model.

TEST_F(RefViewModelControllerTest, fromVectorItem)
{
    SessionModel session_model;
    auto vectorItem = session_model.insertItem<VectorItem>();

    RefViewModel view_model;
    auto controller = create_controller(&session_model, &view_model);

    EXPECT_EQ(view_model.rowCount(), 1);
    EXPECT_EQ(view_model.columnCount(), 2);

    // accessing first child under the root item
    QModelIndex vectorLabelIndex = view_model.index(0, 0);
    QModelIndex vectorDataIndex = view_model.index(0, 1);

    // it should be ViewLabelItem and ViewDataItem looking at our VectorItem item
    EXPECT_EQ(view_model.itemFromIndex(vectorLabelIndex)->item_role(), ItemDataRole::DISPLAY);
    EXPECT_EQ(view_model.itemFromIndex(vectorLabelIndex)->item(), vectorItem);
    EXPECT_EQ(view_model.itemFromIndex(vectorDataIndex)->item_role(), ItemDataRole::DATA);
    EXPECT_EQ(view_model.itemFromIndex(vectorDataIndex)->item(), vectorItem);

    // checking X, Y, Z
    std::vector<SessionItem*> children = vectorItem->children();
    for (int row = 0; row < 3; ++row) { // x, y, z
        QModelIndex x_labelIndex = view_model.index(row, 0, vectorLabelIndex);
        QModelIndex x_dataIndex = view_model.index(row, 1, vectorLabelIndex);
        EXPECT_EQ(view_model.itemFromIndex(x_labelIndex)->item_role(), ItemDataRole::DISPLAY);
        EXPECT_EQ(view_model.itemFromIndex(x_labelIndex)->item(),
                  children[static_cast<size_t>(row)]);
        EXPECT_EQ(view_model.itemFromIndex(x_dataIndex)->item_role(), ItemDataRole::DATA);
        EXPECT_EQ(view_model.itemFromIndex(x_dataIndex)->item(),
                  children[static_cast<size_t>(row)]);
    }
}
