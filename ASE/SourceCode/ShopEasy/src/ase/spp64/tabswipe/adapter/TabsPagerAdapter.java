package ase.spp64.tabswipe.adapter;

import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentPagerAdapter;
import ase.spp64.shopeasy.GroceryFragment;
import ase.spp64.shopeasy.PantryFragment;

public class TabsPagerAdapter extends FragmentPagerAdapter {

	public TabsPagerAdapter(FragmentManager fm) {
		super(fm);
	}

	@Override
	public Fragment getItem(int index) {

		switch (index) {
		case 0:
			// Top Rated fragment activity
			return new GroceryFragment();
		case 1:
			// Games fragment activity
			// return new GamesFragment();
			return new PantryFragment();
		case 2:	
		
		}
		

		return null;
	}

	@Override
	public int getCount() {
		// get item count - equal to number of tabs
		return 3;
	}

}
