// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "coloreditor.h"
#include <QHBoxLayout>

using namespace ModelView;

ColorEditor::ColorEditor(QWidget* parent)
    : CustomEditor(parent)

{
    setAutoFillBackground(true);
    auto layout = new QHBoxLayout;
    layout->setContentsMargins(4, 0, 0, 0);
    setLayout(layout);
}

void ColorEditor::update_components()
{

}
