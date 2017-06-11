/**
 * uvrpn - a minimal wrapper for VRPN in Unity
 * 
 * Copyright (c) 2013-2017 Hartmut Seichter
 * 
 * This file is part of uvrpn and licensed under the terms of the MIT License
 * 
 */

using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using uvrpn;

public class Tracking : MonoBehaviour {

	private uvrpn.Tracker tracker = null;

	public string trackerURL;

	void Start () {
		// on start launch the tracker
		tracker = new uvrpn.Tracker (trackerURL);
		
	}

	void Update () {

		// the tracker needs some update
		tracker.Update ();

		// only if we have the sensors ready, update data
		for (int i = 0; i < tracker.GetSensorCount ();i++) {

			// retrieve
			uvrpn.Sensor s = tracker.GetSensor (i);

			Debug.Log ("Sensor" + i + " Pos: " + s.posX + " " + s.posY + " " + s.posZ);
			Debug.Log ("Sensor" + i + " Rot: " + s.quatW + " " + s.quatX + " " + s.quatY + " " + s.quatZ);

		}
	}
}
