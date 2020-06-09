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
#include "dataselectionmodel.h"
#include "datasetconvenience.h"
#include "datasetitem.h"
#include "importoutput.h"
#include "realdatamodel.h"
#include "styleutils.h"

#include <QAction>
#include <QDialog>
#include <QHBoxLayout>
#include <QItemSelectionModel>
#include <QLabel>
#include <QMessageBox>
#include <QSplitter>
#include <QToolBar>
#include <QTreeView>
#include <QVBoxLayout>

#include <mvvm/model/modelutils.h>
#include <mvvm/plotting/graphcanvas.h>
#include <mvvm/standarditems/containeritem.h>
#include <mvvm/standarditems/graphitem.h>
#include <mvvm/standarditems/graphviewportitem.h>
#include <mvvm/utils/fileutils.h>
#include <mvvm/viewmodel/viewmodel.h>
#include <mvvm/viewmodel/viewmodelutils.h>
#include <mvvm/widgets/standardtreeviews.h>

using namespace ModelView;

ImportDataEditor::ImportDataEditor(RealDataModel* model, QWidget* parent)
    : QWidget(parent), p_model(model), p_topitems_tree(new TopItemsTreeView(model)),
      p_data_selection_model(
          new DataSelectionModel(p_topitems_tree->viewModel(), p_topitems_tree->treeView())),
      p_toolbar(new QToolBar), p_graph_canvas(new GraphCanvas),
      p_property_tree(new PropertyTreeView)
{
    setupToolBar();
    setupLayout();
    setupViews();

    p_topitems_tree->viewModel()->setRootSessionItem(
        ModelView::Utils::TopItem<DataCollectionItem>(model));
    p_topitems_tree->treeView()->setSelectionModel(p_data_selection_model);
}

//! Set up the toolbar for the data management
void ImportDataEditor::setupToolBar()
{
    auto load_action = new QAction("Data Loader", this);
    load_action->setToolTip("Opens the data loading dialog ...");
    load_action->setIcon(QIcon(":/icons/import.svg"));

    auto delete_action = new QAction("Delete selected", this);
    delete_action->setToolTip("Remove the currently selected item.");
    delete_action->setIcon(QIcon(":/icons/file-remove.svg"));

    auto reset_action = new QAction("Reset loaded", this);
    reset_action->setToolTip("Reset all the loaded items.");
    reset_action->setIcon(QIcon(":/icons/beaker-remove-outline.svg"));

    auto undo_action = new QAction("Undo data action", this);
    undo_action->setToolTip("Undo the action kust performed.");
    undo_action->setIcon(QIcon(":/icons/undo.svg"));

    auto redo_action = new QAction("Redo data action", this);
    redo_action->setToolTip("Redo the action ust performed.");
    redo_action->setIcon(QIcon(":/icons/redo.svg"));

    auto reset_graph_action = new QAction("Reset Aspect ratio", this);
    reset_graph_action->setToolTip("Reset the graph aspect ratio");
    reset_graph_action->setIcon(QIcon(":/icons/aspect-ratio.svg"));

    p_toolbar->setIconSize(StyleUtils::ToolBarIconSize());
    p_toolbar->setOrientation(Qt::Horizontal);
    p_toolbar->addAction(load_action);
    p_toolbar->addSeparator();
    p_toolbar->addAction(delete_action);
    p_toolbar->addAction(reset_action);
    p_toolbar->addSeparator();
    p_toolbar->addAction(undo_action);
    p_toolbar->addAction(redo_action);

    auto empty = new QWidget(p_toolbar);
    empty->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    p_toolbar->addWidget(empty);
    p_toolbar->addAction(reset_graph_action);

    connect(load_action, &QAction::triggered, this, &ImportDataEditor::invokeImportDialog);
    connect(delete_action, &QAction::triggered, this, &ImportDataEditor::deleteItem);
    connect(reset_action, &QAction::triggered, this, &ImportDataEditor::resetAll);
    connect(reset_graph_action, &QAction::triggered, p_graph_canvas,
            &ModelView::GraphCanvas::update_viewport);
}

//! Set up all the view items
void ImportDataEditor::setupViews()
{
    // make property tree showing the item selected
    auto on_item_selected = [this]() {
        auto items = p_data_selection_model->selectedItems();
        if (items.size() == 0)
            return;
        auto item = items.at(0);
        p_property_tree->setItem(item);
        if (auto viewport = dynamic_cast<ModelView::GraphViewportItem*>(item); viewport) {
            viewport->resetSelected();
            p_graph_canvas->setItem(viewport);
        } else if (auto graph_item = dynamic_cast<ModelView::GraphItem*>(item); graph_item) {
            auto viewport = dynamic_cast<ModelView::GraphViewportItem*>(graph_item->parent());
            viewport->setSelected(std::vector<ModelView::GraphItem*>{graph_item});
            p_graph_canvas->setItem(viewport);
        }
    };
    connect(p_data_selection_model, &DataSelectionModel::selectionChanged, on_item_selected);
}

//! Set up the layout of the widget
void ImportDataEditor::setupLayout()
{
    auto main_layout = new QVBoxLayout(this);
    auto main_splitter = new QSplitter(this);

    auto sub_data_widget = new QWidget(main_splitter);
    auto sub_data_layout = new QHBoxLayout(sub_data_widget);

    auto sub_graph_widget = new QWidget(main_splitter);
    auto sub_graph_layout = new QHBoxLayout(sub_graph_widget);

    auto left_splitter = new QSplitter(sub_data_widget);

    left_splitter->setOrientation(Qt::Vertical);
    left_splitter->addWidget(p_topitems_tree);
    left_splitter->addWidget(p_property_tree);
    left_splitter->setStretchFactor(0, 1);
    left_splitter->setStretchFactor(1, 0);

    sub_data_layout->addWidget(left_splitter);
    sub_graph_layout->addWidget(p_graph_canvas);

    main_splitter->addWidget(sub_data_widget);
    main_splitter->addWidget(sub_graph_widget);
    main_splitter->setStretchFactor(0, 0);
    main_splitter->setStretchFactor(1, 1);

    main_layout->addWidget(p_toolbar);
    main_layout->addWidget(main_splitter);
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
    DataCollectionItem* data_node = ModelView::Utils::TopItem<DataCollectionItem>(p_model);
    for (auto& path : import_output.keys()) {
        auto parsed_file_output = import_output[path];
        for (int i = 0; i < parsed_file_output->dataCount(); ++i) {
            auto data_struct = convertToRealDataStruct(path, parsed_file_output, i);
            p_model->addDataToNode(data_node, data_struct);
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

//! Delete the currently selected item
void ImportDataEditor::deleteItem()
{
    std::vector<SessionItem*> items_to_delete = p_data_selection_model->selectedItems();
    p_model->removeDataFromNode(items_to_delete);
}

//! Reset all items
void ImportDataEditor::resetAll()
{
    QMessageBox* reset_message = new QMessageBox;
    reset_message->setIcon(QMessageBox::Warning);
    reset_message->setText("You are about to clear all the loaded data.");
    reset_message->setInformativeText("Are you sure you want to proceed ?");
    reset_message->setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
    reset_message->setDefaultButton(QMessageBox::Cancel);
    int ret = reset_message->exec();

    if (ret == QMessageBox::Yes) {
        DataCollectionItem* data_node = ModelView::Utils::TopItem<DataCollectionItem>(p_model);
        p_model->removeAllDataFromNode(data_node);
    }
}
