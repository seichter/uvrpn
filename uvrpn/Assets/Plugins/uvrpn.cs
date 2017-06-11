/**
 * uvrpn - a minimal wrapper for VRPN in Unity
 * 
 * Copyright (c) 2013-2017 Hartmut Seichter
 * 
 * This file is part of uvrpn and licensed under the terms of the MIT License
 * 
 */

using System;
using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;

namespace uvrpn {

	// the sensor layout is equivalent to the internal structure
	[StructLayout(LayoutKind.Sequential)]
	public struct Sensor
	{
		public float posX, posY, posZ;
		public double quatX,quatY,quatZ,quatW;

	}

	internal class PInvoke {

#if UNITY_IPHONE || UNITY_XBOX360	
		const string dll_name = "__Internal";
#else	
		const string dll_name = "uvrpn";
#endif
		public PInvoke() {}

		//
		// Tracker
		// 
		[DllImport(dll_name)]
		internal static extern IntPtr uvrpn_tracker_create(string url);

		[DllImport(dll_name)]
		internal static extern void uvrpn_tracker_update(IntPtr ptr);

		[DllImport(dll_name)]
		internal static extern int uvrpn_tracker_get_sensor_count(IntPtr ptr);

		[DllImport(dll_name)]
		internal static extern int uvrpn_tracker_get_sensor(IntPtr ptr,ref Sensor s,int num);

		[DllImport(dll_name)]
		internal static extern int uvrpn_tracker_get_update_count(IntPtr ptr);

		[DllImport(dll_name)]
		internal static extern void uvrpn_tracker_destroy(IntPtr ptr);

	}

	public class Tracker {

		// internal pointer to an unmanaged instance
		private IntPtr ptr = new IntPtr();

		// instantiate tracker using the url such as Tracker0@localhost
		public Tracker(string url) {
			ptr = PInvoke.uvrpn_tracker_create (url);
		}

		// the update method calling the respective vrpn*->mainloop()
		public void Update() {
			PInvoke.uvrpn_tracker_update (this.ptr);
		}

		// retrieve the sensor count
		public int GetSensorCount() {
			return PInvoke.uvrpn_tracker_get_sensor_count (this.ptr);
		}

		// get the actual update count
		public int GetUpdateCount() {
			return PInvoke.uvrpn_tracker_get_update_count (this.ptr);
		}

		// get sensor data
		public Sensor GetSensor(int num) {
			Sensor s = new Sensor ();
			PInvoke.uvrpn_tracker_get_sensor (this.ptr, ref s, num);
			return s;
		}

		// d'tor
		~Tracker() {
			PInvoke.uvrpn_tracker_destroy (this.ptr);
		}

	}

}
