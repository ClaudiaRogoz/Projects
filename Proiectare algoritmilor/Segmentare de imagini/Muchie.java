
public class Muchie {
	private int v1,v2;
	double c;
	double pixelv1;
	double pixelv2;
	public Muchie(int a ,int b, double cap,double p,double q) {
		v1 = a ;
		v2 = b;
		c = cap;
		pixelv1 = p;
		pixelv2 = q;
	}
	
	
	
	public int getV2() {
		return v2;
	}

	public void setV2(int v2) {
		this.v2 = v2;
	}

	public int getV1() {
		return v1;
	}

	public void setV1(int v1) {
		this.v1 = v1;
	}

	public double getC() {
		return c;
	}

	public void setC(double c) {
		this.c = c;
	}
	
	@Override
	public String toString() {
		
		return "(" + Integer.toString(v1) + "  " + Integer.toString(v2 ) + "  " + c + "  " + pixelv1 + "  " + pixelv2 +")" ;
		
	}
	
}
