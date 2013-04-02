/**
 * O clasa de intrari adica pereche valoare cheie 
 * @author Merca
 *
 * @param <K> cheia
 * @param <V> valoarea 
 */
public class EntryImpl<K, V> implements MyHashMap.Entry<K, V> {
	
	private K key;
	private V value;
	/**
	 * Constructor 
	 * @param key cheia 
	 * @param value valoare
	 */
	public EntryImpl(K key, V value) {
		this.key = key;
		this.value = value;
	}
	
	
	@Override
	public K getKey() {
		
		return this.key;
	}

	@Override
	public V getValue() {
		
		return this.value;
	}
	
	@Override
	public String toString() {
		
		return this.key.toString() +  "==>"+ this.value.toString();
	}

}
