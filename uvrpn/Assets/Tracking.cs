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
		
	}
}
