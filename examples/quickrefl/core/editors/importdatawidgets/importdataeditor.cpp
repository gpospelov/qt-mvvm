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
#include "dataviewmodel.h"
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
    : QWidget(parent), p_tree_view(new QTreeView(this)), p_model(model),
      p_view_model(new DataViewModel(model)),
      p_data_selection_model(new DataSelectionModel(p_view_model, p_tree_view)),
      p_toolbar(new QToolBar), p_graph_canvas(new GraphCanvas),
      p_property_tree(new PropertyTreeView)
{
    setupToolBar();
    setupLayout();
    setupViews();

    p_view_model->setRootSessionItem(ModelView::Utils::TopItem<DataCollectionItem>(model));
    p_tree_view->setModel(p_view_model);
    p_tree_view->setSelectionModel(p_data_selection_model);
    p_tree_view->setSelectionMode(QAbstractItemView::ExtendedSelection);
    p_tree_view->setDragDropMode(QAbstractItemView::InternalMove);
    p_tree_view->setDragEnabled(true);
}

//! Set up the toolbar for the data management
void ImportDataEditor::setupToolBar()
{
    auto add_group_action = new QAction("Add a data group", this);
    add_group_action->setToolTip("Add a data group to manage loaded items.");
    add_group_action->setIcon(QIcon(":/icons/plus-box-outline.svg"));

    auto merge_group_action = new QAction("Merge data groups", this);
    merge_group_action->setToolTip("Merge selected data groups into one.");
    merge_group_action->setIcon(QIcon(":/icons/set-merge.svg"));
    merge_group_action->setObjectName("merge_group_action");

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
    undo_action->setToolTip("Undo the action last performed.");
    undo_action->setIcon(QIcon(":/icons/undo.svg"));

    auto redo_action = new QAction("Redo data action", this);
    redo_action->setToolTip("Redo the action just performed.");
    redo_action->setIcon(QIcon(":/icons/redo.svg"));

    auto reset_graph_action = new QAction("Reset Aspect ratio", this);
    reset_graph_action->setToolTip("Reset the graph aspect ratio");
    reset_graph_action->setIcon(QIcon(":/icons/aspect-ratio.svg"));

    p_toolbar->setIconSize(StyleUtils::ToolBarIconSize());
    p_toolbar->setOrientation(Qt::Horizontal);

    p_toolbar->addAction(add_group_action);
    p_toolbar->addAction(merge_group_action);
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

    connect(add_group_action, &QAction::triggered, this, &ImportDataEditor::addDataGroup);
    connect(merge_group_action, &QAction::triggered, this, &ImportDataEditor::mergeDataGroups);
    connect(load_action, &QAction::triggered, this, &ImportDataEditor::invokeImportDialog);
    connect(delete_action, &QAction::triggered, this, &ImportDataEditor::deleteItem);
    connect(reset_action, &QAction::triggered, this, &ImportDataEditor::resetAll);
    connect(reset_graph_action, &QAction::triggered, p_graph_canvas,
            &ModelView::GraphCanvas::update_viewport);
}

//! Set up all the view items
void ImportDataEditor::setupViews()
{
    connect(p_data_selection_model, &DataSelectionModel::selectionChanged, this,
            &ImportDataEditor::selectionChanged);
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
    left_splitter->addWidget(p_tree_view);
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

//! Manage a selection change of the treeview
void ImportDataEditor::selectionChanged()
{
    auto items = p_data_selection_model->selectedItems();
    items.erase(std::remove(begin(items), end(items), nullptr), end(items));
    setMergeEnabled((items.size() > 1) ? (p_model->checkAllGroup(items)) : (false));

    if (items.size() == 0)
        return;

    if (auto viewport = p_model->checkAllGraph(items); viewport) {
        std::vector<ModelView::GraphItem*> graph_items;
        for (std::vector<ModelView::SessionItem*>::iterator it = items.begin(); it != items.end();
             ++it) {
            graph_items.push_back(dynamic_cast<ModelView::GraphItem*>(*it));
        }
        viewport->setSelected(graph_items);
        p_graph_canvas->setItem(viewport);
        return;
    }

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
}

//! check itf all items are DataGroupItems, if yes return true
void ImportDataEditor::setMergeEnabled(bool enabled)
{
    auto action = findChild<QAction*>("merge_group_action");
    action->setEnabled(enabled);
}

//! Create a new data grou item in the current data collection item
void ImportDataEditor::addDataGroup()
{
    DataCollectionItem* data_node = ModelView::Utils::TopItem<DataCollectionItem>(p_model);
    p_model->addDataToCollection(RealDataStruct(), data_node, nullptr);
}

//! Merge the selected actions
void ImportDataEditor::mergeDataGroups()
{
    auto items = p_data_selection_model->selectedItems();
    items.erase(std::remove(begin(items), end(items), nullptr), end(items));
    if (!p_model->checkAllGroup(items))
        return;

    p_model->mergeItems(items);
}

//! Invoke the data load dialog and connect its state
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
    DataGroupItem* data_group = nullptr;
    for (auto& path : import_output.keys()) {
        auto parsed_file_output = import_output[path];
        for (int i = 0; i < parsed_file_output->dataCount(); ++i) {
            auto data_struct = convertToRealDataStruct(path, parsed_file_output, i);
            data_group = p_model->addDataToCollection(data_struct, data_node, data_group);
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
    p_model->removeDataFromCollection(items_to_delete);
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
        p_model->removeAllDataFromCollection(data_node);
    }
}
