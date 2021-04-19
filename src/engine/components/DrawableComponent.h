#ifndef DRAWABLECOMPONENT_H
#define DRAWABLECOMPONENT_H

#include "Component.h"
class Graphics;
class Shape;
class Material;

class DrawableComponent: public Component
{
public:
    DrawableComponent(GameObject* object, QString shape, QString mat, bool isText = false);

    virtual void onTick(float seconds) override;

    void setShape(QString shape);

    void draw(Graphics* g) const;

private:

    QString m_shape;
    QString m_material;
    bool m_isText;
};

#endif // DRAWABLECOMPONENT_H
