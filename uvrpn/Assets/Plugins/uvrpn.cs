using System;
using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;

//using UnityEngine;

namespace uvrpn {

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

		IntPtr ptr = new IntPtr();

		public Tracker(string url) {
			ptr = PInvoke.uvrpn_tracker_create (url);
		}

		public void Update() {
			PInvoke.uvrpn_tracker_update (this.ptr);
		}

		public int GetSensorCount() {
			return PInvoke.uvrpn_tracker_get_sensor_count (this.ptr);
		}

		public int GetUpdateCount() {
			return PInvoke.uvrpn_tracker_get_update_count (this.ptr);
		}

		public Sensor GetSensor(int num) {
			Sensor s = new Sensor ();
			PInvoke.uvrpn_tracker_get_sensor (this.ptr, ref s, num);
			return s;
		}

		~Tracker() {
			PInvoke.uvrpn_tracker_destroy (this.ptr);
		}

	}

}
