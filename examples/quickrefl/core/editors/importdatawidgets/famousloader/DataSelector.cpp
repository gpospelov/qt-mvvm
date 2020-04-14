// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/ImportDataWidgets/CsvImportAssistant/DataSelector.cpp
//! @brief     Implements class DataSelector
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "DataSelector.h"
#include "CsvImportTable.h"
#include "ImportDataInfo.h"
//#include "StyleUtils.h"
#include "TableContextMenu.h"
//#include "mainwindow_constants.h"
#include <QFileDialog>
#include <QFormLayout>
#include <QGroupBox>
#include <QMenu>
#include <QMessageBox>
#include <QPushButton>
#include <QSettings>
#include <QTableWidget>
#include <QVBoxLayout>
#include <locale>
#include <sstream>

namespace
{
const QSize default_dialog_size(300, 400);
}

DataSelector::DataSelector(csv::DataArray csvArray, QWidget* parent)
    : QDialog(parent), m_data(csvArray), m_tableWidget(nullptr), m_separatorField(nullptr),
      m_firstDataRowSpinBox(nullptr), m_lastDataRowSpinBox(nullptr),
      m_coordinateUnitsComboBox(nullptr), m_importButton(nullptr), m_cancelButton(nullptr),
      m_errorLabel(nullptr)
{
    setWindowTitle("Data Importer");
    setMinimumSize(default_dialog_size);
    resize(600, 600);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    //StyleUtils::setResizable(this);
    setLayout(createLayout());

    if (!updateData())
        return;
}

bool DataSelector::updateData()
{
    size_t lastRow = m_data.size();

    if (lastRow < 1) {
        m_importButton->setDisabled(true);
        CsvImportAssistant::showErrorMessage("There is no data to show");
        return false;
    }

    m_tableWidget->setData(m_data);
    m_firstDataRowSpinBox->setMaximum(int(lastRow));
    m_lastDataRowSpinBox->setMaximum(int(lastRow));
    m_lastDataRowSpinBox->setValue(int(lastRow));

    return true;
}

void DataSelector::setColumnSlot(csv::ColumnType ct)
{
    setColumnAs(ct);
}

bool DataSelector::isInsideTable(const QPoint position)
{
    auto item = m_tableWidget->itemAt(position);

    if (!item)
        return false;

    auto row = item->row();
    auto col = item->column();
    if (row * col < 0)
        return false;

    return true;
}

void DataSelector::onColumnRightClick(const QPoint& position)
{
    if (!isInsideTable(position))
        return;

    auto globalPos = m_tableWidget->mapToGlobal(position);

    TableContextMenu contextMenu(this);
    connect(&contextMenu, &TableContextMenu::setFirstRow, this, [this]() { setFirstRow(); });
    connect(&contextMenu, &TableContextMenu::setLastRow, this, [this]() { setLastRow(); });
    connect(&contextMenu, &TableContextMenu::setColumnAs, this, &DataSelector::setColumnSlot);
    connect(&contextMenu, &TableContextMenu::discardRow, this, [this]() { discardRow(); });
    connect(&contextMenu, &TableContextMenu::resetTable, this, [this]() {
        resetSelection();
        updateSelection();
    });
    contextMenu.exec(globalPos);
}

void DataSelector::updateSelection()
{
    m_importButton->setEnabled(false);
    m_coordinateUnitsComboBox->setEnabled(false);
    m_tableWidget->setFirstRow(firstLine() - 1);
    m_tableWidget->setLastRow(lastLine() - 1);

    if (!m_tableWidget->dataLooksGood()) {
        m_errorLabel->setText(
            "\n\n"
            "Data selected for importing does not look good!\n\n"
            "Make sure that:\n"
            "    1. There are no repeated values in the coordinate column.\n"
            "    2. The coordinate values are ascendingly sorted.\n"
            "    3. Intensity and coordinate values are valid numbers.\n\n"
            "Use the context menu of the table to manually discard some rows;\n"
            "Alternatively, modify the file in an external editor.");
    } else {
        m_errorLabel->clear();
    }

    // Enable import button only if the user has selected its columns for 1d
    if (m_tableWidget->intensityColumn() > -1)
        if (m_tableWidget->dataLooksGood())
            m_importButton->setEnabled(true);

    // Enable Coordinate Selector
    if (m_tableWidget->coordinateColumn() > -1) {
        m_coordinateUnitsComboBox->setEnabled(true);
    } else {
        m_coordinateUnitsComboBox->clear();
        m_coordinateUnitsComboBox->addItem(csv::UnitsLabels[AxesUnits::NBINS]);
    }
}

void DataSelector::setColumnAs(int col, csv::ColumnType coordOrInt)
{
    m_tableWidget->setColumnAs(col, coordOrInt);
    populateUnitsComboBox();
    updateSelection();
}

void DataSelector::populateUnitsComboBox()
{
    QList<QString> available_units = m_tableWidget->availableCoordinateUnits();
    m_coordinateUnitsComboBox->clear();
    for (auto units: available_units)
        m_coordinateUnitsComboBox->addItem(units);
}

void DataSelector::setColumnAs(csv::ColumnType coordOrInt)
{
    auto col = m_tableWidget->selectedColumn();
    if (col < 0)
        return;

    setColumnAs(col, coordOrInt);
}

void DataSelector::setFirstRow()
{
    auto row = m_tableWidget->selectedRow();
    if (row < 0)
        return;

    auto currentMax = m_firstDataRowSpinBox->maximum();
    auto desiredVal = row + 1;
    auto newMax = std::max(currentMax, desiredVal);
    m_firstDataRowSpinBox->setMaximum(newMax);
    m_firstDataRowSpinBox->setValue(desiredVal);
    m_tableWidget->setFirstRow(size_t(row));
}

void DataSelector::setLastRow()
{
    auto row = m_tableWidget->selectedRow();
    if (row < 0)
        return;

    auto currentMin = m_firstDataRowSpinBox->minimum();
    auto desiredVal = row + 1;
    auto newMin = std::min(currentMin, desiredVal);
    m_lastDataRowSpinBox->setMinimum(newMin);
    m_lastDataRowSpinBox->setValue(desiredVal);
    m_tableWidget->setLastRow(size_t(row));
}

void DataSelector::discardRow()
{
    std::set<int> selection = m_tableWidget->selectedRows();
    m_tableWidget->discardRows(selection);
}

void DataSelector::resetSelection()
{
    m_firstDataRowSpinBox->setValue(0);
    m_lastDataRowSpinBox->setValue(int(maxLines()));
    m_tableWidget->resetSelection();
}

size_t DataSelector::firstLine() const
{
    return size_t(m_firstDataRowSpinBox->value());
}

size_t DataSelector::lastLine() const
{
    return size_t(m_lastDataRowSpinBox->value());
}

size_t DataSelector::maxLines() const
{
    return size_t(m_lastDataRowSpinBox->maximum());
}

AxesUnits DataSelector::units() const
{
    AxesUnits defaultUnits = AxesUnits::NBINS;
    for (int i = 0; i < csv::UnitsLabels.size(); i++)
        if (m_coordinateUnitsComboBox->currentText() == csv::UnitsLabels[i])
            return AxesUnits(i);
    return defaultUnits;
}

char DataSelector::separator() const
{
    char separator;
    QString tmpstr = m_separatorField->text();
    if (tmpstr.size() < 1) {
        separator = '\0';
    } else {
        separator = tmpstr.at(0).toLatin1();
    }
    return separator;
}

void DataSelector::onCancelButton()
{
    reject();
}

void DataSelector::onImportButton()
{
    //We shouldn't be here if the data is
    //not previously sanitised.
        accept();
}

QBoxLayout* DataSelector::createLayout()
{
    // table Widget
    m_tableWidget = new CsvImportTable();
    m_tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    m_tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    connect(m_tableWidget, &QTableWidget::customContextMenuRequested, this,
            &DataSelector::onColumnRightClick);
    connect(m_tableWidget, &CsvImportTable::dataSanityChanged, this,
            [this]() { updateSelection(); });

    // Error label
    m_errorLabel = new QLabel();
    m_errorLabel->setStyleSheet("QLabel { color : red; }");
    m_errorLabel->setText("");

    // Import button
    m_importButton = new QPushButton("Import");
    m_importButton->setDefault(false);
    m_importButton->setAutoDefault(false);
    connect(m_importButton, &QPushButton::clicked, this, &DataSelector::onImportButton);

    // Reject button
    m_cancelButton = new QPushButton("Cancel");
    m_cancelButton->setDefault(false);
    m_cancelButton->setAutoDefault(false);
    connect(m_cancelButton, &QPushButton::clicked, this, [this]() { reject(); });

    // Separator field -- This needs to communicate with importAssistant
    m_separatorField = new QLineEdit(QString(""));
    m_separatorField->setMaxLength(1);
    m_separatorField->setMaximumWidth(70);
    m_separatorField->setMinimumWidth(70);
    connect(m_separatorField, &QLineEdit::editingFinished, this,
            [this]() { emit separatorChanged(separator()); });

    // First Row SpinBox
    m_firstDataRowSpinBox = new QSpinBox();
    m_firstDataRowSpinBox->setMinimum(1);
    m_firstDataRowSpinBox->setMaximum(1);
    m_firstDataRowSpinBox->setValue(1);
    m_firstDataRowSpinBox->setMaximumWidth(70);
    m_firstDataRowSpinBox->setMinimumWidth(70);
    connect(m_firstDataRowSpinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            this, [this]() {
                m_lastDataRowSpinBox->setMinimum(m_firstDataRowSpinBox->value());
                updateSelection();
            });

    // Last Row SpinBox
    m_lastDataRowSpinBox = new QSpinBox();
    m_lastDataRowSpinBox->setMinimum(1);
    m_lastDataRowSpinBox->setMaximum(1);
    m_lastDataRowSpinBox->setValue(1);
    m_lastDataRowSpinBox->setMaximumWidth(70);
    m_lastDataRowSpinBox->setMinimumWidth(70);
    connect(m_lastDataRowSpinBox, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            this, [this]() {
                m_firstDataRowSpinBox->setMaximum(m_lastDataRowSpinBox->value());
                updateSelection();
            });

    // Coordinate units selector:
    m_coordinateUnitsComboBox = new QComboBox();
    m_coordinateUnitsComboBox->setMaximumWidth(70);
    m_coordinateUnitsComboBox->setMinimumWidth(70);
    m_coordinateUnitsComboBox->addItem(csv::UnitsLabels[AxesUnits::NBINS]);

    auto layout = new QVBoxLayout;
    layout->setContentsMargins(0, 0, 0, 0);

    // Separator:
    auto separatorFieldLayout = new QFormLayout;
    separatorFieldLayout->addRow(tr("&Separator: "), m_separatorField);

    // Place table Widget:
    auto tableLayout = new QVBoxLayout;
    tableLayout->setMargin(10);
    tableLayout->addWidget(new QLabel("Right click on the table to select what will be imported"));
    tableLayout->addWidget(m_tableWidget);
    tableLayout->addLayout(separatorFieldLayout);
    tableLayout->addLayout(separatorFieldLayout);
    tableLayout->addWidget(m_errorLabel);

    // First and last data rows:
    auto rowControlsLayout = new QFormLayout;
    auto* rowControlsGroupBox = new QGroupBox;
    rowControlsLayout->addRow(tr("&From row: "), m_firstDataRowSpinBox);
    rowControlsLayout->addRow(tr("&To row: "), m_lastDataRowSpinBox);
    rowControlsLayout->setMargin(10);
    rowControlsGroupBox->setTitle(tr("&Data rows:"));
    rowControlsGroupBox->setLayout(rowControlsLayout);

    // Unit selector
    auto unitSelectionLayout = new QFormLayout;
    unitSelectionLayout->addRow(tr("&Coordinate units: "), m_coordinateUnitsComboBox);
    unitSelectionLayout->setMargin(10);

    // buttons layout
    auto buttonsLayout = new QHBoxLayout;
    buttonsLayout->addWidget(m_importButton);
    buttonsLayout->addWidget(m_cancelButton);

    // place controls and import/reject buttons
    auto controlsAndButtonsGrid = new QGridLayout;
    controlsAndButtonsGrid->setMargin(10);
    controlsAndButtonsGrid->addItem(new QSpacerItem(10000, 1), 1, 1, 2, 1);
    controlsAndButtonsGrid->addWidget(rowControlsGroupBox, 1, 2, 1, 1, Qt::AlignRight);
    controlsAndButtonsGrid->addLayout(unitSelectionLayout, 2, 2, Qt::AlignRight);
    controlsAndButtonsGrid->addLayout(buttonsLayout, 3, 2, 1, 1, Qt::AlignRight);

    // build all the layout
    layout->addLayout(separatorFieldLayout);
    layout->addLayout(tableLayout);
    layout->addLayout(controlsAndButtonsGrid);

    return layout;
}
