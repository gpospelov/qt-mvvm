#include "google_test.h"
#include "viewmodelutils.h"
#include "model_types.h"
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
}


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

    Utils::iterate_model(&model, QModelIndex(), [&](const QStandardItem* item){
        result.push_back(item->data(Qt::EditRole).toInt());
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
    expected = {Qt::TextColorRole};
    EXPECT_EQ(roles, expected);
}
