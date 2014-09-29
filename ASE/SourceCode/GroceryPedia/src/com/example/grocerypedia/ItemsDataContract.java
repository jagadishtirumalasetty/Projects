package com.example.grocerypedia;

import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.ArrayList;

import org.xmlpull.v1.XmlPullParser;
import org.xmlpull.v1.XmlPullParserFactory;

public class ItemsDataContract {

	public String ItemName;
	public String urlString;
	private ArrayList<StoreAndLocation> list;
	private XmlPullParserFactory xmlFactoryObject;
	public volatile boolean isParsed = true;
	
	public ArrayList<StoreAndLocation> getList() {
		return list;
	}

	

	public void getXML(){
	      Thread thread = new Thread(new Runnable(){
	         @Override
	         public void run() {
	            try {
	               URL url = new URL(urlString);
	               HttpURLConnection conn = (HttpURLConnection) 
	               url.openConnection();
	                  conn.setReadTimeout(10000);  /* milliseconds */
	                  conn.setConnectTimeout(15000);  /* milliseconds */
	                  conn.setRequestMethod("GET");
	                  conn.setDoInput(true);
	                  conn.connect();
	            InputStream stream = conn.getInputStream();

	            xmlFactoryObject = XmlPullParserFactory.newInstance();
	            XmlPullParser myparser = xmlFactoryObject.newPullParser();

	            myparser.setFeature(XmlPullParser.FEATURE_PROCESS_NAMESPACES
	            , false);
	            myparser.setInput(stream, null);
	            parseXMLAndStoreIt(myparser);
	            stream.close();
	            } catch (Exception e) {
	               e.printStackTrace();
	            }
	        }
	    });

	    thread.start(); 
	   }
	
	 public void parseXMLAndStoreIt(XmlPullParser myParser) {
	     StoreAndLocation store = null;
		 int event;
	      try {
	         event = myParser.getEventType();
	         while (event != XmlPullParser.END_DOCUMENT) {
	            String name=myParser.getName();
	            switch (event){
	               case XmlPullParser.START_DOCUMENT:
	            	   list= new ArrayList<StoreAndLocation>();
	               case XmlPullParser.START_TAG:
	            	   name= myParser.getName();
	            	   if(name == "Store"){
	            		   store = new StoreAndLocation();
	            	   }else if(store != null){
	            		   if(name == "string"){
	            			   store.Name = myParser.nextText();
	            		   }
	            	   }
	            	   
	               case XmlPullParser.END_TAG:
	            	   name = myParser.getName();
	            	   if(name.equalsIgnoreCase("Store") && store != null){
	            		   list.add(store);
	            	   }
	            }	 
	                  event = myParser.next(); 

	              }
	                 isParsed = false;
	      } catch (Exception e) {
	         e.printStackTrace();
	      }

	   }
	 
	 class StoreAndLocation {
			String Name;
			
		}
}
