// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_COLORSCALEPLOTCONTROLLER_H
#define MVVM_COLORSCALEPLOTCONTROLLER_H

#include "itemcontroller.h"

class QCPColorScale;

namespace ModelView
{

class ViewportAxisItem;

/*!
@class ColorScalePlotController
@brief Establishes communication between QCPColorScale and ViewportAxisItem.
*/

class CORE_EXPORT ColorScalePlotController : public ItemController<ViewportAxisItem>
{
public:
    explicit ColorScalePlotController(QCPColorScale* color_scale);
    ~ColorScalePlotController() override;

protected:
    void subscribe() override;

public:
    struct ColorScalePlotControllerPrivate;
    std::unique_ptr<ColorScalePlotControllerPrivate> p_impl;
};

} // namespace ModelView

#endif // MVVM_COLORSCALEPLOTCONTROLLER_H
