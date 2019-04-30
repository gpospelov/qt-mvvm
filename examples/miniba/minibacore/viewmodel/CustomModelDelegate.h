// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef CUSTOMMODELDELEGATE_H
#define CUSTOMMODELDELEGATE_H

#include "viewmodeldelegate.h"

class ApplicationModels;

class CORE_EXPORT CustomModelDelegate : public ModelView::ViewModelDelegate
{
public:
    explicit CustomModelDelegate(ApplicationModels* models, QObject* parent = nullptr);

};

#endif
