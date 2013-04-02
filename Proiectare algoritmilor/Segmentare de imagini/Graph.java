import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.ObjectInputStream.GetField;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.Map.Entry;
import java.util.Queue;
import java.util.Scanner;
import java.util.Set;
import java.util.Vector;


public class Graph {
	private ArrayList<Integer> vertices;
	private ArrayList<Muchie> edges;
	private HashMap<Integer, ArrayList<Muchie>> adjList ;
	private int size;
	private int[] parents;
	private int n;
	private int m;
	public	int sursa;
	public int drena;
	public final static int UNDEFINED = Integer.MAX_VALUE;	
	public Graph() {
		setVertices(new ArrayList<Integer>());
		setEdges(new ArrayList<Muchie>());
		setAdjList(new HashMap<Integer, ArrayList<Muchie>>());
		
	}
	
	public void clearParents() {
		  for (int i = 0; i <= size+1; i++) {
		      parents[i] = UNDEFINED;
		  }
	}
	
	/**
	 * functie care construieste graful fara sursa si drena 
	 * @param n
	 * @param m
	 * @param image
	 * @param treshold
	 * @param lambda
	 */
	public void makeGraph(int n ,int m, int[] image,int treshold,int lambda,double niuf , double niub , double sigmaf , double sigmab){
		this.n = n;
		this.m = m;
		this.setSize(n *m +1);
		sursa = m*n;
		drena = m*n+1;
		setParents(new int[size+2]);
		clearParents();
		for(int i = 0 ; i < n*m ;i++){
			// calculam toti potentialii vecini pentru pixelul i 
			int sus = i - n;
			int jos = i + n;
			int stg = i - 1;
			int drp = i + 1;
			addMuchieSus(sus, n, m, image, lambda, i, treshold);
			addMuchieJos(jos, n, m, image, lambda, i, treshold);
			addMuchieStg(stg, n, m, image, lambda, i, treshold);
			addMuchieDrp(drp, n, m, image, lambda, i, treshold);
			addMuchieSD(image, i, 1, sursa, niuf, niub, sigmaf, sigmab);
			addMuchieSD(image, i, 0, drena, niuf, niub, sigmaf, sigmab);
			
			vertices.add(i);
			
		}
	}
	/**
	 * adauga muchie intre nodul i si sursa sau drena 
	 * @param image vector de pixeli 
	 * @param i nodul
	 * @param x 0/1 
	 * @param sd sursa/drena
	 * @param niuf 
	 * @param niub
	 * @param sigmaf
	 * @param sigmab
	 */
	public void addMuchieSD(int[] image, int i, int x,int sd,double niuf , double niub , double sigmaf, double sigmab){
		double fu = Formule.fu(niuf, niub, sigmaf, sigmab, x, image[i]);
		
		if(getAdjList().containsKey(i)){
			getAdjList().get(i).add(new Muchie(i, sd, fu,image[i],1));
		}else{
			ArrayList<Muchie> vecini = new ArrayList<Muchie>();
			vecini.add(new Muchie(i, sd, fu,image[i],1));
			getAdjList().put(i, vecini);
		}
		this.edges.add(new Muchie(i,sd,fu,image[i],1));
		
		if(getAdjList().containsKey(sd)){
			getAdjList().get(sd).add(new Muchie(sd,i,fu,image[i],1));
		}else{
			ArrayList<Muchie> vecini = new ArrayList<Muchie>();
			vecini.add(new Muchie(sd, i, fu,image[i],1));
			getAdjList().put(sd, vecini);
		}
		this.edges.add(new Muchie(sd,i,fu,image[i],1));
		
	}
	/**
	 * adauga muchie intre pixelul i si vecinul de sus
	 * @param sus 
	 * @param n
	 * @param m
	 * @param image
	 * @param lambda
	 * @param i
	 * @param treshold
	 */
	public void addMuchieSus(int sus, int n, int m,int[] image,int lambda,int i,int treshold){
		//verificam daca pixelul este valid adica are un indice corect 
		if(sus >= 0){
			// daca este valid aplicam functia fp^ij(x1,x2) si daca intoarce diferit de 0 adica 
			// daca abs(Img(i) - Img(j)) <= treshold atunci adaugam muchia altfel nu
			if(Math.abs(image[i] - image[sus]) <= treshold ){
				ArrayList<Muchie> vecini = new ArrayList<Muchie>();
				vecini.add(new Muchie(i, sus, lambda,image[i],image[sus]));
				getAdjList().put(i, vecini);
				this.edges.add(new Muchie(i, sus, lambda,image[i],image[sus]));
			}
			
		}
		
	}
	
	/**
	 * adauga muchie intre nodul i si nodul de jos
	 * @param jos
	 * @param n
	 * @param m
	 * @param image
	 * @param lambda
	 * @param i
	 * @param treshold
	 */
	public void addMuchieJos(int jos, int n, int m,int[] image,int lambda,int i,int treshold){
		if(jos < n*m){
			if(Math.abs(image[i] - image[jos]) <= treshold ){
				if(getAdjList().containsKey(i)){
					getAdjList().get(i).add(new Muchie(i, jos, lambda,image[i],image[jos]));
				}else{
					ArrayList<Muchie> vecini = new ArrayList<Muchie>();
					vecini.add(new Muchie(i, jos, lambda,image[i],image[jos]));
					getAdjList().put(i, vecini);
				}
				this.edges.add(new Muchie(i, jos, lambda,image[i],image[jos]));
			}
		}
	}
	/**
	 * adauga muchie intre nodul stg si i
	 * @param stg
	 * @param n
	 * @param m
	 * @param image
	 * @param lambda
	 * @param i
	 * @param treshold
	 */
	public void addMuchieStg(int stg, int n, int m,int[] image,int lambda,int i,int treshold){
		
		if(i % n !=0 && stg >= 0 ){

			if(Math.abs(image[i] - image[stg]) <= treshold ){
				if(getAdjList().containsKey(i)){
					getAdjList().get(i).add(new Muchie(i, stg, lambda,image[i],image[stg]));
				}else{
					ArrayList<Muchie> vecini = new ArrayList<Muchie>();
					vecini.add(new Muchie(i, stg, lambda,image[i],image[stg]));
					getAdjList().put(i, vecini);
				}
				this.edges.add(new Muchie(i, stg, lambda,image[i],image[stg]));
			}
		}
	}
	/**
	 * adauga muchie intre nodul dreapta si nodul i
	 * @param drp
	 * @param n
	 * @param m
	 * @param image
	 * @param lambda
	 * @param i
	 * @param treshold
	 */
	public void addMuchieDrp(int drp, int n, int m,int[] image,int lambda,int i,int treshold){
		
		if(((i+1) % n) !=0 && drp < n*m){
	
			if(Math.abs(image[i] - image[drp]) <= treshold ){
				if(getAdjList().containsKey(i)){
					getAdjList().get(i).add(new Muchie(i, drp, lambda,image[i],image[drp]));
				}else{
					ArrayList<Muchie> vecini = new ArrayList<Muchie>();
					vecini.add(new Muchie(i, drp, lambda,image[i],image[drp]));
					getAdjList().put(i, vecini);
				}
				this.edges.add(new Muchie(i, drp, lambda,image[i],image[drp]));
				
			}
		}
		
	}
	
	/**
	 * facem bfs intre un nod u si un nod v returnand un vector de noduri de la u la v care reprezinta drumul minim 
	 * de la u la v
	 * @param g
	 * @param u
	 * @param v
	 * @return
	 */
	public static Vector<Integer> bfs (Graph g, int u, int v){
		// coada care retine toate nodurile care urmeaza a fi vizitate 
		Queue<Integer> que = new LinkedList<Integer>();
		ArrayList<Muchie> vecini = new ArrayList<Muchie>();
		Vector<Integer> drum = new Vector<Integer>();

		// adaugam in coada primul nod care va fi vizitat adica nodul de start
		que.add(u);
		g.setParent(u, -1);
		boolean ok = false;
		while(que.size() != 0){
			//scoate primul element din coada
			  Integer q = que.poll();
			  // il comparam daca este destinatia daca nu il extindem si ii adaugam vecinii in coada
			  if(q == v){
				  ok = true;
				  break;
			  }else{
				  vecini = g.getAdjList().get(q);
				  for(Muchie x : vecini ){
					  if(g.getParent(x.getV2()) == Graph.UNDEFINED && x.c > 0){
						  que.add(x.getV2());
						  g.setParent(x.getV2(), q);
					  }
				  }
			  }
			  
		  }
		  // daca nu se ajunge la nodul destinatie returnam vector gol
		  Vector<Integer> drum1 = new Vector<Integer>();
		  if(ok == false){
	
			  return drum1; 
		  }
		  
		  //returnam drumul in ordinea corecta
		  while(g.getParent(v) != -1){
			  drum.add(v);
			  v = g.getParent(v);
		  }
		  
		  drum.add(v);
		  for(int i = drum.size()-1 ; i >=0 ;i--){
			  drum1.add(drum.get(i));
		  }
			  
		  	return drum1;
		  
		  
	  }
	/**
	 * functie care satureaza un drum in graf adica calculeaza capacitatea minima pe drum si apoi saturam in graf toate nodurile din cale 
	 * iar pentru ca este graf neorientat saturam atat in lista de vecini a lui u cat si in lista de vecini a lui v 
	 * @param g
	 * @param drum
	 * @return
	 */
	public double saturate_path(Graph g, Vector<Integer> drum){
		
		double maxflow = Double.MAX_VALUE;
		
		// determinam fluxul maxim pe acel drum 
		for(int i = 0; i < drum.size()-1 ; i++){
			ArrayList<Muchie> vecini = g.getAdjList().get(drum.get(i));
			Iterator<Muchie> it = vecini.iterator();
			while(it.hasNext()){
				Muchie next = it.next();
				//daca acest vecin este urmatorul in drum 
				if(next.getV2() == drum.get(i+1)){
					// iar daca capacitatea muchiei este mai mica decat maxflow 
					if(maxflow > next.getC()){
						maxflow = next.getC();
					}
				}
			}
		}
		// saturam drumul in graf
		for(int i = 0; i< drum.size()-1; i++){
			ArrayList<Muchie> vecini = g.getAdjList().get(drum.get(i));
			ArrayList<Muchie> vecini2 = g.getAdjList().get(drum.get(i+1));
			Iterator<Muchie> it = vecini.iterator();
			while(it.hasNext()){
				Muchie next = it.next();
				//daca acest vecin este urmatorul in drum 
				if(next.getV2() == drum.get(i+1)){
					
					next.setC(next.getC() - maxflow);
					break;
				
				}
				
			}
			it = vecini2.iterator();
			while(it.hasNext()){
				Muchie next = it.next();
				//daca acest vecin este urmatorul in drum 
				if(next.getV2() == drum.get(i)){
					
					next.setC(next.getC() - maxflow);
					break;
				
				}
				
			}
		}
		
		return maxflow;
	}
	/**
	 * functie care satureaza toate drumurile de la sursa la drena din graf 
	 * adica calculeaza un drum apoi pentru acel drum apelam saturate path care satureaza acel drum 
	 * apoi urmatorul drum luat de bfs nu va mai fi acelasi pentru ca o muchi pe drumul precedent va avea 
	 * capacitatea zero pentru ca  a fost saturat
	 * @param g
	 * @param source
	 * @param sink
	 * @return
	 */
	public double max_flow(Graph g,Integer source, Integer sink){
		Vector<Integer> path ;
		double maxflow = 0;
		while(true){
			path = bfs(g,source,sink);
		
			if(path.size()== 0){
				return maxflow ;
			}
			else {
				maxflow += saturate_path(g, path);
				g.clearParents();
			}
			
		}
	}
	
	  
	/**
	 * functie care face un bfs de la sursa la drena retine toate nodurile la care se poate ajunge din sursa
	 * iar apoi scriem in fisier o cifra corespunzatoare, adica de la sursa se ajunge la toate nodurile din foreground
	 * @param source_set
	 * @param drain_set
	 */
	public void  min_cut(ArrayList<Integer> source_set, ArrayList<Integer> drain_set){
		
		Queue<Integer> que = new LinkedList<Integer>();
		Vector<Boolean> in_que = new Vector<Boolean>();
		int sursa = size;
		int drena = size+1;
		for(int i = 0; i <=size+1 ; i++){
			
			in_que.add(false);
			
		}
		int dist = in_que.size();
		in_que.set(sursa,true);
		que.add(sursa);
		System.out.println("in_que" + in_que.size());
		int u;
		
		while(!que.isEmpty()){
			u = que.poll();
			ArrayList<Muchie> vecini = getAdjList().get(u);
			Iterator<Muchie> it = vecini.iterator();
			while(it.hasNext()){
				Muchie next = it.next();
				if(next.getC() > 0 && in_que.get(next.getV2()) == false){
					in_que.set(next.getV2(), true);
					que.add(next.getV2());
				}
			}
					
		}
		
		 try {
			 
			FileWriter fstream = new FileWriter("segment.pgm");
			BufferedWriter out = new BufferedWriter(fstream);
			out.write("P2\n");
			out.write(n + " " +  m + "\n");
			out.write(255+"\n");
			System.out.println(in_que.size());
			for(int i = 0 ; i < dist-3; i++){
				if(in_que.get(i)){
					out.write(255 + " \n") ;
				}else{
					out.write(0 + " \n");
				}
			}
			out.close();
		} catch (IOException e) {
			e.printStackTrace();
			
		}
		
		
		
		
		
		
		
	}
	
	public int getSize() {
		return size;
	}

	public void setSize(int size) {
		this.size = size;
	}

	public HashMap<Integer, ArrayList<Muchie>> getAdjList() {
		return adjList;
	}

	public void setAdjList(HashMap<Integer,ArrayList<Muchie>> hashMap) {
		this.adjList = hashMap;
	}

	public ArrayList<Muchie> getEdges() {
		return edges;
	}

	public void setEdges(ArrayList<Muchie> edges) {
		this.edges = edges;
	}

	public ArrayList<Integer> getVertices() {
		return vertices;
	}

	public void setVertices(ArrayList<Integer> vertices) {
		this.vertices = vertices;
	}
	@Override
	public String toString() {
		String s = new String() ;
		Iterator<Entry<Integer, ArrayList<Muchie>>> it = getAdjList().entrySet().iterator();
		while(it.hasNext()){
			Entry<Integer, ArrayList<Muchie>> next = it.next();
			s += next.getKey().toString() + "  " + next.getValue().toString() + "\n";
			
		}
		
		return s;
	}

	public int[] getParents() {
		return parents;
	}

	public void setParents(int[] parents) {
		this.parents = parents;
	}
	
	public int getParent(int node){
		return getParents()[node];
	}
	
	public void setParent(int node,int parent){
		getParents()[node] = parent;
	}
	
}
