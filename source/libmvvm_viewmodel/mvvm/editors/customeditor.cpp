// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/editors/customeditor.h"

using namespace ModelView;

CustomEditor::CustomEditor(QWidget* parent) : QWidget(parent) {}

QVariant CustomEditor::data() const
{
    return m_data;
}

//! Returns true if editor should remains alive after editing finished.

bool CustomEditor::is_persistent() const
{
    return false;
}

//! Sets the data from model to editor.

void CustomEditor::setData(const QVariant& data)
{
    m_data = data;
    update_components();
}

//! Saves the data as given by editor's internal components and notifies the model.

void CustomEditor::setDataIntern(const QVariant& data)
{
    m_data = data;
    dataChanged(m_data);
}
