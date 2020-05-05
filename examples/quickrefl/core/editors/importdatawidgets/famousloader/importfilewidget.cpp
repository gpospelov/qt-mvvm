// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "importfilewidget.h"

#include <QFileDialog>
#include <QHBoxLayout>
#include <QIcon>
#include <QItemSelectionModel>
#include <QListView>
#include <QSettings>
#include <QSizePolicy>
#include <QStringListModel>
#include <QStyle>
#include <QToolButton>

#include <iostream>

namespace DataImportGui
{

//! This is the constructor
ImportFileWidget::ImportFileWidget(QWidget* parent) : QWidget(parent)
{
    createWidgets();
}

//! Create all the widget elements
void ImportFileWidget::createWidgets()
{
    auto main_layout = new QHBoxLayout(this);
    auto side_layout = new QVBoxLayout();

    // Set up the list
    p_list_view = new QListView(this);
    p_list_model = new QStringListModel();
    p_list_view->setModel(p_list_model);
    p_list_view->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // Set up the buttons
    auto add_button = new QToolButton(this);
    QIcon add_ic(style()->standardIcon(QStyle::SP_FileDialogNewFolder));
    add_button->setIcon(add_ic);

    auto reset_button = new QToolButton(this);
    QIcon reset_ic(style()->standardIcon(QStyle::SP_DialogResetButton));
    reset_button->setIcon(reset_ic);

    // Build the layout
    main_layout->addWidget(p_list_view);
    side_layout->addWidget(add_button);
    side_layout->addWidget(reset_button);
    side_layout->addStretch();
    main_layout->addLayout(side_layout);

    // Set the size policy
    p_list_view->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Ignored);

    // Connect the buttons
    connect(add_button, &QToolButton::clicked, this, &ImportFileWidget::addFiles);
    connect(reset_button, &QToolButton::clicked, this, &ImportFileWidget::resetFiles);
    connect(p_list_view->selectionModel(), &QItemSelectionModel::currentChanged,
            [=](QModelIndex, QModelIndex) { emit selectionChanged(); });
}

//! Get the current selection
int ImportFileWidget::currentSelection() const
{
    return p_list_view->currentIndex().row();
}

//! Read the settings froma QSetting structure
void ImportFileWidget::readSettings(QSettings& settings)
{
    settings.beginGroup("Files");
    m_default_path = settings.value("last_path", ".").toString();
    settings.endGroup();
}

//! Write the settings from a QSetting structure
void ImportFileWidget::writeSettings(QSettings& settings)
{
    settings.beginGroup("Files");
    settings.setValue("last_path", m_default_path);
    settings.endGroup();
}

//! This is the method called by the add file button
void ImportFileWidget::addFiles()
{
    QStringList files = QFileDialog::getOpenFileNames(this, "Select one or more files to load",
                                                      m_default_path, "Text (*.txt);; CSV (*.csv)");
    if (files.count() > 0)
        m_default_path = QFileInfo(files[0]).absoluteDir().absolutePath();

    // Save the current string
    QString current_input;
    if (p_list_model->rowCount() != 0
        && p_list_view->selectionModel()->selectedIndexes().count() != 0) {
        current_input = p_list_model->data(p_list_view->selectionModel()->selectedIndexes()[0])
                            .value<QString>();
    }

    // Refresh
    files = p_list_model->stringList() + files;
    files.removeDuplicates();
    p_list_model->setStringList(files);
    emit filesChanged(currentFiles());

    // Set back the initial string is present
    if (p_list_model->rowCount() != 0) {
        auto to_select = p_list_model->index(0, 0);
        for (int i = 0; i < p_list_model->rowCount(); ++i) {
            if (current_input.toStdString()
                == p_list_model->data(p_list_model->index(i, 0)).value<QString>().toStdString()) {
                to_select = p_list_model->index(i, 0);
                break;
            }
        }
        p_list_view->setCurrentIndex(to_select);
    }
}

//! This is the method called by the reset file button
void ImportFileWidget::resetFiles()
{
    p_list_model->setStringList(QStringList());
    emit filesChanged(currentFiles());
}

//! Return the string list formated as a vector of strings
std::vector<std::string> ImportFileWidget::currentFiles() const
{
    std::vector<std::string> string_vector;
    foreach (QString str, p_list_model->stringList()) {
        string_vector.push_back(str.toStdString());
    }
    return string_vector;
}

} // End of namespace DataImportGui
