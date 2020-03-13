// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MATERIALTABLEVIEW_H
#define MATERIALTABLEVIEW_H

#include <QTableView>

//! Extension of QTableView for material editing.
//! Provide better user experinece while navigating between cells.
//! Part of MaterialTableWidget.

class MaterialTableView : public QTableView
{
public:
    using QTableView::QTableView;
    ~MaterialTableView() override;

    void setModel(QAbstractItemModel* model) override;

protected:
    void keyPressEvent(QKeyEvent* event) override;
    QModelIndex moveCursor(QAbstractItemView::CursorAction cursorAction,
                           Qt::KeyboardModifiers modifiers) override;

private:
    bool isTextField(const QModelIndex& index) const;
    bool isKeyboardEditable(const QModelIndex& index) const;
};

#endif // MATERIALTABLEVIEW_H
