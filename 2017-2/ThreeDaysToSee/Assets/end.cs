using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class end : MonoBehaviour {
	int _state;
	GameObject title;
	string str1 = "\n\n장애인의 불편함을 아시겠나요?\n\n-press enter-";
	string str2 = "\n\n배려와 양보를 잊지 않는,\n\n-press enter-";
	string str3 = "\n\n올바른 대한민국을 만듭시다.\n\n-press enter-";
	string str4 = "\n\nRESTART\n\n-press enter-";

	// Use this for initialization
	void Start ()
	{
		_state = 0;
		this.title = GameObject.Find("Title");
		this.title.GetComponent<Text>().fontSize = 60;
		this.title.GetComponent<Text>().text = str1;		
	}

	// Update is called once per frame
	void Update () {
		if (Input.GetKeyDown (KeyCode.Return) & _state == 0) {
			_state = 1;
			this.title.GetComponent<Text> ().text = str2;
		} else if (Input.GetKeyDown (KeyCode.Return) & _state == 1) {
			_state = 2;
			this.title.GetComponent<Text> ().text = str3;
		} else if (Input.GetKeyDown (KeyCode.Return) & _state == 2) {
			_state = 3;
			this.title.GetComponent<Text> ().text = str4;
		} else if (Input.GetKeyDown (KeyCode.Return) & _state == 3) {
			SceneManager.LoadScene("start");
		}
	}
}
