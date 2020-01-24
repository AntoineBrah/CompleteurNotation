package Pieces;

public class Fou extends Piece{
	private static Famille famille = Famille.FOU;
	private char id;
	
	public Fou(Couleur c, int x, int y) {
		super(c, x, y);
		
		switch(c) {
			case BLANC:
				this.id = '♗';
				break;
			case NOIR:
				this.id = '♝';
				break;		
		}
	}
	
	public char getId() {
		return this.id;
	}
}
