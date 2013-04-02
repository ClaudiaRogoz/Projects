package com.example.tweetswithmap;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import org.apache.http.client.ClientProtocolException;
import org.apache.http.client.HttpClient;
import org.apache.http.client.ResponseHandler;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.impl.client.BasicResponseHandler;
import org.apache.http.impl.client.DefaultHttpClient;
import org.json.JSONArray;
import org.json.JSONException;
import org.json.JSONObject;

import com.example.tweetswithmap.R;

import android.app.Activity;
import android.app.Dialog;
import android.app.ProgressDialog;
import android.content.Context;
import android.content.Intent;
import android.content.SharedPreferences;
import android.location.Location;
import android.location.LocationManager;
import android.net.Uri;
import android.os.AsyncTask;
import android.os.Bundle;
import android.util.FloatMath;
import android.util.Log;
import android.view.ContextMenu;
import android.view.ContextMenu.ContextMenuInfo;
import android.view.MenuInflater;
import android.view.MenuItem;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.AdapterView.AdapterContextMenuInfo;
import android.widget.Button;
import android.widget.ListView;
import android.widget.TextView;

public class Proj2Activity extends Activity {
	public static final String TAG = "MyActivity";
	private float myLatitude;
	private float myLongitute;
	private float tweetLat;
	private float tweetLong;
	private ArrayList<TweetModel> tweets;
	public static double distance(float lat_a, float lng_a, float lat_b, float lng_b) {
	    float pk = (float) (180/3.14169);

	    float a1 = lat_a / pk;
	    float a2 = lng_a / pk;
	    float b1 = lat_b / pk;
	    float b2 = lng_b / pk;
	    
	    float t1 = FloatMath.cos(a1)*FloatMath.cos(a2)*FloatMath.cos(b1)*FloatMath.cos(b2);
	    float t2 = FloatMath.cos(a1)*FloatMath.sin(a2)*FloatMath.cos(b1)*FloatMath.sin(b2);
	    float t3 = FloatMath.sin(a1)*FloatMath.sin(b1);
	    double tt = Math.acos(t1 + t2 + t3);
	   
	    return 6366000*tt;
	}
	
	
	public static Location getLocation(Context ctx) {
	    LocationManager lm = (LocationManager) ctx
	            .getSystemService(Context.LOCATION_SERVICE);
	    List<String> providers = lm.getProviders(true);

	    /*
	     * Loop over the array backwards, and if you get an accurate location,
	     * then break out the loop
	     */
	    Location l = null;

	    for (int i = providers.size() - 1; i >= 0; i--) {
	        l = lm.getLastKnownLocation(providers.get(i));
	        if (l != null)
	            break;
	    }
	    return l;
	}
	

    
	
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        LoadTweetsTask ltt = new LoadTweetsTask("androiddev");
        ltt.execute();

        
        final TextView text1 = (TextView) findViewById(R.id.nume);
      	final Button btnGo = (Button) findViewById(R.id.button1);
      	
      	btnGo.setOnClickListener(new OnClickListener() {
			
			public void onClick(View v) {
				String name1 = text1.getText().toString();
				
				SharedPreferences settings = getSharedPreferences("My_Pref", 0);
			      SharedPreferences.Editor editor = settings.edit();
			      editor.putBoolean(name1, true);
			      editor.commit();
				 LoadTweetsTask ltt = new LoadTweetsTask(name1);
			     ltt.execute();
			}
		});
      	registerForContextMenu(findViewById(R.id.listTweets));

        
    }
    
    
    @Override
    public void onCreateContextMenu(ContextMenu menu, View v,
                                    ContextMenuInfo menuInfo) {
        super.onCreateContextMenu(menu, v, menuInfo);
        MenuInflater inflater = getMenuInflater();
        inflater.inflate(R.layout.menu1, menu);
        
    }

    @Override
    public boolean onContextItemSelected(MenuItem item) {
    	AdapterContextMenuInfo info = (AdapterContextMenuInfo) item.getMenuInfo();
        switch (item.getItemId()) {
            case R.id.viewlink:
            	String s = tweets.get((int)info.id).getTweet();
            	System.out.println(s);
            	String[] spl = s.split(" ");
            	int i;
            	for( i = 0; i < spl.length; i++){
            		System.out.println(spl[i]);
            	}
            	
            	for( i = 0; i < spl.length; i++){
            		if(spl[i].contains("http")){
            			Intent in = new Intent(Intent.ACTION_VIEW, 
            				       Uri.parse(spl[i]));
            			startActivity(in);
            			break;
            		}
            	}
            	if(i == spl.length){
            		Dialog dialog=new Dialog(this);
        			TextView txt= (TextView)dialog.findViewById(R.id.dialog);
        			txt.setText("Not a link");
        			dialog.show();
        			
            	}
            	break;
            case R.id.viewMap:
            	Intent myIntent = new Intent(Proj2Activity.this, ShowMapActivity.class);
            	myIntent.putExtra("mylat", myLatitude);
            	myIntent.putExtra("mylong", myLongitute);
            	myIntent.putExtra("lat",tweetLat);
            	myIntent.putExtra("long", tweetLong);
            	Proj2Activity.this.startActivity(myIntent);
            	
            	break;
            }
		return false;
        
    }


    
    
    
    
    private class LoadTweetsTask extends AsyncTask<Void, Void, Void> {
    	
    	ProgressDialog progressDialog;
    	public String name;
    	
      	
      	public LoadTweetsTask(String name) {
        	this.name = name;
		}
    	
    	@Override
    	protected void onPreExecute() {
    		tweets = new ArrayList<TweetModel>();
    		
    		progressDialog = new ProgressDialog(Proj2Activity.this);
    		progressDialog.setMessage("Loading Tweets");
    		progressDialog.show();
    		
    	}
    	
    	@Override
    	protected void onPostExecute(Void result) {
    		progressDialog.dismiss();
    		
    		TweetListAdapter1 adapter = new TweetListAdapter1(getApplicationContext(), tweets);
    		((ListView)findViewById(R.id.listTweets)).setAdapter(adapter);
    	}
    	
		@Override
		protected Void doInBackground(Void... params) {
			
			
			
			HttpClient client = new DefaultHttpClient();
			
			String requestUrl = "http://api.twitter.com/1/statuses/user_timeline.json" + "?screen_name=" + name + "&count=200";
			HttpGet request = new HttpGet(requestUrl);
			ResponseHandler<String> responseHandler = new BasicResponseHandler();
			
			try {
				String jsonResponse = client.execute(request, responseHandler);
				
				JSONArray json = new JSONArray(jsonResponse);
				//used to display 20 valid tweets from 200 tweets which have the location specified
				int count = 0;
				for (int i = 0; i < json.length(); i++) {
					if(count <= 20){
						JSONObject jsonTweet = json.getJSONObject(i);
						
						try{
							
							JSONObject obj = jsonTweet.getJSONObject("geo");
							
							if(obj!=null){
								Location myLocation = getLocation(getBaseContext());
								double distance;
								JSONArray arr = obj.getJSONArray("coordinates");
								tweetLat = (float) arr.getDouble(0);
								tweetLong = (float) arr.getDouble(1);
								Log.d("COORDTweet",Float.toString(tweetLat)+  "  " +Float.toString(tweetLong) );
								myLatitude = (float) 44.438254;
								myLongitute = (float) 26.051009;
								Log.d("COORDMY",Float.toString(myLatitude)+  "  " +Float.toString(myLongitute) );
								distance = distance(tweetLat,tweetLong, myLatitude, myLongitute);
								Log.d("Distance",Double.toString(distance));
								tweets.add(new TweetModel(jsonTweet.getJSONObject("user").getString("name"), jsonTweet.getString("created_at"), jsonTweet.getString("text"),(int)distance/1000));
								
								count++;
							}
							
							Log.d("TRY", "OK");
							
						}catch(JSONException e){
							Log.d("EXCP","NULL");
						}
						
					}
					else{
						break;
					}
				}
				
			}
			
			catch(ClientProtocolException e) {
				Log.e(TAG, e.getMessage(), e);
			}
			catch (IOException e ) {
				Log.e(TAG, e.getMessage(), e);
			}
			catch (JSONException e ) {
				Log.e(TAG, e.getMessage(), e);
			}
			return null;
			
		}
    	
    }
}