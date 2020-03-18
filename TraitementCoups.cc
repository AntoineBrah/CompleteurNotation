#include "TraitementCoups.h"

void seFaitMangerPiece(Piece* p){

    cout << "[+] -> " << p->getNomString() << " " << p->getCouleur() << " en position : " << p->getPosition().getCoord() << " vient de se faire manger.\n" << endl;

    p->setPostion("NULL"); // On sort la pièce du plateau

    // On créér la cellule qui représente la mort de la pièce (Position : NULL, CSP : NULL, CSE : NULL)
    Cellule *mortPiece = new Cellule(p);
    mortPiece->setCSP(NULL);
    mortPiece->setCSE(NULL);

    Cellule *tmp = getDernierCSP(p->getFirstCell());

    mortPiece->setCPP(tmp);

    tmp->setCSP(mortPiece); // On chaine l'avant dernière cellule de la pièce avec la dernière (la dernière représentant la mort de la pièce)

    updateListeCoupsPossiblesAll(false); // On met à jour la liste des coups possibles de toutes les pièces et on vide celle de la pièce qui vient de mourir par la même occasion
}

void annulationSeFaitMangerPiece(Piece* p, Position pos){

    p->setPostion(pos.getCoord()); // On remet la pièce à sa position
    updateListeCoupsPossiblesAll(false); // On met à jour la liste des coups possibles de tout le monde

    cout << "[-] -> " << p->getNomString() << " " << p->getCouleur() << " en position : " << pos.getCoord() << " annulation du fait qu'il se soit fait manger.\n" << endl;

    Cellule *c1 = p->getFirstCell();
    Cellule *tmp = c1;
    
    while(c1->getCSP()){
        tmp = c1;
        c1 = c1->getCSP(); // c1 devient la dernière cellule des Cellules de CSP de la pièce
    }
    
    tmp->setCSP(NULL); // On enlève le lien entre l'avant dernière et la dernière cellule des CSP de la pièce
    delete c1; // On supprime la dernière cellule 
}

bool traitementCoups(lectureFichier* f){
    
    vector<Cellule*> *instancesEchiquier = initialiserCellules();

    lectureFichier *File = f;

    int nbCoup = 0;
    Cellule *k = NULL; // contient l'adresse de la cellule de CSE
    
    do{
        nbCoup++;

        string deplacementBlanc = f->getCoupBlanc();
        string deplacementNoir = f->getCoupNoir();

        if(deplacementBlanc != ""){

            if(File->getCoupBlanc().size() == 3){

                string typePiece;
                string deplacement = string{File->getCoupBlanc()[1]} + File->getCoupBlanc()[2];

                switch(File->getCoupBlanc()[0]){
                    case 'T':
                        typePiece = "Tour";
                        break;
                    case 'C':
                        typePiece = "Cavalier";
                        break;
                    case 'F':
                        typePiece = "Fou";
                        break;
                    case 'D':
                        typePiece = "Dame";
                        break;
                    case 'R':
                        typePiece = "Roi";
                        break;
                    default:
                        cout << "ERREUR : Impossible de déterminer de quelle pièce il s'agit (coup blanc)." << endl;
                        break;
                }

                for(Cellule* cell : (*instancesEchiquier)){
                    if(cell->getPiece()->getCouleur() == "Blanc" && cell->getPiece()->getNomString() == typePiece){
                        Cellule *dernierCSP = getDernierCSP(cell);

                        for(Position pos : cell->getPiece()->getListeCoupsPossibles()){
                            if(pos.getCoord() == deplacement){
                                if(nbCoup == 1){
                                    // On récupère la première pièce possèdant cette position dans sa liste des coups possibles
                                    cell->getPiece()->setPostion(deplacement); // on déplace la pièce

                                    // On créé une nouvelle cellule contenant la pièce avec les nouvelles positions
                                    Cellule *c = new Cellule(cell->getPiece());
                                    c->copieListeCoupsPossibles(dernierCSP);

                                    dernierCSP->setCSP(c);
                                    dernierCSP->setCSE(c);
                                    c->setCPP(dernierCSP);

                                    k=c;

                                    updateListeCoupsPossiblesAll(true); // Vu qu'on déplace une piece, on met à jour la liste des coups possibles de toutes les pièces
                                }
                                else{
                                    Position pos = cell->getPiece()->getPosition(); // On stock la position initiale de la pièce

                                    Piece *p = NULL; // On récupère la pièce qui se situe sur le déplacement
                                    
                                    if(existePieceSurPosition(deplacement)){
                                        p = existePieceSurPosition(deplacement);
                                        seFaitMangerPiece(p); // Si une pièce est présente sur la position du déplacement, alors elle se fait manger
                                    }

                                    cell->getPiece()->setPostion(deplacement); // on déplace la pièce
                                    updateListeCoupsPossiblesAll(false); // Vu qu'on déplace une piece, on met à jour la liste des coups possibles de toutes les pièces
                                    
                                    if(estEnEchecRoiBlanc()){
                                        // Si malgré le déplacement de la pièce, le roi est toujours en échec (ou devient en échec) alors on annule le déplacement de la pièce
                                        // et on ne créé pas de nouvelle cellule

                                        cell->getPiece()->setPostion(pos.getCoord());

                                        if(p != NULL){
                                            annulationSeFaitMangerPiece(p, deplacement);
                                        }

                                        updateListeCoupsPossiblesAll(false);
                                        cout << "\n[i] " << cell->getPiece()->getNomString() << " " << cell->getPiece()->getCouleur() << " ne peut pas être déplacé en " << deplacement << " car sinon son Roi est (ou reste) en échec.\n" << endl;
                                    }
                                    else{
                                        // Cas ou le déplacement d'une piece entraine le fait que le Roi Blanc n'est plus en échec
                                        // Dans cette situation tout se déroule comme quand le Roi n'est pas en échec

                                        cell->getPiece()->setPostion(deplacement); // on déplace la pièce
                                        
                                        // On créé une nouvelle cellule contenant la pièce avec les nouvelles positions
                                        Cellule *c = new Cellule(cell->getPiece());
                                        c->copieListeCoupsPossibles(dernierCSP);

                                        dernierCSP->setCSP(c);
                                        k->setCSE(c);
                                        c->setCPP(dernierCSP);

                                        k=c;
                                        updateListeCoupsPossiblesAll(true); // Vu qu'on déplace une piece, on met à jour la liste des coups possibles de toutes les pièces
                                    }
                                }
                            }
                        }
                    }
                }
            }
            else if(File->getCoupBlanc().size() == 2){
            // C'est donc forcément un pion blanc
                for(Cellule* cell : (*instancesEchiquier)){
                    if(cell->getPiece()->getCouleur() == "Blanc" && cell->getPiece()->getNomString() == "Pion"){
                        Cellule *dernierCSP = getDernierCSP(cell);
                        for(Position pos : cell->getPiece()->getListeCoupsPossibles()){
                            if(pos.getCoord() == deplacementBlanc){
                                if(nbCoup == 1){
                                    // On récupère la première pièce possèdant cette position dans sa liste des coups possibles
                                    cell->getPiece()->setPostion(deplacementBlanc); // on déplace la pièce

                                    // On créé une nouvelle cellule contenant la pièce avec les nouvelles positions
                                    Cellule *c = new Cellule(cell->getPiece());
                                    c->copieListeCoupsPossibles(dernierCSP);

                                    dernierCSP->setCSP(c);
                                    dernierCSP->setCSE(c);
                                    c->setCPP(dernierCSP);

                                    k=c;
                                    updateListeCoupsPossiblesAll(true); // Vu qu'on déplace une piece, on met à jour la liste des coups possibles de toutes les pièces
                                }
                                else{
                                    Position pos = cell->getPiece()->getPosition(); // On stock la position initiale de la pièce
                                    
                                    Piece *p = NULL; // On récupère la pièce qui se situe sur le déplacement

                                    bool prendEnPassant = false;
                                    
                                    if(existePieceSurPosition(deplacementBlanc)){
                                        p = existePieceSurPosition(deplacementBlanc);
                                        seFaitMangerPiece(p); // Si une pièce est présente sur la position du déplacement, alors elle se fait manger
                                    }
                                    else if(existePieceSurPosition(convertPointToPosition(convertPositionToPoint(deplacementBlanc)-Point(1,0))) && existePieceSurPosition(convertPointToPosition(convertPositionToPoint(deplacementBlanc)-Point(1,0)))->getCouleur() == "Noir" && existePieceSurPosition(convertPointToPosition(convertPositionToPoint(deplacementBlanc)-Point(1,0)))->getNomString() == "Pion"){
                                        // Cas ou on prend en passant
                                        p = existePieceSurPosition(convertPointToPosition(convertPositionToPoint(deplacementBlanc)-Point(1,0)));
                                        cout << "Prise en passant : " << endl;
                                        seFaitMangerPiece(p);
                                        prendEnPassant = true;
                                    }

                                    cell->getPiece()->setPostion(deplacementBlanc); // on déplace la pièce
                                    updateListeCoupsPossiblesAll(false); // Vu qu'on déplace une piece, on met à jour la liste des coups possibles de toutes les pièces
                                    
                                    if(estEnEchecRoiBlanc()){
                                        // Si malgré le déplacement de la pièce, le roi est toujours en échec (ou devient en échec) alors on annule le déplacement de la pièce
                                        // et on ne créé pas de nouvelle cellule

                                        cell->getPiece()->setPostion(pos.getCoord());

                                        if(p != NULL){
                                            if(!prendEnPassant)
                                                annulationSeFaitMangerPiece(p, deplacementBlanc);
                                            else
                                                annulationSeFaitMangerPiece(p, convertPointToPosition(convertPositionToPoint(deplacementBlanc)-Point(1,0)));
                                        }

                                        updateListeCoupsPossiblesAll(false);
                                        cout << "\n[i] " << cell->getPiece()->getNomString() << " " << cell->getPiece()->getCouleur() << " ne peut pas être déplacé en " << deplacementBlanc << " car sinon son Roi est (ou reste) en échec.\n" << endl;
                                    }
                                    else{
                                        // Cas ou le déplacement d'une piece entraine le fait que le Roi Blanc n'est plus en échec
                                        // Dans cette situation tout se déroule comme quand le Roi n'est pas en 
                                        
                                        cell->getPiece()->setPostion(deplacementBlanc); // on déplace la pièce
                                        
                                        // On créé une nouvelle cellule contenant la pièce avec les nouvelles positions
                                        Cellule *c = new Cellule(cell->getPiece());
                                        c->copieListeCoupsPossibles(dernierCSP);
                                        
                                        dernierCSP->setCSP(c);
                                        k->setCSE(c);
                                        c->setCPP(dernierCSP);

                                        k=c;
                                        updateListeCoupsPossiblesAll(true); // Vu qu'on déplace une piece, on met à jour la liste des coups possibles de toutes les pièces
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        // Si le tout premier coup joué (coup blanc) est faux, les listes ne peuvent pas être générées correctement
        if(nbCoup == 1 && k == NULL){
            cout << "[!] : ARRÊT DU PROGRAMME : Le premier coup de la partie (joueur blanc) étant faux, il est impossible générer la structure de chaînage correctement." << endl;
            return false;
        }

        if(deplacementNoir != ""){
            
            if(File->getCoupNoir().size() == 3){

                string typePiece;
                string deplacement = string{File->getCoupNoir()[1]} + File->getCoupNoir()[2];
                
                switch(File->getCoupNoir()[0]){
                    case 'T':
                        typePiece = "Tour";
                        break;
                    case 'C':
                        typePiece = "Cavalier";
                        break;
                    case 'F':
                        typePiece = "Fou";
                        break;
                    case 'D':
                        typePiece = "Dame";
                        break;
                    case 'R':
                        typePiece = "Roi";
                        break;
                    default:
                        cout << "ERREUR : Impossible de déterminer de quelle pièce il s'agit (coup noir)." << endl;
                        break;
                }
                
                for(Cellule* cell : (*instancesEchiquier)){
                    if(cell->getPiece()->getCouleur() == "Noir" && cell->getPiece()->getNomString() == typePiece){
                        Cellule *dernierCSP = getDernierCSP(cell);

                        for(Position pos : cell->getPiece()->getListeCoupsPossibles()){
                            
                            if(pos.getCoord() == deplacement){
                                
                                Position pos = cell->getPiece()->getPosition(); // On stock la position initiale de la pièce

                                Piece *p = NULL; // On récupère la pièce qui se situe sur le déplacement
                                    
                                if(existePieceSurPosition(deplacement)){
                                    p = existePieceSurPosition(deplacement);
                                    seFaitMangerPiece(p); // Si une pièce est présente sur la position du déplacement, alors elle se fait manger
                                }
                                

                                cell->getPiece()->setPostion(deplacement); // on déplace la pièce
                                updateListeCoupsPossiblesAll(false); // Vu qu'on déplace une piece, on met à jour la liste des coups possibles de toutes les pièces
                                
                                if(estEnEchecRoiNoir()){
                                    // Si malgré le déplacement de la pièce, le roi est toujours en échec (ou devient en échec) alors on annule le déplacement de la pièce
                                    // et on ne créé pas de nouvelle cellule

                                    cell->getPiece()->setPostion(pos.getCoord());

                                    if(p != NULL){
                                        annulationSeFaitMangerPiece(p, deplacement);
                                    }

                                    updateListeCoupsPossiblesAll(false);
                                    cout << "\n[i] " << cell->getPiece()->getNomString() << " " << cell->getPiece()->getCouleur() << " ne peut pas être déplacé en " << deplacement << " car sinon son Roi est (ou reste) en échec.\n" << endl;
                                }
                                else{
                                    // Cas ou le déplacement d'une piece entraine le fait que le Roi Blanc n'est plus en échec
                                    // Dans cette situation tout se déroule comme quand le Roi n'est pas en échec

                                    cell->getPiece()->setPostion(deplacement); // on déplace la pièce
                                    
                                    // On créé une nouvelle cellule contenant la pièce avec les nouvelles positions
                                    Cellule *c = new Cellule(cell->getPiece());
                                    c->copieListeCoupsPossibles(dernierCSP);

                                    dernierCSP->setCSP(c);
                                    k->setCSE(c);
                                    c->setCPP(dernierCSP);

                                    k=c;
                                    updateListeCoupsPossiblesAll(true); // Vu qu'on déplace une piece, on met à jour la liste des coups possibles de toutes les pièces
                                }
                            }
                        }
                    }
                }
            }
            else if(File->getCoupNoir().size() == 2){
            // C'est donc forcément un pion noir

                for(Cellule* cell : (*instancesEchiquier)){
                    if(cell->getPiece()->getCouleur() == "Noir" && cell->getPiece()->getNomString() == "Pion"){
                        Cellule *dernierCSP = getDernierCSP(cell);

                        for(Position pos : cell->getPiece()->getListeCoupsPossibles()){
                            if(pos.getCoord() == deplacementNoir){
                                Position pos = cell->getPiece()->getPosition(); // On stock la position initiale de la pièce
                                
                                Piece *p = NULL; // On récupère la pièce qui se situe sur le déplacement

                                bool prendEnPassant = false;
                                    
                                if(existePieceSurPosition(deplacementNoir)){
                                    p = existePieceSurPosition(deplacementNoir);
                                    seFaitMangerPiece(p); // Si une pièce est présente sur la position du déplacement, alors elle se fait manger
                                }
                                else if(existePieceSurPosition(convertPointToPosition(convertPositionToPoint(deplacementNoir)+Point(1,0))) && existePieceSurPosition(convertPointToPosition(convertPositionToPoint(deplacementNoir)+Point(1,0)))->getCouleur() == "Blanc" && existePieceSurPosition(convertPointToPosition(convertPositionToPoint(deplacementNoir)+Point(1,0)))->getNomString() == "Pion"){
                                    // Cas ou on prend en passant
                                    p = existePieceSurPosition(convertPointToPosition(convertPositionToPoint(deplacementNoir)+Point(1,0)));
                                    cout << "Prise en passant : " << endl;
                                    seFaitMangerPiece(p);
                                    prendEnPassant = true;
                                }

                                cell->getPiece()->setPostion(deplacementNoir); // on déplace la pièce
                                updateListeCoupsPossiblesAll(false); // Vu qu'on déplace une piece, on met à jour la liste des coups possibles de toutes les pièces
                                
                                if(estEnEchecRoiNoir()){
                                    // Si malgré le déplacement de la pièce, le roi est toujours en échec (ou devient en échec) alors on annule le déplacement de la pièce
                                    // et on ne créé pas de nouvelle cellule

                                    cell->getPiece()->setPostion(pos.getCoord());

                                    if(p != NULL){
                                        if(!prendEnPassant)
                                                annulationSeFaitMangerPiece(p, deplacementNoir);
                                        else
                                            annulationSeFaitMangerPiece(p, convertPointToPosition(convertPositionToPoint(deplacementNoir)+Point(1,0)));
                                    }

                                    updateListeCoupsPossiblesAll(false);
                                    cout << "\n[i] " << cell->getPiece()->getNomString() << " " << cell->getPiece()->getCouleur() << " ne peut pas être déplacé en " << deplacementNoir << " car sinon son Roi est (ou reste) en échec.\n" << endl;
                                }
                                else{
                                    // Cas ou le déplacement d'une piece entraine le fait que le Roi Blanc n'est plus en échec
                                    // Dans cette situation tout se déroule comme quand le Roi n'est pas en échec

                                    cell->getPiece()->setPostion(deplacementNoir); // on déplace la pièce
                                    
                                    // On créé une nouvelle cellule contenant la pièce avec les nouvelles positions
                                    Cellule *c = new Cellule(cell->getPiece());
                                    c->copieListeCoupsPossibles(dernierCSP);

                                    dernierCSP->setCSP(c);
                                    k->setCSE(c);
                                    c->setCPP(dernierCSP);

                                    k=c;
                                    updateListeCoupsPossiblesAll(true); // Vu qu'on déplace une piece, on met à jour la liste des coups possibles de toutes les pièce
                                }
                            }
                        }
                    }
                }
            }
        }

    }while(File->lireLigneSuivante());

    // On ajoute les infos de chaque cellules dans notre fichier JSON
    for(Cellule* cell : (*getListeCellule())){
        ecritureFichier(cell->getJSON() + ",");
    }

    // On efface le contenu des vectors (mémoire dynamique)
    for(Cellule* cell : (*instancesEchiquier)){
        delete cell->getPiece(); // On efface la pièce contenu dans la cellule
        delete cell; // On efface la cellule
    }
    
    instancesEchiquier->clear();

    return true;
}
