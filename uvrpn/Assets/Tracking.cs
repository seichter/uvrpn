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
	public int useSensorNumber = 0;

	public bool applyTranslation = true;
	public bool applyRotation = true;

	public float amplification = 10;

	public bool mute = false;

	public Matrix4x4 flip = Matrix4x4.Scale(new Vector3(-1,1,-1));

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

			// update
			if (i == useSensorNumber && ! mute) {

				// get actual data
				Vector3 pos = new Vector3 ((float)s.posX, (float)s.posY, (float)s.posZ) * amplification;
				Quaternion q = new Quaternion ((float)s.quatX, (float)s.quatY, (float)s.quatZ, (float)s.quatW);

				// copy translation
				if (applyTranslation) {
					// only apply rotation with flip from VRPN
					this.transform.localPosition = flip * pos;
				}
				
				// copy rotation
				if (applyRotation) {

					// apply VRPN flip to rotation
					Matrix4x4 rotationMatrix = flip * Matrix4x4.TRS (Vector3.zero, q, Vector3.one);

					this.transform.localRotation = Quaternion.LookRotation (rotationMatrix.GetColumn(2),rotationMatrix.GetColumn(1));
				}
			}
		}
	}
}
