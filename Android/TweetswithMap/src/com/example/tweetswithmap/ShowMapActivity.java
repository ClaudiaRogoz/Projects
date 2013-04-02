package com.example.tweetswithmap;

import android.content.Context;
import android.content.Intent;
import android.graphics.drawable.Drawable;
import android.os.Bundle;

import com.google.android.maps.GeoPoint;
import com.google.android.maps.MapActivity;
import com.google.android.maps.MapController;
import com.google.android.maps.MapView;
import com.google.android.maps.OverlayItem;

public class ShowMapActivity extends MapActivity{
    private MapController mapControll;
    private GeoPoint geoPoint=null;
    private MapView mapview;
    private MyItemizedOverlay userPicOverlay;
    private MyItemizedOverlay nearPicOverlay;
    private Drawable userPic,atmPic;
    private OverlayItem nearatms[] = new OverlayItem[50];
    public static Context context;
    private float latitude, longitude;
    @Override
    protected void onCreate(Bundle icicle) {
        // TODO Auto-generated method stub
        super.onCreate(icicle);
        context = getApplicationContext();
        setContentView(R.layout.map);
        Intent intent = getIntent();
        latitude = intent.getFloatExtra("mylat", 0);
        longitude = intent.getFloatExtra("mylong",0);
        
        showMap();
        
    }

    @SuppressWarnings("deprecation")
	public void showMap() {
        // TODO Auto-generated method stub
    	
        try {
            geoPoint = new GeoPoint((int)(latitude * 1E6),(int)(longitude * 1E6));          
            mapview = (MapView)findViewById(R.id.mapview);
            mapControll= mapview.getController();
            mapview.setBuiltInZoomControls(true);
            mapview.setStreetView(false);
            mapControll.setZoom(16);
            mapControll.animateTo(geoPoint);

            userPic = this.getResources().getDrawable(R.drawable.ic_action_search);
            userPicOverlay = new MyItemizedOverlay(userPic);
            OverlayItem overlayItem = new OverlayItem(geoPoint, "I'm Here!!!", null);
            userPicOverlay.addOverlay(overlayItem);
            mapview.getOverlays().add(userPicOverlay);


            atmPic = this.getResources().getDrawable(R.drawable.ic_action_search);
            nearPicOverlay = new MyItemizedOverlay(atmPic);
            for (int i = 0; i < 2; i++) {
                nearatms[i] = new OverlayItem(new GeoPoint((int)((latitude) * 1E6),(int) ((int)(longitude) * 1E6)),"Name", null);//just check the brackets i just made change here so....
                nearPicOverlay.addOverlay(nearatms[i]);
            }
            mapview.getOverlays().add(nearPicOverlay);
            //Added symbols will be displayed when map is redrawn so force redraw now
            mapview.postInvalidate();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    @Override
    protected boolean isRouteDisplayed() {
        // TODO Auto-generated method stub
        return false;
    }

}