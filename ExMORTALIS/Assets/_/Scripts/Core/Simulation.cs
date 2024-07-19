using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using UnityEngine;

namespace NecrotekLabs.Core
{
    public enum SimState
    {
        Start,
        Run,
        Pause,
        ShutDown,
    }

    public class Simulation
    {
        public EntityContainer EntityContainer;

        public List<SystemBase>[] systems = new List<SystemBase>[(int)SystemTick.Max];

        private List<IPostprocessEvent> _postprocessEvents = new List<IPostprocessEvent>();

        public SimState SimState;

        public Simulation()
        {
            EntityContainer = new EntityContainer();

            for (int i = 0; i < systems.Length; i++)
            {
                systems[i] = new List<SystemBase>();
            }
        }

        public void StartSim()
        {
            SimState = SimState.Start;
            
            for (int i = 0; i < systems[(int)SystemTick.Startup].Count; i++)
            {
                systems[(int)SystemTick.Startup][i].Run(EntityContainer.Entities, EntityContainer.Components, EntityContainer.EntityArchetypes, _postprocessEvents);
            }
            
            SimState = SimState.Run;
        }

        public void Tick()
        {   
            if (SimState != SimState.Run) return; 
            
            for (int i = 0; i < systems[(int)SystemTick.Tick].Count; i++)
            {
                systems[(int)SystemTick.Tick][i].Run(EntityContainer.Entities, EntityContainer.Components, EntityContainer.EntityArchetypes, _postprocessEvents);
            }

            for (int i = 0; i < systems[(int)SystemTick.Postprocess].Count; i++)
            {
                systems[(int)SystemTick.Postprocess][i].Run(EntityContainer.Entities, EntityContainer.Components, EntityContainer.EntityArchetypes, _postprocessEvents);
            }
            
            _postprocessEvents.Clear();
        }

        public void FixedTick()
        {
            if (SimState != SimState.Run) return;
            
            for (int i = 0; i < systems[(int)SystemTick.FixedTick].Count; i++)
            {
                systems[(int)SystemTick.FixedTick][i].Run(EntityContainer.Entities, EntityContainer.Components, EntityContainer.EntityArchetypes, _postprocessEvents);
            }
        }
        
        public void LateTick()
        {
            if (SimState != SimState.Run) return;
            
            for (int i = 0; i < systems[(int)SystemTick.LateTick].Count; i++)
            {
                systems[(int)SystemTick.LateTick][i].Run(EntityContainer.Entities, EntityContainer.Components, EntityContainer.EntityArchetypes, _postprocessEvents);
            }
        }

        public void StopSim()
        {
            SimState = SimState.ShutDown;

            for (int i = 0; i < systems[(int)SystemTick.Shutdown].Count; i++)
            {
                systems[(int)SystemTick.Shutdown][i].Run(EntityContainer.Entities, EntityContainer.Components, EntityContainer.EntityArchetypes, _postprocessEvents);
            }
        }
    }
}