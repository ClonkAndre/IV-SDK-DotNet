# IVAnimManager

### Definition
Namespace: `IVSDKDotNet`  
Path: `IVSDKDotNetWrapper/IVAnimManager.h`  
Source: [IVAnimManager.h](https://github.com/ClonkAndre/IV-SDK-DotNet/blob/main/IVSDKDotNetWrapper/IVAnimManager.h)

### Properties

<details>
<summary><b>AnimAssocDefinitions</b> - Gets or sets the array of animation association definitions.</summary>

#

Type: `IVAnimAssocDefinition[]`

Provides access to the array of animation association definitions (AnimAssocDefinition) used by the animation manager. You can retrieve or assign the entire array.

#

</details>

<details>
<summary><b>NumAnimAssocDefinitions</b> - Gets or sets the number of animation association definitions.</summary>

#

Type: `int`

Specifies the total count of animation association definitions currently managed by the animation manager.

#

</details>

### Methods

<details>
<summary><b>Initialise</b> - Initializes the animation manager.</summary>

#

### Parameters
None

## Return Value
`void`

#

</details>

<details>
<summary><b>AddAnimAssocDefinition</b> - Adds a new animation association definition.</summary>

#

### Parameters
`id (int)` - The identifier for the new animation association.  
`pName (String)` - The name of the animation association.  
`pFile (String)` - The file name associated with the animation block.  
`numAnims (uint)` - The number of animations in the association.  
`pAnimNames (String[])` - An array of animation names.  
`pAnimDescs (UIntPtr)` - A pointer to the animation descriptors.  
`unk1 (int)` - Unknown parameter 1.  
`unk2 (int)` - Unknown parameter 2.  
`unk3 (int)` - Unknown parameter 3.  
`unk4 (bool)` - Unknown boolean parameter.  

### Return Value
`void`

#

</details>