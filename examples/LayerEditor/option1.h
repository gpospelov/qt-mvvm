#ifndef OPTION1_H
#define OPTION1_H

#include <QWidget>

class QComboBox;
class QPushButton;
class QTableView;
class QTreeView;
class QVBoxLayout;
class MaterialModel;

class Option1Widget : public QWidget
{
    Q_OBJECT
public:
    Option1Widget(QWidget* parent = nullptr);

private:
    QVBoxLayout* createMaterialPanel();
    QVBoxLayout* createMultilayerPanel();

    // views
    QTableView* m_tableView;
    QTreeView* m_treeView;

    // models
    MaterialModel* m_material_model;
};

#endif // OPTION1_H
