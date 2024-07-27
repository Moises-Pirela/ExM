using NecrotekLabs.Core.Components;
using NecrotekLabs.Utilities;

namespace NecrotekLabs.Core.Archetypes
{
    public enum Archetype
    {
        Damageable,
        Max,
    }
    
    public interface IEntityArchetype
    {   
        public Archetype GetArchetype();
        public NecroFlags<ComponentType> GetSignature();
    }
}