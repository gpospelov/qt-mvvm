// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "dataimportdialog.h"

#include "importfilewidget.h"
#include "importparameterwidget.h"
#include "importtextview.h"

#include <QSplitter>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDialogButtonBox>
#include <QSizePolicy>

//! This is the constructor
DataImport::DataLoaderDialog::DataLoaderDialog(QWidget* parent): QDialog(parent)
{   
    // The placeholders
    auto v_splitter = new QSplitter(Qt::Vertical, this);
    auto h_splitter = new QSplitter(v_splitter);
    v_splitter->setChildrenCollapsible(false);
    h_splitter->setChildrenCollapsible(false);

    auto file_list_space = new QGroupBox("Selected Files:", h_splitter);
    auto selection_space = new QTabWidget(h_splitter);
    auto parameter_space = new QGroupBox("Import parameters:", v_splitter);

    // The dialog buttons
    auto button_box = new QDialogButtonBox(QDialogButtonBox::Cancel | QDialogButtonBox::Ok);
    connect(button_box, SIGNAL(accepted()), this, SLOT(accept()));
    connect(button_box, SIGNAL(rejected()), this, SLOT(reject()));

    // Manage the layout
    h_splitter->addWidget(file_list_space);
    h_splitter->addWidget(selection_space);
    auto v_layout = new QVBoxLayout(this);
    v_splitter->addWidget(h_splitter);
    v_splitter->addWidget(parameter_space);
    v_layout->addWidget(v_splitter);
    v_layout->addWidget(button_box);

    // Finally set up the individual elements
    setUpFileListSpace(file_list_space);
    setUpParameterSpace(parameter_space);
    setUpSelectionSpace(selection_space);
}

//! Helper function to set up the file list area
void DataImport::DataLoaderDialog::setUpFileListSpace(QGroupBox* conainer)
{
    conainer->setContentsMargins(0,0,0,0);
    auto layout = new QVBoxLayout(conainer);
    p_import_file_list = new DataImport::ImportFileWidget(conainer);
    layout->addWidget(p_import_file_list);
    layout->setSpacing(0);
}

//! Helper function to set up the parameter area
void DataImport::DataLoaderDialog::setUpParameterSpace(QGroupBox* conainer)
{
    conainer->setContentsMargins(0,0,0,0);
    auto layout = new QVBoxLayout(conainer);
    p_parameter_dialog = new DataImport::ImportParameterWidget(p_data_import_logic.get(), conainer);
    layout->addWidget(p_parameter_dialog);
    layout->setSpacing(0);
}

//! Helper function to set up the selection area
void DataImport::DataLoaderDialog::setUpSelectionSpace(QTabWidget* tab_widget)
{
    auto first_tab = new QWidget(tab_widget);
    auto first_layout = new QVBoxLayout(first_tab);
    p_text_view = new ImportTextView(first_tab);
    first_layout->addWidget(p_text_view);

    auto second_tab = new QWidget(tab_widget);
    auto second_layout = new QVBoxLayout(second_tab);
    p_table_view = new QTableView(second_tab);
    second_layout->addWidget(p_table_view);

    
    tab_widget->addTab(first_tab, "Text view");
    tab_widget->addTab(second_tab, "Table view");
}

//! This function will manage the chnage of file selection
void DataImport::DataLoaderDialog::selectedFileChanged()
{
    int file_num = p_import_file_list->currentSelection();
    if (file_num<0){
        p_text_view->setHtml("");
    }else{
        p_text_view->setHtml(QString::fromStdString(p_data_import_logic->getPreview(file_num)));
    }
}

//! This function will manage the change in the line selections
void DataImport::DataLoaderDialog::lineParameterChanged()
{
    // p_data_import_logic->setProcessingText(p_parameter_dialog->stringPresent(),
    //                                        p_parameter_dialog->stringLocation(),
    //                                        p_parameter_dialog->stringColor());
    selectedFileChanged();
}
