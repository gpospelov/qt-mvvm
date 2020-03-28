// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef QUICKSIMEDITOR_H
#define QUICKSIMEDITOR_H

#include <QWidget>
#include <memory>

namespace ModelView
{
class GraphCanvas;
}

class JobModel;
class ApplicationModels;
class QuickSimController;

//! Quick reflectivity simulations.

class QuickSimEditor : public QWidget
{
    Q_OBJECT
public:
    QuickSimEditor(ApplicationModels* app_models, QWidget* parent = nullptr);
    ~QuickSimEditor();

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

private:
    ApplicationModels* app_models{nullptr};
    std::unique_ptr<JobModel> job_model;
    QuickSimController* sim_controller{nullptr};
    ModelView::GraphCanvas* graph_canvas{nullptr};
};

#endif // QUICKSIMEDITOR_H
