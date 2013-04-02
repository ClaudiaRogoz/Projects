import java.util.Scanner;
import java.util.TreeMap;


public class Main {

	
	public static void main(String[] args) {
		
		
		Scanner in = new Scanner(System.in);
		//String  s = args[0];
		//System.out.println(s);
		Correction corect = new Correction();
		Sentence corectat ;
		
		String s = in.nextLine();
		long time = System.currentTimeMillis();
		IO io = new IO();
		TreeMap<Integer, TreeMap<String, Integer>> dictionary = new TreeMap<Integer, TreeMap<String,Integer>>();
		dictionary = io.getDictionary("dict.txt");
		corectat = corect.corectAnything(s, dictionary);
		System.out.println(corectat.getSentence());
		
		
		long time1 = System.currentTimeMillis() - time;
		//System.out.println("timpul este "+ time1);
		
		
		
		
		
	}

}
