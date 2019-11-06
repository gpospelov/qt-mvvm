// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef MVVM_EXTERNALPROPERTY_H
#define MVVM_EXTERNALPROPERTY_H

#include <mvvm/core/export.h>
#include <QColor>
#include <QVariant>
#include <string>

namespace ModelView
{

//! Property for QVariant to carry text, color and identifier. Can be used to link items with each
//! other.

class CORE_EXPORT ExternalProperty
{
public:
    ExternalProperty();
    ExternalProperty(std::string text, QColor color, std::string id = {});

    std::string text() const;

    QColor color() const;

    std::string identifier() const;

    bool isValid() const;

    bool operator==(const ExternalProperty& other) const;
    bool operator!=(const ExternalProperty& other) const;
    bool operator<(const ExternalProperty& other) const;

private:
    std::string m_text;
    QColor m_color;
    std::string m_identifier;
};

} // namespace ModelView

Q_DECLARE_METATYPE(ModelView::ExternalProperty)

#endif // MVVM_EXTERNALPROPERTY_H
