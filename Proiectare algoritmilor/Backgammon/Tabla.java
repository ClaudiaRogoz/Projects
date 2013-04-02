
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;




public class Tabla {
	private final static Integer  DIMTABLA = 25;
	final static Integer N = 1;
	final static Integer A = 0;
	final static Integer G = -1;
	private Coloana[] tabla;
	private int scoaseA;
	private int scoaseN;
	public Tabla() {
		tabla = new Coloana[getDimtabla() +1 ];
		for(int i = 0;i <= getDimtabla() ; i++){
			tabla[i] = new Coloana(0,G);
		}
		tabla[0] = new Coloana(0, N);
		tabla[25] = new Coloana(0, A);
		tabla[24] = new Coloana(2 , A);
		tabla[19] = new Coloana(5 , N);
		tabla[17] = new Coloana(3, N);
		tabla[13] = new Coloana(5, A);
		tabla[12] = new Coloana(5, N);
		tabla[8] = new Coloana(3, A);
		tabla[6] = new Coloana(5, A);
		tabla[1] = new Coloana(2, N);
		setScoaseA(0);
		setScoaseN(0);
	}
	
	public Tabla(Coloana[] t){
		tabla = t;
	}
	/**
	 * Functie care baga piesele de pe bara 
	 * @param init de unde pleaca
	 * @param dist distanta 
	 * @param color culoare pul-ului 
	 * @return
	 */
	public boolean bara(Integer init,Integer dist, Integer color){
		
		
		if(init == 0 && color == N && tabla[0].getPiese()!=0){
			int next = dist;
			if(tabla[next].getColor() == A){
				if(tabla[next].getPiese()==1){
					
					tabla[25].setPiese(tabla[25].getPiese()+1);
					tabla[25].setColor(A);
					if(!sterge(init, color)){
						return false;
					}
					tabla[next] = new Coloana(1, color);
				
				}else
					
				return false;
				
			}else if(tabla[next].getColor() == N){
				if(!sterge(init, color)){
					return false;
				}
				tabla[next].setPiese(tabla[next].getPiese()+1);
				
			}else if(tabla[next].getColor() == G){
				if(!sterge(init, color)){
					return false;
				}
				tabla[next] = new Coloana(1, color);
			}
		}else if(init == 25 && color == A && tabla[25].getPiese()!=0){
			int next = 25 - dist;
			if(tabla[next].getColor() == N){
				if(tabla[next].getPiese()==1){
					
					tabla[0].setPiese(tabla[0].getPiese()+1);
					tabla[0].setColor(N);
					if(!sterge(init, color)){
						return false;
					}
					tabla[next] = new Coloana(1, color);
				
				}else
					
				return false;
				
			}else if(tabla[next].getColor() == A){
				if(!sterge(init, color)){
					return false;
				}
				tabla[next].setPiese(tabla[next].getPiese()+1);
				
			}else if(tabla[next].getColor() == G){
				if(!sterge(init, color)){
					return false;
				}
				tabla[next] = new Coloana(1, color);
			}
		}
		return true;
	}
	
	/**
	 * functie care verifica ce tip de mutare trebuie sa se efectueze 
	 * @param init de unde pleaca
	 * @param dist distanta 
	 * @param color culoarea 
	 * @return
	 */
	public boolean move(Integer init ,Integer dist,Integer color){
		if(init == 0 || init == 25){
			return bara(init, dist, color);
		}
		else return makeMove(init, dist, color);
	}
	
	/**
	 * functie care sterge o piese de pe pozitia init 
	 * @param init de unde sterge
	 * @param color ce culoare
	 * @return returneaza daca s-a efectuat cu succes sau nu 
	 */
	public boolean sterge(Integer init,Integer color){
		
		if(tabla[init].getColor() == color){
			if(tabla[init].getPiese() > 1){
				tabla[init] = new Coloana(tabla[init].getPiese()-1,tabla[init].getColor());
			}
			else {
				tabla[init] = new Coloana(0,G);
				
			}
		} else{
			return false;
		}
		return true;
	}

	public int[] goodZar(Zar zar,int color){
		int[] ok;
		if(zar.dubla()){
			HashMap<Tabla, Integer[]> all = new HashMap<Tabla, Integer[]>();
			all = this.allPosMov(zar.getZ1(), color);
			// daca nu exista nici o mutare valida 
			if(all.isEmpty()){
				return new int[0];
			}else{
				return zar.getVect();
			}
		}else{
			// mutarilepentru primul zar
			HashMap<Tabla, Integer[]> all1 = new HashMap<Tabla, Integer[]>();
			all1 = this.allPosMov(zar.getZ1(), color);
			HashMap<Tabla, Integer[]> all2 = new HashMap<Tabla, Integer[]>();
			all2 = this.allPosMov(zar.getZ2(), color);
			// daca nu exista nici o mutare valida pentru primul verificam pentru aldoilea 
			if(all1.isEmpty()){
				
				// daca nu este nici pentru al doilea returnam vid altfel cautam o mutare valida pentru primul zar in mutarile celui de-al doilea 
				if(all2.isEmpty()){
					return new int[0];
				}else{
					Iterator<Tabla> it = all2.keySet().iterator();
					
					while(it.hasNext()){
						Tabla t = it.next();
						HashMap<Tabla, Integer[]> all3 = new HashMap<Tabla, Integer[]>();
						all3 = t.allPosMov(zar.getZ1(), color);
						if(!all3.isEmpty()){
							ok = new int[2];
							ok[0]= zar.getZ2();
							ok[1]= zar.getZ1();
							return ok;
						}
					}
					ok = new int[1];
					ok[0] = zar.getZ2();
					return ok;
				}
					
			}else if(all2.isEmpty()){
				
				if(all1.isEmpty()){
					return new int[0];
				}else{
					
					Iterator<Tabla> it = all1.keySet().iterator();
					
					while(it.hasNext()){
						Tabla t = it.next();
						HashMap<Tabla, Integer[]> all3 = new HashMap<Tabla, Integer[]>();
						all3 = t.allPosMov(zar.getZ2(), color);
						if(!all3.isEmpty()){
							ok = new int[2];
							ok[0]= zar.getZ1();
							ok[1]= zar.getZ2();
							return ok;
						}
					}

					ok = new int[1];
					ok[0] = zar.getZ1();
					return ok;
				}
			}else{
				return zar.getVect();
			}
		}
		

	}
	
	/**
	 * mutarea propriu zisa pentru un caz normal
	 * @param init de unde pleaca
	 * @param dist ce distanta
	 * @param color culoare
	 * @return succes sau nu 
	 */
	public boolean makeMove(Integer init ,Integer dist,Integer color){
		if(!(dist > 0 && dist <=6)){
			return false;
		}
		
		int next = 0;
		int othercolor = color == N ? A : N;
		int scos = color == 1 ? 25 : 0;
		// daca jucatorul este negru 
		if(color == N){
			next = init+dist;
		}
		else 
			if(color == A)
				next = init - dist;
		
		
			if(next > 0 && next < 25){
				// daca au aceeasi culoare ok
				if(tabla[next].getColor() == color){
					if(!sterge(init, color)){
						return false;
					}
					tabla[next].setPiese(tabla[next].getPiese()+1);
					
				}else{
					//daca au culoare diferita
					if(tabla[next].getColor() == othercolor){
						// daca nr de piese este 1 poate fi scoasa 
						if(tabla[next].getPiese() == 1){
							// scoatem piesa si adaugam noua piesa
							if(!sterge(init, color)){
								return false;
							}
							tabla[scos] = new Coloana(tabla[scos].getPiese()+1,tabla[next].getColor());
							
							tabla[next] = new Coloana(1,color);
							
						} else 
							//daca are mai multe piese miscare eronata
							if (tabla[next].getPiese() > 1 ){
							
								return false;
								
							}
					} else {
						// daca este goala coloana
						if(tabla[next].getColor() == G){
							if(!sterge(init, color)){
								return false;
							}
							tabla[next].setColor(color);
							tabla[next].setPiese(1);
						
						}else {
						
							return false;
							
						}
					}
				}
				
			}else if(next <= 0 && color == A) {
				
				if(tabla[25].getPiese()==0 && inCasa(color)){
					if(!sterge(init, color)){
						System.out.println("????????");
						return false;
					}
					setScoaseA(getScoaseA() + 1);
				
				}else
				
					return false;
				
			}else if(next >= 25 && color == N){
				
				if(tabla[0].getPiese()==0 && inCasa(color)){
					if(!sterge(init, color)){

						System.out.println("????????");
						return false;
					}
					setScoaseN(getScoaseN()+1);
				
				}else 
				
					return false;
			}
			
		return true;
	}
	
	/**
	 * verifica daca toate piesele sunt in casa 
	 * @param color culoarea pentru care se verifica
	 * @return
	 */
	public boolean inCasa(int color){
		int sum = 0;
		
		if(color == N){
			for(int i = 19; i <=24;i++){
				if(tabla[i].getColor() == color){
					
					sum += tabla[i].getPiese();
				
				}
			}
			sum += getScoaseN();
		}else 
			if(color == A){
				for(int i = 1; i<=6 ;i++){
					if(tabla[i].getColor() == color){
						
						sum += tabla[i].getPiese();
						
					}
				}
				sum += getScoaseA();
			}
		if(sum == 15){
			return true;
		}else
			return false;
		
	}
	
	
	
	/**
	 * verifica daca sunt scoase toate piesele pentru un anumit adversar
	 * @return
	 */
	public boolean gameOver(){
		if(getScoaseA() == 15 || getScoaseN() == 15){
			return true;
		}
		return false;
	}
	
	
	/**
	 * functie care returneaza o clona pentru o tabla pentru a nu fi modificata tabla initiala 
	 */
	public Tabla clone(){
		Coloana[] t = new Coloana[DIMTABLA+1];
		for(int i = 0; i <= DIMTABLA; i++ ){
			t[i] = tabla[i].clone();
		}
		
		Tabla tab = new Tabla(t);
		return tab;
	}
	
	
	
	public boolean isPosible(int init , int dist, int color){
		int next = 0;
		int othercolor = color == N ? A : N;
		
		// daca jucatorul este negru 
		if(color == N){
			next = init+dist;
		}
		else 
			if(color == A)
				next = init - dist;
		if(next > 0 && next < 25){
			if(tabla[init].getColor() == color &&tabla[init].getPiese() > 0 ){
				if(tabla[next].getColor() == color){
					return true;
				}
				else{
					if(tabla[next].getColor() == othercolor && tabla[next].getPiese() == 1 || tabla[next].getColor() == G){
						return true;
					}else {
						return false;
					}
				}
			}else{
				return false;
			}
		} else {
			if(this.inCasa(color)){
				return true;
			}else{
				return false;
			}
		}
		
	}
	

	/**
	 * returneaza toate posibilitatile de mutari pentru zar
	 * @param zar zarul
	 * @param color color 
	 * @return toate tablele modificate
	 */
	public HashMap<Tabla, Integer[]> allPosMov(int zar, int color){
		HashMap<Tabla, Integer[]> table = new HashMap<Tabla,Integer[]>();
		
			for(int i = 0; i <= 25 ; i++){
				
				if(tabla[i].getColor() == color && tabla[i].getPiese() !=0){
					//System.out.println("coloana " + i + "si piese " + tabla[i].getPiese() );
					if(this.isPosible(i, zar, color)){
						
						Tabla x = this.clone();
						if(x.move(i, zar, color)){
							Integer[] moves = new Integer[2];
							moves[0] = i;
							moves[1] = zar;
							table.put(x,moves);
						
						}else{
							
							return null;
						}
					}
				}
			}
		
		return table;
	}
	/**
	 * functie care ia cele mai bune mutari
	 * @param t tabla initiala
	 * @param z2 zarul care s-a dat
	 * @param color culoarea jucatorului 
	 * @return Perechi de mutari
	 */
	public ArrayList<Pair<Integer, Integer>> bestMove(Tabla t,int[] z2,int color){
		int[] z = z2;
		
		System.out.println("In bestMove avem lungimea " + z.length);
		
		ArrayList<Pair<Integer, Integer>> moves = new ArrayList<Pair<Integer, Integer>>();
		Arbore x = new Arbore(t, color);
		Arbore maxi = new Arbore(t, "INIT", 0);
		// pentru fiecare zar facem toate posibilitatile si alegem cea mai buna mutare 
		for(int i = 0; i < z.length; i++){
			
			// toate posibilitatile
			int[] z1 = new int[1];
			z1[0]= z[i];
			Arbore all = x.treeinit(maxi.tabla, color, z1,maxi );
			if(all == null){
				return null;
			}
			Iterator<Arbore> it = all.noduri.iterator();
			
			int max = Integer.MIN_VALUE;
			
			
			while(it.hasNext()){
				Arbore nxt = it.next();
				int score = Evaluation.evaluate(nxt.tabla, color);
				if(score > max ){
					max = score;
					maxi = nxt;
				}
			}
			
			System.err.println("========================= " + i + z[i]);
			System.err.println(maxi);
			System.err.println("=========================");
			moves.addAll(maxi.moves);
			
		}
		
	
		
		return moves;
		
		
	}
	
	public ArrayList<Pair<Integer, Integer>> deScos(Tabla t,Zar zar, int color ,ArrayList<Integer> xs){
		int[] z= zar.getVect();
	
		ArrayList<Pair<Integer, Integer>> moves = new ArrayList<Pair<Integer, Integer>>();
		
		int scose = color == A ? t.getTabla()[25].getPiese() : t.getTabla()[0].getPiese();
		int k = 0;
		if(t.inCasa(color) && scose == 0){
			if(color == A){
				for(int i = 6; i>= 1 ; i--){
					int piese = t.getTabla()[i].getPiese();
					
					while(piese != 0 && t.getTabla()[i].getColor() == color && k < zar.length() ){
						moves.add(new Pair<Integer, Integer>(i, z[k]));
						xs.remove((Integer)z[k]);
						piese--;
						k++;
					}
				}
			}else if(color == N){
				for(int i = 19; i>= 24 ; i--){
					int piese = t.getTabla()[i].getPiese();
					
					while(piese != 0 && t.getTabla()[i].getColor() == color && k < zar.length() ){
						moves.add(new Pair<Integer, Integer>(i, z[k]));
						xs.remove((Integer)z[k]);
						piese--;
						k++;
					}
				}
			}
		}
		return moves;
	}
	
	/**
	 * functie care face o verificare suplimentara adica daca avem piese pe bara au prioritate restul d emutari fiind executate cu bestmove
	 * @param t tabla
	 * @param zar zarul 
	 * @param color culoare
	 * @return mutarile posibile
	 */
	public ArrayList<Pair<Integer, Integer>> best(Tabla t,Zar zar,int color){
		
		int[] z= zar.getVect();
		ArrayList<Integer> xs = new ArrayList<Integer>();

		for(int i = 0; i < z.length; i++){
			xs.add(z[i]);
		}
		
		ArrayList<Pair<Integer, Integer>> moves = new ArrayList<Pair<Integer, Integer>>();
		
		int scose = color == A ? t.getTabla()[25].getPiese() : t.getTabla()[0].getPiese();
		int k = 0;
		if(t.inCasa(color) && scose == 0){
			if(color == A){
				for(int i = 6; i>= 1 ; i--){
					int piese = t.getTabla()[i].getPiese();
					
					while(piese != 0 && t.getTabla()[i].getColor() == color && k < zar.length() ){
						moves.add(new Pair<Integer, Integer>(i, z[k]));
						xs.remove((Integer)z[k]);
						piese--;
						k++;
					}
				}
			}else if(color == N){
				for(int i = 19; i>= 24 ; i--){
					int piese = t.getTabla()[i].getPiese();
					
					while(piese != 0 && t.getTabla()[i].getColor() == color && k < zar.length() ){
						moves.add(new Pair<Integer, Integer>(i, z[k]));
						xs.remove((Integer)z[k]);
						piese--;
						k++;
					}
				}
			}
		}
	
	//	moves = deScos(t, zar, color, xs);
		System.out.println("Numarul de mutari valide pana acum este dupa scoatere " + moves.size());
		
		int len = z.length;
		int len1 = len;
		
		
		if(color == A && t.getTabla()[25].getPiese()!=0){
			
			int scos = t.getTabla()[25].getPiese();
			
			boolean ok = false;
			for(int i = 0 ; i < len1; i++){
				
				if(t.isPosible(25, z[i], color)){
					
					moves.add(new Pair<Integer, Integer>(25,z[i]));
					xs.remove((Integer)z[i]);
					len--;
					scos--;
					
				}
				if(scos == 0 ){
					
					ok = true;
					break;
				}
			}
			
			if(ok == false){
				
				return moves;
			}
			
		}
		else if(color == N && t.getTabla()[0].getPiese()!=0) {
			int scos = t.getTabla()[0].getPiese();
			boolean ok = false;
			
			for(int i=0;i<len1;i++){
				
				if(t.isPosible(0, z[i], color)){

					
					moves.add(new Pair<Integer, Integer>(0,z[i]));
					
					xs.remove((Integer)z[i]);
					len--;
					scos--;
					
				}
				if(scos == 0 ){
					ok = true;
				
					break;
				}
			}
			if(ok == false){
				
				return moves;
			}
			
		}
		
		System.out.println("Numarul de mutari valide pana acum este dupa bagare" + moves.size());
		
		Iterator<Integer> it = xs.iterator();
		
		 k = 0;
		int[] z2 = new int[xs.size()];
		while(it.hasNext()){
			z2[k] = it.next();
			k++;
		}
		if(len == 0){
			return moves;
		}
		
		
			
		ArrayList<Pair<Integer, Integer>> m = new ArrayList<Pair<Integer, Integer>>();
		m = bestMove(t, z2, color);
		
		if(m==null){

			System.out.println("S-a dus pe pula");
			return null;
		}
		
		moves.addAll(m);
		Iterator<Pair<Integer,Integer>> itx = moves.iterator();
		System.out.println("aicisea mutarile sunt ");
		while(itx.hasNext()){
			
			System.out.println(itx.next());
			
		}
		System.out.println("aici");
		return moves;
	}
	
	// getteri si setteri 
	
	public Coloana[] getTabla() {
		return tabla;
	}

	public void setTabla(Coloana[] tabla) {
		this.tabla = tabla;
	}


	public int getScoaseN() {
		return scoaseN;
	}


	public void setScoaseN(int scoaseN) {
		this.scoaseN = scoaseN;
	}


	public int getScoaseA() {
		return scoaseA;
	}


	public void setScoaseA(int scoaseA) {
		this.scoaseA = scoaseA;
	}
	@Override
	public String toString() {
		String s = "";
		for(int i=0 ; i<=25; i++){
			s+= String.valueOf(i) + "   " + tabla[i].toString() + "\n";
		}
		s+= "Numarul de piese scoase alb" + this.getScoaseA()+ "\n";
		s+= "Numarul de piese scoase negru" + this.getScoaseN() + "\n";
		return s;
	}

	public static Integer getDimtabla() {
		return DIMTABLA;
	}
	
}
