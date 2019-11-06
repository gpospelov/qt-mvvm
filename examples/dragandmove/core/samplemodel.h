// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef SAMPLEMODEL_H
#define SAMPLEMODEL_H

#include <mvvm/model/sessionmodel.h>

namespace ModelView {
class SessionItem;
}

//! Main application model.

class SampleModel : public ModelView::SessionModel
{
public:
    SampleModel();

    void append_random_item(ModelView::SessionItem* container);

private:
    void init_model_content();
};

#endif
