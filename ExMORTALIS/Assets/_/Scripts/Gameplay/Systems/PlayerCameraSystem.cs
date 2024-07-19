using System;
using System.Collections.Generic;
using ExMORTALIS.Components;
using NecrotekLabs.Core;
using NecrotekLabs.Core.Components;
using NecrotekLabs.Utilities;
using UnityEngine;

namespace ExMORTALIS.Systems
{
    [NecroSystem(SystemTick.LateTick)]
    public class PlayerCameraSystem : SystemBase
    {
        private const float RotationSmoothTime = 0f;
        private const float LeanSmoothTime = 0.1f;
        private Vector3 currentRotation;
        private Vector3 rotationVelocity;
        private Vector3 leanVelocity;

        public override void Run(Entity[] entities, Dictionary<ComponentType, IComponent[]> components,
            Tuple<NecroFlags<ComponentType>, List<int>>[] archetypes, List<IPostprocessEvent> postprocessEvents)
        {
            PlayerCameraComponent playerCameraComponent =
                (PlayerCameraComponent)components[ComponentType.PlayerCamera][EntityContainer.PlayerEntityId];

            float deltaTime = Time.deltaTime;

            //playerCameraComponent.lookInput.Normalize();

            float targetRotationY = currentRotation.y +
                                    playerCameraComponent.lookInput.x * playerCameraComponent.horizontalSens;
            float targetRotationX = currentRotation.x +
                                    -playerCameraComponent.lookInput.y * playerCameraComponent.verticalSens;
            float targetLeanRotation = -playerCameraComponent.leanDirection * 15;
            float targetLeanPosition = playerCameraComponent.leanDirection * 0.5f;

            currentRotation.y = Mathf.SmoothDamp(currentRotation.y, targetRotationY, ref rotationVelocity.y,
                RotationSmoothTime, Mathf.Infinity, deltaTime);
            currentRotation.x = Mathf.SmoothDamp(currentRotation.x, targetRotationX, ref rotationVelocity.x,
                RotationSmoothTime, Mathf.Infinity, deltaTime);
            currentRotation.z = Mathf.SmoothDamp(currentRotation.z, targetLeanRotation, ref rotationVelocity.z,
                LeanSmoothTime, Mathf.Infinity, deltaTime);
            currentRotation.x = Mathf.Clamp(currentRotation.x, -85f, 90f);
            currentRotation.z = Mathf.Clamp(currentRotation.z, -15f, 15f);

            playerCameraComponent.cameraRoot.localRotation = Quaternion.Euler(new Vector3(currentRotation.x, 0, currentRotation.z));
            entities[EntityContainer.PlayerEntityId].transform.Rotate(new Vector3(0,
                playerCameraComponent.lookInput.x * playerCameraComponent.horizontalSens, 0));
            
            var localPosition = playerCameraComponent.cameraRoot.localPosition;
            localPosition.x = Mathf.SmoothDamp(localPosition.x, targetLeanPosition, ref leanVelocity.x, LeanSmoothTime, Mathf.Infinity, deltaTime);
            localPosition.x = Mathf.Clamp(localPosition.x, -5, 5);
            playerCameraComponent.cameraRoot.localPosition = localPosition;
        }
    }
}