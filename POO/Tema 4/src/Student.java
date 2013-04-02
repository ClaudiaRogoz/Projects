/**
 * clasa Student ce contine 2 parametrii nume si varsta
 * @author Merca
 *
 */
public class Student {
	String nume ;
	int varsta;
	/**
	 * Constructor
	 * @param name numele
	 * @param age varsta
	 */
	Student(String name, int age){
		nume = name;
		varsta = age;
	}
	@Override
	public boolean equals(Object obj) {
		
		if(((Student)obj).varsta == this.varsta && this.nume.equals(((Student)obj).nume)){
			return true;
		}
		else return false;
	}
	@Override
	public int hashCode() {
		int h = 17;
		h = 37*h + varsta;
		h = 37*h + nume.hashCode();
		return h;
	
	}
}
