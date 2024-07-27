using System;

namespace NecrotekLabs.Core
{
    public class NecroSystemAttribute : Attribute
    {
        public SystemTick SystemTick;
        public int Priority;
        
        public NecroSystemAttribute(SystemTick systemTick, int priority = -1)
        {
            SystemTick = systemTick;
            Priority = priority;
        }
    }
}