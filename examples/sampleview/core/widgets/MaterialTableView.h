#ifndef MATERIALSELECTIONMODEL_H
#define MATERIALSELECTIONMODEL_H

#include <QTableView>

class MaterialTableView : public QTableView
{
public:
    using QTableView::QTableView;
    ~MaterialTableView() override;

protected:
    QItemSelectionModel::SelectionFlags
    selectionCommand(const QModelIndex& index, const QEvent* event = nullptr) const override;

    void keyPressEvent(QKeyEvent* event) override;
    QModelIndex moveCursor(QAbstractItemView::CursorAction cursorAction,
                           Qt::KeyboardModifiers modifiers) override;

private:
    bool isTextField(const QModelIndex& index) const;
    bool isKeyboardEditable(const QModelIndex& index) const;
};

#endif // MATERIALSELECTIONMODEL_H
