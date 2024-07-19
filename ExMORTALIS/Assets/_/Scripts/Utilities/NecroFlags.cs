using System;

namespace NecrotekLabs.Utilities
{
    public struct NecroFlags<T> where T : Enum
    {
        private int _value;

        public NecroFlags(params T[] flags)
        {
            _value = 0;
            
            foreach (T flag in flags)
            {
                SetFlag(flag);
            }
        }

        public void SetFlag(T flag)
        {
            int castedFlag = (int)(object)flag;
            _value |= (1 << castedFlag);
        }

        public bool HasFlag(T flag)
        {
            int castedFlag = (int)(object)flag;
            return (_value & (1 << castedFlag)) != 0;;
        }

        public void RemoveFlag(T flag)
        {
            int castedFlag = (int)(object)flag;
            _value &= ~(1 << castedFlag);
        }

        public bool HasMatchingSignature(NecroFlags<T> signature)
        {
            return _value == signature._value;
        }
    }
}