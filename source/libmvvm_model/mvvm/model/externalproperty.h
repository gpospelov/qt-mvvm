// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#ifndef MVVM_MODEL_EXTERNALPROPERTY_H
#define MVVM_MODEL_EXTERNALPROPERTY_H

#include "mvvm/core/variant.h"
#include "mvvm/model_export.h"
#include <QColor>
#include <string>

namespace ModelView {

//! Property to carry text, color and identifier.
//! Can be used to link items with each other.

class MVVM_MODEL_EXPORT ExternalProperty {
public:
    ExternalProperty();
    ExternalProperty(std::string text, QColor color, std::string id = {});

    static ExternalProperty undefined();

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

#endif // MVVM_MODEL_EXTERNALPROPERTY_H
