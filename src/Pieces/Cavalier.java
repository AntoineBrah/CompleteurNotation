package Pieces;

public class Cavalier extends Piece{
	private static Famille famille = Famille.CAVALIER;
	private char id;
	
	public Cavalier(Couleur c, int x, int y) {
		super(c, x, y);
		
		switch(c) {
			case BLANC:
				this.id = '♘';
				break;
			case NOIR:
				this.id = '♞';
				break;		
		}
	}
	
	public char getId() {
		return this.id;
	}
	
}
