// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_CELLDECORATIONINTERFACE_H
#define MVVM_CELLDECORATIONINTERFACE_H

#include <mvvm/core/export.h>
#include <string>

class QModelIndex;

namespace ModelView
{

//! Interface class to generate cell decorations (i.e. text) in Qt trees and tables.

class CORE_EXPORT CellDecorationInterface
{
public:
    virtual ~CellDecorationInterface() = default;

    virtual bool hasCustomDecoration(const QModelIndex& index) const = 0;
    virtual std::string cellText(const QModelIndex& index) const = 0;
};

} // namespace ModelView

#endif // MVVM_CELLDECORATIONINTERFACE_H
