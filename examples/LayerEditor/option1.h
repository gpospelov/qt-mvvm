#ifndef OPTION1_H
#define OPTION1_H

#include <QWidget>

class CustomTableView;
class QComboBox;
class QPushButton;
class QTableView;
class QTreeView;
class QVBoxLayout;
class MaterialModel;
class TreeModel;

class Option1Widget : public QWidget
{
    Q_OBJECT
public:
    Option1Widget(QWidget* parent = nullptr);

private:
    QVBoxLayout* createMaterialPanel();
    QVBoxLayout* createMultilayerPanel();

    // views
    QTableView* m_material_view;
	CustomTableView* m_sample_view;
    QTreeView* m_sample_model_view;

    // models
    MaterialModel* m_material_model;
    TreeModel* m_sample_model;
};

#endif // OPTION1_H
