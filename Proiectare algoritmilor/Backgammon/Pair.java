
public class Pair<K,V> {
	private K first ;
	private V second;
	public Pair(K x, V y){
		first = x ;
		second = y;
	}
	public V getSecond() {
		return second;
	}
	public void setSecond(V second) {
		this.second = second;
	}
	public K getFirst() {
		return first;
	}
	public void setFirst(K first) {
		this.first = first;
	}
	@Override
	public String toString() {
		return first.toString() +  " , " + second.toString();
	}
}
