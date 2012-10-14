#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "../src/Image.hpp"
#include "../src/Fonction.hpp"
#include "../src/Traitement.hpp"

#include <string>
#include <iostream>

const QString PATH("./data/");

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    //Image vide
    img = Image();
    output = Image();

    ui->setupUi(this);
    this->setWindowTitle(QString("TP1 - Friedel - Rudnik"));


    //Pour quitter
    QAction *a_quitter = new QAction("Quitter", this);
    ui->menubar->addAction(a_quitter);
    connect(a_quitter , SIGNAL(triggered()), qApp, SLOT(quit()));

    //bouton chargement
    connect(ui->b_load_img, SIGNAL(clicked()), this, SLOT(load_img()));

    //liste de filtres
    ui->cb_filters->addItem(QString("Diffusion d'erreur"));
    ui->cb_filters->addItem(QString("Negatif"));
    ui->cb_filters->addItem(QString("Recadrage"));
    ui->cb_filters->addItem(QString("Egalisation"));
    ui->cb_filters->addItem(QString("Filtre Median"));
    //ui->cb_filters->addItem(QString("Egalisation"));

    //bouton choix de filtre
    connect(ui->b_apply, SIGNAL(clicked()), this, SLOT(apply_filter()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::load_img()
{
    std::cout << "load" << std::endl;
    QString name = QString(PATH) + ui->line_load->text();

    std::cout << "load : " << name.toStdString() << std::endl;

    QImage q_image(PATH + ui->line_load->text());

    if (!q_image.isNull())
    {
        img = Image(name.toStdString());
        QPixmap pixmap_img = QPixmap::fromImage(q_image);


        pixmap_img = pixmap_img.scaled(300,300,Qt::KeepAspectRatio);

        ui->l_im_ori->clear();

        ui->l_im_ori->setPixmap(pixmap_img);
    }
    else
    {
        std::cout << "Erreur de chargement" << std::endl;
    }

}

void MainWindow::apply_filter()
{
    Traitement tr = Traitement();
    std::cout << img.getHauteur() << std::endl;
    if(img.getHauteur()!=0)
    {
        if (output.getHauteur() != 0)
        {
            output = Image();
        }
        Fonction func = Fonction(255);
        switch (ui->cb_filters->currentIndex())
        {
        case 0:
          std::cout << "Diff erreur" << std::endl;
          tr.diffusionErreur(img, output);
          //func.correspondance(img, output);
          break;
        case 1:
          std::cout << "Negatif" << std::endl;
          func.negatif(img, output);
          break;
        case 2:
          std::cout << "Recadrage" << std::endl;
          func.recadrage(img, output);
          break;
        case 3:
          std::cout << "Egalisation" << std::endl;
          func.egalisation(img, output);
          break;
        case 4:
            std::cout << "Filtre Median" << std::endl;
            tr.filtreMedian(img, output);
            break;
        case 5:

            break;

        default:
          // Code
          break;
        }

        //Chargement de l'image dans le label d'arrivée
        output.saveBin(PATH.toStdString() + "output_qt.pgm");
        img.saveBin(PATH.toStdString() + "img_qt.pgm");

        QString name_o = QString(PATH + "output_qt.pgm");

        QImage q_image_o(name_o);

        output = Image(name_o.toStdString());
        QPixmap pixmap_img_o = QPixmap::fromImage(q_image_o);


        pixmap_img_o = pixmap_img_o.scaled(300,300,Qt::KeepAspectRatio);

        ui->l_im_end->clear();

        ui->l_im_end->setPixmap(pixmap_img_o);
    }else{
        std::cout << "image non chargée" << std::endl;
    }
}
