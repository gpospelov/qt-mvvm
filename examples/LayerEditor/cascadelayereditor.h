#ifndef CASCADELAYEREDITOR_H
#define CASCADELAYEREDITOR_H

#include <QWidget>

class CustomTableView;
class QComboBox;
class QPushButton;
class QStandardItemModel;
class QTableView;
class QTreeView;
class QVBoxLayout;
class TreeModel;

class CascadeLayerEditor : public QWidget
{
    Q_OBJECT
public:
    CascadeLayerEditor(QWidget* parent = nullptr);

private:
    QVBoxLayout* createMaterialPanel();
    QVBoxLayout* createMultilayerPanel();

    // views
    QTableView* m_material_view;
    CustomTableView* m_sample_view;

    // models
    QStandardItemModel* m_material_model;
    TreeModel* m_sample_model;
};

#endif // CASCADELAYEREDITOR_H
