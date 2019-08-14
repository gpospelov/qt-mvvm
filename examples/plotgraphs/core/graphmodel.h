// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef GRAPHMODEL_H
#define GRAPHMODEL_H

#include "sessionmodel.h"

/*!
@class GraphModel
@brief Main application model.
*/

class GraphModel : public ModelView::SessionModel
{
public:
    GraphModel();
};

#endif // GRAPHMODEL_H
