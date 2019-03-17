# KingGarron_Engine

Nicolas Babot Altisen
Xavier Olivenza Busquets

Scene of the Engine:

![Scene](https://github.com/nicobabot/KingGarron_Engine/blob/master/Images/Scene.PNG?raw=true)

Hierarcy to add and remove objects:

![Hierarcy](https://github.com/nicobabot/KingGarron_Engine/blob/master/Images/Hierarcy.PNG?raw=true)

Inspector to view all the information of the object:

![Inspector](https://github.com/nicobabot/KingGarron_Engine/blob/master/Images/Inspector.PNG?raw=true)

Component Transform
In this component is stored by now position x and position y of the object:

![CompTransform](https://github.com/nicobabot/KingGarron_Engine/blob/master/Images/CompTransform.PNG?raw=true)

Component Render
In this component is stored the shape of the object, also the color and the size of the object:

![RenderTransform](https://github.com/nicobabot/KingGarron_Engine/blob/master/Images/RenderTransform.PNG?raw=true)

We've created entities that have components.
This components store all the information about their type of comoponent.
We've also created Widgets of all the components types and connected the components to the widgets by using slots and signals.

Connect:
 ```bash
    connect(ui->pos_x, SIGNAL(valueChanged(double)), this, SLOT(PosXWidget(double)));
    connect(ui->pos_y, SIGNAL(valueChanged(double)), this, SLOT(PosYWidget(double)));
    connect(ui->pos_z, SIGNAL(valueChanged(double)), this, SLOT(PosZWidget(double)));
 ```
 
 Slots:
 
  ```bash
 public slots:
    void PosXWidget(double item);
    void PosYWidget(double item);
    void PosZWidget(double item);
   ```
 
To print the scene we have a class that inheritates from QWidget and a widget promoted that will print using Qpainter all the objects.

Scene in paint event calling object drawing:

```bash
void GScene::paintEvent(QPaintEvent* event)
{
    for (gObject* object : scenegObjectVector)
        object->PaintGGObject(this); 
}
```
To choose the color of the Objects we used a QColorDialog to let the user choose the color and finally we change the stylesheet of a button to show the user the color of the object.

```bash
void GRenderWidget::ColorPicker()
{
    QColor color = QColorDialog::getColor();
    if (renderComponent != nullptr)
    {
        renderComponent->color = color;
        ui->ColorButton->setStyleSheet(QString("Background-Color: %0;").arg(renderComponent->color.name()));
    }
}
```

Honor to the name of the engine:

![KingKRool](https://github.com/nicobabot/KingGarron_Engine/blob/master/Images/KingKRool.jpg?raw=true)
