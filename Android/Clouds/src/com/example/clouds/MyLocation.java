package com.example.clouds;

import android.content.Context;
import android.location.Location;
import android.location.LocationListener;
import android.location.LocationManager;
import android.os.AsyncTask;
import android.os.Bundle;
import android.widget.Toast;

public class MyLocation  {
	Context mContext;
	LocationManager mlocManager;
	LocationListener mlocListener;
	double  lat=0,lng=0;
	
	public MyLocation(Context mContext) {
	
		super();
		this.mContext = mContext;
		mlocManager = (LocationManager)mContext.getSystemService(mContext.LOCATION_SERVICE);
		mlocListener = new MyLocationListener();
		mlocManager.requestLocationUpdates( LocationManager.NETWORK_PROVIDER, 0, 0, mlocListener);
		
	}


	/* Class My Location Listener */



	public class MyLocationListener implements LocationListener {
		private static final int TWO_MINUTES = 1000 * 60 * 2;
		
		@Override
		public void onLocationChanged(Location loc)	{
			loc.getLatitude();
			loc.getLongitude();
			
			String Text = "My current location is: " +"Latitud = " + loc.getLatitude() +"Longitud = " + loc.getLongitude();
		//	Toast.makeText( mContext,Text,Toast.LENGTH_SHORT).show();
			lat = loc.getLatitude();
			lng = loc.getLongitude();
		}
		@Override
		public void onProviderDisabled(String provider){
			Toast.makeText(mContext,"Gps Disabled",Toast.LENGTH_SHORT ).show();
		}
		
		@Override
		public void onProviderEnabled(String provider){
			Toast.makeText( mContext," Gps Enabled" ,Toast.LENGTH_SHORT).show();
		}
		
		@Override
		public void onStatusChanged(String provider, int status, Bundle extras) {
			// TODO Auto-generated method stub
			
		}

		


	}
}
