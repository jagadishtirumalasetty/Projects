package ase.spp64.shopeasy;

import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;

public class BarcodeFragment extends Fragment{

	View rootView;
	
	 @Override
	    public View onCreateView(LayoutInflater inflater, ViewGroup container,
	            Bundle savedInstanceState) {
	 
	        rootView = inflater.inflate(R.layout.fragment_barcode, container, false);
	        return rootView;
	 }
	        	
}
