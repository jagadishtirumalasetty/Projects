package ase.spp64.shopeasy;

import android.app.Activity;
import android.content.Intent;
import android.os.AsyncTask;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

public class StoreFinder extends Activity {

	public static final String SUPERMARKET_APIKEY ="c613445d26";
	String zip;
	private String state;
	private String city; 
	EditText zipText;
	EditText cityText;
	EditText stateText;
	
	
	
	Button findNearBy;
	Button findStores;
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_store_finder);
		findNearBy = (Button) findViewById(R.id.findNearBy);
		
		zipText = (EditText) findViewById(R.id.zip);
		zip = zipText.getText().toString();
		
		findNearBy.setOnClickListener(new View.OnClickListener() {
			
			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				Intent i = new Intent(StoreFinder.this, StoreNearBy.class);
				i.putExtra("zip", zip);
				startActivity(i);
				
			}
		});
		
		findStores = (Button) findViewById(R.id.findStores);
		cityText =  (EditText) findViewById(R.id.City);
		stateText = (EditText) findViewById(R.id.State);
		
		state = stateText.getText().toString();
		city = cityText.getText().toString();
		findStores.setOnClickListener(new View.OnClickListener() {
			
			@Override
			public void onClick(View v) {
				// TODO Auto-generated method stub
				Intent i = new Intent(StoreFinder.this, StoresInCity.class);
				i.putExtra("state", state);
				i.putExtra("city", city);
				startActivity(i);
				
			}
		});
	}
	
	
	

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.store_finder, menu);
		return true;
	}

	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		// Handle action bar item clicks here. The action bar will
		// automatically handle clicks on the Home/Up button, so long
		// as you specify a parent activity in AndroidManifest.xml.
		int id = item.getItemId();
		if (id == R.id.action_settings) {
			return true;
		}
		return super.onOptionsItemSelected(item);
	}
	
	
}
