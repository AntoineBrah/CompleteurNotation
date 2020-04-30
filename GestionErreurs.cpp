#include "GestionErreurs.h"

/*
*   Rajoute un "x" à la Pièce/Pion qui mange une autre Pièce/Pion + Chaque fois qu'un Pion mange une pièce on précise également sa colonne.
*/
void deplacementPiece(Piece* p, Cellule* &k, string coup, string couleur, vector<string> &descCoup, int nbCoup){

    if(descCoup[0] != "Pion" && couleur == "Blanc" && nbCoup == 1){

        Cellule *dernierCSP = getDernierCSP(p->getFirstCell());

        // On récupère la première pièce possèdant cette position dans sa liste des coups possibles
        p->setPostion(descCoup[3]); // on déplace la pièce

        // On créé une nouvelle cellule contenant la pièce avec les nouvelles positions
        Cellule *c = new Cellule(p);
        c->copieListeCoupsPossibles(dernierCSP);

        dernierCSP->setCSP(c);
        dernierCSP->setCSE(c);
        c->setCPP(dernierCSP);
        c->setCPE(dernierCSP);

        k=c;

        updateListeCoupsPossiblesAll(true); // Vu qu'on déplace une piece, on met à jour la liste des coups possibles de toutes les pièces
    }
    else if(descCoup[0] != "Pion" && couleur == "Blanc"){

        Cellule *dernierCSP = getDernierCSP(p->getFirstCell());

        Position pos = Position(descCoup[3]); // On stock la position initiale de la pièce

        Piece *p2 = NULL; // On récupère la pièce qui se situe sur le déplacement
        
        if(existePieceSurPosition(descCoup[3])){
            p2 = existePieceSurPosition(descCoup[3]);
            seFaitMangerPiece(p2); // Si une pièce est présente sur la position du déplacement, alors elle se fait manger

            descCoup[6] = "x"; // On rajoute le "x" étant donné qu'une pièce se fait manger
        }

        p->setPostion(descCoup[3]); // on déplace la pièce
        updateListeCoupsPossiblesAll(false); // Vu qu'on déplace une piece, on met à jour la liste des coups possibles de toutes les pièces
        
        if(estEnEchecRoi("Blanc")){
            // Si malgré le déplacement de la pièce, le roi est toujours en échec (ou devient en échec) alors on annule le déplacement de la pièce
            // et on ne créé pas de nouvelle cellule


            p->setPostion(pos.getCoord());

            if(p2 != NULL){
                annulationSeFaitMangerPiece(p2, descCoup[3]);

                descCoup[6] = ""; // On enlève le "x"
            }

            updateListeCoupsPossiblesAll(false);
            cout << "\n[i] " << p->getNomString() << " " << p->getCouleur() << " ne peut pas être déplacé en " << descCoup[3] << " car sinon son Roi est (ou reste) en échec.\n" << endl;
        }
        else{
            // Cas ou le déplacement d'une piece entraine le fait que le Roi Blanc n'est plus en échec
            // Dans cette situation tout se déroule comme quand le Roi n'est pas en échec

            p->setPostion(descCoup[3]); // on déplace la pièce

            // On créé une nouvelle cellule contenant la pièce avec les nouvelles positions
            Cellule *c = new Cellule(p);
            c->copieListeCoupsPossibles(dernierCSP);

            dernierCSP->setCSP(c);
            k->setCSE(c);
            c->setCPP(dernierCSP);
            c->setCPE(k);

            k=c;

            // On déplace juste la Tour (on a déplacé le Roi auparavant)
            /* Cas ou le Roi Blanc Roque */
            if(p->getNomString() == "Roi" && descCoup[3] == "g1" && (Point(1,7)-convertPositionToPoint(getDernierCSP(p->getFirstCell())->getCPP()->getPositionCell())).getY() == 2){ // Petit Roque
                
                Piece *t = existePieceSurPosition("h1"); // La Tour en h1 qu'on bouge (elle existe forcément car si le roi possède g1 dans sa LCP alors beaucoup de conditions ont été vérifié au préalable)
                t->setPostion("f1"); // On déplace la tour en f1

                // On s'occupe des cellules de la Tour
                Cellule *deplacementTour = new Cellule(t); // On créer la Cellule avec la nouvelle position de la tour qu'on chaine à sa LCP
                Cellule *tmp = getDernierCSP(t->getFirstCell()); // On récupère la dernière cellule CSP de la tour et on effectue le chainage

                tmp->setCSP(deplacementTour);
                deplacementTour->setCPP(tmp);
                deplacementTour->copieListeCoupsPossibles(tmp);

            }
            else if(p->getNomString() == "Roi" && descCoup[3] == "c1" && (convertPositionToPoint(getDernierCSP(p->getFirstCell())->getCPP()->getPositionCell())-Point(1,3)).getY() == 2){ // Grand Roque
                
                Piece *t = existePieceSurPosition("a1"); // La Tour en a1 qu'on bouge (elle existe forcément car si le roi possède c1 dans sa LCP alors beaucoup de conditions ont été vérifié au préalable)
                t->setPostion("d1"); // On déplace la tour en d1

                // On s'occupe des cellules de la Tour
                Cellule *deplacementTour = new Cellule(t); // On créer la Cellule avec la nouvelle position de la tour qu'on chaine à sa LCP 
                Cellule *tmp = getDernierCSP(t->getFirstCell()); // On récupère la dernière cellule CSP de la tour et on effectue le chainage

                tmp->setCSP(deplacementTour);
                deplacementTour->setCPP(tmp);
                deplacementTour->copieListeCoupsPossibles(tmp);

            }
            
            updateListeCoupsPossiblesAll(true); // Vu qu'on déplace une piece, on met à jour la liste des coups possibles de toutes les pièces
        }
    }
    else if(descCoup[0] == "Pion" && couleur == "Blanc" && nbCoup == 1){

        Cellule *dernierCSP = getDernierCSP(p->getFirstCell());

        // On récupère la première pièce possèdant cette position dans sa liste des coups possibles
        p->setPostion(descCoup[3]); // on déplace la pièce

        // On créé une nouvelle cellule contenant la pièce avec les nouvelles positions
        Cellule *c = new Cellule(p);
        c->copieListeCoupsPossibles(dernierCSP);

        dernierCSP->setCSP(c);
        dernierCSP->setCSE(c);
        c->setCPP(dernierCSP);
        c->setCPE(dernierCSP);
    
        k=c;
        updateListeCoupsPossiblesAll(true); // Vu qu'on déplace une piece, on met à jour la liste des coups possibles de toutes les pièces
    }
    else if(descCoup[0] == "Pion" && couleur == "Blanc"){

        Cellule *dernierCSP = getDernierCSP(p->getFirstCell());
            
        Position pos = Position(descCoup[3]); // On stock la position initiale de la pièce
        
        Piece *p2(NULL); // On récupère la pièce qui se situe sur le déplacement

        bool prendEnPassant = false;
        
        if(existePieceSurPosition(descCoup[3])){
            p2 = existePieceSurPosition(descCoup[3]);
            seFaitMangerPiece(p2); // Si une pièce est présente sur la position du déplacement, alors elle se fait manger

            descCoup[1] = p->getPosition().getColonne(); // On précise de quelle colonne il s'agit
            descCoup[6] = "x"; // On rajoute le "x" étant donné qu'une pièce se fait manger
        }
        else if(existePieceSurPosition(convertPointToPosition(convertPositionToPoint(descCoup[3])-Point(1,0))) && existePieceSurPosition(convertPointToPosition(convertPositionToPoint(descCoup[3])-Point(1,0)))->getCouleur() == "Noir" && existePieceSurPosition(convertPointToPosition(convertPositionToPoint(descCoup[3])-Point(1,0)))->getNomString() == "Pion"){
            // Cas ou on prend en passant
            p2 = existePieceSurPosition(convertPointToPosition(convertPositionToPoint(descCoup[3])-Point(1,0)));
            cout << "Prise en passant : " << endl;
            seFaitMangerPiece(p2);
            prendEnPassant = true;

            descCoup[1] = p->getPosition().getColonne(); // On précise de quelle colonne il s'agit
            descCoup[6] = "x"; // On rajoute le "x" étant donné qu'une pièce se fait manger
        }


        p->setPostion(descCoup[3]); // on déplace la pièce
        updateListeCoupsPossiblesAll(false); // Vu qu'on déplace une piece, on met à jour la liste des coups possibles de toutes les pièces
        
        if(estEnEchecRoi("Blanc")){
            // Si malgré le déplacement de la pièce, le roi est toujours en échec (ou devient en échec) alors on annule le déplacement de la pièce
            // et on ne créé pas de nouvelle cellule

            p->setPostion(pos.getCoord());

            if(p2 != NULL){
                if(!prendEnPassant){
                    annulationSeFaitMangerPiece(p2, descCoup[3]);

                    descCoup[1] = ""; // On enlève la précision de la colonne
                    descCoup[6] = ""; // On enlève le "x"
                }
                else{
                    annulationSeFaitMangerPiece(p2, convertPointToPosition(convertPositionToPoint(descCoup[3])-Point(1,0)));

                    descCoup[1] = ""; // On enlève la précision de la colonne
                    descCoup[6] = ""; // On enlève le "x"
                }
            }
            
            updateListeCoupsPossiblesAll(false);
            cout << "\n[i] " << p->getNomString() << " " << p->getCouleur() << " ne peut pas être déplacé en " << descCoup[3] << " car sinon son Roi est (ou reste) en échec.\n" << endl;
        }
        else{
            // Cas ou le déplacement d'une piece entraine le fait que le Roi Blanc n'est plus en échec
            // Dans cette situation tout se déroule comme quand le Roi n'est pas en
            
            p->setPostion(descCoup[3]); // on déplace la pièce

            // S'il y a une promotion
            if(p->getPosition().getLigne() == "8" && descCoup[4] != ""){
                cout << "--> Promotion du pion blanc en " << descCoup[3] << endl << endl; 
                p->setNom(descCoup[4]);
            } 

            // On créé une nouvelle cellule contenant la pièce avec les nouvelles positions
            Cellule *c = new Cellule(p);
            c->copieListeCoupsPossibles(dernierCSP);
            
            dernierCSP->setCSP(c);
            k->setCSE(c);
            c->setCPP(dernierCSP);
            c->setCPE(k);
            
            k=c;
            updateListeCoupsPossiblesAll(true); // Vu qu'on déplace une piece, on met à jour la liste des coups possibles de toutes les pièces    
        }
    }
    else if(descCoup[0] != "Pion" && couleur == "Noir"){

        Cellule *dernierCSP = getDernierCSP(p->getFirstCell());

        Position pos = Position(descCoup[3]); // On stock la position initiale de la pièce

        Piece *p2 = NULL; // On récupère la pièce qui se situe sur le déplacement
        
        if(existePieceSurPosition(descCoup[3])){
            p2 = existePieceSurPosition(descCoup[3]);
            seFaitMangerPiece(p2); // Si une pièce est présente sur la position du déplacement, alors elle se fait manger

            descCoup[6] = "x"; // On rajoute le "x" étant donné qu'une pièce se fait manger
        }

        p->setPostion(descCoup[3]); // on déplace la pièce
        updateListeCoupsPossiblesAll(false); // Vu qu'on déplace une piece, on met à jour la liste des coups possibles de toutes les pièces
        
        if(estEnEchecRoi("Noir")){
            // Si malgré le déplacement de la pièce, le roi est toujours en échec (ou devient en échec) alors on annule le déplacement de la pièce
            // et on ne créé pas de nouvelle cellule

            p->setPostion(pos.getCoord());

            if(p2 != NULL){
                annulationSeFaitMangerPiece(p2, descCoup[3]);

                descCoup[6] = ""; // On enlève le "x"
            }

            updateListeCoupsPossiblesAll(false);
            cout << "\n[i] " << p->getNomString() << " " << p->getCouleur() << " ne peut pas être déplacé en " << descCoup[3] << " car sinon son Roi est (ou reste) en échec.\n" << endl;
        }
        else{
            // Cas ou le déplacement d'une piece entraine le fait que le Roi Blanc n'est plus en échec
            // Dans cette situation tout se déroule comme quand le Roi n'est pas en échec

            p->setPostion(descCoup[3]); // on déplace la pièce

            // On créé une nouvelle cellule contenant la pièce avec les nouvelles positions
            Cellule *c = new Cellule(p);
            c->copieListeCoupsPossibles(dernierCSP);

            dernierCSP->setCSP(c);
            k->setCSE(c);
            c->setCPP(dernierCSP);
            c->setCPE(k);

            k=c;

            // On déplace juste la Tour (on a déplacé le Roi auparavant)
            /* Cas ou le Roi Blanc Roque */
            if(p->getNomString() == "Roi" && descCoup[3] == "g8" && (Point(8,7)-convertPositionToPoint(getDernierCSP(p->getFirstCell())->getCPP()->getPositionCell())).getY() == 2){ // Petit Roque

                Piece *t = existePieceSurPosition("h8"); // La Tour en h8 qu'on bouge (elle existe forcément car si le roi possède g8 dans sa LCP alors beaucoup de conditions ont été vérifié au préalable)
                t->setPostion("f8"); // On déplace la tour en f8

                // On s'occupe des cellules de la Tour
                Cellule *deplacementTour = new Cellule(t); // On créer la Cellule avec la nouvelle position de la tour qu'on chaine à sa LCP
                Cellule *tmp = getDernierCSP(t->getFirstCell()); // On récupère la dernière cellule CSP de la tour et on effectue le chainage

                tmp->setCSP(deplacementTour);
                deplacementTour->setCPP(tmp);
                deplacementTour->copieListeCoupsPossibles(tmp);

            }
            else if(p->getNomString() == "Roi" && descCoup[3] == "c8" && (convertPositionToPoint(getDernierCSP(p->getFirstCell())->getCPP()->getPositionCell())-Point(8,3)).getY() == 2){ // Grand Roque

                Piece *t = existePieceSurPosition("a8"); // La Tour en a8 qu'on bouge (elle existe forcément car si le roi possède g1 dans sa LCP alors beaucoup de conditions ont été vérifié au préalable)
                t->setPostion("d8"); // On déplace la tour en d8

                // On s'occupe des cellules de la Tour
                Cellule *deplacementTour = new Cellule(t); // On créer la Cellule avec la nouvelle position de la tour qu'on chaine à sa LCP 
                Cellule *tmp = getDernierCSP(t->getFirstCell()); // On récupère la dernière cellule CSP de la tour et on effectue le chainage

                tmp->setCSP(deplacementTour);
                deplacementTour->setCPP(tmp);
                deplacementTour->copieListeCoupsPossibles(tmp);

            }
            
            updateListeCoupsPossiblesAll(true); // Vu qu'on déplace une piece, on met à jour la liste des coups possibles de toutes les pièces
        }
    }
    else if(descCoup[0] == "Pion" && couleur == "Noir"){

        Cellule *dernierCSP = getDernierCSP(p->getFirstCell());

        Position pos = Position(descCoup[3]); // On stock la position initiale de la pièce
        
        Piece *p2(NULL); // On récupère la pièce qui se situe sur le déplacement

        bool prendEnPassant = false;
            
        if(existePieceSurPosition(descCoup[3])){
            p2 = existePieceSurPosition(descCoup[3]);
            seFaitMangerPiece(p2); // Si une pièce est présente sur la position du déplacement, alors elle se fait manger

            descCoup[1] = p->getPosition().getColonne(); // On précise de quelle colonne il s'agit
            descCoup[6] = "x"; // On rajoute le "x" étant donné qu'une pièce se fait manger
        }
        else if(existePieceSurPosition(convertPointToPosition(convertPositionToPoint(descCoup[3])+Point(1,0))) && existePieceSurPosition(convertPointToPosition(convertPositionToPoint(descCoup[3])+Point(1,0)))->getCouleur() == "Blanc" && existePieceSurPosition(convertPointToPosition(convertPositionToPoint(descCoup[3])+Point(1,0)))->getNomString() == "Pion"){
            // Cas ou on prend en passant
            p2 = existePieceSurPosition(convertPointToPosition(convertPositionToPoint(descCoup[3])+Point(1,0)));
            cout << "Prise en passant : " << endl;
            seFaitMangerPiece(p2);
            prendEnPassant = true;

            descCoup[1] = p->getPosition().getColonne(); // On précise de quelle colonne il s'agit
            descCoup[6] = "x"; // On rajoute le "x" étant donné qu'une pièce se fait manger
        }

        p->setPostion(descCoup[3]); // on déplace la pièce
        updateListeCoupsPossiblesAll(false); // Vu qu'on déplace une piece, on met à jour la liste des coups possibles de toutes les pièces
        
        if(estEnEchecRoi("Noir")){
            // Si malgré le déplacement de la pièce, le roi est toujours en échec (ou devient en échec) alors on annule le déplacement de la pièce
            // et on ne créé pas de nouvelle cellule

            p->setPostion(pos.getCoord());

            if(p2 != NULL){
                if(!prendEnPassant){
                    annulationSeFaitMangerPiece(p2, descCoup[3]);

                    descCoup[1] = ""; // On enlève la précision de la colonne
                    descCoup[6] = ""; // On enlève le "x"
                }
                else{
                    annulationSeFaitMangerPiece(p2, convertPointToPosition(convertPositionToPoint(descCoup[3])+Point(1,0)));
                    
                    descCoup[1] = ""; // On enlève la précision de la colonne
                    descCoup[6] = ""; // On enlève le "x"
                }
            }

            updateListeCoupsPossiblesAll(false);
            cout << "\n[i] " << p->getNomString() << " " << p->getCouleur() << " ne peut pas être déplacé en " << descCoup[3] << " car sinon son Roi est (ou reste) en échec.\n" << endl;
        }
        else{
            // Cas ou le déplacement d'une piece entraine le fait que le Roi Blanc n'est plus en échec
            // Dans cette situation tout se déroule comme quand le Roi n'est pas en échec

            p->setPostion(descCoup[3]); // on déplace la pièce


            // S'il y a une promotion
            if(p->getPosition().getLigne() == "1" && descCoup[4] != ""){
                cout << "--> Promotion du pion noir en " << descCoup[3] << endl;
                p->setNom(descCoup[4]);
            } 
            
            // On créé une nouvelle cellule contenant la pièce avec les nouvelles positions
            Cellule *c = new Cellule(p);
            c->copieListeCoupsPossibles(dernierCSP);

            dernierCSP->setCSP(c);
            k->setCSE(c);
            c->setCPP(dernierCSP);
            c->setCPE(k);

            k=c;
            updateListeCoupsPossiblesAll(true); // Vu qu'on déplace une piece, on met à jour la liste des coups possibles de toutes les pièce
        }
    }
}


/*
*   verificationDeplacementPiece a pour but de corriger les erreurs de notations avec déplacement correcte, 
*   ex : exf5 et le joueur note seulement f5
*   ex : C3xf5 et le joueur note seulement Cf5
*
*   Ça fonctionne pour le moment pour les Pions (rajoute le "x" s'il mange + précise la colonne), ça rajoute le "x" pour les pièces également.
*   Néanmoins c'est toujours pas fonctionnel dans le cas plus compliqué ou 2 pièces peuvent se déplacer au même endroit et que l'on doit déterminer de quelle pièce il s'agit...
*   
*/

// Traitement de : Erreur de notation (déplacement correct)
void verificationDeplacementPiece(Cellule* &k, string coup, string couleur, vector<string> &descCoup, int nbCoup, lectureFichier* File){

    // k correspond au pointeur CSE qui permet de définir la liste chainée des Coups Suivants Échiquier (passage de pointeur par référence)

    vector<string> descCoupCorrection;

    string typePiece = "";

    if(descCoup[0] == "Pion")
        typePiece = "";
    else if(descCoup[0] == "Roi")
        typePiece = "R";
    else if(descCoup[0] == "Dame")
        typePiece = "D";
    else if(descCoup[0] == "Fou")
        typePiece = "F";
    else if(descCoup[0] == "Cavalier")
        typePiece = "C";
    else if(descCoup[0] == "Tour")
        typePiece = "T";

    //separator();
    //separator();
    //cout << "Le coup joué est : " << coup << endl;

    descCoupCorrection.push_back(descCoup[0]); // Piece
    descCoupCorrection.push_back(descCoup[1]); // Colonne
    descCoupCorrection.push_back(descCoup[2]); // Ligne
    descCoupCorrection.push_back(descCoup[3]); // Deplacement
    descCoupCorrection.push_back(descCoup[4]); // Promotion
    descCoupCorrection.push_back(descCoup[5]); // Echec
    descCoupCorrection.push_back(descCoup[6]); // Mange une pièce


    vector<Piece*> piecesDeplacables;
    vector<Piece*> piecesAmbigues;

    for(Piece* p : getListePiece()){
        if(p->getCouleur() == couleur && p->getNomString() == descCoup[0] && ((descCoup[1] == "" || p->getPosition().getColonne() == descCoup[1]) && (descCoup[2] == "" || p->getPosition().getLigne() == descCoup[2])) && appartientLCP(p, descCoup[3])){
            piecesDeplacables.push_back(p);
        }
    }
    
    //Créer une pièce (l.436) provoque un core dumped, on ne sait pourquoi//
    /*if(piecesDeplacables.size() == 0){
      if (typePiece == "" && couleur == "Noir"){
        Piece *PbFaux = new Pion(Noir, type::Pion, descCoup[3]);
        Cellule* Fausse = new Cellule(PbFaux);
        getListeCellule().push_back(Fausse);
      }
    }*/
    
    
    if(piecesDeplacables.size() == 1){ // Si une seule pièce peut se déplacer sur la position donnée, on la déplace
        deplacementPiece(piecesDeplacables[0], k, coup, couleur, descCoupCorrection, nbCoup);
        cout << "Coup : " << coup << " | Position curseur : " << File->getFlux()->tellg() << endl << endl;
    }
    else{
      for(Piece *p : piecesDeplacables){
        piecesAmbigues.push_back(p);
      }

      if(File->getFlux()->tellg() == -1){
        cout << "Le coup ambigu est : " << coup << " | Position curseur : " << File->getFlux()->tellg() << " | c-a-d : " << File->getLigne().size() << endl << endl;
      }
      else{
        cout << "Le coup ambigu est : " << coup << " | Position curseur : " << File->getFlux()->tellg() << endl << endl;
      }

    }

    //cout << "Après correction le coup est : " << typePiece + descCoupCorrection[1] + descCoupCorrection[2] + descCoupCorrection[6] + descCoupCorrection[3] + descCoupCorrection[4] + descCoupCorrection[5] << endl;
    //separator();
    //separator();

    descCoupCorrection.clear();
}

void coupOublie(Cellule* cell){

  Cellule* CAT;

  //Ce bloc permet de retrouver la cellule vierge dans la liste de toutes les cellules.//
  for (Cellule* C : getListeCellule()){
    if(C->getVeracite() == "Incertain"){
      CAT = C; //CAT = Cellule A Traité
      cout<<"Cellule à traité à l'adresse :"<<CAT<<endl;
      break;
    }
  }

  //Ce bloc devait servir à tester pour chaque pièce pour chaque position de la cellule vierge, si la partie est juste alors l'ensemble pièce/position est une possibilité, mais le fait qu'on ne puisse détecter un coup faux rend invalide ce bloc (erreur ligne 436)//

  /*for (Piece* P : getListePiece()){
    for (Position pos : P->getListeCoupsPossibles()){
      CAT->setPiece(P);
      CAT->setPosition();
    }
    CAT->setPiece(P);
  }*/
}

//renvoie 1 si la partie est juste , 0 sinon
int PartieJuste(Cellule* cell){
  for (Cellule* C : getListeCellule()){
    if(C->getVeracite() != "Vrai"){
      return 0;
    }
  }
  return 1;
}

void affichagePartieJuste(Cellule* cell){
  if(PartieJuste(cell)){
    cout<<"La partie est correctement notée."<<endl;
  }
  else{
    cout<<"Il y a une erreur dans la notation de la partie."<<endl;
  }
}
