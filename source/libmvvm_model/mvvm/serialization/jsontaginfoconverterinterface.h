// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_SERIALIZATION_JSONTAGINFOCONVERTERINTERFACE_H
#define MVVM_SERIALIZATION_JSONTAGINFOCONVERTERINTERFACE_H

#include "mvvm/model_export.h"

class QJsonObject;

namespace ModelView {

class TagInfo;

//! Base class for all converters of TagInfo to/from json object

class MVVM_MODEL_EXPORT JsonTagInfoConverterInterface {
public:
    virtual ~JsonTagInfoConverterInterface() = default;

    virtual QJsonObject to_json(const TagInfo&) = 0;

    virtual TagInfo from_json(const QJsonObject&) = 0;
};

} // namespace ModelView

#endif // MVVM_SERIALIZATION_JSONTAGINFOCONVERTERINTERFACE_H
