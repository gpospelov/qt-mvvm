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

//! Quick reflectivity simulations.

class QuickSimEditor : public QWidget
{
    Q_OBJECT
public:
    QuickSimEditor(QWidget* parent = nullptr);
    ~QuickSimEditor();

    QSize sizeHint() const override;
    QSize minimumSizeHint() const override;

private:
    std::unique_ptr<JobModel> job_model;
    ModelView::GraphCanvas* graph_canvas{nullptr};
};

#endif // QUICKSIMEDITOR_H
