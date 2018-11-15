package com.trimble.outdoors.ndk.parcelinfo;

import java.util.ArrayList;


public class ParcelUtils {
	static
	{

		System.loadLibrary("parcelinfo");
	}
	public static class Polygon {
        String stateID;
        int idx;
        ArrayList<Ring> rings;
        public Polygon()
	    {
        	rings = new ArrayList<Ring>();
	    }
}

public static class Ring {
        int idx;
        ArrayList<Point> points;
        public Ring()
	    {
        	points = new ArrayList<Point>();
	    }
}
	public static class Point {
	      public float lat;
	      public float lon;
	      public Point()
	      {
	    	  lat = 2.3f;
	    	  lon = 3.4f;
	      }
	      public Point(float a, float b)
	      {
	    	  lat = a;
	    	  lon = b;
	      }
	   }
	
	public static class ParcelInfo {
	      public String apn;
	      public String apn2;
	      public String owner;
	      public String address;
	      public String city;
	      public String zip;
	      public Point point;
	      public ParcelInfo()
	      {
	    	  point = new Point();
	      }
	   }

	
	
	public native ParcelInfo getParcelInfo(final String stPath, Point point); 
	
	//public native void getParcelInfo(final String stPath,final int iLen);
}