// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef SCENEUTILS_H
#define SCENEUTILS_H

//! @file sceneutils.h
//! Collection of utility functions for graphics scene.

class QGradient;
class QColor;
class QRectF;

namespace NodeEditor {

//! Returns vertical gradient using provided base color and rectangle.
QGradient CreateViewGradient(const QColor& color, const QRectF& rect);

} // namespace NodeEditor

#endif
