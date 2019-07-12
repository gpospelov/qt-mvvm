// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#include "dragviewmodel.h"

using namespace ModelView;

DragViewModel::DragViewModel(SessionModel* model, QObject* parent)
    : PropertyTableViewModel(model, parent)
{

}
