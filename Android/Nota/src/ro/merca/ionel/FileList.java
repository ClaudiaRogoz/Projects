package ro.merca.ionel;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Iterator;

import android.animation.AnimatorSet.Builder;
import android.app.ListActivity;
import android.content.Intent;
import android.os.Bundle;
import android.os.Environment;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.ArrayAdapter;
import android.widget.ListView;



public class FileList extends ListActivity {
	
	String[] listItems = {"explore","android"};
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		
		super.onCreate(savedInstanceState);
		setContentView(R.layout.main);
		
		writeFileToExternalStorage("nota10", "Ace4asta este o nota misto");
		
		
		ArrayList<String> files = Functions.ls(Environment.getExternalStorageDirectory().getAbsolutePath() + "/MyDir");
		
		System.out.println(files.size());
		Iterator<String> it = files.iterator();
		System.out.println(Environment.getExternalStorageDirectory().getAbsolutePath());
		while(it.hasNext()){
				  System.out.println(it.next());
		}
		
		final String[] file = (String[]) files.toArray(new String[0]);
		setListAdapter(new ArrayAdapter(this, android.R.layout.simple_list_item_1,file));
		
		ListView lv = getListView();
	      lv.setTextFilterEnabled(true);

	      lv.setOnItemClickListener(new OnItemClickListener() {
	        public void onItemClick(AdapterView<?> parent, View view,
	            int position, long id) {
	          // When clicked, show a toast with the TextView text
	        	String nameClicked = file[position];
	        	String content = readFileFromSDCard(Environment.getExternalStorageDirectory().getAbsolutePath() + "/MyDir", nameClicked);
	            Intent myIntent = new Intent(view.getContext(), EditView.class);
	            myIntent.putExtra("name",nameClicked);
	            myIntent.putExtra("content", content);
	            startActivityForResult(myIntent, 0);
	            
	        }
	      });

		
		
	}
	
	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		menu.add(1,1,1,"Nota Noua").setIcon(android.R.drawable.btn_default);
		return super.onCreateOptionsMenu(menu);
		
	}
	
	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		switch(item.getItemId()){
			case 1 : 
				Intent intent = new Intent(this, EditView.class);
		        startActivity(intent);
		        break;
			default:
				break;
		}
		return super.onOptionsItemSelected(item);
	}
	

	public static void writeFileToExternalStorage(String name, String txt) {
		String eol = System.getProperty("line.separator");
		BufferedWriter writer = null;
		File sdCard = Environment.getExternalStorageDirectory();
		File dir = new File (sdCard.getAbsolutePath() + "/MyDir");
		dir.mkdirs();
		File file = new File(dir, name);
		
		try {
			FileOutputStream f = new FileOutputStream(file);
			try {
				f.write(txt.getBytes());
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		

	}
	
	
	public void createFiles(){
		File folder = new File(Environment.getExternalStorageDirectory().getAbsolutePath());
		File[] files = folder.listFiles();
		if(files!=null){
			ArrayList<String> ret = new ArrayList<String>();
			for(int i = 0; i < files.length; i++){
				ret.add(files[i].getName());
			}
		
			for(int i = 0; i < 5; i++){
				
				if(!ret.contains("nota" + i )){
					writeFileToExternalStorage("nota" + i , "textul din nota");
				}
			}
		}else{
			System.out.println("de aici");
			for(int i = 0; i < 5; i++){
				writeFileToExternalStorage("nota" + i , "textul din nota");
			}
		}
		
	
		
	}
	
	@SuppressWarnings("unused")
	public static String readFileFromSDCard(String string , String fileName) {
		//File directory = Environment.getExternalStorageDirectory();
		// Assumes that a file article.rss is available on the SD card
		File file = new File(string + "/" + fileName);
		if (!file.exists()) {
			throw new RuntimeException("File not found");
		}
		
		Log.e("Testing", "Starting to read");
		BufferedReader reader = null;
		StringBuilder builder = new StringBuilder();
		try {
			reader = new BufferedReader(new FileReader(file));
			
			String line;
			while ((line = reader.readLine()) != null) {
				builder.append(line);
			}
		} catch (Exception e) {
			e.printStackTrace();
		} finally {
			if (reader != null) {
				try {
					reader.close();
				} catch (IOException e) {
					e.printStackTrace();
				}
			}
		}
		return builder.toString();
		
		
	}
	
}
