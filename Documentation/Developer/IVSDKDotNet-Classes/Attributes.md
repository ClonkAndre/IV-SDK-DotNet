# Attributes

[Attributes](https://learn.microsoft.com/en-us/dotnet/csharp/advanced-topics/reflection-and-attributes/) in .NET are metadata markers that can be placed above a class, property, or method declaration to indicate special behaviour.  

IV-SDK .NET provides a few IV-SDK.NET-specific attributes which can be found within the `IVSDKDotNet.Attributes` namespace.  
Below you'll find details and examples for each available attribute.

---

### 🧩 ShowStaticFieldsInInspector

By default, only instance-level public variables in your main script class (i.e., the one inheriting from Script) appear in the Public Fields window of the ManagerUI.  
Applying the ShowStaticFieldsInInspector attribute to a class allows its static fields to be displayed and modified through the Public Fields window.

Example
```C#
using IVSDKDotNet.Attributes;

[ShowStaticFieldsInInspector]
public static class GameSettings
{
    public static bool EnableGodMode = false;
    public static int MaxWantedLevel = 5;
}
```

In this example, the static fields `EnableGodMode` and `MaxWantedLevel` will appear in the Public Fields window when the script is running, allowing real-time tweaks in-game.

---

### 🧩 SeparatorAttribute

This attribute allows you to visually organize the Public Fields window by adding horizontal separators between fields making your script's interface easier to read and navigate.  
You can optionally specify a label to be shown alongside the separator, which is helpful for grouping related fields or providing contextual hints.

Example
```C#
using IVSDKDotNet;
using IVSDKDotNet.Attributes;

public class ExampleScript : Script
{
    public bool EnableCheats = false;

    [Separator("Weapon Settings")]
    public bool InfiniteAmmo = true;
    public int MaxAmmo = 999;

    [Separator]
    public bool DebugMode = false;
}
```

In the Public Fields window, this will render two horizontal lines, one labeled `Weapon Settings`, to group and visually separate related fields.

---

### 🧩 SpaceAttribute

This attribute lets you add vertical spacing between fields in the Public Fields window. This is useful for improving layout clarity and separating unrelated variables without adding a full visual separator.  
You can provide a float value to control the amount of space in pixels.

Example
```C#
using IVSDKDotNet;
using IVSDKDotNet.Attributes;

public class ExampleScript : Script
{
    public bool EnableHUD = true;

    [Space(20f)]
    public bool ShowMinimap = true;

    [Space(40f)]
    public bool ShowDebugInfo = false;
}
```

In the example above, 20 and 40 pixels of vertical space will be inserted before the `ShowMinimap` and `ShowDebugInfo` fields, respectively.

---

### 🧩 SpeedAttribute

This attribute controls the sensitivity of sliders in the Public Fields window. It defines how quickly a value changes when dragging the slider, making it easier to fine-tune values or make larger adjustments more efficiently.

You can apply it to any numeric field (e.g., `float`, `int`) that is displayed as a slider.

Example
```C#
using IVSDKDotNet;
using IVSDKDotNet.Attributes;

public class ExampleScript : Script
{
    [Speed(0.01f)]
    public float CameraZoom = 1.0f;

    [Speed(5f)]
    public int MaxEnemies = 20;
}
```

In this example:

- `CameraZoom` changes in small increments (ideal for precision).
- `MaxEnemies` changes in larger steps, suitable for whole-number tuning.

---

### 🧩 RangeAttribute

This attribute sets the **minimum and maximum limits** for numeric fields displayed as sliders in the Public Fields window. This helps constrain user input to a valid range and gives better control over adjustable values.

It accepts two float parameters: the **minimum** and **maximum** values.

Example
```C#
using IVSDKDotNet;
using IVSDKDotNet.Attributes;

public class ExampleScript : Script
{
    [Range(0f, 1f)]
    public float Volume = 0.5f;

    [Range(10f, 100f)]
    public float PlayerSpeed = 25f;
}
```

In this example:

- `Volume` is limited to values between 0 and 1.
- `PlayerSpeed` is adjustable between 10 and 100.

The values will be constrained within the specified range using the slider.

---

### 🧩 HelpMarkerAttribute

This attribute adds a **small question mark icon ("?")** next to a field in the Public Fields window. When hovered over, it displays a custom tooltip with helpful information or context about that field.  
This is useful for explaining the purpose of settings directly in the UI without cluttering your code or interface.

Example
```C#
using IVSDKDotNet;
using IVSDKDotNet.Attributes;

public class ExampleScript : Script
{
    [HelpMarker("Enables god mode for the player. You won't take damage.")]
    public bool GodMode = false;

    [HelpMarker("Adjusts gravity strength. 9.81 is Earth-like.")]
    public float Gravity = 9.81f;
}
```

In this example, a tooltip will appear showing the specified description when hovering over the **small question mark icon ("?")**.

---

### 🧩 HideInInspectorAttribute

This attribute prevents a public field from appearing in the Public Fields window. This is useful for hiding internal values that should not be edited at runtime, while still keeping them accessible in code.

Example
```C#
using IVSDKDotNet;
using IVSDKDotNet.Attributes;

public class ExampleScript : Script
{
    public bool IsActive = true;

    [HideInInspector]
    public float InternalTimer = 0f;
}
```

In this example, `InternalTimer` will not show up in the Public Fields window, even though it's a public field.

---

### 🧩 ReadOnlyInInspectorAttribute

This attribute makes a public field visible but not editable in the Public Fields window. This is useful for displaying debug information or runtime values without allowing users to modify them.

Example
```C#
using IVSDKDotNet;
using IVSDKDotNet.Attributes;

public class ExampleScript : Script
{
    public string PlayerName = "Niko";

    [ReadOnlyInInspector]
    public float CurrentHealth = 100f;
}
```

In this example, `CurrentHealth` will be shown in the UI but cannot be changed.

---

### 🧩 ExcludeFromJsonSerializationAttribute

This attribute prevents a field from being included when an object is serialized to JSON using IV-SDK .NET's helper utilities. This is useful for hiding sensitive data, temporary values, or runtime-only variables.  

Example
```C#
using System;
using System.Windows.Forms; // For "KeyEventArgs" and "Keys"

using IVSDKDotNet;
using IVSDKDotNet.Attributes;

public class PlayerData
{
    public string Name = "Niko";
    public int Level = 5;

    [ExcludeFromJsonSerialization]
    public string SessionToken = Guid.NewGuid().ToString();
}

public class Main : Script
{
    public Main()
    {
        KeyDown += Main_KeyDown;
    }

    public Main_KeyDown(object sender, KeyEventArgs e)
    {
        if (e.KeyCode == Keys.NumPad9)
        {
            PlayerData data = new PlayerData();
            Helper.ConvertObjectToJsonString(data, true); // Returns a string which contains the JSON
        }
    }
}
```

In this example, if `PlayerData` is serialized to JSON, the `SessionToken` field will be excluded from the output.

### Serialized Output:
```json
{
  "Name": "Niko",
  "Level": 5
}
```

---