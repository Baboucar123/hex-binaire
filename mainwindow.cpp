#include "mainwindow.h"

MaFenetre::MaFenetre(QWidget *parent) : QDialog(parent)
{
   // 1. Instancier les widgets
   valeur = new QLineEdit(this);
   resultat = new QLabel(this);
   unite = new QLabel(this);
   choixConversion = new QComboBox(this);
   bConvertir = new QPushButton(QString::fromUtf8("Convertir"), this);
   bQuitter = new QPushButton(QString::fromUtf8("Quitter"), this);

   // 2. Personnaliser les widgets
   valeur->setStyleSheet("color: #0a214c; background-color: #C19A6B;");
   valeur->clear();
   QFont font("Liberation Sans", 12, QFont::Bold);
   choixConversion->setFont(font);
   choixConversion->addItem(QString::fromUtf8("Base 2 -> Base 16"));
   choixConversion->addItem(QString::fromUtf8("Base 16 -> Base 2"));
   resultat->setStyleSheet("color: #0a214c;");
   unite->setStyleSheet("color: #0a214c;");

   // 3. Instancier les layouts
   QHBoxLayout *hLayout1 = new QHBoxLayout;
   QHBoxLayout *hLayout2 = new QHBoxLayout;
   QVBoxLayout *mainLayout = new QVBoxLayout;

   // 4. Positionner les widgets dans les layouts
   hLayout1->addWidget(valeur);
   hLayout1->addWidget(choixConversion);
   hLayout1->addWidget(resultat);
   hLayout1->addWidget(unite);
   hLayout2->addWidget(bConvertir);
   hLayout2->addWidget(bQuitter);
   mainLayout->addLayout(hLayout1);
   mainLayout->addLayout(hLayout2);
   setLayout(mainLayout);

   // 5. Connecter les signaux et slots
   connect(bConvertir, SIGNAL(clicked()), this, SLOT(convertir()));
   connect(choixConversion, SIGNAL(currentIndexChanged(int)), this, SLOT(permuter()));
   connect(bQuitter, SIGNAL(clicked()), qApp, SLOT(quit()));
   // Bonus : conversion automatique
   connect(valeur, SIGNAL(textChanged(const QString &)), this, SLOT(convertir()));

   // 6. Personnaliser la fenêtre
   setWindowTitle(QString::fromUtf8("Convertisseur de bases"));
   adjustSize();
}

// 7. Définir les slots
void MaFenetre::convertir()
{
   QString nombre = valeur->text();
   if (nombre.isEmpty())
   {
       resultat->setText(QString::fromUtf8("--.--"));
       afficherUnite();
       return;
   }

   bool ok;
   switch (choixConversion->currentIndex())
   {
   case Base16_Base2:
   {
       int base16 = nombre.toInt(&ok, 16);
       if (ok)
       {
           resultat->setText(QString::number(base16, 2));
       }
       else
       {
           resultat->setText(QString::fromUtf8("Erreur"));
       }
       break;
   }
   case Base2_Base16:
   {
       int base2 = nombre.toInt(&ok, 2);
       if (ok)
       {
           resultat->setText(QString::number(base2, 16));
       }
       else
       {
           resultat->setText(QString::fromUtf8("Erreur"));
       }
       break;
   }
   }
   afficherUnite();
}

void MaFenetre::permuter()
{
   if (resultat->text() != "--.--")
   {
       valeur->setText(resultat->text());
       convertir();  // Appeler directement convertir
   }
   afficherUnite();
}

// 8. Définir les méthodes
void MaFenetre::afficherUnite()
{
   switch (choixConversion->currentIndex())
   {
   case Base16_Base2:
       unite->setText(QString::fromUtf8(" (base 2)"));
       break;
   case Base2_Base16:
       unite->setText(QString::fromUtf8(" (base 16)"));
       break;
   }
}

