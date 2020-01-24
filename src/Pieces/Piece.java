package Pieces;

public abstract class Piece {
	private Couleur couleur;
	private int coordX;
	private int coordY;
	
	public Piece(Couleur c, int x, int y) {
		this.couleur = c;
		this.coordX = x;
		this.coordY = y;
	}
	
	public Couleur getCouleur() {
		return this.couleur;
	}
	
	public void setCouleur(Couleur c) {
		this.couleur = c;
	}
	
	public int getCoordX() {
		return this.coordX;
	}
	
	public int getCoordY() {
		return this.coordY;
	}
	
	// x = ligne et y = colonne 
	public void setCoordXY(int x, int y) {
		this.coordX = x;
		this.coordY = y;
	}
	
	public abstract char getId();
	
	/*
	 * On doit définir le déplacement de chaque pièces
	 */
	
	
}
