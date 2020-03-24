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

class MaterialModel;
class MaterialEditorActions;
class MaterialEditorToolBar;
class MaterialEditorWidget;

namespace ModelView
{
class AbstractViewModel;
}

//! Material editor.

class MaterialEditor : public QWidget
{
    Q_OBJECT
public:
    MaterialEditor(MaterialModel* material_model, QWidget* parent = nullptr);
    ~MaterialEditor();

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

private:
    MaterialModel* material_model{nullptr};
    MaterialEditorActions* actions{nullptr};
    MaterialEditorToolBar* toolbar{nullptr};
    MaterialEditorWidget* editor_widget{nullptr};
};

#endif // MATERIALEDITOR_H
