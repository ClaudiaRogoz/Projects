import java.util.Iterator;
import java.util.Set;
import java.util.TreeMap;


public class Correction {
	public static final int NRLET = 18;
	
	public TreeMap<Integer, TreeMap<Integer, String>> search (TreeMap<Integer, TreeMap<String, Integer>> dict, int lung,TreeMap<Integer, TreeMap<Integer, String>> result,String decorect){
		// returneaza un map cu cuvintele de dinctionar de lungimea lung in care o sa cautam rezultate pe care le vom depune in rezultat un map 
		TreeMap<String, Integer> map = dict.get(lung);
		Set<String> strings = map.keySet();
		
		Iterator<String> it = strings.iterator();
		int dist =0;
		
		while(it.hasNext()){
			String s1 = it.next();
			//calculam distanta levenshtein intre cuvantul de corectat si sirul s1 din map 
			dist = Levenshtein.getDistance( decorect , s1);
			// daca exista un rezultat mai bun decat acesta nu se va mai pune in result alfel se pune 
			if(result.isEmpty()){
				if(result.containsKey(dist)){
					
					result.get(dist).put(map.get(s1), s1);
					
				}else{
					
					TreeMap<Integer, String> tm = new TreeMap<Integer, String>();
					tm.put(map.get(s1), s1);
					result.put(dist, tm);
					
				}
			}
			else {
				if( dist <= result.firstKey()){
				
					if(result.containsKey(dist)){
						
						result.get(dist).put(map.get(s1), s1);
						
					}else{
						
						TreeMap<Integer, String> tm = new TreeMap<Integer, String>();
						tm.put(map.get(s1), s1);
						result.put(dist, tm);
						
					}
				}
			}
		}
		
		return result;
	}
	
	/**
	 * Corecteaza un singur cuvantadica ii face disntanta 
	 * @param s
	 * @param dict
	 * @return
	 */
	public Sentence corectWord(String s, TreeMap<Integer, TreeMap<String, Integer>> dict){
		int len = s.length();
		
		int x = dict.size();
		if(len >= x ){
			len = x-1;
		}
		int i = len ,j = len;
		//TreeMap<Integer, String> best = new TreeMap<Integer,String>();

		// se vor retine rezultatele cele mai bune
		TreeMap<Integer, TreeMap<Integer, String>> result = new TreeMap<Integer, TreeMap<Integer,String>>();
		
		// parcurgem dictionarul pana cand gasim un cuvant cu distanta 1 pentru o lungime a sirului de +1 sau -1 
		// daca nu gasim atunci marim pe j si miscoram pe i parcurgand astfel atat stringurile care au lungime 
		// mai mare ca len si mai mic ca len  din dictionar. 
		
		while(j <= len +2){
			
			if(i == j){
				
				result = this.search(dict, i, result, s);
				if(i!=1&&j!=1){
					result = this.search(dict, i-1, result, s);
					result = this.search(dict, j+1, result, s);
				}
				
				if(result.containsKey(0)){
					return new Sentence(result.get(0).lastEntry().getValue(),0,result.get(0).lastEntry().getKey(),0);
				}else
					if(result.containsKey(1)){
						return new Sentence(result.get(1).lastEntry().getValue(),1,result.get(1).lastEntry().getKey(),0);
					}
				
				i = -1;
				j +=2;
				
			}else{
				
				if(i > 0 && j < x){
					result = this.search(dict, i, result, s);
					result = this.search(dict, j, result, s);
					if(result.containsKey(1)){
						return new Sentence(result.get(1).lastEntry().getValue(),1,result.get(1).lastEntry().getKey(),0);
					}
					i--;
					j++;
				}else {
					if(i > 0 ){
						
						result = this.search(dict, i, result, s);
						if(result.containsKey(1)){
							return new Sentence(result.get(1).lastEntry().getValue(),1,result.get(1).lastEntry().getKey(),0);
						}
						i--;
						
					}else {
						if(j < x){
							result = this.search(dict, j, result, s);
							if(result.containsKey(1)){
								return new Sentence(result.get(1).lastEntry().getValue(),1,result.get(1).lastEntry().getKey(),0);
							}
							j++;
						}else {
							break;
						}
					}
				}
				
			}
			
		}	
		
		return new Sentence(result.firstEntry().getValue().lastEntry().getValue(),result.firstEntry().getKey(),result.firstEntry().getValue().lastEntry().getKey(),0);
		
	}
	/**
	 * functie care corecteaza cuvanta cu cuvanta nu prea este folositoare 
	 * @param s
	 * @param dict
	 * @return
	 */
	public String corectSentenceS(String s ,TreeMap<Integer, TreeMap<String, Integer>> dict ){
		String[] split;
		split = s.split(" ");
		int i;
		String rez =  "";
		for(i = 0; i < split.length; i++){
			rez += corectWord(split[i], dict) + " ";
		}
		
		return rez.substring(0, rez.length()-1);
	}
	/**
	 * combina doua Sentence adica le aduna distantele si frecventa concateneaza stringurile si mareste numarul de cuvinte 
	 * @param s1
	 * @param s2
	 * @return
	 */
	public Sentence combina(Sentence s1 , Sentence s2){
		Sentence rez = new Sentence();
		rez.setDistance(s1.getDistance() + s2.getDistance());
		rez.setFreq(s1.getFreq()+ s2.getFreq());
		rez.setNrwords(s1.getNrwords()+ s2.getNrwords());
		rez.setSentence(s1.getSentence() + " " + s2.getSentence());

		return rez;
	}
	/**
	 * functie care elimina spatiile si apeleaza corectSentenceWS
	 * @param s
	 * @param dict
	 * @return
	 */
	public Sentence corectAnything (String s,TreeMap<Integer, TreeMap<String, Integer>> dict){
		String[] str = s.split(" ");
		String rez = new String();
		for(int i = 0; i < str.length; i++){
			rez += str[i];
		}
		Sentence finalrez = new Sentence();
		finalrez = corectSentenceWS(rez, dict);
		return finalrez;
	}

	/**
	 * Functie care corecteaza o propozitie fara spatii
	 * @param s stringul de corectat
	 * @param dict dictionarul
	 * @return un Sentence ce contine sirul corectat si distanta,frecventa,nrdecuv
	 */
	public Sentence corectSentenceWS(String s,TreeMap<Integer, TreeMap<String, Integer>> dict){
		int len = s.length();
		
		Sentence[][] propz = new Sentence[len][len];
		for(int i = 0; i < len ;i++){
			for(int j = 0; j < len ; j++){
				propz[i][j] = new Sentence();
			}
		}
	
		// parcurgem o matrice formata din propozitii si formam pe parcurs in functie de rezultatele intermediare adica de ex pentru linia i 
		// ne folosim de cel mai bun rezultat de pe coloana i-1 in final rezultatul fiind unul din cele de pe ultima coloana 
		//long x = System.currentTimeMillis();
		for(int i = 0;i < len;i++){
			Sentence best = null;
			//verificam daca i > 0 adica pentru linii mai mari de 0 calculam in functie de rezultatele precendete 
			// pentru prima linie calculam rezultatul pe poz i,j doar ca substring,
			if(i > 0){
				
				best = propz[0][i-1];
				// daca i este mai mare decat 0 atunci trebuie sa calculam elementele de pe pozitiile i [i..len] in functie de 
				// un maxim pana acum adica cea mai buna alegere de concatenare
				
				for(int k = 1; k < i; k++){
					
					if(best.getDistance() > propz[k][i-1].getDistance()){
						
						best = propz[k][i-1];
						
					}else{
						
						if(best.getDistance() == propz[k][i-1].getDistance()){
							
							if(best.getNrwords() > propz[k][i-1].getNrwords()){
								
								best = propz[k][i-1];
								
							}else{
								
								if(best.getNrwords() == propz[k][i-1].getNrwords()){
									
									if(best.getFreq() < propz[k][i-1].getFreq()){
										
										best = propz[k][i-1];
										
									}else{
										if(best.getFreq() == propz[k][i-1].getFreq()){
											if(best.getSentence().compareTo(propz[k][i-1].getSentence()) > 0 ){
												
												best = propz[k][i-1];
											}
										}
									}

								}
							}
						}
					}
				}
				
			}
			
			
			
			
			
			for(int j = i; j < len; j++ ){
				
				String substr = s.substring(i,j+1);
				
				
				if(j+1 - i < NRLET){
					Sentence result = this.corectWord(substr, dict);
					
					result.setNrwords(1);
					propz[i][j] = result;
				}else{
					propz[i][j] = propz[i][j-1];
				}
				
				if(i>0){
					
					propz[i][j] = combina(best, propz[i][j]);
					
					
				}
				
			}
		}
		
		//calculam maximul global la fel cum calculam si maxim de pe coloana
		Sentence globalbest = propz[0][len-1];
	
		for(int i = 1; i < len ;i++){
			if(globalbest.getDistance() > propz[i][len-1].getDistance()){
				
				globalbest = propz[i][len-1];
				
			}else{
				
				if(globalbest.getDistance() == propz[i][len-1].getDistance()){
					
					if(globalbest.getNrwords() > propz[i][len-1].getNrwords()){
						
						globalbest = propz[i][len-1];
						
					}else{
						
						if(globalbest.getNrwords() == propz[i][len-1].getNrwords()){
							
							if(globalbest.getFreq() < propz[i][len-1].getFreq()){
								
								globalbest = propz[i][len-1];
								
							}else{
								if(globalbest.getFreq() == propz[i][len-1].getFreq()){
									
								if(globalbest.getSentence().compareTo(propz[i][len-1].getSentence()) > 0 ){
									
									globalbest = propz[i][len-1];
								}
								}
							}

						}
					}
				}
			}
		}
		
		
	
		
		return globalbest;
		
	}
	
	
}
