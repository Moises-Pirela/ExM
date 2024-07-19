using System;
using NecrotekLabs.Core.Components;
using UnityEngine;

namespace ExMORTALIS.Components
{
    public enum DamageType
    {
        Physical,
        Necrotic,
        Blunt,
        Slash,
        Fall,
        Max
    }

    public class ResistancesComponent : MonoBehaviour, IComponent
    {
        public Resistance[] resistances = new Resistance[(int)DamageType.Max];
        
        public ComponentType GetComponentType()
        {
            return ComponentType.Resistances;
        }
    }

    [Serializable]
    public struct Resistance
    {
        public DamageType damageType;
        [Range(0, 1)] public float ratio;
    }
}