// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MATERIALEDITORACTIONS_H
#define MATERIALEDITORACTIONS_H

#include <QObject>
#include <memory>

class MaterialModel;
class MaterialSelectionModel;

//! Handles user actions applied to material table.
//! Belongs to MaterialEditor.

class MaterialEditorActions : public QObject
{
    Q_OBJECT
public:
    MaterialEditorActions(MaterialModel* material_model, QObject* parent = nullptr);
    ~MaterialEditorActions();

    void onAddMaterial();
    void onCloneMaterial();
    void onRemoveMaterial();
    void onMoveUp();
    void onMoveDown();
    void onExport();
    void onImport();

    void setMaterialSelectionModel(MaterialSelectionModel* selection_model);

private:
    struct MaterialEditorActionsImpl;
    std::unique_ptr<MaterialEditorActionsImpl> p_impl;
};

#endif // MATERIALEDITORACTIONS_H
