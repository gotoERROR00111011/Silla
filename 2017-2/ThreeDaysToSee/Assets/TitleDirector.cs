using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class TitleDirector : MonoBehaviour {
    int _state;
    GameObject title;
    string str1 = "\n\n사흘만 볼 수 있다면\n\n-press enter-";
    string str2 = "\n\n첫째날은 사랑하는 이의 얼굴을 볼것이고,\n둘째날은 밤이 아침으로 변하는 기적을 볼것이고,\n셋째날은 사람들이 오가는 평범한 거리를 보고싶다.\n\n단언컨대 본다는 것은 가장 큰 축복이다. -헬렌 켈러-\n\n                -press enter-";
    
	// Use this for initialization
	void Start ()
    {
        _state = 0;
        this.title = GameObject.Find("Title");
        this.title.GetComponent<Text>().fontSize = 100;
        this.title.GetComponent<Text>().text = str1;		
	}
	
	// Update is called once per frame
	void Update () {
        if (Input.GetKeyDown(KeyCode.Return) & _state==0)
        {
            _state = 1;
            this.title.GetComponent<Text>().fontSize = 40;
            this.title.GetComponent<Text>().text = str2;
        }
        else if (Input.GetKeyDown(KeyCode.Return) & _state == 1)
        {
            SceneManager.LoadScene("stage01");
        }

    }
}
