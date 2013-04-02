import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

/**
 * Clasa care implementeaza MyHashMap
 * @author Merca
 *
 * @param <K> tipul key 
 * @param <V>	tipul value
 */
public class MyHashMapImpl<K, V> implements MyHashMap<K, V> {
	// numarul maxim de buckets 
	private int numBuckets;
	// numarul efectiv de buckets in map
	private int count;
	// vectorul de buckets
	@SuppressWarnings("rawtypes")
	private BucketImpl[] buckets ;
	
	/**
	 * Constructor ce initializeaza nr maxim de buckets count si vectorul cu dimensiunea numBuckets
	 * @param numBuckets numarul de buckets
	 */
	MyHashMapImpl(int numBuckets){
		this.numBuckets = numBuckets;
		buckets =  new BucketImpl[numBuckets];
		count = 0;
	}
	
	
	@Override
	public V get(K key) {
		int index;
		// calculam indexul pentru key
		if(key == null){
			index = 0;
		}else{
			index = index(key);
		}
		// verificam existenta indexului
		if(existsIndex(index)==true){
			// parcurgem lista de entry pentru bucketul cu acel index 
			@SuppressWarnings("unchecked")
			BucketImpl<K, V> buc = buckets[index];
			Iterator<EntryImpl<K,V>> it = buc.entries.iterator();
			while(it.hasNext()){
				EntryImpl<K, V> toget = it.next();
				// verificam daca elementul curent este egal cu key si 
				// returnam valoarea
				if(toget.getKey().equals(key) || toget.getKey()== key){
					return toget.getValue();
				}
				
			}
		}
		return null;
	}
	/**
	 * calculeaza indexul adica pozitia in vectorul de buckets ca fiind modulo numBuckets din modulul 
	 * hasCode ului cheii respective
	 * @param key  cheia pentru care se calculeaza indexul 
	 * @return indexul 
	 */
	public Integer index(K key){
		Integer k = key.hashCode();
		return Math.abs(k) % numBuckets;
	}
	/**
	 * verifica daca exista elemente la index
	 * @param index pozitia in care cautam
	 * @return true /false
	 */
	public boolean existsIndex(int index){
		if(buckets[index]!=null){
			return true;
		}
		else return false;
		
	}
	
	@Override
	public V put(K key, V value) {
		int index;
		// calculam indexul pentru key 
		if(key == null){
			index = 0;
		}else{
			index = index(key);
			} 
		// daca a mai fost un element cu acel index
			if(existsIndex(index)==true){
				
				@SuppressWarnings("unchecked")
				BucketImpl<K, V> buc = buckets[index];
				// luam toate bucket urile cu acel index si le parcurgem 
				Iterator<EntryImpl<K, V>> it = buc.entries.iterator();
				while(it.hasNext()){
					Entry<K, V> en = it.next();
					
					if(en!=null){
						// daca gasim o cheie cu key
						if(en.getKey().equals(key)|| key== en.getKey()){
							V before = en.getValue();
							// returnam valoare de dinainte si o inlocuim cu noua valoare
							it.remove();
							EntryImpl<K, V> newEntry = new EntryImpl<K, V>(key, value);
							buc.entries.add(newEntry);
							return before;
						}
					}
				}
				//daca nu adaugam value si returnam null
				EntryImpl<K, V> newEntry = new EntryImpl<K, V>(key, value);
				buc.entries.add(newEntry);
				return null;
		
			}
		// daca nu exista nici indexul adaugam bucket si entry cu acel key returnam null 
			// marim nr de bucket uri 
		BucketImpl<K, V> buc = new BucketImpl<K,V>(index);
		EntryImpl<K, V> newEntry = new EntryImpl<K,V>(key, value);
		buc.entries = new ArrayList<EntryImpl<K, V>>();
		buc.entries.add(newEntry);
		buc.setHash(index);
		buckets[index] = buc;
		count++;
		return null;
	}

	
	@Override
	public V remove(K key) {
		int index;
		if(key == null){
			index = 0;
		 }else{
			index = index(key);
		 }
		if(existsIndex(index)){
			@SuppressWarnings("unchecked")
			BucketImpl<K, V> buc = buckets[index];
			// parcurgem daca exista acel index toate entry urile din bucket 
			
			Iterator<EntryImpl<K,V>> it = buc.entries.iterator();
			while(it.hasNext()){
			// cand gasim cheia respectiva o stergem 
				EntryImpl<K, V> toremove = it.next();
				if(toremove.getKey().equals(key)){
					V torem = toremove.getValue();
					it.remove();
					count--;
					return torem;
				}
			}
		}
		
		
		
		return null;
	}

	
	
	@Override
	public int size() {
		
		return count;
	}
	
	
	
	@SuppressWarnings("unchecked")
	@Override
	public List<? extends MyHashMap.Bucket<K, V>> getBuckets() {
		List<BucketImpl<K, V>>  list = new ArrayList<BucketImpl<K,V>>();
		for(int i=0;i< buckets.length;i++){
			if(buckets[i]==null){
				list.add(i, buckets[i]);
			}
		}
		return list;
	}


}
