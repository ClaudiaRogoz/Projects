package com.example.cameraprevieww;

public class MyData {
	double lat,lng;
	String  name;
	String text;
	
	
	public String getName() {
		return name;
	}
	public void setName(String name) {
		this.name = name;
	}
	public String getText() {
		return text;
	}
	public void setText(String text) {
		this.text = text;
	}
	public MyData() {
		this.lat=0;
		this.lng=0;
	}
	public double getLat() {
		return lat;
	}
	public void setLat(double lat) {
		this.lat = lat;
	}
	public double getLng() {
		return lng;
	}
	public void setLng(double lng) {
		this.lng = lng;
	}
	
	
	@Override
	public String toString() {
		return "Name : " + name + "\n Text: " + text ;
	}
}
