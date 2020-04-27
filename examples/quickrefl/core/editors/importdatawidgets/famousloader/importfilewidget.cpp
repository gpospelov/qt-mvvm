// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "importfilewidget.h"

#include <QListView>
#include <QStringListModel>
#include <QHBoxLayout>
#include <QPushButton>
#include <QStyle>
#include <QSizePolicy>
#include <QIcon>
#include <QFileDialog>
#include <QItemSelectionModel>

//! This is the constructor
DataImport::ImportFileWidget::ImportFileWidget(QWidget* parent): QWidget(parent)
{   
    createWidgets();
}

//! Create all the widget elements
void DataImport::ImportFileWidget::createWidgets()
{
    auto main_layout = new QHBoxLayout(this);
    auto side_layout = new QVBoxLayout();

    // Set up the list
    p_list_view = new QListView(this);
    p_list_model = new QStringListModel();
    p_list_view->setModel(p_list_model);
    p_list_view->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // Set up the buttons
    auto add_button = new QPushButton(this);
    QIcon add_ic(style()->standardIcon(QStyle::SP_FileDialogNewFolder));
    add_button->setFlat(true);
    add_button->setFixedSize(add_ic.actualSize(add_ic.availableSizes().first()));
    add_button->setIcon(add_ic);
    add_button->setIconSize(add_ic.availableSizes().first());

    auto reset_button = new QPushButton(this);
    QIcon reset_ic(style()->standardIcon(QStyle::SP_DialogResetButton));
    reset_button->setFlat(true);
    reset_button->setFixedSize(reset_ic.actualSize(reset_ic.availableSizes().first()));
    reset_button->setIcon(reset_ic);
    reset_button->setIconSize(reset_ic.availableSizes().first());

    // Build the layout
    main_layout->addWidget(p_list_view);
    side_layout->addWidget(add_button);
    side_layout->addWidget(reset_button);
    side_layout->addStretch();
    main_layout->addLayout(side_layout);

    // Set the size policy
    p_list_view->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Ignored);

    // Connect the buttons
    connect(
        add_button, &QPushButton::clicked,
        this, &DataImport::ImportFileWidget::addFiles
    );
    connect(
        reset_button, &QPushButton::clicked,
        this, &DataImport::ImportFileWidget::resetFiles
    );
    connect(
        p_list_view->selectionModel(), &QItemSelectionModel::currentChanged,
        [=](QModelIndex,QModelIndex){emit selectionChanged();}
    );
}

//! Get the current selection
int DataImport::ImportFileWidget::currentSelection() const
{
    return p_list_view->currentIndex().row();
}

//! This is the method called by the add file button
void DataImport::ImportFileWidget::addFiles()
{
    QStringList files = QFileDialog::getOpenFileNames(
                        this,
                        "Select one or more files to load",
                        "/home",
                        "Text (*.txt);; CSV (*.csv)");

    p_list_model->setStringList(p_list_model->stringList() + files);
    emit filesChanged(currentFiles());
}

//! This is the method called by the reset file button
void DataImport::ImportFileWidget::resetFiles()
{
    p_list_model->setStringList(QStringList());
    emit filesChanged(currentFiles());
}

//! Return the string list formated as a vector of strings
std::vector<std::string> DataImport::ImportFileWidget::currentFiles() const
{
    std::vector<std::string> string_vector;
    foreach( QString str, p_list_model->stringList()) {
        string_vector.push_back(str.toStdString());
    }
    return string_vector;
}
