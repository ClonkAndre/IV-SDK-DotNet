# SettingsFile

### Definition
Namespace: `IVSDKDotNet`  
Path: `IVSDKDotNetWrapper/SettingsFile.h`  
Source: [SettingsFile.h](https://github.com/ClonkAndre/IV-SDK-DotNet/blob/main/IVSDKDotNetWrapper/SettingsFile.h)

### Properties

<details>
<summary><b>FilePath</b> - Gets the path to the ini file.</summary>

#

Type: `String`

#

</details>

### Constructors

<details>
<summary><b>SettingsFile</b> - 1 Parameter</summary>

#

### Parameters
`filePath (String)` - The path to the ini file.

#

</details>


### Methods


<!------ Save ------>
<details>
<summary><b>Save</b> - Overrides the current ini file with the new content.</summary>

#

### Parameters
`None`

### Return Value
`bool` - **True if the file got saved. False when the file does not exists or if there is nothing to save.**

#

</details>

<!------ Load ------>
<details>
<summary><b>Load</b> - Loads the content of the specified ini file.</summary>

#

### Parameters
`None`

### Return Value
`bool` - **True if the file got loaded. False when the file does not exists.**

#

</details>

<!------ Clear ------>
<details>
<summary><b>Clear</b> - Clears everything from the loaded ini file.</summary>

#

### Parameters
`None`

### Return Value
`void`

#

</details>

<!------ GetSectionNames ------>
<details>
<summary><b>GetSectionNames</b> - Retrieves all the section names within the ini file.</summary>

#

### Parameters
`None`

### Return Value
`String[]` - **An array of type string containing all the current ini section names.**

#

</details>

<!------ GetValueNames ------>
<details>
<summary><b>GetValueNames</b> - Retrieves all the value names of a section within the ini file.</summary>

#

### Parameters
`section (String)` - **The section to retrieve all the value names of.**

### Return Value
`String[]` - **An array of type string containing all the current value names of the section.**

#

</details>

<!------ AddSection ------>
<details>
<summary><b>AddSection</b> - Adds a new section to the ini file.</summary>

#

### Parameters
`section (String)` - **The name of the new section.**

### Return Value
`bool` - **True if the section got created. Otherwise false if the section already exists in the ini or if the name is null.**

#

</details>

<!------ AddKeyToSection ------>
<details>
<summary><b>AddKeyToSection</b> - Adds a new key to the specified section.</summary>

#

### Parameters
`section (String)` - **The section to add the new key.**
`key (String)` - **The name of the new key.**

### Return Value
`bool` - **True if the key got created in the section. Otherwise false if the section does not exists, the key already exists in the ini or if the name is null.**

#

</details>

<!------ InsertAt ------>
<details>
<summary><b>InsertAt</b> - Allows you to insert a string at the given line number.</summary>

#

### Parameters
`line (int)` - **At which line you would like to add the new string.**
`str (String)` - **The string to add at the given line.**

### Return Value
`void`

#

</details>

<!------ DoesSectionExists ------>
<details>
<summary><b>DoesSectionExists</b> - Checks if a section exists.</summary>

#

### Parameters
`section (String)` - **The name of the section.**

### Return Value
`bool` - **True if the section exists. False if the given name is null or whitespace, or if the section does not exists.**

#

</details>

<!------ DoesKeyExists ------>
<details>
<summary><b>DoesKeyExists</b> - Checks if the key exists in the given section.</summary>

#

### Parameters
`section (String)` - **The section to check if the key exists in it.**
`key (String)` - **The key to check for if it exists in the given section.**

### Return Value
`bool` - **True if the key exists in the given secrion. False if any of the names is null or whitespace, or if the section or key does not exists.**

#

</details>

<!------ ClearSection ------>
<details>
<summary><b>ClearSection</b> - Clears all keys that are within the given section.</summary>

#

### Parameters
`section (String)` - **The section to clear all keys from.**

### Return Value
`bool` - **True if the keys should be removed from this section. False if the given name is null or whitespace, or if the section does not exists.**

#

</details>

<!------ GetTotalLineCount ------>
<details>
<summary><b>GetTotalLineCount</b> - Gets the total number of lines there are currently in the settings file.</summary>

#

### Parameters
`None`

### Return Value
`int` - **The current number of lines there will be file.**

#

</details>



<!------ GetValue ------>
<details>
<summary><b>GetValue</b> - Gets the value from the given section and key strings from the loaded ini file.</summary>

#

### Parameters
`section (String)` - **The section the key is located.**
`key (String)` - **The key you want to get the value from.**
`defaultValue (String)` - **The default value if get value fails.**

### Return Value
`String` - **The value from the given section and key strings. Otherwise it returns defaultValue.**

#

</details>

<!------ SetValue ------>
<details>
<summary><b>SetValue</b> - Sets the value from the given section and key strings from the loaded ini file.</summary>

#

### Parameters
`section (String)` - **The section the key is located.**
`key (String)` - **The key you want to set the value to.**
`value (String)` - **The new value.**

### Return Value
`bool` - **True if the value from the given section and key got changed. Otherwise false if the section or key does not exists.**

#

</details>



<!------ GetBoolean ------>
<details>
<summary><b>GetBoolean</b> - Gets the boolean from the given section and key strings from the loaded ini file.</summary>

#

### Parameters
`section (String)` - **The section the key is located.**
`key (String)` - **The key you want to get the value from.**
`defaultValue (bool)` - **The default value if get value fails.**

### Return Value
`bool` - **The boolean from the given section and key strings. Otherwise it returns defaultValue.**

#

</details>

<!------ SetBoolean ------>
<details>
<summary><b>SetBoolean</b> - Sets the boolean from the given section and key strings from the loaded ini file..</summary>

#

### Parameters
`section (String)` - **The section the key is located.**
`key (String)` - **The key you want to set the value to.**
`value (bool)` - **The new value.**

### Return Value
`bool` - **True if the value from the given section and key got changed. Otherwise false if the section or key does not exists.**

#

</details>



<!------ GetInteger ------>
<details>
<summary><b>GetInteger</b> - Gets the integer from the given section and key strings from the loaded ini file.</summary>

#

### Parameters
`section (String)` - **The section the key is located.**
`key (String)` - **The key you want to get the value from.**
`defaultValue (int)` - **The default value if get value fails.**

### Return Value
`int` - **The integer from the given section and key strings. Otherwise it returns defaultValue.**

#

</details>

<!------ SetInteger ------>
<details>
<summary><b>SetInteger</b> - Sets the integer from the given section and key strings from the loaded ini file.</summary>

#

### Parameters
`section (String)` - **The section the key is located.**
`key (String)` - **The key you want to set the value to.**
`value (int)` - **The new value.**

### Return Value
`bool` - **True if the value from the given section and key got changed. Otherwise false if the section or key does not exists.**

#

</details>



<!------ GetUInteger ------>
<details>
<summary><b>GetUInteger</b> - Gets the unsigned integer from the given section and key strings from the loaded ini file.</summary>

#

### Parameters
`section (String)` - **The section the key is located.**
`key (String)` - **The key you want to get the value from.**
`defaultValue (uint)` - **The default value if get value fails.**

### Return Value
`uint` - **The unsigned integer from the given section and key strings. Otherwise it returns defaultValue.**

#

</details>

<!------ SetUInteger ------>
<details>
<summary><b>SetUInteger</b> - Sets the unsigned integer from the given section and key strings from the loaded ini file.</summary>

#

### Parameters
`section (String)` - **The section the key is located.**
`key (String)` - **The key you want to set the value to.**
`value (uint)` - **The new value.**

### Return Value
`bool` - **True if the value from the given section and key got changed. Otherwise false if the section or key does not exists.**

#

</details>



<!------ GetFloat ------>
<details>
<summary><b>GetFloat</b> - Gets the float from the given section and key strings from the loaded ini file.</summary>

#

### Parameters
`section (String)` - **The section the key is located.**
`key (String)` - **The key you want to get the value from.**
`defaultValue (float)` - **The default value if get value fails.**

### Return Value
`float` - **The float from the given section and key strings. Otherwise it returns defaultValue.**

#

</details>

<!------ SetFloat ------>
<details>
<summary><b>SetFloat</b> - Sets the float from the given section and key strings from the loaded ini file.</summary>

#

### Parameters
`section (String)` - **The section the key is located.**
`key (String)` - **The key you want to set the value to.**
`value (float)` - **The new value.**

### Return Value
`bool` - **True if the value from the given section and key got changed. Otherwise false if the section or key does not exists.**

#

</details>



<!------ GetDouble ------>
<details>
<summary><b>GetDouble</b> - Gets the double from the given section and key strings from the loaded ini file.</summary>

#

### Parameters
`section (String)` - **The section the key is located.**
`key (String)` - **The key you want to get the value from.**
`defaultValue (double)` - **The default value if get value fails.**

### Return Value
`double` - **The double from the given section and key strings. Otherwise it returns defaultValue.**

#

</details>

<!------ SetDouble ------>
<details>
<summary><b>SetDouble</b> - Sets the double from the given section and key strings from the loaded ini file.</summary>

#

### Parameters
`section (String)` - **The section the key is located.**
`key (String)` - **The key you want to set the value to.**
`value (double)` - **The new value.**

### Return Value
`bool` - **True if the value from the given section and key got changed. Otherwise false if the section or key does not exists.**

#

</details>



<!------ GetColor ------>
<details>
<summary><b>GetColor</b> - Gets the Color from the given section and key strings from the loaded ini file.</summary>

#

### Parameters
`section (String)` - **The section the key is located.**
`key (String)` - **The key you want to get the value from.**
`defaultValue (Color)` - **The default value if get value fails.**

### Return Value
`Color` - **The color from the given section and key strings. Otherwise it returns defaultValue.**

#

</details>

<!------ SetColor ------>
<details>
<summary><b>SetColor</b> - Sets the color from the given section and key strings from the loaded ini file.</summary>

#

### Parameters
`section (String)` - **The section the key is located.**
`key (String)` - **The key you want to set the value to.**
`value (Color)` - **The new value.**

### Return Value
`bool` - **True if the value from the given section and key got changed. Otherwise false if the section or key does not exists.**

#

</details>



<!------ GetKey ------>
<details>
<summary><b>GetKey</b> - Gets the WinForms Key from the given section and key strings from the loaded ini file.</summary>

#

### Parameters
`section (String)` - **The section the key is located.**
`key (String)` - **The key you want to get the value from.**
`defaultValue (Keys)` - **The default value if get value fails.**

### Return Value
`Keys` - **The WinForms Key from the given section and key strings. Otherwise it returns defaultValue.**

#

</details>

<!------ SetKey ------>
<details>
<summary><b>SetKey</b> - Sets the WinForms Key from the given section and key strings from the loaded ini file.</summary>

#

### Parameters
`section (String)` - **The section the key is located.**
`key (String)` - **The key you want to set the value to.**
`value (Keys)` - **The new value.**

### Return Value
`bool` - **True if the value from the given section and key got changed. Otherwise false if the section or key does not exists.**

#

</details>



<!------ GetQuaternion ------>
<details>
<summary><b>GetQuaternion</b> - Gets the Quaternion from the given section and key strings from the loaded ini file.</summary>

#

### Parameters
`section (String)` - **The section the key is located.**
`key (String)` - **The key you want to get the value from.**
`defaultValue (Quaternion)` - **The default value if get value fails.**

### Return Value
`Keys` - **The Quaternion from the given section and key strings. Otherwise it returns defaultValue.**

#

</details>

<!------ SetQuaternion ------>
<details>
<summary><b>SetQuaternion</b> - Sets the Quaternion from the given section and key strings from the loaded ini file.</summary>

#

### Parameters
`section (String)` - **The section the key is located.**
`key (String)` - **The key you want to set the value to.**
`value (Quaternion)` - **The new value.**

### Return Value
`bool` - **True if the value from the given section and key got changed. Otherwise false if the section or key does not exists.**

#

</details>



<!------ GetVector2 ------>
<details>
<summary><b>GetVector2</b> - Gets the Vector2 from the given section and key strings from the loaded ini file.</summary>

#

### Parameters
`section (String)` - **The section the key is located.**
`key (String)` - **The key you want to get the value from.**
`defaultValue (Vector2)` - **The default value if get value fails.**

### Return Value
`Vector2` - **The Vector2 from the given section and key strings. Otherwise it returns defaultValue.**

#

</details>

<!------ SetVector2 ------>
<details>
<summary><b>SetVector2</b> - Sets the Vector2 from the given section and key strings from the loaded ini file.</summary>

#

### Parameters
`section (String)` - **The section the key is located.**
`key (String)` - **The key you want to set the value to.**
`value (Vector2)` - **The new value.**

### Return Value
`bool` - **True if the value from the given section and key got changed. Otherwise false if the section or key does not exists.**

#

</details>



<!------ GetVector3 ------>
<details>
<summary><b>GetVector3</b> - Gets the Vector3 from the given section and key strings from the loaded ini file.</summary>

#

### Parameters
`section (String)` - **The section the key is located.**
`key (String)` - **The key you want to get the value from.**
`defaultValue (Vector3)` - **The default value if get value fails.**

### Return Value
`Vector3` - **The Vector3 from the given section and key strings. Otherwise it returns defaultValue.**

#

</details>

<!------ SetVector3 ------>
<details>
<summary><b>SetVector3</b> - Sets the Vector3 from the given section and key strings from the loaded ini file.</summary>

#

### Parameters
`section (String)` - **The section the key is located.**
`key (String)` - **The key you want to set the value to.**
`value (Vector3)` - **The new value.**

### Return Value
`bool` - **True if the value from the given section and key got changed. Otherwise false if the section or key does not exists.**

#

</details>



<!------ GetVector4 ------>
<details>
<summary><b>GetVector4</b> - Gets the Vector4 from the given section and key strings from the loaded ini file.</summary>

#

### Parameters
`section (String)` - **The section the key is located.**
`key (String)` - **The key you want to get the value from.**
`defaultValue (Vector4)` - **The default value if get value fails.**

### Return Value
`Vector4` - **The Vector4 from the given section and key strings. Otherwise it returns defaultValue.**

#

</details>

<!------ SetVector4 ------>
<details>
<summary><b>SetVector4</b> - Sets the Vector4 from the given section and key strings from the loaded ini file.</summary>

#

### Parameters
`section (String)` - **The section the key is located.**
`key (String)` - **The key you want to set the value to.**
`value (Vector4)` - **The new value.**

### Return Value
`bool` - **True if the value from the given section and key got changed. Otherwise false if the section or key does not exists.**

#

</details>