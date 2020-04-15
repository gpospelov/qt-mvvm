// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef SLDEDITOR_H
#define SLDEDITOR_H

class SLDEditorActions;
class SLDEditorToolBar;
class SLDViewWidget;
class ApplicationModels;

#include <QWidget>

//! The SLD editor QWidget
class SLDEditor : public QWidget
{

public:
    SLDEditor(ApplicationModels* apps_model, QWidget* parent = nullptr);
    ~SLDEditor();

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

private:
    SLDEditorActions* p_editor_actions{nullptr};
    SLDEditorToolBar* p_editor_tollbar{nullptr};
    SLDViewWidget* p_view_widget{nullptr};
};

#endif // SLDEDITOR_H