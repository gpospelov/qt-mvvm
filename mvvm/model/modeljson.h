// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //


#ifndef MODELJSON_H
#define MODELJSON_H

#include <string>
class SessionModel;
class QJsonObject;

namespace ModelJson
{

const std::string modelKey = "model";


//! Writes content of model into json object.
void write(const SessionModel& model, QJsonObject& json);

}

#endif
