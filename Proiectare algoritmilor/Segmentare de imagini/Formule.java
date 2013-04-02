
public class Formule {
	/**
	 * functie care calculeaza niu 
	 * @param image
	 * @param mask
	 * @param m
	 * @param n
	 * @return
	 */
	public static double niu(int[] image, int[] mask,int m,int n){
		double s = 0;
		int nr = 0;
		for(int i = 0; i < n*m; i++){
			if(mask[i] != 0){
				s += image[i];
				nr++;
			}
		}
		
		
		return s / nr;
	}
	/**
	 * functie care calculeaza sigma 
	 * @param image
	 * @param mask
	 * @param m
	 * @param n
	 * @return
	 */
	public static double sigma(int[] image, int[] mask, int m , int n){
		double niu = niu(image, mask, m, n);
		double suma = 0;
		int nr = 0;
		for(int i = 0; i < n*m ; i++){
			if(mask[i] != 0){
				suma += Math.pow((niu - image[i]),2); 
				nr ++;
			}
		}
		
		
		return Math.sqrt(suma/nr);
		
	}
	/**
	 * 
	 * @param niuf
	 * @param niub
	 * @param sigmaf
	 * @param sigmab
	 * @param x
	 * @param i
	 * @return
	 */
	public static double fu(double niuf, double niub, double sigmaf, double sigmab ,int x,int i){
		double fu = x*(0.5*(Math.pow(((i - niuf)/sigmaf),2)) + Math.log(Math.sqrt(2* Math.PI * Math.pow(sigmaf,2)))) + (1-x) *( (0.5 * Math.pow(((i -niub)/sigmab),2 )) + Math.log(Math.sqrt(2* Math.PI * Math.pow(sigmab,2))));
		
		return Math.min(fu, 10);
	}
	
	
	
}
