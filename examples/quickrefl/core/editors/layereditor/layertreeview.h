// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef LAYERTREEVIEW_H
#define LAYERTREEVIEW_H

#include <QTreeView>

//! Extension of QTreeView for layer editing.

class LayerTreeView : public QTreeView
{
public:
    using QTreeView::QTreeView;

    explicit LayerTreeView(QWidget* parent = nullptr);
    ~LayerTreeView() override;

    void setModel(QAbstractItemModel* model) override;
};

#endif // LAYERTREEVIEW_H
