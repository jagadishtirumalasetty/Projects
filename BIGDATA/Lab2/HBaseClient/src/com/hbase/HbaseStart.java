package com.hbase;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.FSDataInputStream;
import org.apache.hadoop.fs.FSDataOutputStream;
import org.apache.hadoop.fs.FileStatus;
import org.apache.hadoop.fs.FileSystem;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.hbase.HBaseConfiguration;
import org.apache.hadoop.hbase.HColumnDescriptor;
import org.apache.hadoop.hbase.HTableDescriptor;
import org.apache.hadoop.hbase.KeyValue;
import org.apache.hadoop.hbase.MasterNotRunningException;
import org.apache.hadoop.hbase.ZooKeeperConnectionException;
import org.apache.hadoop.hbase.client.Get;
import org.apache.hadoop.hbase.client.HBaseAdmin;
import org.apache.hadoop.hbase.client.HTable;
import org.apache.hadoop.hbase.client.Put;
import org.apache.hadoop.hbase.client.Result;
import org.apache.hadoop.hbase.client.ResultScanner;
import org.apache.hadoop.hbase.client.Scan;
import org.apache.hadoop.hbase.util.Bytes;

public class HbaseStart
{
	static public void main(String args[]) throws IOException {
		
		//createTable();
		insertTable();
	//	retrieveTable();
	//	deleteTable();
		//getAllRow();
	//	getAllTable();
		}
	
	
	public static void createTable() throws IOException
	{
		Configuration config = HBaseConfiguration.create();		 
		config.clear();
         config.set("hbase.zookeeper.quorum", "134.193.136.147");
         config.set("hbase.zookeeper.property.clientPort","2181");
         config.set("hbase.master", "134.193.136.147:60010");
		
		HBaseAdmin admin = new HBaseAdmin(config);
		
		try {
			// HBaseConfiguration hc = new HBaseConfiguration(new Configuration());
			
			  HTableDescriptor ht = new HTableDescriptor("SensorL2T3014"); 
			  
			  ht.addFamily( new HColumnDescriptor("Date"));
			  
			  ht.addFamily( new HColumnDescriptor("AccelerometerX"));
			  ht.addFamily( new HColumnDescriptor("AccelerometerY"));
			  ht.addFamily( new HColumnDescriptor("AccelerometerZ"));
			  
			  ht.addFamily( new HColumnDescriptor("Humidity"));
			  
			  ht.addFamily( new HColumnDescriptor("Gyro1"));

		  ht.addFamily( new HColumnDescriptor("Gyro2"));
		  ht.addFamily( new HColumnDescriptor("Gyro3"));  
		  
			  
			  
			  
			  
			  
		//	  ht.addFamily( new HColumnDescriptor("y"));
			  
		//	  ht.addFamily( new HColumnDescriptor("z"));
			  
			  System.out.println( "connecting" );

			  HBaseAdmin hba = new HBaseAdmin( config );

			  System.out.println( "Creating Table" );

			  hba.createTable( ht );

			  System.out.println("Done......");
			  
			  	
        } finally {
            admin.close();
        }
		
		
	}
	
	
	public static void insertTable() throws IOException{
	
		Configuration config = HBaseConfiguration.create();		 
		config.clear();
         config.set("hbase.zookeeper.quorum", "134.193.136.147");
         config.set("hbase.zookeeper.property.clientPort","2181");
         config.set("hbase.master", "134.193.136.147:60010");
         
         
         String Date="",x="",y="",z="",d="",x1="",x2="",x3="";
         

		  HTable table = new HTable(config, "SensorL2T3014");
	
		  //Put p = new Put(Bytes.toBytes("row1"));
		  
		  int count=1;
		  int timestamp=10000;
         
        BufferedReader br = null;
         
 		try {
  
 			String sCurrentLine;
  
 			br = new BufferedReader(new FileReader("3014.txt"));
  
 			while ((sCurrentLine = br.readLine()) != null) {
 				
 				 Put p = new Put(Bytes.toBytes("row1"),timestamp);
 				
 				if(sCurrentLine.equals(""))
 				{
 					continue;
 				}
 				
 				String[] array = sCurrentLine.split("\t");
 				Date = array[0];
 				x=array[1];
 				y=array[2];
 				z=array[3];
 				d=array[4];
 				x1=array[5];
 				x2=array[6];
 				x3=array[7];
 				  
 				 p.add(Bytes.toBytes("Date"), Bytes.toBytes("col"+(count)),Bytes.toBytes(Date));
 				p.add(Bytes.toBytes("AccelerometerX"), Bytes.toBytes("col"+(count+1)),Bytes.toBytes(x));
 				p.add(Bytes.toBytes("AccelerometerY"), Bytes.toBytes("col"+(count+2)),Bytes.toBytes(y));
 				p.add(Bytes.toBytes("AccelerometerZ"), Bytes.toBytes("col"+(count+3)),Bytes.toBytes(z));
 				p.add(Bytes.toBytes("Humidity"), Bytes.toBytes("col"+(count+4)),Bytes.toBytes(d));
 				p.add(Bytes.toBytes("Gyro1"), Bytes.toBytes("col"+(count)),Bytes.toBytes(x1));
 				p.add(Bytes.toBytes("Gyro2"), Bytes.toBytes("col"+(count)),Bytes.toBytes(x2));
 				p.add(Bytes.toBytes("Gyro3"), Bytes.toBytes("col"+(count)),Bytes.toBytes(x3));
 				 //p.add(Bytes.toBytes("GeoLocation"), Bytes.toBytes("col"+count),Bytes.toBytes(latitude+","+longitude));
 				  
 				// p.add(Bytes.toBytes("longitude"), Bytes.toBytes("col"+(count+1)),Bytes.toBytes(longitude));
 				 
 				// p.add(Bytes.toBytes("Date"), Bytes.toBytes("col"+(count+2)),Bytes.toBytes(Date));
 				 
 				 //p.add(Bytes.toBytes("Accelerometer"), Bytes.toBytes("col"+(count+3)),Bytes.toBytes(x+","+y+","+z));
 				 
 			//	p.add(Bytes.toBytes("y"), Bytes.toBytes("col"+(count+4)),Bytes.toBytes(y));
 				
 			//	p.add(Bytes.toBytes("z"), Bytes.toBytes("col"+(count+5)),Bytes.toBytes(z));

 			      table.put(p);
 			      
 			      count=count+1;
 			      timestamp=timestamp+1;
 				
 			}
  
 		} catch (IOException e) {
 			e.printStackTrace();
 		} finally {
 			try {
 				if (br != null)br.close();
 			} catch (IOException ex) {
 				ex.printStackTrace();
 			}
 		}
         
         
		
		
	  
	    
	}
	
	
	public static void retrieveTable() throws IOException{
		
		Configuration config = HBaseConfiguration.create();		 
		config.clear();
         config.set("hbase.zookeeper.quorum", "134.193.136.127");
         config.set("hbase.zookeeper.property.clientPort","2181");
         config.set("hbase.master", "134.193.136.127:60010");
		
		
		  HTable table = new HTable(config, "SensorTagTable3");
		
		 Get g = new Get(Bytes.toBytes("row1"));

		  Result r = table.get(g);

		  byte [] value = r.getValue(Bytes.toBytes("latitude"),Bytes.toBytes("col1"));

		  byte [] value1 = r.getValue(Bytes.toBytes("longitude"),Bytes.toBytes("col2"));

		  byte [] value2 = r.getValue(Bytes.toBytes("Date"),Bytes.toBytes("col3"));
		  
		  byte [] value3 = r.getValue(Bytes.toBytes("x"),Bytes.toBytes("col4"));
		  
		  byte [] value4 = r.getValue(Bytes.toBytes("y"),Bytes.toBytes("col5"));
		  
		  byte [] value5 = r.getValue(Bytes.toBytes("z"),Bytes.toBytes("col6"));
		  
		  String valueStr = Bytes.toString(value);

		  String valueStr1 = Bytes.toString(value1);
		  
		  String valueStr2 = Bytes.toString(value2);
		  
		  String valueStr3 = Bytes.toString(value3);
		  
		  String valueStr4 = Bytes.toString(value4);
		  
		  String valueStr5 = Bytes.toString(value5);

		  System.out.println("GET: " +"latitude: "+ valueStr+"longitude: "+valueStr1);
		  System.out.println("GET: " +"Date: "+ valueStr2);
		  System.out.println("GET: " +"x: "+ valueStr3);
		  System.out.println("GET: " +"y: "+ valueStr4);
		  System.out.println("GET: " +"z: "+ valueStr5);

		  

		  Scan s = new Scan();

		  s.addColumn(Bytes.toBytes("latitude"), Bytes.toBytes("col1"));

		  s.addColumn(Bytes.toBytes("longitude"), Bytes.toBytes("col2"));

		  ResultScanner scanner = table.getScanner(s);

		  try
		  {
		   for (Result rr = scanner.next(); rr != null; rr = scanner.next())
		   {
		    System.out.println("Found row : " + rr);
		   }
		  } finally
		  {
		   // Make sure you close your scanners when you are done!
		   scanner.close();
		  }
		
	}
	
	
	public static void deleteTable() throws IOException{
		
		Configuration config = HBaseConfiguration.create();		 
		config.clear();
         config.set("hbase.zookeeper.quorum", "134.193.136.127");
         config.set("hbase.zookeeper.property.clientPort","2181");
         config.set("hbase.master", "134.193.136.127:60010");
         
         HBaseAdmin admin = new HBaseAdmin(config);
         admin.disableTable("SensorTagTable");
         admin.deleteTable("SensorTagTable");

	}
	
	public static void getAllRow() throws IOException
	{
		Configuration config = HBaseConfiguration.create();		 
		config.clear();
         config.set("hbase.zookeeper.quorum", "134.193.136.127");
         config.set("hbase.zookeeper.property.clientPort","2181");
         config.set("hbase.master", "134.193.136.127:60010");
         
         HTable table = new HTable(config, "SensorTagTable");
         Get g = new Get(Bytes.toBytes("row1"));

		  Result r = table.get(g);
         for(KeyValue kv : r.raw()){
             System.out.print(new String(kv.getRow()) + " " );
             System.out.print(new String(kv.getFamily()) + ":" );
             System.out.print(new String(kv.getQualifier()) + " " );
             System.out.print(kv.getTimestamp() + " " );
             System.out.println(new String(kv.getValue()));
         }
         
   /*      for(KeyValue kv : r.raw()){
        	 
        	 String familyname = new String(kv.getFamily());
            
        	 if(familyname.equals("Accelerometer"))
        	 {
        		 System.out.println("=============="+familyname+"==============");
        		 System.out.print(new String(kv.getQualifier())+":");
        		 System.out.println(new String(kv.getValue()));
        	 }
        	 
         }*/
	}
	
	public static void getAllTable() throws IOException
	{
		Configuration config = HBaseConfiguration.create();		 
		config.clear();
         config.set("hbase.zookeeper.quorum", "134.193.136.127");
         config.set("hbase.zookeeper.property.clientPort","2181");
         config.set("hbase.master", "134.193.136.127:60010");
		
		try{
            HTable table = new HTable(config, "SensorTagTable");
            Scan s = new Scan();
            ResultScanner ss = table.getScanner(s);
            for(Result r:ss){
                for(KeyValue kv : r.raw()){
                   System.out.print(new String(kv.getRow()) + " ");
                   System.out.print(new String(kv.getFamily()) + ":");
                   System.out.print(new String(kv.getQualifier()) + " ");
                   System.out.print(kv.getTimestamp() + " ");
                   System.out.println(new String(kv.getValue()));
                }
            }
       } catch (IOException e){
           e.printStackTrace();
       }
		
	}
}

