package com.example.clouds;


import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Path;
import android.hardware.GeomagneticField;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.location.Location;
import android.os.Bundle;
import android.util.Config;
import android.util.Log;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.LinearLayout;

public class Activity1 extends Activity {
		 private float[] valuesAccelerometer;
		 private float[] valuesMagneticField;
		 
		 private float[] matrixR;
		 private float[] matrixI;
		 private float[] matrixValues;
		MyLocation mylocation;
		private double messagelat = 44.573182;
		private double messagelong =  27.132908;
		private double hislat = 44.573083;
		private double hislong = 27.133987;
		
		Button button;
	    private static final String TAG = "Compass";

	    private SensorManager mSensorManager;
	    private Sensor mSensor;
	    private SampleView mView;
	    private float[] mValues;
	    
	    private final SensorEventListener mListener = new SensorEventListener() {
	        public void onSensorChanged(SensorEvent event) {
	           
	            mValues = event.values;
	            Location msj = new Location(SENSOR_SERVICE);
	            Location mel = new Location(SENSOR_SERVICE);
	            msj.setLatitude(messagelat);
	            msj.setLongitude(messagelong);
	            mel.setLatitude(hislat);
	            mel.setLongitude(hislong);
	            float bearing = mel.bearingTo(msj);
	            mValues[0] -=  bearing;
	            if (mView != null) {
	                mView.invalidate();
	            }
	            

	        	
	        	switch(event.sensor.getType()){
	        	  case Sensor.TYPE_ACCELEROMETER:
	        	   for(int i =0; i < 3; i++){
	        	    valuesAccelerometer[i] = event.values[i];
	        	   }
	        	   break;
	        	  case Sensor.TYPE_MAGNETIC_FIELD:
	        	   for(int i =0; i < 3; i++){
	        	    valuesMagneticField[i] = event.values[i];
	        	   }
	        	   break;
	        	  }
	        	   
	        	  boolean success = SensorManager.getRotationMatrix(
	        	       matrixR,
	        	       matrixI,
	        	       valuesAccelerometer,
	        	       valuesMagneticField);
	        	   
	        	  if(success){
	        	   SensorManager.getOrientation(matrixR, matrixValues);
	        	   
	        	   double azimuth = Math.toDegrees(matrixValues[0]);
	        	   double pitch = Math.toDegrees(matrixValues[1]);
	        	   double roll = Math.toDegrees(matrixValues[2]);
	        	   System.out.println(matrixValues[0]);
	        	  }
	        }

	        public void onAccuracyChanged(Sensor sensor, int accuracy) {
	        }
	    };

		@Override
	    protected void onCreate(Bundle savedInstanceState) {
		   super.onCreate(savedInstanceState);
		   this.setContentView(R.layout.activity_clouds);
		   mylocation = new MyLocation(this);
		   valuesAccelerometer = new float[3];
	       valuesMagneticField = new float[3];
	       
	       matrixR = new float[9];
	       matrixI = new float[9];
	       matrixValues = new float[3];
	       
		   double distance = distance (hislat, hislong, messagelat, messagelong);
		   Log.d("Distance",Double.toString(distance));
		   mSensorManager = (SensorManager)getSystemService(Context.SENSOR_SERVICE);
	       mSensor = mSensorManager.getDefaultSensor(Sensor.TYPE_ORIENTATION);
	       mView = new SampleView(this,Integer.toString((int)distance) + " m " + "  " +Double.toString(mylocation.lat) + "  " +Double.toString(mylocation.lng));
	       
	       if (distance <= 200) {
	    	   LinearLayout ll = (LinearLayout)findViewById(R.id.btn);
	    	   Button b = new Button(this);
	    	   b.setText("Open camera");
	    	   ll.addView(b);
	    	   
	    	   b.setOnClickListener(new OnClickListener() {

		    	   @Override
		    	   public void onClick(View v) {
		    		   
		    		   Intent myIntent = new Intent(Activity1.this, CameraPreview.class);
			    	   startActivity(myIntent);
		    	   }
	    	   });
	       }
	       
	       LinearLayout mylin = (LinearLayout) findViewById(R.id.linear);
	       mylin.addView(mView);
	   }
		
		
	    @Override
	    protected void onResume()
	    {
	        if (Config.LOGD) Log.d(TAG, "onResume");
	        super.onResume();

	        mSensorManager.registerListener(mListener, mSensor,
	                SensorManager.SENSOR_DELAY_GAME);
	    }
	    
	    @Override
	    protected void onStop()
	    {
	        if (Config.LOGD) Log.d(TAG, "onStop");
	        mSensorManager.unregisterListener(mListener);
	        super.onStop();
	    }

	   

		public static double distance(double lat_a, double lng_a, double lat_b, double lng_b) {
		    double pk = (double) (180/3.14169);

		    double a1 = lat_a / pk;
		    double a2 = lng_a / pk;
		    double b1 = lat_b / pk;
		    double b2 = lng_b / pk;
		    
		    double t1 = Math.cos(a1)*Math.cos(a2)*Math.cos(b1)*Math.cos(b2);
		    double t2 = Math.cos(a1)*Math.sin(a2)*Math.cos(b1)*Math.sin(b2);
		    double t3 = Math.sin(a1)*Math.sin(b1);
		    double tt = Math.acos(t1 + t2 + t3);
		    
		    return 6366000*tt;
		}
		
		
		private class SampleView extends View {
		        private Paint   mPaint = new Paint();
		        private Path    mPath = new Path();
		        private boolean mAnimate;
		        String distance ;
		        public SampleView(Context context,String distance) {
		            super(context);

		            // Construct a wedge-shaped path
		            mPath.moveTo(0, -50);
		            mPath.lineTo(-20, 60);
		            mPath.lineTo(0, 50);
		            mPath.lineTo(20, 60);
		            mPath.close();
		            this.distance = distance;
		        }
		        
		        @Override 
		        protected void onDraw(Canvas canvas) {
		            Paint paint = mPaint;

		            canvas.drawColor(Color.WHITE);
		            
		            paint.setAntiAlias(true);
		            paint.setColor(Color.BLACK);
		            paint.setStyle(Paint.Style.FILL);

		            int w = canvas.getWidth();
		            int h = canvas.getHeight();
		            int cx = w / 2;
		            int cy = h / 2;
		            canvas.save();
		            
		            canvas.translate(cx, cy);
		            if (mValues != null) {            
		                canvas.rotate(-mValues[0]);
		            }
		            
		            canvas.drawPath(mPath, mPaint);
		            canvas.restore();
		            Paint paint1 = new Paint(); 
		            
		            paint1.setColor(Color.BLACK); 
		            paint1.setTextSize(25); 
		            canvas.drawText(distance, 10, 25, paint1); 
		            
		        }
		    
		        @Override
		        protected void onAttachedToWindow() {
		            mAnimate = true;
		            super.onAttachedToWindow();
		        }
		        
		        @Override
		        protected void onDetachedFromWindow() {
		            mAnimate = false;
		            super.onDetachedFromWindow();
		        }
		    }
}
