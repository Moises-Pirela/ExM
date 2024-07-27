using System;
using System.Collections.Generic;
using NecrotekLabs.Core.Components;
using NecrotekLabs.Utilities;
using UnityEngine;

namespace NecrotekLabs.Core
{
    public enum SystemTick
    {
        Startup,
        Tick,
        FixedTick,
        LateTick,
        Postprocess,
        Shutdown,
        Max
    }

    public abstract class SystemBase
    {
        public abstract void Run(Entity[] entities, Dictionary<ComponentType, IComponent[]> components, Tuple<NecroFlags<ComponentType>, List<int>>[] archetypes,  List<IPostprocessEvent> postprocessEvents);
    }
}
