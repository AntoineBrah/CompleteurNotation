#include "Initialisation.h"

void initialiserPiece(){

    /*****************************/
    /* Convention écriture pièce */
    /*****************************/

    // Première lettre de la pièce en majuscule suivi de la première lettre de la couleur de la pièce en minuscule suivi du numéro de la pièce (sauf pour le roi et la dame).
    // Exemple, le pion blanc n°1 se note : Pb1
    // Exemple, le cavalier noir n°2 se note : Cn2
    // Exemple, la dame blanche se note : Db
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

    /* Création plateau */

    // Ce plateau sert juste à simplifier l'initialisation des cellules de chaque pièces 
}
