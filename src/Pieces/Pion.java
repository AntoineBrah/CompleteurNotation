package Pieces;

public class Pion extends Piece{
	private static Famille famille = Famille.PION;
	private char id;
	
	public Pion(Couleur c, int x, int y) {
		super(c, x, y);
		
		switch(c) {
			case BLANC:
				this.id = '♙';
				break;
			case NOIR:
				this.id = '♟';
				break;		
		}
	}
	
	public char getId() {
		return this.id;
	}
}
