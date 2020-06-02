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
#include <string>

namespace ModelView
{
class GraphCanvas;
class TopItemsTreeView;
class PropertyTreeView;
} // namespace ModelView

namespace DataImportLogic
{
class ImportOutput;
class ParsedFileOutptut;
}

class RealDataModel;
class QToolBar;
class QBoxLayout;
class RealDataStruct;

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
    RealDataStruct convertToRealDataStruct(const std::string& path, const DataImportLogic::ParsedFileOutptut* import_output, const int column);

private:
    RealDataModel* model{nullptr};
    QToolBar* toolbar{nullptr};
    ModelView::TopItemsTreeView* topitems_tree{nullptr};
    ModelView::GraphCanvas* graph_canvas{nullptr};
    ModelView::PropertyTreeView* property_tree{nullptr};
};

#endif // IMPORTDATAEDITOR_H
