// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef JSONITEMTAG_H
#define JSONITEMTAG_H

#include "jsonconverterinterfaces.h"
#include <QString>
#include <memory>
#include <vector>

class QJsonObject;

namespace ModelView {

//! Default converter between SessionItemTag and json object.

class CORE_EXPORT JsonItemContainer : public JsonItemContainerInterface
{
public:
    static const QString tagInfoKey;
    static const QString itemsKey;

    JsonItemContainer();
    ~JsonItemContainer() override;

    QJsonObject to_json(const SessionItemContainer& itemTag) override;

    std::unique_ptr<SessionItemContainer> from_json(const QJsonObject&) override;

    bool isSessionItemContainer(const QJsonObject& object);

private:
    std::unique_ptr<JsonTagInfoInterface> m_taginfo_converter;
};

}  // namespace ModelView

#endif // JSONITEMTAG_H
