// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "materialtreeview.h"
#include <QHeaderView>
#include <QMouseEvent>

MaterialTreeView::~MaterialTreeView() = default;

MaterialTreeView::MaterialTreeView(QWidget* parent) : QTreeView(parent)
{
    setAlternatingRowColors(true);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setSelectionMode(QAbstractItemView::ExtendedSelection);
    //    setTabKeyNavigation(true);
    header()->setSectionResizeMode(QHeaderView::Stretch);
}

void MaterialTreeView::setModel(QAbstractItemModel* model)
{
    QTreeView::setModel(model);
    expandAll();
}

void MaterialTreeView::keyPressEvent(QKeyEvent* event)
{
    if (!event || event->key() != Qt::Key_Return || state() == QAbstractItemView::EditingState)
        return QTreeView::keyPressEvent(event);

    const QModelIndex index = currentIndex();
    if (isKeyboardEditable(index))
        edit(index);
}

QModelIndex MaterialTreeView::moveCursor(QAbstractItemView::CursorAction cursorAction,
                                         Qt::KeyboardModifiers modifiers)
{
    const QModelIndex current_index = currentIndex();
    bool filtered_action = cursorAction == QAbstractItemView::MoveNext
                           || cursorAction == QAbstractItemView::MovePrevious;

    if (!current_index.isValid() || !isTextField(current_index) || !filtered_action)
        return QTreeView::moveCursor(cursorAction, modifiers);

    QModelIndex next = current_index;
    do {
        setCurrentIndex(next);
        next = QTreeView::moveCursor(cursorAction, modifiers);
    } while (!isTextField(next));
    return next;
}

bool MaterialTreeView::isTextField(const QModelIndex& index) const
{
    return index.isValid() && index.column() > 0; // color is not keyboard editable
}

bool MaterialTreeView::isKeyboardEditable(const QModelIndex& index) const
{
    return index.isValid();
}
