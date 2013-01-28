#ifndef EXPORT_DIALOG
#define EXPORT_DIALOG

#include <QtGui/QFileDialog>
#include <QtGui/QCheckBox>
#include <QtGui/QLineEdit>

class ExportDialog : public QFileDialog
{
  Q_OBJECT

  public:
    ExportDialog(QWidget* parent = 0);
    ~ExportDialog();

    bool showLabels() { return m_labels->isChecked(); }
    bool showGrid() { return m_grid->isChecked(); }
    bool showHelperItems() { return m_helperItems->isChecked(); }

    QString author() { return m_author->text(); }

  private:
    void extendLayout();

    QCheckBox* m_labels;
    QCheckBox* m_grid;
    QCheckBox* m_helperItems;
    QLineEdit* m_author;
};

#endif
