#include "customtableview.h"
#include "tableviewdelegate.h"

CustomTableView::CustomTableView(QWidget* parent) : QTableView(parent) {}

void CustomTableView::updateRepresentation()
{
    TreeModel* tree_model = dynamic_cast<TreeModel*>(model());
    if (!tree_model)
        return;

    const QModelIndex& root_index = rootIndex();

    for (int row = 0; row < tree_model->rowCount(root_index); ++row)
        for (int col = 0; col < tree_model->columnCount(root_index); ++col) {
            QSize span = tree_model->span(tree_model->index(row, col, root_index));
            if (span.width() > 1)
                setSpan(row, col, span.height(), span.width());
        }

    for (int row = 0; row < tree_model->rowCount(root_index); ++row) {
        QModelIndex index = tree_model->index(row, 0, root_index);
        if (index.data(Qt::UserRole) == TreeItem::Assembly)
            openPersistentEditor(index);
    }
}

void CustomTableView::rowsInserted(const QModelIndex& parent, int start, int end)
{
    if (parent != rootIndex())
        return;

    QTableView::rowsInserted(parent, start, end);

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
