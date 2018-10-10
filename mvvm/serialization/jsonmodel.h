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
#include <functional>
class SessionModel;
class QJsonObject;
class SessionItem;

class JsonModel
{
public:
    static const std::string modelKey;
    static const std::string itemsKey;

    //! Writes content of model into json object.
    void write(const SessionModel& model, QJsonObject& json);

    void write(const SessionItem* item, QJsonObject& json);

};

#endif
