#ifndef SPLITLAYEREDITOR_H
#define SPLITLAYEREDITOR_H

#include <QWidget>

class QStandardItemModel;
class QTableView;
class QTableWidget;
class QVBoxLayout;

class SplitLayerEditor : public QWidget
{
    Q_OBJECT
public:
    explicit SplitLayerEditor(QWidget* parent = nullptr);

private:
    QVBoxLayout* createMaterialPanel();
    QVBoxLayout* createMultilayerPanel();

    // views
    QTableView* m_material_view;
    QTableWidget* m_sample_table;

    // models
    QStandardItemModel* m_material_model;
};

#endif // SPLITLAYEREDITOR_H
