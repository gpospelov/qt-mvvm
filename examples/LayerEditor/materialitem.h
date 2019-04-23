#ifndef MATERIALITEM_H
#define MATERIALITEM_H

#include <QColor>
#include <string>

class MaterialItem
{
public:
    static const int size = 5;
    enum DATA_TYPE {SLD, RefIndex};
    static QString propertyName(int column, DATA_TYPE type);

    MaterialItem(DATA_TYPE type);

    // setters
    void setName(std::string name) {m_name = name;}
    void setDataReal(double real) {m_real = real;}
    void setDataImag(double imag) {m_imag = imag;}
    // void setType(DATA_TYPE type) {m_type = type;}
    void setColor(QColor color) {m_color = color;}

    // getters
    std::string name() const {return m_name;}
    double dataReal() const {return m_real;}
    double dataImag() const {return m_imag;}
    DATA_TYPE type() const {return m_type;}
    QColor color() const {return m_color;}

    QVariant property(int column) const;

private:
    QColor m_color;
    std::string m_name;
    double m_real;
    double m_imag;
    DATA_TYPE m_type;
};

#endif // MATERIALITEM_H
