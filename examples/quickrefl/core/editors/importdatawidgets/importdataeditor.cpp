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
#include <mvvm/standarditems/graphviewportitem.h>
#include <mvvm/utils/fileutils.h>
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
}

void ImportDataEditor::setup_toolbar()
{
    toolbar->setIconSize(StyleUtils::ToolBarIconSize());
    toolbar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    auto load_action = new QAction("Famous Loader");
    load_action->setToolTip("Summons the famous data loader.");
    load_action->setIcon(QIcon(":/icons/aspect-ratio.svg"));
    toolbar->addAction(load_action);
    connect(load_action, &QAction::triggered, this, &ImportDataEditor::invokeImportDialog);
}

void ImportDataEditor::setup_views()
{
    // make left tree looking on container with viewports
    // auto root_item = model->insertItem<ModelView::SessionItem>();
    topitems_tree->setRootSessionItem(model->rootItem());

    // make property tree showing the item selected
    auto on_item_selected = [this](SessionItem* item) {
        property_tree->setItem(item);
        // FIXME if viewport contains lots of graphs we probably would like to show only single
        // graph on graph selection. For that we have to implement for GraphViewportItem
        // corresponding functionality (hide items not from the list, for example).
        if (auto viewport = dynamic_cast<ModelView::GraphViewportItem*>(item); viewport)
            graph_canvas->setItem(viewport);
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
    DataCollectionItem* data_node;
    for (auto& path : import_output.keys()) {
        if ((import_output.merge() && path == *(import_output.keys().begin()))
            || (!import_output.merge()))
            data_node = model->insertDataNode();
        auto parsed_file_output = import_output[path];
        for (int i = 0; i < parsed_file_output->dataCount(); ++i) {
            auto data_struct = RealDataStruct();

            data_struct.name = Utils::base_name(path);
            data_struct.type = parsed_file_output->dataType(i);

            data_struct.axis = parsed_file_output->axis();
            data_struct.axis_name = parsed_file_output->axisName();
            data_struct.axis_unit = parsed_file_output->axisUnit();

            data_struct.data = parsed_file_output->data(i);
            data_struct.data_name = parsed_file_output->dataName(i);
            data_struct.data_unit = parsed_file_output->dataUnit(i);

            model->addDataToNode(data_node, data_struct);
        }
    }
}
