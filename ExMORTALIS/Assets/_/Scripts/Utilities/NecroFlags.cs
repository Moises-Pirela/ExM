using System;

namespace NecrotekLabs.Utilities
{
    public struct NecroFlags<T> where T : Enum
    {
        private byte _value;

        public void SetFlag(T flag)
        {
            
        }

        public bool HasFlag(T flag)
        {
            return false;
        }

        public void RemoveFlag(T flag)
        {
            
        }

        public bool HasMatchingSignature(NecroFlags<T> signature)
        {
            return _value == signature._value;
        }
    }
}