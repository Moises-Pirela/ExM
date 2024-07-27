using System;
using Codice.Client.BaseCommands;
using UnityEngine;
using UnityEngine.InputSystem;

namespace ExMORTALIS.Input
{
    public class InputManager
    {
        public static InputManager Instance;

        public Vector2 MousePos => UnityEngine.Input.mousePosition;

        public Actions InputActions;

        public Action<Vector2> OnMove;
        public Action<Vector2> OnLook;
        
        public Action OnJump;
        public Action<bool> OnSprint;
        
        public Action OnPrimaryFire;
        public Action OnSecondaryFire;

        public Action<float> OnLean;

        public InputManager()
        {
            Instance = this;
            
            InputActions = new Actions();

            InputActions.Gameplay.Move.performed += TriggerMove;
            InputActions.Gameplay.Move.canceled += TriggerMove;
            InputActions.Gameplay.Look.performed += TriggerLook;
            InputActions.Gameplay.Look.canceled += TriggerLook;
            InputActions.Gameplay.Jump.performed += TriggerJump;
            InputActions.Gameplay.Lean.performed += TriggerLean;
            InputActions.Gameplay.Lean.canceled += TriggerLean;

            InputActions.Gameplay.Sprint.started += (InputAction.CallbackContext ctx) =>
            {
                TriggerSprint(true);
            };
            
            InputActions.Gameplay.Sprint.canceled += (InputAction.CallbackContext ctx) =>
            {
                TriggerSprint(false);
            };
            
            InputActions.Enable();
        }

        private void TriggerSprint(bool isHeld)
        {
            OnSprint?.Invoke(isHeld);
        }

        private void TriggerMove(InputAction.CallbackContext ctx)
        {
            OnMove?.Invoke(ctx.ReadValue<Vector2>());
        }
        
        private void TriggerLook(InputAction.CallbackContext ctx)
        {
            OnLook?.Invoke(ctx.ReadValue<Vector2>());
        }

        private void TriggerLean(InputAction.CallbackContext ctx)
        {
            OnLean?.Invoke(ctx.ReadValue<float>());                                  
        }

        private void TriggerPrimaryFire(InputAction.CallbackContext ctx)
        {
            
        }
        
        private void TriggerSecondaryFire(InputAction.CallbackContext ctx)
        {
            
        }
        
        private void TriggerJump(InputAction.CallbackContext ctx)
        {
            OnJump?.Invoke();
        }
    }
}