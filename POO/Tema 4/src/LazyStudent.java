/**
 * lazyStudent extinde Student si este facuta pentru a compara rapiditatea
 * unui hasCode constant si unul implementat cu o anumita functie
 * @author Merca
 *
 */
public class LazyStudent extends Student{
/**
 * Constructor pentru LazyStudent 
 * @param name numele studentului
 * @param age varsta
 */
	LazyStudent(String name, int age) {
		super(name, age);
	}
	@Override
	public int hashCode() {
		
		return 42;
	}
	
}
