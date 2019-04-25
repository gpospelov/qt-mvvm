#ifndef CUSTOMTABLEVIEW_H
#define CUSTOMTABLEVIEW_H

#include <QTableView>
#include "treemodel.h"

class TableViewDelegate;

class CustomTableView : public QTableView
{
    Q_OBJECT
public:
    CustomTableView(QWidget* parent = nullptr);
    void updateRepresentation();

protected slots:
    void rowsInserted(const QModelIndex& parent, int start, int end) override;
    void rowsAboutToBeRemoved(const QModelIndex& parent, int start, int end) override;
};

#endif // CUSTOMTABLEVIEW_H
