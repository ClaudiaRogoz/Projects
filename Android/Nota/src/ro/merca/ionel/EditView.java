package ro.merca.ionel;


import java.io.File;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.os.Environment;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.EditText;
import android.widget.TextView;

public class EditView extends Activity {
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.second);
		Intent intent = getIntent();
		Bundle extras = getIntent().getExtras();
		String numefis = new String();
		String content = new String();
		if(extras !=null) {
			numefis = extras.getString("name");
			content = extras.getString("content");
		}
		EditText editText = (EditText) findViewById(R.id.name);
		editText.setText(numefis);
		editText = (EditText)findViewById(R.id.text);
		editText.setText(content);
		
		
		
	}	
	
	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		menu.add(1,1,1,"Salveaza Nota").setIcon(android.R.drawable.btn_default);
		menu.add(1,2,2,"Anuleaza Modificari").setIcon(android.R.drawable.btn_default);
		menu.add(1,3,3,"Sterge Nota").setIcon(android.R.drawable.btn_default);
		menu.add(1,4,4,"Share").setIcon(android.R.drawable.btn_default);
		
		return super.onCreateOptionsMenu(menu);
		
	}
	
	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		switch(item.getItemId()){
			case 1 : 
				TextView tv = new TextView(this);
				final TextView name = (TextView) findViewById(R.id.name);
				final TextView text = (TextView) findViewById(R.id.text);
				String filename = name.getText().toString();
				String cont = text.getText().toString();
				FileList.writeFileToExternalStorage(filename, cont);
				Intent intent = new Intent(this,FileList.class);
		        startActivity(intent);
		        finish();
		        break;
			case 2 :
				EditText editText = (EditText) findViewById(R.id.name);
				editText.setText("");
				editText = (EditText)findViewById(R.id.text);
				editText.setText("");
				
				break;
			case 3 :
				TextView tv1 = new TextView(this);
				final TextView name1 = (TextView) findViewById(R.id.name);
				Log.d("MSG", name1.getText().toString());
				File filen = new File(Environment.getExternalStorageDirectory() + "/MyDir/" + name1.getText().toString());
				filen.delete();
				intent = new Intent(this,FileList.class);
		        startActivity(intent);
		        finish();
				break;
			case 4 : 
				break;
			default:
				break;
		}
		return super.onOptionsItemSelected(item);
	}
	
	
	
}
