import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map.Entry;


public class Arbore {
	static final String  MAX = "MAX" ;
	static final String  MIN = "MIN" ;
	static final String  CHANCE = "CHANCE" ;
	static final String INIT = "INIT";
	
	ArrayList<Arbore> noduri;
	String tip;
	Tabla tabla ;
	ArrayList<Pair<Integer, Integer>> moves;
	
	Integer[] themove;
	int color;
	public Arbore(Tabla t,int color) {
		noduri = new ArrayList<Arbore>();
		tip = INIT;
		tabla = t;
		this.color = color;
		moves = new ArrayList<Pair<Integer, Integer>>();
		
	}
	
	public Arbore(Tabla t , String tip,int col){
			this.tip = tip;
			tabla = t ;
			noduri = new ArrayList<Arbore>();
			color = col;
			moves = new ArrayList<Pair<Integer, Integer>>();
			
	}
	public Arbore(Tabla t, String tip, Integer[] move,int c,ArrayList<Pair<Integer, Integer>> mov){
		this.tip = tip;
		themove = move;
		color = c;		
		tabla = t;
		moves = mov;
		noduri = new ArrayList<Arbore>();
		
	}
	/**
	 * functie care formeaza arborele 
	 * @param init tabla initiala 
	 * @param c culoarea jucatorului
	 * @param zar valorile zarului
	 * @param tree un arbore
	 * @return arborele cu toate posibiliatile in noduri 
	 */
	public Arbore treeinit(Tabla init,int c,int[] zar, Arbore tree){
		//TODO sa apelez cu good zar 
			if(zar.length == 0){
				return null;
				
				
				
				
				
				
			}else{
				
				//ArrayList<Arbore> noduri = new ArrayList<Arbore>();
				HashMap<Tabla, Integer[]> x = new HashMap<Tabla, Integer[]>();
				// generam toate posibilitatile de mutari pentru zarul 0 
				x = init.allPosMov(zar[0], c);
				if(x == null){
					return null;
				}
				// iteram pe toate posibilitatile
				
				Iterator<Entry<Tabla, Integer[]>> it = x.entrySet().iterator();
				while(it.hasNext()){
					// una din posibilitati 
					Entry<Tabla, Integer[]> nxt = it.next();
					ArrayList<Pair<Integer, Integer>> moves = new ArrayList<Pair<Integer, Integer>>();
					Pair<Integer, Integer> p = new Pair<Integer, Integer>(nxt.getValue()[0], nxt.getValue()[1]);
					moves.add(p);
					tree.moves.addAll(moves);
					Arbore nod = new Arbore(nxt.getKey(), INIT,nxt.getValue(), c,moves);
					int[] z = new int[zar.length-1];
					
					for(int i = 0;i<zar.length-1 ;i++){
						z[i] = zar[i+1];
					}
					tree.noduri.add(nod);
					//System.out.println(z[0]);
					nod.treeinit(nxt.getKey(), c, z,nod);
					
					
				}
				
			}
			
			
		
		return tree;
	}
	
	
	@Override
	public String toString() {
		return tabla.toString() + "\n" + moves.toString();
	}
	
	public void afisArb(Arbore arb,int depth ){
		System.out.println("*********************                   " + depth );
		System.out.println(arb);
		
		Iterator<Arbore> it = arb.noduri.iterator();
		while(it.hasNext()){
			afisArb(it.next(),depth +1);
		}
		
	}
	
}
