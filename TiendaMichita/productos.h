#ifndef PRODUCTOS_H
#define PRODUCTOS_H

#include <QDialog>
#include "principal.h"


namespace Ui {
class Productos;
}

class Productos : public QDialog
{
    Q_OBJECT

public:
    explicit Productos(QWidget *parent = nullptr);
    ~Productos();
        void setIni(QStringList);
        void setProductos(int, QString, float);
       QString archivosGuardado;

private slots:
    void Agregar();

    void Eliminar();

    void Guardar();

private:
    Ui::Productos *ui;

};

#endif // PRODUCTOS_H
