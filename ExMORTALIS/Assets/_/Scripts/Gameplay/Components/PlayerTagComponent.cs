using NecrotekLabs.Core.Components;
using UnityEngine;

namespace ExMORTALIS
{
    public class PlayerTagComponent : MonoBehaviour, IComponent
    {
        public ComponentType GetComponentType()
        {
            return ComponentType.PlayerTag;
        }
    }
}
