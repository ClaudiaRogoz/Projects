import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.util.Scanner;
import java.util.Vector;


public class Main {
	
	private static final long MEGABYTE = 1024L * 1024L;
	public static long bytesToMegabytes(long bytes) {
		return bytes / MEGABYTE;
	}
	public static void main(String[] args) {
		String image = args[0];
		long x = System.currentTimeMillis();
		String mask_bg = args[1];
		String mask_fg = args[2];
		String parametrii = args[3];
		FileInputStream fstream = null;
		try {
			fstream = new FileInputStream(image);
		} catch (FileNotFoundException e) {

			e.printStackTrace();
		}
		Scanner s = new Scanner(fstream);
		s.next();
		int n = s.nextInt();
		int m = s.nextInt();
		int maxVal = s.nextInt();
		System.out.println(n + "   " + m);
		int[] img = new int[n*m];
	
		for(int i = 0; i < n*m; i++){
			img[i] = s.nextInt();
		}
		try {
			fstream = new FileInputStream(mask_bg);
		} catch (FileNotFoundException e2) {
			
			e2.printStackTrace();
		
		}
		
		s = new Scanner(fstream);
		s.nextLine();
		s.nextLine();
		maxVal = s.nextInt();
		int[] bg = new int[n*m];
		
		for(int i = 0; i < n*m; i++){
		
			bg[i] = s.nextInt();
		
		}
		try {
			fstream = new FileInputStream(mask_fg);
		} catch (FileNotFoundException e1) {

			e1.printStackTrace();
		}
		s = new Scanner(fstream);
		s.nextLine();
		s.nextLine();
		maxVal = s.nextInt();
		int[] fg = new int[n*m];
		
		for(int i = 0; i < n*m; i++){
		
			fg[i] = s.nextInt();
		
		}
		
		int lambda , treshold;
		try {
			fstream = new FileInputStream(parametrii);
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}
		
		s = new Scanner(fstream);
		lambda = s.nextInt();
		treshold = s.nextInt();

		double niuf = Formule.niu(img, fg, m, n);
		double niub = Formule.niu(img, bg, m, n);
		double sigmaf = Formule.sigma(img, fg, m, n);
		double sigmab = Formule.sigma(img, bg, m, n);
		System.out.println(niuf);
		System.out.println(niub);
		System.out.println(sigmaf);
		System.out.println(sigmab);
		
		System.out.println(Formule.fu(niuf, niub, sigmaf, sigmab, 1,50));
		
		Graph g = new Graph();
		g.makeGraph(n, m, img, treshold, lambda, niuf, niub, sigmaf, sigmab);
		System.out.println(g.max_flow(g, g.sursa, g.drena));
		
		g.min_cut(null, null);
		System.out.println("timpul");
		System.out.println((System.currentTimeMillis() - x));
		// Get the Java runtime
				Runtime runtime = Runtime.getRuntime();
				// Run the garbage collector
				// Calculate the used memory
				long memory = runtime.totalMemory() - runtime.freeMemory();
				System.out.println("Used memory is bytes: " + memory);
				System.out.println("Used memory is megabytes: "
						+ bytesToMegabytes(memory));
		
		
	}

}
