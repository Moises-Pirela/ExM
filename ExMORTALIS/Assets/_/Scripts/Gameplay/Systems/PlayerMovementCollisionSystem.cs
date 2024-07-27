using System;
using System.Collections.Generic;
using ExMORTALIS.Components;
using NecrotekLabs.Core;
using NecrotekLabs.Core.Components;
using NecrotekLabs.Utilities;
using UnityEngine;

namespace ExMORTALIS.Systems
{
    [NecroSystem(SystemTick.Tick)]
    public class PlayerMovementCollisionSystem : SystemBase
    {
        public override void Run(Entity[] entities, Dictionary<ComponentType, IComponent[]> components,
            Tuple<NecroFlags<ComponentType>, List<int>>[] archetypes, List<IPostprocessEvent> postprocessEvents)
        {
            PlayerMovementComponent playerMovementComponent =
                (PlayerMovementComponent)components[ComponentType.PlayerMovement][EntityContainer.PlayerEntityId];

            float sphereCastRadius = playerMovementComponent.characterController.radius / 2;
            float sphereCastDistance = (playerMovementComponent.characterController.height / 2) + 0.1f;
            Vector3 sphereCastOrigin = playerMovementComponent.transform.position +
                                       playerMovementComponent.characterController.center;

            bool isGrounded = Physics.SphereCast(sphereCastOrigin, sphereCastRadius, -playerMovementComponent.transform.up, out RaycastHit hit,
                sphereCastDistance);

            playerMovementComponent.isGrounded = isGrounded;

            Debug.DrawLine(sphereCastOrigin, -playerMovementComponent.transform.up * sphereCastDistance, isGrounded ? Color.red : Color.green);
        }
    }
}