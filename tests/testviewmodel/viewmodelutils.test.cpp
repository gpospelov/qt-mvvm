// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/viewmodel/viewmodelutils.h"

#include "google_test.h"
#include "mvvm/model/mvvm_types.h"
#include "mvvm/model/sessionitem.h"
#include "mvvm/model/sessionmodel.h"
#include "mvvm/standarditems/vectoritem.h"
#include "mvvm/viewmodel/propertytableviewmodel.h"
#include "mvvm/viewmodel/standardviewitems.h"
#include <QColor>
#include <QModelIndexList>
#include <QStandardItemModel>

namespace {
QList<QStandardItem*> get_items(const std::vector<int>& data)
{
    QList<QStandardItem*> result;

    for (auto x : data)
        result.append(new QStandardItem(QString::number(x)));

    return result;
}
} // namespace

using namespace ModelView;

class ViewModelUtilsTest : public ::testing::Test {
};

TEST_F(ViewModelUtilsTest, iterate)
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

    Utils::iterate_model(&model, QModelIndex(), [&](const QModelIndex& index) {
        auto item = model.itemFromIndex(index);
        result.push_back(item->data(Qt::EditRole).value<int>());
    });

    EXPECT_EQ(result, expected);
}

//! Translation of item role to Qt roles.

TEST_F(ViewModelUtilsTest, ItemRoleToQtRole)
{
    // DATA role of SessionItem should be translated to two Qt roles (edit and display)
    auto roles = Utils::ItemRoleToQtRole(ItemDataRole::DATA);
    QVector<int> expected = {Qt::DisplayRole, Qt::EditRole};
    EXPECT_EQ(roles, expected);

    // APPEARANCE roles of SessionItem on Qt site means color
    roles = Utils::ItemRoleToQtRole(ItemDataRole::APPEARANCE);
#if QT_VERSION >= QT_VERSION_CHECK(5, 13, 0)
    expected = {Qt::ForegroundRole};
#else
    expected = {Qt::TextColorRole};
#endif
    EXPECT_EQ(roles, expected);

    // tooltip role
    roles = Utils::ItemRoleToQtRole(ItemDataRole::TOOLTIP);
    expected = {Qt::ToolTipRole};
    EXPECT_EQ(roles, expected);
}

//! Testing color role of item.

TEST_F(ViewModelUtilsTest, itemTextColorRole)
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

TEST_F(ViewModelUtilsTest, itemCheckStateRole)
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

TEST_F(ViewModelUtilsTest, itemDecorationRole)
{
    SessionItem item("Something");

    // no color defined for item by default
    auto variant = Utils::DecorationRole(item);
    EXPECT_FALSE(variant.isValid());

    QColor expected(Qt::green);
    item.setData(expected);
    EXPECT_EQ(Utils::DecorationRole(item).value<QColor>(), expected);
}

//! Testing tooltip role of the item.

TEST_F(ViewModelUtilsTest, itemToolTipRole)
{
    SessionItem item("Something");

    auto variant = Utils::ToolTipRole(item);
    EXPECT_FALSE(variant.isValid());

    item.setToolTip("abc");
    EXPECT_EQ(Utils::ToolTipRole(item).toString(), QString("abc"));
}

//! Check ItemsFromIndex in PropertyTableViewModel context.
//! ViewItem with its three property x, y, z forms one row. All corresponding
//! indices of (x,y,z) should give us pointers to VectorItem's properties.

TEST_F(ViewModelUtilsTest, itemsFromIndex)
{
    // creating VectorItem and viewModel to see it as a table
    SessionModel model;
    auto parent = model.insertItem<VectorItem>();
    PropertyTableViewModel viewModel(&model);

    // it's a table with one row and x,y,z columns
    EXPECT_EQ(viewModel.rowCount(), 1);
    EXPECT_EQ(viewModel.columnCount(), 3);

    // empty index list doesn't lead to SessionItem's
    QModelIndexList index_list;
    EXPECT_EQ(Utils::ItemsFromIndex(index_list).size(), 0);

    // index list populated with column of properties
    index_list.push_back(viewModel.index(0, 0));
    index_list.push_back(viewModel.index(0, 1));
    index_list.push_back(viewModel.index(0, 2));

    std::vector<SessionItem*> expected = {parent->getItem(VectorItem::P_X),
                                          parent->getItem(VectorItem::P_Y),
                                          parent->getItem(VectorItem::P_Z)};
    EXPECT_EQ(Utils::ItemsFromIndex(index_list), expected);
    EXPECT_EQ(Utils::UniqueItemsFromIndex(index_list), expected);
}

//! Check UniqueItemsFromIndex for artificially constructed viewmodel.

TEST_F(ViewModelUtilsTest, UniqueItemsFromIndex)
{
    SessionItem item1;
    item1.setData(42, ItemDataRole::DATA);
    SessionItem item2;
    item2.setData(42, ItemDataRole::DATA);

    ViewModelBase viewmodel;
    std::vector<std::unique_ptr<ViewItem>> items;
    items.emplace_back(std::make_unique<ViewLabelItem>(&item1));
    items.emplace_back(std::make_unique<ViewLabelItem>(&item2));
    items.emplace_back(std::make_unique<ViewDataItem>(&item1));
    items.emplace_back(std::make_unique<ViewDataItem>(&item2));
    viewmodel.insertRow(viewmodel.rootItem(), 0, std::move(items));

    QModelIndexList index_list = {viewmodel.index(0, 0), viewmodel.index(0, 1),
                                  viewmodel.index(0, 2), viewmodel.index(0, 3)};

    EXPECT_EQ(Utils::ItemsFromIndex(index_list),
              std::vector<SessionItem*>({&item1, &item2, &item1, &item2}));
    EXPECT_EQ(Utils::UniqueItemsFromIndex(index_list), std::vector<SessionItem*>({&item1, &item2}));
}

//! Check ParentItemsFromIndex in PropertyTableViewModel context.
//! ViewItem with its three property x, y, z forms one row. All corresponding
//! indices of (x,y,z) should give us pointer to VectorItem.

TEST_F(ViewModelUtilsTest, parentItemsFromIndex)
{
    // creating VectorItem and viewModel to see it as a table
    SessionModel model;
    auto parent = model.insertItem<VectorItem>();
    PropertyTableViewModel viewModel(&model);

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
