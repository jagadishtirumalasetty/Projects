package ase.spp64.shopeasy;

import java.util.ArrayList;

import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup;
import android.webkit.WebView.FindListener;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ListView;

public class GroceryFragment extends Fragment {
	
	/** Items entered by the user is stored in this ArrayList variable */
    ArrayList<String> list = new ArrayList<String>();
 
    /** Declaring an ArrayAdapter to set items to ListView */
    ArrayAdapter<String> adapter;
    View rootView;
    ListView list2;
	
	 @Override
	    public View onCreateView(LayoutInflater inflater, ViewGroup container,
	            Bundle savedInstanceState) {
	 
	        rootView = inflater.inflate(R.layout.fragament_grocery, container, false);
	         
	       
	        
	        /** Reference to the button of the layout main.xml */
	        Button btn = (Button) rootView.findViewById(R.id.btnAdd);
	        
	        
	 
	        /** Defining the ArrayAdapter to set items to ListView */
	        adapter = new ArrayAdapter<String>(getActivity().getBaseContext(), android.R.layout.simple_list_item_1, list);
	 
	        list2 = (ListView) rootView.findViewById(R.id.list);
	        
	        /** Defining a click event listener for the button "Add" */
	        OnClickListener listener = new OnClickListener() {
	            @Override
	            public void onClick(View v) {
	                EditText edit = (EditText) rootView.findViewById(R.id.txtItem);
	                list.add(edit.getText().toString());
	                edit.setText("");
	                adapter.notifyDataSetChanged();
	            }
	        };
	 
	        /** Setting the event listener for the add button */
	        btn.setOnClickListener(listener);
	 
	        /** Setting the adapter to the ListView */
	        //setListAdapter(adapter);
	        list2.setAdapter(adapter);
	        
	        return rootView;
	    }
}
