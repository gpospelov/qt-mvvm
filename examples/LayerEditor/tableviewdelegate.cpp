#include "tableviewdelegate.h"
#include "detailswidget.h"
#include "treeitem.h"

TableViewDelegate::TableViewDelegate(QObject* parent)
    : QStyledItemDelegate(parent)
{}

QWidget* TableViewDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option,
                                         const QModelIndex& index) const
{
    if (index.isValid() && index.column() == 0 && index.data(Qt::UserRole) == TreeItem::Assembly) {
        auto result = new Utils::DetailsWidget(parent);
        result->setSummaryText("Assembly");
        result->setSummaryFontBold(true);
        return result;
    }
    return QStyledItemDelegate::createEditor(parent, option, index);
}
