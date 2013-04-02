import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map.Entry;


public class ExpectiMinimax {
	
	public Pair<ArrayList<Pair<Integer,Integer>>, Integer> expectiminimax (Arbore a ,int zar[], int color, int depth,ArrayList<Pair<Integer,Integer>> moves){
		Integer score;
		if(depth == 0){
			return new Pair<ArrayList<Pair<Integer,Integer>>, Integer>(moves, Evaluation.evaluate(a.tabla, color));
		}
		return null;
		
	}
	

	
}
