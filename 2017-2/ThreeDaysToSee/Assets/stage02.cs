using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using System;
using UnityEngine.SceneManagement;

public class stage02 : MonoBehaviour {

	public int state;
	GameObject dist;
	GameObject goal;
	GameObject circle;

	// Use this for initialization
	void Start ()
	{
		state = 0;
		this.dist = GameObject.Find("dist");
		this.goal = GameObject.Find("goal");
		this.circle = GameObject.Find("circle");
		this.dist.GetComponent<Text> ().text = "서고로 가자.";
	}

	// Update is called once per frame
	void Update () {
		if (Input.GetKey (KeyCode.UpArrow) | Input.GetKey(KeyCode.DownArrow) | Input.GetKey(KeyCode.LeftArrow) | Input.GetKey(KeyCode.RightArrow)) {
			state = 1;
		}
		if (state == 1) {
			float x = this.circle.transform.position.x - this.goal.transform.position.x;
			float y = this.circle.transform.position.y - this.goal.transform.position.y;
			float length = (float)Math.Sqrt (Math.Pow (x, 2) + Math.Pow (y, 2));
			this.dist.GetComponent<Text> ().text = length.ToString ("F2") + "m";
			if (length < 0.5f) {
				SceneManager.LoadScene ("stage03");
			}
		}
	}
}
