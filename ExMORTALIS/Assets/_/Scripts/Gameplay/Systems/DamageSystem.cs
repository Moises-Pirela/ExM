using System;
using System.Collections.Generic;
using ExMORTALIS.PostprocessEvents;
using NecrotekLabs.Core;
using NecrotekLabs.Core.Components;
using NecrotekLabs.Utilities;
using UnityEditor.Callbacks;

namespace ExMORTALIS.Systems
{
    [NecroSystem(SystemTick.Postprocess)]
    public class DamageSystem : SystemBase
    {
        public override void Run(Entity[] entities, Dictionary<ComponentType, IComponent[]> components, Tuple<NecroFlags<ComponentType>, List<int>>[] archetypes, List<IPostprocessEvent> postprocessEvents)
        {
            foreach (IPostprocessEvent postprocessEvent in postprocessEvents)
            {
                if (postprocessEvent is DamagePostprocessEvent)
                {
                    DamagePostprocessEvent damagePostprocessEvent = (DamagePostprocessEvent)postprocessEvent;

                    int targetEntityId = damagePostprocessEvent.TargetEntityId;
                    int damageDealerEntityId = damagePostprocessEvent.DamageDealerEntityId;
                    float baseDamage = damagePostprocessEvent.BaseDamage;
                    
                    
                }
            }
        }
    }
}