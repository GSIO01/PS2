#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include <QtCore/QString>

#include <QtGui/QColor>
#include <QtGui/QGraphicsItem>

/**
 * Base class for all graphical helper objects of functions (e.g. the
 * rolling circle which generates a cycloid).
 */
class Primitive
{
  public:
    enum PrimitiveType
    {
      PT_Point,
      PT_Line,
      PT_Circle
    };

    Primitive(PrimitiveType type, const QString& name,
              const QString& description = QString());

    QString name() const { return m_name; }
    PrimitiveType type() const { return m_type; }

    QString description() const { return m_description; }
    void setDescription(const QString& m_description);

    QColor color() const { return m_color; }
    void setColor(const QColor& color);

    bool isAnimated() const { return m_isAnimated; }
    void setIsAnimated(bool isAnimated);

    virtual QGraphicsItem* toGraphicsItem() const = 0;
    virtual void updateGraphicsItem(QGraphicsItem* item) const = 0;

    bool operator==(const Primitive& other);

  protected:
    PrimitiveType m_type;

    QString m_name;
    QString m_description;
    QColor m_color;

    bool m_isAnimated;
};

#endif
