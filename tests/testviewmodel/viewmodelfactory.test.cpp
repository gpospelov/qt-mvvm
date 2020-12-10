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
#include <mvvm/factories/viewmodelfactory.h>
#include <mvvm/model/propertyitem.h>
#include <mvvm/model/sessionmodel.h>
#include <mvvm/viewmodel/labeldatarowstrategy.h>
#include <mvvm/viewmodel/standardchildrenstrategies.h>
#include <mvvm/viewmodel/standardviewitems.h>

using namespace ModelView;

namespace
{
std::unique_ptr<ViewModelController> createController(SessionModel* model, ViewModelBase* viewModel)
{
    return Factory::CreateController<TopItemsStrategy, LabelDataRowStrategy>(model, viewModel);
}
} // namespace

class ViewModelFactoryTest : public ::testing::Test
{
public:
    ~ViewModelFactoryTest();

    class CustomModel : public ViewModel
    {
    public:
        CustomModel(SessionModel* model) : ViewModel(createController(model, this), nullptr) {}
    };
};

ViewModelFactoryTest::~ViewModelFactoryTest() = default;

//! Creating DefaultViewModel using strategies.

TEST_F(ViewModelFactoryTest, createDefaultViewModelInitial)
{
    SessionModel model;

    auto viewModel = Factory::CreateViewModel<AllChildrenStrategy, LabelDataRowStrategy>(&model);
    EXPECT_EQ(viewModel->rowCount(), 0);
    EXPECT_EQ(viewModel->columnCount(), 0);
    EXPECT_EQ(viewModel->sessionItemFromIndex(QModelIndex()), model.rootItem());
}

//! Creating DefaultViewModel using strategies, validating behaviour on single item in SessionModel.

TEST_F(ViewModelFactoryTest, createDefaultViewModelUseProperty)
{
    SessionModel model;
    auto propertyItem = model.insertItem<PropertyItem>();
    propertyItem->setData(42.0);

    auto viewModel = Factory::CreateViewModel<AllChildrenStrategy, LabelDataRowStrategy>(&model);

    EXPECT_EQ(viewModel->rowCount(), 1);
    EXPECT_EQ(viewModel->columnCount(), 2);

    // accessing first child under the root item
    QModelIndex labelIndex = viewModel->index(0, 0);
    QModelIndex dataIndex = viewModel->index(0, 1);

    // it should be ViewLabelItem looking at our PropertyItem item
    auto labelItem = dynamic_cast<ViewLabelItem*>(viewModel->itemFromIndex(labelIndex));
    ASSERT_TRUE(labelItem != nullptr);
    EXPECT_EQ(labelItem->item(), propertyItem);

    auto dataItem = dynamic_cast<ViewDataItem*>(viewModel->itemFromIndex(dataIndex));
    ASSERT_TRUE(dataItem != nullptr);
    EXPECT_EQ(dataItem->item(), propertyItem);
}

//! Creating DefaultViewModel using strategies, validating behaviour on single item in SessionModel.

TEST_F(ViewModelFactoryTest, createCustomViewModel)
{
    SessionModel model;
    auto propertyItem = model.insertItem<PropertyItem>();
    propertyItem->setData(42.0);

    CustomModel viewModel(&model);

    EXPECT_EQ(viewModel.rowCount(), 1);
    EXPECT_EQ(viewModel.columnCount(), 2);

    // accessing first child under the root item
    QModelIndex labelIndex = viewModel.index(0, 0);
    QModelIndex dataIndex = viewModel.index(0, 1);

    // it should be ViewLabelItem looking at our PropertyItem item
    auto labelItem = dynamic_cast<ViewLabelItem*>(viewModel.itemFromIndex(labelIndex));
    ASSERT_TRUE(labelItem != nullptr);
    EXPECT_EQ(labelItem->item(), propertyItem);

    auto dataItem = dynamic_cast<ViewDataItem*>(viewModel.itemFromIndex(dataIndex));
    ASSERT_TRUE(dataItem != nullptr);
    EXPECT_EQ(dataItem->item(), propertyItem);
}
