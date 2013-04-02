
public class Sentence {
	private String sentence;
	private Integer distance;
	private Integer freq;
	private Integer nrwords;
	public String getSentence() {
		return sentence;
	}
	public void setSentence(String sentence) {
		this.sentence = sentence;
	}
	public Integer getDistance() {
		return distance;
	}
	public void setDistance(Integer distance) {
		this.distance = distance;
	}
	public Integer getFreq() {
		return freq;
	}
	public void setFreq(Integer freq) {
		this.freq = freq;
	}
	public Integer getNrwords() {
		return nrwords;
	}
	public void setNrwords(Integer nrwords) {
		this.nrwords = nrwords;
	}
	public Sentence() {
		sentence = new String();
		distance = -1;
		freq = -1;
		nrwords = 1;
	}
	public Sentence(String s, int d , int f , int nr) {
		sentence = s;
		distance = d;
		freq = f;
		nrwords = nr;
	}
	@Override
	public String toString() {
		return "(" + sentence + "," + distance.toString() + "," + freq.toString() + "," + nrwords.toString() + ")";
	}
	
}
