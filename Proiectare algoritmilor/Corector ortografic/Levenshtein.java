
public class Levenshtein {

	public static int getDistance(String s1,String s2){
		int l1 = s1.length();
		int l2 = s2.length();
		int i;
		int[][] tab = new int[l1+1][l2+1];
		for( i = 0; i<= l1 ; i++){
			tab[i][0] = i; 
		}
		for(i = 0;i <= l2;i++){
			tab[0][i] = i; 
		}
		int j ;
		for(i = 1; i<=l1;i++){
			for(j=1;j<=l2;j++){
				if(s1.charAt(i-1) == s2.charAt(j-1)){
					tab[i][j] = tab[i-1][j-1];
					
				}else{
					tab[i][j] = Math.min(Math.min(tab[i-1][j]+1,tab[i][j-1]+1), tab[i-1][j-1]+1);
					
				}
			}
		}
		
		return tab[l1][l2];
	}

}

	
