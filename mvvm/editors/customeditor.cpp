// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "customeditor.h"
#include <QDebug>

using namespace ModelView;

CustomEditor::CustomEditor(QWidget* parent)
    : QWidget(parent)
{

}

QVariant CustomEditor::data() const
{
    qDebug() << "CustomEditor::data()";
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
    qDebug() << "CustomEditor::setData()";
    m_data = data;
    update_components();
}

void CustomEditor::setDataIntern(const QVariant& data)
{
    m_data = data;
    dataChanged();
}
