using System;
using System.Collections.Generic;
using ExMORTALIS.Components;
using NecrotekLabs.Core;
using NecrotekLabs.Core.Components;
using NecrotekLabs.Utilities;
using UnityEngine;

namespace ExMORTALIS.Systems
{
    [NecroSystem(SystemTick.FixedTick)]
    public class PlayerMovementSystem : SystemBase
    {
        public override void Run(Entity[] entities, Dictionary<ComponentType, IComponent[]> components, Tuple<NecroFlags<ComponentType>, List<int>>[] archetypes, List<IPostprocessEvent> postprocessEvents)
        {
            PlayerMovementComponent playerMovementComponent = (PlayerMovementComponent)components[ComponentType.PlayerMovement][EntityContainer.PlayerEntityId];
            
            float sphereCastRadius = playerMovementComponent.characterController.radius;
            float sphereCastDistance = (playerMovementComponent.characterController.height / 2) + 0.1f;
            Vector3 sphereCastOrigin = playerMovementComponent.transform.position + playerMovementComponent.characterController.center;

            bool isGrounded = playerMovementComponent.isGrounded;

            if (playerMovementComponent.hasJumped && isGrounded && playerMovementComponent.currentStance == Stance.Standing)
            {
                playerMovementComponent.currentVelocity.y = playerMovementComponent.jumpForce;
                playerMovementComponent.rigidbody.linearVelocity = playerMovementComponent.currentVelocity;
            }
            else
            {
                playerMovementComponent.hasJumped = false;
            }
            
            if (playerMovementComponent.rigidbody.linearVelocity.y < 0)
            {
                playerMovementComponent.ChangeMovementMode(MovementMode.Falling);

            }
            else if (playerMovementComponent.rigidbody.linearVelocity.y > 0)
            {
                playerMovementComponent.ChangeMovementMode(MovementMode.Jump);
            }

            if (isGrounded && playerMovementComponent.currentMovementMode == MovementMode.Falling)
            {
                playerMovementComponent.ChangeMovementMode(MovementMode.Idle);
            }
            
            float airControl = 1;

            if (!isGrounded)
            {
                airControl = 0.8f;
            }
            else
            {
                if (playerMovementComponent.targetDirection != Vector2.zero)
                {
                    playerMovementComponent.ChangeMovementMode(playerMovementComponent.isSprinting ? MovementMode.Sprint : MovementMode.Walk);
                }
                else if (playerMovementComponent.currentMovementMode == MovementMode.Walk)
                {
                    playerMovementComponent.ChangeMovementMode(MovementMode.Idle);
                    return;
                } 
            }

            if (playerMovementComponent.currentStance == Stance.Standing)
            {
                playerMovementComponent.currentMovementSpeed = playerMovementComponent.currentMovementMode switch
                {
                    MovementMode.Walk => playerMovementComponent.walkSpeed,
                    MovementMode.Sprint => playerMovementComponent.sprintSpeed,
                    _ => playerMovementComponent.currentMovementSpeed
                };
            }
            else
            {
                playerMovementComponent.currentMovementSpeed = playerMovementComponent.crouchSpeed;
            }

            Vector3 desiredMovement = new Vector3(playerMovementComponent.targetDirection.x, 0,
                playerMovementComponent.targetDirection.y).normalized;

            desiredMovement = entities[EntityContainer.PlayerEntityId].transform.TransformDirection(desiredMovement);

            if (isGrounded && desiredMovement != Vector3.zero)
            {
                bool slopeHit = Physics.SphereCast(sphereCastOrigin, sphereCastRadius, Vector3.down, out RaycastHit hit, sphereCastDistance);
            
                if (slopeHit)
                {
                    if (Vector3.Angle(hit.normal, Vector3.up) <= playerMovementComponent.characterController.slopeLimit)
                    {
                        desiredMovement = Vector3.ProjectOnPlane(desiredMovement, hit.normal);
                    }   
                }
            }
            
            playerMovementComponent.transform.position += desiredMovement * playerMovementComponent.currentMovementSpeed * airControl * Time.deltaTime;
        }
    }
}