#include "customtableview.h"
#include "tableviewdelegate.h"

CustomTableView::CustomTableView(QWidget* parent)
    : QTableView(parent)
{}

void CustomTableView::rowsInserted(const QModelIndex& parent, int start, int end)
{
    QTableView::rowsInserted(parent, start, end);
	if (parent != rootIndex())
		return;

    // setting spans
    for (int row = start; row <= end; ++row) {
        for (int col = 0; col < model()->columnCount(); ++col) {
            QSize span = model()->span(model()->index(row, col, parent));
            if (span.width() > 1)
                setSpan(row, col, span.height(), span.width());
        }
    }

    // opening editors for assembly items
    for (int row = start; row <= end; ++row) {
        QModelIndex index = model()->index(row, 0, parent);
        if (index.data(Qt::UserRole) == TreeItem::Assembly)
            openPersistentEditor(index);
    }
}

void CustomTableView::rowsAboutToBeRemoved(const QModelIndex& parent, int start, int end)
{
	QTableView::rowsAboutToBeRemoved(parent, start, end);
	if (parent != rootIndex())
		return;

	// closing editors for assembly items
	// seemingly persistent editors are closed anyway. Still doing it
	// for the sake of logically clear release of resources.
	for (int row = start; row <= end; ++row) {
		QModelIndex index = model()->index(row, 0, parent);
		if (index.data(Qt::UserRole) == TreeItem::Assembly)
			closePersistentEditor(index);
	}
}
