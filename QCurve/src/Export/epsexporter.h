#ifndef EPSEXPORTER_H
#define EPSEXPORTER_H

#include <QtCore/QString>

/**
 * Implemts an EPS exporter.
 */
class EpsExporter
{
  public:
    /**
     * Constructor.
     */
    EpsExporter();
    /**
     * Destructor.
     */
    ~EpsExporter();

    /**
     * Get author.
     * 
     * \returns Author.
     */
    QString author() const;
    /**
     * Set the author.
     * 
     * \param author New value for author.
     */
    void setAuthor(const QString& author);

    /**
     * Export to EPS file.
     * 
     * \param fileName File name for the EPS file.
     */
    void exportToFile(const QString& fileName);

  private:
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
     */
    void writeFooter();
};

#endif
