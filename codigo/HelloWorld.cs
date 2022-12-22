/*
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class HelloWorld : MonoBehaviour {
    private void Start() {
        Debug.Log("alo");
    }  a

    float smooth = 1000f;
    float tiltAngle = 90f;
    private void Update() {
        transform.Rotate(1f*Input.GetAxis("Vertical"),0f,-180f*Input.GetAxis("Horizontal"));

        // Smoothly tilts a transform towards a target rotation.
        
        float tiltAroundZ = -Input.GetAxis("Horizontal") * tiltAngle;
        float tiltAroundX = Input.GetAxis("Vertical") * tiltAngle;

        // Rotate the cube by converting the angles into a quaternion.
        Quaternion target = Quaternion.Euler(tiltAroundX, 0, tiltAroundZ);

        // Dampen towards the target rotation
        transform.rotation = Quaternion.Slerp(transform.rotation, target,  Time.deltaTime * smooth);
        
    }
}
*/

using UnityEngine;

// Transform.Rotate example
//
// This script creates two different cubes: one red which is rotated using Space.Self; one green which is rotated using Space.World.
// Add it onto any GameObject in a scene and hit play to see it run. The rotation is controlled using xAngle, yAngle and zAngle, modifiable on the inspector.

public class HelloWorld : MonoBehaviour
{
    public float xAngle, yAngle, zAngle;


    void Update()
    {
        if (Input.GetKeyDown("space"))
        {
            transform.Rotate(xAngle, yAngle, zAngle);
        }
        
    }
}
