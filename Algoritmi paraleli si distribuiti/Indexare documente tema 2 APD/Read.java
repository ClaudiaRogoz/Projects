import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.io.RandomAccessFile;
import java.util.ArrayList;
import java.util.HashMap;


public class Read {
	
	Integer NC  = 0;
	Integer D;
	Integer N;
	Integer X;
	Integer ND;
	String documente[];
	String cuvinte[];
	HashMap<String, ArrayList<Byte[]>> mapptdoc = new HashMap<String, ArrayList<Byte[]>>();
	
	public void readfromfile(String fisin){

		BufferedReader br = null;

		try {

			br = new BufferedReader(new FileReader(fisin));

		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		String line;
		try {

			line = br.readLine();
			NC = Integer.valueOf(line);
			line = br.readLine();
			cuvinte = line.split(" ");

			D = Integer.valueOf(br.readLine());
			N = Integer.valueOf(br.readLine());
			X = Integer.valueOf(br.readLine());
			ND = Integer.valueOf(br.readLine());
			int i = 0;
			documente = new String[ND];
			while ((line = br.readLine()) != null && i < ND ) {
				documente[i] = line;
				
				i++;
			}
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		try {
			br.close();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

	}
	    
        
	
	public Read(String fisin) {
		readfromfile(fisin);
		
	}
}
