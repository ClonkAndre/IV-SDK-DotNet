#pragma once

using namespace System;
using namespace System::Drawing;
using namespace System::Windows::Forms;

// =======================================================================
// =========================== DEBUGGING =================================
// =======================================================================
#define SHOW_DEBUG_MESSAGES		true

#ifndef NDEBUG
#define DISABLE_ALL_MESSAGES	false
#else
#define DISABLE_ALL_MESSAGES	true
#endif

#define SHOW_MESSAGE(text)			if (SHOW_DEBUG_MESSAGES && !DISABLE_ALL_MESSAGES) MessageBox::Show(text, "IV-SDK DotNet");
#define SHOW_INFO_MESSAGE(text)		if (SHOW_DEBUG_MESSAGES && !DISABLE_ALL_MESSAGES) MessageBox::Show(text, "IV-SDK DotNet Info",	MessageBoxButtons::OK, MessageBoxIcon::Information);
#define SHOW_WARN_MESSAGE(text)		if (SHOW_DEBUG_MESSAGES && !DISABLE_ALL_MESSAGES) MessageBox::Show(text, "IV-SDK DotNet Warning",	MessageBoxButtons::OK, MessageBoxIcon::Warning);
#define SHOW_ERROR_MESSAGE(text)	if (SHOW_DEBUG_MESSAGES && !DISABLE_ALL_MESSAGES) MessageBox::Show(text, "IV-SDK DotNet Error",	MessageBoxButtons::OK, MessageBoxIcon::Error);

// =======================================================================
// ============================ DEFINES ==================================
// =======================================================================
#define WIN32_LEAN_AND_MEAN

#define NULL 0

#define VALIDATE_SIZE(struc, size)				static_assert(sizeof(struc) == size, "Invalid structure size of " #struc)
#define VALIDATE_OFFSET(struc, member, offset)	static_assert(offsetof(struc, member) == offset, "The offset of " #member " in " #struc " is not " #offset "...")

// =======================================================================
// ============================= TYPES ===================================
// =======================================================================
typedef bool b8;
typedef char ch;
typedef float f32;

typedef unsigned char uint8_t;
typedef unsigned int uint32_t;

typedef uint32_t ScriptVoid;	// uint32_t is unsigned int
typedef int ScriptAny;

typedef int Player;
typedef int Entity;
typedef Entity Ped;			// Entity is int
typedef Entity Car;			// Entity is int
typedef Entity Vehicle;		// Entity is int
typedef Entity Object;		// Entity is int
typedef uint32_t Hash;		// uint32_t is unsigned int
typedef int Cam;
typedef int FireId;
typedef int CarGenerator;
typedef int Group;
typedef int Train;
typedef int Pickup;
typedef int Object;
typedef int Weapon;
typedef int Interior;
typedef int Blip;
typedef int Texture;
typedef int TextureDict;
typedef int CoverPoint;
typedef int Camera;
typedef int TaskSequence;
typedef int ColourIndex;
typedef int Sphere;
typedef int ScrHandle;
typedef int DecisionMaker;
typedef int UnkInt;
typedef int Actor;
typedef int Controller;
typedef int Layout;
typedef int Iterator;
typedef int IterationSet;
typedef int GUIWindow;

//typedef union vector3
//{
//	struct { float x, y, z; };
//	float v[3];
//} vector3;
//
//typedef vector3 Vector3;