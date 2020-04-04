// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/ImportDataWidgets/CsvImportAssistant/DataSelector.h
//! @brief     Defines class DataSelector
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef DATASELECTOR_H
#define DATASELECTOR_H

#include "CsvDataColumn.h"
#include "CsvImportAssistant.h"
#include "CsvImportTable.h"
#include "CsvNamespace.h"
#include "ImportDataInfo.h"
#include <QAction>
#include <QComboBox>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QTableWidget>
#include <memory>

class QBoxLayout;

//! Dialog to hold DataSelector.
class DataSelector : public QDialog
{
    Q_OBJECT
public:
    DataSelector(csv::DataArray csvArray, QWidget* parent = nullptr);
    size_t firstLine() const;
    size_t lastLine() const;
    int intensityColumn() const { return m_tableWidget->intensityColumn(); }
    int coordinateColumn() const { return m_tableWidget->coordinateColumn(); }
    double intensityMultiplier() const { return m_tableWidget->intensityMultiplier(); }
    double coordinateMultiplier() const { return m_tableWidget->coordinateMultiplier(); }
    std::set<int> rowsToDiscard() const { return m_tableWidget->rowsToDiscard(); }
    AxesUnits units() const;
    void setDataArray(csv::DataArray csvArray)
    {
        m_data = std::move(csvArray);
        updateData();
        resetSelection();
    }
    void setSeparator(char newSeparator)
    {
        m_separatorField->setText(QString(QChar(newSeparator)));
    }

public slots:
    void onImportButton();
    void onCancelButton();
    void onColumnRightClick(const QPoint& position);
    void setColumnSlot(csv::ColumnType ct);

signals:
    void separatorChanged(char newSeparator);

private:
    size_t maxLines() const;
    char separator() const;
    void setColumnAs(csv::ColumnType coordOrInt);
    void setColumnAs(int col, csv::ColumnType coordOrInt);
    void setFirstRow();
    void setLastRow();
    void discardRow();
    void resetSelection();
    void updateSelection();
    bool updateData();
    QBoxLayout* createLayout();
    void populateUnitsComboBox();
    bool isInsideTable(QPoint point);
    bool dataLooksGood();

    csv::DataArray m_data;
    CsvImportTable* m_tableWidget;
    QLineEdit* m_separatorField;
    QSpinBox* m_firstDataRowSpinBox;
    QSpinBox* m_lastDataRowSpinBox;
    QComboBox* m_coordinateUnitsComboBox;
    QPushButton* m_importButton;
    QPushButton* m_cancelButton;
    QLabel* m_errorLabel;
};
#endif // DATASELECTOR_H
