#include <QApplication>
#include "mainwindow.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv); // Initialisation de l'application Qt
    MaFenetre maFenetre; // Création de l'objet fenêtre
    maFenetre.show(); // Affichage de la fenêtre
    return app.exec(); // Démarrage de la boucle d'événements
}
