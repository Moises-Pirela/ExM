using System;
using NecrotekLabs.Core.Components;
using UnityEngine;
using UnityEngine.Serialization;

namespace ExMORTALIS.Components
{
    public enum MovementMode
    {
        Idle,
        Walk,
        Sprint,
        Vaulting,
        Jump,
        Falling
    }

    public enum Stance
    {
        Standing,
        Crouching
    }

    public class PlayerMovementComponent : MonoBehaviour, IComponent
    {
        public CharacterController characterController;
        public MovementMode currentMovementMode { get; private set; }
        public MovementMode prevMovementMode { get; private set; }

        public Stance currentStance { get; private set; }
        public Stance prevStance { get; private set; }

        [HideInInspector] public Vector2 targetDirection;
        [HideInInspector] public Vector3 currentVelocity;

        [HideInInspector] public float currentMovementSpeed;
        public float walkSpeed;
        public float sprintSpeed;
        public float crouchSpeed;
        public float jumpForce;
        [HideInInspector] public bool isGrounded;
        [HideInInspector] public bool hasJumped;
        [HideInInspector] public bool isSprinting;

        public LayerMask groundLayer;

        public Action OnLand;
        public Action OnJump;
        public Action OnCrouch;
        public Action OnStand;

        public Action<MovementMode, MovementMode> OnMovementModeChanged;
        public Action<Stance, Stance> OnStanceChanged;

        public Rigidbody rigidbody;

        public void ChangeMovementMode(MovementMode newMovementMode)
        {
            prevMovementMode = currentMovementMode;
            currentMovementMode = newMovementMode;
            
            if (prevMovementMode == MovementMode.Falling)
                OnLand?.Invoke();
            
            OnMovementModeChanged?.Invoke(prevMovementMode, newMovementMode);
        }

        public void ChangeStance(Stance newStance)
        {
            prevStance = currentStance;
            currentStance = newStance;
            
            OnStanceChanged?.Invoke(prevStance, currentStance);
        }

        public ComponentType GetComponentType()
        {
            return ComponentType.PlayerMovement;
        }

        private void OnDrawGizmos()
        {
            float sphereCastRadius = characterController.radius / 2;
            float sphereCastDistance = (characterController.height / 2) + 0.1f;
            Vector3 sphereCastOrigin = transform.position + characterController.center;

            switch (currentMovementMode)
            {
                case MovementMode.Idle:
                    Gizmos.color = Color.blue;
                    break;
                case MovementMode.Walk:
                    Gizmos.color = Color.green;
                    break;
                case MovementMode.Sprint:
                    Gizmos.color = Color.red;
                    break;
                case MovementMode.Vaulting:
                    Gizmos.color = Color.yellow;
                    break;
                case MovementMode.Jump:
                    Gizmos.color = Color.white;
                    break;
                default:
                    Gizmos.color = Color.gray;
                    break;
            }

            Gizmos.DrawWireSphere(sphereCastOrigin, sphereCastRadius);
            Gizmos.DrawLine(sphereCastOrigin, sphereCastOrigin + Vector3.down * sphereCastDistance);
            Gizmos.DrawWireSphere(sphereCastOrigin + Vector3.down * sphereCastDistance, sphereCastRadius);
            
            Vector3 forwardDirection = transform.forward;
            Gizmos.color = Color.yellow;
            Gizmos.DrawRay(sphereCastOrigin, forwardDirection * 2); 
            Gizmos.DrawWireSphere(sphereCastOrigin + forwardDirection * 2, 0.1f);
        }
    }
}