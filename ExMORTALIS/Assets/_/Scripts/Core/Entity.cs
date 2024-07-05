using NecrotekLabs.Core.Components;
using NecrotekLabs.Utilities;
using UnityEngine;
using UnityEngine.Serialization;

namespace NecrotekLabs.Core
{
    public enum EntityState : byte
    {
        Active,
        Dead,
        Inactive
    }

    public class Entity : MonoBehaviour
    {
        public int entityId;
        public int entityConfigId;

        public NecroFlags<EntityState> EntityStateFlags;
        public NecroFlags<ComponentType> ComponentSignature;
    }
}
