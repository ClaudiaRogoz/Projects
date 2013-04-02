package ro.merca.ionel;

import java.io.File;
import java.util.ArrayList;

public class Functions {
	public static ArrayList<String> ls(String dir){
		File folder = new File(dir);
		
		File[] files = folder.listFiles();
		
		if(files == null){
			return new ArrayList<String>();
		}
		System.out.println("aici");
		System.out.println(files.length);
		ArrayList<String> ret = new ArrayList<String>();
		for(int i = 0; i < files.length; i++){
			ret.add(files[i].getName());
		}
		
		return ret;
	}
	

}