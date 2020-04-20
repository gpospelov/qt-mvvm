// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "importparameterwidget.h"

#include <mvvm/editors/coloreditor.h>
#include <mvvm/editors/styleutils.h>

#include <QCheckBox>
#include <QSpinBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSizePolicy>

//! This is the constructor
DataImport::ImportParameterWidget::ImportParameterWidget(QWidget* parent): QWidget(parent)
{   
    createWidgets();
    setLayout();
    setInitialState();
    connectAll();
    checkValues(0);
}

//! Create all the widget elements
void DataImport::ImportParameterWidget::createWidgets()
{
    m_checkboxes.push_back(new QCheckBox("File-info at line:", this));
    m_checkboxes.push_back(new QCheckBox("Meta-data at line:", this));
    m_checkboxes.push_back(new QCheckBox("Header-data at line:", this));
    m_checkboxes.push_back(new QCheckBox("Column-data at line:", this));
    m_checkboxes.push_back(new QCheckBox("Footer-data at line:", this));

    for (auto checkbox: m_checkboxes){
        m_spinboxes.push_back(new QSpinBox(this));
        m_color_editors.push_back(new ModelView::ColorEditor(this));
    }
}

//! Set all the layouts and positioning of the items
void DataImport::ImportParameterWidget::setLayout()
{
    auto widget_layout = new QVBoxLayout(this);
    for (int i = 0; i < m_checkboxes.size(); ++i){
        auto h_layout = new QHBoxLayout();
        h_layout->addWidget(m_checkboxes.at(i));
        h_layout->addWidget(m_spinboxes.at(i));
        h_layout->addWidget(m_color_editors.at(i));
        widget_layout->addLayout(h_layout);
    }
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

//! Set the connection logic between items
void DataImport::ImportParameterWidget::setInitialState()
{
    std::vector<QColor> init_color {QColor("green"), QColor("blue"), QColor("red"), QColor("violet"), QColor("grey")};
    for (int i = 0; i < m_checkboxes.size(); ++i){
        m_checkboxes.at(i)->setStyleSheet( "QCheckBox:checked{color: black;} QCheckBox:unchecked{color: grey;}");
        m_checkboxes.at(i)->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        m_spinboxes.at(i)->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        m_spinboxes.at(i)->setEnabled(false);
        m_color_editors.at(i)->setEnabled(false);
        m_color_editors.at(i)->layout()->setContentsMargins(4, 4, 4, 4);
        m_color_editors.at(i)->layout()->takeAt(m_color_editors.at(i)->layout()->count()-1);
        m_color_editors.at(i)->setFixedSize(ModelView::Style::DefaultPixmapSize(),ModelView::Style::DefaultPixmapSize());
        m_color_editors.at(i)->setData(init_color.at(i));
    }
}

//! Set the connection logic between items
void DataImport::ImportParameterWidget::connectAll()
{
    for (int i = 0; i < m_checkboxes.size(); ++i){
        connect(
            m_checkboxes.at(i), &QCheckBox::stateChanged,
            [=](int state){
                m_spinboxes.at(i)->setEnabled(state);
                m_color_editors.at(i)->setEnabled(state);
                int line = 0;
                (i > 0) ? (line = m_spinboxes.at(i-1)->value()) : (line = 0);
                if (!state) m_spinboxes.at(i)->setValue(line);
                checkValues(i);}
            );
        connect(
            m_spinboxes.at(i), static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            [=](int value){checkValues(i);});
    }
}

//! This method will check that all the entered values are in order
void DataImport::ImportParameterWidget::checkValues(int start)
{   
    int i;
    for ( (start > 0) ? (i = start) : (i = 1); i < m_checkboxes.size(); ++i){

        // Find the last value that was enabled
        int last_enabled_value = -1;
        for ( int j = i-1 ; j >= 0; --j){
            if (m_spinboxes.at(j)->isEnabled()) {
                last_enabled_value = m_spinboxes.at(j)->value();
                break;
            }
        }

        // The logic
        if (m_spinboxes.at(i)->isEnabled()){
            if (m_spinboxes.at(i)->value() <= last_enabled_value){
                m_spinboxes.at(i)->setValue(last_enabled_value+1);
            }
        }else{
            m_spinboxes.at(i)->setValue(last_enabled_value);
        }
    }

    emit valuesChanged();

}

//! Getter for the presence of individual string parts
std::vector<bool> DataImport::ImportParameterWidget::stringPresent() const
{
    std::vector<bool> presence;
    for (auto const &checkbox : m_checkboxes){
        presence.push_back(checkbox->isChecked());
    }
    return presence;
}

//! Getter for the location of individual string parts
std::vector<int> DataImport::ImportParameterWidget::stringLocation() const
{
    std::vector<int> lines;
    for (auto const &spinbox : m_spinboxes){
        lines.push_back(spinbox->value());
    }
    return lines;
}

//! Getter for the color of individual string parts
std::vector<QColor> DataImport::ImportParameterWidget::stringColor() const
{
    std::vector<QColor> colors;
    for (auto const &colorbox : m_color_editors){
        colors.push_back(colorbox->data().value<QColor>());
    }
    return colors;
}
