package Jeu;

import Pieces.*;

public class Plateau {
	private Roi j1; //Blancs
	private Roi j2; //Noirs
	private Piece[][] plateau;
	
	public Plateau(Roi joueur1, Roi joueur2) {
		this.j1 = joueur1;
		this.j2 = joueur2;
		
		plateau = new Piece[8][8];
		
		this.j1.setCoordXY(7,4);
		this.j2.setCoordXY(0,4);
		
		this.initialisationPlateau();
	}
	
	public void initialisationPlateau() {
		for(int col=0; col<plateau.length; col++) {
			for(int ligne=0; ligne<plateau.length; ligne++) {
				plateau[col][ligne] = null;
			}
		}
		
		// Initialisation des pièces du joueur blanc
		setCase(7,0, new Tour(Couleur.BLANC, 7,0));
		setCase(7,1, new Cavalier(Couleur.BLANC, 7,1));
		setCase(7,2, new Fou(Couleur.BLANC, 7,2));
		setCase(7,3, new Reine(Couleur.BLANC, 7,3));
		setCase(7,4, this.j1);
		setCase(7,5, new Fou(Couleur.BLANC, 7, 5));
		setCase(7,6, new Cavalier(Couleur.BLANC, 7, 6));
		setCase(7,7, new Tour(Couleur.BLANC, 7, 7));
		
		setCase(6,0, new Pion(Couleur.BLANC, 6, 0));
		setCase(6,1, new Pion(Couleur.BLANC, 6, 1));
		setCase(6,2, new Pion(Couleur.BLANC, 6, 2));
		setCase(6,3, new Pion(Couleur.BLANC, 6, 3));
		setCase(6,4, new Pion(Couleur.BLANC, 6, 4));
		setCase(6,5, new Pion(Couleur.BLANC, 6, 5));
		setCase(6,6, new Pion(Couleur.BLANC, 6, 6));
		setCase(6,7, new Pion(Couleur.BLANC, 6, 7));
		
		// Initialisation des pièces du joueur noir
		setCase(0,0, new Tour(Couleur.NOIR, 0,0));
		setCase(0,1, new Cavalier(Couleur.NOIR, 0,1));
		setCase(0,2, new Fou(Couleur.NOIR, 0,2));
		setCase(0,3, new Reine(Couleur.NOIR, 0,3));
		setCase(0,4, this.j2);
		setCase(0,5, new Fou(Couleur.NOIR, 0, 5));
		setCase(0,6, new Cavalier(Couleur.NOIR, 0, 6));
		setCase(0,7, new Tour(Couleur.NOIR, 0, 7));
		
		setCase(1, 0, new Pion(Couleur.NOIR, 1, 0));
		setCase(1, 1, new Pion(Couleur.NOIR, 1, 1));
		setCase(1, 2, new Pion(Couleur.NOIR, 1, 2));
		setCase(1, 3, new Pion(Couleur.NOIR, 1, 3));
		setCase(1, 4, new Pion(Couleur.NOIR, 1, 4));
		setCase(1, 5, new Pion(Couleur.NOIR, 1, 5));
		setCase(1, 6, new Pion(Couleur.NOIR, 1, 6));
		setCase(1, 7, new Pion(Couleur.NOIR, 1, 7));
		
	}
	
	public void setCase(int ligne, int col, Piece p) {
		this.plateau[ligne][col] = p;
	}
	
	public Piece getCase(int ligne, int col) {
		return this.plateau[ligne][col];
	}
	
	public String toString() {
		String s = "  0 1 2 3 4 5 6 7\n";
        for (int ligne = 0; ligne < 8; ligne++) {
            s += ligne;
            for (int col = 0; col < 8; col++) {
                if (plateau[ligne][col] != null) {
                    s += " " + plateau[ligne][col].getId();
                } else {
                    s += " -";
                }
            }
            s += "\n";
        }
        return s;
	}
}
