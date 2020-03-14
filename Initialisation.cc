#include "Initialisation.h"

vector<Cellule*>* initialiserCellules(){

    /*****************************/
    /* Convention écriture pièce */
    /*****************************/

    // Première lettre de la pièce en majuscule suivi de la première lettre de la couleur de la pièce en minuscule suivi du numéro de la pièce (sauf pour le roi).
    // Exemple, le pion blanc n°1 se note : Pb1
    // Exemple, le cavalier noir n°2 se note : Cn2
    // Exemple, la dame blanche se note : Db1
    // Exemple, le roi noir se note : Rn

    /*****************************/
    /*****************************/

    // Ne pas oublier de delete toutes les pièces allouées dynamiquement

    /* Pièces joueur blanc */

    Piece *Pb1 = new Pion(Blanc, type::Pion, "a2"); // Pion blanc n°1 situé en a2
    Piece *Pb2 = new Pion(Blanc, type::Pion, "b2"); 
    Piece *Pb3 = new Pion(Blanc, type::Pion, "c2");
    Piece *Pb4 = new Pion(Blanc, type::Pion, "d2");
    Piece *Pb5 = new Pion(Blanc, type::Pion, "e2");
    Piece *Pb6 = new Pion(Blanc, type::Pion, "f2");
    Piece *Pb7 = new Pion(Blanc, type::Pion, "g2");
    Piece *Pb8 = new Pion(Blanc, type::Pion, "h2");

    Piece *Tb1 = new Tour(Blanc, type::Tour, "a1"); // Tour blanche n°1 situé en a1
    Piece *Tb2 = new Tour(Blanc, type::Tour, "h1"); // Tour blanche n°2 situé en h1
    Piece *Cb1 = new Cavalier(Blanc, type::Cavalier, "b1"); // Cavalier blanc n°1 situé en b1
    Piece *Cb2 = new Cavalier(Blanc, type::Cavalier, "g1"); // Cavalier blanc n°2 situé en b2
    Piece *Fb1 = new Fou(Blanc, type::Fou, "c1"); // Fou blanc n°1 situé en c1
    Piece *Fb2 = new Fou(Blanc, type::Fou, "f1"); // Fou blanc n°1 situé en c1
    Piece *Db1 = new Dame(Blanc, type::Dame, "d1"); // Dame blanche n°1 situé en d1 (n°1 car il peut y avoir des promotions)
    Piece *Rb = new Roi(Blanc, type::Roi, "e1"); // Roi blanc situé en e1

    /* Pièces joueur noir */
    
    Piece *Pn1 = new Pion(Noir, type::Pion, "h7"); // Pion noir n°1 situé en h7
    Piece *Pn2 = new Pion(Noir, type::Pion, "g7"); 
    Piece *Pn3 = new Pion(Noir, type::Pion, "f7");
    Piece *Pn4 = new Pion(Noir, type::Pion, "e7");
    Piece *Pn5 = new Pion(Noir, type::Pion, "d7");
    Piece *Pn6 = new Pion(Noir, type::Pion, "c7");
    Piece *Pn7 = new Pion(Noir, type::Pion, "b7");
    Piece *Pn8 = new Pion(Noir, type::Pion, "a7");

    Piece *Tn1 = new Tour(Noir, type::Tour, "h8"); // Tour noire n°1 situé en h8
    Piece *Tn2 = new Tour(Noir, type::Tour, "a8"); // Tour noire n°2 situé en a8
    Piece *Cn1 = new Cavalier(Noir, type::Cavalier, "g8"); 
    Piece *Cn2 = new Cavalier(Noir, type::Cavalier, "b8"); 
    Piece *Fn1 = new Fou(Noir, type::Fou, "f8"); 
    Piece *Fn2 = new Fou(Noir, type::Fou, "c8"); 
    Piece *Dn1 = new Dame(Noir, type::Dame, "d8"); 
    Piece *Rn = new Roi(Noir, type::Roi, "e8"); 

    /* Création listeCellules */

    // Ce vector contient les 32 cellules initiales qui elles mêmes contiennent chacune 1 pièce.
    // Chaque fois qu'on créera une nouvelle cellule on la "rangera" dans ce vector
    
    vector<Cellule*> *listeCellules = new vector<Cellule*>;

    // Les pions noirs
    Cellule* cPn1 = new Cellule(Pn1);
    listeCellules->push_back(cPn1);
    Pn1->setFirstCell(cPn1);

    Cellule* cPn2 = new Cellule(Pn2);
    listeCellules->push_back(cPn2);
    Pn2->setFirstCell(cPn2);

    Cellule* cPn3 = new Cellule(Pn3);
    listeCellules->push_back(cPn3);
    Pn3->setFirstCell(cPn3);

    Cellule* cPn4 = new Cellule(Pn4);
    listeCellules->push_back(cPn4);
    Pn4->setFirstCell(cPn4);

    Cellule* cPn5 = new Cellule(Pn5);
    listeCellules->push_back(cPn5);
    Pn5->setFirstCell(cPn5);

    Cellule* cPn6 = new Cellule(Pn6);
    listeCellules->push_back(cPn6);
    Pn6->setFirstCell(cPn6);

    Cellule* cPn7 = new Cellule(Pn7);
    listeCellules->push_back(cPn7);
    Pn7->setFirstCell(cPn7);

    Cellule* cPn8 = new Cellule(Pn8);
    listeCellules->push_back(cPn8);
    Pn8->setFirstCell(cPn8);

    // Les pièces noires
    Cellule* cTn1 = new Cellule(Tn1);
    listeCellules->push_back(cTn1);
    Tn1->setFirstCell(cTn1);

    Cellule* cTn2 = new Cellule(Tn2);
    listeCellules->push_back(cTn2);
    Tn2->setFirstCell(cTn2);

    Cellule* cCn1 = new Cellule(Cn1);
    listeCellules->push_back(cCn1);
    Cn1->setFirstCell(cCn1);

    Cellule* cCn2 = new Cellule(Cn2);
    listeCellules->push_back(cCn2);
    Cn2->setFirstCell(cCn2);

    Cellule* cFn1 = new Cellule(Fn1);
    listeCellules->push_back(cFn1);
    Fn1->setFirstCell(cFn1);

    Cellule* cFn2 = new Cellule(Fn2);
    listeCellules->push_back(cFn2);
    Fn2->setFirstCell(cFn2);

    Cellule* cDn1 = new Cellule(Dn1);
    listeCellules->push_back(cDn1);
    Dn1->setFirstCell(cDn1);

    Cellule* cRn = new Cellule(Rn);
    listeCellules->push_back(cRn);
    Rn->setFirstCell(cRn);

    // Les pions blancs
    Cellule* cPb1 = new Cellule(Pb1);
    listeCellules->push_back(cPb1);
    Pb1->setFirstCell(cPb1);

    Cellule* cPb2 = new Cellule(Pb2);
    listeCellules->push_back(cPb2);
    Pb2->setFirstCell(cPb2);

    Cellule* cPb3 = new Cellule(Pb3);
    listeCellules->push_back(cPb3);
    Pb3->setFirstCell(cPb3);

    Cellule* cPb4 = new Cellule(Pb4);
    listeCellules->push_back(cPb4);
    Pb4->setFirstCell(cPb4);

    Cellule* cPb5 = new Cellule(Pb5);
    listeCellules->push_back(cPb5);
    Pb5->setFirstCell(cPb5);

    Cellule* cPb6 = new Cellule(Pb6);
    listeCellules->push_back(cPb6);
    Pb6->setFirstCell(cPb6);

    Cellule* cPb7 = new Cellule(Pb7);
    listeCellules->push_back(cPb7);
    Pb7->setFirstCell(cPb7);

    Cellule* cPb8 = new Cellule(Pb8);
    listeCellules->push_back(cPb8);
    Pb8->setFirstCell(cPb8);

    // Les pièces blanches
    Cellule* cTb1 = new Cellule(Tb1);
    listeCellules->push_back(cTb1);
    Tb1->setFirstCell(cTb1);

    Cellule* cTb2 = new Cellule(Tb2);
    listeCellules->push_back(cTb2);
    Tb2->setFirstCell(cTb2);

    Cellule* cCb1 = new Cellule(Cb1);
    listeCellules->push_back(cCb1);
    Cb1->setFirstCell(cCb1);

    Cellule* cCb2 = new Cellule(Cb2);
    listeCellules->push_back(cCb2);
    Cb2->setFirstCell(cCb2);

    Cellule* cFb1 = new Cellule(Fb1);
    listeCellules->push_back(cFb1);
    Fb1->setFirstCell(cFb1);

    Cellule* cFb2 = new Cellule(Fb2);
    listeCellules->push_back(cFb2);
    Fb2->setFirstCell(cFb2);

    Cellule* cDb1 = new Cellule(Db1);
    listeCellules->push_back(cDb1);
    Db1->setFirstCell(cDb1);

    Cellule* cRb = new Cellule(Rb);
    listeCellules->push_back(cRb);
    Rb->setFirstCell(cRb);

    updateListeCoupsPossiblesAll(true); // On met à jour la liste des coups possibles de toutes les pièces instanciées
    
    return listeCellules;
}
