import java.io.*;
import java.util.*;


public class IO {
	/**
	 * citim din fisier si depunem rezultatele in map in functie de lungimea sirului citit. 
	 * @param name
	 * @return
	 */
	public TreeMap<Integer,TreeMap<String, Integer>> getDictionary(String name){
		TreeMap<Integer, TreeMap<String, Integer>> dictionary = new TreeMap<Integer, TreeMap<String,Integer>>();
		
		
		
		try{
			  
			  FileInputStream fstream = new FileInputStream(name);
			  
			  DataInputStream in = new DataInputStream(fstream);
			  BufferedReader br = new BufferedReader(new InputStreamReader(in));
			  String strLine;
			  String[] splited ;
			  
			  while ((strLine = br.readLine()) != null)   {
				  splited = strLine.split(" ");
				  
				  if(dictionary.containsKey(splited[0].length())){
					  dictionary.get(splited[0].length()).put(splited[0], Integer.parseInt(splited[1]));
				  }else{
					  TreeMap<String, Integer> dic = new TreeMap<String,Integer>();
					  dic.put(splited[0], Integer.parseInt(splited[1]));
					  dictionary.put(splited[0].length(), dic);
				  }
			  }
			
			  in.close();
			  
			    }catch (Exception e){
			    	System.err.println("Error: " + e.getMessage());
			  }

		
		return dictionary;
	}
}
