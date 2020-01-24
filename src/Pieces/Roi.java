package Pieces;

public class Roi extends Piece{
	private static Famille famille = Famille.ROI;
	private char id;
	
	public Roi(Couleur c, int x, int y) {
		super(c, x, y);
		
		switch(c) {
			case BLANC:
				this.id = '♔';
				break;
			case NOIR:
				this.id = '♚';
				break;		
		}
	}
	
	public char getId() {
		return this.id;
	}
	
}
