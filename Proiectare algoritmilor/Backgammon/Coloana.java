
public class Coloana {
	private Integer piese ;
	private Integer color;
	public Coloana(Integer nrpiese , Integer cul) {
		piese = nrpiese;
		color = cul;
	}
	
	public Integer getColor() {
		return color;
	}
	public void setColor(Integer color) {
		this.color = color;
	}
	public Integer getPiese() {
		return piese;
	}
	public void setPiese(Integer piese) {
		this.piese = piese;
	}
	@Override
	public String toString() {
		String s = color == 0 ? "O" : "X";
		String res = "";
		for(int i = 0; i < piese ;i++){
			res += s;
		}
		return res;
		
	}
	
	public Coloana clone(){
		Coloana x = new Coloana(piese,color);
		return x;
	}
}
