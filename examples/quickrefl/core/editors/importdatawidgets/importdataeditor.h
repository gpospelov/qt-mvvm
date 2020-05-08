// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef IMPORTDATAEDITOR_H
#define IMPORTDATAEDITOR_H

#include <QWidget>

namespace ModelView
{
class GraphCanvas;
class TopItemsTreeView;
class PropertyTreeView;
} // namespace ModelView

namespace DataImportLogic
{
class ImportOutput;
}

class RealDataModel;
class QToolBar;
class QBoxLayout;

//! Main editor to import user data.

class ImportDataEditor : public QWidget
{
    Q_OBJECT
public:
    ImportDataEditor(RealDataModel* model, QWidget* parent = nullptr);

private:
    void setup_toolbar();
    void setup_views();
    QBoxLayout* create_bottom_layout();

    void invokeImportDialog();
    void onImportDialogAccept(DataImportLogic::ImportOutput import_output);

private:
    RealDataModel* model{nullptr};
    QToolBar* toolbar{nullptr};
    ModelView::TopItemsTreeView* topitems_tree{nullptr};
    ModelView::GraphCanvas* graph_canvas{nullptr};
    ModelView::PropertyTreeView* property_tree{nullptr};
};

#endif // IMPORTDATAEDITOR_H
