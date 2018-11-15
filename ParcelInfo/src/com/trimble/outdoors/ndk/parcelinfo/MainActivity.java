package com.trimble.outdoors.ndk.parcelinfo;

import java.io.File;
import java.io.IOException;

import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.os.Environment;
import android.util.Log;
import android.view.Menu;
import android.view.MenuItem;

public class MainActivity extends ActionBarActivity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		
		final ParcelUtils pu =  new ParcelUtils();
		final String stFilePath=Environment.getExternalStorageDirectory().getAbsolutePath()+
				File.separator+
				"040130467.sdb";
		final File file = new File(stFilePath);
		
		Log.i("TNP", "file:"+file.getAbsolutePath() +", file exists:"+file.exists());
		
		
		
		File dir=Environment.getExternalStorageDirectory();
		File outputFile = new File(dir, "write.txt");
		if(!outputFile.exists())
		{
			try {
				outputFile.createNewFile();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		Log.i("TNP", "file:"+outputFile.getAbsolutePath() +", file exists:"+outputFile.exists());
		
		
		ParcelUtils.Point pt = new ParcelUtils.Point();

		pt.lat=(float)33.772808;
		pt.lon=(float)-111.726898;
		
		ParcelUtils.ParcelInfo pi=new ParcelUtils.ParcelInfo();
		//NavtiveCalls.ParcelInfo pi=new NavtiveCalls.ParcelInfo();
		
		pi=pu.getParcelInfo(stFilePath, pt);
		
		System.out.println("apn: "+pi.apn);
		System.out.println("apn2: "+pi.apn2);
		//System.out.println("owner: "+pi.owner);
		//System.out.println("address: "+pi.address);
		System.out.println("city : "+pi.city);
		System.out.println("zip :"+pi.zip);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
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
