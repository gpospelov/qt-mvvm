// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_JSONVARIANTINTERFACE_H
#define MVVM_JSONVARIANTINTERFACE_H

#include "mvvm_export.h"

class QJsonObject;
class QVariant;

namespace ModelView
{

//! Base class for all supported converters of QVariant to/from json object

class CORE_EXPORT JsonVariantInterface
{
public:
    virtual ~JsonVariantInterface() = default;

    virtual QJsonObject get_json(const QVariant&) = 0;

    virtual QVariant get_variant(const QJsonObject&) = 0;
};

} // namespace ModelView

#endif // MVVM_JSONVARIANTINTERFACE_H
