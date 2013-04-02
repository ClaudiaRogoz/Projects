
public class Evaluation {
	public static int distCasa(Tabla t,int color){
		int x;
		int scor = 100;
		if(color == 0){
			x = 6;
		}else{
			x=19;
		}
		
		if(t.inCasa(color)){
			return 100;
		}
		else{
			for(int i=1;i<Tabla.getDimtabla();i++){
				if((i > 6 && color == 0)||(i<19 && color == 1)){
					if(t.getTabla()[i].getColor() == color)
					scor -= Math.abs(x-i)*t.getTabla()[i].getPiese();
					
				}
			}
		}
		return scor;
	}
	
	public static int InCasa(Tabla t,int color){
		int scor = 0;
		if(color == 1){
			for(int i = 19; i<= 24;i++){
				if(t.getTabla()[i].getColor() == color){
					scor += t.getTabla()[i].getPiese()*15;
				}
			}
		}
		else{
			for(int i = 1; i<= 6; i++){
				if(t.getTabla()[i].getColor()== color){
					scor+= t.getTabla()[i].getPiese()*15;
				}
			}
		}
		return scor;
	}
	
	
	
	public static int evaluate(Tabla t ,int color){
		return Evaluation.distCasa(t, color) + Evaluation.InCasa(t, color);
	}
}
