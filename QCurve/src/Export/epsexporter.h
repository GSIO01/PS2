#ifndef EPSEXPORTER_H
#define EPSEXPORTER_H

#include <QtCore/QString>

class EpsExporter
{
  public:
    EpsExporter();
    ~EpsExporter();

    QString author() const;
    void setAuthor(const QString& author);

    void exportToFile(const QString& fileName);

  private:
    void writeHeader();
    void writeDefinitions();
    void writeFooter();
};

#endif
