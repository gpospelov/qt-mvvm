// ************************************************************************** //
//
//  Model-view-view-model framework for large GUI applications
//
//! @license   GNU General Public License v3 or higher (see COPYING)
//! @authors   see AUTHORS
//
// ************************************************************************** //

#include "mvvm/editors/scientificspinbox.h"
#include "mvvm/editors/editor_constants.h"
#include <QLineEdit>
#include <cmath>
#include <limits>

namespace {
const double upper_switch = 1000;
const double lower_switch = 0.1;
const double min_val = std::numeric_limits<double>::min();
const double max_val = std::numeric_limits<double>::max();

bool useExponentialNotation(double val);
} // namespace

using namespace ModelView;

ScientificSpinBox::ScientificSpinBox(QWidget* parent)
    : QAbstractSpinBox(parent)
    , m_value(0.0)
    , m_min(-max_val)
    , m_max(max_val)
    , m_step(1.0)
    , m_decimals(Constants::default_double_decimals)
{
    QLocale locale;
    locale.setNumberOptions(QLocale::RejectGroupSeparator);
    m_validator.setLocale(locale);
    m_validator.setNotation(QDoubleValidator::ScientificNotation);

    connect(this, &QAbstractSpinBox::editingFinished, this, &ScientificSpinBox::updateValue);
}

ScientificSpinBox::~ScientificSpinBox() = default;

double ScientificSpinBox::value() const
{
    // return last acceptable input (required for the proper focus-out behaviour)
    double val = toDouble(text(), m_validator, m_min, m_max, m_value);
    return round(val, m_decimals);
}

void ScientificSpinBox::setValue(double val)
{
    double old_val = m_value;
    m_value = round(val, m_decimals);
    updateText();
    if (std::abs(old_val - m_value) > min_val)
        emit valueChanged(m_value);
}

void ScientificSpinBox::updateValue()
{
    double new_val = toDouble(text(), m_validator, m_min, m_max, m_value);
    setValue(new_val);
}

double ScientificSpinBox::singleStep() const
{
    return m_step;
}

void ScientificSpinBox::setSingleStep(double step)
{
    m_step = step;
}

double ScientificSpinBox::minimum() const
{
    return m_min;
}

void ScientificSpinBox::setMinimum(double min)
{
    m_min = min;
    if (m_value < m_min)
        setValue(m_min);
}

double ScientificSpinBox::maximum() const
{
    return m_max;
}

void ScientificSpinBox::setMaximum(double max)
{
    m_max = max;
    if (m_value > m_max)
        setValue(m_max);
}

void ScientificSpinBox::setDecimals(int val)
{
    if (val <= 0)
        return;
    m_decimals = val;
    setValue(m_value);
}

int ScientificSpinBox::decimals() const
{
    return m_decimals;
}

void ScientificSpinBox::stepBy(int steps)
{
    double new_val = round(m_value + m_step * steps, m_decimals);
    if (inRange(new_val))
        setValue(new_val);
}

QString ScientificSpinBox::toString(double val, int decimal_points)
{
    QString result = useExponentialNotation(val) ? QString::number(val, 'e', decimal_points)
                                                 : QString::number(val, 'f', decimal_points);

    return result.replace(QRegExp("(\\.?0+)?((e{1}[\\+|-]{1})(0+)?([1-9]{1}.*))?$"), "\\3\\5");
}

double ScientificSpinBox::toDouble(QString text, const QDoubleValidator& validator, double min,
                                   double max, double default_value)
{
    int pos = 0;
    if (validator.validate(text, pos) == QValidator::Acceptable) {
        double new_val = validator.locale().toDouble(text);
        if (std::abs(new_val) < min_val)
            new_val = 0.0;
        return new_val >= min && new_val <= max ? new_val : default_value;
    }
    return default_value;
}

double ScientificSpinBox::round(double val, int decimals)
{
    char notation = useExponentialNotation(val) ? 'e' : 'f';
    return QString::number(val, notation, decimals).toDouble();
}

QAbstractSpinBox::StepEnabled ScientificSpinBox::stepEnabled() const
{
    return isReadOnly() ? StepNone : StepUpEnabled | StepDownEnabled;
}

void ScientificSpinBox::updateText()
{
    QString new_text = toString(m_value, m_decimals);
    if (new_text != text())
        lineEdit()->setText(new_text);
}

bool ScientificSpinBox::inRange(double val) const
{
    return val >= m_min && val <= m_max;
}

namespace {
bool useExponentialNotation(double val)
{
    const double abs_val = std::abs(val);

    if (abs_val <= min_val)
        return false;

    return abs_val >= upper_switch || abs_val < lower_switch;
}
} // namespace
