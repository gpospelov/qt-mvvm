// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "importdataeditor.h"
#include "dataimportdialog.h"
#include "datasetconvenience.h"
#include "datasetitem.h"
#include "importoutput.h"
#include "realdatamodel.h"
#include "styleutils.h"

#include <QAction>
#include <QDebug>
#include <QDialog>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QLabel>
#include <QToolBar>
#include <QVBoxLayout>

#include <mvvm/model/modelutils.h>
#include <mvvm/plotting/graphcanvas.h>
#include <mvvm/standarditems/containeritem.h>
#include <mvvm/standarditems/graphitem.h>
#include <mvvm/standarditems/graphviewportitem.h>
#include <mvvm/utils/fileutils.h>
#include <mvvm/viewmodel/viewmodel.h>
#include <mvvm/widgets/standardtreeviews.h>

using namespace ModelView;

ImportDataEditor::ImportDataEditor(RealDataModel* model, QWidget* parent)
    : QWidget(parent), model(model), toolbar(new QToolBar),
      topitems_tree(new TopItemsTreeView(model)), graph_canvas(new GraphCanvas),
      property_tree(new PropertyTreeView)
{
    auto layout = new QVBoxLayout(this);
    layout->addWidget(toolbar);
    layout->addLayout(create_bottom_layout());
    setup_toolbar();
    setup_views();

    topitems_tree->viewModel()->setRootSessionItem(
        ModelView::Utils::TopItem<DataCollectionItem>(model));
}

void ImportDataEditor::setup_toolbar()
{
    toolbar->setIconSize(StyleUtils::ToolBarIconSize());
    toolbar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    auto load_action = new QAction("Famous Loader", this);
    load_action->setToolTip("Summons the famous data loader.");
    load_action->setIcon(QIcon(":/icons/aspect-ratio.svg"));
    toolbar->addAction(load_action);
    connect(load_action, &QAction::triggered, this, &ImportDataEditor::invokeImportDialog);
}

void ImportDataEditor::setup_views()
{
    // make left tree looking on container with viewports
    topitems_tree->setRootSessionItem(model->rootItem());

    // make property tree showing the item selected
    auto on_item_selected = [this](SessionItem* item) {
        property_tree->setItem(item);
        if (auto viewport = dynamic_cast<ModelView::GraphViewportItem*>(item); viewport) {
            viewport->resetSelected();
            graph_canvas->setItem(viewport);
        } else if (auto graph_item = dynamic_cast<ModelView::GraphItem*>(item); graph_item) {
            auto viewport = dynamic_cast<ModelView::GraphViewportItem*>(graph_item->parent());
            viewport->setSelected(std::vector<ModelView::GraphItem*>{graph_item});
            graph_canvas->setItem(viewport);
        }
    };
    connect(topitems_tree, &TopItemsTreeView::itemSelected, on_item_selected);
}

QBoxLayout* ImportDataEditor::create_bottom_layout()
{
    auto result = new QHBoxLayout;
    result->addWidget(topitems_tree, 1);
    result->addWidget(graph_canvas, 5);
    result->addWidget(property_tree, 1);
    return result;
}

//! Invode the data load dialog and connect its state
void ImportDataEditor::invokeImportDialog()
{
    DataImportGui::DataLoaderDialog assistant(this);
    int dialog_code = assistant.exec();
    if (dialog_code == QDialog::Accepted) {
        onImportDialogAccept(assistant.result());
    }
}

//! Process the accepted state
void ImportDataEditor::onImportDialogAccept(DataImportLogic::ImportOutput import_output)
{
    DataCollectionItem* data_node = ModelView::Utils::TopItem<DataCollectionItem>(model);
    for (auto& path : import_output.keys()) {
        auto parsed_file_output = import_output[path];
        for (int i = 0; i < parsed_file_output->dataCount(); ++i) {
            auto data_struct = convertToRealDataStruct(path, parsed_file_output, i);
            model->addDataToNode(data_node, data_struct);
        }
    }
}

//! Convert data column to RealDatastructure
RealDataStruct
ImportDataEditor::convertToRealDataStruct(const std::string& path,
                                          const DataImportLogic::ParsedFileOutptut* import_output,
                                          const int column)
{
    auto data_struct = RealDataStruct();

    data_struct.name = Utils::base_name(path);
    data_struct.type = import_output->dataType(column);

    data_struct.axis = import_output->axis();
    data_struct.axis_name = import_output->axisName();
    data_struct.axis_unit = import_output->axisUnit();

    data_struct.data = import_output->data(column);
    data_struct.data_name = import_output->dataName(column);
    data_struct.data_unit = import_output->dataUnit(column);

    return data_struct;
}
