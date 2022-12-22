using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class BOLA : MonoBehaviour
{
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        
    }

    void OnCollisionEnter(Collision collision)
    {
        foreach (ContactPoint contact in collision.contacts)
        {
            Debug.Log($"{contact.otherCollider.name}");
            if(contact.otherCollider.name == "Plane"){
                transform.position = new Vector3(0,20,0);
            }
        }
        /*
        ContactPoint contact = collision.contacts[0];
        Quaternion rotation = Quaternion.FromToRotation(Vector3.up, contact.normal);
        Vector3 position = contact.point;
        Instantiate(explosionPrefab, position, rotation);
        
        transform.position(0,20,0);
        */
    }
}
