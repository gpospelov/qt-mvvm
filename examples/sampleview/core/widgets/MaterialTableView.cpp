#include "MaterialTableView.h"
#include <QMouseEvent>

namespace {
int mouse_events = QEvent::MouseButtonPress | QEvent::MouseButtonRelease | QEvent::MouseMove;
}

MaterialTableView::~MaterialTableView() = default;

QItemSelectionModel::SelectionFlags MaterialTableView::selectionCommand(const QModelIndex& index,
                                                                        const QEvent* event) const
{
    auto mouse_event = dynamic_cast<const QMouseEvent*>(event);
    auto event_type = mouse_event ? mouse_event->type() : QEvent::None;
    bool check_column = index.isValid() && index.column() == 0;

    if (check_column && (event_type & mouse_events)) {
        if ((mouse_event->buttons() & Qt::LeftButton) && event_type == QEvent::MouseButtonPress) {
            bool checkState = index.data(Qt::CheckStateRole).value<bool>();
            return QItemSelectionModel::Rows
                   | (checkState ? QItemSelectionModel::Deselect : QItemSelectionModel::Select);
        }
        return QItemSelectionModel::NoUpdate;
    }

    return QTableView::selectionCommand(index, event);
}

void MaterialTableView::keyPressEvent(QKeyEvent* event)
{
    if (!event || event->key() != Qt::Key_Return || state() == QAbstractItemView::EditingState)
        return QTableView::keyPressEvent(event);

    const QModelIndex index = currentIndex();
    if (isKeyboardEditable(index))
        edit(index);
}

QModelIndex MaterialTableView::moveCursor(QAbstractItemView::CursorAction cursorAction,
                                          Qt::KeyboardModifiers modifiers)
{
    const QModelIndex current_index = currentIndex();
    bool filtered_action = cursorAction == QAbstractItemView::MoveNext
                           || cursorAction == QAbstractItemView::MovePrevious;

    if (!current_index.isValid() || !isTextField(current_index) || !filtered_action)
        return QTableView::moveCursor(cursorAction, modifiers);

    QModelIndex next = current_index;
    do {
        setCurrentIndex(next);
        next = QTableView::moveCursor(cursorAction, modifiers);
    } while (!isTextField(next));
    return next;
}

bool MaterialTableView::isTextField(const QModelIndex& index) const
{
    return index.isValid() && index.column() > 1; // color and checkbox are not keyboard editable
}

bool MaterialTableView::isKeyboardEditable(const QModelIndex& index) const
{
    return index.isValid() && index.column() > 0; // color and checkbox are not keyboard editable
}
