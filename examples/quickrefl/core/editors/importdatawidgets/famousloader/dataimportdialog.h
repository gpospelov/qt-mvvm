// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //


#ifndef IMPORTDIALOG_H
#define IMPORTDIALOG_H

#include <QDialog>
#include <QGroupBox>
#include <QTabWidget>
#include <QTableView>

namespace DataImport
{

class ImportFileWidget;
class ImportParameterWidget;
class ImportTextView;
// class ImportTableView;

//! This is the main dialog for the data loader
class DataLoaderDialog : public QDialog
{
public:
    DataLoaderDialog(QWidget* parent = nullptr);
    ~DataLoaderDialog() = default;

private:
    void setUpFileListSpace(QGroupBox* conainer);
    void setUpParameterSpace(QGroupBox* conainer);
    void setUpSelectionSpace(QTabWidget* tab_widget);

private:
    ImportFileWidget* p_import_file_list{nullptr};
    ImportParameterWidget* p_parameter_dialog{nullptr};
    ImportTextView* p_text_view{nullptr};
    QTableView* p_table_view{nullptr};
};
}

#endif // IMPORTDIALOG_H