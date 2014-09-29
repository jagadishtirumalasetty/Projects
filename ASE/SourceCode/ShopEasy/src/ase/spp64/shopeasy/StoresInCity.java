package ase.spp64.shopeasy;

import java.io.IOException;
import java.util.ArrayList;
import java.util.List;
import java.util.Locale;

import android.app.Activity;
import android.content.Intent;
import android.location.Address;
import android.location.Geocoder;
import android.os.AsyncTask;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.LinearLayout;
import ase.spp64.shopeasy.ParseXML.StoreAndLocation;

public class StoresInCity extends Activity {

	private String url1 = "http://www.SupermarketAPI.com/api.asmx/StoresByCityState?APIKEY=";
	private String url2 = "&SelectedCity=";
	private String url3 = "&SelectedState=";
	public ParseXML obj;
	private String state;
	private String city;
	ArrayList<StoreAndLocation> list;
	double latitude;
	double longitude;
	LinearLayout linear;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_stores_in_city);

		Bundle bundle = getIntent().getExtras();
		if (bundle != null) {
			state = bundle.getString("state");
			city = bundle.getString("city");
		}
		// list = getStores();

		linear = (LinearLayout) findViewById(R.id.storesInCity);

		new getLocation().execute();
		if (list != null) {
			int size = list.size();

			if (size != 0) {
				for (int i = 0; i < size; i++) {
					LinearLayout.LayoutParams params = new LinearLayout.LayoutParams(
							LinearLayout.LayoutParams.MATCH_PARENT,
							LinearLayout.LayoutParams.WRAP_CONTENT);
					Button btn = new Button(this);
					btn.setId(i);
					final int id_ = btn.getId();

					StoreAndLocation location = list.get(i);

					btn.setText(location.eStoreName + "\n" + location.eAddress);

					String locationName = location.eAddress + ","
							+ location.eCity + "," + location.eState;
					Geocoder geocoder = new Geocoder(getBaseContext(),
							Locale.getDefault());
					List<Address> addresses = null;
					try {
						addresses = geocoder.getFromLocationName(locationName,
								3);
					} catch (IOException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
					Address address = (Address) addresses.get(0);

					latitude = address.getLatitude() * 1E6;
					longitude = address.getLongitude() * 1E6;

					linear.addView(btn, params);
					btn = ((Button) findViewById(id_));
					btn.setOnClickListener(new View.OnClickListener() {
						public void onClick(View view) {
							Intent i = new Intent(StoresInCity.this,
									MapDirections.class);
							i.putExtra("latitude", latitude);
							i.putExtra("long", longitude);
							startActivity(i);
						}
					});
				}
			}
		}

	}

	public ArrayList<StoreAndLocation> getStores() {
		String url = url1 + StoreFinder.SUPERMARKET_APIKEY + url2 + city + url3
				+ state;
		obj = new ParseXML(url);
		obj.getXML();
		while (obj.isParsed)
			;

		return obj.getList();

	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.stores_in_city, menu);
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

	public class getLocation
			extends
			AsyncTask<List<StoreAndLocation>, Void, ArrayList<StoreAndLocation>> {

		@Override
		protected void onPreExecute() {
			// TODO Auto-generated method stub
			super.onPreExecute();
		}

		@Override
		protected void onPostExecute(ArrayList<StoreAndLocation> result) {
			// TODO Auto-generated method stub

			// super.onPostExecute(result);
			list = result;
		}

		@Override
		protected void onProgressUpdate(Void... values) {
			// TODO Auto-generated method stub
			super.onProgressUpdate(values);
		}

		@Override
		protected ArrayList<StoreAndLocation> doInBackground(
				List<StoreAndLocation>... params) {
			// TODO Auto-generated method stub
			ArrayList<StoreAndLocation> arrayList = getStores();
			// list = getStores();
			return arrayList;
		}

	}
}
