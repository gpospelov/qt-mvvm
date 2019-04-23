#ifndef TABLEVIEWDELEGATE_H
#define TABLEVIEWDELEGATE_H

#include <QStyledItemDelegate>

class CustomTableView;

class TableViewDelegate : public QStyledItemDelegate
{
public:
    TableViewDelegate(CustomTableView* parent = nullptr);

    QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option,
                          const QModelIndex& index) const override;

private:
	CustomTableView* m_parent_table;
};

#endif // TABLEVIEWDELEGATE_H
