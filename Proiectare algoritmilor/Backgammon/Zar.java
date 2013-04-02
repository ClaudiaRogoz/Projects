import java.util.ArrayList;


public class Zar {
	private int z1;
	private int z2;
	public Zar(int a ,int b) {
		setZ1(a);
		setZ2(b);
	}
	public ArrayList<Zar> allZar(){
		ArrayList<Zar> zaruri = new ArrayList<Zar>();
		for(int i = 1; i<=6;i++){
			for(int j = 1; j<=6; j++ ){
				zaruri.add(new Zar(i,j));
			}
		}
		return zaruri;
	}
	
	
	public int getZ1() {
		return z1;
	}
	public void setZ1(int z1) {
		this.z1 = z1;
	}
	public int getZ2() {
		return z2;
	}
	public void setZ2(int z2) {
		this.z2 = z2;
	}
	@Override
	public String toString() {
		return "(" + z1 + "," + z2 + ")";
	}
	public boolean dubla(){
		return z1 == z2;
	}
	public int length(){
		int len = 0;
		if(this.dubla()){
			len =4;
		}else if(this.getZ1()!=0&&this.getZ2()!=0){
			
			len = 2;
			
		}else{
			len =1 ;
		}
		return len;
	}
	
	public int[] getVect(){
		
		
		int[] z = new int[this.length()];
		if(this.length() == 2){
			z[0] = this.getZ1();
			z[1]= this.getZ2();
		}else{
			if(this.length()== 1){
				z[0] = this.getZ1() != 0 ? this.getZ1() : this.getZ2();
			}else{
				z[0] = this.getZ1();
				z[1] = this.getZ1();
				z[2] = this.getZ1();
				z[3] = this.getZ1();
			
			}
		}
		return z;
		
	}
}
