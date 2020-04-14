// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Views/ImportDataWidgets/CsvImportAssistant/TableContextMenu.cpp
//! @brief     Implements class TableContextMenu
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#include "TableContextMenu.h"

TableContextMenu::TableContextMenu(QWidget* parent)
    : QMenu(parent), m_coordSubMenu(this),
      m_selectFromThisRowOn(new QAction("Set As First Data Row", this)),
      m_selectUntilThisRow(new QAction("Set As Last Data Row", this)),
      m_resetAction(new QAction("Reset", this)),
      m_setAsTheta(new QAction(csv::HeaderLabels[csv::_theta_], this)),
      m_setAsQ(new QAction(csv::HeaderLabels[csv::_q_], this)),
      m_setAsIntensity(
          new QAction("Set As " + csv::HeaderLabels[csv::_intensity_] + " Column", this)),
      m_discardRow(new QAction("Toogle Discard Selected Rows", this))
{
    this->addAction(m_selectFromThisRowOn);
    this->addAction(m_selectUntilThisRow);
    this->addAction(m_discardRow);

    this->addSeparator();
    this->addAction(m_setAsIntensity);

    m_coordSubMenu = this->addMenu("Set As Coordinate Column...");
    m_coordSubMenu->addAction(m_setAsTheta);
    m_coordSubMenu->addAction(m_setAsQ);

    this->addSeparator();
    this->addAction(m_resetAction);

    connect(m_selectFromThisRowOn, &QAction::triggered, this, [this]() { emit setFirstRow(); });
    connect(m_selectUntilThisRow, &QAction::triggered, this, [this]() { emit setLastRow(); });
    connect(m_setAsIntensity, &QAction::triggered, this,
            [this]() { emit setColumnAs(csv::_intensity_); });
    connect(m_setAsTheta, &QAction::triggered, this, [this]() { emit setColumnAs(csv::_theta_); });
    connect(m_setAsQ, &QAction::triggered, this, [this]() { emit setColumnAs(csv::_q_); });
    connect(m_resetAction, &QAction::triggered, this, [this]() { emit resetTable(); });
    connect(m_discardRow, &QAction::triggered,this,[this](){emit discardRow();});
}
