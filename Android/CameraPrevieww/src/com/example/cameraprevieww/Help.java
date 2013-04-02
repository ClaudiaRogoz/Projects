package com.example.cameraprevieww;

import java.util.ArrayList;
import java.util.Iterator;
import android.content.Context;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Paint.Align;
import android.util.Log;
import android.view.View;

class DrawOnTop extends View { 

    public DrawOnTop(Context context) { 
            super(context); 
            // TODO Auto-generated constructor stub 
    } 

    @Override 
    protected void onDraw(Canvas canvas) { 
            // TODO Auto-generated method stub 
            super.onDraw(canvas); 
            
    } 

} 
class Marker extends View { 
	float  mijloc;
	private static int N = 290;
	private static int E = 20;
	private static int S = 110;
	private static int V = 200;
	public ArrayList<MyData> lista = ((CameraPreview)getContext()).lista;
	public MyLocation mylocation = ((CameraPreview)getContext()).myLocation;
	
    public Marker(Context context) { 
            super(context); 
            // TODO Auto-generated constructor stub 
    } 
    public void updateMarker(float  valoare ){
    	this.mijloc= valoare;
    }
    public Marker(Context context,float mijloc2) { 
        super(context); 
        this.mijloc=mijloc2;
        // TODO Auto-generated constructor stub 
    } 
    public void showlist(){
    	Iterator<MyData> it = lista.iterator();
    	while(it.hasNext()){
    		Log.d("LOG", it.next().toString());
    	}
    }
    /**
     * Params: lat1, long1 => Latitude and Longitude of current point
     *         lat2, long2 => Latitude and Longitude of target  point
     *         
     *         headX       => x-Value of built-in phone-compass
     * 
     * Returns the degree of a direction from current point to target point
     *
     */
    double getDegrees(double lat1 ,double  long1,double  lat2,double  long2,double headX) {
    	
    	double dLat = Math.toRadians(lat2-lat1);
    	double dLon = Math.toRadians(long2-long1);

        lat1 = Math.toRadians(lat1);
        lat2 = Math.toRadians(lat2);

        double y = Math.sin(dLon) * Math.cos(lat2);
        double x = Math.cos(lat1)*Math.sin(lat2) -
                Math.sin(lat1)*Math.cos(lat2)*Math.cos(dLon);
        double brng = Math.toDegrees(Math.atan2(y, x));
        // fix negative degrees
        if(brng<0) {
            brng=360-Math.abs(brng);
        }

        return brng;
    }
    
    @Override  
    protected void onDraw(Canvas canvas) { 
            // TODO Auto-generated method stub 
    		showlist();
            Paint paint = new Paint(); 
            paint.setStyle(Paint.Style.FILL); 
            paint.setColor(Color.RED); 
            paint.setTextAlign(Align.CENTER);
            paint.setTextSize(30);
            int width = this.getWidth(); 
            int height = this.getHeight(); 
            canvas.drawText(mijloc + "", width/2, height/2, paint); 
            double parte = this.getWidth() / 90;
            int todraw = 0;
            if(245 < mijloc && mijloc <= 335){
            	todraw = (int) (width/2 + (N - mijloc) * parte);
            	 Bitmap mBitmap2   = BitmapFactory.decodeResource(getResources(), R.drawable.nord);
                 canvas.drawBitmap(mBitmap2, todraw, 120, paint);
            }else if((335 < mijloc && mijloc <= 360 )){
            	todraw = (int) (width/2 + (E + 360 - mijloc) * parte);
            	Bitmap mBitmap2   = BitmapFactory.decodeResource(getResources(), R.drawable.est);
            	canvas.drawBitmap(mBitmap2, todraw, 120, paint);
            	
    		}else if((0 <= mijloc && mijloc <= 65)){
            	 todraw = (int) (width/2 + (E - mijloc) * parte);
            	 Bitmap mBitmap2   = BitmapFactory.decodeResource(getResources(), R.drawable.est);
                 canvas.drawBitmap(mBitmap2, todraw, 120, paint);
            }else if(65 < mijloc && mijloc <= 155){
            	
            	 todraw = (int) (width/2 + (S - mijloc) * parte);
            	 Bitmap mBitmap2   = BitmapFactory.decodeResource(getResources(), R.drawable.sud);
                 canvas.drawBitmap(mBitmap2,  todraw, 120, paint);
                 
            }else if(155 < mijloc && mijloc <= 245){
            	 todraw = (int) (width/2 + (V - mijloc) * parte);
            	 Bitmap mBitmap2   = BitmapFactory.decodeResource(getResources(), R.drawable.vest);
                 canvas.drawBitmap(mBitmap2, todraw, 120, paint);
            }
            
            Iterator<MyData> it = lista.iterator();
            while(it.hasNext()){
            	MyData data = it.next();
            	double brng = getDegrees(mylocation.lat, mylocation.lng, data.lat,data.lng, mijloc);
            	
            	if((brng - 45) < mijloc && mijloc <= (brng + 45) ){
            		int drw = (int) (width/2 + (brng - mijloc) * parte);
            		Bitmap mBitmap2   = BitmapFactory.decodeResource(getResources(), R.drawable.vest);
                    canvas.drawBitmap(mBitmap2, drw, 120, paint);
            	}
            }
            
            
            
            
            
            super.onDraw(canvas); 
    } 

}

class MarkerViews extends View { 
	ArrayList<MyData> l;	
	double  azimuth;
	double  srclat,srclng;
	double aux;	
    public MarkerViews(Context context) { 
            super(context); 
            // TODO Auto-generated constructor stub 
    } 
    public void updateMarker(){
    }
    public MarkerViews(Context context,ArrayList<MyData> l,	double  azimuth,double srclat,double srclng) { 
        super(context); 
        this.l = l;
        this.azimuth= azimuth;
        this.srclat=srclat;
        this.srclng=srclng;
        // TODO Auto-generated constructor stub 
} 
    @Override  
    protected void onDraw(Canvas canvas) { 
            // TODO Auto-generated method stub 

    	
            super.onDraw(canvas); 
    } 


}

