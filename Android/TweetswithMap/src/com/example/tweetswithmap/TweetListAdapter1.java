package com.example.tweetswithmap;

import java.util.ArrayList;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.TextView;

public class TweetListAdapter1 extends BaseAdapter {
	Context context;
	ArrayList<TweetModel> items;
	
	public TweetListAdapter1(Context context, ArrayList<TweetModel> items) {
		this.context = context;
		this.items = items;
	}
	
	public int getCount() {
		return items.size();
	}

	public Object getItem(int arg0) {
		// TODO Auto-generated method stub
		return null;
	}

	public long getItemId(int arg0) {
		// TODO Auto-generated method stub
		return 0;
	}
	
	public View getView(int position, View convertView, ViewGroup parent) {
		
		LayoutInflater inflater = (LayoutInflater)context.getSystemService(Context.LAYOUT_INFLATER_SERVICE);
		View rowView = inflater.inflate(R.layout.list_item_tweet, parent, false);
		
		TextView txtMessage = (TextView)rowView.findViewById(R.id.txtMessage);
		TweetModel m = items.get(position);
		txtMessage.setText("Name: " + m.getName()  +"\n"+ "Distance :"+ m.getDistance() +  " Km\n" + "Tweet: " +  m.getTweet() + "\n" + "Date: " + m.getDate() + "\n");
		
		return rowView;
	}
	
}
