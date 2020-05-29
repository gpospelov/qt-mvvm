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
#include <QCheckBox>
#include <QDialog>
#include <QGroupBox>
#include <QTabWidget>
#include <QSettings>
#include <memory>

namespace DataImportLogic
{
class ImportOutput;
}

namespace DataImportGui
{

class ImportFileWidget;
class ImportFilterWidget;
class ImportTextView;
class ImportTableView;
class ImportOutput;

//! This is the main dialog for the data loader
class DataLoaderDialog : public QDialog
{
    Q_OBJECT

public:
    DataLoaderDialog(QWidget* parent = nullptr);
    ~DataLoaderDialog() = default;
    DataImportLogic::ImportOutput result();

private:
    void setUpFileListSpace(QGroupBox* conainer);
    void setUpParameterSpace(QGroupBox* conainer);
    void setUpSelectionSpace(QTabWidget* tab_widget);

    void readSettings();
    void writeSettings();

    void readImportLogicSettings(QSettings &settings);
    void writeImportLogicSettings(QSettings &settings);

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
    QCheckBox* p_merge_check{nullptr};
};

} // End of namespace DataImportGui

#endif // IMPORTDIALOG_H