package Pieces;

public class Reine extends Piece{
	private static Famille famille = Famille.REINE;
	private char id;
	
	public Reine(Couleur c, int x, int y) {
		super(c, x, y);
		
		switch(c) {
			case BLANC:
				this.id = '♕';
				break;
			case NOIR:
				this.id = '♛';
				break;		
		}
	}
	
	public char getId() {
		return this.id;
	}
}
