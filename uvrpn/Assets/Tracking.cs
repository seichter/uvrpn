using System.Collections;
using System.Collections.Generic;
using UnityEngine;

using uvrpn;

public class Tracking : MonoBehaviour {

	private uvrpn.Tracker tracker = null;

	public string trackerURL;

	// Use this for initialization
	void Start () {

		tracker = new uvrpn.Tracker (trackerURL);
		
	}
	
	// Update is called once per frame
	void Update () {

		tracker.Update ();

		if (tracker.GetSensorCount () > 0) {

			uvrpn.Sensor s = tracker.GetSensor (0);

			Debug.Log ("Pos: " + s.posX + " " + s.posY + " " + s.posZ);
			Debug.Log ("Rot: " + s.quatW + " " + s.quatX + " " + s.quatY + " " + s.quatZ);

		}
	}
}
