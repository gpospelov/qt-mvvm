// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef TOYMODELS_H
#define TOYMODELS_H

#include "sessionmodel.h"

//! Collection of toy items and models for testing purposes.

namespace ToyItems
{

class SampleModel : public ModelView::SessionModel
{
public:
    SampleModel();

};

} // ToyItems

#endif // TOYMODELS_H

