// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "testwidget1.h"
#include "ApplicationModels.h"

TestWidget1::TestWidget1(ApplicationModels* models, QWidget* parent)
    : QWidget(parent), m_models(models)
{

}

