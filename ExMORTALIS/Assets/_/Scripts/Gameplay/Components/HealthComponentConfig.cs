using NecrotekLabs.Core.Components;
using UnityEngine;

namespace ExMORTALIS.Components
{
    public class HealthComponent : MonoBehaviour, IComponent
    {
        public float MaxHealth;
        public ComponentType GetComponentType()
        {
            return ComponentType.Health;
        }
    }
}
