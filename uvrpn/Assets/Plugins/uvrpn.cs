/**
 * uvrpn - a minimal wrapper for VRPN in Unity
 * 
 * Copyright (c) 2013-2019 Hartmut Seichter
 * 
 * This file is part of uvrpn and licensed under the terms of the MIT License
 * 
 */


//
// get packages
//
using System;
using System.Collections;
using System.Collections.Generic;
using System.Runtime.InteropServices;

namespace uvrpn {

	[StructLayout(LayoutKind.Sequential)]
	public struct SensorQuaternion {
		public double quatX,quatY,quatZ,quatW;

		public override string ToString() => $"{quatX} {quatY} {quatZ} {quatW}";
	}

	[StructLayout(LayoutKind.Sequential)]
	public struct SensorVector3 {
		public double posX, posY, posZ;

		public override string ToString() => $"{posX} {posY} {posZ}";
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
		internal static extern int uvrpn_tracker_get_sensor_rotation(IntPtr ptr,int num,ref SensorQuaternion sq);

		[DllImport(dll_name)]
		internal static extern int uvrpn_tracker_get_sensor_position(IntPtr ptr,int num,ref SensorVector3 sv);

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

		public SensorQuaternion GetSensorRotation(int num) {
			SensorQuaternion sq = new SensorQuaternion();
			PInvoke.uvrpn_tracker_get_sensor_rotation(this.ptr, num,ref sq);
			return sq;
		}

		public SensorVector3 GetSensorPosition(int num) {
			SensorVector3 sv = new SensorVector3();
			PInvoke.uvrpn_tracker_get_sensor_position(this.ptr, num,ref sv);
			return sv;
		}

		// d'tor
		~Tracker() {
			PInvoke.uvrpn_tracker_destroy (this.ptr);
		}

	}

}
