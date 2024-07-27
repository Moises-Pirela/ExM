using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using ExMORTALIS.Input;
using NecrotekLabs.Core;
using NecrotekLabs.Core.Archetypes;
using NecrotekLabs.Core.Components;
using NecrotekLabs.Utilities;
using UnityEngine;

namespace ExMORTALIS
{
    public class GameManager : MonoBehaviour
    {
        public static GameManager Instance;
        
        private InputManager InputManager;
        private Simulation Simulation;

        private void Awake()
        {
            Instance = this;
            Simulation = new Simulation();
            LoadSystems();
            
            InputManager = new InputManager();

            Entity[] entities = FindObjectsByType<Entity>(FindObjectsSortMode.None);
            foreach (Entity entity in entities)
            {
                if (entity.isStartingEntity)
                {
                    Simulation.EntityContainer.CreateEntity(entity, out int entityId);
                }
            }
        }

        private void Start()
        {
            Simulation.StartSim();
        }

        private void Update()
        {
            Simulation.Tick();
        }

        private void FixedUpdate()
        {
            Simulation.FixedTick();
        }

        private void LateUpdate()
        {
            Simulation.LateTick();
        }

        public Component GetEntityComponent<Component>(ComponentType componentType, int entityId) where Component : IComponent
        {
            return (Component)Simulation.EntityContainer.Components[componentType][entityId];
        }
        
        private void LoadSystems()
        {
            var archetypes = Assembly
                .GetExecutingAssembly()
                .GetTypes()
                .Where(t => typeof(IEntityArchetype).IsAssignableFrom(t) && !t.IsInterface && !t.IsAbstract);

            foreach (var type in archetypes)
            {
                var entityArchetype = (IEntityArchetype)Activator.CreateInstance(type);
                Simulation.EntityContainer.EntityArchetypes[(int)entityArchetype.GetArchetype()] = new Tuple<NecroFlags<ComponentType>, List<int>>(entityArchetype.GetSignature(), new List<int>());
            }
            
            var systemTypes = Assembly
                .GetExecutingAssembly()
                .GetTypes()
                .Where(t => t.IsSubclassOf(typeof(SystemBase)) && !t.IsAbstract)
                .Select(t => new { Type = t, Attribute = t.GetCustomAttribute<NecroSystemAttribute>() })
                .Where(t => t.Attribute != null)
                .OrderBy(t => t.Attribute.Priority);

            foreach (var type in systemTypes)
            {
                var system = (SystemBase)Activator.CreateInstance(type.Type);

                Debug.Log($"Loading {type.Attribute.SystemTick} system: {type.Type.Name}");

                if (Simulation.systems[(int)type.Attribute.SystemTick] == null)
                    Simulation.systems[(int)type.Attribute.SystemTick] = new List<SystemBase>();
                
                Simulation.systems[(int)type.Attribute.SystemTick].Add(system);
            }
        }
    }
}
