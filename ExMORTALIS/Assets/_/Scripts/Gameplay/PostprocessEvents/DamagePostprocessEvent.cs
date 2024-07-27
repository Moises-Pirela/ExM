using NecrotekLabs.Core;

namespace ExMORTALIS.PostprocessEvents
{
    public struct DamagePostprocessEvent : IPostprocessEvent
    {
        public int TargetEntityId;
        public int DamageDealerEntityId;
        public float BaseDamage;
    }
}