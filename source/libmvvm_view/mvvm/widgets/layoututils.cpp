// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/widgets/layoututils.h"
#include <QBoxLayout>
#include <QGridLayout>
#include <QLayoutItem>
#include <QWidget>

namespace {
void remove(QGridLayout* layout, int row, int column, bool deleteWidgets);
void deleteChildWidgets(QLayoutItem* item);
} // namespace

void LayoutUtils::clearLayout(QLayout* layout, bool deleteWidgets)
{
    if (!layout)
        return;

    while (QLayoutItem* item = layout->takeAt(0)) {
        if (deleteWidgets)
            delete item->widget();
        if (QLayout* childLayout = item->layout())
            LayoutUtils::clearLayout(childLayout, deleteWidgets);
        delete item;
    }
}

/**
 * Removes all layout items on the given row from the given grid
 * layout. If deleteWidgets is true, all concerned child widgets
 * become not only removed from the layout, but also deleted. Note that
 * this function doesn't actually remove the row itself from the grid
 * layout, as this isn't possible (i.e. the rowCount() and row indices
 * will stay the same after this function has been called).
 */

void LayoutUtils::removeRow(QGridLayout* layout, int row, bool deleteWidgets)
{
    remove(layout, row, -1, deleteWidgets);
    layout->setRowMinimumHeight(row, 0);
    layout->setRowStretch(row, 0);
}

/**
 * Removes all layout items on the given column from the given grid
 * layout. If deleteWidgets is true, all concerned child widgets
 * become not only removed from the layout, but also deleted. Note that
 * this function doesn't actually remove the column itself from the grid
 * layout, as this isn't possible (i.e. the columnCount() and column
 * indices will stay the same after this function has been called).
 */

void LayoutUtils::removeColumn(QGridLayout* layout, int column, bool deleteWidgets)
{
    remove(layout, -1, column, deleteWidgets);
    layout->setColumnMinimumWidth(column, 0);
    layout->setColumnStretch(column, 0);
}

void LayoutUtils::clearGridLayout(QGridLayout* layout, bool deleteWidgets)
{
    for (int i_row = 0; i_row < layout->rowCount(); ++i_row) {
        LayoutUtils::removeRow(layout, i_row, deleteWidgets);
    }
}

namespace {

/**
 * Helper function. Removes all layout items within the given layout
 * which either span the given row or column. If deleteWidgets
 * is true, all concerned child widgets become not only removed from the
 * layout, but also deleted.
 */

void remove(QGridLayout* layout, int row, int column, bool deleteWidgets)
{
    // We avoid usage of QGridLayout::itemAtPosition() here to improve performance.
    for (int i = layout->count() - 1; i >= 0; i--) {
        int r, c, rs, cs;
        layout->getItemPosition(i, &r, &c, &rs, &cs);
        if ((r <= row && r + rs - 1 >= row) || (c <= column && c + cs - 1 >= column)) {
            // This layout item is subject to deletion.
            QLayoutItem* item = layout->takeAt(i);
            if (deleteWidgets)
                deleteChildWidgets(item);
            delete item;
        }
    }
}

/**
 * Helper function. Deletes all child widgets of the given layout item.
 */

void deleteChildWidgets(QLayoutItem* item)
{
    if (item->layout()) {
        // Process all child items recursively.
        for (int i = 0; i < item->layout()->count(); i++)
            deleteChildWidgets(item->layout()->itemAt(i));
    }
    item->widget()->deleteLater();
}

} // namespace

QWidget* LayoutUtils::placeHolder()
{
    auto result = new QWidget;
    result->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    return result;
}
