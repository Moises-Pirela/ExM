using NecrotekLabs.Core.Components;
using UnityEngine;

namespace ExMORTALIS.Components
{
    public class PlayerCameraComponent : MonoBehaviour, IComponent
    {
        [HideInInspector] public Vector2 lookInput;
        [HideInInspector] public float leanDirection;
        public Transform cameraRoot;
        public Camera camera;

        [Range(0,100)] public float verticalSens;
        [Range(0, 100)] public float horizontalSens;
        
        public ComponentType GetComponentType()
        {
            return ComponentType.PlayerCamera;
        }
    }
}