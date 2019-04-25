#ifndef TREELAYEREDITOR_H
#define TREELAYEREDITOR_H

#include <QWidget>

class QStandardItemModel;
class QTableView;
class QTreeView;
class QVBoxLayout;

class TreeLayerEditor : public QWidget
{
    Q_OBJECT
public:
    explicit TreeLayerEditor(QWidget *parent = nullptr);

private:
    QVBoxLayout* createMaterialPanel();
    QVBoxLayout* createMultilayerPanel();

    // views
    QTableView* m_material_view;
    QTreeView* m_sample_tree;

    // models
    QStandardItemModel* m_material_model;
    QStandardItemModel* m_sample_model;
};

#endif // TREELAYEREDITOR_H
