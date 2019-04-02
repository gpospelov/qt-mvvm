// ************************************************************************** //
//
//  BornAgain: simulate and fit scattering at grazing incidence
//
//! @file      GUI/coregui/Models/ComboProperty.h
//! @brief     Defines class ComboProperty
//!
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @copyright Forschungszentrum Jülich GmbH 2018
//! @authors   Scientific Computing Group at MLZ (see CITATION, AUTHORS)
//
// ************************************************************************** //

#ifndef COMBOPROPERTY_H
#define COMBOPROPERTY_H

#include "global.h"
#include <QString>
#include <QStringList>
#include <QVariant>
#include <vector>

//! Custom property to define list of string values with multiple selections.
//! Intended for QVariant.

class CORE_EXPORT ComboProperty
{
public:
    ComboProperty();

    static ComboProperty fromList(const QStringList& values,
                                  const QString& current_value = QString());

    QString getValue() const;
    void setValue(const QString& name);

    QStringList getValues() const;
    void setValues(const QStringList& values);

    QStringList toolTips() const;
    void setToolTips(const QStringList& tooltips);

    int currentIndex() const;
    void setCurrentIndex(int index);

    ComboProperty& operator<<(const QString& str);
    ComboProperty& operator<<(const QStringList& str);
    bool operator==(const ComboProperty& other) const;
    bool operator!=(const ComboProperty& other) const;
    bool operator<(const ComboProperty& other) const;

    QString stringOfValues() const;
    void setStringOfValues(const QString& values);

    QVariant variant() const;

    std::vector<int> selectedIndices() const;
    QStringList selectedValues() const;

    void setSelected(int index, bool value = true);
    void setSelected(const QString& name, bool value = true);

    QString stringOfSelections() const;
    void setStringOfSelections(const QString& values);

    QString label() const;

private:
    ComboProperty(QStringList values);

    QStringList m_values;
    QStringList m_tooltips;
    std::vector<int> m_selected_indices;
};

Q_DECLARE_METATYPE(ComboProperty)

#endif // COMBOPROPERTY_H
