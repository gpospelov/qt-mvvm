// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MATERIALEDITOR_H
#define MATERIALEDITOR_H

#include <QWidget>
#include <memory>

class MaterialEditorToolBar;
class MaterialEditorActions;
class MaterialModel;
class QTableView;

namespace ModelView {
class AbstractViewModel;
}

//! Material editor.

class MaterialEditor : public QWidget
{
    Q_OBJECT
public:
    MaterialEditor(MaterialModel* material_model, QWidget* parent = nullptr);
    ~MaterialEditor();

private:
    MaterialModel* material_model{nullptr};
    std::unique_ptr<ModelView::AbstractViewModel> view_model;
    MaterialEditorActions* actions{nullptr};
    MaterialEditorToolBar* toolbar{nullptr};
};

#endif // MATERIALEDITOR_H

