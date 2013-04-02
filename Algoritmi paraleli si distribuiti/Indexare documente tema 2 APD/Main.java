import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.util.HashMap;
import java.util.concurrent.ConcurrentHashMap;




public class Main {

	/**
	 * @param args
	 */
	public static void main(String[] args) {

		Integer NT = Integer.valueOf(args[0]);
		String fisin = args[1];
		String fisout = args[2];
		Read read = new Read(fisin);
        Map map = new Map(read.documente, NT, read.D);
        ConcurrentHashMap<String, ConcurrentHashMap<String, Double>> mapwordfreq;
        mapwordfreq = map.map();
        Reduce reduce = new Reduce(read.documente, read.N, read.NC, NT, read.cuvinte, mapwordfreq);
        HashMap<String,String> result = reduce.reduce();
        try {
			FileWriter fstream = new FileWriter(fisout);
			BufferedWriter out = new BufferedWriter(fstream);
			String s = "Rezultate pentru: (";
			String s1 = "";
			for(int i = 0; i < read.NC; i++){
			
				s1+= " " + read.cuvinte[i] + ",";
			
			}
			s1 = s1.substring(1, s1.length()-1);
			s += s1 + ")\n";
			int k = 0;
		    out.write(s);
		    
			for(int i = 0; i < read.documente.length; i++){
				k++;
				if(k <= read.X){
					if(!result.get(read.documente[i]).equals("NO")){
						out.write("\n" + result.get(read.documente[i]));
					}
				}
		    }
			out.close();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
        
       
	}

}
