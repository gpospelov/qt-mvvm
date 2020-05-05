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

#include "importlogic.h"
#include <QDialog>
#include <QGroupBox>
#include <QTabWidget>
#include <QTableView>

namespace DataImportGui
{

class ImportFileWidget;
class ImportFilterWidget;
class ImportTextView;
class ImportTableView;

//! This is the main dialog for the data loader
class DataLoaderDialog : public QDialog
{
    Q_OBJECT

public:
    DataLoaderDialog(QWidget* parent = nullptr);
    ~DataLoaderDialog() = default;

private:
    void setUpFileListSpace(QGroupBox* conainer);
    void setUpParameterSpace(QGroupBox* conainer);
    void setUpSelectionSpace(QTabWidget* tab_widget);

    void readSettings();
    void writeSettings();

private slots:
    void selectedFileChanged();

protected:
    void accept() override;

private:
    ImportFileWidget* p_import_file_list{nullptr};
    ImportFilterWidget* p_parameter_dialog{nullptr};
    ImportTextView* p_text_view{nullptr};
    ImportTableView* p_table_view{nullptr};
    std::unique_ptr<DataImportLogic::ImportLogic> p_data_import_logic;
    QTabWidget* p_selection_space{nullptr};
};

} // End of namespace DataImportGui

#endif // IMPORTDIALOG_H