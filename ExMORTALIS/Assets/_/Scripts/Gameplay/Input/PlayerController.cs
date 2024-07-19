using System;
using System.Xml;
using ExMORTALIS.Components;
using NecrotekLabs.Core;
using NecrotekLabs.Core.Components;
using UnityEngine;

namespace ExMORTALIS.Input
{
    public class PlayerController : MonoBehaviour
    {
        public Entity controlledEntity;

        private Vector2 prevMousePos;
        
        public void Start()
        {
            InputManager.Instance.OnMove += OnMove;
            InputManager.Instance.OnLook += OnLook;
            InputManager.Instance.OnJump += OnJump;
            InputManager.Instance.OnLean += OnLean;
            InputManager.Instance.OnSprint += OnSprint;

            controlledEntity = GetComponent<Entity>();

            Cursor.visible = false;
            Cursor.lockState = CursorLockMode.Confined;
            prevMousePos = InputManager.Instance.MousePos;
        }
        
        private void OnSprint(bool isHeld)
        {
            PlayerMovementComponent playerMovementComponent =
                GameManager.Instance.GetEntityComponent<PlayerMovementComponent>(ComponentType.PlayerMovement, EntityContainer.PlayerEntityId);

            playerMovementComponent.isSprinting = isHeld;
        }

        private void OnLean(float leanDirection)
        {
            PlayerCameraComponent playerCameraComponent =  GameManager.Instance.GetEntityComponent<PlayerCameraComponent>(ComponentType.PlayerCamera, EntityContainer.PlayerEntityId);
            playerCameraComponent.leanDirection = leanDirection;
        }

        private void OnJump()
        {
            PlayerMovementComponent playerMovementComponent =
                GameManager.Instance.GetEntityComponent<PlayerMovementComponent>(ComponentType.PlayerMovement, EntityContainer.PlayerEntityId);

            playerMovementComponent.hasJumped = true;
        }

        private void OnMove(Vector2 moveInput)
        {
            moveInput.Normalize();

            PlayerMovementComponent playerMovementComponent =
                GameManager.Instance.GetEntityComponent<PlayerMovementComponent>(ComponentType.PlayerMovement, EntityContainer.PlayerEntityId);

            playerMovementComponent.targetDirection = moveInput;
        }

        private void OnLook(Vector2 lookInput)
        {
            PlayerCameraComponent playerCameraComponent =  GameManager.Instance.GetEntityComponent<PlayerCameraComponent>(ComponentType.PlayerCamera, EntityContainer.PlayerEntityId);

            playerCameraComponent.lookInput = lookInput;
        }
    }
}
