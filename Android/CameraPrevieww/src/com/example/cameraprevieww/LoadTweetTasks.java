package com.example.cameraprevieww;

import java.io.IOException;
import java.util.ArrayList;

import org.apache.http.client.ClientProtocolException;
import org.apache.http.client.HttpClient;
import org.apache.http.client.ResponseHandler;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.impl.client.BasicResponseHandler;
import org.apache.http.impl.client.DefaultHttpClient;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import android.app.ProgressDialog;
import android.content.Context;
import android.os.AsyncTask;
import android.util.Log;
import android.widget.ListView;
import android.widget.Toast;

public class LoadTweetTasks  extends AsyncTask<Void, Void, Void> {
	private static final String TAG = "test";
	String  username;
	ArrayList< MyData> tweets ;
	ProgressDialog progressDialog ; 
	Context mContext;
	public LoadTweetTasks(String username,Context c){
		this.username = username;
		mContext= c;
	}
	
	public LoadTweetTasks() {
		// TODO Auto-generated constructor stub
	}

	@Override
	protected void onPreExecute(){
		tweets = new  ArrayList<MyData>();
		progressDialog = new  ProgressDialog(mContext) ;
		progressDialog.setMessage("loading tweets");
		progressDialog.show();
	}
	
	@Override
	protected void onPostExecute(Void result){
		progressDialog.dismiss();
		Toast.makeText(mContext, tweets.toString() , Toast.LENGTH_LONG).show();
		
	}
	


@Override
protected Void doInBackground(Void... params) {
	// TODO Auto-generated method stub
	
	HttpClient client = new  DefaultHttpClient();
	
	String requestUrl = "http://api.twitter.com/1/statuses/user_timeline.json?screen_name="+ username + "&count=20";
	HttpGet request  =  new HttpGet(requestUrl);
	ResponseHandler<String> responseHandler = new  BasicResponseHandler();
	

	try {
		String  jsonResponse = client.execute(request,responseHandler);
		JSONArray json = new  JSONArray(jsonResponse);
		for  (int  i=0 ; i< json.length();i++){

			JSONObject jsonTweet = json.getJSONObject(i);
			MyData aux = new MyData()  ;
			aux.setName(jsonTweet.getJSONObject("user").getString("name"));
			aux.setText(jsonTweet.getString("text"));
			
			Object menuObject = jsonTweet.get("coordinates");
			if(menuObject != JSONObject.NULL){
			if (jsonTweet.getJSONObject("coordinates") != JSONObject.NULL){
				if (jsonTweet.getJSONObject("coordinates").getJSONArray("coordinates").length() != 0 ){
					aux.setLat(Float.parseFloat(jsonTweet.getJSONObject("coordinates").getJSONArray("coordinates").get(0).toString()));
					aux.setLng(Float.parseFloat(jsonTweet.getJSONObject("coordinates").getJSONArray("coordinates").get(1).toString()));
				}
			}
			}
			else{
				aux.setLat(0);
				aux.setLng(0);				
			}
			tweets.add(aux);
		}
		
	} catch (ClientProtocolException e) {
		Log.e(TAG, e.getMessage(),e);
	}
	catch (IOException e) {
		Log.e(TAG, e.getMessage(),e);
	}
	catch (JSONException e) {
		Log.e(TAG, e.getMessage(),e);
	}
	return null;
}
}