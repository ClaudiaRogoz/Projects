import java.io.File;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.RandomAccessFile;
import java.util.Arrays;
import java.util.Collections;
import java.util.HashSet;
import java.util.List;
import java.util.Set;
import java.util.concurrent.ConcurrentHashMap;

/**
 * Clasa ce reprezinta o solutie partiala pentru problema de rezolvat. Aceste
 * solutii partiale constituie task-uri care sunt introduse in workpool.
 */
class PartialSolutionMap {
	String fis;
	int start;
	int D;
	public PartialSolutionMap(String fis, int s,int D) {
		this.fis = fis;
		start = s;
		
		this.D = D;
	}
	
	public String toString() {
		return "Nume fis: " + fis + " " + start + "  ";
	}
}

/**
 * Clasa ce reprezinta un thread worker.
 */
class Worker extends Thread {
	WorkPoolMap wp;
	
	static final String delimiter = "[^a-zA-Z]+";
	public Worker(WorkPoolMap workpool) {
		this.wp = workpool;
	}

	/**
	 * Procesarea unei solutii partiale. Aceasta poate implica generarea unor
	 * noi solutii partiale care se adauga in workpool folosind putWork().
	 * Daca s-a ajuns la o solutie finala, aceasta va fi afisata.
	 */
	void processPartialSolution(PartialSolutionMap ps) {
		File file = new File(ps.fis);
		RandomAccessFile raf = null;
		try {
			 raf = new RandomAccessFile(file, "r");
		} catch (FileNotFoundException e) {
			
			e.printStackTrace();
		}
		byte[] buf = new byte[ps.D];
		
		String s = null;
		try {
			// daca este inceput de fisier nu mai prelucram inceputul 
			if(ps.start == 0){
				
				raf.seek(ps.start);
				raf.read(buf);
				s = new String(buf);
				//daca ultimul caracter nu este un delimitator atunci adaugam la s 
				// toate caracterele pana la delimitator
				if(!String.valueOf(s.charAt(s.length()-1)).matches(delimiter)){
					byte[] buff = new byte[1];
					int ok = raf.read(buff);
					String ch = new String(buff);
					while(!ch.matches(delimiter) && ok != -1){
						s = s + ch;
						buff = new byte[1];
						ok = raf.read(buff);
						ch = new String(buff);
					}
					
				}
			}else{
				raf.seek(ps.start);
				raf.read(buf);
				s = new String(buf);
				// verificam mai intai sfarsit de bloc
				if(!String.valueOf(s.charAt(s.length()-1)).matches(delimiter)){
					byte[] buff = new byte[1];
					int ok = raf.read(buff);
					String ch = new String(buff);
					while(!ch.matches(delimiter) && ok != -1){
						s = s + ch;
						buff = new byte[1];
						ok = raf.read(buff);
						ch = new String(buff);
					}
					
				}
				// verificam daca caracterul de dinainte de primul caracter din sir 
				// este delimitator iar daca nu este eliminam din sir toate caracterele
				// pana la urmatorul delimitator
				raf.seek(ps.start -1 );
				byte[] buff = new byte[1];
				raf.read(buff);
				String ch = new String(buff);
				
				if(!ch.matches(delimiter)){
					while(!String.valueOf(s.charAt(0)).matches(delimiter)){
						s = s.substring(1, s.length());
					}
				}
				
				
			}
			
		} catch (IOException e1) {
			
			e1.printStackTrace();
		}
		
		// impartim fisierul in cuvinte dupa delimitator, delimitatorii fiind orice 
		// este diferit de litere
		s = s.toLowerCase();
		String[] slices = s.split(delimiter);
		List<String> slicelist = Arrays.asList(slices);
		
		Set<String> unique = new HashSet<String>(slicelist);
		
		if(!wp.mapdocfreq.containsKey(ps.fis)){
			wp.mapdocfreq.put(ps.fis, new ConcurrentHashMap<String,Double>());
		}
		
		ConcurrentHashMap<String, Double> wordfreq = wp.mapdocfreq.get(ps.fis);
		for (String str : unique) {
			Double frq = (double) Collections.frequency(slicelist, str);
			if(wordfreq.containsKey(str)){
						Double f = wordfreq.get(str);
						
						wordfreq.put(str, f + frq);
					}else{
						
						wordfreq.put(str, frq);
						
					}
		}
			
	}

	public void run() {
		//System.out.println("Thread-ul worker " + this.getName() + " a pornit...");
		while (true) {
			PartialSolutionMap ps = wp.getWork();
			if (ps == null)
				break;

			processPartialSolution(ps);
		}
		//System.out.println("Thread-ul worker " + this.getName() + " s-a terminat...");
	}


}


class Map{
	String[] documente;
	Integer NT;
	Integer D;
	ConcurrentHashMap<String, ConcurrentHashMap<String, Double>> mapdocfreq = new ConcurrentHashMap<String, ConcurrentHashMap<String,Double>>();
	
	Map(String[] doc,Integer nt,Integer D){
		documente = doc;
		NT = nt;
		this.D = D;
	}
	
	public ConcurrentHashMap<String, ConcurrentHashMap<String, Double>> map(){
		WorkPoolMap wp = new WorkPoolMap(NT,mapdocfreq);
		for(int i = 0 ; i < documente.length; i++){
			File file = new File(documente[i]);
			int len = 0;
			int depus = D;
			int size = (int) file.length();
			
			while(size != len){
				
				PartialSolutionMap p = new PartialSolutionMap(documente[i], len, depus);
				len += depus;
				if(size - len < D){
					depus = size - len;
				}else{
					depus = D;
				}
				wp.putWork(p);
			}
		}
		
		Worker[] workeri = new Worker[NT];
		for(int i = 0; i < NT; i++){
			workeri[i] = new Worker(wp);
			workeri[i].start();
			
		}
		for(int i = 0; i < NT; i++){
			
			try {
				workeri[i].join();
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
		}
		
		return mapdocfreq;
		
	}
}
