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
#include "importfilterwidget.h"
#include "importtableview.h"
#include "importtextview.h"

#include <QDialogButtonBox>
#include <QHBoxLayout>
#include <QSettings>
#include <QSizePolicy>
#include <QSplitter>
#include <QVBoxLayout>

namespace DataImportGui
{

//! This is the constructor
DataLoaderDialog::DataLoaderDialog(QWidget* parent) : QDialog(parent)
{
    // Init the main import logic
    p_data_import_logic =
        std::unique_ptr<DataImportLogic::ImportLogic>(new DataImportLogic::ImportLogic());

    // The placeholders
    auto h_splitter = new QSplitter(this);
    auto v_splitter = new QSplitter(Qt::Vertical, h_splitter);
    h_splitter->setChildrenCollapsible(false);
    v_splitter->setChildrenCollapsible(false);

    auto file_list_space = new QGroupBox("Selected Files:", v_splitter);
    auto parameter_space = new QGroupBox("Text Selection rules:", v_splitter);
    p_selection_space = new QTabWidget(v_splitter);

    // The dialog buttons
    auto button_box = new QDialogButtonBox(QDialogButtonBox::Cancel | QDialogButtonBox::Ok);
    connect(button_box, SIGNAL(accepted()), this, SLOT(accept()));
    connect(button_box, SIGNAL(rejected()), this, SLOT(reject()));

    // Set up the individual elements
    setUpFileListSpace(file_list_space);
    setUpParameterSpace(parameter_space);
    setUpSelectionSpace(p_selection_space);

    // Manage the layout
    v_splitter->addWidget(file_list_space);
    v_splitter->addWidget(parameter_space);
    h_splitter->addWidget(v_splitter);
    h_splitter->addWidget(p_selection_space);

    auto v_layout = new QVBoxLayout(this);
    v_layout->addWidget(h_splitter);
    v_layout->addWidget(button_box);

    v_splitter->setStretchFactor(0, 0);
    v_splitter->setStretchFactor(1, 1);
    h_splitter->setStretchFactor(0, 0);
    h_splitter->setStretchFactor(1, 1);

    readSettings();
}

//! Helper function to set up the file list area
void DataLoaderDialog::setUpFileListSpace(QGroupBox* conainer)
{

    auto layout = new QVBoxLayout(conainer);
    p_import_file_list = new ImportFileWidget(conainer);
    layout->addWidget(p_import_file_list);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    conainer->setMinimumHeight(p_import_file_list->minimumHeight());
    conainer->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);

    connect(p_import_file_list, SIGNAL(filesChanged(std::vector<std::string>)),
            p_data_import_logic.get(), SLOT(setFiles(std::vector<std::string>)));

    connect(p_import_file_list, SIGNAL(selectionChanged()), this, SLOT(selectedFileChanged()));
}

//! Helper function to set up the parameter area
void DataLoaderDialog::setUpParameterSpace(QGroupBox* conainer)
{

    auto layout = new QVBoxLayout(conainer);
    p_parameter_dialog = new ImportFilterWidget(p_data_import_logic.get(), conainer);
    layout->addWidget(p_parameter_dialog);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(0);
    conainer->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);

    connect(p_parameter_dialog, SIGNAL(parameterChanged()), this, SLOT(selectedFileChanged()));
}

//! Helper function to set up the selection area
void DataLoaderDialog::setUpSelectionSpace(QTabWidget* tab_widget)
{
    auto first_tab = new QWidget(tab_widget);
    auto first_layout = new QVBoxLayout(first_tab);
    p_text_view = new ImportTextView(first_tab);
    first_layout->addWidget(p_text_view);

    auto second_tab = new QWidget(tab_widget);
    auto second_layout = new QVBoxLayout(second_tab);
    p_table_view = new ImportTableView(second_tab);
    p_table_view->model()->setDataStructure(p_data_import_logic->dataStructure());
    second_layout->addWidget(p_table_view);

    tab_widget->addTab(first_tab, "Text view");
    tab_widget->addTab(second_tab, "Table view");

    connect(tab_widget, &QTabWidget::currentChanged, this, &DataLoaderDialog::selectedFileChanged);
}

//! This function will manage the chnage of file selection
void DataLoaderDialog::selectedFileChanged()
{
    int file_num = p_import_file_list->currentSelection();
    if (file_num < 0) {
        p_text_view->setHtml("");
        p_table_view->model()->refreshFromDataStructure();
    } else {
        if (p_selection_space->currentIndex() == 0) {
            p_text_view->setHtml(QString::fromStdString(p_data_import_logic->getPreview(file_num)));
        } else if (p_selection_space->currentIndex() == 1) {
            p_data_import_logic->updateData(file_num);
            p_table_view->model()->refreshFromDataStructure();
        }
    }
}

//! Write the QSettings
void DataLoaderDialog::writeSettings()
{
    QSettings settings("quickrefl", "ImportDialog");

    settings.beginGroup("Geometry");
    settings.setValue("size", size());
    settings.setValue("pos", pos());
    settings.endGroup();

    p_import_file_list->writeSettings(settings);
    p_parameter_dialog->writeSettings(settings);
}

//! read the Qsettings
void DataLoaderDialog::readSettings()
{
    QSettings settings("quickrefl", "ImportDialog");

    settings.beginGroup("Geometry");
    resize(settings.value("size", QSize(400, 400)).toSize());
    move(settings.value("pos", QPoint(200, 200)).toPoint());
    settings.endGroup();

    p_import_file_list->readSettings(settings);
    p_parameter_dialog->readSettings(settings);
}

void DataLoaderDialog::accept()
{
    writeSettings();
    close();
}

} // End of namespace DataImportGui
