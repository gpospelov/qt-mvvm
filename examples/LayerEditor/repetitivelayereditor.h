#ifndef REPETITIVELAYEREDITOR_H
#define REPETITIVELAYEREDITOR_H

#include <QWidget>

class QStandardItemModel;
class QTableView;
class QTableWidget;
class QVBoxLayout;

class RepetitiveLayerEditor : public QWidget
{
    Q_OBJECT
public:
    explicit RepetitiveLayerEditor(QWidget *parent = nullptr);

private:
    QVBoxLayout* createMaterialPanel();
    QVBoxLayout* createMultilayerPanel();

    // views
    QTableView* m_material_view;
    QTableWidget* m_sample_table;

    // models
    QStandardItemModel* m_material_model;
};

#endif // REPETITIVELAYEREDITOR_H
