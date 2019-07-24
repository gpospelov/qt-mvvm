// ************************************************************************** //
//
//  Prototype of mini MVVM framework for bornagainproject.org
//
//! @homepage  http://www.bornagainproject.org
//! @license   GNU General Public License v3 or higher
//
// ************************************************************************** //

#ifndef DESIGNERMIMEDATA_H
#define DESIGNERMIMEDATA_H

#include <QMimeData>

class QDrag;
class QXmlStreamReader;

//! Mime data for use with SampleDesigner drag and drop operations
class DesignerMimeData : public QMimeData
{
    Q_OBJECT
public:
    DesignerMimeData(const std::string& name, const QString &xmldescr, QDrag *drag);
    ~DesignerMimeData() override;

    //! Execute a drag and drop operation.
    static Qt::DropAction execDrag(const std::string& name, const QString &xmldescr, QWidget * dragSource);

    std::string getClassName() const { return m_classname; }
private:
    void read_xmldescr(const QString &xmldescr);
    void read_widget(QXmlStreamReader &reader);

    std::string m_entryname;
    std::string m_classname;

};

#endif // DESIGNERMIMEDATA_H
