// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef APPLICATIONMODELS_H
#define APPLICATIONMODELS_H

#include "global.h"
#include <memory>

namespace ModelView {
class SessionModel;
}

class CORE_EXPORT ApplicationModels
{
public:
    ApplicationModels();
    ~ApplicationModels();

    ModelView::SessionModel* sampleModel();
    ModelView::SessionModel* materialModel();

private:
    class ApplicationModelsPrivate;
    std::unique_ptr<ApplicationModelsPrivate> p_impl;
};

#endif //  APPLICATIONMODELS_H

