import java.util.ArrayList;
import java.util.List;



/**
 * O clasa de bucket ce contine mai multe entry uri 
 * @author Merca
 *
 * @param <K> cheia
 * @param <V> valoarea
 */
public class BucketImpl<K,V> implements MyHashMap.Bucket<K, V> {
	List<EntryImpl<K, V>> entries = new ArrayList<EntryImpl<K,V>>();
	private int hash;
	/**
	 * Constructor 
	 * @param hash
	 */
	public BucketImpl( int hash) {
		this.setHash(hash);
	}
	
	@Override
	public List<? extends MyHashMap.Entry<K, V>> getEntries() {
		
		return entries;
	}
	/**
	 * functie getter pentru private hash
	 * @return valoarea hash codului
	 */
	public int getHash() {
		return hash;
	}
	/**
	 * functie setter
	 * @param hash un int hash code
	 */
	public void setHash(int hash) {
		this.hash = hash;
	}
	

}
