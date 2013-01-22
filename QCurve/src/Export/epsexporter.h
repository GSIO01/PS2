#ifndef EPSEXPORTER_H
#define EPSEXPORTER_H

#include <QtCore/QString>
#include <QtCore/QFile>
#include <QtCore/QTextStream>

class Point2D;
class Function;
/**
 * Implements an simple exporter to draw functions in the EPS format.
 */
class EpsExporter
{
  public:
    EpsExporter(const QString& fileName, const QString& author= QString("QCurve"));
    ~EpsExporter();

    /**
     * Export to EPS file.
     *
     * \param fileName File name for the EPS file.
     */
    bool exportToFile(const Function& function);

  private:
    void drawLine(double x1, double y1, double x2, double y2);
    void drawLine(const Point2D& start, const Point2D& end);
    /** Write the header to the file. */
    void writeHeader();
    /** Write the defintions to the file. */
    void writeDefinitions();
    /** Write footer to the file. */
    void writeFooter(const QRectF& dimension);

    QFile m_file;
    QTextStream m_writer;

    QString m_author;
};

#endif
