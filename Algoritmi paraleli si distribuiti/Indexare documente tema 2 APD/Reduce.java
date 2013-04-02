
import java.util.Comparator;
import java.util.HashMap;
import java.util.Map.Entry;
import java.util.Set;
import java.util.TreeMap;
import java.util.concurrent.ConcurrentHashMap;



/**
 * Clasa ce reprezinta o solutie partiala pentru problema de rezolvat. Aceste
 * solutii partiale constituie task-uri care sunt introduse in workpool.
 */

class PartialSolutionReduce  {
	String fis;
	ConcurrentHashMap<String, Double> wdfq ;
	Integer N;
	Integer NC;
	String[] cuvinte;
	Integer action;

	public PartialSolutionReduce(String fis,Integer nc,String[] cuv,Integer N,
			 Integer action,ConcurrentHashMap<String, Double> wdfq) {

		this.fis = fis;
		NC = nc;
		cuvinte = cuv;
		this.N = N;
		this.action = action;
		this.wdfq = wdfq;

	}


	public String toString() {
		return "Nume fis: " + fis + "  actiunea este : " + action  ;
	}
}

/**
 * Clasa ce reprezinta un thread worker.
 */
class WorkerReduce extends Thread {

	WorkPoolReduce wp;

	public WorkerReduce(WorkPoolReduce workpool) {
		this.wp = workpool;
	}

	/**
	 * Procesarea unei solutii partiale. Aceasta poate implica generarea unor
	 * noi solutii partiale care se adauga in workpool folosind putWork().
	 * Daca s-a ajuns la o solutie finala, aceasta va fi afisata.
	 */


	void processPartialSolution(PartialSolutionReduce ps){
		// sunt doua tipuri de actiuni ce pot fi facute pentru reduce
		// 1 sa se numere totalul de cuvinte, calc frecvente si calcul primele N 
		// cuvinte relevante 
		// 2 sa se verifice daca fisierul convine sau nu 
		if(ps.action == 0){
			
			ConcurrentHashMap<String, Double> wdfq = ps.wdfq;
			Set<String> keyset = wdfq.keySet();
			Double total = 0.0;
			// calculam numarul total de cuvinte 
			for(String str: keyset){
				if(str.length() > 0){
					total += wdfq.get(str);
				}else{
				}
			}
			HashMap<String, Double> wordfrq = new HashMap<String,Double>();

			for(String str : keyset){
				if(str != ""){
					Double freq =100 * (double) (wdfq.get(str)*1.0 / total);
					freq = (double)((int) (freq*100))/100;
					wordfrq.put(str,freq);
				}
			}

			Compara comp = new Compara(wordfrq);
			TreeMap<String, Double> sorted = new TreeMap<String,Double>(comp);
			sorted.putAll(wordfrq);

			ConcurrentHashMap<String,Double> finala = new ConcurrentHashMap<String,Double>();
			int i = 0;
			Set<Entry<String, Double>> entries = sorted.entrySet();
			Double previous = -1.0;
			
			for(Entry<String,Double> ent : entries){
				i++;
				String key = ent.getKey();
				Double value = ent.getValue();

				if( i > ps.N){
					if(!previous.equals(value)){
						break;
					}
					else{
						finala.put(key,value);
					}
				}else{
					finala.put(key, value);
				}
				previous = value;
			}
			PartialSolutionReduce ps1 = new PartialSolutionReduce(ps.fis, ps.NC, ps.cuvinte, ps.N, 1, finala);
			wp.putWork(ps1);
			
		}else{
			int ok = 0;
			for(int i = 0 ; i < ps.NC ; i++){
				String cuv = ps.cuvinte[i];
				if(ps.wdfq.containsKey(cuv)){
					ok++;
				}
			}
			if(ok == ps.NC){
				
				String res = ps.fis + " (";
				String s1 = "";
				for(int i = 0; i < ps.NC; i++){
					String s = String.format("%.2f", ps.wdfq.get(ps.cuvinte[i]));
					s1 += " " +  /*ps.wdfq.get(ps.cuvinte[i]) +*/ s+   ",";
				}
				
				res += s1.substring(1, s1.length()-1);
				res += ")";
				wp.result.put(ps.fis, res);
				
			}else{
				wp.result.put(ps.fis, "NO");
			}
		}
	}

	public void run() {
		//System.out.println("Thread-ul worker " + this.getName() + " a pornit...");
		while (true) {
			PartialSolutionReduce ps = wp.getWork();
			if (ps == null)
				break;

			processPartialSolution(ps);
		}
		//System.out.println("Thread-ul worker " + this.getName() + " s-a terminat...");
	}


}


class Compara implements Comparator<String>{
	HashMap<String,Double> map;

	public Compara(HashMap<String, Double> map){
		this.map = map;
	}

	@Override
	public int compare(String o1, String o2) {
		if(map.get(o1) >= map.get(o2)){
			return -1;
		}else
			return 1;
	}

}


public class Reduce{
	ConcurrentHashMap<String, ConcurrentHashMap<String, Double>> wdfq ;
	Integer N;
	Integer NC;
	String[] cuvinte;
	Integer NT;
	String[] documente;
	public Reduce(String[] documente, Integer N, Integer NC, Integer NT,String[] cuvinte,ConcurrentHashMap<String, ConcurrentHashMap<String, Double>> wdfq) {
		this.documente = documente;
		this.N = N;
		this.NC = NC;
		this.cuvinte = cuvinte;
		this.wdfq = wdfq;
		this.NT = NT;
	}
	
	public HashMap<String,String> reduce(){
		HashMap<String, String> result = new HashMap<String,String>();
		WorkPoolReduce wp = new WorkPoolReduce(NT, result);
		
		for(int i = 0; i < documente.length; i++){
			PartialSolutionReduce ps = new PartialSolutionReduce(documente[i], NC, cuvinte, N, 0, wdfq.get(documente[i]));
			wp.putWork(ps);
		}
		WorkerReduce[] workeri = new WorkerReduce[NT];
		for(int i = 0; i < NT; i++){
			workeri[i] = new WorkerReduce(wp);
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
		
		return wp.result;
		
	}
}
