#include "productos.h"
#include "ui_productos.h"

#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include<QMessageBox>

Productos::Productos(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Productos)
{
    ui->setupUi(this);

    connect(ui->cmdAgregar_2, SIGNAL(clicked(bool)), this, SLOT(Agregar()));
    connect(ui->cmdEliminar_2, SIGNAL(clicked(bool)), this, SLOT(Eliminar()));
    connect(ui->cmdGuardar_2, SIGNAL(clicked(bool)), this, SLOT(Guardar()));
    connect(ui->cmdOK, SIGNAL(clicked(bool)), this, SLOT(close()));
    //Cabecera
    QStringList inicio = {"Codigo", "Producto", "Precio"};
            ui->outProductos_2->setColumnCount(3);
            ui->outProductos_2->setHorizontalHeaderLabels(inicio);

}

Productos::~Productos()
{
    delete ui;
}

void Productos::setIni(QStringList inicio)
{
    ui->outProductos_2->setHorizontalHeaderLabels(inicio);
}

void Productos::setProductos(int codigo, QString producto, float precio)
{
    int posicion = ui->outProductos_2->rowCount();
        ui->outProductos_2->insertRow(posicion);
        ui->outProductos_2->setItem(posicion,0,new QTableWidgetItem(QString::number(codigo)));
        ui->outProductos_2->setItem(posicion,1,new QTableWidgetItem(producto));
        ui->outProductos_2->setItem(posicion,2,new QTableWidgetItem(QString::number(precio)));
}

void Productos::Agregar()

{
    int ing = ui->outProductos_2->rowCount();
        ui->outProductos_2->insertRow(ing);
}

void Productos::Eliminar()
{
    int eli = ui->outProductos_2->currentRow();
           ui->outProductos_2->removeRow(eli);
}

void Productos::Guardar()
{
    //Guardar en el mismo archivo los productos eliminados o agregados
    QMessageBox mensajeBox;
            QString fileName = "productos.csv";
                if (fileName.isEmpty()) {
                    return;
                }

                QFile file(fileName);
                if (!file.open(QIODevice::WriteOnly |   QFile::Text)) {
                    QMessageBox::information(this, tr("No se puede abrir el archivo"),
                    file.errorString());
                    return;
                }

                QTextStream out(&file);
                int rowCount = ui->outProductos_2->rowCount();
                int colCount = ui->outProductos_2->columnCount();

                for (int i = 0; i < rowCount; i++) {

                    for (int j = 0; j < colCount; j++) {
                        if (j > 0) {
                            out << ";";
                        }
                        QTableWidgetItem* item = ui->outProductos_2->item(i,j);
                        out << item->data(Qt::DisplayRole).toString();
                    }
                    out << "\n";
                }
                mensajeBox.setText("Se guardó en el archivo:" + fileName);
                mensajeBox.exec();
}
