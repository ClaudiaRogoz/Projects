package com.example.tweetswithmap;

public class TweetModel {
	private String name, date, tweet;
	private double distance;
	private double lat,longi;
	public TweetModel(String name, String date, String tweet,double distance/*,double lat,double longi*/) {
		this.name = name;
		this.date = date;
		this.tweet = tweet;
		this.setDistance(distance);
		//this.lat = lat;
		//this.longi = longi;
		
	}
	
	public String getName() {
		return name;
	}
	
	public String getDate() {
		return date;
	}
	
	public String getTweet() {
		return tweet;
	}
	
	public double getDistance() {
		return distance;
	}

	public void setDistance(double distance) {
		this.distance = distance;
	}
}
