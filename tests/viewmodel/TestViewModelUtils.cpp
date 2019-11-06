// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //


#include "google_test.h"
#include <mvvm/model/mvvm_types.h>
#include <mvvm/viewmodel/propertytableviewmodel.h>
#include <mvvm/model/sessionitem.h>
#include <mvvm/model/sessionmodel.h>
#include <mvvm/viewmodel/viewmodelutils.h>
#include <mvvm/standarditems/vectoritem.h>
#include <QColor>
#include <QModelIndexList>
#include <QStandardItemModel>

namespace
{
QList<QStandardItem*> get_items(std::vector<int> data)
{
    QList<QStandardItem*> result;

    for (auto x : data)
        result.append(new QStandardItem(QString::number(x)));

    return result;
}
} // namespace

using namespace ModelView;

class TestViewModelUtils : public ::testing::Test
{
public:
    ~TestViewModelUtils();
};

TestViewModelUtils::~TestViewModelUtils() = default;

TEST_F(TestViewModelUtils, iterate)
{
    QStandardItemModel model;

    model.setColumnCount(2);
    QStandardItem* parentItem = model.invisibleRootItem();

    auto row1 = get_items({1, 2});
    parentItem->appendRow(row1);
    row1.at(0)->appendRow(get_items({3, 4}));

    auto row2 = get_items({10, 20});
    parentItem->appendRow(row2);

    std::vector<int> expected = {1, 2, 3, 4, 10, 20};
    std::vector<int> result;

    Utils::iterate_model(&model, QModelIndex(), [&](const QStandardItem* item) {
        result.push_back(item->data(Qt::EditRole).value<int>());
    });

    EXPECT_EQ(result, expected);
}

//! Translation of item role to Qt roles.

TEST_F(TestViewModelUtils, itemRoleToQtRole)
{
    // DATA role of SessionItem should be translated to two Qt roles (edit and siplay)
    auto roles = Utils::item_role_to_qt(ItemDataRole::DATA);
    QVector<int> expected = {Qt::DisplayRole, Qt::EditRole};
    EXPECT_EQ(roles, expected);

    // APPEARANCE roles of SessionItem on Qt site means color
    roles = Utils::item_role_to_qt(ItemDataRole::APPEARANCE);
#if QT_VERSION >= QT_VERSION_CHECK(5, 13, 0)
    expected = {Qt::ForegroundRole};
#else
    expected = {Qt::TextColorRole};
#endif
    EXPECT_EQ(roles, expected);
}

//! Testing color role of item.

TEST_F(TestViewModelUtils, itemTextColorRole)
{
    SessionItem item("Something");

    // no color defined for item by default
    auto variant = Utils::TextColorRole(item);
    EXPECT_FALSE(variant.isValid());

    item.setEnabled(false);
    variant = Utils::TextColorRole(item);
    EXPECT_EQ(variant.value<QColor>(), QColor(Qt::gray));
}

//! Testing check state role of item.

TEST_F(TestViewModelUtils, itemCheckStateRole)
{
    SessionItem item("Something");

    // no color defined for item by default
    auto variant = Utils::CheckStateRole(item);
    EXPECT_FALSE(variant.isValid());

    item.setData(QVariant::fromValue(true));
    EXPECT_EQ(Utils::CheckStateRole(item).value<int>(), Qt::Checked);

    item.setData(QVariant::fromValue(false));
    EXPECT_EQ(Utils::CheckStateRole(item).value<int>(), Qt::Unchecked);
}

//! Testing decoration role of the item.

TEST_F(TestViewModelUtils, itemDecorationRole)
{
    SessionItem item("Something");

    // no color defined for item by default
    auto variant = Utils::DecorationRole(item);
    EXPECT_FALSE(variant.isValid());

    QColor expected(Qt::green);
    item.setData(expected);
    EXPECT_EQ(Utils::DecorationRole(item).value<QColor>(), expected);
}

//! Check ParentItemsFromIndex in PropertyTableViewModel context.
//! ViewItem with its three property x, y, z forms one row. All corresponding
//! indices of (x,y,z) should give us pointer to VectorItem.

TEST_F(TestViewModelUtils, parentItemsFromIndex)
{
    // creating VectorItem and viewModel to see it as a table
    SessionModel model;
    auto parent = model.insertItem<VectorItem>();
    PropertyTableViewModel viewModel;
    viewModel.setSessionModel(&model);

    // it's a table with one row and x,y,z columns
    EXPECT_EQ(viewModel.rowCount(), 1);
    EXPECT_EQ(viewModel.columnCount(), 3);

    // empty index list doesn't lead to SessionItem's
    QModelIndexList index_list;
    EXPECT_EQ(Utils::ParentItemsFromIndex(index_list).size(), 0);

    std::vector<SessionItem*> expected = {parent};

    // one cell in a list should give us pointer to original VectorItem
    index_list.push_back(viewModel.index(0, 1));
    EXPECT_EQ(Utils::ParentItemsFromIndex(index_list), expected);

    index_list.clear();
    index_list.push_back(viewModel.index(0, 1));
    EXPECT_EQ(Utils::ParentItemsFromIndex(index_list), expected);

    index_list.clear();
    index_list.push_back(viewModel.index(0, 2));
    EXPECT_EQ(Utils::ParentItemsFromIndex(index_list), expected);

    // tthree cells (x, y, z) in a list should give us pointer to original VectorItem
    index_list.clear();
    index_list.push_back(viewModel.index(0, 0));
    index_list.push_back(viewModel.index(0, 1));
    index_list.push_back(viewModel.index(0, 2));
    EXPECT_EQ(Utils::ParentItemsFromIndex(index_list), expected);
}
