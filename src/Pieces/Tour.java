package Pieces;

public class Tour extends Piece{
	private static Famille famille = Famille.TOUR;
	private char id;
	
	public Tour(Couleur c, int x, int y) {
		super(c, x, y);
		
		switch(c) {
			case BLANC:
				this.id = '♖';
				break;
			case NOIR:
				this.id = '♜';
				break;		
		}
	}
	
	public char getId() {
		return this.id;
	}
}
