// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef NODEEDITORCORE_SCENEUTILS_H
#define NODEEDITORCORE_SCENEUTILS_H

//! @file sceneutils.h
//! Collection of utility functions for graphics scene.

class QGradient;
class QColor;
class QRectF;

namespace NodeEditor {

//! Returns vertical gradient to paint connectable view with given color and bounding rectangle.
QGradient ConnectableViewGradient(const QColor& color, const QRectF& rect);

//! Returns characteristic rectangle to represent connectable view on a graphics scene.
QRectF ConnectableViewRectangle();

} // namespace NodeEditor

#endif // NODEEDITORCORE_SCENEUTILS_H
