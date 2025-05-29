#pragma once

// =======================================================================
// =========================== DEBUGGING =================================
// =======================================================================
//#define SHOW_DEBUG_MESSAGES		true
//
//#ifndef NDEBUG
//#define DISABLE_ALL_MESSAGES	false
//#else
//#define DISABLE_ALL_MESSAGES	true
//#endif
//
//#define SHOW_MESSAGE(text)			if (SHOW_DEBUG_MESSAGES && !DISABLE_ALL_MESSAGES) MessageBox::Show(text, "IV-SDK .NET");
//#define SHOW_INFO_MESSAGE(text)		if (SHOW_DEBUG_MESSAGES && !DISABLE_ALL_MESSAGES) MessageBox::Show(text, "IV-SDK .NET Info",	MessageBoxButtons::OK, MessageBoxIcon::Information);
//#define SHOW_WARN_MESSAGE(text)		if (SHOW_DEBUG_MESSAGES && !DISABLE_ALL_MESSAGES) MessageBox::Show(text, "IV-SDK .NET Warning",	MessageBoxButtons::OK, MessageBoxIcon::Warning);
//#define SHOW_ERROR_MESSAGE(text)	if (SHOW_DEBUG_MESSAGES && !DISABLE_ALL_MESSAGES) MessageBox::Show(text, "IV-SDK .NET Error",	MessageBoxButtons::OK, MessageBoxIcon::Error);

// =======================================================================
// ============================ DEFINES ==================================
// =======================================================================
#define WIN32_LEAN_AND_MEAN

#define VALIDATE_SIZE(struc, size)				static_assert(sizeof(struc) == size, "Invalid structure size of " #struc)
#define VALIDATE_OFFSET(struc, member, offset)	static_assert(offsetof(struc, member) == offset, "The offset of " #member " in " #struc " is not " #offset "...")

#define NULLPTR_CHECK(ptr)							if (!ptr) return;
#define NULLPTR_CHECK_WITH_RETURN(ptr, ret)			if (!ptr) return ret;

#define INTPTR_ZERO_CHECK(ptr)						if (ptr == IntPtr::Zero) return;
#define INTPTR_ZERO_CHECK_WITH_RETURN(ptr, ret)	    if (ptr == IntPtr::Zero) return ret;
#define UINTPTR_ZERO_CHECK(ptr)						if (ptr == UIntPtr::Zero) return;
#define UINTPTR_ZERO_CHECK_WITH_RETURN(ptr, ret)	if (ptr == UIntPtr::Zero) return ret;

// Does the array given has a length of atleast x? If not, return.
#define CHECK_ARRAY_MINIMUM_LENGTH(arrLength, minimumLength)	if (arrLength < minimumLength) return;

#define CHECK_NULL_OR_WHITESPACE_STRING(str)					if (String::IsNullOrWhiteSpace(str)) return;
#define CHECK_NULL_OR_WHITESPACE_STRING_WITH_RETURN(str, ret)	if (String::IsNullOrWhiteSpace(str)) return ret;

#define GetManagerScript() IVSDKDotNet::Manager::ManagerScript::GetInstance()


// Vector stuff
static ImVec2 Vector2ToImVec2(Vector2 vec)
{
	return ImVec2(vec.X, vec.Y);
}
static ImVec4 Vector4ToImVec4(Vector4 vec)
{
	return ImVec4(vec.X, vec.Y, vec.Z, vec.W);
}

static ImU32 ColorToImU32(Color color)
{
	return IM_COL32(color.R, color.G, color.B, color.A);
}
static ImVec4 ColorToImVec4(Color color, bool convertToFloatRGBA)
{
	if (convertToFloatRGBA)
		return ImVec4(color.R / 255.0F, color.G / 255.0F, color.B / 255.0F, color.A / 255.0F);
	else
		return ImVec4(color.R, color.G, color.B, color.A);
}

static ImVec2 Add(ImVec2 first, ImVec2 second)
{
	return ImVec2(first.x + second.x, first.y + second.y);
}

static Vector2 ImVec2ToVector2(ImVec2 vec)
{
	return Vector2(vec.x, vec.y);
}
static Vector4 ImVec4ToVector4(ImVec4 vec)
{
	return Vector4(vec.x, vec.y, vec.z, vec.w);
}

static ImRect RectangleFToImRect(RectangleF rect)
{
	return ImRect(ImVec2(rect.X, rect.Y), ImVec2(rect.Right, rect.Bottom));
}
static ImRect Vector4ToImRect(Vector4 vec)
{
	return ImRect(ImVec2(vec.X, vec.Y), ImVec2(vec.Z, vec.W));
}

static RectangleF ImRectToRectangleF(ImRect rect)
{
	return RectangleF(rect.Min.x, rect.Min.y, rect.Max.x, rect.Max.y);
}

static Vector3 CVectorPadToVector3(CVector_pad v)
{
	return Vector3(v.x, v.y, v.z);
}
static Vector3 CVectorToVector3(CVector v)
{
	return Vector3(v.x, v.y, v.z);
}

static Vector3 CVector4ToVector3(CVector4 v)
{
	return System::Numerics::Vector3(v.x, v.y, v.z);
}

static CVector_pad Vector3ToCVectorPad(Vector3 v)
{
	CVector_pad pad;
	pad.flags = 0;
	pad.x = v.X;
	pad.y = v.Y;
	pad.z = v.Z;
	return pad;
}
static CVector Vector3ToCVector(Vector3 v)
{
	CVector pad;
	pad.x = v.X;
	pad.y = v.Y;
	pad.z = v.Z;
	return pad;
}

static Vector2 CVector2DToVector2(CVector2D v)
{
	return Vector2(v.x, v.y);
}
static CVector2D Vector2ToCVector2D(Vector2 v)
{
	CVector2D vec;
	vec.x = v.X;
	vec.y = v.Y;
	return vec;
}

static Quaternion CQuaternionToQuaternion(CQuaternion v)
{
	return Quaternion(v.x, v.y, v.z, v.w);
}
static CQuaternion QuaternionToCQuaternion(Quaternion v)
{
	CQuaternion quat;
	quat.x = v.X;
	quat.y = v.Y;
	quat.z = v.Z;
	quat.w = v.W;
	return quat;
}


// Logging
#ifdef _DEBUG

#define WRITE_TO_DEBUG_OUTPUT(text) if (System::Diagnostics::Debugger::IsAttached) System::Diagnostics::Debugger::Log(0, "IV-SDK .NET", text + "\n")

#else

#define WRITE_TO_DEBUG_OUTPUT(text)

#endif

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