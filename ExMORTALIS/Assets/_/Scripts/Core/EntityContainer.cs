using System;
using System.Collections.Generic;
using System.Linq;
using System.Reflection;
using NecrotekLabs.Core.Archetypes;
using NecrotekLabs.Core.Components;
using NecrotekLabs.Utilities;
using UnityEditor.Build.Content;
using UnityEngine;

namespace NecrotekLabs.Core
{
    public class EntityContainer
    {
        public const int MAX_ENTITIES = 1000;

        public static int PlayerEntityId = -1;
        
        public Entity[] Entities = new Entity[MAX_ENTITIES];
        
        public Dictionary<ComponentType, IComponent[]> Components = new Dictionary<ComponentType, IComponent[]>();

        public Tuple<NecroFlags<ComponentType>, List<int>>[] EntityArchetypes = new Tuple<NecroFlags<ComponentType>, List<int>>[(int)Archetype.Max];

        private int _availableEntityId;
        private int _recycledEntityId;

        public EntityContainer()
        {
            for (int i = 0; i < (int)ComponentType.Max; i++)
            {
                Components.Add((ComponentType)i, new IComponent[MAX_ENTITIES]);
            }
        }

        public bool CreateEntity(Entity entity, out int entityId)
        {
            entityId = -1;
            
            if (_availableEntityId >= MAX_ENTITIES)
            {
                Debug.LogError($"ENTITY OVERFLOW");
                return false;
            }

            if (_recycledEntityId == -1)
            {
                entityId = _availableEntityId;
                _availableEntityId++;
            }
            else
            {
                entityId = _recycledEntityId;
            }

            if (entityId >= MAX_ENTITIES)
            {
                Debug.LogError($"ENTITY OVERFLOW");
                return false;
            }
            
            entity.entityId = entityId;

            var components = entity.GetComponentConfigs(); //TODO: CHANGE TO A ENTITY CONFIG FILE

            foreach (var component in components)
            {
                if (component.GetComponentType() == ComponentType.PlayerTag)
                    PlayerEntityId = entityId;
                        
                entity.ComponentSignature.SetFlag(component.GetComponentType());

                Components[component.GetComponentType()][entityId] = component;
            }

            for (var i = 0; i < EntityArchetypes.Length; i++)
            {
                var entityArchetype = EntityArchetypes[i];
                
                if (entity.ComponentSignature.HasMatchingSignature(entityArchetype.Item1))
                {
                    EntityArchetypes[i].Item2.Add(entityId);
                }
            }

            Entities[entityId] = entity;

            return true;
        }

        public bool KillEntity(int entityId)
        {
            Entity entity = Entities[entityId]; 
            
            Entities[entityId] = null;

            for (int i = 0; i < (int)ComponentType.Max; i++)
            {
                if (entity.ComponentSignature.HasFlag((ComponentType)i))
                {
                    Components[(ComponentType)i][entityId] = null;
                }
            }

            for (int i = 0; i < EntityArchetypes.Length; i++)
            {
                var entityArchetype = EntityArchetypes[i];
                
                if (entity.ComponentSignature.HasMatchingSignature(entityArchetype.Item1))
                {
                    EntityArchetypes[i].Item2.Remove(entityId);
                }
            }
            
            GameObject.Destroy(entity);

            _recycledEntityId = entityId;

            return true;
        }
    }
}