using System;
using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEditor;
using UnityEngine;
using Object = UnityEngine.Object;

namespace NecrotekLabs.Tools.EasyRenamer
{
    public enum RenamingType
    {
        Add,
        Emplace,
        Rename,
        Remove,
        RemoveCount,
        Replace,
    }

    public class EasyRenamerEditorWindow : EditorWindow
    {
        private RenamingType RenamingType;

        private string Suffix = "";
        private string Prefix = "";

        private string ReplacePattern = "";
        private string RemovePattern;
        private string AddPattern = "";
        private string EmplaceText = "";

        private int StartIndex = 0;
        private int Count;
        private bool ShouldRename;

        private Texture2D Logo;
        private Font SpaceMono_Regular;
        private Font SpaceMono_Bold;
        private Font SpaceMono_Italic;

        [MenuItem("Tools/Necrotek Labs/Easy Renamer")]
        public static void ShowWindow()
        {
            EasyRenamerEditorWindow window =
                (EasyRenamerEditorWindow)GetWindow(typeof(EasyRenamerEditorWindow), false, "Easy Renamer");
            window.Show();
        }

        private void OnEnable()
        {
            Logo = AssetDatabase.LoadAssetAtPath<Texture2D>("Assets/Necrotek Labs/EasyRenamer/Editor/Logo.png");

            SpaceMono_Regular =
                AssetDatabase.LoadAssetAtPath<Font>("Assets/Necrotek Labs/Fonts/Space_Mono/SpaceMono-Regular.ttf");
            SpaceMono_Bold =
                AssetDatabase.LoadAssetAtPath<Font>("Assets/Necrotek Labs/Fonts/Space_Mono/SpaceMono-Bold.ttf");
            SpaceMono_Italic =
                AssetDatabase.LoadAssetAtPath<Font>("Assets/Necrotek Labs/Fonts/Space_Mono/SpaceMono-Italic.ttf");
        }

        private void OnGUI()
        {
            GUI.backgroundColor = Color.grey;

            if (Logo != null)
            {
                GUILayout.BeginHorizontal();
                GUILayout.FlexibleSpace();
                GUILayout.Label(Logo, GUILayout.Width(128), GUILayout.Height(128));
                GUILayout.FlexibleSpace();
                GUILayout.EndHorizontal();
            }

            GUIStyle titleStyle = new GUIStyle(GUI.skin.label);
            titleStyle.font = SpaceMono_Bold;
            titleStyle.fontSize = 24;
            titleStyle.fontStyle = FontStyle.Bold;
            titleStyle.alignment = TextAnchor.MiddleCenter;

            GUILayout.Label("Easy Renamer", titleStyle);

            GUIStyle subtitleStyle = new GUIStyle(GUI.skin.label);
            subtitleStyle.font = SpaceMono_Italic;
            subtitleStyle.fontSize = 18;
            subtitleStyle.alignment = TextAnchor.MiddleCenter;
            subtitleStyle.normal.textColor = Color.white;

            GUILayout.Label("A simple tool to rename your assets", subtitleStyle);

            EditorGUILayout.LabelField("", GUI.skin.horizontalScrollbarThumb);

            GUIStyle fieldStyle = new GUIStyle(GUI.skin.textField);
            fieldStyle.fixedHeight = 28;
            fieldStyle.font = SpaceMono_Regular;
            fieldStyle.fontSize = 14;
            fieldStyle.normal.textColor = Color.white;

            GUIStyle enumPopupStyle = new GUIStyle(GUI.skin.button);
            enumPopupStyle.fixedHeight = 32;
            enumPopupStyle.font = SpaceMono_Bold;
            enumPopupStyle.fontSize = 14;
            enumPopupStyle.normal.textColor = Color.white;

            GUIStyle buttonStyle = new GUIStyle(GUI.skin.button);
            buttonStyle.font = SpaceMono_Bold;
            buttonStyle.fontSize = 18;

            GUIStyle fieldLabelStyle = new GUIStyle(GUI.skin.label);
            fieldLabelStyle.fixedHeight = 32;
            fieldLabelStyle.font = SpaceMono_Bold;
            fieldLabelStyle.fontSize = 16;
            fieldLabelStyle.normal.textColor = Color.white;

            GUILayout.BeginHorizontal();
            EditorGUILayout.LabelField("Renaming Type", fieldLabelStyle);
            RenamingType = (RenamingType)EditorGUILayout.EnumPopup("", RenamingType, enumPopupStyle);
            GUILayout.EndHorizontal();

            GUILayout.Space(28);


            switch (RenamingType)
            {
                case RenamingType.Remove:
                    RemovePattern = GenerateField("Remove Pattern", fieldStyle, fieldLabelStyle, RemovePattern);
                    break;
                case RenamingType.Replace:
                    ReplacePattern = GenerateField("Replace Pattern", fieldStyle, fieldLabelStyle, ReplacePattern);
                    GUILayout.Space(32);
                    AddPattern = GenerateField("Replace with:", fieldStyle, fieldLabelStyle, AddPattern);
                    break;
                case RenamingType.Add:
                    Prefix = GenerateField("Prefix", fieldStyle, fieldLabelStyle, Prefix);
                    GUILayout.Space(32);
                    Suffix = GenerateField("Suffix", fieldStyle, fieldLabelStyle, Suffix);
                    break;
                case RenamingType.Rename:
                    AddPattern = GenerateField("New Name", fieldStyle, fieldLabelStyle, AddPattern);
                    break;
                case RenamingType.RemoveCount:
                    StartIndex = GenerateIntField("Starting at:", fieldStyle, fieldLabelStyle, StartIndex);
                    GUILayout.Space(32);
                    Count = GenerateIntField("Remove count:", fieldStyle, fieldLabelStyle, Count);
                    break;
                case RenamingType.Emplace:
                    StartIndex = GenerateIntField("Starting at:", fieldStyle, fieldLabelStyle, StartIndex);
                    GUILayout.Space(32);
                    EmplaceText = GenerateField("Emplace text:", fieldStyle, fieldLabelStyle, EmplaceText);
                    break;
            }

            if (Selection.objects.Length <= 0) return;

            GUILayout.Space(32);

            if (GUILayout.Button("Rename Selected Assets", buttonStyle))
            {
                RenameSelectedAssets();
            }
        }

        private string GenerateField(string label, GUIStyle style, GUIStyle labelStyle, string val)
        {
            GUILayout.BeginHorizontal();
            EditorGUILayout.LabelField(label, labelStyle);
            val = EditorGUILayout.TextField("", val, style);
            GUILayout.EndHorizontal();

            return val;
        }

        private int GenerateIntField(string label, GUIStyle style, GUIStyle labelStyle, int val)
        {
            GUILayout.BeginHorizontal();
            EditorGUILayout.LabelField(label, labelStyle);
            val = EditorGUILayout.IntField("", val, style);
            GUILayout.EndHorizontal();

            return val;
        }

        private void RenameSelectedAssets()
        {
            int index = 0;
            foreach (Object obj in Selection.objects)
            {
                string path = AssetDatabase.GetAssetPath(obj);
                string newName = obj.name;

                switch (RenamingType)
                {
                    case RenamingType.Remove:
                        newName = newName.Replace(RemovePattern, "");
                        break;
                    case RenamingType.Replace:
                        newName = newName.Replace(ReplacePattern, AddPattern);
                        break;
                    case RenamingType.Add:
                        newName = Prefix + newName + Suffix;
                        break;
                    case RenamingType.Rename:
                        newName = AddPattern + (Selection.objects.Length > 1 ? $"_{index}" : "");
                        break;
                    case RenamingType.RemoveCount:

                        if (StartIndex >= 0 && StartIndex < newName.Length && Count > 0 &&
                            StartIndex + Count <= newName.Length)
                        {
                            newName = newName.Remove(StartIndex, Count);
                        }

                        break;
                    case RenamingType.Emplace:
                        if (StartIndex >= 0 && StartIndex <= newName.Length)
                        {
                            newName = newName.Insert(StartIndex, EmplaceText);
                        }

                        break;
                }

                AssetDatabase.RenameAsset(path, newName);

                index++;
            }

            AssetDatabase.SaveAssets();
        }
    }
}