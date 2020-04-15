// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "dataimportdialog.h"


#include <QSplitter>
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <QSizePolicy>

//! This is the constructor
DataImport::DataLoaderDialog::DataLoaderDialog(QWidget* parent): QDialog(parent)
{   
    // The main playground
    auto v_splitter = new QSplitter(Qt::Vertical, this);
    auto h_splitter = new QSplitter(v_splitter);
    h_splitter->setChildrenCollapsible(false);
    v_splitter->setChildrenCollapsible(false);

    // The placeholders
    auto file_list_space = new QGroupBox("Selected Files:", h_splitter);
    auto parameter_space = new QGroupBox("Import parameters:", h_splitter);
    auto selection_space = new QTabWidget(v_splitter);

    // The dialog buttons
    auto button_box = new QDialogButtonBox(QDialogButtonBox::Cancel | QDialogButtonBox::Ok);
    connect(button_box, SIGNAL(accepted()), this, SLOT(accept()));
    connect(button_box, SIGNAL(rejected()), this, SLOT(reject()));

    // Manage the layout
    h_splitter->addWidget(file_list_space);
    h_splitter->addWidget(parameter_space);
    v_splitter->addWidget(h_splitter);
    v_splitter->addWidget(selection_space);

    auto layout = new QVBoxLayout(this);
    layout->addWidget(v_splitter);
    layout->addWidget(button_box);

    // Finally set up the individual elements
    setUpFileListSpace(file_list_space);
    setUpParameterSpace(parameter_space);
    setUpSelectionSpace(selection_space);

    h_splitter->setStretchFactor(0,0);
    h_splitter->setStretchFactor(1,1);
    v_splitter->setStretchFactor(0,0);
    v_splitter->setStretchFactor(1,1);
    
}

//! Helper function to set up the file list area
void DataImport::DataLoaderDialog::setUpFileListSpace(QGroupBox* conainer)
{

}

//! Helper function to set up the parameter area
void DataImport::DataLoaderDialog::setUpParameterSpace(QGroupBox* conainer)
{

}

//! Helper function to set up the selection area
void DataImport::DataLoaderDialog::setUpSelectionSpace(QTabWidget* tab_widget)
{

}

