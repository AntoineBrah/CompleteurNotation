import Pieces.*;
import Jeu.*;

public class Main{
	
	public static void main(String[] args) {
		
		Roi j1 = new Roi(Couleur.BLANC, 7, 4);
		Roi j2 = new Roi(Couleur.NOIR, 0, 4);
		
		Plateau p = new Plateau(j1,j2);
		
		System.out.println(p.toString());
		
		
		
	}
}