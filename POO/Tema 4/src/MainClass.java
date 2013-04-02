import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;
import java.util.Random;

/**
 * Clasa main unde se fac prelucrari asupra hashmap ului prin intermediu clasei 
 * Student si lazy student
 * @author Merca
 *
 */
public class MainClass {
	/**
	 * functie care genereaza aleator un string pe care il si returneaza
	 * @return string generat aleator
	 */
	public static String genString(){
		// generez aleator un float
		Random gen = new Random();
		float n = gen.nextFloat();
		int c = 97;
		//lungimea sirului maxim 15
		int nr = (int)Math.ceil(n*100) % 15;
		String s = new String("");
		// generam aleatro cate un caracter adunannd la codul ascii 
		// al caracterului a nu nr intre 0 si 25
		for(int i =0 ;i<=nr ; i++){
			n = gen.nextFloat();
			int ch = (int)Math.ceil(n*1000) % 26;
			char cha = (char)(ch+c);
			// si adaugam caracterul la sir
			s  = s + String.valueOf(cha);
		}
		return s ;
		
	}
	/**
	 * @param args
	 */
	public static void main(String[] args) {
		List<Student> studenti = new LinkedList<Student>();
		Random generator = new Random();
		
		// generam 1400 de studenti aleator si ii adaugam in lista
		for(int i=0;i<1400;i++){
			int x =16 +  Math.abs(generator.nextInt()) % 15;
			String na = genString();
			Student st = new Student(na, x);
			studenti.add(st);
		}
		// apoi in map 
		MyHashMapImpl<Student, Integer> map = new MyHashMapImpl<Student, Integer>(32);
		Iterator<Student> it = studenti.iterator();
		generator = new Random();
		while(it.hasNext()){
			int n = Math.abs(generator.nextInt()) % 11;
			map.put(it.next(),n);
		}
		// calculam timpul pentru 300 de get uri aleatoare
		long begin = System.currentTimeMillis();
		for(int i = 0 ; i<300 ; i++){
		int	n =  Math.abs(generator.nextInt()) % 1400;
			map.get(studenti.get(n));
		}
		long finish = System.currentTimeMillis() - begin;
		System.out.println("pentru Studenti = " + finish);
	
		
		// acelasi lucru pentru lazy student
		
		List<LazyStudent> lazystudenti = new LinkedList<LazyStudent>();
		 generator = new Random();
		
		
		for(int i=0;i<1400;i++){
			int x =16 +  Math.abs(generator.nextInt()) % 15;
			String na = genString();
			LazyStudent st = new LazyStudent(na, x);
			lazystudenti.add(st);
		}
		MyHashMapImpl<LazyStudent, Integer> lazymap = new MyHashMapImpl<LazyStudent, Integer>(32);
		Iterator<LazyStudent> iter = lazystudenti.iterator();
		generator = new Random();
		while(iter.hasNext()){
			int n = Math.abs(generator.nextInt()) % 11;
			lazymap.put(iter.next(),n);
		}
		begin = System.currentTimeMillis();
		for(int i = 0 ; i<300 ; i++){
		int	n =  Math.abs(generator.nextInt()) % 1400;
			lazymap.get(lazystudenti.get(n));
		}
		 finish = System.currentTimeMillis() - begin;
		System.out.println("pentru LazyStudenti = " + finish);
		
		
		
	}

}
