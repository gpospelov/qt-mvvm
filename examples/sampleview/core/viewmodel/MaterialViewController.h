#ifndef MATERIALVIEWCONTROLLER_H
#define MATERIALVIEWCONTROLLER_H

#include "MaterialTableViewModel.h"
#include <mvvm/model/mvvm_types.h>
#include <QItemSelectionModel>
#include <deque>

namespace ModelView {
class SessionItem;
}

class MaterialModel;
class MaterialBaseItem;

class MaterialViewController : public QObject
{
    Q_OBJECT
public:
    MaterialViewController(MaterialModel* model);

// getters:
    MaterialTableViewModel& viewModel() { return m_view_model; }
    QItemSelectionModel& selectionModel() { return m_selection_model; }
    QStringList materialSets() const;

    //! adds row to current selection and checks the box
    void toggleRowSelection(const QModelIndex& index);
    //! adds row span to current selection
    void toggleRowSpanSelection(const QModelIndex& index);

// public slots:
    void onMaterialSelectionChange(const QString& material_display_name);
    void onCreateMaterial();
    void onCloneMaterial();
    void onRemoveMaterial();

signals:
    void rowCheckStateChanged(const QList<QModelIndex>& index_list);

private:
    void updateSelection(const QModelIndex& current);
    void onSelectionChanged(const QItemSelection&, const QItemSelection&);

    //! Returns the material items corresponding to the current selection of the selection model.
    QList<MaterialBaseItem*> selectedMaterialItems() const;
    QList<QModelIndex> checkedItems() const;

    MaterialModel* m_material_model;
    MaterialTableViewModel m_view_model;
    QItemSelectionModel m_selection_model;

    std::string m_current_material_type;
    std::deque<QColor> m_color_queue;
};

#endif // MATERIALVIEWCONTROLLER_H
