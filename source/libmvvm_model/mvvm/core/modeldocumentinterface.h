// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_CORE_MODELDOCUMENTINTERFACE_H
#define MVVM_CORE_MODELDOCUMENTINTERFACE_H

#include <mvvm/core/export.h>
#include <string>

namespace ModelView
{

/*!
@class ModelDocumentInterface
@brief Base class to save and restore session models on and from disk.

Single ModelDocument corresponds to a single file on disk. It can contain arbitrary number
of models.
*/

class CORE_EXPORT ModelDocumentInterface
{
public:
    virtual ~ModelDocumentInterface() = default;

    virtual void save(const std::string& file_name) const = 0;
    virtual void load(const std::string& file_name) = 0;
};

} // namespace ModelView

#endif // MVVM_CORE_MODELDOCUMENTINTERFACE_H
