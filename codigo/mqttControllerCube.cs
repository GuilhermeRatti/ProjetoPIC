using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;
public class mqttControllerCube : MonoBehaviour
{
  float gy_x=0, gy_y=0, gy_z=0;
  int contador = -1; 
  bool trava = true;
  float[] vetorX = new float[100];
  float[] vetorY = new float[100];
  float[] vetorZ = new float[100];

  float m_x1, m_y1, m_z1, m_x2, m_y2, m_z2; 

  
  float smooth = 1f;
  public string nameController = "Controller 1";
  public string tagOfTheMQTTReceiver="";
  public mqttReceiver _eventSender;

  void Start()
  {
      _eventSender=GameObject.FindGameObjectsWithTag(tagOfTheMQTTReceiver)[0].gameObject.GetComponent<mqttReceiver>();
    _eventSender.OnMessageArrived += OnMessageArrivedHandler;
  }

  private void OnMessageArrivedHandler(string newMsg)
  {
    //Debug.Log("Event Fired. The message, from Object " +nameController+" is = " + newMsg);

    float x,y,z;

    var tudo = newMsg.Split(';');
    var aclr = tudo[0].Split(',');
    var gyro = tudo[1].Split(',');

    
    if(float.TryParse(gyro[0], out x) && float.TryParse(gyro[1], out y) && float.TryParse(gyro[2], out z)){
      /*
      contador += 1;
      contador %= 100;

      vetorX[contador] = x;
      vetorY[contador] = z;
      vetorZ[contador] = y;

      if(contador == 99){
        trava = false;
      }
      if(trava){
        return;
      }

      float soma=0;

      m_x2 = m_x1;
      m_y2 = m_y1;
      m_z2 = m_z1;

      soma=0;
      for (int i = 0; i < 100; i++)
      {
        soma += vetorX[i];
      }
      m_x1 = soma/100;
      
      soma=0;
      for (int i = 0; i < 100; i++)
      {
        soma += vetorY[i];
      }
      m_y1 = soma/100;

      soma=0;
      for (int i = 0; i < 100; i++)
      {
        soma += vetorZ[i];
      }
      m_z1 = soma/100;
      

      
      
      
      //gy_x += (m_x1-m_x2)*100/3;
      //gy_y += (m_y1-m_y2)*100/3;
      //gy_z += (m_z1-m_z2)*100/3;
      
      */

      Debug.Log($"{x},{y},{z}");
      
      gy_x += x/1.5f;
      gy_y += z/1.85f;
      gy_z += y/1.75f;
    }

  }

  private void Update() {
    Quaternion target = Quaternion.Euler(gy_x, gy_y, gy_z);

    // Dampen towards the target rotation
    transform.rotation = Quaternion.Slerp(transform.rotation, target,  Time.deltaTime * smooth);
  }
}

        