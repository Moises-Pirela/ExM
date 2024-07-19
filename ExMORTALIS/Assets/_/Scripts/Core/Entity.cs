using NecrotekLabs.Core.Components;
using NecrotekLabs.Utilities;
using UnityEngine;
using UnityEngine.Serialization;

namespace NecrotekLabs.Core
{
    public enum EntityState : int
    {
        Active,
        Dead,
        Inactive
    }

    public class Entity : MonoBehaviour
    {
        public int entityId;
        public int entityConfigId;

        public bool isStartingEntity;

        public NecroFlags<EntityState> EntityStateFlags;
        public NecroFlags<ComponentType> ComponentSignature;

        public IComponent[] GetComponentConfigs()
        {
            var components = GetComponents<IComponent>();

            return components;
        }
    }
}
