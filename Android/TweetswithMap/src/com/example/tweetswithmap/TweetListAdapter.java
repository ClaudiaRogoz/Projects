package com.example.tweetswithmap;

import java.util.ArrayList;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.TextView;

public class TweetListAdapter extends BaseAdapter {
	Context context;
	ArrayList<String> items;
	
	public TweetListAdapter(Context context, ArrayList<String> items) {
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
		txtMessage.setText(items.get(position));
		
		
		return rowView;
	}
	
}
