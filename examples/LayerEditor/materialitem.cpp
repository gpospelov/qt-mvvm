#include "materialitem.h"
#include <QVariant>

QString MaterialItem::propertyName(int column, DATA_TYPE type)
{
    if (column >= size)
        return QString();
    switch (column) {
    case 0: return "Color";
    case 1: return "Name";
    case 2: return type == SLD ? "Re(SLD)" : "delta";
    case 3: return type == SLD ? "Im(SLD)" : "beta";
    case 4: return "Data type";
    }
}

MaterialItem::MaterialItem(MaterialItem::DATA_TYPE type)
    : m_color("blue")
    , m_name("default")
    , m_real(0.0)
    , m_imag(0.0)
    , m_type(type)
{}

QVariant MaterialItem::property(int column) const
{
    if (column >= size)
        return QVariant();
    switch (column) {
    case 0: return m_color;
    case 1: return QString::fromStdString(m_name);
    case 2: return m_real;
    case 3: return m_imag;
    case 4: return m_type;
    }
}
