using NecrotekLabs.Core.Archetypes;
using NecrotekLabs.Core.Components;
using NecrotekLabs.Utilities;

namespace ExMORTALIS.Archetypes
{
    public struct DamageableArchetype : IEntityArchetype
    {
        public Archetype GetArchetype()
        {
            return Archetype.Damageable;
        }

        public NecroFlags<ComponentType> GetSignature()
        {
            return new NecroFlags<ComponentType>(ComponentType.Health, ComponentType.Resistances);
        }
    }
}