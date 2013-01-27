#ifndef EPSEXPORTER_H
#define EPSEXPORTER_H

#include <QtCore/QString>
#include <QtCore/QFile>
#include <QtCore/QTextStream>

class Point3D;
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
     * Toogles visibility of helper items.
     * 
     * \param showHelperItems Whether to show helper items in the exported file or not.
     */
    void setShowHelperItems(bool showHelperItems);
    /**
     * Toogles visibility of Labels.
     * 
     * \param showLabels Whether to show labels in the exported file or not.
     */
    void setShowLabels(bool showLabels);
    /**
     * Toogles visibility of the Grid.
     * 
     * \param showGrid Whether to show the grid in exported file or not.
     */
    void setShowGrid(bool showGrid);

    /**
     * Export to EPS file.
     *
     * \param fileName File name for the EPS file.
     */
    bool exportToFile(const Function& function);

  private:
    /**
     * Adds a line to the file.
     * 
     * \param x1 x coordinate of start point
     * \param x2 x coordinate of end point
     * \param y1 y coordinate of start point
     * \param y2 y coordinate of end point
     */
    void drawLine(double x1, double y1, double x2, double y2);
    /**
     * Adds a line to the file.
     * 
     * \param start start point
     * \param end end point
     */
    void drawLine(const Point3D& start, const Point3D& end);
    /**
     * Adds a circle to the file.
     * 
     * \param p center point
     * \param r radius
     */
    void drawCircle(const Point3D& p, double r);

    /** 
     * Write the header to the file. 
     */
    void writeHeader();
    /** 
     * Write the defintions to the file. 
     */
    void writeDefinitions();
    /** 
     * Write footer to the file. 
     * 
     * \param dimension dimension
     */
    void writeFooter(const QRectF& dimension);

    QFile m_file;
    QTextStream m_writer;

    QString m_author;

    bool m_showHelpers;
    bool m_showLabels;
    bool m_showGrid;
};

#endif
