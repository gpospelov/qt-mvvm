#include "tableviewdelegate.h"
#include "customtableview.h"
#include "detailswidget.h"
#include "treeitem.h"
#include <QHeaderView>

namespace {
	Utils::DetailsWidget* createDetailsWidget(QWidget* parent, const QModelIndex& index)
	{
		auto result = new Utils::DetailsWidget(parent);
		auto internal_table = new CustomTableView();
		internal_table->setModel(const_cast<QAbstractItemModel*>(index.model()));
		internal_table->setRootIndex(index);
		internal_table->setItemDelegate(new TableViewDelegate(internal_table));
		internal_table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
		result->setWidget(internal_table);
		return result;
	}
}

TableViewDelegate::TableViewDelegate(CustomTableView* parent)
    : QStyledItemDelegate(parent)
	, m_parent_table(parent)
{}

QWidget* TableViewDelegate::createEditor(QWidget* parent, const QStyleOptionViewItem& option,
                                         const QModelIndex& index) const
{
    if (index.isValid() && index.column() == 0 && index.data(Qt::UserRole) == TreeItem::Assembly) {
        auto result = createDetailsWidget(parent, index);
        result->setSummaryText("Assembly");
        result->setSummaryFontBold(true);

		// TODO: find a better way to notify the table view about the change in editor's size
		connect(result, &Utils::DetailsWidget::expanded, m_parent_table,
			[this, result](bool) { m_parent_table->resizeRowsToContents(); });
        return result;
    }
    return QStyledItemDelegate::createEditor(parent, option, index);
}
