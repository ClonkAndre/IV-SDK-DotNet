#pragma once

//using namespace System::Runtime::InteropServices;

namespace IVSDKDotNet {
	namespace Native {

		public ref class Function
		{
		public:

			/// <summary>
			/// Does not work yet!
			/// </summary>
			/// <typeparam name="T"></typeparam>
			/// <param name="nativeHash"></param>
			/// <param name="params"></param>
			generic <typename T>
			static void Call(NativeHash nativeHash, ... array<T>^ params);

			/// <summary>
			/// Does not work yet!
			/// </summary>
			/// <typeparam name="R"></typeparam>
			/// <typeparam name="T"></typeparam>
			/// <param name="nativeHash"></param>
			/// <param name="params"></param>
			/// <returns></returns>
			generic <typename R, typename T>
			static R	Call(NativeHash nativeHash, ... array<T>^ params);

		};

		/// <summary>
		/// GTA IV Native Functions.
		/// Functions with an underscore at the beginning will most likely crash the game.
		/// </summary>
		public ref class Natives
		{
		public:

			static void ADD_ARMOUR_TO_CHAR(Ped ped, unsigned int amount) {  NativeInvoke::Invoke<ScriptVoid>(NATIVE_ADD_ARMOUR_TO_CHAR, ped, amount); }
			static void ATTACH_ANIMS_TO_MODEL(unsigned int model, String^ anims)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke<ScriptVoid>(NATIVE_ATTACH_ANIMS_TO_MODEL, model, ctx.marshal_as<const char*>(anims));
			}
			static void BEGIN_CHAR_SEARCH_CRITERIA() { NativeInvoke::Invoke<ScriptVoid>(NATIVE_BEGIN_CHAR_SEARCH_CRITERIA); }
			static unsigned int GET_AUDIBLE_MUSIC_TRACK_TEXT_ID() { return NativeInvoke::Invoke<unsigned int>(NATIVE_GET_AUDIBLE_MUSIC_TRACK_TEXT_ID); }
			static void BLEND_FROM_NM_WITH_ANIM(Ped ped, String^ AnimName0, String^ AnimName1, int Unk1, float x, float y, float z)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke<ScriptVoid>(NATIVE_BLEND_FROM_NM_WITH_ANIM, ped, ctx.marshal_as<const char*>(AnimName0), ctx.marshal_as<const char*>(AnimName1), Unk1, x, y, z);
			}
			static void BLEND_OUT_CHAR_MOVE_ANIMS(Ped ped) { NativeInvoke::Invoke<ScriptVoid>(NATIVE_BLEND_OUT_CHAR_MOVE_ANIMS, ped); }
			static void BLOCK_CHAR_AMBIENT_ANIMS(Ped ped, b8 block) { NativeInvoke::Invoke<ScriptVoid>(NATIVE_BLOCK_CHAR_AMBIENT_ANIMS, ped, block); }
			static void BLOCK_CHAR_GESTURE_ANIMS(Ped ped, b8 value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_BLOCK_CHAR_GESTURE_ANIMS, ped, value); }
			static void BLOCK_CHAR_HEAD_IK(Ped ped, b8 block) { NativeInvoke::Invoke<ScriptVoid>(NATIVE_BLOCK_CHAR_HEAD_IK, ped, block); }
			static void BLOCK_CHAR_VISEME_ANIMS(Ped ped, b8 block) { NativeInvoke::Invoke<ScriptVoid>(NATIVE_BLOCK_CHAR_VISEME_ANIMS, ped, block); }
			static void CANCEL_CURRENTLY_PLAYING_AMBIENT_SPEECH(Ped ped) { NativeInvoke::Invoke<ScriptVoid>(NATIVE_CANCEL_CURRENTLY_PLAYING_AMBIENT_SPEECH, ped); }
			static void CHANGE_CHAR_SIT_IDLE_ANIM(Ped ped, ScriptAny Unk2, ScriptAny Unk3, ScriptAny Unk4) { NativeInvoke::Invoke<ScriptVoid>(NATIVE_CHANGE_CHAR_SIT_IDLE_ANIM, ped, Unk2, Unk3, Unk4); }
			static void CLEAR_ALL_CHAR_PROPS(Ped ped) { NativeInvoke::Invoke<ScriptVoid>(NATIVE_CLEAR_ALL_CHAR_PROPS, ped); }
			static void CLEAR_ALL_CHAR_RELATIONSHIPS(Ped ped, int relgroup) { NativeInvoke::Invoke<ScriptVoid>(NATIVE_CLEAR_ALL_CHAR_RELATIONSHIPS, ped, relgroup); }
			static void CLEAR_CHAR_LAST_DAMAGE_BONE(Ped ped) { NativeInvoke::Invoke<ScriptVoid>(NATIVE_CLEAR_CHAR_LAST_DAMAGE_BONE, ped); }
			static void CLEAR_CHAR_LAST_DAMAGE_ENTITY(Ped ped) { NativeInvoke::Invoke<ScriptVoid>(NATIVE_CLEAR_CHAR_LAST_DAMAGE_ENTITY, ped); }
			static void CLEAR_CHAR_LAST_WEAPON_DAMAGE(Ped ped) { NativeInvoke::Invoke<ScriptVoid>(NATIVE_CLEAR_CHAR_LAST_WEAPON_DAMAGE, ped); }
			static void CLEAR_CHAR_PROP(Ped ped, int unknown) { NativeInvoke::Invoke<ScriptVoid>(NATIVE_CLEAR_CHAR_PROP, ped, unknown); }
			static void CLEAR_CHAR_RELATIONSHIP(Ped ped, int reltype, int relgroup) { NativeInvoke::Invoke<ScriptVoid>(NATIVE_CLEAR_CHAR_RELATIONSHIP, ped, reltype, relgroup); }
			static void CLEAR_CHAR_SECONDARY_TASK(Ped ped) { NativeInvoke::Invoke<ScriptVoid>(NATIVE_CLEAR_CHAR_SECONDARY_TASK, ped); }
			static void CLEAR_CHAR_TASKS(Ped ped) { NativeInvoke::Invoke<ScriptVoid>(NATIVE_CLEAR_CHAR_TASKS, ped); }
			static void CLEAR_CHAR_TASKS_IMMEDIATELY(Ped ped) { NativeInvoke::Invoke<ScriptVoid>(NATIVE_CLEAR_CHAR_TASKS_IMMEDIATELY, ped); }
			static void CLEAR_RELATIONSHIP(int p0, int p1, int p2) { NativeInvoke::Invoke<ScriptVoid>(NATIVE_CLEAR_RELATIONSHIP, p0, p1, p2); }
			static void CLEAR_ROOM_FOR_CHAR(Ped ped) { NativeInvoke::Invoke<ScriptVoid>(NATIVE_CLEAR_ROOM_FOR_CHAR, ped); }
			static void CREATE_CHAR(int type, int model, Vector3 pos, [OutAttribute] Ped% pPed, b8 unknownTrue)
			{
				Ped p;
				NativeInvoke::Invoke<ScriptVoid>(NATIVE_CREATE_CHAR, type, model, pos.X, pos.Y, pos.Z, &p, unknownTrue);
				pPed = p;
			}
			static void CREATE_CHAR(int type, int model, float x, float y, float z, [OutAttribute] Ped% pPed, b8 unknownTrue)
			{
				Ped p;
				NativeInvoke::Invoke<ScriptVoid>(NATIVE_CREATE_CHAR, type, model, x, y, z, &p, unknownTrue);
				pPed = p;
			}
			static void CREATE_CHAR_AS_PASSENGER(Vehicle vehicle, unsigned int charType, unsigned int model, unsigned int passengerIndex, [OutAttribute] Ped% pPed)
			{
				Ped p;
				NativeInvoke::Invoke<ScriptVoid>(NATIVE_CREATE_CHAR_AS_PASSENGER, vehicle, charType, model, passengerIndex, &p);
				pPed = p;
			}
			static void CREATE_CHAR_INSIDE_CAR(Vehicle vehicle, unsigned int charType, unsigned int model, [OutAttribute] Ped% pPed)
			{
				Ped p;
				NativeInvoke::Invoke<ScriptVoid>(NATIVE_CREATE_CHAR_INSIDE_CAR, vehicle, charType, model, &p);
				pPed = p;
			}
			static void CREATE_RANDOM_CHAR(float x, float y, float z, [OutAttribute] Ped% pPed)
			{
				Ped p;
				NativeInvoke::Invoke<ScriptVoid>(NATIVE_CREATE_RANDOM_CHAR, x, y, z, &p);
				pPed = p;
			}
			static void CREATE_RANDOM_CHAR_AS_PASSENGER(Vehicle vehicle, unsigned int seat, Ped% pPed) { NativeInvoke::Invoke<ScriptVoid>(NATIVE_CREATE_RANDOM_CHAR_AS_PASSENGER, vehicle, seat, pPed); }
			static void CREATE_RANDOM_FEMALE_CHAR(float x, float y, float z, Ped% pPed) { NativeInvoke::Invoke<ScriptVoid>(NATIVE_CREATE_RANDOM_FEMALE_CHAR, x, y, z, pPed); }
			static void CREATE_RANDOM_MALE_CHAR(float x, float y, float z, Ped% pPed) { NativeInvoke::Invoke<ScriptVoid>(NATIVE_CREATE_RANDOM_MALE_CHAR, x, y, z, pPed); }
			static void DAMAGE_CHAR(Ped ped, unsigned int hitPoints, b8 unknown) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DAMAGE_CHAR, ped, hitPoints, unknown); }
			
			[System::ObsoleteAttribute("This native is obsolete. Use CPools.DeleteChar instead.")]
			static void DELETE_CHAR(Ped* pPed) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DELETE_CHAR, pPed); }

			static void DONT_REMOVE_CHAR(Ped ped) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DONT_REMOVE_CHAR, ped); }
			static void END_CHAR_SEARCH_CRITERIA() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_END_CHAR_SEARCH_CRITERIA); }
			static void EXPLODE_CHAR_HEAD(Ped ped) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_EXPLODE_CHAR_HEAD, ped); }
			static void EXTINGUISH_CHAR_FIRE(Ped ped) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_EXTINGUISH_CHAR_FIRE, ped); }
			static void FREEZE_CHAR_POSITION(Ped ped, b8 frozen) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_FREEZE_CHAR_POSITION, ped, frozen); }
			static void FREEZE_CHAR_POSITION_AND_DONT_LOAD_COLLISION(Ped ped, b8 frozen) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_FREEZE_CHAR_POSITION_AND_DONT_LOAD_COLLISION, ped, frozen); }
			static void GET_CHAR_ANIM_CURRENT_TIME(Ped ped, String^ animGroup, String^ animName, [OutAttribute] float% pValue)
			{
				float v;
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke<ScriptVoid>(NATIVE_GET_CHAR_ANIM_CURRENT_TIME, ped, ctx.marshal_as<const char*>(animGroup), ctx.marshal_as<const char*>(animName), &v);
				pValue = v;
			}
			static void GET_CHAR_ANIM_TOTAL_TIME(Ped ped, String^ animGroup, String^ animName, [OutAttribute] float% pValue)
			{
				float p;
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke<ScriptVoid>(NATIVE_GET_CHAR_ANIM_TOTAL_TIME, ped, ctx.marshal_as<const char*>(animGroup), ctx.marshal_as<const char*>(animName), &p);
				pValue = p;
			}
			static void GET_CHAR_ARMOUR(Ped ped, [OutAttribute] unsigned int% pArmour)
			{
				unsigned int p;
				NativeInvoke::Invoke<ScriptVoid>(NATIVE_GET_CHAR_ARMOUR, ped, &p);
				pArmour = p;
			}
			static void GET_CHAR_COORDINATES(Ped ped, [OutAttribute] Vector3% pos)
			{
				float x, y, z;
				NativeInvoke::Invoke<ScriptVoid>(NATIVE_GET_CHAR_COORDINATES, ped, &x, &y, &z);
				pos = Vector3(x, y, z);
			}
			static void GET_CHAR_COORDINATES(Ped ped, [OutAttribute] float% pX, [OutAttribute] float% pY, [OutAttribute] float% pZ)
			{
				float x, y, z;
				NativeInvoke::Invoke<ScriptVoid>(NATIVE_GET_CHAR_COORDINATES, ped, &x, &y, &z);
				pX = x;
				pY = y;
				pZ = z;
			}
			static void GET_CHAR_EXTRACTED_DISPLACEMENT(Ped ped, b8 unknown, [OutAttribute] float% pX, [OutAttribute] float% pY, [OutAttribute] float% pZ)
			{
				float x, y, z;
				NativeInvoke::Invoke<ScriptVoid>(NATIVE_GET_CHAR_EXTRACTED_DISPLACEMENT, ped, unknown, &x, &y, &z);
				pX = x;
				pY = y;
				pZ = z;
			}
			static void GET_CHAR_EXTRACTED_VELOCITY(Ped ped, b8 Unk5, [OutAttribute] float% pX, [OutAttribute] float% pY, [OutAttribute] float% pZ)
			{
				float x, y, z;
				NativeInvoke::Invoke<ScriptVoid>(NATIVE_GET_CHAR_EXTRACTED_VELOCITY, ped, Unk5, &x, &y, &z);
				pX = x;
				pY = y;
				pZ = z;
			}
			static void GET_CHAR_HEADING(Ped ped, [OutAttribute] f32% pValue)
			{
				f32 p;
				NativeInvoke::Invoke<ScriptVoid>(NATIVE_GET_CHAR_HEADING, ped, &p);
				pValue = p;
			}
			static void GET_CHAR_HEALTH(Ped ped, [OutAttribute] unsigned int% pHealth)
			{
				unsigned int p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_CHAR_HEALTH, ped, &p);
				pHealth = p;
			}
			static void GET_CHAR_HEIGHT_ABOVE_GROUND(Ped ped, [OutAttribute] float% pValue)
			{
				float p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_CHAR_HEIGHT_ABOVE_GROUND, ped, &p);
				pValue = p;
			}
			static void GET_CHAR_HIGHEST_PRIORITY_EVENT(Ped ped, [OutAttribute] int% pEvent)
			{
				int p;
				NativeInvoke::Invoke<ScriptVoid>(NATIVE_GET_CHAR_HIGHEST_PRIORITY_EVENT, ped, &p);
				pEvent = p;
			}
			static void GET_CHAR_IN_CAR_PASSENGER_SEAT(Vehicle vehicle, unsigned int seatIndex, [OutAttribute] Ped% pPed)
			{
				Ped p;
				NativeInvoke::Invoke<ScriptVoid>(NATIVE_GET_CHAR_IN_CAR_PASSENGER_SEAT, vehicle, seatIndex, &p);
				pPed = p;
			}
			static void GET_CHAR_MODEL(Ped ped, [OutAttribute] unsigned int% pModel)
			{
				unsigned int p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_CHAR_MODEL, ped, &p);
				pModel = p;
			}
			static void GET_CHAR_MODEL(Ped ped, [OutAttribute] int% pModel)
			{
				int p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_CHAR_MODEL, ped, &p);
				pModel = p;
			}
			static void GET_CHAR_MOVE_ANIM_SPEED_MULTIPLIER(Ped ped, [OutAttribute] float% pMultiplier)
			{
				float p;
				NativeInvoke::Invoke<ScriptVoid>(NATIVE_GET_CHAR_MOVE_ANIM_SPEED_MULTIPLIER, ped, &p);
				pMultiplier = p;
			}
			static void GET_CHAR_PROP_INDEX(Ped ped, int unknown, [OutAttribute] int% pIndex)
			{
				int p;
				NativeInvoke::Invoke<ScriptVoid>(NATIVE_GET_CHAR_PROP_INDEX, ped, unknown, &p);
				pIndex = p;
			}
			static void GET_CHAR_SPEED(Ped ped, [OutAttribute] float% pValue)
			{
				float p;
				NativeInvoke::Invoke<ScriptVoid>(NATIVE_GET_CHAR_SPEED, ped, &p);
				pValue = p;
			}
			static void GET_CHAR_VELOCITY(Ped ped, [OutAttribute] float% pX, [OutAttribute] float% pY, [OutAttribute] float% pZ)
			{
				float x, y, z;
				NativeInvoke::Invoke<ScriptVoid>(NATIVE_GET_CHAR_VELOCITY, ped, &x, &y, &z);
				pX = x;
				pY = y;
				pZ = z;
			}
			static void GET_DEAD_CHAR_PICKUP_COORDS(Ped ped, [OutAttribute] float% pX, [OutAttribute] float% pY, [OutAttribute] float% pZ)
			{
				float x, y, z;
				NativeInvoke::Invoke<ScriptVoid>(NATIVE_GET_DEAD_CHAR_PICKUP_COORDS, ped, &x, &y, &z);
				pX = x;
				pY = y;
				pZ = z;
			}
			static void GET_KEY_FOR_CHAR_IN_ROOM(Ped ped, [OutAttribute] unsigned int% pKey)
			{
				unsigned int p;
				NativeInvoke::Invoke<ScriptVoid>(NATIVE_GET_KEY_FOR_CHAR_IN_ROOM, ped, &p);
				pKey = p;
			}
			static void GET_OFFSET_FROM_CHAR_IN_WORLD_COORDS(Ped ped, float pX, float pY, float pZ, [OutAttribute] float% pOffX, [OutAttribute] float% pOffY, [OutAttribute] float% pOffZ)
			{
				float x, y, z;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_OFFSET_FROM_CHAR_IN_WORLD_COORDS, ped, pX, pY, pZ, &x, &y, &z);
				pOffX = x;
				pOffY = y;
				pOffZ = z;
			}
			static void MARK_CHAR_AS_NO_LONGER_NEEDED(Ped% pPed) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_MARK_CHAR_AS_NO_LONGER_NEEDED, pPed); }
			static void MODIFY_CHAR_MOVE_BLEND_RATIO(Ped ped, ScriptAny Unk6) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_MODIFY_CHAR_MOVE_BLEND_RATIO, ped, Unk6); }
			static void MODIFY_CHAR_MOVE_STATE(Ped ped, unsigned int state) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_MODIFY_CHAR_MOVE_STATE, ped, state); }
			static void REMOVE_CHAR_DEFENSIVE_AREA(Ped ped) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_REMOVE_CHAR_DEFENSIVE_AREA, ped); }
			static void REMOVE_CHAR_ELEGANTLY(Ped ped) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_REMOVE_CHAR_ELEGANTLY, ped); }
			static void REMOVE_CHAR_FROM_CAR_MAINTAIN_POSITION(Ped ped, Vehicle car) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_REMOVE_CHAR_FROM_CAR_MAINTAIN_POSITION, ped, car); }
			static void REMOVE_CHAR_FROM_GROUP(Ped ped) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_REMOVE_CHAR_FROM_GROUP, ped); }
			static void SET_ANIM_GROUP_FOR_CHAR(Ped ped, String^ grname)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_ANIM_GROUP_FOR_CHAR, ped, ctx.marshal_as<const char*>(grname));
			}
			static void SET_CHAR_ACCURACY(Ped ped, unsigned int value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_ACCURACY, ped, value); }
			static void SET_CHAR_ALLOWED_TO_DUCK(Ped ped, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_ALLOWED_TO_DUCK, ped, set); }
			static void SET_CHAR_ALL_ANIMS_SPEED(Ped ped, float speed) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_ALL_ANIMS_SPEED, ped, speed); }
			static void SET_CHAR_ANGLED_DEFENSIVE_AREA(Ped ped, float x0, float y0, float z0, float x1, float y1, float z1, float angle) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_ANGLED_DEFENSIVE_AREA, ped, x0, y0, z0, x1, y1, z1, angle); }
			static void SET_CHAR_ANIM_CURRENT_TIME(Ped ped, String^ AnimName0, String^ AnimName1, float time)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_ANIM_CURRENT_TIME, ped, ctx.marshal_as<const char*>(AnimName0), ctx.marshal_as<const char*>(AnimName1), time);
			}
			static void SET_CHAR_ANIM_SPEED(Ped ped, String^ AnimName0, String^ AnimName1, float speed)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_ANIM_SPEED, ped, ctx.marshal_as<const char*>(AnimName0), ctx.marshal_as<const char*>(AnimName1), speed);
			}
			static void SET_CHAR_AS_ENEMY(Ped ped, b8 value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_AS_ENEMY, ped, value); }
			static void SET_CHAR_AS_MISSION_CHAR(Ped ped) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_AS_MISSION_CHAR, ped); }
			static void SET_CHAR_BLEEDING(Ped ped, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_BLEEDING, ped, set); }
			static void SET_CHAR_BULLETPROOF_VEST(Ped ped, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_BULLETPROOF_VEST, ped, set); }
			static void SET_CHAR_CANT_BE_DRAGGED_OUT(Ped ped, b8 enabled) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_CANT_BE_DRAGGED_OUT, ped, enabled); }
			static void SET_CHAR_CAN_BE_KNOCKED_OFF_BIKE(Ped ped, b8 value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_CAN_BE_KNOCKED_OFF_BIKE, ped, value); }
			static void SET_CHAR_CAN_BE_SHOT_IN_VEHICLE(Ped ped, b8 enabled) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_CAN_BE_SHOT_IN_VEHICLE, ped, enabled); }
			static void SET_CHAR_CAN_SMASH_GLASS(Ped ped, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_CAN_SMASH_GLASS, ped, set); }
			static void SET_CHAR_CLIMB_ANIM_RATE(Ped ped, float rate) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_CLIMB_ANIM_RATE, ped, rate); }
			static void SET_CHAR_COLLISION(Ped ped, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_COLLISION, ped, set); }
			static void SET_CHAR_COMPONENT_VARIATION(Ped ped, unsigned int component, unsigned int modelVariation, unsigned int textureVariation) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_COMPONENT_VARIATION, ped, component, modelVariation, textureVariation); }
			static void SET_CHAR_COORDINATES(Ped ped, Vector3 pos) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_COORDINATES, ped, pos.X, pos.Y, pos.Z); }
			static void SET_CHAR_COORDINATES(Ped ped, float x, float y, float z) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_COORDINATES, ped, x, y, z); }
			static void SET_CHAR_COORDINATES_DONT_WARP_GANG(Ped ped, float x, float y, float z) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_COORDINATES_DONT_WARP_GANG, ped, x, y, z); }
			static void SET_CHAR_COORDINATES_DONT_WARP_GANG_NO_OFFSET(Ped ped, float x, float y, float z) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_COORDINATES_DONT_WARP_GANG_NO_OFFSET, ped, x, y, z); }
			static void _SET_CHAR_COORDINATES_NO_OFFSET(Ped ped, float x, float y, float z) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_COORDINATES_NO_OFFSET, ped, x, y, z); }
			static void SET_CHAR_DEFAULT_COMPONENT_VARIATION(Ped ped) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_DEFAULT_COMPONENT_VARIATION, ped); }
			static void SET_CHAR_DEFENSIVE_AREA_ATTACHED_TO_PED(Ped ped, Ped pednext, float x0, float y0, float z0, float x1, float y1, float z1, int Unk7, int Unk8) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_DEFENSIVE_AREA_ATTACHED_TO_PED, ped, pednext, x0, y0, z0, x1, y1, z1, Unk7, Unk8); }
			static void SET_CHAR_DESIRED_HEADING(Ped ped, float heading) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_DESIRED_HEADING, ped, heading); }
			static void SET_CHAR_DIES_INSTANTLY_IN_WATER(Ped ped, b8 allow) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_DIES_INSTANTLY_IN_WATER, ped, allow); }
			static void SET_CHAR_DROPS_WEAPONS_WHEN_DEAD(Ped ped, b8 value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_DROPS_WEAPONS_WHEN_DEAD, ped, value); }
			static void SET_CHAR_DROWNS_IN_SINKING_VEHICLE(Ped ped, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_DROWNS_IN_SINKING_VEHICLE, ped, set); }
			static void SET_CHAR_DROWNS_IN_WATER(Ped ped, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_DROWNS_IN_WATER, ped, set); }
			static void SET_CHAR_DRUGGED_UP(Ped ped, b8 drugged) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_DRUGGED_UP, ped, drugged); }
			static void SET_CHAR_DUCKING_TIMED(Ped ped, int timed) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_DUCKING_TIMED, ped, timed); }
			static void SET_CHAR_FIRE_DAMAGE_MULTIPLIER(Ped ped, float multiplier) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_FIRE_DAMAGE_MULTIPLIER, ped, multiplier); }
			static void SET_CHAR_FORCE_DIE_IN_CAR(Ped ped, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_FORCE_DIE_IN_CAR, ped, set); }
			static void SET_CHAR_GESTURE_GROUP(Ped ped, String^ AnimGroup)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_GESTURE_GROUP, ped, ctx.marshal_as<const char*>(AnimGroup));
			}
			static void SET_CHAR_GET_OUT_UPSIDE_DOWN_CAR(Ped ped, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_GET_OUT_UPSIDE_DOWN_CAR, ped, set); }
			static void SET_CHAR_GRAVITY(Ped ped, float value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_GRAVITY, ped, value); }
			static void SET_CHAR_HEADING(Ped ped, float heading) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_HEADING, ped, heading); }
			static void SET_CHAR_HEALTH(Ped ped, unsigned int health) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_HEALTH, ped, health); }
			static void SET_CHAR_INVINCIBLE(Ped ped, b8 enable) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_INVINCIBLE, ped, enable); }
			static void SET_CHAR_IN_CUTSCENE(Ped ped, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_IN_CUTSCENE, ped, set); }
			static void SET_CHAR_IS_TARGET_PRIORITY(Ped ped, b8 enable) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_IS_TARGET_PRIORITY, ped, enable); }
			static void SET_CHAR_KEEP_TASK(Ped ped, b8 value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_KEEP_TASK, ped, value); }
			static void SET_CHAR_MAX_HEALTH(Ped ped, unsigned int value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_MAX_HEALTH, ped, value); }
			static void SET_CHAR_MAX_TIME_IN_WATER(Ped ped, float time) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_MAX_TIME_IN_WATER, ped, time); }
			static void SET_CHAR_MAX_TIME_UNDERWATER(Ped ped, float time) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_MAX_TIME_UNDERWATER, ped, time); }
			static void SET_CHAR_MELEE_ACTION_FLAG0(Ped ped, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_MELEE_ACTION_FLAG0, ped, set); }
			static void SET_CHAR_MELEE_ACTION_FLAG1(Ped ped, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_MELEE_ACTION_FLAG1, ped, set); }
			static void SET_CHAR_MELEE_ACTION_FLAG2(Ped ped, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_MELEE_ACTION_FLAG2, ped, set); }
			static void SET_CHAR_MONEY(Ped ped, unsigned int amount) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_MONEY, ped, amount); }
			static void SET_CHAR_MOVE_ANIM_SPEED_MULTIPLIER(Ped ped, float multiplier) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_MOVE_ANIM_SPEED_MULTIPLIER, ped, multiplier); }
			static void SET_CHAR_NEVER_LEAVES_GROUP(Ped ped, b8 value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_NEVER_LEAVES_GROUP, ped, value); }
			static void SET_CHAR_NEVER_TARGETTED(Ped ped, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_NEVER_TARGETTED, ped, set); }
			static void SET_CHAR_NOT_DAMAGED_BY_RELATIONSHIP_GROUP(Ped ped, int relationshipGroup, b8 enable) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_NOT_DAMAGED_BY_RELATIONSHIP_GROUP, ped, relationshipGroup, enable); }
			static void SET_CHAR_ONLY_DAMAGED_BY_PLAYER(Ped ped, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_ONLY_DAMAGED_BY_PLAYER, ped, set); }
			static void SET_CHAR_ONLY_DAMAGED_BY_RELATIONSHIP_GROUP(Ped ped, b8 set, int relgroup) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_ONLY_DAMAGED_BY_RELATIONSHIP_GROUP, ped, set, relgroup); }
			static void SET_CHAR_PROOFS(Ped ped, b8 unknown0, b8 fallingDamage, b8 unknown1, b8 unknown2, b8 meleeDamage) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_PROOFS, ped, unknown0, fallingDamage, unknown1, unknown2, meleeDamage); }
			static void SET_CHAR_PROP_INDEX(Ped ped, unsigned int propType, unsigned int index) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_PROP_INDEX, ped, propType, index); }
			static void SET_CHAR_PROP_INDEX_TEXTURE(Ped ped, unsigned int propType, unsigned int index, unsigned int texture) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_PROP_INDEX_TEXTURE, ped, propType, index, texture); }
			static void SET_CHAR_PROVIDE_COVERING_FIRE(Ped ped, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_PROVIDE_COVERING_FIRE, ped, set); }
			static void SET_CHAR_RANDOM_COMPONENT_VARIATION(Ped ped) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_RANDOM_COMPONENT_VARIATION, ped); }
			static void SET_CHAR_READY_TO_BE_EXECUTED(Ped ped, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_READY_TO_BE_EXECUTED, ped, set); }
			static void SET_CHAR_READY_TO_BE_STUNNED(Ped ped, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_READY_TO_BE_STUNNED, ped, set); }
			static void SET_CHAR_RELATIONSHIP(Ped ped, unsigned int relationshipLevel, int relationshipGroup) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_RELATIONSHIP, ped, relationshipLevel, relationshipGroup); }
			static void SET_CHAR_RELATIONSHIP_GROUP(Ped ped, int relationshipGroup) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_RELATIONSHIP_GROUP, ped, relationshipGroup); }
			static void SET_CHAR_ROTATION(Ped ped, float xr, float yr, float zr) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_ROTATION, ped, xr, yr, zr); }
			static void SET_CHAR_SHOOT_RATE(Ped ped, int rate) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_SHOOT_RATE, ped, rate); }
			static void SET_CHAR_SIGNAL_AFTER_KILL(Ped ped, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_SIGNAL_AFTER_KILL, ped, set); }
			static void SET_CHAR_SPHERE_DEFENSIVE_AREA(Ped ped, float x, float y, float z, float radius) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_SPHERE_DEFENSIVE_AREA, ped, x, y, z, radius); }
			static void SET_CHAR_STAY_IN_CAR_WHEN_JACKED(Ped ped, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_STAY_IN_CAR_WHEN_JACKED, ped, set); }
			static void SET_CHAR_SUFFERS_CRITICAL_HITS(Ped ped, b8 value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_SUFFERS_CRITICAL_HITS, ped, value); }
			static void SET_CHAR_USES_DEAFULT_ANIM_GROUP_WHEN_FLEEING(Ped ped, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_USES_DEAFULT_ANIM_GROUP_WHEN_FLEEING, ped, set); }
			static void SET_CHAR_USES_UPPERBODY_DAMAGE_ANIMS_ONLY(Ped ped, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_USES_UPPERBODY_DAMAGE_ANIMS_ONLY, ped, set); }
			static void SET_CHAR_VELOCITY(Ped ped, float x, float y, float z) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_VELOCITY, ped, x, y, z); }
			static void SET_CHAR_VISIBLE(Ped ped, b8 value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_VISIBLE, ped, value); }
			static void SET_CHAR_WATCH_MELEE(Ped ped, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_WATCH_MELEE, ped, set); }
			static void SET_CHAR_WILL_COWER_INSTEAD_OF_FLEEING(Ped ped, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_WILL_COWER_INSTEAD_OF_FLEEING, ped, set); }
			static void SET_CHAR_WILL_DO_DRIVEBYS(Ped ped, b8 value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_WILL_DO_DRIVEBYS, ped, value); }
			static void SET_CHAR_WILL_FLY_THROUGH_WINDSCREEN(Ped ped, b8 value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_WILL_FLY_THROUGH_WINDSCREEN, ped, value); }
			static void SET_CHAR_WILL_LEAVE_CAR_IN_COMBAT(Ped ped, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_WILL_LEAVE_CAR_IN_COMBAT, ped, set); }
			static void SET_CHAR_WILL_MOVE_WHEN_INJURED(Ped ped, b8 value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_WILL_MOVE_WHEN_INJURED, ped, value); }
			static void SET_CHAR_WILL_ONLY_FIRE_WITH_CLEAR_LOS(Ped ped, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_WILL_ONLY_FIRE_WITH_CLEAR_LOS, ped, set); }
			static void SET_CHAR_WILL_REMAIN_ON_BOAT_AFTER_MISSION_ENDS(Ped ped, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_WILL_REMAIN_ON_BOAT_AFTER_MISSION_ENDS, ped, set); }
			static void SET_CHAR_WILL_USE_CARS_IN_COMBAT(Ped ped, b8 value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_WILL_USE_CARS_IN_COMBAT, ped, value); }
			static void SET_CHAR_WILL_USE_COVER(Ped ped, b8 value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_WILL_USE_COVER, ped, value); }
			static void SET_DEAD_CHAR_COORDINATES(Ped ped, float x, float y, float z) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_DEAD_CHAR_COORDINATES, ped, x, y, z); }
			static void SET_GROUP_CHAR_DUCKS_WHEN_AIMED_AT(Ped ped, b8 value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_GROUP_CHAR_DUCKS_WHEN_AIMED_AT, ped, value); }
			static void SET_LOAD_COLLISION_FOR_CHAR_FLAG(Ped ped, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_LOAD_COLLISION_FOR_CHAR_FLAG, ped, set); }
			static void SET_ROOM_FOR_CHAR_BY_KEY(Ped ped, unsigned int key) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_ROOM_FOR_CHAR_BY_KEY, ped, key); }
			static void SET_ROOM_FOR_CHAR_BY_NAME(Ped ped, String^ roomname)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_ROOM_FOR_CHAR_BY_NAME, ped, ctx.marshal_as<const char*>(roomname));
			}
			static void ADD_SCORE(Player playerIndex, int score) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ADD_SCORE, playerIndex, score); }
			static void ALLOW_LOCKON_TO_RANDOM_PEDS(int player, b8 allow) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ALLOW_LOCKON_TO_RANDOM_PEDS, player, allow); }
			static void ALLOW_PLAYER_TO_CARRY_NON_MISSION_OBJECTS(Player playerIndex, b8 allow) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ALLOW_PLAYER_TO_CARRY_NON_MISSION_OBJECTS, playerIndex, allow); }
			static void AWARD_PLAYER_MISSION_RESPECT(float respect) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_AWARD_PLAYER_MISSION_RESPECT, respect); }
			static void CHANGE_PLAYER_MODEL(Player playerIndex, unsigned int model) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_CHANGE_PLAYER_MODEL, playerIndex, model); }
			static void CHANGE_PLAYER_PHONE_MODEL(int player, unsigned int model) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_CHANGE_PLAYER_PHONE_MODEL, player, model); }
			static void CHANGE_PLAYER_PHONE_MODEL_OFFSETS(int player, float x0, float y0, float z0, float x1, float y1, float z1) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_CHANGE_PLAYER_PHONE_MODEL_OFFSETS, player, x0, y0, z0, x1, y1, z1); }
			static void CLEAR_PLAYER_HAS_DAMAGED_AT_LEAST_ONE_PED(Player playerIndex) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_CLEAR_PLAYER_HAS_DAMAGED_AT_LEAST_ONE_PED, playerIndex); }
			static void CLEAR_PLAYER_HAS_DAMAGED_AT_LEAST_ONE_VEHICLE(int player) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_CLEAR_PLAYER_HAS_DAMAGED_AT_LEAST_ONE_VEHICLE, player); }
			static void CREATE_PLAYER(unsigned int playerId, float x, float y, float z, [OutAttribute] Player% pPlayerIndex)
			{
				Player p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_CREATE_PLAYER, playerId, x, y, z, &p);
				pPlayerIndex = p;
			}
			static void DELETE_PLAYER() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DELETE_PLAYER); }
			static void DISABLE_PLAYER_LOCKON(Player playerIndex, b8 disabled) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DISABLE_PLAYER_LOCKON, playerIndex, disabled); }
			static void FAKE_DEATHARREST() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_FAKE_DEATHARREST); }
			static void FORCE_AIR_DRAG_MULT_FOR_PLAYERS_CAR(int player, float multiplier) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_FORCE_AIR_DRAG_MULT_FOR_PLAYERS_CAR, player, multiplier); }
			static void GET_NUM_OF_MODELS_KILLED_BY_PLAYER(int player, unsigned int model, [OutAttribute] int% num)
			{
				int p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_NUM_OF_MODELS_KILLED_BY_PLAYER, player, model, &p);
				num = p;
			}
			static void GET_PLAYERS_LAST_CAR_NO_SAVE([OutAttribute] Vehicle% pVehicle)
			{
				Vehicle p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_PLAYERS_LAST_CAR_NO_SAVE, &p);
				pVehicle = p;
			}
			static void GET_PLAYER_CHAR(Player playerIndex, [OutAttribute] Ped% pPed)
			{
				Ped p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_PLAYER_CHAR, playerIndex, &p);
				pPed = p;
			}
			static void GET_PLAYER_GROUP(Player playerIndex, [OutAttribute] Group% pGroup)
			{
				Group p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_PLAYER_GROUP, playerIndex, &p);
				pGroup = p;
			}
			static void GET_PLAYER_MAX_ARMOUR(Player playerIndex, [OutAttribute] unsigned int% pMaxArmour)
			{
				unsigned int p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_PLAYER_MAX_ARMOUR, playerIndex, &p);
				pMaxArmour = p;
			}
			static void GET_PLAYER_MAX_HEALTH(int player, [OutAttribute] int% maxhealth)
			{
				int p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_PLAYER_MAX_HEALTH, player, &p);
				maxhealth = p;
			}
			static void GIVE_PLAYER_RAGDOLL_CONTROL(int player, b8 give) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_GIVE_PLAYER_RAGDOLL_CONTROL, player, give); }
			static void INCREASE_PLAYER_MAX_ARMOUR(int player, float armour) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_INCREASE_PLAYER_MAX_ARMOUR, player, armour); }
			static void INCREASE_PLAYER_MAX_HEALTH(int player, int maxhealth) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_INCREASE_PLAYER_MAX_HEALTH, player, maxhealth); }
			static void LISTEN_TO_PLAYER_GROUP_COMMANDS(Ped ped, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_LISTEN_TO_PLAYER_GROUP_COMMANDS, ped, set); }
			static void MAKE_PLAYER_FIRE_PROOF(int player, b8 proof) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_MAKE_PLAYER_FIRE_PROOF, player, proof); }
			static void MAKE_PLAYER_GANG_DISAPPEAR() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_MAKE_PLAYER_GANG_DISAPPEAR); }
			static void MAKE_PLAYER_GANG_REAPPEAR() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_MAKE_PLAYER_GANG_REAPPEAR); }
			static void MAKE_PLAYER_SAFE_FOR_CUTSCENE(int player) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_MAKE_PLAYER_SAFE_FOR_CUTSCENE, player); }
			static void REGISTER_PLAYER_RESPAWN_COORDS(Player playerIndex, float x, float y, float z) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_REGISTER_PLAYER_RESPAWN_COORDS, playerIndex, x, y, z); }
			static void REMOVE_PLAYER_HELMET(Player playerIndex, b8 remove) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_REMOVE_PLAYER_HELMET, playerIndex, remove); }
			static void RESET_NUM_OF_MODELS_KILLED_BY_PLAYER(unsigned int model) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_RESET_NUM_OF_MODELS_KILLED_BY_PLAYER, model); }
			static void SET_ALL_RANDOM_PEDS_FLEE(int player, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_ALL_RANDOM_PEDS_FLEE, player, set); }
			static void SET_DONT_ACTIVATE_RAGDOLL_FROM_PLAYER_IMPACT(Ped ped, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_DONT_ACTIVATE_RAGDOLL_FROM_PLAYER_IMPACT, ped, set); }
			static void SET_DRAW_PLAYER_COMPONENT(int component, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_DRAW_PLAYER_COMPONENT, component, set); }
			static void SET_EVERYONE_IGNORE_PLAYER(Player playerIndex, b8 value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_EVERYONE_IGNORE_PLAYER, playerIndex, value); }
			static void SET_FORCE_LOOK_BEHIND(b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_FORCE_LOOK_BEHIND, set); }
			static void SET_FREE_HEALTH_CARE(int player, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_FREE_HEALTH_CARE, player, set); }
			static void SET_LOCAL_PLAYER_PAIN_VOICE(String^ name)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_LOCAL_PLAYER_PAIN_VOICE, ctx.marshal_as<const char*>(name));
			}
			static void SET_LOCAL_PLAYER_VOICE(String^ name)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_LOCAL_PLAYER_VOICE, ctx.marshal_as<const char*>(name));
			}
			static void SET_PLAYERSETTINGS_MODEL_VARIATIONS_CHOICE(Player playerIndex) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_PLAYERSETTINGS_MODEL_VARIATIONS_CHOICE, playerIndex); }
			static void SET_PLAYER_CAN_BE_HASSLED_BY_GANGS(Player playerIndex, b8 value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_PLAYER_CAN_BE_HASSLED_BY_GANGS, playerIndex, value); }
			static void SET_PLAYER_CAN_DO_DRIVE_BY(Player playerIndex, b8 value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_PLAYER_CAN_DO_DRIVE_BY, playerIndex, value); }
			static void SET_PLAYER_CAN_DROP_WEAPONS_IN_CAR(b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_PLAYER_CAN_DROP_WEAPONS_IN_CAR, set); }
			static void SET_PLAYER_CAN_USE_COVER(Player playerIndex, b8 value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_PLAYER_CAN_USE_COVER, playerIndex, value); }
			static void SET_PLAYER_CONTROL(Player playerIndex, b8 value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_PLAYER_CONTROL, playerIndex, value); }
			static void SET_PLAYER_CONTROL_ADVANCED(Player playerIndex, b8 unknown1, b8 unknown2, b8 unknown3) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_PLAYER_CONTROL_ADVANCED, playerIndex, unknown1, unknown2, unknown3); }
			static void SET_PLAYER_CONTROL_FOR_AMBIENT_SCRIPT(int player, b8 flag0, b8 flag1) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_PLAYER_CONTROL_FOR_AMBIENT_SCRIPT, player, flag0, flag1); }
			static void SET_PLAYER_CONTROL_FOR_TEXT_CHAT(int player, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_PLAYER_CONTROL_FOR_TEXT_CHAT, player, set); }
			static void SET_PLAYER_CONTROL_ON_IN_MISSION_CLEANUP(b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_PLAYER_CONTROL_ON_IN_MISSION_CLEANUP, set); }
			static void SET_PLAYER_FAST_RELOAD(Player playerIndex, b8 value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_PLAYER_FAST_RELOAD, playerIndex, value); }
			static void SET_PLAYER_GROUP_RECRUITMENT(int player, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_PLAYER_GROUP_RECRUITMENT, player, set); }
			static void SET_PLAYER_GROUP_TO_FOLLOW_ALWAYS(Player playerIndex, b8 value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_PLAYER_GROUP_TO_FOLLOW_ALWAYS, playerIndex, value); }
			static void SET_PLAYER_GROUP_TO_FOLLOW_NEVER(int player, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_PLAYER_GROUP_TO_FOLLOW_NEVER, player, set); }
			static void SET_PLAYER_ICON_COLOUR(int colour) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_PLAYER_ICON_COLOUR, colour); }
			static void SET_PLAYER_INVINCIBLE(Player playerIndex, b8 value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_PLAYER_INVINCIBLE, playerIndex, value); }
			static void SET_PLAYER_INVISIBLE_TO_AI(b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_PLAYER_INVISIBLE_TO_AI, set); }
			static void SET_PLAYER_IS_IN_STADIUM(b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_PLAYER_IS_IN_STADIUM, set); }
			static void SET_PLAYER_KEEPS_WEAPONS_WHEN_RESPAWNED(b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_PLAYER_KEEPS_WEAPONS_WHEN_RESPAWNED, set); }
			static void SET_PLAYER_MAY_ONLY_ENTER_THIS_VEHICLE(int player, Vehicle veh) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_PLAYER_MAY_ONLY_ENTER_THIS_VEHICLE, player, veh); }
			static void SET_PLAYER_MOOD_NORMAL(Player playerIndex) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_PLAYER_MOOD_NORMAL, playerIndex); }
			static void SET_PLAYER_MOOD_PISSED_OFF(Player playerIndex, unsigned int unknown150) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_PLAYER_MOOD_PISSED_OFF, playerIndex, unknown150); }
			static void SET_PLAYER_NEVER_GETS_TIRED(Player playerIndex, b8 value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_PLAYER_NEVER_GETS_TIRED, playerIndex, value); }
			static void SET_PLAYER_PAIN_ROOT_BANK_NAME(String^ name)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_PLAYER_PAIN_ROOT_BANK_NAME, ctx.marshal_as<const char*>(name));
			}
			static void SET_PLAYER_PLAYER_TARGETTING(b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_PLAYER_PLAYER_TARGETTING, set); }
			static void SET_USE_LEG_IK(int player, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_USE_LEG_IK, player, set); }
			static void STORE_SCORE(Player playerIndex, [OutAttribute] unsigned int% value)
			{
				unsigned int p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_STORE_SCORE, playerIndex, &p);
				value = p;
			}
			static void ALLOW_LOCKON_TO_FRIENDLY_PLAYERS(int player, b8 allow) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ALLOW_LOCKON_TO_FRIENDLY_PLAYERS, player, allow); }
			static void ADD_PED_TO_CINEMATOGRAPHY_AI(int Unk28, Ped ped) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ADD_PED_TO_CINEMATOGRAPHY_AI, Unk28, ped); }
			static void ADD_PED_TO_MISSION_DELETION_LIST(Ped ped, b8 Unk29) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ADD_PED_TO_MISSION_DELETION_LIST, ped, Unk29); }
			static void ALLOW_TARGET_WHEN_INJURED(Ped ped, b8 allow) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ALLOW_TARGET_WHEN_INJURED, ped, allow); }
			static void ALWAYS_USE_HEAD_ON_HORN_ANIM_WHEN_DEAD_IN_CAR(Ped ped, b8 use) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ALWAYS_USE_HEAD_ON_HORN_ANIM_WHEN_DEAD_IN_CAR, ped, use); }
			static void APPLY_FORCE_TO_PED(Ped ped, unsigned int unknown0_3, float x, float y, float z, float spinX, float spinY, float spinZ, unsigned int unknown4_0, unsigned int unknown5_1, unsigned int unknown6_1, unsigned int unknown7_1) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_APPLY_FORCE_TO_PED, ped, unknown0_3, x, y, z, spinX, spinY, spinZ, unknown4_0, unknown5_1, unknown6_1, unknown7_1); }
			static void ATTACH_PED_TO_CAR_PHYSICALLY(Ped ped, Vehicle car, int pedbone, float x, float y, float z, float angle, float Unk30, b8 Unk31, b8 Unk32) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ATTACH_PED_TO_CAR_PHYSICALLY, ped, car, pedbone, x, y, z, angle, Unk30, Unk31, Unk32); }
			static void ATTACH_PED_TO_OBJECT(Ped ped, Entity obj, int pedbone, float x, float y, float z, float angle, float Unk33, b8 Unk34, b8 Unk35) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ATTACH_PED_TO_OBJECT, ped, obj, pedbone, x, y, z, angle, Unk33, Unk34, Unk35); }
			static void ATTACH_PED_TO_OBJECT_PHYSICALLY(Ped ped, Entity obj, int pedbone, float x, float y, float z, float angle, float Unk36, b8 Unk37, b8 Unk38) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ATTACH_PED_TO_OBJECT_PHYSICALLY, ped, obj, pedbone, x, y, z, angle, Unk36, Unk37, Unk38); }
			static void ATTACH_PED_TO_SHIMMY_EDGE(Ped ped, float x, float y, float z, float Unk39) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ATTACH_PED_TO_SHIMMY_EDGE, ped, x, y, z, Unk39); }
			static void CLOSE_MIC_PED(int id, Ped ped) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_CLOSE_MIC_PED, id, ped); }
			static void COPY_ANIMATIONS(Ped ped, Ped pednext, float speed) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_COPY_ANIMATIONS, ped, pednext, speed); }
			static void CREATE_GROUP(b8 unknownFalse, [OutAttribute] Group% pGroup, b8 unknownTrue)
			{
				Group p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_CREATE_GROUP, unknownFalse, &p, unknownTrue);
				pGroup = p;
			}
			static void CREATE_NM_MESSAGE(b8 Unk40, int id) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_CREATE_NM_MESSAGE, Unk40, id); }
			static void DAMAGE_PED_BODY_PART(Ped ped, unsigned int part, unsigned int hitPoints) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DAMAGE_PED_BODY_PART, ped, part, hitPoints); }
			static void DETACH_PED(Ped ped, b8 unknown) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DETACH_PED, ped, unknown); }
			static void DONT_SUPPRESS_ANY_PED_MODELS() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DONT_SUPPRESS_ANY_PED_MODELS); }
			static void DONT_SUPPRESS_PED_MODEL(unsigned int model) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DONT_SUPPRESS_PED_MODEL, model); }
			static void ENABLE_ALL_PED_HELMETS(b8 enable) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ENABLE_ALL_PED_HELMETS, enable); }
			static void ENABLE_PED_HELMET(Ped ped, b8 enable) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ENABLE_PED_HELMET, ped, enable); }
			static void FORCE_FULL_VOICE(Ped ped) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_FORCE_FULL_VOICE, ped); }
			static void FORCE_PED_PINNED_DOWN(Ped ped, b8 force, unsigned int timerMaybe) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_FORCE_PED_PINNED_DOWN, ped, force, timerMaybe); }
			static void FORCE_PED_TO_FLEE_WHILST_DRIVING_VEHICLE(Ped ped, Vehicle vehicle) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_FORCE_PED_TO_FLEE_WHILST_DRIVING_VEHICLE, ped, vehicle); }
			static void FORCE_PED_TO_LOAD_COVER(Ped ped, b8 force) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_FORCE_PED_TO_LOAD_COVER, ped, force); }
			static void FORCE_RANDOM_PED_TYPE(unsigned int type) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_FORCE_RANDOM_PED_TYPE, type); }
			static void FORCE_SPAWN_SCENARIO_PEDS_IN_AREA(float x, float y, float z, float radius, int Unk41) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_FORCE_SPAWN_SCENARIO_PEDS_IN_AREA, x, y, z, radius, Unk41); }
			static void GET_CUTSCENE_PED_POSITION(int unkped, [OutAttribute] Vector3% pos)
			{
				Vector3 v;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_CUTSCENE_PED_POSITION, unkped, &v);
				pos = v;
			}
			static void GET_DRIVER_OF_CAR(Vehicle vehicle, [OutAttribute] Ped% pPed)
			{
				Ped p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_DRIVER_OF_CAR, vehicle, &p);
				pPed = p;
			}
			static void GET_GROUP_FORMATION(int group, [OutAttribute] int% formation)
			{
				int p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_GROUP_FORMATION, group, &p);
				formation = p;
			}
			static void GET_GROUP_FORMATION_SPACING(int group, [OutAttribute] float% spacing)
			{
				float p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_GROUP_FORMATION_SPACING, group, &p);
				spacing = p;
			}
			static void GET_GROUP_LEADER(Group group, [OutAttribute] Ped% pPed)
			{
				Ped p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_GROUP_LEADER, group, &p);
				pPed = p;
			}
			static void GET_GROUP_MEMBER(Group group, unsigned int index, [OutAttribute] Ped% pPed)
			{
				Ped p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_GROUP_MEMBER, group, index, &p);
				pPed = p;
			}
			static void GET_GROUP_SIZE(Group group, [OutAttribute] unsigned int% pStartIndex, [OutAttribute] unsigned int% pCount)
			{
				unsigned int index, count;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_GROUP_SIZE, group, &index, &count);
				pStartIndex = index;
				pCount = count;
			}
			static void GET_NTH_GROUP_MEMBER(int group, int n, [OutAttribute] Ped% ped)
			{
				Ped p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_NTH_GROUP_MEMBER, group, n, &p);
				ped = p;
			}
			static void GET_NUMBER_OF_FOLLOWERS(Ped ped, [OutAttribute] int% followers)
			{
				int p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_NUMBER_OF_FOLLOWERS, ped, &p);
				followers = p;
			}
			static void GET_PED_BONE_POSITION(Ped ped, unsigned int bone, float x, float y, float z, [OutAttribute] Vector3% pPosition)
			{
				Vector3 p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_PED_BONE_POSITION, ped, bone, x, y, z, &p);
				pPosition = p;
			}
			static void GET_PED_GROUP_INDEX(Ped ped, [OutAttribute] unsigned int% pIndex)
			{
				unsigned int p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_PED_GROUP_INDEX, ped, &p);
				pIndex = p;
			}
			static void GET_PED_TYPE(Ped ped, [OutAttribute] unsigned int% pType)
			{
				unsigned int p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_PED_TYPE, ped, &p);
				pType = p;
			}
			static void GET_SCRIPT_TASK_STATUS(Ped ped, int task, [OutAttribute] int% status)
			{
				int p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_SCRIPT_TASK_STATUS, ped, task, &p);
				status = p;
			}
			static void GIVE_PED_AMBIENT_OBJECT(Ped ped, unsigned int model) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_GIVE_PED_AMBIENT_OBJECT, ped, model); }
			static void GIVE_PED_FAKE_NETWORK_NAME(Ped ped, String^ name, int r, int g, int b, int a)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GIVE_PED_FAKE_NETWORK_NAME, ped, ctx.marshal_as<const char*>(name), r, g, b, a);
			}
			static void GIVE_PED_HELMET(Ped ped) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_GIVE_PED_HELMET, ped); }
			static void GIVE_PED_HELMET_WITH_OPTS(Ped ped, b8 Unk42) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_GIVE_PED_HELMET_WITH_OPTS, ped, Unk42); }
			static void GIVE_PED_PICKUP_OBJECT(Ped ped, Entity obj, b8 flag) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_GIVE_PED_PICKUP_OBJECT, ped, obj, flag); }
			static void KNOCK_PED_OFF_BIKE(Vehicle vehicle) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_KNOCK_PED_OFF_BIKE, vehicle); }
			static void PED_QUEUE_CONSIDER_PEDS_WITH_FLAG_FALSE(int flagid) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_PED_QUEUE_CONSIDER_PEDS_WITH_FLAG_FALSE, flagid); }
			static void PED_QUEUE_CONSIDER_PEDS_WITH_FLAG_TRUE(int flagid) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_PED_QUEUE_CONSIDER_PEDS_WITH_FLAG_TRUE, flagid); }
			static void PED_QUEUE_REJECT_PEDS_WITH_FLAG_FALSE(int flagid) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_PED_QUEUE_REJECT_PEDS_WITH_FLAG_FALSE, flagid); }
			static void PED_QUEUE_REJECT_PEDS_WITH_FLAG_TRUE(int flagid) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_PED_QUEUE_REJECT_PEDS_WITH_FLAG_TRUE, flagid); }
			static void REGISTER_HATED_TARGETS_AROUND_PED(Ped ped, float radius) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_REGISTER_HATED_TARGETS_AROUND_PED, ped, radius); }
			static void REGISTER_HATED_TARGETS_IN_AREA(Ped ped, float x, float y, float z, float radius) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_REGISTER_HATED_TARGETS_IN_AREA, ped, x, y, z, radius); }
			static void REGISTER_TARGET(Ped ped, Ped target) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_REGISTER_TARGET, ped, target); }
			static void REMOVE_CLOSE_MIC_PED(Ped ped) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_REMOVE_CLOSE_MIC_PED, ped); }
			static void REMOVE_FAKE_NETWORK_NAME_FROM_PED(Ped ped) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_REMOVE_FAKE_NETWORK_NAME_FROM_PED, ped); }
			static void REMOVE_GROUP(Group group) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_REMOVE_GROUP, group); }
			static void REMOVE_PED_HELMET(Ped ped, b8 removed) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_REMOVE_PED_HELMET, ped, removed); }
			static void RESET_VISIBLE_PED_DAMAGE(Ped ped) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_RESET_VISIBLE_PED_DAMAGE, ped); }
			static void REVIVE_INJURED_PED(Ped ped) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_REVIVE_INJURED_PED, ped); }
			static void SEARCH_CRITERIA_CONSIDER_PEDS_WITH_FLAG_FALSE(int flagid) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SEARCH_CRITERIA_CONSIDER_PEDS_WITH_FLAG_FALSE, flagid); }
			static void SEARCH_CRITERIA_CONSIDER_PEDS_WITH_FLAG_TRUE(unsigned int flagId) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SEARCH_CRITERIA_CONSIDER_PEDS_WITH_FLAG_TRUE, flagId); }
			static void SEARCH_CRITERIA_REJECT_PEDS_WITH_FLAG_FALSE(int flagid) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SEARCH_CRITERIA_REJECT_PEDS_WITH_FLAG_FALSE, flagid); }
			static void SEARCH_CRITERIA_REJECT_PEDS_WITH_FLAG_TRUE(unsigned int flagId) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SEARCH_CRITERIA_REJECT_PEDS_WITH_FLAG_TRUE, flagId); }
			static void SEND_NM_MESSAGE(Ped ped) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SEND_NM_MESSAGE, ped); }
			static void SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(Ped ped, b8 value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_BLOCKING_OF_NON_TEMPORARY_EVENTS, ped, value); }
			static void SET_BRIANS_MOOD(int mood) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_BRIANS_MOOD, mood); }
			static void SET_COLLIDE_WITH_PEDS(b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_COLLIDE_WITH_PEDS, set); }
			static void SET_DEAD_PEDS_DROP_WEAPONS(b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_DEAD_PEDS_DROP_WEAPONS, set); }
			static void SET_DEATH_WEAPONS_PERSIST(Ped ped, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_DEATH_WEAPONS_PERSIST, ped, set); }
			static void SET_GROUP_FOLLOW_STATUS(Group group, unsigned int status) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_GROUP_FOLLOW_STATUS, group, status); }
			static void SET_GROUP_FORMATION(Group group, unsigned int formation) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_GROUP_FORMATION, group, formation); }
			static void SET_GROUP_FORMATION_SPACING(Group group, float space) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_GROUP_FORMATION_SPACING, group, space); }
			static void SET_GROUP_LEADER(Group group, Ped leader) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_GROUP_LEADER, group, leader); }
			static void SET_GROUP_MEMBER(Group group, Ped member) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_GROUP_MEMBER, group, member); }
			static void SET_GROUP_SEPARATION_RANGE(Group group, float seperation) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_GROUP_SEPARATION_RANGE, group, seperation); }
			static void SET_HEADING_LIMIT_FOR_ATTACHED_PED(Ped ped, float heading0, float heading1) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_HEADING_LIMIT_FOR_ATTACHED_PED, ped, heading0, heading1); }
			static void SET_IGNORE_LOW_PRIORITY_SHOCKING_EVENTS(Ped ped, b8 value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_IGNORE_LOW_PRIORITY_SHOCKING_EVENTS, ped, value); }
			static void SET_INFORM_RESPECTED_FRIENDS(Ped ped, int Unk43, int Unk44) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_INFORM_RESPECTED_FRIENDS, ped, Unk43, Unk44); }
			static void SET_MONEY_CARRIED_BY_ALL_NEW_PEDS(int money) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_MONEY_CARRIED_BY_ALL_NEW_PEDS, money); }
			static void SET_NM_ANIM_POSE(Ped ped, String^ AnimName0, String^ AnimName1, float pose)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_NM_ANIM_POSE, ped, ctx.marshal_as<const char*>(AnimName0), ctx.marshal_as<const char*>(AnimName1), pose);
			}
			static void SET_NM_MESSAGE_BOOL(int id, b8 value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_NM_MESSAGE_BOOL, id, value); }
			static void SET_NM_MESSAGE_FLOAT(int id, float value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_NM_MESSAGE_FLOAT, id, value); }
			static void SET_NM_MESSAGE_INSTANCE_INDEX(int id, Ped ped, Vehicle car, Entity obj) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_NM_MESSAGE_INSTANCE_INDEX, id, ped, car, obj); }
			static void SET_NM_MESSAGE_INT(int id, int value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_NM_MESSAGE_INT, id, value); }
			static void SET_NM_MESSAGE_STRING(int id, String^ string)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_NM_MESSAGE_STRING, id, ctx.marshal_as<const char*>(string));
			}
			static void SET_NM_MESSAGE_VEC3(int id, float x, float y, float z) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_NM_MESSAGE_VEC3, id, x, y, z); }
			static void SET_PED_ALLOW_MISSION_ONLY_DRIVEBY_USE(Ped ped, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_PED_ALLOW_MISSION_ONLY_DRIVEBY_USE, ped, set); }
			static void SET_PED_ALPHA(Ped ped, int alpha) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_PED_ALPHA, ped, alpha); }
			static void SET_PED_DENSITY_MULTIPLIER(float density) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_PED_DENSITY_MULTIPLIER, density); }
			static void SET_PED_DIES_WHEN_INJURED(Ped ped, b8 value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_PED_DIES_WHEN_INJURED, ped, value); }
			static void SET_PED_DONT_DO_EVASIVE_DIVES(Ped ped, b8 value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_PED_DONT_DO_EVASIVE_DIVES, ped, value); }
			static void SET_PED_DONT_USE_VEHICLE_SPECIFIC_ANIMS(Ped ped, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_PED_DONT_USE_VEHICLE_SPECIFIC_ANIMS, ped, set); }
			static void SET_PED_ENABLE_LEG_IK(Ped ped, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_PED_ENABLE_LEG_IK, ped, set); }
			static void SET_PED_FALL_OFF_BIKES_WHEN_SHOT(Ped ped, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_PED_FALL_OFF_BIKES_WHEN_SHOT, ped, set); }
			static void SET_PED_FORCE_FLY_THROUGH_WINDSCREEN(Ped ped, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_PED_FORCE_FLY_THROUGH_WINDSCREEN, ped, set); }
			static void SET_PED_GENERATES_DEAD_BODY_EVENTS(Ped ped, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_PED_GENERATES_DEAD_BODY_EVENTS, ped, set); }
			static void SET_PED_HEEDS_THE_EVERYONE_IGNORE_PLAYER_FLAG(Ped ped, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_PED_HEEDS_THE_EVERYONE_IGNORE_PLAYER_FLAG, ped, set); }
			static void SET_PED_HELMET_TEXTURE_INDEX(Ped ped, int index) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_PED_HELMET_TEXTURE_INDEX, ped, index); }
			static void SET_PED_IS_BLIND_RAGING(Ped ped, b8 value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_PED_IS_BLIND_RAGING, ped, value); }
			static void SET_PED_IS_DRUNK(Ped ped, b8 value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_PED_IS_DRUNK, ped, value); }
			static void SET_PED_MOBILE_RING_TYPE(Ped ped, int RingtoneId) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_PED_MOBILE_RING_TYPE, ped, RingtoneId); }
			static void SET_PED_NON_CREATION_AREA(float x0, float y0, float z0, float x1, float y1, float z1) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_PED_NON_CREATION_AREA, x0, y0, z0, x1, y1, z1); }
			static void SET_PED_NON_REMOVAL_AREA(float x0, float y0, float z0, float x1, float y1, float z1) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_PED_NON_REMOVAL_AREA, x0, y0, z0, x1, y1, z1); }
			static void SET_PED_PATH_MAY_DROP_FROM_HEIGHT(Ped ped, b8 value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_PED_PATH_MAY_DROP_FROM_HEIGHT, ped, value); }
			static void SET_PED_PATH_MAY_USE_CLIMBOVERS(Ped ped, b8 value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_PED_PATH_MAY_USE_CLIMBOVERS, ped, value); }
			static void SET_PED_PATH_MAY_USE_LADDERS(Ped ped, b8 value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_PED_PATH_MAY_USE_LADDERS, ped, value); }
			static void SET_PED_PATH_WILL_AVOID_DYNAMIC_OBJECTS(Ped ped, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_PED_PATH_WILL_AVOID_DYNAMIC_OBJECTS, ped, set); }
			static void SET_PED_WITH_BRAIN_CAN_BE_CONVERTED_TO_DUMMY_PED(Ped ped, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_PED_WITH_BRAIN_CAN_BE_CONVERTED_TO_DUMMY_PED, ped, set); }
			static void SET_REDUCE_PED_MODEL_BUDGET(b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_REDUCE_PED_MODEL_BUDGET, set); }
			static void SET_RELATIONSHIP(unsigned int relationshipLevel, int relationshipGroup1, int relationshipGroup2) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_RELATIONSHIP, relationshipLevel, relationshipGroup1, relationshipGroup2); }
			static void SET_ROMANS_MOOD(int moood) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_ROMANS_MOOD, moood); }
			static void SET_ROTATION_FOR_ATTACHED_PED(Ped ped, float xr, float yr, float zr) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_ROTATION_FOR_ATTACHED_PED, ped, xr, yr, zr); }
			static void SET_SCENARIO_PED_DENSITY_MULTIPLIER(float density, float densitynext) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_SCENARIO_PED_DENSITY_MULTIPLIER, density, densitynext); }
			static void SET_SCRIPTED_ANIM_SEAT_OFFSET(Ped ped, float offset) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_SCRIPTED_ANIM_SEAT_OFFSET, ped, offset); }
			static void SET_SENSE_RANGE(Ped ped, float value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_SENSE_RANGE, ped, value); }
			static void SET_SPECIFIC_PASSENGER_INDEX_TO_USE_IN_GROUPS(Ped ped, int index) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_SPECIFIC_PASSENGER_INDEX_TO_USE_IN_GROUPS, ped, index); }
			static void SET_SWIM_SPEED(Ped ped, float speed) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_SWIM_SPEED, ped, speed); }
			static void STOP_PED_DOING_FALL_OFF_TESTS_WHEN_SHOT(Ped ped) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_STOP_PED_DOING_FALL_OFF_TESTS_WHEN_SHOT, ped); }
			static void STOP_PED_MOBILE_RINGING(Ped ped) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_STOP_PED_MOBILE_RINGING, ped); }
			static void STOP_PED_SPEAKING(Ped ped, b8 stopspeaking) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_STOP_PED_SPEAKING, ped, stopspeaking); }
			static void STOP_PED_WEAPON_FIRING_WHEN_DROPPED(Ped ped) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_STOP_PED_WEAPON_FIRING_WHEN_DROPPED, ped); }
			static void SUPPRESS_PED_MODEL(unsigned int model) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SUPPRESS_PED_MODEL, model); }
			static void SWITCH_PED_TO_ANIMATED(Ped ped, b8 unknownTrue) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SWITCH_PED_TO_ANIMATED, ped, unknownTrue); }
			static void UNLOCK_RAGDOLL(Ped ped, b8 value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_UNLOCK_RAGDOLL, ped, value); }
			static void UPDATE_PED_PHYSICAL_ATTACHMENT_POSITION(Ped ped, float x0, float y0, float z0, float x1, float y1) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_UPDATE_PED_PHYSICAL_ATTACHMENT_POSITION, ped, x0, y0, z0, x1, y1); }
			static void ACTIVATE_HELI_SPEED_CHEAT(Vehicle heli, int cheat) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ACTIVATE_HELI_SPEED_CHEAT, heli, cheat); }//10
			static void ADD_CAR_TO_MISSION_DELETION_LIST(Vehicle car) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ADD_CAR_TO_MISSION_DELETION_LIST, car); }
			static void ADD_STUCK_CAR_CHECK(Vehicle car, float stuckdif, int timeout) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ADD_STUCK_CAR_CHECK, car, stuckdif, timeout); }
			static void ADD_STUCK_CAR_CHECK_WITH_WARP(Vehicle car, float stuckdif, int time, b8 flag0, b8 flag1, b8 flag2, b8 flag3) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ADD_STUCK_CAR_CHECK_WITH_WARP, car, stuckdif, time, flag0, flag1, flag2, flag3); }
			static void ADD_UPSIDEDOWN_CAR_CHECK(Vehicle vehicle) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ADD_UPSIDEDOWN_CAR_CHECK, vehicle); }
			static void ANCHOR_BOAT(Vehicle boat, b8 anchor) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ANCHOR_BOAT, boat, anchor); }
			static void APPLY_FORCE_TO_CAR(Vehicle vehicle, unsigned int unknown0_3, float x, float y, float z, float spinX, float spinY, float spinZ, unsigned int unknown4_0, unsigned int unknown5_1, unsigned int unknown6_1, unsigned int unknown7_1) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_APPLY_FORCE_TO_CAR, vehicle, unknown0_3, x, y, z, spinX, spinY, spinZ, unknown4_0, unknown5_1, unknown6_1, unknown7_1); }
			static void ATTACH_CAR_TO_CAR(Vehicle car0, Vehicle car1, int Unk51, float x0, float y0, float z0, float x1, float y1, float z1) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ATTACH_CAR_TO_CAR, car0, car1, Unk51, x0, y0, z0, x1, y1, z1); }
			static void ATTACH_CAR_TO_CAR_PHYSICALLY(int vehid1, int vehid2, b8 Unk52, int Unk53, float xoffset, float yoffset, float zoffset, float xbuffer, float ybuffer, float zbuffer, float xrotateveh1, float yrotateveh1, float Unk54, float Unk55, float Unk56) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ATTACH_CAR_TO_CAR_PHYSICALLY, vehid1, vehid2, Unk52, Unk53, xoffset, yoffset, zoffset, xbuffer, ybuffer, zbuffer, xrotateveh1, yrotateveh1, Unk54, Unk55, Unk56); }
			static void ATTACH_CAR_TO_OBJECT(Vehicle car, Entity obj, float Unk57, float Unk58, float Unk59, float Unk60, float Unk61, float Unk62, float Unk63) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ATTACH_CAR_TO_OBJECT, car, obj, Unk57, Unk58, Unk59, Unk60, Unk61, Unk62, Unk63); }
			static void ATTACH_PED_TO_CAR(Ped ped, Vehicle vehicle, unsigned int unknown0_0, float offsetX, float offsetY, float offsetZ, float rotX, float rotY, float rotZ, b8 Unk65) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ATTACH_PED_TO_CAR, ped, vehicle, unknown0_0, offsetX, offsetY, offsetZ, rotX, rotY, rotZ, Unk65); }
			static void BREAK_CAR_DOOR(Vehicle vehicle, unsigned int door, b8 deleteDoorProp) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_BREAK_CAR_DOOR, vehicle, door, deleteDoorProp); }
			static void BURST_CAR_TYRE(Vehicle vehicle, unsigned int tyre) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_BURST_CAR_TYRE, vehicle, tyre); }
			static void CHANGE_CAR_COLOUR(Vehicle vehicle, ColourIndex colour1, ColourIndex colour2) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_CHANGE_CAR_COLOUR, vehicle, colour1, colour2); }
			static void CHANGE_PLAYBACK_TO_USE_AI(Vehicle car) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_CHANGE_PLAYBACK_TO_USE_AI, car); }
			static void CLEAR_CAR_LAST_DAMAGE_ENTITY(Vehicle vehicle) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_CLEAR_CAR_LAST_DAMAGE_ENTITY, vehicle); }
			static void CLEAR_CAR_LAST_WEAPON_DAMAGE(Vehicle vehicle) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_CLEAR_CAR_LAST_WEAPON_DAMAGE, vehicle); }
			static void CLEAR_ROOM_FOR_CAR(Vehicle vehicle) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_CLEAR_ROOM_FOR_CAR, vehicle); }
			static void CLOSE_ALL_CAR_DOORS(Vehicle vehicle) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_CLOSE_ALL_CAR_DOORS, vehicle); }
			static void CONTROL_CAR_DOOR(Vehicle vehicle, unsigned int door, unsigned int unknown_maybe_open, float angle) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_CONTROL_CAR_DOOR, vehicle, door, unknown_maybe_open, angle); }
			static void CREATE_CAR(int nameHash, Vector3 pos, [OutAttribute] Vehicle% pVehicle, b8 unknownTrue)
			{
				Vehicle v;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_CREATE_CAR, nameHash, pos.X, pos.Y, pos.Z, &v, unknownTrue);
				pVehicle = v;
			}
			static void CREATE_CAR(int nameHash, float x, float y, float z, [OutAttribute] Vehicle% pVehicle, b8 unknownTrue)
			{
				Vehicle v;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_CREATE_CAR, nameHash, x, y, z, &v, unknownTrue);
				pVehicle = v;
			}
			static void CREATE_CARS_ON_GENERATORS_IN_AREA(float x0, float y0, float z0, float x1, float y1, float z1) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_CREATE_CARS_ON_GENERATORS_IN_AREA, x0, y0, z0, x1, y1, z1); }
			static void CREATE_CAR_GENERATOR(float x, float y, float z, float yaw, float pitch, float roll, unsigned int model, unsigned int color1, unsigned int color2, unsigned int spec1, unsigned int spec2, int Unk66, b8 alarm, b8 doorlock, int* handle) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_CREATE_CAR_GENERATOR, x, y, z, yaw, pitch, roll, model, color1, color2, spec1, spec2, Unk66, alarm, doorlock, handle); }
			static void CREATE_MISSION_TRAIN(unsigned int unknown1, float x, float y, float z, b8 unknown2, [OutAttribute] Train% pTrain)
			{
				Train p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_CREATE_MISSION_TRAIN, unknown1, x, y, z, unknown2, &p);
				pTrain = p;
			}
			static void CREATE_RANDOM_CAR_FOR_CAR_PARK(float x, float y, float z, float radius) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_CREATE_RANDOM_CAR_FOR_CAR_PARK, x, y, z, radius); }
			static void CREATE_RANDOM_CHAR_AS_DRIVER(Vehicle vehicle, [OutAttribute] Ped% pPed)
			{
				Ped p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_CREATE_RANDOM_CHAR_AS_DRIVER, vehicle, &p);
				pPed = p;
			}
			static void DAMAGE_CAR(Vehicle car, float x, float y, float z, float unkforce0, float unkforce1, b8 flag) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DAMAGE_CAR, car, x, y, z, unkforce0, unkforce1, flag); }
			static void DELETE_ALL_TRAINS() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DELETE_ALL_TRAINS); }
			
			[System::ObsoleteAttribute("This native is obsolete. Use CPools.DeleteCar instead.")]
			static void DELETE_CAR(Vehicle* pVehicle)
			{
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_DELETE_CAR, pVehicle);
			}

			static void DELETE_CAR_GENERATOR(int handle) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DELETE_CAR_GENERATOR, handle); }
			static void DELETE_MISSION_TRAIN(Train% pTrain) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DELETE_MISSION_TRAIN, pTrain); }
			static void DELETE_MISSION_TRAINS() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DELETE_MISSION_TRAINS); }
			static void DETACH_CAR(Vehicle vehicle) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DETACH_CAR, vehicle); }
			static void DISABLE_CAR_GENERATORS(b8 flag0, b8 flag1) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DISABLE_CAR_GENERATORS, flag0, flag1); }
			static void DISABLE_CAR_GENERATORS_WITH_HELI(b8 disable) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DISABLE_CAR_GENERATORS_WITH_HELI, disable); }
			static void DONT_SUPPRESS_ANY_CAR_MODELS() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DONT_SUPPRESS_ANY_CAR_MODELS); }
			static void DONT_SUPPRESS_CAR_MODEL(unsigned int model) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DONT_SUPPRESS_CAR_MODEL, model); }
			static void ENABLE_GPS_IN_VEHICLE(Vehicle veh, b8 enable) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ENABLE_GPS_IN_VEHICLE, veh, enable); }
			static void FIX_CAR(Vehicle vehicle) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_FIX_CAR, vehicle); }
			static void FIX_CAR_TYRE(Vehicle vehicle, unsigned int tyre) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_FIX_CAR_TYRE, vehicle, tyre); }
			static void FORCE_ALL_VEHICLE_LIGHTS_OFF(b8 off) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_FORCE_ALL_VEHICLE_LIGHTS_OFF, off); }
			static void FORCE_CAR_LIGHTS(Vehicle car, int lights) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_FORCE_CAR_LIGHTS, car, lights); }
			static void FORCE_GENERATE_PARKED_CARS_TOO_CLOSE_TO_OTHERS(b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_FORCE_GENERATE_PARKED_CARS_TOO_CLOSE_TO_OTHERS, set); }
			static void FORCE_RANDOM_CAR_MODEL(unsigned int hash) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_FORCE_RANDOM_CAR_MODEL, hash); }
			static void FREEZE_CAR_POSITION(Vehicle vehicle, b8 frozen) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_FREEZE_CAR_POSITION, vehicle, frozen); }
			static void FREEZE_CAR_POSITION_AND_DONT_LOAD_COLLISION(Vehicle vehicle, b8 frozen) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_FREEZE_CAR_POSITION_AND_DONT_LOAD_COLLISION, vehicle, frozen); }
			static void GET_CAR_ANIM_CURRENT_TIME(Vehicle car, String^ animname0, String^ animname1, [OutAttribute] float% time)
			{
				msclr::interop::marshal_context ctx;
				float p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_CAR_ANIM_CURRENT_TIME, car, ctx.marshal_as<const char*>(animname0), ctx.marshal_as<const char*>(animname1), &p);
				time = p;
			}
			static void GET_CAR_ANIM_TOTAL_TIME(Vehicle car, String^ animname0, String^ animname1, [OutAttribute] float% time)
			{
				msclr::interop::marshal_context ctx;
				float p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_CAR_ANIM_TOTAL_TIME, car, ctx.marshal_as<const char*>(animname0), ctx.marshal_as<const char*>(animname1), &p);
				time = p;
			}
			static void GET_CAR_BLOCKING_CAR(Vehicle car0, [OutAttribute] Vehicle% car1)
			{
				Vehicle p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_CAR_BLOCKING_CAR, car0, &p);
				car1 = p;
			}
			static void GET_CAR_CHAR_IS_USING(Ped ped, [OutAttribute] Vehicle% pVehicle)
			{
				Vehicle p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_CAR_CHAR_IS_USING, ped, &p);
				pVehicle = p;
			}
			static void GET_CAR_COLOURS(Vehicle vehicle, [OutAttribute] ColourIndex% pColour1, [OutAttribute] ColourIndex% pColour2)
			{
				ColourIndex p1, p2;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_CAR_COLOURS, vehicle, &p1, &p2);
				pColour1 = p1;
				pColour2 = p2;
			}
			static void GET_CAR_COORDINATES(Vehicle vehicle, [OutAttribute] Vector3% pos)
			{
				float x, y, z;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_CAR_COORDINATES, vehicle, &x, &y, &z);
				pos = Vector3(x, y, z);
			}
			static void GET_CAR_COORDINATES(Vehicle vehicle, [OutAttribute] float% pX, [OutAttribute] float% pY, [OutAttribute] float% pZ)
			{
				float x, y, z;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_CAR_COORDINATES, vehicle, &x, &y, &z);
				pX = x;
				pY = y;
				pZ = z;
			}
			static void GET_CAR_DEFORMATION_AT_POS(Vehicle vehicle, float x, float y, float z, [OutAttribute] Vector3% pDeformation)
			{
				Vector3 v;
				NativeInvoke::Invoke<ScriptVoid>(NATIVE_GET_CAR_DEFORMATION_AT_POS, vehicle, x, y, z, &v);
				pDeformation = v;
			}
			static void GET_CAR_DOOR_LOCK_STATUS(Vehicle vehicle, [OutAttribute] unsigned int% pValue)
			{
				unsigned int p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_CAR_DOOR_LOCK_STATUS, vehicle, &p);
				pValue = p;
			}
			static void GET_CAR_FORWARD_VECTOR(Vehicle car, [OutAttribute] Vector3% vec)
			{
				Vector3 v;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_CAR_FORWARD_VECTOR, car, &v);
				vec = v;
			}
			static void GET_CAR_FORWARD_X(Vehicle vehicle, [OutAttribute] float% pValue)
			{
				float p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_CAR_FORWARD_X, vehicle, &p);
				pValue = p;
			}
			static void GET_CAR_FORWARD_Y(Vehicle vehicle, [OutAttribute] float% pValue)
			{
				float p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_CAR_FORWARD_Y, vehicle, &p);
				pValue = p;
			}
			static void GET_CAR_HEADING(Vehicle vehicle, [OutAttribute] float% pValue)
			{
				float p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_CAR_HEADING, vehicle, &p);
				pValue = p;
			}
			static void GET_CAR_HEALTH(Vehicle vehicle, [OutAttribute] unsigned int% pValue)
			{
				unsigned int p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_CAR_HEALTH, vehicle, &p);
				pValue = p;
			}
			static void GET_CAR_LIVERY(Vehicle car, [OutAttribute] int% livery)
			{
				int p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_CAR_LIVERY, car, &p);
				livery = p;
			}
			static void GET_CAR_MASS(Vehicle car, [OutAttribute] float% mass)
			{
				float p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_CAR_MASS, car, &p);
				mass = p;
			}
			static void GET_CAR_MODEL(Vehicle vehicle, [OutAttribute] unsigned int% pValue)
			{
				unsigned int p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_CAR_MODEL, vehicle, &p);
				pValue = p;
			}
			static void GET_CAR_MODEL_VALUE(Vehicle car, [OutAttribute] int% value)
			{
				int p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_CAR_MODEL_VALUE, car, &p);
				value = p;
			}
			static void GET_CAR_PITCH(Vehicle vehicle, [OutAttribute] float% pValue)
			{
				float p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_CAR_PITCH, vehicle, &p);
				pValue = p;
			}
			static void GET_CAR_ROLL(Vehicle vehicle, [OutAttribute] float% pValue)
			{
				float p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_CAR_ROLL, vehicle, &p);
				pValue = p;
			}
			static void GET_CAR_SPEED(Vehicle vehicle, [OutAttribute] float% pValue)
			{
				float p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_CAR_SPEED, vehicle, &p);
				pValue = p;
			}
			static void GET_CAR_SPEED_VECTOR(Vehicle vehicle, [OutAttribute] Vector3% pVector, b8 unknownFalse)
			{
				Vector3 v;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_CAR_SPEED_VECTOR, vehicle, &v, unknownFalse);
				pVector = v;
			}
			static void GET_CAR_UPRIGHT_VALUE(Vehicle vehicle, [OutAttribute] float% pValue)
			{
				float p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_CAR_UPRIGHT_VALUE, vehicle, &p);
				pValue = p;
			}
			static void GET_CURRENT_TAXI_CAR_MODEL([OutAttribute] unsigned int% pModel)
			{
				unsigned int p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_CURRENT_TAXI_CAR_MODEL, &p);
				pModel = p;
			}
			static void GET_DEAD_CAR_COORDINATES(Vehicle vehicle, [OutAttribute] float% pX, [OutAttribute] float% pY, [OutAttribute] float% pZ)
			{
				float x, y, z;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_DEAD_CAR_COORDINATES, vehicle, &x, &y, &z);
				pX = x;
				pY = y;
				pZ = z;
			}
			static void GET_DOOR_ANGLE_RATIO(Vehicle vehicle, unsigned int door, [OutAttribute] float% pAngleRatio)
			{
				float p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_DOOR_ANGLE_RATIO, vehicle, door, &p);
				pAngleRatio = p;
			}
			static void GET_EXTRA_CAR_COLOURS(Vehicle vehicle, [OutAttribute] ColourIndex% pColour1, [OutAttribute] ColourIndex% pColour2)
			{
				ColourIndex p1, p2;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_EXTRA_CAR_COLOURS, vehicle, &p1, &p2);
				pColour1 = p1;
				pColour2 = p2;
			}
			static void GET_KEY_FOR_CAR_IN_ROOM(Vehicle vehicle, [OutAttribute] unsigned int% pKey)
			{
				unsigned int p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_KEY_FOR_CAR_IN_ROOM, vehicle, &p);
				pKey = p;
			}
			static void GET_MAXIMUM_NUMBER_OF_PASSENGERS(Vehicle vehicle, [OutAttribute] unsigned int% pMax)
			{
				unsigned int p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_MAXIMUM_NUMBER_OF_PASSENGERS, vehicle, &p);
				pMax = p;
			}
			static void GET_NEAREST_CABLE_CAR(float x, float y, float z, float radius, [OutAttribute] Vehicle% pVehicle)
			{
				Vehicle p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_NEAREST_CABLE_CAR, x, y, z, radius, &p);
				pVehicle = p;
			}
			static void GET_NUMBER_OF_PASSENGERS(Vehicle vehicle, [OutAttribute] unsigned int% pNumPassengers)
			{
				unsigned int p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_NUMBER_OF_PASSENGERS, vehicle, &p);
				pNumPassengers = p;
			}
			static void GET_NUM_CAR_COLOURS(Vehicle vehicle, [OutAttribute] unsigned int% pNumColours)
			{
				unsigned int p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_NUM_CAR_COLOURS, vehicle, &p);
				pNumColours = p;
			}
			static void GET_NUM_CAR_LIVERIES(Vehicle car, [OutAttribute] int% num)
			{
				int p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_NUM_CAR_LIVERIES, car, &p);
				num = p;
			}
			static void GET_OFFSETS_FOR_ATTACH_CAR_TO_CAR(Vehicle car0, Vehicle car1, [OutAttribute] Vector3% Unk67, [OutAttribute] Vector3% Unk68)
			{
				Vector3 v1, v2;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_OFFSETS_FOR_ATTACH_CAR_TO_CAR, car0, car1, &v1, &v2);
				Unk67 = v1;
				Unk68 = v2;
			}
			static void GET_OFFSET_FROM_CAR_GIVEN_WORLD_COORDS(Vehicle vehicle, float pX, float pY, float pZ, [OutAttribute] float% pOffX, [OutAttribute] float% pOffY, [OutAttribute] float% pOffZ)
			{
				float x, y, z;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_OFFSET_FROM_CAR_GIVEN_WORLD_COORDS, vehicle, pX, pY, pZ, &x, &y, &z);
				pOffX = x;
				pOffY = y;
				pOffZ = z;
			}
			static void GET_OFFSET_FROM_CAR_IN_WORLD_COORDS(Vehicle vehicle, float pX, float pY, float pZ, [OutAttribute] float% pOffX, [OutAttribute] float% pOffY, [OutAttribute] float% pOffZ)
			{
				float x, y, z;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_OFFSET_FROM_CAR_IN_WORLD_COORDS, vehicle, pX, pY, pZ, &x, &y, &z);
				pOffX = x;
				pOffY = y;
				pOffZ = z;
			}
			static void GET_PLANE_UNDERCARRIAGE_POSITION(Vehicle plane, [OutAttribute] float% pos)
			{
				float p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_PLANE_UNDERCARRIAGE_POSITION, plane, &p);
				pos = p;
			}
			static void GET_POSITION_OF_CAR_RECORDING_AT_TIME(int CarRec, float time, [OutAttribute] float% pos)
			{
				float p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_POSITION_OF_CAR_RECORDING_AT_TIME, CarRec, time, &p);
				pos = p;
			}
			static void GET_TRAIN_CABOOSE(Vehicle train, [OutAttribute] Vehicle% caboose)
			{
				Vehicle p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_TRAIN_CABOOSE, train, &p);
				caboose = p;
			}
			static void GET_TRAIN_CARRIAGE(Vehicle train, int num, [OutAttribute] Vehicle% carriage)
			{
				Vehicle p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_TRAIN_CARRIAGE, train, num, &p);
				carriage = p;
			}
			static void GET_TRAIN_PLAYER_WOULD_ENTER(int player, [OutAttribute] int% train)
			{
				int p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_TRAIN_PLAYER_WOULD_ENTER, player, &p);
				train = p;
			}
			static void GET_VEHICLE_DIRT_LEVEL(Vehicle vehicle, [OutAttribute] float% pIntensity)
			{
				float p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_VEHICLE_DIRT_LEVEL, vehicle, &p);
				pIntensity = p;
			}
			static void GET_VEHICLE_PLAYER_WOULD_ENTER(int player, [OutAttribute] Vehicle% veh)
			{
				Vehicle p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_VEHICLE_PLAYER_WOULD_ENTER, player, &p);
				veh = p;
			}
			static void GET_VEHICLE_QUATERNION(Vehicle veh, [OutAttribute] float% qx, [OutAttribute] float% qy, [OutAttribute] float% qz, [OutAttribute] float% qw)
			{
				float x, y, z, w;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_VEHICLE_QUATERNION, veh, &x, &y, &z, &w);
				qx = x;
				qy = y;
				qz = z;
				qw = w;
			}
			static void HAND_VEHICLE_CONTROL_BACK_TO_PLAYER(Vehicle veh) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_HAND_VEHICLE_CONTROL_BACK_TO_PLAYER, veh); }
			static void LOCK_CAR_DOORS(Vehicle vehicle, unsigned int value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_LOCK_CAR_DOORS, vehicle, value); }
			static void MARK_CAR_AS_CONVOY_CAR(Vehicle vehicle, b8 convoyCar) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_MARK_CAR_AS_CONVOY_CAR, vehicle, convoyCar); }
			static void MARK_CAR_AS_NO_LONGER_NEEDED(Vehicle% pVehicle) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_MARK_CAR_AS_NO_LONGER_NEEDED, pVehicle); }
			static void MARK_MISSION_TRAINS_AS_NO_LONGER_NEEDED() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_MARK_MISSION_TRAINS_AS_NO_LONGER_NEEDED); }
			static void MARK_MISSION_TRAIN_AS_NO_LONGER_NEEDED(Train train) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_MARK_MISSION_TRAIN_AS_NO_LONGER_NEEDED, train); }
			static void OPEN_CAR_DOOR(Vehicle vehicle, unsigned int door) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_OPEN_CAR_DOOR, vehicle, door); }
			static void OVERRIDE_NUMBER_OF_PARKED_CARS(int num) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_OVERRIDE_NUMBER_OF_PARKED_CARS, num); }
			static void PAUSE_PLAYBACK_RECORDED_CAR(Vehicle car) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_PAUSE_PLAYBACK_RECORDED_CAR, car); }
			static void PLANE_STARTS_IN_AIR(Vehicle plane) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_PLANE_STARTS_IN_AIR, plane); }
			static void POP_CAR_BOOT(Vehicle vehicle) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_POP_CAR_BOOT, vehicle); }
			static void REMOVE_CARS_FROM_GENERATORS_IN_AREA(float x0, float y0, float z0, float x1, float y1, float z1) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_REMOVE_CARS_FROM_GENERATORS_IN_AREA, x0, y0, z0, x1, y1, z1); }
			static void REMOVE_CAR_RECORDING(int CarRec) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_REMOVE_CAR_RECORDING, CarRec); }
			static void REMOVE_CAR_WINDOW(Vehicle car, int windnum) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_REMOVE_CAR_WINDOW, car, windnum); }
			static void REMOVE_STUCK_CAR_CHECK(Vehicle vehicle) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_REMOVE_STUCK_CAR_CHECK, vehicle); }
			static void REMOVE_UPSIDEDOWN_CAR_CHECK(Vehicle vehicle) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_REMOVE_UPSIDEDOWN_CAR_CHECK, vehicle); }
			static void RESET_CAR_WHEELS(Vehicle car, b8 reset) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_RESET_CAR_WHEELS, car, reset); }
			static void RESET_STUCK_TIMER(Vehicle car, int timer_num) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_RESET_STUCK_TIMER, car, timer_num); }
			static void SELECT_WEAPONS_FOR_VEHICLE(Vehicle veh, int weapon) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SELECT_WEAPONS_FOR_VEHICLE, veh, weapon); }
			static void SET_ALL_CARS_CAN_BE_DAMAGED(b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_ALL_CARS_CAN_BE_DAMAGED, set); }
			static void SET_ALL_CAR_GENERATORS_BACK_TO_ACTIVE() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_ALL_CAR_GENERATORS_BACK_TO_ACTIVE); }
			static void SET_AMBIENT_PLANES_SPEED_MULTIPLIER(float multiplier) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_AMBIENT_PLANES_SPEED_MULTIPLIER, multiplier); }
			static void SET_BIKE_RIDER_WILL_PUT_FOOT_DOWN_WHEN_STOPPED(Vehicle bike, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_BIKE_RIDER_WILL_PUT_FOOT_DOWN_WHEN_STOPPED, bike, set); }
			static void SET_BLIP_THROTTLE_RANDOMLY(Vehicle veh, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_BLIP_THROTTLE_RANDOMLY, veh, set); }
			static void SET_CAN_BURST_CAR_TYRES(Vehicle car, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CAN_BURST_CAR_TYRES, car, set); }
			static void SET_CAN_RESPRAY_CAR(Vehicle car, b8 can) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CAN_RESPRAY_CAR, car, can); }
			static void SET_CAR_ALWAYS_CREATE_SKIDS(Vehicle car, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CAR_ALWAYS_CREATE_SKIDS, car, set); }
			static void SET_CAR_ANIM_CURRENT_TIME(Vehicle car, String^ animname0, String^ animname1, float time)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CAR_ANIM_CURRENT_TIME, car, ctx.marshal_as<const char*>(animname0), ctx.marshal_as<const char*>(animname1), time);
			}
			static void SET_CAR_ANIM_SPEED(Vehicle car, String^ animname0, String^ animname1, float speed)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CAR_ANIM_SPEED, car, ctx.marshal_as<const char*>(animname0), ctx.marshal_as<const char*>(animname1), speed);
			}
			static void SET_CAR_AS_MISSION_CAR(Vehicle car) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CAR_AS_MISSION_CAR, car); }
			static void SET_CAR_CAN_BE_DAMAGED(Vehicle vehicle, b8 value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CAR_CAN_BE_DAMAGED, vehicle, value); }
			static void SET_CAR_CAN_BE_VISIBLY_DAMAGED(Vehicle vehicle, b8 value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CAR_CAN_BE_VISIBLY_DAMAGED, vehicle, value); }
			static void SET_CAR_COLLISION(Vehicle car, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CAR_COLLISION, car, set); }
			static void SET_CAR_COLOUR_COMBINATION(Vehicle car, int combination) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CAR_COLOUR_COMBINATION, car, combination); }
			static void SET_CAR_COORDINATES(Vehicle vehicle, Vector3 pos) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CAR_COORDINATES, vehicle, pos.X, pos.Y, pos.Z); }
			static void SET_CAR_COORDINATES(Vehicle vehicle, float pX, float pY, float pZ) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CAR_COORDINATES, vehicle, pX, pY, pZ); }
			static void SET_CAR_COORDINATES_NO_OFFSET(Vehicle car, Vector3 pos) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CAR_COORDINATES_NO_OFFSET, car, pos.X, pos.Y, pos.Z); }
			static void SET_CAR_COORDINATES_NO_OFFSET(Vehicle car, float x, float y, float z) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CAR_COORDINATES_NO_OFFSET, car, x, y, z); }
			static void SET_CAR_DENSITY_MULTIPLIER(float density) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CAR_DENSITY_MULTIPLIER, density); }
			static void SET_CAR_DISTANCE_AHEAD_MULTIPLIER(Vehicle car, float multiplier) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CAR_DISTANCE_AHEAD_MULTIPLIER, car, multiplier); }
			static void SET_CAR_DOOR_LATCHED(Vehicle car, int door, b8 flag0, b8 flag1) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CAR_DOOR_LATCHED, car, door, flag0, flag1); }
			static void SET_CAR_ENGINE_ON(Vehicle car, b8 flag0, b8 flag1) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CAR_ENGINE_ON, car, flag0, flag1); }
			static void SET_CAR_FORWARD_SPEED(Vehicle vehicle, float speed) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CAR_FORWARD_SPEED, vehicle, speed); }
			static void SET_CAR_GENERATORS_ACTIVE_IN_AREA(float x0, float y0, float z0, float x1, float y1, float z1, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CAR_GENERATORS_ACTIVE_IN_AREA, x0, y0, z0, x1, y1, z1, set); }
			static void SET_CAR_HEADING(Vehicle vehicle, float dir) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CAR_HEADING, vehicle, dir); }
			static void SET_CAR_HEALTH(Vehicle vehicle, unsigned int Value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CAR_HEALTH, vehicle, Value); }
			static void SET_CAR_IN_CUTSCENE(Vehicle car, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CAR_IN_CUTSCENE, car, set); }
			static void SET_CAR_LANE_SHIFT(Vehicle car, float shift) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CAR_LANE_SHIFT, car, shift); }
			static void SET_CAR_LIGHT_MULTIPLIER(Vehicle car, float multiplier) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CAR_LIGHT_MULTIPLIER, car, multiplier); }
			static void SET_CAR_LIVERY(Vehicle car, int livery) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CAR_LIVERY, car, livery); }
			static void SET_CAR_NOT_DAMAGED_BY_RELATIONSHIP_GROUP(Vehicle car, b8 set, int group) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CAR_NOT_DAMAGED_BY_RELATIONSHIP_GROUP, car, set, group); }
			static void SET_CAR_ONLY_DAMAGED_BY_PLAYER(Vehicle car, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CAR_ONLY_DAMAGED_BY_PLAYER, car, set); }
			static void SET_CAR_ONLY_DAMAGED_BY_RELATIONSHIP_GROUP(Vehicle car, b8 set, int group) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CAR_ONLY_DAMAGED_BY_RELATIONSHIP_GROUP, car, set, group); }
			static void SET_CAR_PROOFS(Vehicle vehicle, b8 bulletProof, b8 fireProof, b8 explosionProof, b8 collisionProof, b8 meleeProof) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CAR_PROOFS, vehicle, bulletProof, fireProof, explosionProof, collisionProof, meleeProof); }
			static void SET_CAR_RANDOM_ROUTE_SEED(Vehicle car, int seed) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CAR_RANDOM_ROUTE_SEED, car, seed); }
			static void SET_CAR_STAY_IN_FAST_LANE(Vehicle car, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CAR_STAY_IN_FAST_LANE, car, set); }
			static void SET_CAR_STAY_IN_SLOW_LANE(Vehicle car, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CAR_STAY_IN_SLOW_LANE, car, set); }
			static void SET_CAR_STRONG(Vehicle vehicle, b8 strong) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CAR_STRONG, vehicle, strong); }
			static void SET_CAR_TRACTION(Vehicle car, float traction) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CAR_TRACTION, car, traction); }
			static void SET_CAR_VISIBLE(Vehicle vehicle, b8 value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CAR_VISIBLE, vehicle, value); }
			static void SET_CAR_WATERTIGHT(Vehicle car, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CAR_WATERTIGHT, car, set); }
			static void SET_CONVERTIBLE_ROOF(Vehicle car, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CONVERTIBLE_ROOF, car, set); }
			static void SET_ENGINE_HEALTH(Vehicle vehicle, float health) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_ENGINE_HEALTH, vehicle, health); }
			static void SET_EXTRA_CAR_COLOURS(Vehicle vehicle, ColourIndex colour1, ColourIndex colour2) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_EXTRA_CAR_COLOURS, vehicle, colour1, colour2); }
			static void SET_FREEBIES_IN_VEHICLE(Vehicle veh, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_FREEBIES_IN_VEHICLE, veh, set); }
			static void SET_FREE_RESPRAYS(b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_FREE_RESPRAYS, set); }
			static void SET_GANG_CAR(Vehicle car, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_GANG_CAR, car, set); }
			static void SET_GPS_REMAINS_WHEN_TARGET_REACHED_FLAG(b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_GPS_REMAINS_WHEN_TARGET_REACHED_FLAG, set); }
			static void SET_GPS_TEST_IN_3D_FLAG(b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_GPS_TEST_IN_3D_FLAG, set); }
			static void SET_HAS_BEEN_OWNED_BY_PLAYER(Vehicle car, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_HAS_BEEN_OWNED_BY_PLAYER, car, set); }
			static void SET_HAS_BEEN_OWNED_FOR_CAR_GENERATOR(int CarGen, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_HAS_BEEN_OWNED_FOR_CAR_GENERATOR, CarGen, set); }
			static void SET_HELI_BLADES_FULL_SPEED(Vehicle heli) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_HELI_BLADES_FULL_SPEED, heli); }
			static void SET_HELI_STABILISER(Vehicle heli, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_HELI_STABILISER, heli, set); }
			static void SET_IGNORE_NO_GPS_FLAG(b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_IGNORE_NO_GPS_FLAG, set); }
			static void SET_INTERP_IN_OUT_VEHICLE_ENABLED_THIS_FRAME(b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_INTERP_IN_OUT_VEHICLE_ENABLED_THIS_FRAME, set); }
			static void SET_LOAD_COLLISION_FOR_CAR_FLAG(Vehicle car, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_LOAD_COLLISION_FOR_CAR_FLAG, car, set); }
			static void SET_MISSION_TRAIN_COORDINATES(Vehicle train, float x, float y, float z) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_MISSION_TRAIN_COORDINATES, train, x, y, z); }
			static void SET_NEEDS_TO_BE_HOTWIRED(Vehicle veh, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_NEEDS_TO_BE_HOTWIRED, veh, set); }
			static void SET_NO_RESPRAYS(b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_NO_RESPRAYS, set); }
			static void SET_PARKED_CAR_DENSITY_MULTIPLIER(float multiplier) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_PARKED_CAR_DENSITY_MULTIPLIER, multiplier); }
			static void SET_PETROL_TANK_HEALTH(Vehicle vehicle, float value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_PETROL_TANK_HEALTH, vehicle, value); }
			static void SET_PETROL_TANK_WEAKPOINT(Vehicle car, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_PETROL_TANK_WEAKPOINT, car, set); }
			static void SET_PLANE_THROTTLE(Vehicle plane, float throttle) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_PLANE_THROTTLE, plane, throttle); }
			static void SET_PLANE_UNDERCARRIAGE_UP(Vehicle plain, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_PLANE_UNDERCARRIAGE_UP, plain, set); }
			static void SET_PLAYBACK_SPEED(Vehicle car, float speed) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_PLAYBACK_SPEED, car, speed); }
			static void SET_RANDOM_CAR_DENSITY_MULTIPLIER(float density) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_RANDOM_CAR_DENSITY_MULTIPLIER, density); }
			static void SET_RECORDING_TO_POINT_NEAREST_TO_COORS(Vehicle cat, float x, float y, float z) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_RECORDING_TO_POINT_NEAREST_TO_COORS, cat, x, y, z); }
			static void SET_REDUCE_VEHICLE_MODEL_BUDGET(b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_REDUCE_VEHICLE_MODEL_BUDGET, set); }
			static void SET_RENDER_TRAIN_AS_DERAILED(Vehicle train, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_RENDER_TRAIN_AS_DERAILED, train, set); }
			static void SET_ROCKET_LAUNCHER_FREEBIE_IN_HELI(b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_ROCKET_LAUNCHER_FREEBIE_IN_HELI, set); }
			static void SET_ROOM_FOR_CAR_BY_KEY(Vehicle car, unsigned int roomkey) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_ROOM_FOR_CAR_BY_KEY, car, roomkey); }
			static void SET_ROOM_FOR_CAR_BY_NAME(Vehicle car, String^ roomname)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_ROOM_FOR_CAR_BY_NAME, car, ctx.marshal_as<const char*>(roomname));
			}
			static void SET_SIREN_WITH_NO_DRIVER(Vehicle car, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_SIREN_WITH_NO_DRIVER, car, set); }
			static void SET_SUPPRESS_HEADLIGHT_SWITCH(b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_SUPPRESS_HEADLIGHT_SWITCH, set); }
			static void SET_TARGET_CAR_FOR_MISSION_GARAGE(int garage, Vehicle car) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_TARGET_CAR_FOR_MISSION_GARAGE, garage, car); }
			static void SET_TAXI_LIGHTS(Vehicle car, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_TAXI_LIGHTS, car, set); }
			static void SET_TRAIN_AUDIO_ROLLOFF(Vehicle train, float rolloff) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_TRAIN_AUDIO_ROLLOFF, train, rolloff); }
			static void SET_TRAIN_CRUISE_SPEED(Vehicle train, float speed) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_TRAIN_CRUISE_SPEED, train, speed); }
			static void SET_TRAIN_FORCED_TO_SLOW_DOWN(Vehicle train, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_TRAIN_FORCED_TO_SLOW_DOWN, train, set); }
			static void SET_TRAIN_IS_STOPPED_AT_STATION(Vehicle train) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_TRAIN_IS_STOPPED_AT_STATION, train); }
			static void SET_TRAIN_SPEED(Vehicle train, float speed) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_TRAIN_SPEED, train, speed); }
			static void SET_TRAIN_STOPS_FOR_STATIONS(Vehicle train, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_TRAIN_STOPS_FOR_STATIONS, train, set); }
			static void SET_UPSIDEDOWN_CAR_NOT_DAMAGED(Vehicle car, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_UPSIDEDOWN_CAR_NOT_DAMAGED, car, set); }
			static void SET_VEHICLE_ALPHA(Vehicle veh, int alpha) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_VEHICLE_ALPHA, veh, alpha); }
			static void SET_VEHICLE_CAN_BE_TARGETTED(Vehicle veh, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_VEHICLE_CAN_BE_TARGETTED, veh, set); }
			static void SET_VEHICLE_DIRT_LEVEL(Vehicle vehicle, float intensity) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_VEHICLE_DIRT_LEVEL, vehicle, intensity); }
			static void SET_VEHICLE_EXPLODES_ON_HIGH_EXPLOSION_DAMAGE(Vehicle veh, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_VEHICLE_EXPLODES_ON_HIGH_EXPLOSION_DAMAGE, veh, set); }
			static void SET_VEHICLE_IS_CONSIDERED_BY_PLAYER(Vehicle veh, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_VEHICLE_IS_CONSIDERED_BY_PLAYER, veh, set); }
			static void SET_VEHICLE_QUATERNION(Vehicle veh, float qx, float qy, float qz, float qw) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_VEHICLE_QUATERNION, veh, qx, qy, qz, qw); }
			static void SET_VEHICLE_STEER_BIAS(Vehicle veh, float val) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_VEHICLE_STEER_BIAS, veh, val); }
			static void SET_VEH_ALARM(Vehicle veh, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_VEH_ALARM, veh, set); }
			static void SET_VEH_ALARM_DURATION(Vehicle veh, int duration) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_VEH_ALARM_DURATION, veh, duration); }
			static void SET_VEH_HAS_STRONG_AXLES(Vehicle veh, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_VEH_HAS_STRONG_AXLES, veh, set); }
			static void SET_VEH_HAZARDLIGHTS(Vehicle vehicle, b8 on) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_VEH_HAZARDLIGHTS, vehicle, on); }
			static void SET_VEH_INDICATORLIGHTS(Vehicle veh, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_VEH_INDICATORLIGHTS, veh, set); }
			static void SET_VEH_INTERIORLIGHT(Vehicle veh, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_VEH_INTERIORLIGHT, veh, set); }
			static void SHUT_CAR_DOOR(Vehicle vehicle, unsigned int door) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SHUT_CAR_DOOR, vehicle, door); }
			static void SKIP_IN_PLAYBACK_RECORDED_CAR(Vehicle car, float time) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SKIP_IN_PLAYBACK_RECORDED_CAR, car, time); }
			static void SKIP_TIME_IN_PLAYBACK_RECORDED_CAR(int CarRec, float time) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SKIP_TIME_IN_PLAYBACK_RECORDED_CAR, CarRec, time); }
			static void SKIP_TO_END_AND_STOP_PLAYBACK_RECORDED_CAR(Vehicle car) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SKIP_TO_END_AND_STOP_PLAYBACK_RECORDED_CAR, car); }
			static void SKIP_TO_NEXT_ALLOWED_STATION(Vehicle train) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SKIP_TO_NEXT_ALLOWED_STATION, train); }
			static void SMASH_CAR_WINDOW(Vehicle car, int windownum) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SMASH_CAR_WINDOW, car, windownum); }
			static void SOUND_CAR_HORN(Vehicle vehicle, unsigned int duration) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SOUND_CAR_HORN, vehicle, duration); }
			static void START_PLAYBACK_RECORDED_CAR(Vehicle car, int CarRec) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_START_PLAYBACK_RECORDED_CAR, car, CarRec); }
			static void START_PLAYBACK_RECORDED_CAR_LOOPED(Vehicle car, int Unk69) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_START_PLAYBACK_RECORDED_CAR_LOOPED, car, Unk69); }
			static void START_PLAYBACK_RECORDED_CAR_USING_AI(Vehicle car, int CarRec) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_START_PLAYBACK_RECORDED_CAR_USING_AI, car, CarRec); }
			static void STOP_CAR_BREAKING(Vehicle car, b8 stop) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_STOP_CAR_BREAKING, car, stop); }
			static void STOP_PLAYBACK_RECORDED_CAR(Vehicle car) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_STOP_PLAYBACK_RECORDED_CAR, car); }
			static void STORE_CAR_CHAR_IS_IN_NO_SAVE(Ped ped, Vehicle* car) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_STORE_CAR_CHAR_IS_IN_NO_SAVE, ped, car); }
			static void SUPPRESS_CAR_MODEL(unsigned int model) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SUPPRESS_CAR_MODEL, model); }
			static void SWITCH_CAR_GENERATOR(int handle, int type) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SWITCH_CAR_GENERATOR, handle, type); }
			static void SWITCH_CAR_SIREN(Vehicle car, b8 siren) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SWITCH_CAR_SIREN, car, siren); }
			static void TRAIN_LEAVE_STATION(Vehicle train) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TRAIN_LEAVE_STATION, train); }
			static void TRIGGER_VEH_ALARM(Vehicle car) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TRIGGER_VEH_ALARM, car); }
			static void TURN_CAR_TO_FACE_COORD(Vehicle car, float x, float y) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TURN_CAR_TO_FACE_COORD, car, x, y); }
			static void TURN_OFF_VEHICLE_EXTRA(Vehicle veh, int extra, b8 turnoff) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TURN_OFF_VEHICLE_EXTRA, veh, extra, turnoff); }
			static void UNPAUSE_PLAYBACK_RECORDED_CAR(Vehicle car) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_UNPAUSE_PLAYBACK_RECORDED_CAR, car); }
			static void VEHICLE_CAN_BE_TARGETTED_BY_HS_MISSILE(Vehicle car, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_VEHICLE_CAN_BE_TARGETTED_BY_HS_MISSILE, car, set); }
			static void VEHICLE_DOES_PROVIDE_COVER(Vehicle veh, b8 cover) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_VEHICLE_DOES_PROVIDE_COVER, veh, cover); }
			static void WARP_CHAR_FROM_CAR_TO_CAR(Ped ped, Vehicle vehicle, unsigned int seatIndex) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_WARP_CHAR_FROM_CAR_TO_CAR, ped, vehicle, seatIndex); }
			static void WARP_CHAR_FROM_CAR_TO_COORD(Ped ped, float x, float y, float z) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_WARP_CHAR_FROM_CAR_TO_COORD, ped, x, y, z); }
			static void WARP_CHAR_INTO_CAR(Ped ped, Vehicle vehicle) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_WARP_CHAR_INTO_CAR, ped, vehicle); }
			static void WARP_CHAR_INTO_CAR_AS_PASSENGER(Ped ped, Vehicle vehicle, unsigned int seatIndex) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_WARP_CHAR_INTO_CAR_AS_PASSENGER, ped, vehicle, seatIndex); }
			static void WASH_VEHICLE_TEXTURES(Vehicle vehicle, unsigned int intensity) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_WASH_VEHICLE_TEXTURES, vehicle, intensity); }
			static void ADD_OBJECT_TO_INTERIOR_ROOM_BY_KEY(Entity obj, unsigned int roomKey) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ADD_OBJECT_TO_INTERIOR_ROOM_BY_KEY, obj, roomKey); }
			static void ADD_OBJECT_TO_INTERIOR_ROOM_BY_NAME(Entity obj, String^ roomName)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_ADD_OBJECT_TO_INTERIOR_ROOM_BY_NAME, obj, ctx.marshal_as<const char*>(roomName));
			}
			static void ADD_STUNT_JUMP(float x, float y, float z, float x0, float y0, float z0, float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3, int reward) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ADD_STUNT_JUMP, x, y, z, x0, y0, z0, x1, y1, z1, x2, y2, z2, x3, y3, z3, reward); }
			static void ANCHOR_OBJECT(Entity obj, b8 anchor, unsigned int flags) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ANCHOR_OBJECT, obj, anchor, flags); }
			static void APPLY_FORCE_TO_OBJECT(Entity obj, unsigned int uk0_3, float pX, float pY, float pZ, float spinX, float spinY, float spinZ, unsigned int uk4_0, unsigned int uk5_1, unsigned int uk6_1, unsigned int uk7_1) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_APPLY_FORCE_TO_OBJECT, obj, uk0_3, pX, pY, pZ, spinX, spinY, spinZ, uk4_0, uk5_1, uk6_1, uk7_1); }
			static void ATTACH_OBJECT_TO_CAR(Entity obj, Vehicle v, unsigned int unknown0_0, float pX, float pY, float pZ, float rX, float rY, float rZ) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ATTACH_OBJECT_TO_CAR, obj, v, unknown0_0, pX, pY, pZ, rX, rY, rZ); }
			static void ATTACH_OBJECT_TO_CAR_PHYSICALLY(Entity obj, Vehicle car, ScriptAny Unk79, ScriptAny Unk80, ScriptAny Unk81, ScriptAny Unk82, ScriptAny Unk83, ScriptAny Unk84, ScriptAny Unk85, ScriptAny Unk86, ScriptAny Unk87, ScriptAny Unk88, ScriptAny Unk89, ScriptAny Unk90, b8 flag) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ATTACH_OBJECT_TO_CAR_PHYSICALLY, obj, car, Unk79, Unk80, Unk81, Unk82, Unk83, Unk84, Unk85, Unk86, Unk87, Unk88, Unk89, Unk90, flag); }
			static void ATTACH_OBJECT_TO_OBJECT(Entity obj0, Entity obj1_attach_to, int Unk91, float x0, float y0, float z0, float x1, float y1, float z1) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ATTACH_OBJECT_TO_OBJECT, obj0, obj1_attach_to, Unk91, x0, y0, z0, x1, y1, z1); }
			static void ATTACH_OBJECT_TO_PED(Entity obj, Ped c, unsigned int bone, float pX, float pY, float pZ, float rX, float rY, float rZ, unsigned int unknown1_0) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ATTACH_OBJECT_TO_PED, obj, c, bone, pX, pY, pZ, rX, rY, rZ, unknown1_0); }
			static void ATTACH_OBJECT_TO_PED_PHYSICALLY(Entity obj, Ped c, b8 unknown, unsigned int bone, float pX, float pY, float pZ, float rX, float rY, float rZ, unsigned int unknown1_0, unsigned int unknown2_0) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ATTACH_OBJECT_TO_PED_PHYSICALLY, obj, c, unknown, bone, pX, pY, pZ, rX, rY, rZ, unknown1_0, unknown2_0); }
			static void CHANGE_GARAGE_TYPE(int garage, int type) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_CHANGE_GARAGE_TYPE, garage, type); }
			static void CLEAR_OBJECT_LAST_DAMAGE_ENTITY(Entity obj) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_CLEAR_OBJECT_LAST_DAMAGE_ENTITY, obj); }
			static void CLEAR_OBJECT_LAST_WEAPON_DAMAGE(Entity obj) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_CLEAR_OBJECT_LAST_WEAPON_DAMAGE, obj); }
			static void CLEAR_ROOM_FOR_OBJECT(Entity obj) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_CLEAR_ROOM_FOR_OBJECT, obj); }
			static void CLOSE_GARAGE(String^ garageName)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_CLOSE_GARAGE, ctx.marshal_as<const char*>(garageName));
			}
			static void CONNECT_LODS(Entity obj0, Entity obj1) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_CONNECT_LODS, obj0, obj1); }
			static void CREATE_OBJECT(int model, Vector3 pos, [OutAttribute] Entity% pObj, b8 unknownTrue)
			{
				Entity p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_CREATE_OBJECT, model, pos.X, pos.Y, pos.Z, &p, unknownTrue);
				pObj = p;
			}
			static void CREATE_OBJECT(int model, float x, float y, float z, [OutAttribute] Entity% pObj, b8 unknownTrue)
			{
				Entity p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_CREATE_OBJECT, model, x, y, z, &p, unknownTrue);
				pObj = p;
			}
			static void CREATE_OBJECT_NO_OFFSET(int model, Vector3 pos, [OutAttribute] Entity% pObj, b8 unknownTrue)
			{
				Entity p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_CREATE_OBJECT_NO_OFFSET, model, pos.X, pos.Y, pos.Z, &p, unknownTrue);
				pObj = p;
			}
			static void CREATE_OBJECT_NO_OFFSET(int model, float x, float y, float z, [OutAttribute] Entity% pObj, b8 unknownTrue)
			{
				Entity p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_CREATE_OBJECT_NO_OFFSET, model, x, y, z, &p, unknownTrue);
				pObj = p;
			}
			
			[System::ObsoleteAttribute("This native is obsolete. Use CPools.DeleteObject instead.")]
			static void DELETE_OBJECT(Entity* pObj) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DELETE_OBJECT, pObj); }

			static void DETACH_OBJECT(Entity obj, b8 unknown) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DETACH_OBJECT, obj, unknown); }
			static void DETACH_OBJECT_NO_COLLIDE(Entity obj, b8 flag) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DETACH_OBJECT_NO_COLLIDE, obj, flag); }
			static void DONT_REMOVE_OBJECT(Entity obj) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DONT_REMOVE_OBJECT, obj); }
			static void DROP_OBJECT(Ped ped, b8 unknownTrue) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DROP_OBJECT, ped, unknownTrue); }
			static void ENABLE_DISABLED_ATTRACTORS_ON_OBJECT(Entity obj, b8 enable) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ENABLE_DISABLED_ATTRACTORS_ON_OBJECT, obj, enable); }
			static void FREEZE_OBJECT_POSITION(Entity obj, b8 frozen) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_FREEZE_OBJECT_POSITION, obj, frozen); }
			static void FREEZE_OBJECT_POSITION_AND_DONT_LOAD_COLLISION(Entity obj, b8 freeze) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_FREEZE_OBJECT_POSITION_AND_DONT_LOAD_COLLISION, obj, freeze); }
			static void FREEZE_POSITION_OF_CLOSEST_OBJECT_OF_TYPE(float x, float y, float z, float radius, unsigned int model, b8 frozen) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_FREEZE_POSITION_OF_CLOSEST_OBJECT_OF_TYPE, x, y, z, radius, model, frozen); }
			static void GET_CLOSEST_STEALABLE_OBJECT(float x, float y, float z, float radius, [OutAttribute] Entity% obj)
			{
				Entity p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_CLOSEST_STEALABLE_OBJECT, x, y, z, radius, &p);
				obj = p;
			}
			static void GET_DOOR_STATE(Entity obj, [OutAttribute] unsigned int% Unk92, [OutAttribute] float% Unk93)
			{
				unsigned int p1;
				float p2;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_DOOR_STATE, obj, &p1, &p2);
				Unk92 = p1;
				Unk93 = p2;
			}
			static void GET_OBJECT_ANIM_CURRENT_TIME(Entity obj, String^ animname0, String^ animname1, [OutAttribute] float% time)
			{
				msclr::interop::marshal_context ctx;
				float p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_OBJECT_ANIM_CURRENT_TIME, obj, ctx.marshal_as<const char*>(animname0), ctx.marshal_as<const char*>(animname1), &p);
				time = p;
			}
			static void GET_OBJECT_ANIM_TOTAL_TIME(Entity obj, String^ animname0, String^ animname1, [OutAttribute] float% time)
			{
				msclr::interop::marshal_context ctx;
				float p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_OBJECT_ANIM_TOTAL_TIME, obj, ctx.marshal_as<const char*>(animname0), ctx.marshal_as<const char*>(animname1), &p);
				time = p;
			}
			static void GET_OBJECT_COORDINATES(Entity obj, [OutAttribute] Vector3% pos)
			{
				float x, y, z;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_OBJECT_COORDINATES, obj, &x, &y, &z);
				pos = Vector3(x, y, z);
			}
			static void GET_OBJECT_COORDINATES(Entity obj, [OutAttribute] float% pX, [OutAttribute] float% pY, [OutAttribute] float% pZ)
			{
				float x, y, z;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_OBJECT_COORDINATES, obj, &x, &y, &z);
				pX = x;
				pY = y;
				pZ = z;
			}
			static void GET_OBJECT_HEADING(Entity obj, [OutAttribute] float% pHeading)
			{
				float p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_OBJECT_HEADING, obj, &p);
				pHeading = p;
			}
			static void GET_OBJECT_HEALTH(Entity obj, [OutAttribute] float% pHealth)
			{
				float p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_OBJECT_HEALTH, obj, &p);
				pHealth = p;
			}
			static void GET_OBJECT_MASS(Entity obj, [OutAttribute] float% mass)
			{
				float p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_OBJECT_MASS, obj, &p);
				mass = p;
			}
			static void GET_OBJECT_MODEL(Entity obj, [OutAttribute] unsigned int% pModel)
			{
				unsigned int p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_OBJECT_MODEL, obj, &p);
				pModel = p;
			}
			static void GET_OBJECT_QUATERNION(Entity obj, [OutAttribute] float% qx, [OutAttribute] float% qy, [OutAttribute] float% qz, [OutAttribute] float% qw)
			{
				float x, y, z, w;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_OBJECT_QUATERNION, obj, &x, &y, &z, &w);
				qx = x;
				qy = y;
				qz = z;
				qw = w;
			}
			static void GET_OBJECT_ROTATION_VELOCITY(Entity obj, [OutAttribute] float% pX, [OutAttribute] float% pY, [OutAttribute] float% pZ)
			{
				float x, y, z;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_OBJECT_ROTATION_VELOCITY, obj, &x, &y, &z);
				pX = x;
				pY = y;
				pZ = z;
			}
			static void GET_OBJECT_SPEED(Entity obj, [OutAttribute] float% pSpeed)
			{
				float p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_OBJECT_SPEED, obj, &p);
				pSpeed = p;
			}
			static void GET_OBJECT_TURN_MASS(Entity obj, [OutAttribute] float% turnmass)
			{
				float p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_OBJECT_TURN_MASS, obj, &p);
				turnmass = p;
			}
			static void GET_OBJECT_VELOCITY(Entity obj, [OutAttribute] float% pX, [OutAttribute] float% pY, [OutAttribute] float% pZ)
			{
				float x, y, z;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_OBJECT_VELOCITY, obj, &x, &y, &z);
				pX = x;
				pY = y;
				pZ = z;
			}
			static void GET_OFFSET_FROM_OBJECT_IN_WORLD_COORDS(Entity obj, float pX, float pY, float pZ, [OutAttribute] float% pOffX, [OutAttribute] float% pOffY, [OutAttribute] float% pOffZ)
			{
				float x, y, z;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_OFFSET_FROM_OBJECT_IN_WORLD_COORDS, obj, pX, pY, pZ, &x, &y, &z);
				pOffX = x;
				pOffY = y;
				pOffZ = z;
			}
			static void GET_ROOM_KEY_FROM_OBJECT(Entity obj, [OutAttribute] unsigned int% pRoomKey)
			{
				unsigned int p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_ROOM_KEY_FROM_OBJECT, obj, &p);
				pRoomKey = p;
			}
			static void GET_STATE_OF_CLOSEST_DOOR_OF_TYPE(unsigned int model, float x, float y, float z, [OutAttribute] int% state, [OutAttribute] float% Unk94)
			{
				int p1;
				float p2;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_STATE_OF_CLOSEST_DOOR_OF_TYPE, model, x, y, z, &p1, &p2);
				state = p1;
				Unk94 = p2;
			}
			static void GRAB_NEARBY_OBJECT_WITH_SPECIAL_ATTRIBUTE(int attribute, [OutAttribute] Entity% obj)
			{
				Entity p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GRAB_NEARBY_OBJECT_WITH_SPECIAL_ATTRIBUTE, attribute, &p);
				obj = p;
			}
			static void MAKE_OBJECT_TARGETTABLE(Entity obj, b8 targettable) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_MAKE_OBJECT_TARGETTABLE, obj, targettable); }
			static void MARK_OBJECT_AS_NO_LONGER_NEEDED(Entity% pObj) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_MARK_OBJECT_AS_NO_LONGER_NEEDED, pObj); }
			static void OPEN_GARAGE(String^ name)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_OPEN_GARAGE, ctx.marshal_as<const char*>(name));
			}
			static void PLACE_OBJECT_RELATIVE_TO_CAR(Entity obj, Vehicle car, float x, float y, float z) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_PLACE_OBJECT_RELATIVE_TO_CAR, obj, car, x, y, z); }
			static void SET_ACTIVATE_OBJECT_PHYSICS_AS_SOON_AS_IT_IS_UNFROZEN(Entity obj, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_ACTIVATE_OBJECT_PHYSICS_AS_SOON_AS_IT_IS_UNFROZEN, obj, set); }
			static void SET_DOOR_STATE(Entity door, b8 flag, float Unk95) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_DOOR_STATE, door, flag, Unk95); }
			static void SET_GARAGE_LEAVE_CAMERA_ALONE(String^ garageName, b8 set)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_GARAGE_LEAVE_CAMERA_ALONE, ctx.marshal_as<const char*>(garageName), set);
			}
			static void SET_HEADING_OF_CLOSEST_OBJECT_OF_TYPE(float x, float y, float z, float radius, unsigned int type_or_model, float heading) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_HEADING_OF_CLOSEST_OBJECT_OF_TYPE, x, y, z, radius, type_or_model, heading); }
			static void SET_LOAD_COLLISION_FOR_OBJECT_FLAG(Entity obj, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_LOAD_COLLISION_FOR_OBJECT_FLAG, obj, set); }
			static void SET_OBJECT_ALPHA(Entity obj, int alpha) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_OBJECT_ALPHA, obj, alpha); }
			static void SET_OBJECT_ANIM_CURRENT_TIME(Entity obj, String^ animname0, String^ animname1, float time)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_OBJECT_ANIM_CURRENT_TIME, obj, ctx.marshal_as<const char*>(animname0), ctx.marshal_as<const char*>(animname1), time);
			}
			static void SET_OBJECT_ANIM_PLAYING_FLAG(Entity obj, String^ animname0, String^ animname1, b8 flag)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_OBJECT_ANIM_PLAYING_FLAG, obj, ctx.marshal_as<const char*>(animname0), ctx.marshal_as<const char*>(animname1), flag);
			}
			static void SET_OBJECT_ANIM_SPEED(Entity obj, String^ animname0, String^ animname1, float speed)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_OBJECT_ANIM_SPEED, obj, ctx.marshal_as<const char*>(animname0), ctx.marshal_as<const char*>(animname1), speed);
			}
			static void SET_OBJECT_AS_STEALABLE(Entity obj, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_OBJECT_AS_STEALABLE, obj, set); }
			static void SET_OBJECT_CCD(Entity obj, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_OBJECT_CCD, obj, set); }
			static void SET_OBJECT_COLLISION(Entity obj, b8 value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_OBJECT_COLLISION, obj, value); }
			static void SET_OBJECT_COORDINATES(Entity obj, Vector3 pos) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_OBJECT_COORDINATES, obj, pos.X, pos.Y, pos.Z); }
			static void SET_OBJECT_COORDINATES(Entity obj, float pX, float pY, float pZ) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_OBJECT_COORDINATES, obj, pX, pY, pZ); }
			static void SET_OBJECT_DRAW_LAST(Entity obj, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_OBJECT_DRAW_LAST, obj, set); }
			static void SET_OBJECT_DYNAMIC(Entity obj, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_OBJECT_DYNAMIC, obj, set); }
			static void SET_OBJECT_HEADING(Entity obj, float value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_OBJECT_HEADING, obj, value); }
			static void SET_OBJECT_HEALTH(Entity obj, float health) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_OBJECT_HEALTH, obj, health); }
			static void SET_OBJECT_INITIAL_ROTATION_VELOCITY(Entity obj, float x, float y, float z) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_OBJECT_INITIAL_ROTATION_VELOCITY, obj, x, y, z); }
			static void SET_OBJECT_INITIAL_VELOCITY(Entity obj, float x, float y, float z) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_OBJECT_INITIAL_VELOCITY, obj, x, y, z); }
			static void SET_OBJECT_INVINCIBLE(Entity obj, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_OBJECT_INVINCIBLE, obj, set); }
			static void SET_OBJECT_LIGHTS(Entity obj, b8 lights) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_OBJECT_LIGHTS, obj, lights); }
			static void SET_OBJECT_ONLY_DAMAGED_BY_PLAYER(Entity obj, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_OBJECT_ONLY_DAMAGED_BY_PLAYER, obj, set); }
			static void SET_OBJECT_PHYSICS_PARAMS(Entity obj, float Unk96, float Unk97, float v0x, float v0y, float v0z, float v1x, float v1y, float v1z, unsigned int flag0, unsigned int flag1) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_OBJECT_PHYSICS_PARAMS, obj, Unk96, Unk97, v0x, v0y, v0z, v1x, v1y, v1z, flag0, flag1); }
			static void SET_OBJECT_PROOFS(Entity obj, b8 unknown0, b8 fallingDamage, b8 unknown1, b8 unknown2, b8 unknown3) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_OBJECT_PROOFS, obj, unknown0, fallingDamage, unknown1, unknown2, unknown3); }
			static void SET_OBJECT_QUATERNION(Entity obj, float qx, float qy, float qz, float qw) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_OBJECT_QUATERNION, obj, qx, qy, qz, qw); }
			static void SET_OBJECT_RECORDS_COLLISIONS(Entity obj, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_OBJECT_RECORDS_COLLISIONS, obj, set); }
			static void SET_OBJECT_RENDER_SCORCHED(Entity obj, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_OBJECT_RENDER_SCORCHED, obj, set); }
			static void SET_OBJECT_ROTATION(Entity obj, float Pitch, float Roll, float Yaw) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_OBJECT_ROTATION, obj, Pitch, Roll, Yaw); }
			static void SET_OBJECT_SCALE(Entity obj, float scale) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_OBJECT_SCALE, obj, scale); }
			static void SET_OBJECT_USED_IN_POOL_GAME(Entity obj, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_OBJECT_USED_IN_POOL_GAME, obj, set); }
			static void SET_OBJECT_VISIBLE(Entity obj, b8 value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_OBJECT_VISIBLE, obj, value); }
			static void SET_USES_COLLISION_OF_CLOSEST_OBJECT_OF_TYPE(float x, float y, float z, float radius, unsigned int type_or_model, b8 flag) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_USES_COLLISION_OF_CLOSEST_OBJECT_OF_TYPE, x, y, z, radius, type_or_model, flag); }
			static void SET_VISIBILITY_OF_CLOSEST_OBJECT_OF_TYPE(float x, float y, float z, float radius, unsigned int type_or_model, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_VISIBILITY_OF_CLOSEST_OBJECT_OF_TYPE, x, y, z, radius, type_or_model, set); }
			static void SWAP_NEAREST_BUILDING_MODEL(float x, float y, float z, float radius, unsigned int modelfrom, unsigned int modelto) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SWAP_NEAREST_BUILDING_MODEL, x, y, z, radius, modelfrom, modelto); }
			static void WINCH_CAN_PICK_OBJECT_UP(Entity obj, b8 can) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_WINCH_CAN_PICK_OBJECT_UP, obj, can); }
			static void FIND_NEAREST_ENTITIES_WITH_SPECIAL_ATTRIBUTE(float x, float y, float z) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_FIND_NEAREST_ENTITIES_WITH_SPECIAL_ATTRIBUTE, x, y, z); }
			static void SET_VISIBILITY_OF_NEARBY_ENTITY_WITH_SPECIAL_ATTRIBUTE(int attribute, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_VISIBILITY_OF_NEARBY_ENTITY_WITH_SPECIAL_ATTRIBUTE, attribute, set); }
			static void ADD_COVER_BLOCKING_AREA(ScriptAny Unk110, ScriptAny Unk111, ScriptAny Unk112, ScriptAny Unk113, ScriptAny Unk114, ScriptAny Unk115, ScriptAny Unk116, ScriptAny Unk117, ScriptAny Unk118) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ADD_COVER_BLOCKING_AREA, Unk110, Unk111, Unk112, Unk113, Unk114, Unk115, Unk116, Unk117, Unk118); }
			static void ADD_COVER_POINT(float Unk119, float Unk120, float Unk121, int Unk122, float Unk123, int Unk124, int Unk125, [OutAttribute] uint32_t% Unk126)
			{
				uint32_t p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_ADD_COVER_POINT, Unk119, Unk120, Unk121, Unk122, Unk123, Unk124, Unk125, &p);
				Unk126 = p;
			}
			static void ADD_FOLLOW_NAVMESH_TO_PHONE_TASK(Ped ped, ScriptAny Unk127, ScriptAny Unk128, ScriptAny Unk129) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ADD_FOLLOW_NAVMESH_TO_PHONE_TASK, ped, Unk127, Unk128, Unk129); }
			static void ADD_NEEDED_AT_POSN(float x, float y, float z) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ADD_NEEDED_AT_POSN, x, y, z); }
			//static void ADD_POINT_TO_GPS_RACE_TRACK(Vector3* point) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ADD_POINT_TO_GPS_RACE_TRACK, point); }
			static void ADD_SCENARIO_BLOCKING_AREA(float x0, float y0, float z0, float x1, float y1, float z1) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ADD_SCENARIO_BLOCKING_AREA, x0, y0, z0, x1, y1, z1); }
			static void BLOCK_COWERING_IN_COVER(Ped ped, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_BLOCK_COWERING_IN_COVER, ped, set); }
			static void BLOCK_PEEKING_IN_COVER(Ped ped, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_BLOCK_PEEKING_IN_COVER, ped, set); }
			static void CLEAR_SEQUENCE_TASK(TaskSequence taskSequence) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_CLEAR_SEQUENCE_TASK, taskSequence); }
			static void CLOSE_SEQUENCE_TASK(TaskSequence taskSequence) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_CLOSE_SEQUENCE_TASK, taskSequence); }
			static void FIRE_PED_WEAPON(Ped ped, float x, float y, float z) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_FIRE_PED_WEAPON, ped, x, y, z); }
			static void HIGH_FALL_SCREAM(Ped ped) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_HIGH_FALL_SCREAM, ped); }
			static void ON_FIRE_SCREAM(Ped ped) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ON_FIRE_SCREAM, ped); }
			//static void OPEN_SEQUENCE_TASK(TaskSequence* pTaskSequence) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_OPEN_SEQUENCE_TASK, pTaskSequence); }
			static void PANIC_SCREAM(Ped ped) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_PANIC_SCREAM, ped); }
			static void REMOVE_COVER_POINT(CoverPoint coverPoint) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_REMOVE_COVER_POINT, coverPoint); }
			static void SET_DEFAULT_TARGET_SCORING_FUNCTION(Ped ped, ScriptAny Unk132) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_DEFAULT_TARGET_SCORING_FUNCTION, ped, Unk132); }
			static void SET_DRIVE_TASK_CRUISE_SPEED(Ped ped, float speed) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_DRIVE_TASK_CRUISE_SPEED, ped, speed); }
			static void TAKE_CAR_OUT_OF_PARKED_CARS_BUDGET(Vehicle car, b8 out) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TAKE_CAR_OUT_OF_PARKED_CARS_BUDGET, car, out); }
			static void _TASK_ACHIEVE_HEADING(Ped ped, float heading) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_ACHIEVE_HEADING, ped, heading); }
			static void _TASK_AIM_GUN_AT_CHAR(Ped ped, Ped targetPed, unsigned int duration) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_AIM_GUN_AT_CHAR, ped, targetPed, duration); }
			static void _TASK_AIM_GUN_AT_COORD(Ped ped, float tX, float tY, float tZ, unsigned int duration) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_AIM_GUN_AT_COORD, ped, tX, tY, tZ, duration); }
			static void _TASK_CAR_DRIVE_TO_COORD(Ped ped, Vehicle veh, float Unk133, float Unk134, float Unk135, float Unk136, int Unk137, int Unk138, int Unk139, float Unk140, int Unk141) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_CAR_DRIVE_TO_COORD, ped, veh, Unk133, Unk134, Unk135, Unk136, Unk137, Unk138, Unk139, Unk140, Unk141); }
			static void _TASK_CAR_DRIVE_TO_COORD_NOT_AGAINST_TRAFFIC(Ped ped, ScriptAny Unk142, ScriptAny Unk143, ScriptAny Unk144, ScriptAny Unk145, ScriptAny Unk146, ScriptAny Unk147, ScriptAny Unk148, ScriptAny Unk149, ScriptAny Unk150, ScriptAny Unk151) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_CAR_DRIVE_TO_COORD_NOT_AGAINST_TRAFFIC, ped, Unk142, Unk143, Unk144, Unk145, Unk146, Unk147, Unk148, Unk149, Unk150, Unk151); }
			static void _TASK_CAR_DRIVE_WANDER(Ped ped, Vehicle vehicle, float speed, unsigned int drivingStyle) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_CAR_DRIVE_WANDER, ped, vehicle, speed, drivingStyle); }
			static void _TASK_CAR_MISSION(Ped ped, Vehicle vehicle, unsigned int targetEntity, unsigned int missionType, float speed, unsigned int drivingStyle, unsigned int unknown6_10, unsigned int unknown7_5) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_CAR_MISSION, ped, vehicle, targetEntity, missionType, speed, drivingStyle, unknown6_10, unknown7_5); }
			static void _TASK_CAR_MISSION_COORS_TARGET(Ped ped, Vehicle vehicle, float x, float y, float z, unsigned int unknown0_4, float speed, unsigned int unknown2_1, unsigned int unknown3_5, unsigned int unknown4_10) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_CAR_MISSION_COORS_TARGET, ped, vehicle, x, y, z, unknown0_4, speed, unknown2_1, unknown3_5, unknown4_10); }
			static void _TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC(Ped ped, Vehicle vehicle, float x, float y, float z, unsigned int unknown0_4, float speed, unsigned int unknown2_1, unsigned int unknown3_5, unsigned int unknown4_10) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_CAR_MISSION_COORS_TARGET_NOT_AGAINST_TRAFFIC, ped, vehicle, x, y, z, unknown0_4, speed, unknown2_1, unknown3_5, unknown4_10); }
			static void _TASK_CAR_MISSION_NOT_AGAINST_TRAFFIC(Ped ped, Vehicle vehicle, unsigned int targetEntity, unsigned int missionType, float speed, unsigned int drivingStyle, unsigned int unknown6_10, unsigned int unknown7_5) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_CAR_MISSION_NOT_AGAINST_TRAFFIC, ped, vehicle, targetEntity, missionType, speed, drivingStyle, unknown6_10, unknown7_5); }
			static void _TASK_CAR_MISSION_PED_TARGET(Ped ped, Vehicle vehicle, Ped target, unsigned int unknown0_4, float speed, unsigned int unknown2_1, unsigned int unknown3_5, unsigned int unknown4_10) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_CAR_MISSION_PED_TARGET, ped, vehicle, target, unknown0_4, speed, unknown2_1, unknown3_5, unknown4_10); }
			static void _TASK_CAR_MISSION_PED_TARGET_NOT_AGAINST_TRAFFIC(Ped ped, ScriptAny Unk152, ScriptAny Unk153, ScriptAny Unk154, ScriptAny Unk155, ScriptAny Unk156, ScriptAny Unk157, ScriptAny Unk158) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_CAR_MISSION_PED_TARGET_NOT_AGAINST_TRAFFIC, ped, Unk152, Unk153, Unk154, Unk155, Unk156, Unk157, Unk158); }
			static void _TASK_CAR_TEMP_ACTION(Ped ped, Vehicle vehicle, unsigned int action, unsigned int duration) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_CAR_TEMP_ACTION, ped, vehicle, action, duration); }
			static void _TASK_CHAR_ARREST_CHAR(Ped ped0, Ped ped1) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_CHAR_ARREST_CHAR, ped0, ped1); }
			static void _TASK_CHAR_SLIDE_TO_COORD(Ped ped, ScriptAny Unk159, ScriptAny Unk160, ScriptAny Unk161, ScriptAny Unk162, ScriptAny Unk163) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_CHAR_SLIDE_TO_COORD, ped, Unk159, Unk160, Unk161, Unk162, Unk163); }
			static void _TASK_CHAR_SLIDE_TO_COORD_AND_PLAY_ANIM(Ped ped, ScriptAny Unk164, ScriptAny Unk165, ScriptAny Unk166, ScriptAny Unk167, ScriptAny Unk168, ScriptAny Unk169, ScriptAny Unk170, ScriptAny Unk171, ScriptAny Unk172, ScriptAny Unk173, ScriptAny Unk174, ScriptAny Unk175, ScriptAny Unk176) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_CHAR_SLIDE_TO_COORD_AND_PLAY_ANIM, ped, Unk164, Unk165, Unk166, Unk167, Unk168, Unk169, Unk170, Unk171, Unk172, Unk173, Unk174, Unk175, Unk176); }
			static void _TASK_CHAR_SLIDE_TO_COORD_HDG_RATE(Ped ped, ScriptAny Unk177, ScriptAny Unk178, ScriptAny Unk179, ScriptAny Unk180, ScriptAny Unk181, ScriptAny Unk182) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_CHAR_SLIDE_TO_COORD_HDG_RATE, ped, Unk177, Unk178, Unk179, Unk180, Unk181, Unk182); }
			static void _TASK_CHAT_WITH_CHAR(Ped ped, Ped pednext, b8 Unk183, b8 Unk184) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_CHAT_WITH_CHAR, ped, pednext, Unk183, Unk184); }
			static void _TASK_CLEAR_LOOK_AT(Ped ped) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_CLEAR_LOOK_AT, ped); }
			static void _TASK_CLIMB(Ped ped, b8 Unk185) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_CLIMB, ped, Unk185); }
			static void _TASK_CLIMB_LADDER(Ped ped, ScriptAny Unk186) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_CLIMB_LADDER, ped, Unk186); }
			static void _TASK_COMBAT(Ped ped, Ped target) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_COMBAT, ped, target); }
			static void _TASK_COMBAT_HATED_TARGETS_AROUND_CHAR(Ped ped, float radius) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_COMBAT_HATED_TARGETS_AROUND_CHAR, ped, radius); }
			static void _TASK_COMBAT_HATED_TARGETS_AROUND_CHAR_TIMED(Ped ped, float radius, unsigned int duration) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_COMBAT_HATED_TARGETS_AROUND_CHAR_TIMED, ped, radius, duration); }
			static void _TASK_COMBAT_HATED_TARGETS_IN_AREA(Ped ped, ScriptAny Unk187, ScriptAny Unk188, ScriptAny Unk189, ScriptAny Unk190) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_COMBAT_HATED_TARGETS_IN_AREA, ped, Unk187, Unk188, Unk189, Unk190); }
			static void _TASK_COMBAT_ROLL(Ped ped, ScriptAny Unk191) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_COMBAT_ROLL, ped, Unk191); }
			static void _TASK_COMBAT_TIMED(Ped ped, Ped target, unsigned int duration) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_COMBAT_TIMED, ped, target, duration); }
			static void _TASK_COWER(Ped ped) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_COWER, ped); }
			static void _TASK_DEAD(Ped ped) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_DEAD, ped); }
			static void _TASK_DESTROY_CAR(Ped ped, Vehicle car) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_DESTROY_CAR, ped, car); }
			static void _TASK_DIE(Ped ped) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_DIE, ped); }
			static void _TASK_DRIVE_BY(Ped ped, Ped pednext, int Unk192, float x, float y, float z, float angle, int Unk193, b8 Unk194, int Unk195) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_DRIVE_BY, ped, pednext, Unk192, x, y, z, angle, Unk193, Unk194, Unk195); }
			static void _TASK_DRIVE_POINT_ROUTE(Ped ped, int point, float radius) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_DRIVE_POINT_ROUTE, ped, point, radius); }
			static void _TASK_DRIVE_POINT_ROUTE_ADVANCED(Ped ped, ScriptAny Unk197, ScriptAny Unk198, ScriptAny Unk199, ScriptAny Unk200, ScriptAny Unk201) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_DRIVE_POINT_ROUTE_ADVANCED, ped, Unk197, Unk198, Unk199, Unk200, Unk201); }
			static void _TASK_DUCK(Ped ped, ScriptAny Unk202) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_DUCK, ped, Unk202); }
			static void _TASK_ENTER_CAR_AS_DRIVER(Ped ped, Vehicle vehicle, unsigned int duration) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_ENTER_CAR_AS_DRIVER, ped, vehicle, duration); }
			static void _TASK_ENTER_CAR_AS_PASSENGER(Ped ped, Vehicle vehicle, unsigned int duration, unsigned int seatIndex) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_ENTER_CAR_AS_PASSENGER, ped, vehicle, duration, seatIndex); }
			static void _TASK_EVERYONE_LEAVE_CAR(Vehicle vehicle) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_EVERYONE_LEAVE_CAR, vehicle); }
			static void _TASK_EXTEND_ROUTE(Ped ped, ScriptAny Unk203, ScriptAny Unk204) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_EXTEND_ROUTE, ped, Unk203, Unk204); }
			static void _TASK_FALL_AND_GET_UP(Ped ped, ScriptAny Unk205, ScriptAny Unk206) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_FALL_AND_GET_UP, ped, Unk205, Unk206); }
			static void _TASK_FLEE_CHAR_ANY_MEANS(Ped ped, ScriptAny Unk207, ScriptAny Unk208, ScriptAny Unk209, ScriptAny Unk210, ScriptAny Unk211, ScriptAny Unk212, ScriptAny Unk213) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_FLEE_CHAR_ANY_MEANS, ped, Unk207, Unk208, Unk209, Unk210, Unk211, Unk212, Unk213); }
			static void _TASK_FLUSH_ROUTE() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_FLUSH_ROUTE); }
			static void _TASK_FOLLOW_FOOTSTEPS(Ped ped, ScriptAny Unk214) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_FOLLOW_FOOTSTEPS, ped, Unk214); }
			static void _TASK_FOLLOW_NAV_MESH_AND_SLIDE_TO_COORD(Ped ped, float x, float y, float z, int Unk215, int Unk216, float Unk217, float angle) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_FOLLOW_NAV_MESH_AND_SLIDE_TO_COORD, ped, x, y, z, Unk215, Unk216, Unk217, angle); }
			static void _TASK_FOLLOW_NAV_MESH_TO_COORD(Ped ped, float x, float y, float z, unsigned int unknown0_2, unsigned int unknown1_minus1, float unknown2_1) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_FOLLOW_NAV_MESH_TO_COORD, ped, x, y, z, unknown0_2, unknown1_minus1, unknown2_1); }
			static void _TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP(Ped ped, float x, float y, float z, unsigned int unknown0_2, unsigned int unknown1_minus1, float unknown2_1) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_FOLLOW_NAV_MESH_TO_COORD_NO_STOP, ped, x, y, z, unknown0_2, unknown1_minus1, unknown2_1); }
			static void _TASK_GET_OFF_BOAT(Ped ped, int timeout) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_GET_OFF_BOAT, ped, timeout); }
			static void _TASK_GOTO_CAR(Ped ped, ScriptAny Unk221, ScriptAny Unk222, ScriptAny Unk223) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_GOTO_CAR, ped, Unk221, Unk222, Unk223); }
			static void _TASK_GOTO_CHAR_AIMING(Ped ped, ScriptAny Unk224, ScriptAny Unk225, ScriptAny Unk226) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_GOTO_CHAR_AIMING, ped, Unk224, Unk225, Unk226); }
			static void _TASK_GOTO_CHAR_OFFSET(Ped ped, Ped target, unsigned int duration, float offsetRight, float offsetFront) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_GOTO_CHAR_OFFSET, ped, target, duration, offsetRight, offsetFront); }
			static void _TASK_GO_STRAIGHT_TO_COORD(Ped ped, float x, float y, float z, unsigned int unknown2, unsigned int unknown45000) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_GO_STRAIGHT_TO_COORD, ped, x, y, z, unknown2, unknown45000); }
			static void _TASK_GO_STRAIGHT_TO_COORD_RELATIVE_TO_CAR(Ped ped, ScriptAny Unk227, ScriptAny Unk228, ScriptAny Unk229, ScriptAny Unk230, ScriptAny Unk231, ScriptAny Unk232) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_GO_STRAIGHT_TO_COORD_RELATIVE_TO_CAR, ped, Unk227, Unk228, Unk229, Unk230, Unk231, Unk232); }
			static void _TASK_GO_TO_CHAR(Ped ped, ScriptAny Unk233, ScriptAny Unk234, ScriptAny Unk235) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_GO_TO_CHAR, ped, Unk233, Unk234, Unk235); }
			static void _TASK_GO_TO_COORD_ANY_MEANS(Ped ped, ScriptAny Unk236, ScriptAny Unk237, ScriptAny Unk238, ScriptAny Unk239, ScriptAny Unk240) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_GO_TO_COORD_ANY_MEANS, ped, Unk236, Unk237, Unk238, Unk239, Unk240); }
			static void _TASK_GO_TO_COORD_WHILE_AIMING(Ped ped, ScriptAny Unk241, ScriptAny Unk242, ScriptAny Unk243, ScriptAny Unk244, ScriptAny Unk245, ScriptAny Unk246, ScriptAny Unk247, ScriptAny Unk248, ScriptAny Unk249, ScriptAny Unk250, ScriptAny Unk251) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_GO_TO_COORD_WHILE_AIMING, ped, Unk241, Unk242, Unk243, Unk244, Unk245, Unk246, Unk247, Unk248, Unk249, Unk250, Unk251); }
			static void _TASK_GO_TO_COORD_WHILE_SHOOTING(Ped ped, ScriptAny Unk252, ScriptAny Unk253, ScriptAny Unk254, ScriptAny Unk255, ScriptAny Unk256, ScriptAny Unk257, ScriptAny Unk258, ScriptAny Unk259) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_GO_TO_COORD_WHILE_SHOOTING, ped, Unk252, Unk253, Unk254, Unk255, Unk256, Unk257, Unk258, Unk259); }
			static void _TASK_GO_TO_OBJECT(Ped ped, ScriptAny Unk260, ScriptAny Unk261, ScriptAny Unk262) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_GO_TO_OBJECT, ped, Unk260, Unk261, Unk262); }
			static void _TASK_GUARD_ANGLED_DEFENSIVE_AREA(Ped ped, ScriptAny Unk263, ScriptAny Unk264, ScriptAny Unk265, ScriptAny Unk266, ScriptAny Unk267, ScriptAny Unk268, ScriptAny Unk269, ScriptAny Unk270, ScriptAny Unk271, ScriptAny Unk272, ScriptAny Unk273, ScriptAny Unk274, ScriptAny Unk275) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_GUARD_ANGLED_DEFENSIVE_AREA, ped, Unk263, Unk264, Unk265, Unk266, Unk267, Unk268, Unk269, Unk270, Unk271, Unk272, Unk273, Unk274, Unk275); }
			static void _TASK_GUARD_ASSIGNED_DEFENSIVE_AREA(Ped ped, ScriptAny Unk276, ScriptAny Unk277, ScriptAny Unk278, ScriptAny Unk279, ScriptAny Unk280, ScriptAny Unk281) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_GUARD_ASSIGNED_DEFENSIVE_AREA, ped, Unk276, Unk277, Unk278, Unk279, Unk280, Unk281); }
			static void _TASK_GUARD_CURRENT_POSITION(Ped ped, float unknown0_15, float unknown1_10, unsigned int unknown2_1) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_GUARD_CURRENT_POSITION, ped, unknown0_15, unknown1_10, unknown2_1); }
			static void _TASK_GUARD_SPHERE_DEFENSIVE_AREA(Ped ped, ScriptAny Unk282, ScriptAny Unk283, ScriptAny Unk284, ScriptAny Unk285, ScriptAny Unk286, ScriptAny Unk287, ScriptAny Unk288, ScriptAny Unk289, ScriptAny Unk290, ScriptAny Unk291) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_GUARD_SPHERE_DEFENSIVE_AREA, ped, Unk282, Unk283, Unk284, Unk285, Unk286, Unk287, Unk288, Unk289, Unk290, Unk291); }
			static void _TASK_HANDS_UP(Ped ped, unsigned int duration) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_HANDS_UP, ped, duration); }
			static void _TASK_HELI_MISSION(Ped ped, Vehicle heli, unsigned int uk0_0, unsigned int uk1_0, float pX, float pY, float pZ, unsigned int uk2_4, float speed, unsigned int uk3_5, float uk4_minus1, unsigned int uk5_round_z_plus_1, unsigned int uk6_40) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_HELI_MISSION, ped, heli, uk0_0, uk1_0, pX, pY, pZ, uk2_4, speed, uk3_5, uk4_minus1, uk5_round_z_plus_1, uk6_40); }
			static void _TASK_JUMP(Ped ped, b8 flag) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_JUMP, ped, flag); }
			static void _TASK_LEAVE_ANY_CAR(Ped ped) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_LEAVE_ANY_CAR, ped); }
			static void _TASK_LEAVE_CAR(Ped ped, Vehicle vehicle) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_LEAVE_CAR, ped, vehicle); }
			static void _TASK_LEAVE_CAR_AND_FLEE(Ped ped, ScriptAny Unk292, ScriptAny Unk293, ScriptAny Unk294, ScriptAny Unk295) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_LEAVE_CAR_AND_FLEE, ped, Unk292, Unk293, Unk294, Unk295); }
			static void _TASK_LEAVE_CAR_DONT_CLOSE_DOOR(Ped ped, Vehicle vehicle) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_LEAVE_CAR_DONT_CLOSE_DOOR, ped, vehicle); }
			static void _TASK_LEAVE_CAR_IMMEDIATELY(Ped ped, Vehicle vehicle) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_LEAVE_CAR_IMMEDIATELY, ped, vehicle); }
			static void _TASK_LEAVE_CAR_IN_DIRECTION(Ped ped, Vehicle car, b8 direction) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_LEAVE_CAR_IN_DIRECTION, ped, car, direction); }
			static void _TASK_LEAVE_GROUP(Ped ped) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_LEAVE_GROUP, ped); }
			static void _TASK_LOOK_AT_CHAR(Ped ped, Ped targetPed, unsigned int duration, unsigned int unknown_0) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_LOOK_AT_CHAR, ped, targetPed, duration, unknown_0); }
			static void _TASK_LOOK_AT_COORD(Ped ped, float x, float y, float z, unsigned int duration, unsigned int unknown_0) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_LOOK_AT_COORD, ped, x, y, z, duration, unknown_0); }
			static void _TASK_LOOK_AT_OBJECT(Ped ped, Entity targetObject, unsigned int duration, unsigned int unknown_0) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_LOOK_AT_OBJECT, ped, targetObject, duration, unknown_0); }
			static void _TASK_LOOK_AT_VEHICLE(Ped ped, Vehicle targetVehicle, unsigned int duration, unsigned int unknown_0) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_LOOK_AT_VEHICLE, ped, targetVehicle, duration, unknown_0); }
			static void _TASK_MOBILE_CONVERSATION(Ped ped, ScriptAny Unk296) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_MOBILE_CONVERSATION, ped, Unk296); }
			static void _TASK_OPEN_DRIVER_DOOR(Ped ped, Vehicle vehicle, unsigned int unknown0) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_OPEN_DRIVER_DOOR, ped, vehicle, unknown0); }
			static void _TASK_OPEN_PASSENGER_DOOR(Ped ped, Vehicle vehicle, unsigned int seatIndex, unsigned int unknown0) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_OPEN_PASSENGER_DOOR, ped, vehicle, seatIndex, unknown0); }
			static void _TASK_PAUSE(Ped ped, unsigned int duration) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_PAUSE, ped, duration); }
			static void _TASK_PERFORM_SEQUENCE(Ped ped, TaskSequence taskSequence) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_PERFORM_SEQUENCE, ped, taskSequence); }
			static void _TASK_PERFORM_SEQUENCE_FROM_PROGRESS(Ped ped, ScriptAny Unk297, ScriptAny Unk298, ScriptAny Unk299) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_PERFORM_SEQUENCE_FROM_PROGRESS, ped, Unk297, Unk298, Unk299); }
			static void _TASK_PERFORM_SEQUENCE_LOCALLY(Ped ped, ScriptAny Unk300) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_PERFORM_SEQUENCE_LOCALLY, ped, Unk300); }
			static void _TASK_PICKUP_AND_CARRY_OBJECT(Ped ped, ScriptAny Unk301, ScriptAny Unk302, ScriptAny Unk303, ScriptAny Unk304, ScriptAny Unk305) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_PICKUP_AND_CARRY_OBJECT, ped, Unk301, Unk302, Unk303, Unk304, Unk305); }
			static void _TASK_PLAY_ANIM(Ped ped, ScriptAny Unk306, ScriptAny Unk307, ScriptAny Unk308, ScriptAny Unk309, ScriptAny Unk310, ScriptAny Unk311, ScriptAny Unk312, ScriptAny Unk313) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_PLAY_ANIM, ped, Unk306, Unk307, Unk308, Unk309, Unk310, Unk311, Unk312, Unk313); }
			static void _TASK_PLAY_ANIM_FACIAL(Ped ped, String^ Unk314, String^ Unk315, float Unk316, int Unk317, int Unk318, int Unk319)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_PLAY_ANIM_FACIAL, ped, ctx.marshal_as<const char*>(Unk314), ctx.marshal_as<const char*>(Unk315), Unk316, Unk317, Unk318, Unk319);
			}
			static void _TASK_PLAY_ANIM_NON_INTERRUPTABLE(Ped ped, String^ animname0, String^ animname1, float Unk320, int Unk321, int Unk322, int Unk323, int Unk324, int Unk325)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_PLAY_ANIM_NON_INTERRUPTABLE, ped, ctx.marshal_as<const char*>(animname0), ctx.marshal_as<const char*>(animname1), Unk320, Unk321, Unk322, Unk323, Unk324, Unk325);
			}
			static void _TASK_PLAY_ANIM_ON_CLONE(Ped ped, ScriptAny Unk326, ScriptAny Unk327, ScriptAny Unk328, ScriptAny Unk329, ScriptAny Unk330, ScriptAny Unk331, ScriptAny Unk332, ScriptAny Unk333) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_PLAY_ANIM_ON_CLONE, ped, Unk326, Unk327, Unk328, Unk329, Unk330, Unk331, Unk332, Unk333); }
			static void _TASK_PLAY_ANIM_READY_TO_BE_EXECUTED(Ped ped, ScriptAny Unk334, ScriptAny Unk335, ScriptAny Unk336) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_PLAY_ANIM_READY_TO_BE_EXECUTED, ped, Unk334, Unk335, Unk336); }
			static void _TASK_PLAY_ANIM_SECONDARY(Ped ped, ScriptAny Unk337, ScriptAny Unk338, ScriptAny Unk339, ScriptAny Unk340, ScriptAny Unk341, ScriptAny Unk342, ScriptAny Unk343, ScriptAny Unk344) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_PLAY_ANIM_SECONDARY, ped, Unk337, Unk338, Unk339, Unk340, Unk341, Unk342, Unk343, Unk344); }
			static void _TASK_PLAY_ANIM_SECONDARY_IN_CAR(Ped ped, ScriptAny Unk345, ScriptAny Unk346, ScriptAny Unk347, ScriptAny Unk348, ScriptAny Unk349, ScriptAny Unk350, ScriptAny Unk351, ScriptAny Unk352) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_PLAY_ANIM_SECONDARY_IN_CAR, ped, Unk345, Unk346, Unk347, Unk348, Unk349, Unk350, Unk351, Unk352); }
			static void _TASK_PLAY_ANIM_SECONDARY_NO_INTERRUPT(Ped ped, ScriptAny Unk353, ScriptAny Unk354, ScriptAny Unk355, ScriptAny Unk356, ScriptAny Unk357, ScriptAny Unk358, ScriptAny Unk359, ScriptAny Unk360) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_PLAY_ANIM_SECONDARY_NO_INTERRUPT, ped, Unk353, Unk354, Unk355, Unk356, Unk357, Unk358, Unk359, Unk360); }
			static void _TASK_PLAY_ANIM_SECONDARY_UPPER_BODY(Ped ped, ScriptAny Unk361, ScriptAny Unk362, ScriptAny Unk363, ScriptAny Unk364, ScriptAny Unk365, ScriptAny Unk366, ScriptAny Unk367, ScriptAny Unk368) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_PLAY_ANIM_SECONDARY_UPPER_BODY, ped, Unk361, Unk362, Unk363, Unk364, Unk365, Unk366, Unk367, Unk368); }
			static void _TASK_PLAY_ANIM_UPPER_BODY(Ped ped, ScriptAny Unk369, ScriptAny Unk370, ScriptAny Unk371, ScriptAny Unk372, ScriptAny Unk373, ScriptAny Unk374, ScriptAny Unk375, ScriptAny Unk376) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_PLAY_ANIM_UPPER_BODY, ped, Unk369, Unk370, Unk371, Unk372, Unk373, Unk374, Unk375, Unk376); }
			static void _TASK_PLAY_ANIM_WITH_ADVANCED_FLAGS(Ped ped, ScriptAny Unk377, ScriptAny Unk378, ScriptAny Unk379, ScriptAny Unk380, ScriptAny Unk381, ScriptAny Unk382, ScriptAny Unk383, ScriptAny Unk384, ScriptAny Unk385, ScriptAny Unk386, ScriptAny Unk387) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_PLAY_ANIM_WITH_ADVANCED_FLAGS, ped, Unk377, Unk378, Unk379, Unk380, Unk381, Unk382, Unk383, Unk384, Unk385, Unk386, Unk387); }
			static void _TASK_PLAY_ANIM_WITH_FLAGS(Ped ped, String^ animName, String^ animSet, float unknown0_8, unsigned int unknown1_0, unsigned int flags)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_PLAY_ANIM_WITH_FLAGS, ped, ctx.marshal_as<const char*>(animName), ctx.marshal_as<const char*>(animSet), unknown0_8, unknown1_0, flags);
			}
			static void _TASK_PUT_CHAR_DIRECTLY_INTO_COVER(ScriptAny Unk394, ScriptAny Unk395, ScriptAny Unk396, ScriptAny Unk397, ScriptAny Unk398) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_PUT_CHAR_DIRECTLY_INTO_COVER, Unk394, Unk395, Unk396, Unk397, Unk398); }
			static void _TASK_SEEK_COVER_FROM_PED(Ped ped, ScriptAny Unk399, ScriptAny Unk400) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_SEEK_COVER_FROM_PED, ped, Unk399, Unk400); }
			static void _TASK_SEEK_COVER_FROM_POS(Ped ped, ScriptAny Unk401, ScriptAny Unk402, ScriptAny Unk403, ScriptAny Unk404) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_SEEK_COVER_FROM_POS, ped, Unk401, Unk402, Unk403, Unk404); }
			static void _TASK_SEEK_COVER_TO_COORDS(Ped ped, ScriptAny Unk405, ScriptAny Unk406, ScriptAny Unk407, ScriptAny Unk408, ScriptAny Unk409, ScriptAny Unk410, ScriptAny Unk411) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_SEEK_COVER_TO_COORDS, ped, Unk405, Unk406, Unk407, Unk408, Unk409, Unk410, Unk411); }
			static void _TASK_SEEK_COVER_TO_COVER_POINT(Ped ped, ScriptAny Unk412, ScriptAny Unk413, ScriptAny Unk414, ScriptAny Unk415, ScriptAny Unk416) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_SEEK_COVER_TO_COVER_POINT, ped, Unk412, Unk413, Unk414, Unk415, Unk416); }
			static void _TASK_SEEK_COVER_TO_OBJECT(Ped ped, ScriptAny Unk417, ScriptAny Unk418, ScriptAny Unk419, ScriptAny Unk420, ScriptAny Unk421) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_SEEK_COVER_TO_OBJECT, ped, Unk417, Unk418, Unk419, Unk420, Unk421); }
			static void _TASK_SET_IGNORE_WEAPON_RANGE_FLAG(Ped ped, b8 ignore) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_SET_IGNORE_WEAPON_RANGE_FLAG, ped, ignore); }
			static void _TASK_SHAKE_FIST(Ped ped) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_SHAKE_FIST, ped); }
			static void _TASK_SHIMMY(Ped ped, ScriptAny Unk422) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_SHIMMY, ped, Unk422); }
			static void _TASK_SHOOT_AT_CHAR(Ped shooter, Ped victim, int time, int shootmode) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_SHOOT_AT_CHAR, shooter, victim, time, shootmode); }
			static void _TASK_SHOOT_AT_COORD(Ped ped, ScriptAny Unk423, ScriptAny Unk424, ScriptAny Unk425, ScriptAny Unk426, ScriptAny Unk427) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_SHOOT_AT_COORD, ped, Unk423, Unk424, Unk425, Unk426, Unk427); }
			static void _TASK_SHUFFLE_TO_NEXT_CAR_SEAT(Ped ped, ScriptAny Unk428) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_SHUFFLE_TO_NEXT_CAR_SEAT, ped, Unk428); }
			static void _TASK_SIT_DOWN(Ped ped, ScriptAny Unk429, ScriptAny Unk430, ScriptAny Unk431) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_SIT_DOWN, ped, Unk429, Unk430, Unk431); }
			static void _TASK_SIT_DOWN_INSTANTLY(Ped ped, ScriptAny Unk432, ScriptAny Unk433, ScriptAny Unk434) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_SIT_DOWN_INSTANTLY, ped, Unk432, Unk433, Unk434); }
			static void _TASK_SIT_DOWN_ON_NEAREST_OBJECT(Ped ped, ScriptAny Unk435, ScriptAny Unk436, ScriptAny Unk437, ScriptAny Unk438, ScriptAny Unk439, ScriptAny Unk440, ScriptAny Unk441, ScriptAny Unk442, ScriptAny Unk443) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_SIT_DOWN_ON_NEAREST_OBJECT, ped, Unk435, Unk436, Unk437, Unk438, Unk439, Unk440, Unk441, Unk442, Unk443); }
			static void _TASK_SIT_DOWN_ON_OBJECT(Ped ped, ScriptAny Unk444, ScriptAny Unk445, ScriptAny Unk446, ScriptAny Unk447, ScriptAny Unk448, ScriptAny Unk449, ScriptAny Unk450, ScriptAny Unk451, ScriptAny Unk452) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_SIT_DOWN_ON_OBJECT, ped, Unk444, Unk445, Unk446, Unk447, Unk448, Unk449, Unk450, Unk451, Unk452); }
			static void _TASK_SIT_DOWN_ON_SEAT(Ped ped, ScriptAny Unk453, ScriptAny Unk454, ScriptAny Unk455, ScriptAny Unk456, ScriptAny Unk457, ScriptAny Unk458, ScriptAny Unk459) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_SIT_DOWN_ON_SEAT, ped, Unk453, Unk454, Unk455, Unk456, Unk457, Unk458, Unk459); }
			static void _TASK_SMART_FLEE_CHAR(Ped ped, Ped fleeFromPed, float unknown0_100, unsigned int duration) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_SMART_FLEE_CHAR, ped, fleeFromPed, unknown0_100, duration); }
			static void _TASK_SMART_FLEE_CHAR_PREFERRING_PAVEMENTS(Ped ped, Ped fleeFromPed, float unknown0_100, unsigned int duration) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_SMART_FLEE_CHAR_PREFERRING_PAVEMENTS, ped, fleeFromPed, unknown0_100, duration); }
			static void _TASK_SMART_FLEE_POINT(Ped ped, float x, float y, float z, float unknown0_100, unsigned int duration) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_SMART_FLEE_POINT, ped, x, y, z, unknown0_100, duration); }
			static void _TASK_SMART_FLEE_POINT_PREFERRING_PAVEMENTS(Ped ped, float x, float y, float z, float radius, int time_prob) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_SMART_FLEE_POINT_PREFERRING_PAVEMENTS, ped, x, y, z, radius, time_prob); }
			static void _TASK_STAND_GUARD(Ped ped, float x, float y, float z, float Unk460, float Unk461, b8 Unk462, int Unk463) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_STAND_GUARD, ped, x, y, z, Unk460, Unk461, Unk462, Unk463); }
			static void _TASK_STAND_STILL(Ped ped, int duration) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_STAND_STILL, ped, duration); }
			static void _TASK_START_SCENARIO_AT_POSITION(Ped ped, ScriptAny Unk464, ScriptAny Unk465, ScriptAny Unk466, ScriptAny Unk467, ScriptAny Unk468) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_START_SCENARIO_AT_POSITION, ped, Unk464, Unk465, Unk466, Unk467, Unk468); }
			static void _TASK_START_SCENARIO_IN_PLACE(Ped ped, ScriptAny Unk469, ScriptAny Unk470) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_START_SCENARIO_IN_PLACE, ped, Unk469, Unk470); }
			static void _TASK_SWAP_WEAPON(Ped ped, unsigned int weapon) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_SWAP_WEAPON, ped, weapon); }
			static void _TASK_SWIM_TO_COORD(Ped ped, float x, float y, float z) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_SWIM_TO_COORD, ped, x, y, z); }
			static void _TASK_TIRED(Ped ped, int Unk471) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_TIRED, ped, Unk471); }
			static void _TASK_TOGGLE_DUCK(Ped ped, int Unk472) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_TOGGLE_DUCK, ped, Unk472); }
			static void _TASK_TOGGLE_PED_THREAT_SCANNER(Ped ped, b8 Unk473, b8 Unk474, b8 Unk475) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_TOGGLE_PED_THREAT_SCANNER, ped, Unk473, Unk474, Unk475); }
			static void _TASK_TURN_CHAR_TO_FACE_CHAR(Ped ped, Ped targetPed) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_TURN_CHAR_TO_FACE_CHAR, ped, targetPed); }
			static void _TASK_TURN_CHAR_TO_FACE_COORD(Ped ped, float x, float y, float z) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_TURN_CHAR_TO_FACE_COORD, ped, x, y, z); }
			static void _TASK_USE_MOBILE_PHONE(Ped ped, b8 use) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_USE_MOBILE_PHONE, ped, use); }
			static void _TASK_USE_MOBILE_PHONE_TIMED(Ped ped, unsigned int duration) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_USE_MOBILE_PHONE_TIMED, ped, duration); }
			static void _TASK_USE_NEAREST_SCENARIO_TO_POS(Ped ped, ScriptAny Unk476, ScriptAny Unk477, ScriptAny Unk478, ScriptAny Unk479) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_USE_NEAREST_SCENARIO_TO_POS, ped, Unk476, Unk477, Unk478, Unk479); }
			static void _TASK_USE_NEAREST_SCENARIO_TO_POS_WARP(Ped ped, ScriptAny Unk480, ScriptAny Unk481, ScriptAny Unk482, ScriptAny Unk483) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_USE_NEAREST_SCENARIO_TO_POS_WARP, ped, Unk480, Unk481, Unk482, Unk483); }
			static void _TASK_WANDER_STANDARD(Ped ped) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_WANDER_STANDARD, ped); }
			static void _TASK_WARP_CHAR_INTO_CAR_AS_DRIVER(Ped ped, Vehicle vehicle) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_WARP_CHAR_INTO_CAR_AS_DRIVER, ped, vehicle); }
			static void _TASK_WARP_CHAR_INTO_CAR_AS_PASSENGER(Ped ped, Vehicle vehicle, unsigned int seatIndex) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_WARP_CHAR_INTO_CAR_AS_PASSENGER, ped, vehicle, seatIndex); }
			static void ADD_HOSPITAL_RESTART(float x, float y, float z, float heading, int islandnum) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ADD_HOSPITAL_RESTART, x, y, z, heading, islandnum); }
			static void ADD_POLICE_RESTART(float x, float y, float z, float heading, int islandnum) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ADD_POLICE_RESTART, x, y, z, heading, islandnum); }
			static void ALTER_WANTED_LEVEL(Player playerIndex, unsigned int level) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ALTER_WANTED_LEVEL, playerIndex, level); }
			static void ALTER_WANTED_LEVEL_NO_DROP(Player playerIndex, unsigned int level) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ALTER_WANTED_LEVEL_NO_DROP, playerIndex, level); }
			static void APPLY_WANTED_LEVEL_CHANGE_NOW(Player playerIndex) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_APPLY_WANTED_LEVEL_CHANGE_NOW, playerIndex); }
			static void CLEAR_AREA_OF_COPS(float x, float y, float z, float radius) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_CLEAR_AREA_OF_COPS, x, y, z, radius); }
			static void CLEAR_WANTED_LEVEL(Player playerIndex) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_CLEAR_WANTED_LEVEL, playerIndex); }
			static void DISABLE_POLICE_SCANNER() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DISABLE_POLICE_SCANNER); }
			static void DONT_DISPATCH_COPS_FOR_PLAYER(int player, b8 dont) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DONT_DISPATCH_COPS_FOR_PLAYER, player, dont); }
			static void ENABLE_POLICE_SCANNER() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ENABLE_POLICE_SCANNER); }
			static void EXTEND_PATROL_ROUTE(ScriptAny Unk484, ScriptAny Unk485, ScriptAny Unk486, ScriptAny Unk487, ScriptAny Unk488) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_EXTEND_PATROL_ROUTE, Unk484, Unk485, Unk486, Unk487, Unk488); }
			static void FLUSH_PATROL_ROUTE() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_FLUSH_PATROL_ROUTE); }
			
			static void GET_CURRENT_BASIC_COP_MODEL([OutAttribute] unsigned int% pModel)
			{
				unsigned int p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_CURRENT_BASIC_COP_MODEL, &p);
				pModel = p;
			}
			static void GET_CURRENT_BASIC_POLICE_CAR_MODEL([OutAttribute] unsigned int% pModel)
			{
				unsigned int p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_CURRENT_BASIC_POLICE_CAR_MODEL, &p);
				pModel = p;
			}
			static void GET_CURRENT_COP_MODEL([OutAttribute] unsigned int% pModel)
			{
				unsigned int p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_CURRENT_COP_MODEL, &p);
				pModel = p;
			}
			static void GET_CURRENT_POLICE_CAR_MODEL([OutAttribute] unsigned int% pModel)
			{
				unsigned int p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_CURRENT_POLICE_CAR_MODEL, &p);
				pModel = p;
			}
			static void GET_MAX_WANTED_LEVEL([OutAttribute] unsigned int% pMaxWantedLevel)
			{
				unsigned int p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_MAX_WANTED_LEVEL, &p);
				pMaxWantedLevel = p;
			}
			static void MAINTAIN_FLASHING_STAR_AFTER_OFFENCE(int player, b8 maintain) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_MAINTAIN_FLASHING_STAR_AFTER_OFFENCE, player, maintain); }
			static void SET_CHAR_WANTED_BY_POLICE(Ped ped, b8 wanted) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_WANTED_BY_POLICE, ped, wanted); }
			static void SET_CREATE_RANDOM_COPS(b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CREATE_RANDOM_COPS, set); }
			static void SET_DITCH_POLICE_MODELS(b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_DITCH_POLICE_MODELS, set); }
			static void SET_EXTRA_HOSPITAL_RESTART_POINT(float x, float y, float z, float Unk489, float Unk490) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_EXTRA_HOSPITAL_RESTART_POINT, x, y, z, Unk489, Unk490); }
			static void SET_EXTRA_POLICE_STATION_RESTART_POINT(float x, float y, float z, float Unk491, float Unk492) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_EXTRA_POLICE_STATION_RESTART_POINT, x, y, z, Unk491, Unk492); }
			static void SET_FAKE_WANTED_CIRCLE(float x, float y, float radius) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_FAKE_WANTED_CIRCLE, x, y, radius); }
			static void SET_FAKE_WANTED_LEVEL(int lvl) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_FAKE_WANTED_LEVEL, lvl); }
			static void SET_MAX_WANTED_LEVEL(unsigned int lvl) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_MAX_WANTED_LEVEL, lvl); }
			static void SET_PED_WONT_ATTACK_PLAYER_WITHOUT_WANTED_LEVEL(Ped ped, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_PED_WONT_ATTACK_PLAYER_WITHOUT_WANTED_LEVEL, ped, set); }
			static void SET_POLICE_FOCUS_WILL_TRACK_CAR(Vehicle car, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_POLICE_FOCUS_WILL_TRACK_CAR, car, set); }
			static void SET_POLICE_IGNORE_PLAYER(Player playerIndex, b8 value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_POLICE_IGNORE_PLAYER, playerIndex, value); }
			static void SET_POLICE_RADAR_BLIPS(b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_POLICE_RADAR_BLIPS, set); }
			static void SET_WANTED_MULTIPLIER(float multiplier) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_WANTED_MULTIPLIER, multiplier); }
			static void SET_ZONE_NO_COPS(String^ name, b8 set)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_ZONE_NO_COPS, ctx.marshal_as<const char*>(name), set);
			}
			static void SPECIFY_SCRIPT_POPULATION_ZONE_PERCENTAGE_COPS(int percentage) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SPECIFY_SCRIPT_POPULATION_ZONE_PERCENTAGE_COPS, percentage); }
			static void STORE_WANTED_LEVEL(Player playerIndex, [OutAttribute] unsigned int% value)
			{
				unsigned int p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_STORE_WANTED_LEVEL, playerIndex, &p);
				value = p;
			}
			static void SWITCH_POLICE_HELIS(b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SWITCH_POLICE_HELIS, set); }
			static void TRIGGER_POLICE_REPORT(String^ name)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_TRIGGER_POLICE_REPORT, ctx.marshal_as<const char*>(name));
			}
			static void TRIGGER_VIGILANTE_CRIME(int id, float x, float y, float z) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TRIGGER_VIGILANTE_CRIME, id, x, y, z); }
			static void ABORT_ALL_GARAGE_ACTIVITY() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ABORT_ALL_GARAGE_ACTIVITY); }
			static void ACTIVATE_CHEAT(unsigned int cheat) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ACTIVATE_CHEAT, cheat); }
			static void ALLOW_AUTO_CONVERSATION_LOOKATS(Ped ped, b8 allow) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ALLOW_AUTO_CONVERSATION_LOOKATS, ped, allow); }
			static void ALLOW_EMERGENCY_SERVICES(b8 allow) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ALLOW_EMERGENCY_SERVICES, allow); }
			static void ALLOW_GAME_TO_PAUSE_FOR_STREAMING(b8 allow) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ALLOW_GAME_TO_PAUSE_FOR_STREAMING, allow); }
			static void ALLOW_GANG_RELATIONSHIPS_TO_BE_CHANGED_BY_NEXT_COMMAND(b8 value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ALLOW_GANG_RELATIONSHIPS_TO_BE_CHANGED_BY_NEXT_COMMAND, value); }
			static void ALLOW_MULTIPLE_DRIVEBY_PICKUPS(b8 allow) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ALLOW_MULTIPLE_DRIVEBY_PICKUPS, allow); }
			static void ALLOW_REACTION_ANIMS(Ped ped, b8 allow) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ALLOW_REACTION_ANIMS, ped, allow); }
			static void ALLOW_SCENARIO_PEDS_TO_BE_RETURNED_BY_NEXT_COMMAND(b8 value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ALLOW_SCENARIO_PEDS_TO_BE_RETURNED_BY_NEXT_COMMAND, value); }
			static void ALLOW_STUNT_JUMPS_TO_TRIGGER(b8 allow) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ALLOW_STUNT_JUMPS_TO_TRIGGER, allow); }
			static void CANCEL_OVERRIDE_RESTART() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_CANCEL_OVERRIDE_RESTART); }
			static void CLEAR_ANGLED_AREA_OF_CARS(float x0, float y0, float z0, float x1, float y1, float z1, float radius) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_CLEAR_ANGLED_AREA_OF_CARS, x0, y0, z0, x1, y1, z1, radius); }
			static void CLEAR_AREA(float x, float y, float z, float radius, b8 unknown) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_CLEAR_AREA, x, y, z, radius, unknown); }
			static void CLEAR_AREA_OF_CARS(float x, float y, float z, float radius) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_CLEAR_AREA_OF_CARS, x, y, z, radius); }
			static void CLEAR_AREA_OF_CHARS(float x, float y, float z, float radius) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_CLEAR_AREA_OF_CHARS, x, y, z, radius); }
			static void CLEAR_AREA_OF_OBJECTS(float x, float y, float z, float radius) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_CLEAR_AREA_OF_OBJECTS, x, y, z, radius); }
			//static void CLEAR_BIT(int* val, int bit) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_CLEAR_BIT, val, bit); }
			static void CLEAR_PED_NON_CREATION_AREA() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_CLEAR_PED_NON_CREATION_AREA); }
			static void CLEAR_PED_NON_REMOVAL_AREA() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_CLEAR_PED_NON_REMOVAL_AREA); }
			static void CLEAR_SCRIPTED_CONVERSION_CENTRE() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_CLEAR_SCRIPTED_CONVERSION_CENTRE); }
			static void DISABLE_PAUSE_MENU(b8 disabled) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DISABLE_PAUSE_MENU, disabled); }
			static void DONT_DISPLAY_LOADING_ON_FADE_THIS_FRAME() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DONT_DISPLAY_LOADING_ON_FADE_THIS_FRAME); }
			static void DO_AUTO_SAVE() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DO_AUTO_SAVE); }
			static void ENABLE_FANCY_WATER(b8 enable) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ENABLE_FANCY_WATER, enable); }
			static void ENABLE_SAVE_HOUSE(unsigned int savehouse, b8 enable) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ENABLE_SAVE_HOUSE, savehouse, enable); }
			static void FAIL_KILL_FRENZY() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_FAIL_KILL_FRENZY); }
			static void FIND_NEAREST_COLLECTABLE_BIN_BAGS(float x, float y, float z) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_FIND_NEAREST_COLLECTABLE_BIN_BAGS, x, y, z); }
			static void FIND_STREET_NAME_AT_POSITION(float pX, float pY, float pZ, [OutAttribute] unsigned int& strHash0, [OutAttribute] unsigned int% strHash1)
			{
				unsigned int p1, p2;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_FIND_STREET_NAME_AT_POSITION, pX, pY, pZ, &p1, &p2);
				strHash0 = p1;
				strHash1 = p2;
			}
			static void FIX_AMBIENCE_ORIENTATION(b8 fix) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_FIX_AMBIENCE_ORIENTATION, fix); }
			static void FIX_SCRIPT_MIC_TO_CURRENT_POSISITION() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_FIX_SCRIPT_MIC_TO_CURRENT_POSISITION); }
			static void FLUSH_ALL_OUT_OF_DATE_RADAR_BLIPS_FROM_MISSION_CLEANUP_LIST() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_FLUSH_ALL_OUT_OF_DATE_RADAR_BLIPS_FROM_MISSION_CLEANUP_LIST); }
			static void FLUSH_COVER_BLOCKING_AREAS() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_FLUSH_COVER_BLOCKING_AREAS); }
			static void FLUSH_SCENARIO_BLOCKING_AREAS() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_FLUSH_SCENARIO_BLOCKING_AREAS); }
			static void FORCE_HIGH_LOD(b8 force) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_FORCE_HIGH_LOD, force); }
			static void FORCE_LOADING_SCREEN(b8 force) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_FORCE_LOADING_SCREEN, force); }
			static void FORCE_POPULATION_INIT() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_FORCE_POPULATION_INIT); }
			static void FORCE_WEATHER(unsigned int weather) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_FORCE_WEATHER, weather); }
			static void FORCE_WEATHER_NOW(unsigned int weather) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_FORCE_WEATHER_NOW, weather); }
			static void FORCE_WIND(float wind) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_FORCE_WIND, wind); }
			static void GET_ANGLE_BETWEEN_2D_VECTORS(float x1, float y1, float x2, float y2, [OutAttribute] float% pResult)
			{
				float p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_ANGLE_BETWEEN_2D_VECTORS, x1, y1, x2, y2, &p);
				pResult = p;
			}
			static void GET_CURRENT_DATE([OutAttribute] unsigned int% day, [OutAttribute] unsigned int% month)
			{
				unsigned int p1, p2;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_CURRENT_DATE, &p1, &p2);
				day = p1;
				month = p2;
			}
			static void GET_CURRENT_WEATHER([OutAttribute] int% pWeather)
			{
				int p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_CURRENT_WEATHER, &p);
				pWeather = p;
			}
			static void GET_CURRENT_WEATHER_FULL([OutAttribute] int% weatherparam0, [OutAttribute] int% weatherparam1, [OutAttribute] int% weatherparam2)
			{
				int p1, p2, p3;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_CURRENT_WEATHER_FULL, &p1, &p2, &p3);
				weatherparam0 = p1;
				weatherparam1 = p2;
				weatherparam2 = p3;
			}
			static void GET_DISTANCE_BETWEEN_COORDS_2D(float x1, float y1, float x2, float y2, [OutAttribute] float% pDist)
			{
				float p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_DISTANCE_BETWEEN_COORDS_2D, x1, y1, x2, y2, &p);
				pDist = p;
			}
			static void GET_DISTANCE_BETWEEN_COORDS_3D(float x1, float y1, float z1, float x2, float y2, float z2, [OutAttribute] float% pDist)
			{
				float p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_DISTANCE_BETWEEN_COORDS_3D, x1, y1, z1, x2, y2, z2, &p);
				pDist = p;
			}
			static void GET_FRONTEND_DESIGN_VALUE(int frontendid, [OutAttribute] float% Unk499, [OutAttribute] float% Unk500)
			{
				float p1, p2;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_FRONTEND_DESIGN_VALUE, frontendid, &p1, &p2);
				Unk499 = p1;
				Unk500 = p2;
			}
			static void GET_HEADING_FROM_VECTOR_2D(float x, float y, [OutAttribute] float% pHeading)
			{
				float p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_HEADING_FROM_VECTOR_2D, x, y, &p);
				pHeading = p;
			}
			static void GET_HUD_COLOUR(unsigned int type, [OutAttribute] int% pR, [OutAttribute] int% pG, [OutAttribute] int% pB, [OutAttribute] int% pA)
			{
				int r, g, b, a;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_HUD_COLOUR, type, &r, &g, &b, &a);
				pR = r;
				pG = g;
				pB = b;
				pA = a;
			}
			static void GET_SEQUENCE_PROGRESS(int seq, [OutAttribute] int% progress)
			{
				int p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_SEQUENCE_PROGRESS, seq, &p);
				progress = p;
			}
			static void LIMIT_ANGLE(float angle, [OutAttribute] float% anglelimited)
			{
				float p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_LIMIT_ANGLE, angle, &p);
				anglelimited = p;
			}
			static void LIMIT_TWO_PLAYER_DISTANCE(float distance) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_LIMIT_TWO_PLAYER_DISTANCE, distance); }
			static void LOCK_LAZLOW_STATION() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_LOCK_LAZLOW_STATION); }
			static void OVERRIDE_FREEZE_FLAGS(b8 Unk504) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_OVERRIDE_FREEZE_FLAGS, Unk504); }
			static void OVERRIDE_NEXT_RESTART(float x, float y, float z, float heading) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_OVERRIDE_NEXT_RESTART, x, y, z, heading); }
			static void PICKUPS_PASS_TIME(unsigned int time) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_PICKUPS_PASS_TIME, time); }
			static void POPULATE_NOW() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_POPULATE_NOW); }
			static void PRIORITIZE_STREAMING_REQUEST() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_PRIORITIZE_STREAMING_REQUEST); }
			static void PROCESS_MISSION_DELETION_LIST() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_PROCESS_MISSION_DELETION_LIST); }
			static void REGISTER_BEST_POSITION(int Unk505, int position) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_REGISTER_BEST_POSITION, Unk505, position); }
			static void REGISTER_MISSION_PASSED(String^ str)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_REGISTER_MISSION_PASSED, ctx.marshal_as<const char*>(str));
			}
			static void REGISTER_ODDJOB_MISSION_PASSED() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_REGISTER_ODDJOB_MISSION_PASSED); }
			static void REGISTER_TRACK_NUMBER(int number) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_REGISTER_TRACK_NUMBER, number); }
			static void RELEASE_TEXTURE(Texture texture) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_RELEASE_TEXTURE, texture); }
			static void RELEASE_TIME_OF_DAY() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_RELEASE_TIME_OF_DAY); }
			static void RELEASE_WEATHER() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_RELEASE_WEATHER); }
			static void REMOVE_SCRIPT_MIC() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_REMOVE_SCRIPT_MIC); }
			static void RENDER_RACE_TRACK(b8 render) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_RENDER_RACE_TRACK, render); }
			static void REPORT_TAGGED_RADIO_TRACK(int TrackTextId) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_REPORT_TAGGED_RADIO_TRACK, TrackTextId); }
			static void SAVE_SETTINGS() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SAVE_SETTINGS); }
			static void SET_ALLOW_DUMMY_CONVERSIONS(b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_ALLOW_DUMMY_CONVERSIONS, set); }
			//static void SET_BIT(int* val, int bit) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_BIT, val, bit); }
			//static void SET_BITS_IN_RANGE(int* Unk506, int rangebegin, int rangeend, int val) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_BITS_IN_RANGE, Unk506, rangebegin, rangeend, val); }
			static void SET_CLEAR_HELP_IN_MISSION_CLEANUP(b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CLEAR_HELP_IN_MISSION_CLEANUP, set); }
			static void SET_CLEAR_MANIFOLDS(b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CLEAR_MANIFOLDS, set); }
			static void SET_COLLECTABLE1_TOTAL(int total) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_COLLECTABLE1_TOTAL, total); }
			static void SET_CREDITS_TO_RENDER_BEFORE_FADE(b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CREDITS_TO_RENDER_BEFORE_FADE, set); }
			static void SET_DEFAULT_GLOBAL_INSTANCE_PRIORITY() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_DEFAULT_GLOBAL_INSTANCE_PRIORITY); }
			static void SET_FADE_IN_AFTER_LOAD(b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_FADE_IN_AFTER_LOAD, set); }
			static void SET_FILTER_SAVE_SETTING(int filterid, int setting) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_FILTER_SAVE_SETTING, filterid, setting); }
			static void SET_GLOBAL_INSTANCE_PRIORITY(int priority) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_GLOBAL_INSTANCE_PRIORITY, priority); }
			static void SET_GLOBAL_RENDER_FLAGS(b8 Unk507, b8 Unk508, b8 Unk509, b8 Unk510) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_GLOBAL_RENDER_FLAGS, Unk507, Unk508, Unk509, Unk510); }
			static void SET_GRAVITY_OFF(b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_GRAVITY_OFF, set); }
			static void SET_GFWL_HAS_SAFE_HOUSE(unsigned int ukn) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_GFWL_HAS_SAFE_HOUSE, ukn); }
			static void SET_GUNSHOT_SENSE_RANGE_FOR_RIOT2(float range) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_GUNSHOT_SENSE_RANGE_FOR_RIOT2, range); }
			static void SET_MINIGAME_IN_PROGRESS(b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_MINIGAME_IN_PROGRESS, set); }
			static void SET_MISSION_FLAG(b8 isMission) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_MISSION_FLAG, isMission); }
			static void SET_MISSION_PASSED_CASH(b8 add, int cash, int Unk511) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_MISSION_PASSED_CASH, add, cash, Unk511); }
			static void SET_MISSION_PICKUP_SOUND(unsigned int model, String^ SoundName)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_MISSION_PICKUP_SOUND, model, ctx.marshal_as<const char*>(SoundName));
			}
			static void SET_MISSION_RESPECT_TOTAL(float respect) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_MISSION_RESPECT_TOTAL, respect); }
			static void SET_NEXT_DESIRED_MOVE_STATE(int state) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_NEXT_DESIRED_MOVE_STATE, state); }
			static void SET_PHYS_CCD_HANDLES_ROTATION(b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_PHYS_CCD_HANDLES_ROTATION, set); }
			static void SET_RAILTRACK_RESISTANCE_MULT(float resistance) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_RAILTRACK_RESISTANCE_MULT, resistance); }
			static void SET_RANDOM_SEED(int seed) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_RANDOM_SEED, seed); }
			static void SET_ROT_ORDER(int order) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_ROT_ORDER, order); }
			static void SET_SCRIPTED_CONVERSION_CENTRE(float x, float y, float z) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_SCRIPTED_CONVERSION_CENTRE, x, y, z); }
			static void SET_SEQUENCE_TO_REPEAT(int seq, int repeat) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_SEQUENCE_TO_REPEAT, seq, repeat); }
			static void SET_SLEEP_MODE_ACTIVE(b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_SLEEP_MODE_ACTIVE, set); }
			static void SET_SNIPER_ZOOM_FACTOR(float factor) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_SNIPER_ZOOM_FACTOR, factor); }
			static void SET_TAXI_GARAGE_RADIO_STATE(b8 radiostate) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_TAXI_GARAGE_RADIO_STATE, radiostate); }
			static void SET_TOTAL_NUMBER_OF_MISSIONS(float floatstatval) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_TOTAL_NUMBER_OF_MISSIONS, floatstatval); }
			static void SET_USE_POOL_GAME_PHYSICS_SETTINGS(b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_USE_POOL_GAME_PHYSICS_SETTINGS, set); }
			static void START_CREDITS() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_START_CREDITS); }
			static void START_FIRING_AMNESTY() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_START_FIRING_AMNESTY); }
			static void START_GPS_RACE_TRACK(int trackid) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_START_GPS_RACE_TRACK, trackid); }
			static void START_KILL_FRENZY(String^ gxtname, int Unk512, int Unk513, int Unk514, int Unk515, int Unk516, int Unk517, int Unk518, b8 Unk519)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_START_KILL_FRENZY, ctx.marshal_as<const char*>(gxtname), Unk512, Unk513, Unk514, Unk515, Unk516, Unk517, Unk518, Unk519);
			}
			static void STOP_CREDITS() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_STOP_CREDITS); }
			static void SUPPRESS_FADE_IN_AFTER_DEATH_ARREST(b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SUPPRESS_FADE_IN_AFTER_DEATH_ARREST, set); }
			static void SWITCH_AMBIENT_PLANES(b8 on) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SWITCH_AMBIENT_PLANES, on); }
			static void SWITCH_GARBAGE_TRUCKS(b8 on) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SWITCH_GARBAGE_TRUCKS, on); }
			static void SWITCH_MAD_DRIVERS(b8 on) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SWITCH_MAD_DRIVERS, on); }
			static void SWITCH_OFF_WAYPOINT() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SWITCH_OFF_WAYPOINT); }
			static void SWITCH_RANDOM_BOATS(b8 on) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SWITCH_RANDOM_BOATS, on); }
			static void SWITCH_RANDOM_TRAINS(b8 on) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SWITCH_RANDOM_TRAINS, on); }
			static void SWITCH_STREAMING(b8 on) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SWITCH_STREAMING, on); }
			static void SYNCH_AMBIENT_PLANES(int Unk520, int Unk521) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SYNCH_AMBIENT_PLANES, Unk520, Unk521); }
			static void TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME(String^ name)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_TERMINATE_ALL_SCRIPTS_WITH_THIS_NAME, ctx.marshal_as<const char*>(name));
			}
			static void UNLOCK_GENERIC_NEWS_STORY(int StoryId) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_UNLOCK_GENERIC_NEWS_STORY, StoryId); }
			static void UNLOCK_LAZLOW_STATION() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_UNLOCK_LAZLOW_STATION); }
			static void UNLOCK_MISSION_NEWS_STORY(int id) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_UNLOCK_MISSION_NEWS_STORY, id); }
			static void ADD_LINE_TO_CONVERSATION(ScriptAny Unk522, ScriptAny Unk523, ScriptAny Unk524, ScriptAny Unk525, ScriptAny Unk526) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ADD_LINE_TO_CONVERSATION, Unk522, Unk523, Unk524, Unk525, Unk526); }
			static void ADD_LINE_TO_SCRIPTED_CONVERSATION(unsigned int conversation, int Unk527, int Unk528) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ADD_LINE_TO_SCRIPTED_CONVERSATION, conversation, Unk527, Unk528); }
			static void ADD_NEW_CONVERSATION_SPEAKER(int id, int Unk529, [OutAttribute] int% Unk530)
			{
				int p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_ADD_NEW_CONVERSATION_SPEAKER, id, Unk529, &p);
				Unk530 = p;
			}
			static void ADD_NEW_FRONTEND_CONVERSATION_SPEAKER(int Unk531, int Unk532) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ADD_NEW_FRONTEND_CONVERSATION_SPEAKER, Unk531, Unk532); }
			static void AMBIENT_AUDIO_BANK_NO_LONGER_NEEDED() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_AMBIENT_AUDIO_BANK_NO_LONGER_NEEDED); }
			static void DISABLE_FRONTEND_RADIO() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DISABLE_FRONTEND_RADIO); }
			static void DISABLE_GPS(b8 disable) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DISABLE_GPS, disable); }
			static void DONT_ABORT_CAR_CONVERSATIONS(b8 flag0, b8 flag1) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DONT_ABORT_CAR_CONVERSATIONS, flag0, flag1); }
			static void ENABLE_CHASE_AUDIO(b8 enable) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ENABLE_CHASE_AUDIO, enable); }
			static void ENABLE_FRONTEND_RADIO() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ENABLE_FRONTEND_RADIO); }
			static void FORCE_INITIAL_PLAYER_STATION(String^ stationName)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_FORCE_INITIAL_PLAYER_STATION, ctx.marshal_as<const char*>(stationName));
			}
			static void FORCE_NOISE_OFF(b8 off) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_FORCE_NOISE_OFF, off); }
			static void FORCE_RADIO_TRACK(String^ radiostation, String^ trackname, int Unk533, int Unk534)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_FORCE_RADIO_TRACK, ctx.marshal_as<const char*>(radiostation), ctx.marshal_as<const char*>(trackname), Unk533, Unk534);
			}
			static void FREEZE_RADIO_STATION(String^ stationName)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_FREEZE_RADIO_STATION, ctx.marshal_as<const char*>(stationName));
			}
			static void GET_SOUND_LEVEL_AT_COORDS(Ped ped, float x, float y, float z, [OutAttribute] int% level)
			{
				int p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_SOUND_LEVEL_AT_COORDS, ped, x, y, z, &p);
				level = p;
			}
			static void HANDLE_AUDIO_ANIM_EVENT(Ped ped, String^ AudioAnimEventName)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_HANDLE_AUDIO_ANIM_EVENT, ped, ctx.marshal_as<const char*>(AudioAnimEventName));
			}
			static void HELI_AUDIO_SHOULD_SKIP_STARTUP(Vehicle heli, b8 skip) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_HELI_AUDIO_SHOULD_SKIP_STARTUP, heli, skip); }
			static void MISSION_AUDIO_BANK_NO_LONGER_NEEDED() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_MISSION_AUDIO_BANK_NO_LONGER_NEEDED); }
			static void MUTE_GAMEWORLD_AND_POSITIONED_RADIO_FOR_TV(b8 mute) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_MUTE_GAMEWORLD_AND_POSITIONED_RADIO_FOR_TV, mute); }
			static void MUTE_GAMEWORLD_AUDIO(b8 mute) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_MUTE_GAMEWORLD_AUDIO, mute); }
			static void MUTE_POSITIONED_RADIO(b8 mute) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_MUTE_POSITIONED_RADIO, mute); }
			static void NEW_SCRIPTED_CONVERSATION() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_NEW_SCRIPTED_CONVERSATION); }
			static void PAUSE_SCRIPTED_CONVERSATION(b8 pause) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_PAUSE_SCRIPTED_CONVERSATION, pause); }
			static void PLAY_AUDIO_EVENT(String^ name)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_PLAY_AUDIO_EVENT, ctx.marshal_as<const char*>(name));
			}
			static void PLAY_AUDIO_EVENT_FROM_OBJECT(String^ EventName, Entity obj)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_PLAY_AUDIO_EVENT_FROM_OBJECT, ctx.marshal_as<const char*>(EventName), obj);
			}
			static void PLAY_AUDIO_EVENT_FROM_PED(String^ name, Ped ped)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_PLAY_AUDIO_EVENT_FROM_PED, ctx.marshal_as<const char*>(name), ped);
			}
			static void PLAY_AUDIO_EVENT_FROM_VEHICLE(String^ name, Vehicle veh)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_PLAY_AUDIO_EVENT_FROM_VEHICLE, ctx.marshal_as<const char*>(name), veh);
			}
			static void PLAY_FIRE_SOUND_FROM_POSITION(int sound_id, float x, float y, float z) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_PLAY_FIRE_SOUND_FROM_POSITION, sound_id, x, y, z); }
			static void PLAY_SCRIPTED_CONVERSATION_FRONTEND(b8 play) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_PLAY_SCRIPTED_CONVERSATION_FRONTEND, play); }
			static void PLAY_SOUND(int SoundId, String^ SoundName)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_PLAY_SOUND, SoundId, (char*)ctx.marshal_as<const char*>(SoundName));
			}
			static void PLAY_SOUND_FROM_OBJECT(int sound_id, String^ name, Entity obj)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_PLAY_SOUND_FROM_OBJECT, sound_id, (char*)ctx.marshal_as<const char*>(name), obj);
			}
			static void PLAY_SOUND_FROM_PED(int SoundId, String^ SoundName, Ped ped)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_PLAY_SOUND_FROM_PED, SoundId, (char*)ctx.marshal_as<const char*>(SoundName), ped);
			}
			static void PLAY_SOUND_FROM_POSITION(int sound_id, String^ name, float x, float y, float z)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_PLAY_SOUND_FROM_POSITION, sound_id, (char*)ctx.marshal_as<const char*>(name), x, y, z);
			}
			static void PLAY_SOUND_FROM_VEHICLE(int SoundId, String^ SoundName, Vehicle veh)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_PLAY_SOUND_FROM_VEHICLE, SoundId, (char*)ctx.marshal_as<const char*>(SoundName), veh);
			}
			static void PLAY_SOUND_FRONTEND(int soundId, String^ soundName)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_PLAY_SOUND_FRONTEND, soundId, (char*)ctx.marshal_as<const char*>(soundName));
			}
			static void PLAY_STREAM_FROM_OBJECT(Entity obj) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_PLAY_STREAM_FROM_OBJECT, obj); }
			static void PLAY_STREAM_FROM_PED(Ped ped) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_PLAY_STREAM_FROM_PED, ped); }
			static void PLAY_STREAM_FRONTEND() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_PLAY_STREAM_FRONTEND); }
			static void REGISTER_SCRIPT_WITH_AUDIO(b8 reg) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_REGISTER_SCRIPT_WITH_AUDIO, reg); }
			static void RELEASE_SCRIPT_CONTROLLED_MICROPHONE() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_RELEASE_SCRIPT_CONTROLLED_MICROPHONE); }
			static void RELEASE_SOUND_ID(unsigned int sound) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_RELEASE_SOUND_ID, sound); }
			static void RESTART_SCRIPTED_CONVERSATION() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_RESTART_SCRIPTED_CONVERSATION); }
			static void RETUNE_RADIO_DOWN() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_RETUNE_RADIO_DOWN); }
			static void RETUNE_RADIO_TO_STATION_INDEX(unsigned int radioStation) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_RETUNE_RADIO_TO_STATION_INDEX, radioStation); }
			static void RETUNE_RADIO_TO_STATION_NAME(String^ name)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_RETUNE_RADIO_TO_STATION_NAME, ctx.marshal_as<const char*>(name));
			}
			static void RETUNE_RADIO_UP() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_RETUNE_RADIO_UP); }
			static void SAY_AMBIENT_SPEECH(Ped ped, String^ phraseName, b8 flag0, b8 flag1, int style)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_SAY_AMBIENT_SPEECH, ped, ctx.marshal_as<const char*>(phraseName), flag0, flag1, style);
			}
			static void SAY_AMBIENT_SPEECH_WITH_VOICE(Ped ped, String^ SpeechName, String^ VoiceName, b8 flag0, b8 flag1, int style)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_SAY_AMBIENT_SPEECH_WITH_VOICE, ped, ctx.marshal_as<const char*>(SpeechName), ctx.marshal_as<const char*>(VoiceName), flag0, flag1, style);
			}
			static void SET_AMBIENT_VOICE_NAME(Ped ped, String^ name)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_AMBIENT_VOICE_NAME, ped, ctx.marshal_as<const char*>(name));
			}
			static void SET_GPS_VOICE_FOR_VEHICLE(Vehicle veh, int VoiceId) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_GPS_VOICE_FOR_VEHICLE, veh, VoiceId); }
			static void SET_LOUD_VEHICLE_RADIO(Vehicle veh, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_LOUD_VEHICLE_RADIO, veh, set); }
			static void SET_MOVIE_VOLUME(float volume) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_MOVIE_VOLUME, volume); }
			static void SET_SCRIPT_MIC_LOOK_AT(float x, float y, float z) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_SCRIPT_MIC_LOOK_AT, x, y, z); }
			static void SET_SCRIPT_MIC_POSITION(float x, float y, float z) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_SCRIPT_MIC_POSITION, x, y, z); }
			static void SET_VARIABLE_ON_SOUND(unsigned int sound, String^ varname, float value)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_VARIABLE_ON_SOUND, sound, ctx.marshal_as<const char*>(varname), value);
			}
			static void SET_VOICE_ID_FROM_HEAD_COMPONENT(Ped ped, int VoiceId, b8 IsMale) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_VOICE_ID_FROM_HEAD_COMPONENT, ped, VoiceId, IsMale); }
			static void SKIP_RADIO_FORWARD() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SKIP_RADIO_FORWARD); }
			static void SKIP_TO_NEXT_SCRIPTED_CONVERSATION_LINE() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SKIP_TO_NEXT_SCRIPTED_CONVERSATION_LINE); }
			static void START_END_CREDITS_MUSIC() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_START_END_CREDITS_MUSIC); }
			static void START_SCRIPT_CONVERSATION(b8 flag0, b8 flag1) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_START_SCRIPT_CONVERSATION, flag0, flag1); }
			static void STOP_END_CREDITS_MUSIC() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_STOP_END_CREDITS_MUSIC); }
			static void STOP_SOUND(unsigned int sound) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_STOP_SOUND, sound); }
			static void TRIGGER_LOADING_MUSIC_ON_NEXT_FADE() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TRIGGER_LOADING_MUSIC_ON_NEXT_FADE); }
			static void TRIGGER_MISSION_COMPLETE_AUDIO(int id) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TRIGGER_MISSION_COMPLETE_AUDIO, id); }
			static void UNFREEZE_RADIO_STATION(String^ radiostation)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_UNFREEZE_RADIO_STATION, ctx.marshal_as<const char*>(radiostation));
			}
			static void UNPAUSE_RADIO() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_UNPAUSE_RADIO); }
			static void UNREGISTER_SCRIPT_WITH_AUDIO() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_UNREGISTER_SCRIPT_WITH_AUDIO); }
			static void CLEAR_CUTSCENE() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_CLEAR_CUTSCENE); }
			static void CLEAR_NAMED_CUTSCENE(String^ name)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_CLEAR_NAMED_CUTSCENE, ctx.marshal_as<const char*>(name));
			}
			static void INIT_CUTSCENE(String^ name)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_INIT_CUTSCENE, ctx.marshal_as<const char*>(name));
			}
			static void SET_CUTSCENE_EXTRA_ROOM_POS(float x, float y, float z) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CUTSCENE_EXTRA_ROOM_POS, x, y, z); }
			static void START_CUTSCENE() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_START_CUTSCENE); }
			static void START_CUTSCENE_NOW(String^ name)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_START_CUTSCENE_NOW, ctx.marshal_as<const char*>(name));
			}
			static void STOP_CUTSCENE() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_STOP_CUTSCENE); }
			static void STREAM_CUTSCENE() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_STREAM_CUTSCENE); }
			static void ACTIVATE_INTERIOR(Interior interior, b8 unknownTrue) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ACTIVATE_INTERIOR, interior, unknownTrue); }
			static void GET_INTERIOR_AT_COORDS(float x, float y, float z, [OutAttribute] Interior% pInterior)
			{
				Interior p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_INTERIOR_AT_COORDS, x, y, z, &p);
				pInterior = p;
			}
			static void GET_INTERIOR_FROM_CAR(Vehicle vehicle, [OutAttribute] Interior% pInterior)
			{
				Interior p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_INTERIOR_FROM_CAR, vehicle, &p);
				pInterior = p;
			}
			static void GET_INTERIOR_FROM_CHAR(Ped ped, [OutAttribute] Interior% pInterior)
			{
				Interior p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_INTERIOR_FROM_CHAR, ped, &p);
				pInterior = p;
			}
			static void GET_INTERIOR_HEADING(Interior interior, [OutAttribute] float% pHeading)
			{
				float p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_INTERIOR_HEADING, interior, &p);
				pHeading = p;
			}
			static void GET_OFFSET_FROM_INTERIOR_IN_WORLD_COORDS(Interior interior, float x, float y, float z, [OutAttribute] float% pOffset)
			{
				float p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_OFFSET_FROM_INTERIOR_IN_WORLD_COORDS, interior, x, y, z, &p);
				pOffset = p;
			}
			static void ACTIVATE_SCRIPTED_CAMS(b8 Unk538, b8 Unk539) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ACTIVATE_SCRIPTED_CAMS, Unk538, Unk539); }
			static void ACTIVATE_VIEWPORT(int viewportid, b8 activate) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ACTIVATE_VIEWPORT, viewportid, activate); }
			static void ADD_CAM_SPLINE_NODE(int cam, int camnode) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ADD_CAM_SPLINE_NODE, cam, camnode); }
			static void ATTACH_CAM_TO_OBJECT(int cam, Entity obj) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ATTACH_CAM_TO_OBJECT, cam, obj); }
			static void ATTACH_CAM_TO_PED(int cam, Ped ped) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ATTACH_CAM_TO_PED, cam, ped); }
			static void ATTACH_CAM_TO_VEHICLE(int cam, Vehicle veh) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ATTACH_CAM_TO_VEHICLE, cam, veh); }
			static void ATTACH_CAM_TO_VIEWPORT(int cam, int viewportid) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ATTACH_CAM_TO_VIEWPORT, cam, viewportid); }
			//static void BEGIN_CAM_COMMANDS(int* Unk540) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_BEGIN_CAM_COMMANDS, Unk540); }
			static void CAM_PROCESS(int cam) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_CAM_PROCESS, cam); }
			static void CAM_RESTORE() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_CAM_RESTORE); }
			static void CAM_RESTORE_JUMPCUT() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_CAM_RESTORE_JUMPCUT); }
			static void CAM_SEQUENCE_CLOSE() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_CAM_SEQUENCE_CLOSE); }
			static void CAM_SEQUENCE_GET_PROGRESS(int Unk541, [OutAttribute] int% progress)
			{
				int p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_CAM_SEQUENCE_GET_PROGRESS, Unk541, &p);
				progress = p;
			}
			static void CAM_SEQUENCE_OPEN(int Unk542) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_CAM_SEQUENCE_OPEN, Unk542); }
			static void CAM_SEQUENCE_REMOVE(int Unk543) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_CAM_SEQUENCE_REMOVE, Unk543); }
			static void CAM_SEQUENCE_START(int Unk544) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_CAM_SEQUENCE_START, Unk544); }
			static void CAM_SEQUENCE_STOP(int Unk545) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_CAM_SEQUENCE_STOP, Unk545); }
			static void CAM_SEQUENCE_WAIT(int cam, int time) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_CAM_SEQUENCE_WAIT, cam, time); }
			static void CAM_SET_CINEMATIC(Vehicle veh, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_CAM_SET_CINEMATIC, veh, set); }
			static void CAM_SET_DOLLY_ZOOM_LOCK(int cam, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_CAM_SET_DOLLY_ZOOM_LOCK, cam, set); }
			static void CAM_SET_INTERPOLATION_DETAILS(int Unk546) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_CAM_SET_INTERPOLATION_DETAILS, Unk546); }
			static void CAM_SET_INTERP_GRAPH_POS(int cam, int Unk547) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_CAM_SET_INTERP_GRAPH_POS, cam, Unk547); }
			static void CAM_SET_INTERP_GRAPH_ROT(int cam, int val) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_CAM_SET_INTERP_GRAPH_ROT, cam, val); }
			static void CAM_SET_INTERP_STATE_SRC(int cam, int Unk548) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_CAM_SET_INTERP_STATE_SRC, cam, Unk548); }
			static void CELL_CAM_ACTIVATE(b8 Unk551, b8 Unk552) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_CELL_CAM_ACTIVATE, Unk551, Unk552); }
			static void CELL_CAM_SET_CENTRE_POS(float x, float y) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_CELL_CAM_SET_CENTRE_POS, x, y); }
			static void CELL_CAM_SET_COLOUR_BRIGHTNESS(float Unk553, float Unk554, float Unk555, float Unk556) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_CELL_CAM_SET_COLOUR_BRIGHTNESS, Unk553, Unk554, Unk555, Unk556); }
			static void CELL_CAM_SET_ZOOM(float zoom) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_CELL_CAM_SET_ZOOM, zoom); }
			static void CLEAR_ROOM_FOR_VIEWPORT(int viewportid) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_CLEAR_ROOM_FOR_VIEWPORT, viewportid); }
			static void CLONE_CAM(int cam, [OutAttribute] int% camcopy)
			{
				int p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_CLONE_CAM, cam, &p);
				camcopy = p;
			}
			static void CREATE_CAM(unsigned int camtype_usually14, [OutAttribute] int% camera)
			{
				int p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_CREATE_CAM, camtype_usually14, &p);
				camera = p;
			}
			static void CREATE_HTML_VIEWPORT([OutAttribute] int% htmlviewport)
			{
				int p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_CREATE_HTML_VIEWPORT, &p);
				htmlviewport = p;
			}
			static void CREATE_VIEWPORT([OutAttribute] int% viewport)
			{
				int p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_CREATE_VIEWPORT, &p);
				viewport = p;
			}
			static void DESTROY_ALL_CAMS() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DESTROY_ALL_CAMS); }
			static void DESTROY_ALL_SCRIPT_VIEWPORTS() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DESTROY_ALL_SCRIPT_VIEWPORTS); }
			static void DESTROY_CAM(int camera) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DESTROY_CAM, camera); }
			static void DESTROY_VIEWPORT(int viewportid) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DESTROY_VIEWPORT, viewportid); }
			static void DETACH_CAM_FROM_VIEWPORT(int Unk557) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DETACH_CAM_FROM_VIEWPORT, Unk557); }
			static void ENABLE_CAM_COLLISION(int cam, b8 enable) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ENABLE_CAM_COLLISION, cam, enable); }
			static void ENABLE_FOV_LOD_MULTIPLIER(b8 enable) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ENABLE_FOV_LOD_MULTIPLIER, enable); }
			//static void END_CAM_COMMANDS(int* Unk558) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_END_CAM_COMMANDS, Unk558); }
			static void FORCE_GAME_TELESCOPE_CAM(b8 force) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_FORCE_GAME_TELESCOPE_CAM, force); }
			static void FORCE_NO_CAM_PAUSE(b8 foce) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_FORCE_NO_CAM_PAUSE, foce); }
			static void GET_CAM_FAR_CLIP(int cam, [OutAttribute] float% clip)
			{
				float p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_CAM_FAR_CLIP, cam, &p);
				clip = p;
			}
			static void GET_CAM_FAR_DOF(int cam, [OutAttribute] float% fardof)
			{
				float p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_CAM_FAR_DOF, cam, &p);
				fardof = p;
			}
			static void GET_CAM_FOV(int camera, [OutAttribute] float% fov)
			{
				float p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_CAM_FOV, camera, &p);
				fov = p;
			}
			static void GET_CAM_MOTION_BLUR(int cam, [OutAttribute] int% blur)
			{
				int p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_CAM_MOTION_BLUR, cam, &p);
				blur = p;
			}
			static void GET_CAM_NEAR_CLIP(int cam, [OutAttribute] float% clip)
			{
				float p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_CAM_NEAR_CLIP, cam, &p);
				clip = p;
			}
			static void GET_CAM_NEAR_DOF(int cam, [OutAttribute] float% dof)
			{
				float p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_CAM_NEAR_DOF, cam, &p);
				dof = p;
			}
			static void GET_CAM_POS(int camera, [OutAttribute] float% pX, [OutAttribute] float% pY, [OutAttribute] float% pZ)
			{
				float x, y, z;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_CAM_POS, camera, &x, &y, &z);
				pX = x;
				pY = y;
				pZ = z;
			}
			static void GET_CAM_ROT(int camera, [OutAttribute] float% angleX, [OutAttribute] float% angleY, [OutAttribute] float% angleZ)
			{
				float x, y, z;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_CAM_ROT, camera, &x, &y, &z);
				angleX = x;
				angleY = y;
				angleZ = z;
			}
			static void GET_CINEMATIC_CAM([OutAttribute] int% cam)
			{
				int p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_CINEMATIC_CAM, &p);
				cam = p;
			}
			static void GET_FOLLOW_VEHICLE_CAM_SUBMODE([OutAttribute] int% mode)
			{
				int p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_FOLLOW_VEHICLE_CAM_SUBMODE, &p);
				mode = p;
			}
			static void GET_FREE_CAM([OutAttribute] int% cam)
			{
				int p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_FREE_CAM, &p);
				cam = p;
			}
			static void GET_GAME_CAM([OutAttribute] int% camera)
			{
				int p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_GAME_CAM, &p);
				camera = p;
			}
			static void GET_GAME_CAM_CHILD([OutAttribute] Camera% camera)
			{
				Camera p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_GAME_CAM_CHILD, &p);
				camera = p;
			}
			static void GET_GAME_VIEWPORT_ID([OutAttribute] int% viewportid)
			{
				int p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_GAME_VIEWPORT_ID, &p);
				viewportid = p;
			}
			static void GET_GROUND_Z_FOR_3D_COORD(f32 x, f32 y, f32 z, [OutAttribute] f32% pGroundZ)
			{
				f32 p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_GROUND_Z_FOR_3D_COORD, x, y, z, &p);
				pGroundZ = p;
			}
			static float GET_STRING_WIDTH_WITH_STRING(String^ gxt, String^ str)
			{
				msclr::interop::marshal_context ctx;
				return NativeInvoke::Invoke< float>(NATIVE_GET_STRING_WIDTH_WITH_STRING, ctx.marshal_as<const char*>(gxt), ctx.marshal_as<const char*>(str));
			}
			static void GET_KEY_FOR_VIEWPORT_IN_ROOM(int viewportid, [OutAttribute] int% roomkey)
			{
				int p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_KEY_FOR_VIEWPORT_IN_ROOM, viewportid, &p);
				roomkey = p;
			}
			static void GET_RADAR_VIEWPORT_ID([OutAttribute] int% viewport)
			{
				int p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_RADAR_VIEWPORT_ID, &p);
				viewport = p;
			}
			static void GET_ROOT_CAM([OutAttribute] Cam% rootcam)
			{
				Cam p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_ROOT_CAM, &p);
				rootcam = p;
			}
			static void GET_SCREEN_VIEWPORT_ID([OutAttribute] int% viewportid)
			{
				int p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_SCREEN_VIEWPORT_ID, &p);
				viewportid = p;
			}
			static void GET_SCRIPT_CAM([OutAttribute] int% cam)
			{
				int p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_SCRIPT_CAM, &p);
				cam = p;
			}
			static void GET_SCRIPT_DRAW_CAM([OutAttribute] int% cam)
			{
				int p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_SCRIPT_DRAW_CAM, &p);
				cam = p;
			}
			static void GET_VIEWPORT_POS_AND_SIZE(int viewportid, [OutAttribute] float% pX, [OutAttribute] float% pY, [OutAttribute] float% pXSize, [OutAttribute] float% pYSize)
			{
				float x, y, sX, sY;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_VIEWPORT_POS_AND_SIZE, viewportid, &x, &y, &sX, &sY);
				pX = x;
				pY = y;
				pXSize = sX;
				pYSize = sY;
			}
			static void HINT_CAM(float x, float y, float z, int Unk559, int Unk560, int Unk561, int Unk562) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_HINT_CAM, x, y, z, Unk559, Unk560, Unk561, Unk562); }
			static void POINT_CAM_AT_CAM(int cam, int camnext) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_POINT_CAM_AT_CAM, cam, camnext); }
			static void POINT_CAM_AT_COORD(int cam, float x, float y, float z) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_POINT_CAM_AT_COORD, cam, x, y, z); }
			static void POINT_CAM_AT_OBJECT(int cam, Entity obj) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_POINT_CAM_AT_OBJECT, cam, obj); }
			static void POINT_CAM_AT_PED(int cam, Ped ped) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_POINT_CAM_AT_PED, cam, ped); }
			static void POINT_CAM_AT_VEHICLE(int cam, Vehicle veh) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_POINT_CAM_AT_VEHICLE, cam, veh); }
			static void POINT_FIXED_CAM(float x, float y, float z, int Unk563) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_POINT_FIXED_CAM, x, y, z, Unk563); }
			static void POINT_FIXED_CAM_AT_OBJ(Entity obj, int cam) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_POINT_FIXED_CAM_AT_OBJ, obj, cam); }
			static void POINT_FIXED_CAM_AT_PED(Ped ped, int cam) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_POINT_FIXED_CAM_AT_PED, ped, cam); }
			static void POINT_FIXED_CAM_AT_POS(float x, float y, float z, int cam) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_POINT_FIXED_CAM_AT_POS, x, y, z, cam); }
			static void POINT_FIXED_CAM_AT_VEHICLE(Vehicle veh, int cam) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_POINT_FIXED_CAM_AT_VEHICLE, veh, cam); }
			static void PROSTITUTE_CAM_ACTIVATE(b8 activate) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_PROSTITUTE_CAM_ACTIVATE, activate); }
			static void RESET_CAM_INTERP_CUSTOM_SPEED_GRAPH() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_RESET_CAM_INTERP_CUSTOM_SPEED_GRAPH); }
			static void RESET_CAM_SPLINE_CUSTOM_SPEED_GRAPH() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_RESET_CAM_SPLINE_CUSTOM_SPEED_GRAPH); }
			static void SET_CAMERA_AUTO_SCRIPT_ACTIVATION(b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CAMERA_AUTO_SCRIPT_ACTIVATION, set); }
			static void SET_CAMERA_BEGIN_CAM_COMMANDS_REQUIRED(b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CAMERA_BEGIN_CAM_COMMANDS_REQUIRED, set); }
			static void SET_CAMERA_CONTROLS_DISABLED_WITH_PLAYER_CONTROLS(b8 value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CAMERA_CONTROLS_DISABLED_WITH_PLAYER_CONTROLS, value); }
			static void SET_CAMERA_STATE(int cam, int state) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CAMERA_STATE, cam, state); }
			static void SET_CAM_ACTIVE(int camera, b8 value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CAM_ACTIVE, camera, value); }
			static void SET_CAM_ATTACH_OFFSET(int cam, float x, float y, float z) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CAM_ATTACH_OFFSET, cam, x, y, z); }
			static void SET_CAM_ATTACH_OFFSET_IS_RELATIVE(int cam, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CAM_ATTACH_OFFSET_IS_RELATIVE, cam, set); }
			static void SET_CAM_BEHIND_PED(Ped ped) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CAM_BEHIND_PED, ped); }
			static void SET_CAM_COMPONENT_SHAKE(int cam, int componentid, int Unk564, int time, float x, float y, float z) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CAM_COMPONENT_SHAKE, cam, componentid, Unk564, time, x, y, z); }
			static void SET_CAM_DOF_FOCUSPOINT(int cam, float x, float y, float z, float Unk565) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CAM_DOF_FOCUSPOINT, cam, x, y, z, Unk565); }
			static void SET_CAM_FAR_CLIP(int cam, float clip) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CAM_FAR_CLIP, cam, clip); }
			static void SET_CAM_FAR_DOF(int cam, float fardof) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CAM_FAR_DOF, cam, fardof); }
			static void SET_CAM_FOV(int camera, float fov) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CAM_FOV, camera, fov); }
			static void SET_CAM_INHERIT_ROLL_OBJECT(int cam, Entity obj) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CAM_INHERIT_ROLL_OBJECT, cam, obj); }
			static void SET_CAM_INHERIT_ROLL_PED(int cam, Ped ped) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CAM_INHERIT_ROLL_PED, cam, ped); }
			static void SET_CAM_INHERIT_ROLL_VEHICLE(int cam, Vehicle veh) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CAM_INHERIT_ROLL_VEHICLE, cam, veh); }
			static void SET_CAM_INTERP_CUSTOM_SPEED_GRAPH(float speed) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CAM_INTERP_CUSTOM_SPEED_GRAPH, speed); }
			static void SET_CAM_INTERP_DETAIL_ROT_STYLE_ANGLES(int Unk566) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CAM_INTERP_DETAIL_ROT_STYLE_ANGLES, Unk566); }
			static void SET_CAM_INTERP_DETAIL_ROT_STYLE_QUATS(int Unk567) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CAM_INTERP_DETAIL_ROT_STYLE_QUATS, Unk567); }
			static void SET_CAM_INTERP_STYLE_CORE(int cam0, int cam1, int cam2, int time, b8 flag) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CAM_INTERP_STYLE_CORE, cam0, cam1, cam2, time, flag); }
			static void SET_CAM_INTERP_STYLE_DETAILED(int cam, b8 Unk568, b8 Unk569, b8 Unk570, b8 Unk571) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CAM_INTERP_STYLE_DETAILED, cam, Unk568, Unk569, Unk570, Unk571); }
			static void SET_CAM_IN_FRONT_OF_PED(Ped ped) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CAM_IN_FRONT_OF_PED, ped); }
			static void SET_CAM_MOTION_BLUR(int cam, float blur) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CAM_MOTION_BLUR, cam, blur); }
			static void SET_CAM_NAME(int cam, String^ camName)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CAM_NAME, cam, ctx.marshal_as<const char*>(camName));
			}
			static void SET_CAM_NEAR_CLIP(int cam, float clip) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CAM_NEAR_CLIP, cam, clip); }
			static void SET_CAM_NEAR_DOF(int cam, float dof) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CAM_NEAR_DOF, cam, dof); }
			static void SET_CAM_POINT_OFFSET(int cam, float x, float y, float z) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CAM_POINT_OFFSET, cam, x, y, z); }
			static void SET_CAM_POINT_OFFSET_IS_RELATIVE(int cam, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CAM_POINT_OFFSET_IS_RELATIVE, cam, set); }
			static void SET_CAM_POS(int camera, float pX, float pY, float pZ) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CAM_POS, camera, pX, pY, pZ); }
			static void SET_CAM_PROPAGATE(int camera, b8 value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CAM_PROPAGATE, camera, value); }
			static void SET_CAM_ROLL(int cam, float roll) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CAM_ROLL, cam, roll); }
			static void SET_CAM_ROT(int camera, float angleX, float angleY, float angleZ) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CAM_ROT, camera, angleX, angleY, angleZ); }
			static void SET_CAM_SHAKE(int cam, b8 Unk572, int shakeval) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CAM_SHAKE, cam, Unk572, shakeval); }
			static void SET_CAM_SPLINE_CUSTOM_SPEED_GRAPH(float speed) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CAM_SPLINE_CUSTOM_SPEED_GRAPH, speed); }
			static void SET_CAM_SPLINE_DURATION(int cam, int duration) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CAM_SPLINE_DURATION, cam, duration); }
			static void SET_CAM_SPLINE_PROGRESS(int cam, float progress) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CAM_SPLINE_PROGRESS, cam, progress); }
			static void SET_CAM_SPLINE_SPEED_CONSTANT(int cam, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CAM_SPLINE_SPEED_CONSTANT, cam, set); }
			static void SET_CAM_SPLINE_SPEED_GRAPH(int cam, int Unk573) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CAM_SPLINE_SPEED_GRAPH, cam, Unk573); }
			static void SET_CAM_TARGET_PED(Camera camera, Ped ped) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CAM_TARGET_PED, camera, ped); }
			static void SET_CINEMATIC_BUTTON_ENABLED(b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CINEMATIC_BUTTON_ENABLED, set); }
			static void SET_DRUNK_CAM(Cam cam, float val, int time) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_DRUNK_CAM, cam, val, time); }
			static void SET_FIXED_CAM_POS(float x, float y, float z) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_FIXED_CAM_POS, x, y, z); }
			static void SET_FOLLOW_PED_PITCH_LIMIT_DOWN(float pitchdownlim) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_FOLLOW_PED_PITCH_LIMIT_DOWN, pitchdownlim); }
			static void SET_FOLLOW_PED_PITCH_LIMIT_UP(float pitchuplim) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_FOLLOW_PED_PITCH_LIMIT_UP, pitchuplim); }
			static void SET_FOLLOW_VEHICLE_CAM_OFFSET(b8 Unk574, float x, float y, float z) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_FOLLOW_VEHICLE_CAM_OFFSET, Unk574, x, y, z); }
			static void SET_FOLLOW_VEHICLE_CAM_SUBMODE(int mode) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_FOLLOW_VEHICLE_CAM_SUBMODE, mode); }
			static void SET_GAME_CAMERA_CONTROLS_ACTIVE(b8 active) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_GAME_CAMERA_CONTROLS_ACTIVE, active); }
			static void SET_GAME_CAM_HEADING(float heading) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_GAME_CAM_HEADING, heading); }
			static void SET_GAME_CAM_PITCH(float pitch) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_GAME_CAM_PITCH, pitch); }
			static void SET_HINT_FOV(float fov) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_HINT_FOV, fov); }
			static void SET_HINT_MOVE_IN_DIST(float dist) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_HINT_MOVE_IN_DIST, dist); }
			static void SET_HINT_MOVE_IN_DIST_DEFAULT() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_HINT_MOVE_IN_DIST_DEFAULT); }
			static void SET_HINT_TIMES(float Unk580, float Unk581, float Unk582) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_HINT_TIMES, Unk580, Unk581, Unk582); }
			static void SET_HINT_TIMES_DEFAULT() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_HINT_TIMES_DEFAULT); }
			static void SET_PTFX_CAM_INSIDE_VEHICLE(b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_PTFX_CAM_INSIDE_VEHICLE, set); }
			static void SET_ROOM_FOR_VIEWPORT_BY_KEY(int viewportid, unsigned int roomkey) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_ROOM_FOR_VIEWPORT_BY_KEY, viewportid, roomkey); }
			static void SET_ROOM_FOR_VIEWPORT_BY_NAME(int viewportid, String^ roomname)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_ROOM_FOR_VIEWPORT_BY_NAME, viewportid, ctx.marshal_as<const char*>(roomname));
			}
			static void SET_TELESCOPE_CAM_ANGLE_LIMITS(float Unk583, float Unk584, float Unk585, float Unk586, float Unk587, float Unk588) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_TELESCOPE_CAM_ANGLE_LIMITS, Unk583, Unk584, Unk585, Unk586, Unk587, Unk588); }
			static void SET_VIEWPORT(int viewportid, float Unk589, float Unk590, float Unk591, float Unk592) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_VIEWPORT, viewportid, Unk589, Unk590, Unk591, Unk592); }
			static void SET_VIEWPORT_DESTINATION(int viewportid, float x, float y, float z, float Unk593, int Unk594, int Unk595) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_VIEWPORT_DESTINATION, viewportid, x, y, z, Unk593, Unk594, Unk595); }
			static void SET_VIEWPORT_MIRRORED(int viewportid, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_VIEWPORT_MIRRORED, viewportid, set); }
			static void SET_VIEWPORT_PRIORITY(int viewportid, int priority) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_VIEWPORT_PRIORITY, viewportid, priority); }
			static void SET_VIEWPORT_SHAPE(int cam, int shape) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_VIEWPORT_SHAPE, cam, shape); }
			static void SNAPSHOT_CAM(int cam, int Unk596) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SNAPSHOT_CAM, cam, Unk596); }
			static void UNATTACH_CAM(int cam) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_UNATTACH_CAM, cam); }
			static void UNINHERIT_CAM_ROLL(int cam) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_UNINHERIT_CAM_ROLL, cam); }
			static void UNPOINT_CAM(int cam) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_UNPOINT_CAM, cam); }
			static void ADD_AMMO_TO_CHAR(Ped ped, unsigned int weapon, unsigned int amount) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ADD_AMMO_TO_CHAR, ped, weapon, amount); }
			static void BLOCK_PED_WEAPON_SWITCHING(Ped ped, b8 value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_BLOCK_PED_WEAPON_SWITCHING, ped, value); }
			static void ENABLE_MAX_AMMO_CAP(b8 enable) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ENABLE_MAX_AMMO_CAP, enable); }
			static void FIRE_SINGLE_BULLET(float x, float y, float z, float targetX, float targetY, float targetZ, unsigned int unknown) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_FIRE_SINGLE_BULLET, x, y, z, targetX, targetY, targetZ, unknown); }
			static void FORCE_CHAR_TO_DROP_WEAPON(Ped ped) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_FORCE_CHAR_TO_DROP_WEAPON, ped); }
			static void GET_AMMO_IN_CHAR_WEAPON(Ped ped, unsigned int weapon, [OutAttribute] unsigned int% pAmmo)
			{
				unsigned int p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_AMMO_IN_CHAR_WEAPON, ped, weapon, &p);
				pAmmo = p;
			}
			static void GET_CHAR_WEAPON_IN_SLOT(Ped ped, unsigned int slot, [OutAttribute] unsigned int% pWeapon, [OutAttribute] unsigned int% pAmmo0, [OutAttribute] unsigned int% pAmmo1)
			{
				unsigned int p1, p2, p3;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_CHAR_WEAPON_IN_SLOT, ped, slot, &p1, &p2, &p3);
				pWeapon = p1;
				pAmmo0 = p2;
				pAmmo1 = p3;
			}
			static void GET_MAX_AMMO_IN_CLIP(Ped ped, unsigned int weapon, [OutAttribute] unsigned int% pMaxAmmo)
			{
				unsigned int p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_MAX_AMMO_IN_CLIP, ped, weapon, &p);
				pMaxAmmo = p;
			}
			static void GET_WEAPONTYPE_MODEL(int weapontype, [OutAttribute] unsigned int% model)
			{
				unsigned int p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_WEAPONTYPE_MODEL, weapontype, &p);
				model = p;
			}
			static void GET_WEAPONTYPE_SLOT(int weapon, [OutAttribute] int% slot)
			{
				int p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_WEAPONTYPE_SLOT, weapon, &p);
				slot = p;
			}
			static void GIVE_DELAYED_WEAPON_TO_CHAR(Ped ped, int weapon, int delaytime, b8 flag) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_GIVE_DELAYED_WEAPON_TO_CHAR, ped, weapon, delaytime, flag); }
			static void GIVE_WEAPON_TO_CHAR(Ped ped, unsigned int weapon, unsigned int ammo, b8 unknown0) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_GIVE_WEAPON_TO_CHAR, ped, weapon, ammo, unknown0); }
			static void HIDE_CHAR_WEAPON_FOR_SCRIPTED_CUTSCENE(Ped ped, b8 hide) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_HIDE_CHAR_WEAPON_FOR_SCRIPTED_CUTSCENE, ped, hide); }
			static void REMOVE_ALL_CHAR_WEAPONS(Ped ped) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_REMOVE_ALL_CHAR_WEAPONS, ped); }
			static void REMOVE_WEAPON_FROM_CHAR(Ped ped, unsigned int weapon) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_REMOVE_WEAPON_FROM_CHAR, ped, weapon); }
			static void SET_CAN_TARGET_CHAR_WITHOUT_LOS(Ped ped, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CAN_TARGET_CHAR_WITHOUT_LOS, ped, set); }
			static void SET_CHAR_AMMO(Ped ped, unsigned int weapon, unsigned int ammo) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_AMMO, ped, weapon, ammo); }
			static void SET_CHAR_CURRENT_WEAPON_VISIBLE(Ped ped, b8 visble) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_CURRENT_WEAPON_VISIBLE, ped, visble); }
			static void SET_CHAR_WEAPON_SKILL(Ped ped, int skill) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_WEAPON_SKILL, ped, skill); }
			static void SET_CURRENT_CHAR_WEAPON(Ped ped, unsigned int w, b8 unknownTrue) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CURRENT_CHAR_WEAPON, ped, w, unknownTrue); }
			static void SET_ENABLE_NEAR_CLIP_SCAN(b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_ENABLE_NEAR_CLIP_SCAN, set); }
			static void SET_ENABLE_RC_DETONATE(b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_ENABLE_RC_DETONATE, set); }
			static void SET_ENABLE_RC_DETONATE_ON_CONTACT(b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_ENABLE_RC_DETONATE_ON_CONTACT, set); }
			static void SET_HOT_WEAPON_SWAP(b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_HOT_WEAPON_SWAP, set); }
			static void ENABLE_SCENE_STREAMING(b8 enable) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ENABLE_SCENE_STREAMING, enable); }
			static void FINISH_STREAMING_REQUEST_LIST() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_FINISH_STREAMING_REQUEST_LIST); }
			static void GET_MODEL_DIMENSIONS(unsigned int model, [OutAttribute] Vector3% pMinVector, [OutAttribute] Vector3% pMaxVector)
			{
				Vector3 p1, p2;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_MODEL_DIMENSIONS, model, &p1, &p2);
				pMinVector = p1;
				pMaxVector = p2;
			}
			static void LOAD_ALL_OBJECTS_NOW() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_LOAD_ALL_OBJECTS_NOW); }
			static void LOAD_SCENE(float x, float y, float z) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_LOAD_SCENE, x, y, z); }
			static void LOAD_SCENE_FOR_ROOM_BY_KEY(int interior, unsigned int roomhash) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_LOAD_SCENE_FOR_ROOM_BY_KEY, interior, roomhash); }
			static void MARK_MODEL_AS_NO_LONGER_NEEDED(int model) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_MARK_MODEL_AS_NO_LONGER_NEEDED, model); }
			static void MARK_STREAMED_TXD_AS_NO_LONGER_NEEDED(String^ txdName)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_MARK_STREAMED_TXD_AS_NO_LONGER_NEEDED, ctx.marshal_as<const char*>(txdName));
			}
			static void REMOVE_ALL_INACTIVE_GROUPS_FROM_CLEANUP_LIST() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_REMOVE_ALL_INACTIVE_GROUPS_FROM_CLEANUP_LIST); }
			static void REMOVE_ANIMS(String^ animName)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_REMOVE_ANIMS, ctx.marshal_as<const char*>(animName));
			}
			static void REMOVE_IPL(String^ iplName)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_REMOVE_IPL, ctx.marshal_as<const char*>(iplName));
			}
			static void REMOVE_IPL_DISCREETLY(String^ iplname)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_REMOVE_IPL_DISCREETLY, ctx.marshal_as<const char*>(iplname));
			}
			static void REMOVE_TXD(TextureDict txd) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_REMOVE_TXD, txd); }
			static void REQUEST_ADDITIONAL_TEXT(String^ textName, unsigned int textIndex)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_REQUEST_ADDITIONAL_TEXT, ctx.marshal_as<const char*>(textName), textIndex);
			}
			static void REQUEST_ANIMS(String^ animName)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_REQUEST_ANIMS, ctx.marshal_as<const char*>(animName));
			}
			static void REQUEST_CAR_RECORDING(int CarRecId) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_REQUEST_CAR_RECORDING, CarRecId); }
			static void REQUEST_COLLISION_AT_POSN(float x, float y, float z) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_REQUEST_COLLISION_AT_POSN, x, y, z); }
			static void REQUEST_COLLISION_FOR_MODEL(unsigned int model) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_REQUEST_COLLISION_FOR_MODEL, model); }
			static void REQUEST_INTERIOR_MODELS(unsigned int model, String^ interiorName)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_REQUEST_INTERIOR_MODELS, model, ctx.marshal_as<const char*>(interiorName));
			}
			static void REQUEST_IPL(String^ iplName)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_REQUEST_IPL, ctx.marshal_as<const char*>(iplName));
			}
			[System::ObsoleteAttribute("This native is obsolete. Use CWorld.RequestModel instead.")] static void _REQUEST_MODEL(unsigned int model) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_REQUEST_MODEL, model); }
			static void REQUEST_STREAMED_TXD(String^ txdName, b8 unknown)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_REQUEST_STREAMED_TXD, ctx.marshal_as<const char*>(txdName), unknown);
			}
			static void SET_STATE_OF_CLOSEST_DOOR_OF_TYPE(unsigned int model, float x, float y, float z, int state, float Unk601) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_STATE_OF_CLOSEST_DOOR_OF_TYPE, model, x, y, z, state, Unk601); }
			static void SET_STREAMING_REQUEST_LIST_TIME(int time) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_STREAMING_REQUEST_LIST_TIME, time); }
			//static void SET_STREAM_PARAMS(float rolloff, int UnkTime) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_STREAM_PARAMS, rolloff, UnkTime); }
			static void SIMULATE_UPDATE_LOAD_SCENE() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SIMULATE_UPDATE_LOAD_SCENE); }
			static void START_LOAD_SCENE(float x, float y, float z) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_START_LOAD_SCENE, x, y, z); }
			static void START_STREAMING_REQUEST_LIST(String^ name)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_START_STREAMING_REQUEST_LIST, ctx.marshal_as<const char*>(name));
			}
			static void STOP_STREAM() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_STOP_STREAM); }
			static void ALLOCATE_SCRIPT_TO_OBJECT(String^ ScriptName, unsigned int model, int Unk602, float radius, int UnkTime)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_ALLOCATE_SCRIPT_TO_OBJECT, ctx.marshal_as<const char*>(ScriptName), model, Unk602, radius, UnkTime);
			}
			static void ALLOCATE_SCRIPT_TO_RANDOM_PED(String^ ScriptName, unsigned int model, int Unk603, b8 flag)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_ALLOCATE_SCRIPT_TO_RANDOM_PED, ctx.marshal_as<const char*>(ScriptName), model, Unk603, flag);
			}
			static void ALLOW_THIS_SCRIPT_TO_BE_PAUSED(b8 allows) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ALLOW_THIS_SCRIPT_TO_BE_PAUSED, allows); }
			static void DESTROY_THREAD(int ScriptHandle) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DESTROY_THREAD, ScriptHandle); }
			static uint32_t GET_MAP_AREA_FROM_COORDS(Vector3 pos) { return NativeInvoke::Invoke<uint32_t>(NATIVE_GET_MAP_AREA_FROM_COORDS, pos.X, pos.Y, pos.Z); }
			static uint32_t GET_MAP_AREA_FROM_COORDS(float x, float y, float z) { return NativeInvoke::Invoke<uint32_t>(NATIVE_GET_MAP_AREA_FROM_COORDS, x, y, z); }
			static void GET_SCRIPT_RENDERTARGET_RENDER_ID([OutAttribute] unsigned int% pRenderId)
			{
				unsigned int p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_SCRIPT_RENDERTARGET_RENDER_ID, &p);
				pRenderId = p;
			}
			static void MARK_SCRIPT_AS_NO_LONGER_NEEDED(String^ scriptName)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_MARK_SCRIPT_AS_NO_LONGER_NEEDED, ctx.marshal_as<const char*>(scriptName));
			}
			static void REQUEST_SCRIPT(String^ scriptName)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_REQUEST_SCRIPT, ctx.marshal_as<const char*>(scriptName));
			}
			static void SET_INTERP_FROM_GAME_TO_SCRIPT(b8 Unk604, int Unk605) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_INTERP_FROM_GAME_TO_SCRIPT, Unk604, Unk605); }
			static void SET_INTERP_FROM_SCRIPT_TO_GAME(b8 Unk606, int Unk607) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_INTERP_FROM_SCRIPT_TO_GAME, Unk606, Unk607); }
			static void SET_SCRIPT_LIMIT_TO_GANG_SIZE(int size) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_SCRIPT_LIMIT_TO_GANG_SIZE, size); }
			static void SET_THIS_SCRIPT_CAN_REMOVE_BLIPS_CREATED_BY_ANY_SCRIPT(b8 allow) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_THIS_SCRIPT_CAN_REMOVE_BLIPS_CREATED_BY_ANY_SCRIPT, allow); }
			static void TERMINATE_THIS_SCRIPT() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TERMINATE_THIS_SCRIPT); }
			static void THIS_SCRIPT_SHOULD_BE_SAVED() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_THIS_SCRIPT_SHOULD_BE_SAVED); }
			static void ACTIVATE_FRONTEND() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ACTIVATE_FRONTEND); }
			static void ACTIVATE_REPLAY_MENU() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ACTIVATE_REPLAY_MENU); }
			static b8 NETWORK_STORE_SINGLE_PLAYER_GAME() { return NativeInvoke::Invoke< b8>(NATIVE_NETWORK_STORE_SINGLE_PLAYER_GAME); }
			static void ACTIVATE_SAVE_MENU() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ACTIVATE_SAVE_MENU); }
			static void ADD_BLIP_FOR_CAR(Vehicle vehicle, [OutAttribute] Blip% pBlip)
			{
				Blip p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_ADD_BLIP_FOR_CAR, vehicle, &p);
				pBlip = p;
			}
			static void ADD_BLIP_FOR_CHAR(Ped ped, [OutAttribute] Blip% pBlip)
			{
				Blip p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_ADD_BLIP_FOR_CHAR, ped, &p);
				pBlip = p;
			}
			static void ADD_BLIP_FOR_CONTACT(float x, float y, float z, [OutAttribute] Blip% pBlip)
			{
				Blip p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_ADD_BLIP_FOR_CONTACT, x, y, z, &p);
				pBlip = p;
			}
			static void ADD_BLIP_FOR_COORD(float x, float y, float z, [OutAttribute] Blip% pBlip)
			{
				Blip p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_ADD_BLIP_FOR_COORD, x, y, z, &p);
				pBlip = p;
			}
			static void ADD_BLIP_FOR_GANG_TERRITORY(float x0, float y0, float x1, float y1, int colour, [OutAttribute] Blip% blip)
			{
				Blip p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_ADD_BLIP_FOR_GANG_TERRITORY, x0, y0, x1, y1, colour, &p);
				blip = p;
			}
			static void ADD_BLIP_FOR_OBJECT(Entity obj, [OutAttribute] Blip% pBlip)
			{
				Blip p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_ADD_BLIP_FOR_OBJECT, obj, &p);
				pBlip = p;
			}
			static void ADD_BLIP_FOR_PICKUP(Pickup pickup, [OutAttribute] Blip% pBlip)
			{
				Blip p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_ADD_BLIP_FOR_PICKUP, pickup, &p);
				pBlip = p;
			}
			static void ADD_BLIP_FOR_WEAPON(float x, float y, float z, [OutAttribute] Blip% blip)
			{
				Blip p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_ADD_BLIP_FOR_WEAPON, x, y, z, &p);
				blip = p;
			}
			static void ADD_FIRST_N_CHARACTERS_OF_STRING_TO_HTML_SCRIPT_OBJECT(int htmlobj, String^ str, int n)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_ADD_FIRST_N_CHARACTERS_OF_STRING_TO_HTML_SCRIPT_OBJECT, htmlobj, ctx.marshal_as<const char*>(str), n);
			}
			static void ADD_NEXT_MESSAGE_TO_PREVIOUS_BRIEFS(b8 add) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ADD_NEXT_MESSAGE_TO_PREVIOUS_BRIEFS, add); }
			static void ADD_SIMPLE_BLIP_FOR_PICKUP(Pickup pickup) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ADD_SIMPLE_BLIP_FOR_PICKUP, pickup); }
			static void ADD_STRING_TO_HTML_SCRIPT_OBJECT(int htmlobj, String^ str)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_ADD_STRING_TO_HTML_SCRIPT_OBJECT, htmlobj, ctx.marshal_as<const char*>(str));
			}
			static void ADD_STRING_TO_NEWS_SCROLLBAR(String^ str)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_ADD_STRING_TO_NEWS_SCROLLBAR, ctx.marshal_as<const char*>(str));
			}
			static void ADD_STRING_WITH_THIS_TEXT_LABEL_TO_PREVIOUS_BRIEF(String^ gxtname)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_ADD_STRING_WITH_THIS_TEXT_LABEL_TO_PREVIOUS_BRIEF, ctx.marshal_as<const char*>(gxtname));
			}
			static void ADD_TICKER_TO_PREVIOUS_BRIEF_WITH_UNDERSCORE(ScriptAny Unk625, ScriptAny Unk626, ScriptAny Unk627, ScriptAny Unk628, ScriptAny Unk629, ScriptAny Unk630, ScriptAny Unk631) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ADD_TICKER_TO_PREVIOUS_BRIEF_WITH_UNDERSCORE, Unk625, Unk626, Unk627, Unk628, Unk629, Unk630, Unk631); }	//used for japanese text correcting
			static void ADD_TO_PREVIOUS_BRIEF(String^ gxtentry)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_ADD_TO_PREVIOUS_BRIEF, ctx.marshal_as<const char*>(gxtentry));
			}
			static void ADD_TO_PREVIOUS_BRIEF_WITH_UNDERSCORE(String^ gxtentry)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_ADD_TO_PREVIOUS_BRIEF_WITH_UNDERSCORE, ctx.marshal_as<const char*>(gxtentry));
			}
			static void CHANGE_BLIP_ALPHA(Blip blip, int alpha) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_CHANGE_BLIP_ALPHA, blip, alpha); }
			static void CHANGE_BLIP_COLOUR(Blip blip, ColourIndex colour) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_CHANGE_BLIP_COLOUR, blip, colour); }
			static void CHANGE_BLIP_DISPLAY(Blip blip, unsigned int display) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_CHANGE_BLIP_DISPLAY, blip, display); }
			static void CHANGE_BLIP_NAME_FROM_ASCII(Blip blip, String^ blipName)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_CHANGE_BLIP_NAME_FROM_ASCII, blip, ctx.marshal_as<const char*>(blipName));
			}
			static void CHANGE_BLIP_NAME_FROM_TEXT_FILE(Blip blip, String^ gxtName)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_CHANGE_BLIP_NAME_FROM_TEXT_FILE, blip, ctx.marshal_as<const char*>(gxtName));
			}
			static void CHANGE_BLIP_NAME_TO_PLAYER_NAME(int blip, int playerid) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_CHANGE_BLIP_NAME_TO_PLAYER_NAME, blip, playerid); }
			static void CHANGE_BLIP_PRIORITY(Blip blip, unsigned int priority) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_CHANGE_BLIP_PRIORITY, blip, priority); }
			static void CHANGE_BLIP_SCALE(Blip blip, float scale) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_CHANGE_BLIP_SCALE, blip, scale); }
			static void CHANGE_BLIP_SPRITE(Blip blip, unsigned int sprite) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_CHANGE_BLIP_SPRITE, blip, sprite); }
			static void CHANGE_BLIP_TEAM_RELEVANCE(int blip, int relevance) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_CHANGE_BLIP_TEAM_RELEVANCE, blip, relevance); }
			static void CHANGE_PICKUP_BLIP_COLOUR(int colour) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_CHANGE_PICKUP_BLIP_COLOUR, colour); }
			static void CHANGE_PICKUP_BLIP_DISPLAY(int display) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_CHANGE_PICKUP_BLIP_DISPLAY, display); }
			static void CHANGE_PICKUP_BLIP_PRIORITY(int priority) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_CHANGE_PICKUP_BLIP_PRIORITY, priority); }
			static void CHANGE_PICKUP_BLIP_SCALE(float scale) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_CHANGE_PICKUP_BLIP_SCALE, scale); }
			static void CHANGE_PICKUP_BLIP_SPRITE(int sprite) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_CHANGE_PICKUP_BLIP_SPRITE, sprite); }
			static void CHANGE_TERRITORY_BLIP_SCALE(int blip, float Unk632, float Unk633) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_CHANGE_TERRITORY_BLIP_SCALE, blip, Unk632, Unk633); }
			static void CLEAR_ADDITIONAL_TEXT(int textid, b8 Unk634) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_CLEAR_ADDITIONAL_TEXT, textid, Unk634); }
			static void CLEAR_BRIEF() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_CLEAR_BRIEF); }
			static void CLEAR_HELP() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_CLEAR_HELP); }
			static void CLEAR_NEWS_SCROLLBAR() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_CLEAR_NEWS_SCROLLBAR); }
			static void CLEAR_ONSCREEN_COUNTER(int counterid) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_CLEAR_ONSCREEN_COUNTER, counterid); }
			static void CLEAR_ONSCREEN_TIMER(int timerid) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_CLEAR_ONSCREEN_TIMER, timerid); }
			static void CLEAR_PRINTS() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_CLEAR_PRINTS); }
			static void CLEAR_SMALL_PRINTS() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_CLEAR_SMALL_PRINTS); }
			static void CLEAR_TEXT_LABEL(String^ label)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_CLEAR_TEXT_LABEL, ctx.marshal_as<const char*>(label));
			}
			static void CLEAR_THIS_BIG_PRINT(String^ gxtentry)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_CLEAR_THIS_BIG_PRINT, ctx.marshal_as<const char*>(gxtentry));
			}
			static void CLEAR_THIS_PRINT(String^ gxtentry)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_CLEAR_THIS_PRINT, ctx.marshal_as<const char*>(gxtentry));
			}
			static void CLEAR_THIS_PRINT_BIG_NOW(b8 Unk635) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_CLEAR_THIS_PRINT_BIG_NOW, Unk635); }
			static void CONVERT_THEN_ADD_STRING_TO_HTML_SCRIPT_OBJECT(int htmlobj, String^ strgxtkey)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_CONVERT_THEN_ADD_STRING_TO_HTML_SCRIPT_OBJECT, htmlobj, ctx.marshal_as<const char*>(strgxtkey));
			}
			static void CREATE_TEMPORARY_RADAR_BLIPS_FOR_PICKUPS_IN_AREA(float x, float y, float z, float radius, int bliptype) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_CREATE_TEMPORARY_RADAR_BLIPS_FOR_PICKUPS_IN_AREA, x, y, z, radius, bliptype); }
			static void DEACTIVATE_FRONTEND() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DEACTIVATE_FRONTEND); }
			static void DIM_BLIP(Blip blip, b8 unknownTrue) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DIM_BLIP, blip, unknownTrue); }
			static void DISPLAY_AMMO(b8 display) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DISPLAY_AMMO, display); }
			static void DISPLAY_AREA_NAME(b8 display) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DISPLAY_AREA_NAME, display); }
			static void DISPLAY_CASH(b8 display) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DISPLAY_CASH, display); }
			static void DISPLAY_FRONTEND_MAP_BLIPS(b8 display) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DISPLAY_FRONTEND_MAP_BLIPS, display); }
			static void DISPLAY_GRIME_THIS_FRAME() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DISPLAY_GRIME_THIS_FRAME); }
			static void DISPLAY_HELP_TEXT_THIS_FRAME(String^ gxtkey, b8 Unk636)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_DISPLAY_HELP_TEXT_THIS_FRAME, ctx.marshal_as<const char*>(gxtkey), Unk636);
			}
			static void DISPLAY_HUD(b8 display) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DISPLAY_HUD, display); }
			static void DISPLAY_LOADING_THIS_FRAME_WITH_SCRIPT_SPRITES() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DISPLAY_LOADING_THIS_FRAME_WITH_SCRIPT_SPRITES); }
			static void DISPLAY_NON_MINIGAME_HELP_MESSAGES(b8 Unk637) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DISPLAY_NON_MINIGAME_HELP_MESSAGES, Unk637); }
			static void DISPLAY_NTH_ONSCREEN_COUNTER_WITH_STRING(int Unk638, int Unk639, int Unk640, String^ str)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_DISPLAY_NTH_ONSCREEN_COUNTER_WITH_STRING, Unk638, Unk639, Unk640, ctx.marshal_as<const char*>(str));
			}
			static void DISPLAY_ONSCREEN_TIMER_WITH_STRING(int timerid, b8 Unk641, String^ str)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_DISPLAY_ONSCREEN_TIMER_WITH_STRING, timerid, Unk641, ctx.marshal_as<const char*>(str));
			}
			static void DISPLAY_RADAR(b8 display) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DISPLAY_RADAR, display); }
			static void DISPLAY_SNIPER_SCOPE_THIS_FRAME() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DISPLAY_SNIPER_SCOPE_THIS_FRAME); }
			static void DISPLAY_TEXT(float x, float y, String^ gxtName)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_DISPLAY_TEXT, x, y, ctx.marshal_as<const char*>(gxtName));
			}
			static void DISPLAY_TEXT_SUBSTRING(ScriptAny Unk642, ScriptAny Unk643, ScriptAny Unk644, ScriptAny Unk645, ScriptAny Unk646, ScriptAny Unk647, ScriptAny Unk648) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DISPLAY_TEXT_SUBSTRING, Unk642, Unk643, Unk644, Unk645, Unk646, Unk647, Unk648); }
			static void DISPLAY_TEXT_WITH_2_NUMBERS(float x, float y, String^ gxtName, int number1, int number2)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_DISPLAY_TEXT_WITH_2_NUMBERS, x, y, ctx.marshal_as<const char*>(gxtName), number1, number2);
			}
			static void DISPLAY_TEXT_WITH_3_NUMBERS(float x, float y, String^ gxtentry, int Unk649, int Unk650, int Unk651)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_DISPLAY_TEXT_WITH_3_NUMBERS, x, y, ctx.marshal_as<const char*>(gxtentry), Unk649, Unk650, Unk651);
			}
			static void DISPLAY_TEXT_WITH_BLIP_NAME(float x, float y, String^ str, int blip)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_DISPLAY_TEXT_WITH_BLIP_NAME, x, y, ctx.marshal_as<const char*>(str), blip);
			}
			static void DISPLAY_TEXT_WITH_FLOAT(float x, float y, String^ gxtName, float value, unsigned int unknown)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_DISPLAY_TEXT_WITH_FLOAT, x, y, ctx.marshal_as<const char*>(gxtName), value, unknown);
			}
			static void DISPLAY_TEXT_WITH_LITERAL_STRING(float x, float y, String^ gxtName, String^ literalStr)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_DISPLAY_TEXT_WITH_LITERAL_STRING, x, y, ctx.marshal_as<const char*>(gxtName), ctx.marshal_as<const char*>(literalStr));
			}
			static void DISPLAY_TEXT_WITH_LITERAL_SUBSTRING(ScriptAny Unk652, ScriptAny Unk653, ScriptAny Unk654, ScriptAny Unk655, ScriptAny Unk656, ScriptAny Unk657) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DISPLAY_TEXT_WITH_LITERAL_SUBSTRING, Unk652, Unk653, Unk654, Unk655, Unk656, Unk657); }
			static void DISPLAY_TEXT_WITH_NUMBER(float x, float y, String^ gxtName, int value)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_DISPLAY_TEXT_WITH_NUMBER, x, y, ctx.marshal_as<const char*>(gxtName), value);
			}
			static void DISPLAY_TEXT_WITH_STRING(float x, float y, String^ gxtName, String^ gxtStringName)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_DISPLAY_TEXT_WITH_STRING, x, y, ctx.marshal_as<const char*>(gxtName), ctx.marshal_as<const char*>(gxtStringName));
			}
			static void DISPLAY_TEXT_WITH_STRING_AND_INT(float x, float y, String^ gxtname, String^ gxtnamenext, int val)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_DISPLAY_TEXT_WITH_STRING_AND_INT, x, y, ctx.marshal_as<const char*>(gxtname), ctx.marshal_as<const char*>(gxtnamenext), val);
			}
			static void DISPLAY_TEXT_WITH_SUBSTRING_GIVEN_HASH_KEY(float x, float y, String^ gxtkey, unsigned int gxtkey0)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_DISPLAY_TEXT_WITH_SUBSTRING_GIVEN_HASH_KEY, x, y, ctx.marshal_as<const char*>(gxtkey), gxtkey0);
			}
			static void DISPLAY_TEXT_WITH_TWO_LITERAL_STRINGS(float x, float y, String^ gxtName, String^ literalStr1, String^ literalStr2)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_DISPLAY_TEXT_WITH_TWO_LITERAL_STRINGS, x, y, ctx.marshal_as<const char*>(gxtName), ctx.marshal_as<const char*>(literalStr1), ctx.marshal_as<const char*>(literalStr2));
			}
			static void DISPLAY_TEXT_WITH_TWO_STRINGS(float x, float y, String^ gxtName, String^ gxtStringName1, String^ gxtStringName2)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_DISPLAY_TEXT_WITH_TWO_STRINGS, x, y, ctx.marshal_as<const char*>(gxtName), ctx.marshal_as<const char*>(gxtStringName1), ctx.marshal_as<const char*>(gxtStringName2));
			}
			static void DISPLAY_TEXT_WITH_TWO_SUBSTRINGS_GIVEN_HASH_KEYS(float x, float y, String^ gxtkey, unsigned int gxtkey0, unsigned int gxtkey1)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_DISPLAY_TEXT_WITH_TWO_SUBSTRINGS_GIVEN_HASH_KEYS, x, y, ctx.marshal_as<const char*>(gxtkey), gxtkey0, gxtkey1);
			}
			static void FLASH_BLIP(Blip blip, b8 on) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_FLASH_BLIP, blip, on); }
			static void FLASH_BLIP_ALT(Blip blip, b8 on) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_FLASH_BLIP_ALT, blip, on); }
			static void FLASH_RADAR(b8 flash) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_FLASH_RADAR, flash); }
			static void FLASH_ROUTE(b8 flash) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_FLASH_ROUTE, flash); }
			static void FLASH_WEAPON_ICON(b8 on) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_FLASH_WEAPON_ICON, on); }
			static void GET_BLIP_ALPHA(int blip, [OutAttribute] int% alpha)
			{
				int p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_BLIP_ALPHA, blip, &p);
				alpha = p;
			}
			static void GET_BLIP_COLOUR(Blip blip, [OutAttribute] uint32_t% pColour)
			{
				uint32_t p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_BLIP_COLOUR, blip, &p);
				pColour = p;
			}
			static void GET_BLIP_COORDS(Blip blip, [OutAttribute] Vector3% pVector)
			{
				Vector3 p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_BLIP_COORDS, blip, &p);
				pVector = p;
			}
			static void HIDE_HELP_TEXT_THIS_FRAME() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_HIDE_HELP_TEXT_THIS_FRAME); }
			static void HIDE_HUD_AND_RADAR_THIS_FRAME() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_HIDE_HUD_AND_RADAR_THIS_FRAME); }
			static void INIT_FRONTEND_HELPER_TEXT() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_INIT_FRONTEND_HELPER_TEXT); }
			static void LOAD_ADDITIONAL_TEXT(String^ textName, unsigned int textIndex)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_LOAD_ADDITIONAL_TEXT, ctx.marshal_as<const char*>(textName), textIndex);
			}
			static void LOAD_SETTINGS() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_LOAD_SETTINGS); }
			static void LOAD_TEXT_FONT(unsigned int font) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_LOAD_TEXT_FONT, font); }
			static void PAUSE_GAME() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_PAUSE_GAME); }
			static void PRINT(String^ gxtName, unsigned int timeMS, b8 enable)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_PRINT, ctx.marshal_as<const char*>(gxtName), timeMS, enable);
			}
			static void PRINTFLOAT(float value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_PRINTFLOAT, value); }
			static void PRINTINT(int value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_PRINT, value); }
			static void PRINTNL() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_PRINTNL); }
			static void PRINTSTRING(String^ value)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_PRINTSTRING, ctx.marshal_as<const char*>(value));
			}
			static void PRINTVECTOR(float x, float y, float z) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_PRINTVECTOR, x, y, z); }
			static void PRINT_BIG(String^ gxtName, unsigned int timeMS, b8 enable)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_PRINT_BIG, ctx.marshal_as<const char*>(gxtName), timeMS, enable);
			}
			static void PRINT_BIG_Q(String^ gxtentry, int time, int flag)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_PRINT_BIG_Q, ctx.marshal_as<const char*>(gxtentry), time, flag);
			}
			static void PRINT_HELP(String^ gxtName)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_PRINT_HELP, ctx.marshal_as<const char*>(gxtName));
			}
			static void PRINT_HELP_FOREVER(String^ gxtName)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_PRINT_HELP_FOREVER, ctx.marshal_as<const char*>(gxtName));
			}
			static void PRINT_HELP_FOREVER_WITH_NUMBER(String^ gxtName, int value)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_PRINT_HELP_FOREVER_WITH_NUMBER, ctx.marshal_as<const char*>(gxtName), value);
			}
			static void PRINT_HELP_FOREVER_WITH_STRING(String^ gxtName, String^ gxtText)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_PRINT_HELP_FOREVER_WITH_STRING, ctx.marshal_as<const char*>(gxtName), ctx.marshal_as<const char*>(gxtText));
			}
			static void PRINT_HELP_FOREVER_WITH_STRING_NO_SOUND(String^ gxtName, String^ gxtText)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_PRINT_HELP_FOREVER_WITH_STRING_NO_SOUND, ctx.marshal_as<const char*>(gxtName), ctx.marshal_as<const char*>(gxtText));
			}
			static void PRINT_HELP_OVER_FRONTEND(String^ gxtentry)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_PRINT_HELP_OVER_FRONTEND, ctx.marshal_as<const char*>(gxtentry));
			}
			static void PRINT_HELP_WITH_NUMBER(String^ gxtName, int value)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_PRINT_HELP_WITH_NUMBER, ctx.marshal_as<const char*>(gxtName), value);
			}
			static void PRINT_HELP_WITH_STRING(String^ gxtName, const char* gxtText)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_PRINT_HELP_WITH_STRING, ctx.marshal_as<const char*>(gxtName), gxtText);
			}
			static void PRINT_HELP_WITH_STRING_NO_SOUND(String^ gxtName, String^ gxtText)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_PRINT_HELP_WITH_STRING_NO_SOUND, ctx.marshal_as<const char*>(gxtName), ctx.marshal_as<const char*>(gxtText));
			}
			static void PRINT_NOW(String^ gxtName, unsigned int timeMS, b8 enable)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_PRINT_NOW, ctx.marshal_as<const char*>(gxtName), timeMS, enable);
			}
			static void PRINT_STRING_IN_STRING(String^ gxtName, String^ gxtText, unsigned int timeMS, b8 enable)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_PRINT_STRING_IN_STRING, ctx.marshal_as<const char*>(gxtName), ctx.marshal_as<const char*>(gxtText), timeMS, enable);
			}
			static void PRINT_STRING_IN_STRING_NOW(String^ gxtName, String^ gxtText, unsigned int timeMS, b8 enable)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_PRINT_STRING_IN_STRING_NOW, ctx.marshal_as<const char*>(gxtName), ctx.marshal_as<const char*>(gxtText), timeMS, enable);
			}
			static void PRINT_STRING_WITH_LITERAL_STRING(String^ gxtentry, String^ string, int time, int flag)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_PRINT_STRING_WITH_LITERAL_STRING, ctx.marshal_as<const char*>(gxtentry), ctx.marshal_as<const char*>(string), time, flag);
			}
			static void PRINT_STRING_WITH_LITERAL_STRING_NOW(String^ gxtName, String^ text, unsigned int timeMS, b8 enable)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_PRINT_STRING_WITH_LITERAL_STRING_NOW, ctx.marshal_as<const char*>(gxtName), ctx.marshal_as<const char*>(text), timeMS, enable);
			}
			static void PRINT_STRING_WITH_SUBSTRING_GIVEN_HASH_KEY_NOW(String^ gxtkey0, unsigned int gxtkey1, int time, int style)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_PRINT_STRING_WITH_SUBSTRING_GIVEN_HASH_KEY_NOW, ctx.marshal_as<const char*>(gxtkey0), gxtkey1, time, style);
			}
			static void PRINT_STRING_WITH_TWO_LITERAL_STRINGS(String^ gxtentry, String^ string1, String^ string2, int time, int flag)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_PRINT_STRING_WITH_TWO_LITERAL_STRINGS, ctx.marshal_as<const char*>(gxtentry), ctx.marshal_as<const char*>(string1), ctx.marshal_as<const char*>(string2), time, flag);
			}
			static void PRINT_STRING_WITH_TWO_LITERAL_STRINGS_NOW(String^ gxtentry, String^ string1, String^ string2, int time, int flag)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_PRINT_STRING_WITH_TWO_LITERAL_STRINGS_NOW, ctx.marshal_as<const char*>(gxtentry), ctx.marshal_as<const char*>(string1), ctx.marshal_as<const char*>(string2), time, flag);
			}
			static void PRINT_WITH_2_NUMBERS(String^ gxtName, int value1, int value2, unsigned int timeMS, b8 enable)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_PRINT_WITH_2_NUMBERS, ctx.marshal_as<const char*>(gxtName), value1, value2, timeMS, enable);
			}
			static void PRINT_WITH_2_NUMBERS_BIG(String^ gxtentry, int Unk662, int Unk663, int time, int flag)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_PRINT_WITH_2_NUMBERS_BIG, ctx.marshal_as<const char*>(gxtentry), Unk662, Unk663, time, flag);
			}
			static void PRINT_WITH_2_NUMBERS_NOW(String^ gxtName, int value1, int value2, unsigned int timeMS, b8 enable)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_PRINT_WITH_2_NUMBERS_NOW, ctx.marshal_as<const char*>(gxtName), value1, value2, timeMS, enable);
			}
			static void PRINT_WITH_3_NUMBERS(String^ gxtentry, int Unk664, int Unk665, int Unk666, int time, int flag)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_PRINT_WITH_3_NUMBERS, ctx.marshal_as<const char*>(gxtentry), Unk664, Unk665, Unk666, time, flag);
			}
			static void PRINT_WITH_3_NUMBERS_NOW(String^ gxtentry, int Unk667, int Unk668, int Unk669, int time, int flag)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_PRINT_WITH_3_NUMBERS_NOW, ctx.marshal_as<const char*>(gxtentry), Unk667, Unk668, Unk669, time, flag);
			}
			static void PRINT_WITH_4_NUMBERS(String^ gxtentry, int Unk670, int Unk671, int Unk672, int Unk673, int time, int flag)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_PRINT_WITH_4_NUMBERS, ctx.marshal_as<const char*>(gxtentry), Unk670, Unk671, Unk672, Unk673, time, flag);
			}
			static void PRINT_WITH_4_NUMBERS_NOW(String^ gxtentry, int Unk674, int Unk675, int Unk676, int Unk677, int time, int flag)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_PRINT_WITH_4_NUMBERS_NOW, ctx.marshal_as<const char*>(gxtentry), Unk674, Unk675, Unk676, Unk677, time, flag);
			}
			static void PRINT_WITH_5_NUMBERS(String^ gxtentry, int Unk678, int Unk679, int Unk680, int Unk681, int Unk682, int time, int flag)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_PRINT_WITH_5_NUMBERS, ctx.marshal_as<const char*>(gxtentry), Unk678, Unk679, Unk680, Unk681, Unk682, time, flag);
			}
			static void PRINT_WITH_5_NUMBERS_NOW(String^ gxtentry, int Unk683, int Unk684, int Unk685, int Unk686, int Unk687, int time, int flag)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_PRINT_WITH_5_NUMBERS_NOW, ctx.marshal_as<const char*>(gxtentry), Unk683, Unk684, Unk685, Unk686, Unk687, time, flag);
			}
			static void PRINT_WITH_6_NUMBERS(String^ gxtentry, int Unk688, int Unk689, int Unk690, int Unk691, int Unk692, int Unk693, int time, int flag)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_PRINT_WITH_6_NUMBERS, ctx.marshal_as<const char*>(gxtentry), Unk688, Unk689, Unk690, Unk691, Unk692, Unk693, time, flag);
			}
			static void PRINT_WITH_6_NUMBERS_NOW(String^ gxtentry, int Unk694, int Unk695, int Unk696, int Unk697, int Unk698, int Unk699, int time, int flag)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_PRINT_WITH_6_NUMBERS_NOW, ctx.marshal_as<const char*>(gxtentry), Unk694, Unk695, Unk696, Unk697, Unk698, Unk699, time, flag);
			}
			static void PRINT_WITH_NUMBER(String^ gxtName, int value, unsigned int timeMS, b8 enable)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_PRINT_WITH_NUMBER, ctx.marshal_as<const char*>(gxtName), value, timeMS, enable);
			}
			static void PRINT_WITH_NUMBER_BIG(String^ gxtName, int value, unsigned int timeMS, b8 enable)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_PRINT_WITH_NUMBER_BIG, ctx.marshal_as<const char*>(gxtName), value, timeMS, enable);
			}
			static void PRINT_WITH_NUMBER_NOW(String^ gxtName, int value, unsigned int timeMS, b8 enable)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_PRINT_WITH_NUMBER_NOW, ctx.marshal_as<const char*>(gxtName), value, timeMS, enable);
			}
			static void REMOVE_BLIP(Blip blip) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_REMOVE_BLIP, blip); }
			static void SET_ALWAYS_DISPLAY_WEAPON_PICKUP_MESSAGE(b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_ALWAYS_DISPLAY_WEAPON_PICKUP_MESSAGE, set); }
			static void SET_BLIP_AS_FRIENDLY(Blip blip, b8 value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_BLIP_AS_FRIENDLY, blip, value); }
			static void SET_BLIP_AS_SHORT_RANGE(Blip blip, b8 value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_BLIP_AS_SHORT_RANGE, blip, value); }
			static void SET_BLIP_MARKER_LONG_DISTANCE(int blip, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_BLIP_MARKER_LONG_DISTANCE, blip, set); }
			static void SET_HIDE_WEAPON_ICON(b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_HIDE_WEAPON_ICON, set); }
			static void SET_MESSAGES_WAITING(b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_MESSAGES_WAITING, set); }
			static void SET_MESSAGE_FORMATTING(b8 Unk700, int Unk701, int Unk702) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_MESSAGE_FORMATTING, Unk700, Unk701, Unk702); }
			static void SET_MULTIPLAYER_HUD_CASH(unsigned int cash) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_MULTIPLAYER_HUD_CASH, cash); }
			static void SET_MULTIPLAYER_HUD_TIME(String^ str)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_MULTIPLAYER_HUD_TIME, ctx.marshal_as<const char*>(str));
			}
			static void SET_ONSCREEN_COUNTER_FLASH_WHEN_FIRST_DISPLAYED(int counterid, b8 flash) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_ONSCREEN_COUNTER_FLASH_WHEN_FIRST_DISPLAYED, counterid, flash); }
			static void SET_RADAR_AS_INTERIOR_THIS_FRAME() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_RADAR_AS_INTERIOR_THIS_FRAME); }
			static void SET_RADAR_ZOOM(float zoom) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_RADAR_ZOOM, zoom); }
			static void SET_ROUTE(Blip blip, b8 value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_ROUTE, blip, value); }
			static void SET_TEXT_BACKGROUND(b8 value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_TEXT_BACKGROUND, value); }
			static void SET_TEXT_CENTRE(b8 value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_TEXT_CENTRE, value); }
			static void SET_TEXT_CENTRE_WRAPX(float wrapx) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_TEXT_CENTRE_WRAPX, wrapx); }
			static void SET_TEXT_COLOUR(unsigned int r, unsigned int g, unsigned int b, unsigned int a) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_TEXT_COLOUR, r, g, b, a); }
			static void SET_TEXT_DRAW_BEFORE_FADE(b8 value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_TEXT_DRAW_BEFORE_FADE, value); }
			static void SET_TEXT_DROPSHADOW(b8 displayShadow, unsigned int r, unsigned int g, unsigned int b, unsigned int a) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_TEXT_DROPSHADOW, displayShadow, r, g, b, a); }
			static void SET_TEXT_EDGE(b8 displayEdge, unsigned int r, unsigned int g, unsigned int b, unsigned int a) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_TEXT_EDGE, displayEdge, r, g, b, a); }
			static void SET_TEXT_FONT(unsigned int font) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_TEXT_FONT, font); }
			static void SET_TEXT_INPUT_ACTIVE(b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_TEXT_INPUT_ACTIVE, set); }
			static void SET_TEXT_JUSTIFY(b8 value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_TEXT_JUSTIFY, value); }
			static void SET_TEXT_LINE_DISPLAY(unsigned int unk1, unsigned int unk2) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_TEXT_LINE_DISPLAY, unk1, unk2); }
			static void SET_TEXT_LINE_HEIGHT_MULT(float lineHeight) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_TEXT_LINE_HEIGHT_MULT, lineHeight); }
			static void SET_TEXT_PROPORTIONAL(b8 value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_TEXT_PROPORTIONAL, value); }
			static void SET_TEXT_RENDER_ID(unsigned int renderId) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_TEXT_RENDER_ID, renderId); }
			static void SET_TEXT_RIGHT_JUSTIFY(b8 value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_TEXT_RIGHT_JUSTIFY, value); }
			static void SET_TEXT_SCALE(float w, float h) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_TEXT_SCALE, w, h); }
			static void SET_TEXT_TO_USE_TEXT_FILE_COLOURS(b8 value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_TEXT_TO_USE_TEXT_FILE_COLOURS, value); }
			static void SET_TEXT_USE_UNDERSCORE(b8 value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_TEXT_USE_UNDERSCORE, value); }
			static void SET_TEXT_VIEWPORT_ID(int id) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_TEXT_VIEWPORT_ID, id); }
			static void SET_TEXT_WRAP(float unk1, float unk2) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_TEXT_WRAP, unk1, unk2); }
			static void SHOW_SIGNIN_UI() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SHOW_SIGNIN_UI); }
			static void SHOW_UPDATE_STATS(b8 show) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SHOW_UPDATE_STATS, show); }
			static void UNLOAD_TEXT_FONT() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_UNLOAD_TEXT_FONT); }
			static void UNPAUSE_GAME() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_UNPAUSE_GAME); }
			static String^ GET_STRING_FROM_TEXT_FILE(String^ gxtentry)
			{
				msclr::interop::marshal_context ctx;
				return gcnew String(NativeInvoke::Invoke<char*>(NATIVE_GET_STRING_FROM_TEXT_FILE, ctx.marshal_as<const char*>(gxtentry)));
			}
			static String^ GET_DISPLAY_NAME_FROM_VEHICLE_MODEL(unsigned int model)
			{
				return gcnew String(NativeInvoke::Invoke<char*>(NATIVE_GET_DISPLAY_NAME_FROM_VEHICLE_MODEL, model));
			}
			static String^ GET_NAME_OF_INFO_ZONE(f32 x, f32 y, f32 z)
			{
				return gcnew String(NativeInvoke::Invoke<char*>(NATIVE_GET_NAME_OF_INFO_ZONE, x, y, z));
			}
			static String^ GET_NAME_OF_ZONE(f32 x, f32 y, f32 z)
			{
				return gcnew String(NativeInvoke::Invoke< char*>(NATIVE_GET_NAME_OF_ZONE, x, y, z));
			}
			static void USE_PREVIOUS_FONT_SETTINGS() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_USE_PREVIOUS_FONT_SETTINGS); }
			static int CREATE_CHECKPOINT(int type, float x, float y, float z, float Unk709, float Unk710) { return NativeInvoke::Invoke<int, int, float, float, float, float, float>(NATIVE_CREATE_CHECKPOINT, type, x, y, z, Unk709, Unk710); }
			static void DELETE_CHECKPOINT(unsigned int checkpoint) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DELETE_CHECKPOINT, checkpoint); }
			static void DISABLE_END_CREDITS_FADE() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DISABLE_END_CREDITS_FADE); }
			static void DO_SCREEN_FADE_IN(unsigned int timeMS) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DO_SCREEN_FADE_IN, timeMS); }
			static void DO_SCREEN_FADE_IN_UNHACKED(unsigned int timeMS) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DO_SCREEN_FADE_IN_UNHACKED, timeMS); }
			static void DO_SCREEN_FADE_OUT(unsigned int timeMS) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DO_SCREEN_FADE_OUT, timeMS); }
			static void DO_SCREEN_FADE_OUT_UNHACKED(unsigned int timeMS) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DO_SCREEN_FADE_OUT_UNHACKED, timeMS); }
			static void DRAW_CHECKPOINT(Vector3 pos, float radius, Color color) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DRAW_CHECKPOINT, pos.X, pos.Y, pos.Z, radius, (int)color.R, (int)color.G, (int)color.B); }
			static void DRAW_CHECKPOINT(float x, float y, float z, float radius, int r, int g, int b) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DRAW_CHECKPOINT, x, y, z, radius, r, g, b); }
			static void DRAW_CHECKPOINT_WITH_ALPHA(Vector3 pos, float radius, Color color) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DRAW_CHECKPOINT_WITH_ALPHA, pos.X, pos.Y, pos.Z, radius, (int)color.R, (int)color.G, (int)color.B, (int)color.A); }
			static void DRAW_CHECKPOINT_WITH_ALPHA(float x, float y, float z, float radius, int r, int g, int b, int a) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DRAW_CHECKPOINT_WITH_ALPHA, x, y, z, radius, r, g, b, a); }
			static void DRAW_COLOURED_CYLINDER(float x, float y, float z, float Unk712, float Unk713, int r, int g, int b, int a) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DRAW_COLOURED_CYLINDER, x, y, z, Unk712, Unk713, r, g, b, a); }
			static void DRAW_CORONA(Vector3 pos, float radius, int Unk714, float Unk715, Color color) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DRAW_CORONA, pos.X, pos.Y, pos.Z, radius, Unk714, Unk715, (int)color.R, (int)color.G, (int)color.B); }
			static void DRAW_CORONA(float x, float y, float z, float radius, int Unk714, float Unk715, int r, int g, int b) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DRAW_CORONA, x, y, z, radius, Unk714, Unk715, r, g, b); }
			static void DRAW_CURVED_WINDOW(float Unk719, float Unk720, float Unk721, float Unk722, unsigned int alpha) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DRAW_CURVED_WINDOW, Unk719, Unk720, Unk721, Unk722, alpha); }
			static void DRAW_CURVED_WINDOW_NOTEXT(float Unk723, float Unk724, float Unk725, float Unk726, int Unk727) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DRAW_CURVED_WINDOW_NOTEXT, Unk723, Unk724, Unk725, Unk726, Unk727); }
			static void DRAW_CURVED_WINDOW_TEXT(float Unk728, float Unk729, float Unk730, int Unk731, int Unk732, String^ str0, String^ str1, int Unk733)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke<ScriptVoid>(NATIVE_DRAW_CURVED_WINDOW_TEXT, Unk728, Unk729, Unk730, Unk731, Unk732, ctx.marshal_as<const char*>(str0), ctx.marshal_as<const char*>(str1), Unk733);
			}
			static void DRAW_FRONTEND_HELPER_TEXT(String^ str0, String^ str1, b8 Unk734)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke<ScriptVoid>(NATIVE_DRAW_FRONTEND_HELPER_TEXT, ctx.marshal_as<const char*>(str0), ctx.marshal_as<const char*>(str1), Unk734);
			}
			static void DRAW_LIGHT_WITH_RANGE(float x, float y, float z, int r, int g, int b, float width, float height) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DRAW_LIGHT_WITH_RANGE, x, y, z, r, g, b, width, height); }
			static void DRAW_MOVIE(float Unk735, float Unk736, float Unk737, float Unk738, float Unk739, int r, int g, int b, int a) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DRAW_MOVIE, Unk735, Unk736, Unk737, Unk738, Unk739, r, g, b, a); }
			static void DRAW_RECT(float x1, float y1, float x2, float y2, int r, int g, int b, int a) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DRAW_RECT, x1, y1, x2, y2, r, g, b, a); }
			static void DRAW_SPHERE(float x, float y, float z, float radius) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DRAW_SPHERE, x, y, z, radius); }
			static void DRAW_SPRITE(unsigned int texture, float xsize, float ysize, float width, float height, float angle, int r, int g, int b, int a) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DRAW_SPRITE, texture, xsize, ysize, width, height, angle, r, g, b, a); }
			static void DRAW_SPRITE_FRONT_BUFF(float x0, float y0, float x1, float y1, float rotation, int r, int g, int b, int a) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DRAW_SPRITE_FRONT_BUFF, x0, y0, x1, y1, rotation, r, g, b, a); }
			static void DRAW_SPRITE_PHOTO(float x0, float y0, float x1, float y1, float rotation, int r, int g, int b, int a) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DRAW_SPRITE_PHOTO, x0, y0, x1, y1, rotation, r, g, b, a); }
			static void DRAW_SPRITE_WITH_UV(unsigned int texture, float Unk748, float Unk749, float Unk750, float Unk751, float angle, int r, int g, int b, int a) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DRAW_SPRITE_WITH_UV, texture, Unk748, Unk749, Unk750, Unk751, angle, r, g, b, a); }
			static void DRAW_TOPLEVEL_SPRITE(unsigned int texture, float Unk760, float Unk761, float Unk762, float Unk763, float angle, int r, int g, int b, int a) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DRAW_TOPLEVEL_SPRITE, texture, Unk760, Unk761, Unk762, Unk763, angle, r, g, b, a); }
			static void DRAW_WINDOW(float Unk764, float Unk765, float Unk766, float Unk767, String^ str, unsigned int alpha)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_DRAW_WINDOW, Unk764, Unk765, Unk766, Unk767, ctx.marshal_as<const char*>(str), alpha);
			}
			static void DRAW_WINDOW_TEXT(float Unk768, float Unk769, float Unk770, int Unk771, String^ str0, int Unk772)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke<ScriptVoid>(NATIVE_DRAW_WINDOW_TEXT, Unk768, Unk769, Unk770, Unk771, ctx.marshal_as<const char*>(str0), Unk772);
			}
			static void ENABLE_DEFERRED_LIGHTING(b8 enable) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ENABLE_DEFERRED_LIGHTING, enable); }
			static void ENABLE_END_CREDITS_FADE() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ENABLE_END_CREDITS_FADE); }
			static void ENABLE_SHADOWS(b8 enable) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ENABLE_SHADOWS, enable); }
			static void GET_FRAME_TIME([OutAttribute] float% time)
			{
				float p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_FRAME_TIME, &p);
				time = p;
			}
			static void GET_HELP_MESSAGE_BOX_SIZE([OutAttribute] float% pX, [OutAttribute] float% pY)
			{
				float x, y;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_HELP_MESSAGE_BOX_SIZE, &x, &y);
				pX = x;
				pY = y;
			}
			static void GET_PHYSICAL_SCREEN_RESOLUTION([OutAttribute] float% pX, [OutAttribute] float% pY)
			{
				float x, y;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_PHYSICAL_SCREEN_RESOLUTION, &x, &y);
				pX = x;
				pY = y;
			}
			static void GET_SCREEN_RESOLUTION([OutAttribute] int% pX, [OutAttribute] int% pY)
			{
				int x, y;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_SCREEN_RESOLUTION, &x, &y);
				pX = x;
				pY = y;
			}
			static void GET_TEXTURE_RESOLUTION(unsigned int texture, [OutAttribute] float% pX, [OutAttribute] float% pY)
			{
				float x, y;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_TEXTURE_RESOLUTION, texture, &x, &y);
				pX = x;
				pY = y;
			}
			static void IMPROVE_LOW_PERFORMANCE_MISSION_PER_FRAME_FLAG() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_IMPROVE_LOW_PERFORMANCE_MISSION_PER_FRAME_FLAG); }
			static void LINE(float x0, float y0, float z0, float x1, float y1, float z1) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_LINE, x0, y0, z0, x1, y1, z1); }
			static void PLAY_MOVIE() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_PLAY_MOVIE); }
			static void RELEASE_MOVIE() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_RELEASE_MOVIE); }
			static void SET_CURRENT_MOVIE(String^ filename)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CURRENT_MOVIE, ctx.marshal_as<const char*>(filename));
			}
			static void SET_HELP_MESSAGE_BOX_SIZE(float Unk773) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_HELP_MESSAGE_BOX_SIZE, Unk773); }
			static void SET_INSTANT_WIDESCREEN_BORDERS(b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_INSTANT_WIDESCREEN_BORDERS, set); }
			static void SET_MASK(float Unk774, float Unk775, float Unk776, float Unk777) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_MASK, Unk774, Unk775, Unk776, Unk777); }
			static void SET_SCREEN_FADE(int viewportid, int Unk778, int Unk779, b8 Unk780, int r, int g, int b, int a, int Unk781, float Unk782, float Unk783) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_SCREEN_FADE, viewportid, Unk778, Unk779, Unk780, r, g, b, a, Unk781, Unk782, Unk783); }
			static void SET_SPRITES_DRAW_BEFORE_FADE(b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_SPRITES_DRAW_BEFORE_FADE, set); }
			static void SET_USE_HIGHDOF(b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_USE_HIGHDOF, set); }
			static void SET_WIDESCREEN_BORDERS(b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_WIDESCREEN_BORDERS, set); }
			static void SET_WIDESCREEN_FORMAT(int wideformatid) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_WIDESCREEN_FORMAT, wideformatid); }
			static void STOP_MOVIE() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_STOP_MOVIE); }
			static void TOGGLE_TOPLEVEL_SPRITE(b8 toggle) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TOGGLE_TOPLEVEL_SPRITE, toggle); }
			static void USE_MASK(b8 use) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_USE_MASK, use); }
			//static void REMOVE_SPHERE(unsigned int sphere) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_REMOVE_SPHERE, sphere); }
			static void DECREMENT_FLOAT_STAT(int stat, float val) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DECREMENT_FLOAT_STAT, stat, val); }
			static void DECREMENT_INT_STAT(unsigned int stat, unsigned int amount) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DECREMENT_INT_STAT, stat, amount); }
			static void INCREMENT_FLOAT_STAT(int stat, float val) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_INCREMENT_FLOAT_STAT, stat, val); }
			static void INCREMENT_FLOAT_STAT_NO_MESSAGE(unsigned int stat, float value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_INCREMENT_FLOAT_STAT_NO_MESSAGE, stat, value); }
			static void INCREMENT_INT_STAT(unsigned int stat, unsigned int value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_INCREMENT_INT_STAT, stat, value); }
			static void INCREMENT_INT_STAT_NO_MESSAGE(unsigned int stat, unsigned int value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_INCREMENT_INT_STAT_NO_MESSAGE, stat, value); }
			static void PLAYSTATS_CHEAT(int stat) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_PLAYSTATS_CHEAT, stat); }
			static void PLAYSTATS_FLOAT(int Unk785, float Unk786) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_PLAYSTATS_FLOAT, Unk785, Unk786); }
			static void PLAYSTATS_INT(ScriptAny Unk787, int Unk788) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_PLAYSTATS_INT, Unk787, Unk788); }
			static void PLAYSTATS_INT_FLOAT(ScriptAny Unk789, int Unk790, float Unk791) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_PLAYSTATS_INT_FLOAT, Unk789, Unk790, Unk791); }
			static void PLAYSTATS_INT_INT(ScriptAny Unk792, int Unk793, int Unk794) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_PLAYSTATS_INT_INT, Unk792, Unk793, Unk794); }
			static void PLAYSTATS_MISSION_CANCELLED(int Unk795) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_PLAYSTATS_MISSION_CANCELLED, Unk795); }
			static void PLAYSTATS_MISSION_FAILED(int Unk796) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_PLAYSTATS_MISSION_FAILED, Unk796); }
			static void PLAYSTATS_MISSION_PASSED(String^ str0)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_PLAYSTATS_MISSION_PASSED, ctx.marshal_as<const char*>(str0));
			}
			static void PLAYSTATS_MISSION_STARTED(int Unk797) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_PLAYSTATS_MISSION_STARTED, Unk797); }
			static void REGISTER_FLOAT_STAT(int stat, float val) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_REGISTER_FLOAT_STAT, stat, val); }
			static void REGISTER_INT_STAT(int stat, int val) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_REGISTER_INT_STAT, stat, val); }
			static void REGISTER_STRING_FOR_FRONTEND_STAT(int stat, String^ str)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_REGISTER_STRING_FOR_FRONTEND_STAT, stat, ctx.marshal_as<const char*>(str));
			}
			static void SET_FLOAT_STAT(unsigned int stat, float value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_FLOAT_STAT, stat, value); }
			static void SET_INT_STAT(unsigned int stat, unsigned int value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_INT_STAT, stat, value); }
			static void SET_STAT_FRONTEND_ALWAYS_VISIBLE(b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_STAT_FRONTEND_ALWAYS_VISIBLE, set); }
			static void SET_STAT_FRONTEND_DISPLAY_TYPE(int stat, int type) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_STAT_FRONTEND_DISPLAY_TYPE, stat, type); }
			static void SET_STAT_FRONTEND_NEVER_VISIBLE(int stat) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_STAT_FRONTEND_NEVER_VISIBLE, stat); }
			static void SET_STAT_FRONTEND_VISIBILITY(int stat, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_STAT_FRONTEND_VISIBILITY, stat, set); }
			static void SET_STAT_FRONTEND_VISIBLE_AFTER_INCREMENTED(int stat) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_STAT_FRONTEND_VISIBLE_AFTER_INCREMENTED, stat); }
			static void REGISTER_WORLD_POINT_SCRIPT_BRAIN(String^ ScriptName, float radius)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_REGISTER_WORLD_POINT_SCRIPT_BRAIN, ctx.marshal_as<const char*>(ScriptName), radius);
			}
			static void SWITCH_OBJECT_BRAINS(int brain, b8 switchstate) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SWITCH_OBJECT_BRAINS, brain, switchstate); }
			static void ADD_LINE_TO_MOBILE_PHONE_CALL(int id, String^ name, String^ text)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_ADD_LINE_TO_MOBILE_PHONE_CALL, id, ctx.marshal_as<const char*>(name), ctx.marshal_as<const char*>(text));
			}
			static void CREATE_MOBILE_PHONE(int Unk799) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_CREATE_MOBILE_PHONE, Unk799); }
			static void DESTROY_MOBILE_PHONE() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DESTROY_MOBILE_PHONE); }
			static void GET_MOBILE_PHONE_RENDER_ID([OutAttribute] unsigned int% pRenderId)
			{
				unsigned int p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_MOBILE_PHONE_RENDER_ID, &p);
				pRenderId = p;
			}
			static void NEW_MOBILE_PHONE_CALL() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_NEW_MOBILE_PHONE_CALL); }
			static void PREVIEW_RINGTONE(int RingtoneId) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_PREVIEW_RINGTONE, RingtoneId); }
			static void SCRIPT_IS_MOVING_MOBILE_PHONE_OFFSCREEN(b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SCRIPT_IS_MOVING_MOBILE_PHONE_OFFSCREEN, set); }
			static void SCRIPT_IS_USING_MOBILE_PHONE(b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SCRIPT_IS_USING_MOBILE_PHONE, set); }
			static void SET_MOBILE_PHONE_POSITION(float x, float y, float z) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_MOBILE_PHONE_POSITION, x, y, z); }
			static void SET_MOBILE_PHONE_RADIO_STATE(b8 state) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_MOBILE_PHONE_RADIO_STATE, state); }
			static void SET_MOBILE_PHONE_ROTATION(float x, float y, float z) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_MOBILE_PHONE_ROTATION, x, y, z); }
			static void SET_MOBILE_PHONE_SCALE(float scale) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_MOBILE_PHONE_SCALE, scale); }
			static void SET_MOBILE_RADIO_ENABLED_DURING_GAMEPLAY(b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_MOBILE_RADIO_ENABLED_DURING_GAMEPLAY, set); }
			static void SET_MOBILE_RING_TYPE(int type) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_MOBILE_RING_TYPE, type); }
			static void SET_PHONE_HUD_ITEM(int id, String^ gxttext, int Unk800)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_PHONE_HUD_ITEM, id, ctx.marshal_as<const char*>(gxttext), Unk800);
			}
			static void START_CUSTOM_MOBILE_PHONE_RINGING(int RingtoneId) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_START_CUSTOM_MOBILE_PHONE_RINGING, RingtoneId); }
			static void START_MOBILE_PHONE_CALL(Ped callfrom, String^ callfromvoice, Ped callto, String^ calltovoice, b8 flag0, b8 flag1)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_START_MOBILE_PHONE_CALL, callfrom, ctx.marshal_as<const char*>(callfromvoice), callto, ctx.marshal_as<const char*>(calltovoice), flag0, flag1);
			}
			static void START_MOBILE_PHONE_CALLING() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_START_MOBILE_PHONE_CALLING); }
			static void START_MOBILE_PHONE_RINGING() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_START_MOBILE_PHONE_RINGING); }
			static void START_PED_MOBILE_RINGING(Ped ped, int Unk801) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_START_PED_MOBILE_RINGING, ped, Unk801); }
			static void STOP_MOBILE_PHONE_RINGING() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_STOP_MOBILE_PHONE_RINGING); }
			static void STOP_PREVIEW_RINGTONE() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_STOP_PREVIEW_RINGTONE); }
			static void ADD_TO_HTML_SCRIPT_OBJECT(int htmlobj, String^ htmlcode)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_ADD_TO_HTML_SCRIPT_OBJECT, htmlobj, ctx.marshal_as<const char*>(htmlcode));
			}
			static void DELETE_ALL_HTML_SCRIPT_OBJECTS() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DELETE_ALL_HTML_SCRIPT_OBJECTS); }
			static void DELETE_HTML_SCRIPT_OBJECT(int htmlobj) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DELETE_HTML_SCRIPT_OBJECT, htmlobj); }
			static void GET_WEB_PAGE_LINK_POSN(int htmlviewport, int linkid, [OutAttribute] float% pX, [OutAttribute] float% pY)
			{
				float x, y;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_WEB_PAGE_LINK_POSN, htmlviewport, linkid, &x, &y);
				pX = x;
				pY = y;
			}
			static void LOAD_WEB_PAGE(int htmlviewport, String^ webaddress)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_LOAD_WEB_PAGE, htmlviewport, ctx.marshal_as<const char*>(webaddress));
			}
			static void RELOAD_WEB_PAGE(int htmlviewport) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_RELOAD_WEB_PAGE, htmlviewport); }
			static void SET_WEB_PAGE_LINK_ACTIVE(int htmlviewport, int linkid, b8 active) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_WEB_PAGE_LINK_ACTIVE, htmlviewport, linkid, active); }
			static void SET_WEB_PAGE_SCROLL(int htmlviewport, float scroll) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_WEB_PAGE_SCROLL, htmlviewport, scroll); }
			static void CLEAR_TIMECYCLE_MODIFIER() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_CLEAR_TIMECYCLE_MODIFIER); }
			static void FORCE_TIME_OF_DAY(unsigned int hour, unsigned int minute) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_FORCE_TIME_OF_DAY, hour, minute); }
			static void FORWARD_TO_TIME_OF_DAY(unsigned int hour, unsigned int minute) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_FORWARD_TO_TIME_OF_DAY, hour, minute); }
			static void FREEZE_ONSCREEN_TIMER(b8 freeze) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_FREEZE_ONSCREEN_TIMER, freeze); }
			static void GET_GAME_TIMER([OutAttribute] unsigned int% pTimer)
			{
				unsigned int p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_GAME_TIMER, &p);
				pTimer = p;
			}
			static void GET_TIME_OF_DAY([OutAttribute] int% hour, [OutAttribute] int% minute)
			{
				int p1, p2;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_TIME_OF_DAY, &p1, &p2);
				hour = p1;
				minute = p2;
			}
			static void SET_MOVIE_TIME(float time) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_MOVIE_TIME, time); }
			static void SET_TIMECYCLE_MODIFIER(String^ name)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_TIMECYCLE_MODIFIER, ctx.marshal_as<const char*>(name));
			}
			static void SET_TIMER_BEEP_COUNTDOWN_TIME(int timerid, int beeptime) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_TIMER_BEEP_COUNTDOWN_TIME, timerid, beeptime); }
			static void SET_TIME_OF_DAY(unsigned int hour, unsigned int minute) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_TIME_OF_DAY, hour, minute); }
			static void SET_TIME_OF_NEXT_APPOINTMENT(int time) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_TIME_OF_NEXT_APPOINTMENT, time); }
			static void SET_TIME_ONE_DAY_BACK() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_TIME_ONE_DAY_BACK); }
			static void SET_TIME_ONE_DAY_FORWARD() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_TIME_ONE_DAY_FORWARD); }
			static void SET_TIME_SCALE(float scale) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_TIME_SCALE, scale); }
			static void GENERATE_DIRECTIONS(float x, float y, float z, [OutAttribute] int% direction, [OutAttribute] Vector3% Unk811)
			{
				int p1;
				Vector3 p2;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GENERATE_DIRECTIONS, x, y, z, &p1, &p2);
				direction = p1;
				Unk811 = p2;
			}
			static void GET_RANDOM_CAR_BACK_BUMPER_IN_SPHERE(float x, float y, float z, float radius, int Unk812, int Unk813, [OutAttribute] Vehicle% veh)
			{
				Vehicle p;
				NativeInvoke::Invoke<ScriptVoid>(NATIVE_GET_RANDOM_CAR_BACK_BUMPER_IN_SPHERE, x, y, z, radius, Unk812, Unk813, &p);
				veh = p;
			}
			static void GET_RANDOM_CAR_FRONT_BUMPER_IN_SPHERE_NO_SAVE(float x, float y, float z, float radius, b8 flag0, b8 flag1, [OutAttribute] int% handle, b8 flag2)
			{
				int p;
				NativeInvoke::Invoke<ScriptVoid>(NATIVE_GET_RANDOM_CAR_FRONT_BUMPER_IN_SPHERE_NO_SAVE, x, y, z, radius, flag0, flag1, &p, flag2);
				handle = p;
			}
			static void GET_RANDOM_CAR_IN_SPHERE(float x, float y, float z, float radius, unsigned int model, int Unk814, [OutAttribute] Vehicle% car)
			{
				Vehicle p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_RANDOM_CAR_IN_SPHERE, x, y, z, radius, model, Unk814, &p);
				car = p;
			}
			static void GET_RANDOM_CAR_IN_SPHERE_NO_SAVE(float x, float y, float z, float radius, unsigned int model, b8 flag, [OutAttribute] Vehicle% car)
			{
				Vehicle p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_RANDOM_CAR_IN_SPHERE_NO_SAVE, x, y, z, radius, model, flag, &p);
				car = p;
			}
			static void GET_RANDOM_CAR_MODEL_IN_MEMORY(b8 MustIncludeSpecialModels, [OutAttribute] unsigned int% pHash, [OutAttribute] int% pErrorId)
			{
				unsigned int p1;
				int p2;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_RANDOM_CAR_MODEL_IN_MEMORY, MustIncludeSpecialModels, &p1, &p2);
				pHash = p1;
				pErrorId = p2;
			}
			static void GET_RANDOM_CAR_OF_TYPE_IN_ANGLED_AREA_NO_SAVE(float Unk815, float Unk816, float Unk817, float Unk818, float Unk819, unsigned int type, [OutAttribute] Vehicle% car)
			{
				Vehicle p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_RANDOM_CAR_OF_TYPE_IN_ANGLED_AREA_NO_SAVE, Unk815, Unk816, Unk817, Unk818, Unk819, type, &p);
				car = p;
			}
			static void GET_RANDOM_CAR_OF_TYPE_IN_AREA_NO_SAVE(float x0, float y0, float x1, float y1, unsigned int model, [OutAttribute] Vehicle% car)
			{
				Vehicle p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_RANDOM_CAR_OF_TYPE_IN_AREA_NO_SAVE, x0, y0, x1, y1, model, &p);
				car = p;
			}
			static void GET_RANDOM_CHAR_IN_AREA_OFFSET_NO_SAVE(float x, float y, float z, float sx, float sy, float sz, [OutAttribute] Ped% pPed)
			{
				Ped p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_RANDOM_CHAR_IN_AREA_OFFSET_NO_SAVE, x, y, z, sx, sy, sz, &p);
				pPed = p;
			}
			static void LOAD_PATH_NODES_IN_AREA(float x, float y, float z, float radius) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_LOAD_PATH_NODES_IN_AREA, x, y, z, radius); }
			static void MARK_ROAD_NODE_AS_DONT_WANDER(float x, float y, float z) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_MARK_ROAD_NODE_AS_DONT_WANDER, x, y, z); }
			static void RELEASE_PATH_NODES() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_RELEASE_PATH_NODES); }
			static void SWITCH_PED_PATHS_OFF(float x0, float y0, float z0, float x1, float y1, float z1) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SWITCH_PED_PATHS_OFF, x0, y0, z0, x1, y1, z1); }
			static void SWITCH_PED_PATHS_ON(float x0, float y0, float z0, float x1, float y1, float z1) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SWITCH_PED_PATHS_ON, x0, y0, z0, x1, y1, z1); }
			static void SWITCH_PED_ROADS_BACK_TO_ORIGINAL(float x0, float y0, float z0, float x1, float y1, float z1) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SWITCH_PED_ROADS_BACK_TO_ORIGINAL, x0, y0, z0, x1, y1, z1); }
			static void SWITCH_ROADS_BACK_TO_ORIGINAL(float x0, float y0, float z0, float x1, float y1, float z1) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SWITCH_ROADS_BACK_TO_ORIGINAL, x0, y0, z0, x1, y1, z1); }
			static void SWITCH_ROADS_OFF(float x0, float y0, float z0, float x1, float y1, float z1) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SWITCH_ROADS_OFF, x0, y0, z0, x1, y1, z1); }
			static void SWITCH_ROADS_ON(float x0, float y0, float z0, float x1, float y1, float z1) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SWITCH_ROADS_ON, x0, y0, z0, x1, y1, z1); }
			static void UNMARK_ALL_ROAD_NODES_AS_DONT_WANDER() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_UNMARK_ALL_ROAD_NODES_AS_DONT_WANDER); }
			static void CLEAR_SHAKE_PLAYERPAD_WHEN_CONTROLLER_DISABLED() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_CLEAR_SHAKE_PLAYERPAD_WHEN_CONTROLLER_DISABLED); }
			static void GET_KEYBOARD_MOVE_INPUT([OutAttribute] int% Unk832, [OutAttribute] int% Unk833)
			{
				int p1, p2;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_KEYBOARD_MOVE_INPUT, &p1, &p2);
				Unk832 = p1;
				Unk833 = p2;
			}
			static void GET_MOUSE_INPUT([OutAttribute] int% pX, [OutAttribute] int% pY)
			{
				int x, y;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_MOUSE_INPUT, &x, &y);
				pX = x;
				pY = y;
			}
			static void GET_MOUSE_POSITION([OutAttribute] int% pX, [OutAttribute] int% pY)
			{
				int x, y;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_MOUSE_POSITION, &x, &y);
				pX = x;
				pY = y;
			}
			static void GET_MOUSE_WHEEL([OutAttribute] int% Unk834)
			{
				int p1;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_MOUSE_WHEEL, &p1);
				Unk834 = p1;
			}
			static float GET_MOUSE_SENSITIVITY()
			{
				return NativeInvoke::Invoke<float>(NATIVE_GET_MOUSE_SENSITIVITY);
			}
			static void GET_PAD_STATE(int Unk835, int Unk836, [OutAttribute] int% Unk837)
			{
				int p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_PAD_STATE, Unk835, Unk836, &p);
				Unk837 = p;
			}
			static void GET_POSITION_OF_ANALOGUE_STICKS(unsigned int padIndex, [OutAttribute] int% pLeftX, [OutAttribute] int% pLeftY, [OutAttribute] int% pRightX, [OutAttribute] int% pRightY)
			{
				int lX, lY;
				int rX, rY;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_POSITION_OF_ANALOGUE_STICKS, padIndex, &lX, &lY, &rX, &rY);
				pLeftX = lX;
				pLeftY = lY;
				pRightX = rX;
				pRightY = rY;
			}
			static void SHAKE_PAD(int Unk838, int Unk839, int Unk840) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SHAKE_PAD, Unk838, Unk839, Unk840); }
			static void SHAKE_PLAYERPAD_WHEN_CONTROLLER_DISABLED() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SHAKE_PLAYERPAD_WHEN_CONTROLLER_DISABLED); }
			static void ADD_EXPLOSION(float x, float y, float z, int exptype, float radius, b8 playsound, b8 novisual, float camshake) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ADD_EXPLOSION, x, y, z, exptype, radius, playsound, novisual, camshake); }
			static void EXPLODE_CAR(Vehicle vehicle, b8 unknownTrue, b8 unknownFalse) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_EXPLODE_CAR, vehicle, unknownTrue, unknownFalse); }
			static void EXPLODE_CAR_IN_CUTSCENE(Vehicle car, b8 explode) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_EXPLODE_CAR_IN_CUTSCENE, car, explode); }
			static void EXPLODE_CAR_IN_CUTSCENE_SHAKE_AND_BIT(Vehicle car, b8 flag0, b8 flag1, b8 flag2) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_EXPLODE_CAR_IN_CUTSCENE_SHAKE_AND_BIT, car, flag0, flag1, flag2); }
			static void EXTINGUISH_CAR_FIRE(Vehicle vehicle) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_EXTINGUISH_CAR_FIRE, vehicle); }
			static void EXTINGUISH_FIRE_AT_POINT(float x, float y, float z, float radius) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_EXTINGUISH_FIRE_AT_POINT, x, y, z, radius); }
			static void EXTINGUISH_OBJECT_FIRE(Entity obj) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_EXTINGUISH_OBJECT_FIRE, obj); }
			static void GET_SCRIPT_FIRE_COORDS(int fire, [OutAttribute] float% pX, [OutAttribute] float% pY, [OutAttribute] float% pZ)
			{
				float x, y, z;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_SCRIPT_FIRE_COORDS, fire, &x, &y, &z);
				pX = x;
				pY = y;
				pZ = z;
			}
			static void REMOVE_SCRIPT_FIRE(FireId fire) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_REMOVE_SCRIPT_FIRE, fire); }
			static void SET_MAX_FIRE_GENERATIONS(int max) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_MAX_FIRE_GENERATIONS, max); }
			static void ADD_CHAR_DECISION_MAKER_EVENT_RESPONSE(DecisionMaker dm, unsigned int eventid, unsigned int responseid, float param1, float param2, float param3, float param4, unsigned int unknown0_1, unsigned int unknown1_1) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ADD_CHAR_DECISION_MAKER_EVENT_RESPONSE, dm, eventid, responseid, param1, param2, param3, param4, unknown0_1, unknown1_1); }
			//static void ADD_COMBAT_DECISION_MAKER_EVENT_RESPONSE(DecisionMaker dm, unsigned int eventid, unsigned int responseid, float param1, float param2, float param3, float param4, unsigned int unknown0_1, unsigned int unknown1_1) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ADD_COMBAT_DECISION_MAKER_EVENT_RESPONSE, dm, eventid, responseid, param1, param2, param3, param4, unknown0_1, unknown1_1); }
			static void ADD_GROUP_DECISION_MAKER_EVENT_RESPONSE(DecisionMaker dm, unsigned int eventid, unsigned int responseid, float param1, float param2, float param3, float param4, unsigned int unknown0_1, unsigned int unknown1_1) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ADD_GROUP_DECISION_MAKER_EVENT_RESPONSE, dm, eventid, responseid, param1, param2, param3, param4, unknown0_1, unknown1_1); }
			static void CLEAR_GROUP_DECISION_MAKER_EVENT_RESPONSE(DecisionMaker dm, unsigned int eventid) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_CLEAR_GROUP_DECISION_MAKER_EVENT_RESPONSE, dm, eventid); }
			static void REMOVE_DECISION_MAKER(DecisionMaker dm) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_REMOVE_DECISION_MAKER, dm); }
			static void SET_ADVANCED_BOOL_IN_DECISION_MAKER(int dm, int Unk844, int Unk845, int Unk846, b8 Unk847) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_ADVANCED_BOOL_IN_DECISION_MAKER, dm, Unk844, Unk845, Unk846, Unk847); }
			static void SET_CHAR_DECISION_MAKER(Ped ped, DecisionMaker dm) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_DECISION_MAKER, ped, dm); }
			static void SET_CHAR_DECISION_MAKER_TO_DEFAULT(Ped ped) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CHAR_DECISION_MAKER_TO_DEFAULT, ped); }
			static void SET_COMBAT_DECISION_MAKER(Ped ped, DecisionMaker dm) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_COMBAT_DECISION_MAKER, ped, dm); }
			static void SET_DECISION_MAKER_ATTRIBUTE_CAN_CHANGE_TARGET(DecisionMaker dm, b8 value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_DECISION_MAKER_ATTRIBUTE_CAN_CHANGE_TARGET, dm, value); }
			static void SET_DECISION_MAKER_ATTRIBUTE_CAUTION(DecisionMaker dm, unsigned int value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_DECISION_MAKER_ATTRIBUTE_CAUTION, dm, value); }
			static void SET_DECISION_MAKER_ATTRIBUTE_FIRE_RATE(DecisionMaker dm, unsigned int value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_DECISION_MAKER_ATTRIBUTE_FIRE_RATE, dm, value); }
			static void SET_DECISION_MAKER_ATTRIBUTE_LOW_HEALTH(DecisionMaker dm, unsigned int value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_DECISION_MAKER_ATTRIBUTE_LOW_HEALTH, dm, value); }
			static void SET_DECISION_MAKER_ATTRIBUTE_MOVEMENT_STYLE(DecisionMaker dm, unsigned int value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_DECISION_MAKER_ATTRIBUTE_MOVEMENT_STYLE, dm, value); }
			static void SET_DECISION_MAKER_ATTRIBUTE_NAVIGATION_STYLE(DecisionMaker dm, unsigned int value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_DECISION_MAKER_ATTRIBUTE_NAVIGATION_STYLE, dm, value); }
			static void SET_DECISION_MAKER_ATTRIBUTE_RETREATING_BEHAVIOUR(DecisionMaker dm, unsigned int value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_DECISION_MAKER_ATTRIBUTE_RETREATING_BEHAVIOUR, dm, value); }
			static void SET_DECISION_MAKER_ATTRIBUTE_SIGHT_RANGE(DecisionMaker dm, unsigned int value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_DECISION_MAKER_ATTRIBUTE_SIGHT_RANGE, dm, value); }
			static void SET_DECISION_MAKER_ATTRIBUTE_STANDING_STYLE(DecisionMaker dm, unsigned int value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_DECISION_MAKER_ATTRIBUTE_STANDING_STYLE, dm, value); }
			static void SET_DECISION_MAKER_ATTRIBUTE_TARGET_INJURED_REACTION(DecisionMaker dm, unsigned int value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_DECISION_MAKER_ATTRIBUTE_TARGET_INJURED_REACTION, dm, value); }
			static void SET_DECISION_MAKER_ATTRIBUTE_TARGET_LOSS_RESPONSE(DecisionMaker dm, unsigned int value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_DECISION_MAKER_ATTRIBUTE_TARGET_LOSS_RESPONSE, dm, value); }
			static void SET_DECISION_MAKER_ATTRIBUTE_TEAMWORK(DecisionMaker dm, unsigned int value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_DECISION_MAKER_ATTRIBUTE_TEAMWORK, dm, value); }
			static void SET_DECISION_MAKER_ATTRIBUTE_WEAPON_ACCURACY(DecisionMaker dm, unsigned int value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_DECISION_MAKER_ATTRIBUTE_WEAPON_ACCURACY, dm, value); }
			static void SET_GROUP_CHAR_DECISION_MAKER(Group group, DecisionMaker dm) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_GROUP_CHAR_DECISION_MAKER, group, dm); }
			static void SET_GROUP_COMBAT_DECISION_MAKER(Group group, DecisionMaker dm) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_GROUP_COMBAT_DECISION_MAKER, group, dm); }
			//static void SET_GROUP_DECISION_MAKER(Group group, DecisionMaker dm) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_GROUP_DECISION_MAKER, group, dm); }
			static void _TASK_SET_CHAR_DECISION_MAKER(Ped ped, DecisionMaker dm) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_SET_CHAR_DECISION_MAKER, ped, dm); }
			static void _TASK_SET_COMBAT_DECISION_MAKER(Ped ped, DecisionMaker dm) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TASK_SET_COMBAT_DECISION_MAKER, ped, dm); }
			static void ACTIVATE_SCRIPT_POPULATION_ZONE() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ACTIVATE_SCRIPT_POPULATION_ZONE); }
			static void DEACTIVATE_SCRIPT_POPULATION_ZONE() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DEACTIVATE_SCRIPT_POPULATION_ZONE); }
			//static void FIND_PRIMARY_POPULATION_ZONE_GROUP(int* groupparam0, int* groupparam1) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_FIND_PRIMARY_POPULATION_ZONE_GROUP, groupparam0, groupparam1); }
			static void SET_ZONE_POPULATION_TYPE(String^ zone, int poptype)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_ZONE_POPULATION_TYPE, ctx.marshal_as<const char*>(zone), poptype);
			}
			static void SET_ZONE_SCUMMINESS(String^ zone, int scumminess)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_ZONE_SCUMMINESS, ctx.marshal_as<const char*>(zone), scumminess);
			}
			static void SPECIFY_SCRIPT_POPULATION_ZONE_AREA(int Unk848, int Unk849, int Unk850, int Unk851, int Unk852, int Unk853) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SPECIFY_SCRIPT_POPULATION_ZONE_AREA, Unk848, Unk849, Unk850, Unk851, Unk852, Unk853); }
			static void SPECIFY_SCRIPT_POPULATION_ZONE_GROUPS(int Unk854, int Unk855, int Unk856, int Unk857, int Unk858) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SPECIFY_SCRIPT_POPULATION_ZONE_GROUPS, Unk854, Unk855, Unk856, Unk857, Unk858); }
			static void SPECIFY_SCRIPT_POPULATION_ZONE_NUM_CARS(int num) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SPECIFY_SCRIPT_POPULATION_ZONE_NUM_CARS, num); }
			static void SPECIFY_SCRIPT_POPULATION_ZONE_NUM_PARKED_CARS(int num) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SPECIFY_SCRIPT_POPULATION_ZONE_NUM_PARKED_CARS, num); }
			static void SPECIFY_SCRIPT_POPULATION_ZONE_NUM_PEDS(int num) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SPECIFY_SCRIPT_POPULATION_ZONE_NUM_PEDS, num); }
			static void SPECIFY_SCRIPT_POPULATION_ZONE_NUM_SCENARIO_PEDS(int num) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SPECIFY_SCRIPT_POPULATION_ZONE_NUM_SCENARIO_PEDS, num); }
			static void ACTIVATE_MENU_ITEM(int menuid, int item, b8 activate) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ACTIVATE_MENU_ITEM, menuid, item, activate); }
			static void CREATE_MENU(String^ gxtentry, ScriptAny Unk859, ScriptAny Unk860, ScriptAny Unk861, ScriptAny Unk862, ScriptAny Unk863, ScriptAny Unk864, ScriptAny Unk865, [OutAttribute] int% menuid)
			{
				msclr::interop::marshal_context ctx;
				int p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_CREATE_MENU, ctx.marshal_as<const char*>(gxtentry), Unk859, Unk860, Unk861, Unk862, Unk863, Unk864, Unk865, &p);
				menuid = p;
			}
			static void DELETE_MENU(int menuid) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DELETE_MENU, menuid); }
			static void GET_MENU_POSITION(int menuid, [OutAttribute] float% pX, [OutAttribute] float% pY)
			{
				float x, y;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_MENU_POSITION, menuid, &x, &y);
				pX = x;
				pY = y;
			}
			static void HIGHLIGHT_MENU_ITEM(int menuid, int item, b8 highlight) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_HIGHLIGHT_MENU_ITEM, menuid, item, highlight); }
			static void SET_MENU_COLUMN(int menuid, ScriptAny Unk866, ScriptAny Unk867, ScriptAny Unk868, ScriptAny Unk869, ScriptAny Unk870, ScriptAny Unk871, ScriptAny Unk872, ScriptAny Unk873, ScriptAny Unk874, ScriptAny Unk875, ScriptAny Unk876, ScriptAny Unk877, ScriptAny Unk878, ScriptAny Unk879) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_MENU_COLUMN, menuid, Unk866, Unk867, Unk868, Unk869, Unk870, Unk871, Unk872, Unk873, Unk874, Unk875, Unk876, Unk877, Unk878, Unk879); }
			static void SET_MENU_COLUMN_ORIENTATION(int menuid, int column, int orientation) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_MENU_COLUMN_ORIENTATION, menuid, column, orientation); }
			static void SET_MENU_COLUMN_WIDTH(int menuid, int column, float width) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_MENU_COLUMN_WIDTH, menuid, column, width); }
			static void SET_MENU_ITEM_WITH_2_NUMBERS(int menuid, int item, int Unk880, String^ gxtkey, int number0, int number1)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_MENU_ITEM_WITH_2_NUMBERS, menuid, item, Unk880, ctx.marshal_as<const char*>(gxtkey), number0, number1);
			}
			static void SET_MENU_ITEM_WITH_NUMBER(int menuid, int item, int Unk881, String^ gxtkey, int number)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_MENU_ITEM_WITH_NUMBER, menuid, item, Unk881, ctx.marshal_as<const char*>(gxtkey), number);
			}
			static void SET_SELECTED_MENU_ITEM(int menuid, int item) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_SELECTED_MENU_ITEM, menuid, item); }
			static void ACTIVATE_DAMAGE_TRACKER_ON_NETWORK_ID(ScriptAny Unk897, ScriptAny Unk898) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ACTIVATE_DAMAGE_TRACKER_ON_NETWORK_ID, Unk897, Unk898); }
			static void ACTIVATE_NETWORK_SETTINGS_MENU() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ACTIVATE_NETWORK_SETTINGS_MENU); }
			static void ADD_GROUP_TO_NETWORK_RESTART_NODE_GROUP_LIST(int Unk899) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ADD_GROUP_TO_NETWORK_RESTART_NODE_GROUP_LIST, Unk899); }
			static void ADD_SPAWN_BLOCKING_AREA(ScriptAny Unk900, ScriptAny Unk901, ScriptAny Unk902, ScriptAny Unk903) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ADD_SPAWN_BLOCKING_AREA, Unk900, Unk901, Unk902, Unk903); }
			static void CLEAR_NETWORK_RESTART_NODE_GROUP_LIST() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_CLEAR_NETWORK_RESTART_NODE_GROUP_LIST); }
			static void CLEAR_SCRIPT_ARRAY_FROM_SCRATCHPAD(int Unk909) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_CLEAR_SCRIPT_ARRAY_FROM_SCRATCHPAD, Unk909); }
			static void DEACTIVATE_NETWORK_SETTINGS_MENU() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DEACTIVATE_NETWORK_SETTINGS_MENU); }
			static void DISPLAY_PLAYER_NAMES(ScriptAny Unk910) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DISPLAY_PLAYER_NAMES, Unk910); }
			static void FIND_NETWORK_RESTART_POINT(ScriptAny Unk911, ScriptAny Unk912, ScriptAny Unk913) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_FIND_NETWORK_RESTART_POINT, Unk911, Unk912, Unk913); }
			static void FLUSH_ALL_SPAWN_BLOCKING_AREAS() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_FLUSH_ALL_SPAWN_BLOCKING_AREAS); }
			static void GET_COORDINATES_FOR_NETWORK_RESTART_NODE(ScriptAny Unk914, ScriptAny Unk915, ScriptAny Unk916) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_COORDINATES_FOR_NETWORK_RESTART_NODE, Unk914, Unk915, Unk916); }
			static void GET_NETWORK_ID_FROM_OBJECT(Entity obj, [OutAttribute] int% netid)
			{
				int p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_NETWORK_ID_FROM_OBJECT, obj, &p);
				netid = p;
			}
			static void GET_NETWORK_ID_FROM_PED(Ped ped, [OutAttribute] int% netid)
			{
				int p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_NETWORK_ID_FROM_PED, ped, &p);
				netid = p;
			}
			static void GET_NETWORK_ID_FROM_VEHICLE(Vehicle vehicle, [OutAttribute] int% netid)
			{
				int p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_NETWORK_ID_FROM_VEHICLE, vehicle, &p);
				netid = p;
			}
			static void GET_NETWORK_TIMER(int Unk917) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_NETWORK_TIMER, Unk917); }
			static void GET_OBJECT_FROM_NETWORK_ID(int netid, [OutAttribute] Entity% obj)
			{
				Entity p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_OBJECT_FROM_NETWORK_ID, netid, &p);
				obj = p;
			}
			static void GET_PED_FROM_NETWORK_ID(int netid, [OutAttribute] Ped% ped)
			{
				Ped p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_PED_FROM_NETWORK_ID, netid, &p);
				ped = p;
			}
			static void GET_PLAYER_RGB_COLOUR(int Player, [OutAttribute] int% pR, [OutAttribute] int% pG, [OutAttribute] int& pB)
			{
				int r, g, b;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_PLAYER_RGB_COLOUR, Player, &r, &g, &b);
				pR = r;
				pG = g;
				pB = b;
			}
			static void GET_SPAWN_COORDINATES_FOR_CAR_NODE(ScriptAny Unk918, ScriptAny Unk919, ScriptAny Unk920, ScriptAny Unk921, ScriptAny Unk922, ScriptAny Unk923) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_SPAWN_COORDINATES_FOR_CAR_NODE, Unk918, Unk919, Unk920, Unk921, Unk922, Unk923); }
			static void GET_TEAM_RGB_COLOUR(int team, [OutAttribute] int% pR, [OutAttribute] int% pG, [OutAttribute] int% pB)
			{
				int r, g, b;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_TEAM_RGB_COLOUR, team, &r, &g, &b);
				pR = r;
				pG = g;
				pB = b;
			}
			static void GET_VEHICLE_FROM_NETWORK_ID(int netid, [OutAttribute] Vehicle% vehicle)
			{
				Vehicle p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_VEHICLE_FROM_NETWORK_ID, netid, &p);
				vehicle = p;
			}
			static void LAUNCH_LOCAL_PLAYER_IN_NETWORK_GAME() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_LAUNCH_LOCAL_PLAYER_IN_NETWORK_GAME); }
			static void NETWORK_ADVERTISE_SESSION(b8 advertise) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_NETWORK_ADVERTISE_SESSION, advertise); }
			static void NETWORK_CHANGE_EXTENDED_GAME_CONFIG(ScriptAny Unk924) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_NETWORK_CHANGE_EXTENDED_GAME_CONFIG, Unk924); }
			static void NETWORK_CLEAR_INVITE_ARRIVAL() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_NETWORK_CLEAR_INVITE_ARRIVAL); }
			static void NETWORK_CLEAR_SUMMONS() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_NETWORK_CLEAR_SUMMONS); }
			static void NETWORK_END_SESSION() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_NETWORK_END_SESSION); }
			static void NETWORK_EXPAND_TO_32_PLAYERS() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_NETWORK_EXPAND_TO_32_PLAYERS); }
			static void NETWORK_FIND_GAME(int GameMode, int ukn0, int ukn1, int ukn2) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_NETWORK_FIND_GAME, GameMode, ukn0, ukn1, ukn2); }
			static void NETWORK_FINISH_EXTENDED_SEARCH() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_NETWORK_FINISH_EXTENDED_SEARCH); }
			static void NETWORK_GET_FIND_RESULT(ScriptAny Unk925, ScriptAny Unk926) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_NETWORK_GET_FIND_RESULT, Unk925, Unk926); }
			static void NETWORK_KICK_PLAYER(Player playerIndex, b8 value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_NETWORK_KICK_PLAYER, playerIndex, value); }
			static void NETWORK_LEAVE_GAME() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_NETWORK_LEAVE_GAME); }
			static void NETWORK_LIMIT_TO_16_PLAYERS() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_NETWORK_LIMIT_TO_16_PLAYERS); }
			static void NETWORK_SET_FRIENDLY_FIRE_OPTION(ScriptAny Unk927) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_NETWORK_SET_FRIENDLY_FIRE_OPTION, Unk927); }
			static void NETWORK_SET_HEALTH_RETICULE_OPTION(b8 Unk928) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_NETWORK_SET_HEALTH_RETICULE_OPTION, Unk928); }
			static void NETWORK_SET_LAN_SESSION(ScriptAny Unk929) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_NETWORK_SET_LAN_SESSION, Unk929); }
			static void NETWORK_SET_LOCAL_PLAYER_IS_TYPING(Player playerIndex) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_NETWORK_SET_LOCAL_PLAYER_IS_TYPING, playerIndex); }
			static void NETWORK_SET_MATCH_PROGRESS(float Unk930) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_NETWORK_SET_MATCH_PROGRESS, Unk930); }
			static void NETWORK_SET_SCRIPT_LOBBY_STATE(ScriptAny Unk931) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_NETWORK_SET_SCRIPT_LOBBY_STATE, Unk931); }
			static void NETWORK_SET_SESSION_INVITABLE(b8 invitable) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_NETWORK_SET_SESSION_INVITABLE, invitable); }
			static void NETWORK_SET_TALKER_FOCUS(ScriptAny Unk932) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_NETWORK_SET_TALKER_FOCUS, Unk932); }
			static void NETWORK_SET_TALKER_PROXIMITY(ScriptAny Unk933) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_NETWORK_SET_TALKER_PROXIMITY, Unk933); }
			static void NETWORK_SET_TEAM_ONLY_CHAT(b8 Unk934) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_NETWORK_SET_TEAM_ONLY_CHAT, Unk934); }
			static void NETWORK_SET_TEXT_CHAT_RECIPIENTS(ScriptAny Unk935) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_NETWORK_SET_TEXT_CHAT_RECIPIENTS, Unk935); }
			static void NETWORK_SHOW_FRIEND_PROFILE_UI(ScriptAny Unk936) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_NETWORK_SHOW_FRIEND_PROFILE_UI, Unk936); }
			static void NETWORK_SHOW_MET_PLAYER_FEEDBACK_UI(Player metPlayerIndex) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_NETWORK_SHOW_MET_PLAYER_FEEDBACK_UI, metPlayerIndex); }
			static void NETWORK_SHOW_PLAYER_FEEDBACK_UI(Player payerIndex) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_NETWORK_SHOW_PLAYER_FEEDBACK_UI, payerIndex); }
			static void NETWORK_SHOW_MET_PLAYER_PROFILE_UI(ScriptAny Unk937) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_NETWORK_SHOW_MET_PLAYER_PROFILE_UI, Unk937); }
			static void NETWORK_SHOW_PLAYER_PROFILE_UI(Player playerIndex) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_NETWORK_SHOW_PLAYER_PROFILE_UI, playerIndex); }
			static void NETWORK_START_EXTENDED_SEARCH(ScriptAny Unk938) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_NETWORK_START_EXTENDED_SEARCH, Unk938); }
			static void NETWORK_START_SESSION() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_NETWORK_START_SESSION); }
			static void NETWORK_STORE_GAME_CONFIG(ScriptAny Unk939) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_NETWORK_STORE_GAME_CONFIG, Unk939); }
			static void NETWORK_VERIFY_USER_STRING(ScriptAny Unk940) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_NETWORK_VERIFY_USER_STRING, Unk940); }
			static void OBFUSCATE_INT(int Unk941, int Unk942) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_OBFUSCATE_INT, Unk941, Unk942); }
			static void OBFUSCATE_INT_ARRAY(ScriptAny Unk943, ScriptAny Unk944) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_OBFUSCATE_INT_ARRAY, Unk943, Unk944); }
			//static void REGISTER_CLIENT_BROADCAST_VARIABLES(void* Unk945, int Unk946, int Unk947) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_REGISTER_CLIENT_BROADCAST_VARIABLES, Unk945, Unk946, Unk947); }
			//static void REGISTER_HOST_BROADCAST_VARIABLES(void* Unk948, int ukn0, int ukn1) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_REGISTER_HOST_BROADCAST_VARIABLES, Unk948, ukn0, ukn1); }
			static void REGISTER_KILL_IN_MULTIPLAYER_GAME(Player playerIndex, int id, unsigned int ukn) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_REGISTER_KILL_IN_MULTIPLAYER_GAME, playerIndex, id, ukn); }
			static void REGISTER_MULTIPLAYER_GAME_WIN(Player playerIndex, b8 Unk949) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_REGISTER_MULTIPLAYER_GAME_WIN, playerIndex, Unk949); }
			static void REGISTER_NETWORK_BEST_GAME_SCORES(Player playerIndex, int Unk950, int Unk951) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_REGISTER_NETWORK_BEST_GAME_SCORES, playerIndex, Unk950, Unk951); }
			static void RESERVE_NETWORK_MISSION_OBJECTS_FOR_HOST(int count) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_RESERVE_NETWORK_MISSION_OBJECTS_FOR_HOST, count); }
			static void RESERVE_NETWORK_MISSION_PEDS_FOR_HOST(int Unk952) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_RESERVE_NETWORK_MISSION_PEDS_FOR_HOST, Unk952); }
			static void RESERVE_NETWORK_MISSION_VEHICLES(int Unk953) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_RESERVE_NETWORK_MISSION_VEHICLES, Unk953); }
			static void RESERVE_NETWORK_MISSION_VEHICLES_FOR_HOST(int Unk954) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_RESERVE_NETWORK_MISSION_VEHICLES_FOR_HOST, Unk954); }
			static void RESTORE_SCRIPT_ARRAY_FROM_SCRATCHPAD(ScriptAny Unk955, ScriptAny Unk956, ScriptAny Unk957, ScriptAny Unk958) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_RESTORE_SCRIPT_ARRAY_FROM_SCRATCHPAD, Unk955, Unk956, Unk957, Unk958); }
			static void RESURRECT_NETWORK_PLAYER(Player playerIndex, float x, float y, float z, int ukn0) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_RESURRECT_NETWORK_PLAYER, playerIndex, x, y, z, ukn0); }
			static void SAVE_SCRIPT_ARRAY_IN_SCRATCHPAD(ScriptAny Unk959, ScriptAny Unk960, ScriptAny Unk961, ScriptAny Unk962) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SAVE_SCRIPT_ARRAY_IN_SCRATCHPAD, Unk959, Unk960, Unk961, Unk962); }
			static void SET_ARMOUR_PICKUP_NETWORK_REGEN_TIME(unsigned int timeMS) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_ARMOUR_PICKUP_NETWORK_REGEN_TIME, timeMS); }
			static void SET_CAR_EXISTS_ON_ALL_MACHINES(Vehicle vehicle, b8 exists) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CAR_EXISTS_ON_ALL_MACHINES, vehicle, exists); }
			static void SET_CELLPHONE_RANKED(b8 toggle) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CELLPHONE_RANKED, toggle); }
			static void SET_FILTER_MENU_ON(b8 toggle) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_FILTER_MENU_ON, toggle); }
			static void SET_GFWL_IS_RETURNING_TO_SINGLE_PLAYER(ScriptAny Unk963) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_GFWL_IS_RETURNING_TO_SINGLE_PLAYER, Unk963); }
			static void SET_HEALTH_PICKUP_NETWORK_REGEN_TIME(unsigned int timeMS) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_HEALTH_PICKUP_NETWORK_REGEN_TIME, timeMS); }
			static void SET_HOST_MATCH_ON(b8 Unk964) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_HOST_MATCH_ON, Unk964); }
			static void SET_IK_DISABLED_FOR_NETWORK_PLAYER(Player playerIndex, b8 Unk965) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_IK_DISABLED_FOR_NETWORK_PLAYER, playerIndex, Unk965); }
			static void SET_IN_MP_TUTORIAL(b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_IN_MP_TUTORIAL, set); }
			static void SET_IN_SPECTATOR_MODE(b8 spectate) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_IN_SPECTATOR_MODE, spectate); }
			static void SET_LOBBY_MUTE_OVERRIDE(b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_LOBBY_MUTE_OVERRIDE, set); }
			static void SET_MSG_FOR_LOADING_SCREEN(String^ label)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_MSG_FOR_LOADING_SCREEN, ctx.marshal_as<const char*>(label));
			}
			static void SET_NETWORK_ID_CAN_MIGRATE(int netid, b8 value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_NETWORK_ID_CAN_MIGRATE, netid, value); }
			static void SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES(int netID, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_NETWORK_ID_EXISTS_ON_ALL_MACHINES, netID, set); }
			static void SET_NETWORK_ID_STOP_CLONING(int id, b8 Unk966) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_NETWORK_ID_STOP_CLONING, id, Unk966); }
			static void SET_NETWORK_JOIN_FAIL(b8 ukn0) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_NETWORK_JOIN_FAIL, ukn0); }
			static void SET_NETWORK_PLAYER_AS_VIP(Player playerIndex, b8 Unk967) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_NETWORK_PLAYER_AS_VIP, playerIndex, Unk967); }
			static void SET_NETWORK_VEHICLE_RESPOT_TIMER(int id, int ukn4000) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_NETWORK_VEHICLE_RESPOT_TIMER, id, ukn4000); }
			static void SET_OBJECT_EXISTS_ON_ALL_MACHINES(Entity obj, b8 exists) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_OBJECT_EXISTS_ON_ALL_MACHINES, obj, exists); }
			static void SET_ONLINE_LAN(b8 Unk968) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_ONLINE_LAN, Unk968); }
			static void SET_OVERRIDE_NO_SPRINTING_ON_PHONE_IN_MULTIPLAYER(b8 Unk969) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_OVERRIDE_NO_SPRINTING_ON_PHONE_IN_MULTIPLAYER, Unk969); }
			static void SET_PED_COMPONENTS_TO_NETWORK_PLAYERSETTINGS_MODEL(Ped ped) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_PED_COMPONENTS_TO_NETWORK_PLAYERSETTINGS_MODEL, ped); }
			static void SET_PED_EXISTS_ON_ALL_MACHINES(Ped ped, b8 exists) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_PED_EXISTS_ON_ALL_MACHINES, ped, exists); }
			static void SET_PLAYERS_DROP_MONEY_IN_NETWORK_GAME(b8 toggle) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_PLAYERS_DROP_MONEY_IN_NETWORK_GAME, toggle); }
			static void SET_PLAYER_CONTROL_FOR_NETWORK(Player playerIndex, b8 unknownTrue, b8 unknownFalse) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_PLAYER_CONTROL_FOR_NETWORK, playerIndex, unknownTrue, unknownFalse); }
			static void SET_PLAYER_TEAM(int Player, int team) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_PLAYER_TEAM, Player, team); }
			static void SET_RETURN_TO_FILTER_MENU(b8 Unk970) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_RETURN_TO_FILTER_MENU, Unk970); }
			static void SET_RICH_PRESENCE(ScriptAny Unk971, ScriptAny Unk972, ScriptAny Unk973, ScriptAny Unk974, ScriptAny Unk975) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_RICH_PRESENCE, Unk971, Unk972, Unk973, Unk974, Unk975); }
			static void SET_RICH_PRESENCE_TEMPLATEFILTER() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_RICH_PRESENCE_TEMPLATEFILTER); }
			static void SET_RICH_PRESENCE_TEMPLATELOBBY(ScriptAny Unk976) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_RICH_PRESENCE_TEMPLATELOBBY, Unk976); }
			static void SET_RICH_PRESENCE_TEMPLATEMP1(ScriptAny Unk977, ScriptAny Unk978, ScriptAny Unk979, ScriptAny Unk980) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_RICH_PRESENCE_TEMPLATEMP1, Unk977, Unk978, Unk979, Unk980); }
			static void SET_RICH_PRESENCE_TEMPLATEMP2(ScriptAny Unk981) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_RICH_PRESENCE_TEMPLATEMP2, Unk981); }
			static void SET_RICH_PRESENCE_TEMPLATEMP3(int Unk982, int Unk983) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_RICH_PRESENCE_TEMPLATEMP3, Unk982, Unk983); }
			static void SET_RICH_PRESENCE_TEMPLATEMP4(ScriptAny Unk984, ScriptAny Unk985) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_RICH_PRESENCE_TEMPLATEMP4, Unk984, Unk985); }
			static void SET_RICH_PRESENCE_TEMPLATEMP5(ScriptAny Unk986, ScriptAny Unk987, ScriptAny Unk988) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_RICH_PRESENCE_TEMPLATEMP5, Unk986, Unk987, Unk988); }
			static void SET_RICH_PRESENCE_TEMPLATEMP6(ScriptAny Unk989, ScriptAny Unk990, ScriptAny Unk991) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_RICH_PRESENCE_TEMPLATEMP6, Unk989, Unk990, Unk991); }
			static void SET_RICH_PRESENCE_TEMPLATEPARTY() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_RICH_PRESENCE_TEMPLATEPARTY); }
			static void SET_RICH_PRESENCE_TEMPLATESP1(ScriptAny Unk992, ScriptAny Unk993, ScriptAny Unk994) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_RICH_PRESENCE_TEMPLATESP1, Unk992, Unk993, Unk994); }
			static void SET_RICH_PRESENCE_TEMPLATESP2(int Unk995) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_RICH_PRESENCE_TEMPLATESP2, Unk995); }
			static void SET_SERVER_ID(int id) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_SERVER_ID, id); }
			static void SET_START_FROM_FILTER_MENU(ScriptAny Unk996) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_START_FROM_FILTER_MENU, Unk996); }
			static void SET_SYNC_WEATHER_AND_GAME_TIME(b8 Unk997) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_SYNC_WEATHER_AND_GAME_TIME, Unk997); }
			static void SET_THIS_MACHINE_RUNNING_SERVER_SCRIPT(b8 host) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_THIS_MACHINE_RUNNING_SERVER_SCRIPT, host); }
			static void SET_WEAPON_PICKUP_NETWORK_REGEN_TIME(int weaponType, unsigned int timeMS) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_WEAPON_PICKUP_NETWORK_REGEN_TIME, weaponType, timeMS); }
			static void SHUTDOWN_AND_LAUNCH_NETWORK_GAME(unsigned int episode) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SHUTDOWN_AND_LAUNCH_NETWORK_GAME, episode); }
			static void SHUTDOWN_AND_LAUNCH_SINGLE_PLAYER_GAME() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SHUTDOWN_AND_LAUNCH_SINGLE_PLAYER_GAME); }
			static void STORE_SCRIPT_VALUES_FOR_NETWORK_GAME(ScriptAny Unk998) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_STORE_SCRIPT_VALUES_FOR_NETWORK_GAME, Unk998); }
			static void TELL_NET_PLAYER_TO_START_PLAYING(Player playerIndex, b8 Unk999) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TELL_NET_PLAYER_TO_START_PLAYING, playerIndex, Unk999); }
			static void TERMINATE_ALL_SCRIPTS_FOR_NETWORK_GAME() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TERMINATE_ALL_SCRIPTS_FOR_NETWORK_GAME); }
			static void THIS_SCRIPT_IS_SAFE_FOR_NETWORK_GAME() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_THIS_SCRIPT_IS_SAFE_FOR_NETWORK_GAME); }
			static void TURN_OFF_RADIOHUD_IN_LOBBY() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TURN_OFF_RADIOHUD_IN_LOBBY); }
			//static void UNOBFUSCATE_INT(int count, int* val) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_UNOBFUSCATE_INT, count, val); }
			static void UNOBFUSCATE_INT_ARRAY(ScriptAny Unk1000, ScriptAny Unk1001) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_UNOBFUSCATE_INT_ARRAY, Unk1000, Unk1001); }
			static void UPDATE_NETWORK_RELATIVE_SCORE(ScriptAny Unk1002, ScriptAny Unk1003, ScriptAny Unk1004) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_UPDATE_NETWORK_RELATIVE_SCORE, Unk1002, Unk1003, Unk1004); }
			static void UPDATE_NETWORK_STATISTICS(Player playerIndex, int ukn0, int ukn1, int ukn2) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_UPDATE_NETWORK_STATISTICS, playerIndex, ukn0, ukn1, ukn2); }
			static void USE_PLAYER_COLOUR_INSTEAD_OF_TEAM_COLOUR(b8 Unk1005) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_USE_PLAYER_COLOUR_INSTEAD_OF_TEAM_COLOUR, Unk1005); }
			static void GET_CAMERA_FROM_NETWORK_ID(int ned_id, [OutAttribute] int% cam)
			{
				int p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_CAMERA_FROM_NETWORK_ID, ned_id, &p);
				cam = p;
			}
			static void FLUSH_ALL_PLAYER_RESPAWN_COORDS() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_FLUSH_ALL_PLAYER_RESPAWN_COORDS); }
			static void SEND_CLIENT_BROADCAST_VARIABLES_NOW() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SEND_CLIENT_BROADCAST_VARIABLES_NOW); }
			static void SET_PLAYER_AS_DAMAGED_PLAYER(Player playerIndex, int Unk1057, b8 Unk1058) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_PLAYER_AS_DAMAGED_PLAYER, playerIndex, Unk1057, Unk1058); }
			static void STOP_SYNCING_SCRIPT_ANIMATIONS(b8 Unk1061) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_STOP_SYNCING_SCRIPT_ANIMATIONS, Unk1061); }
			static void EVOLVE_PTFX(unsigned int ptfx, String^ evolvetype, float val)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_EVOLVE_PTFX, ptfx, ctx.marshal_as<const char*>(evolvetype), val);
			}
			static void REMOVE_PROJTEX_FROM_OBJECT(Entity obj) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_REMOVE_PROJTEX_FROM_OBJECT, obj); }
			static void REMOVE_PTFX_FROM_PED(Ped ped) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_REMOVE_PTFX_FROM_PED, ped); }
			static void REMOVE_PTFX_FROM_VEHICLE(Vehicle veh) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_REMOVE_PTFX_FROM_VEHICLE, veh); }
			static void STOP_PTFX(unsigned int ptfx) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_STOP_PTFX, ptfx); }
			static void UPDATE_PTFX_OFFSETS(unsigned int ptfx, float x, float y, float z, float Unk1081, float Unk1082, float Unk1083) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_UPDATE_PTFX_OFFSETS, ptfx, x, y, z, Unk1081, Unk1082, Unk1083); }
			static float GENERATE_RANDOM_FLOAT()
			{
				float p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GENERATE_RANDOM_FLOAT, &p);
				return p;
			}
			static float GENERATE_RANDOM_FLOAT_IN_RANGE(float min, float max)
			{
				float p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GENERATE_RANDOM_FLOAT_IN_RANGE, min, max, &p);
				return p;
			}
			static int GENERATE_RANDOM_INT()
			{
				int p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GENERATE_RANDOM_INT, &p);
				return p;
			}
			static uint32_t GENERATE_RANDOM_INT_IN_RANGE(unsigned int min, unsigned int max)
			{
				uint32_t p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GENERATE_RANDOM_INT_IN_RANGE, min, max, &p);
				return p;
			}
			static void GET_CORRECTED_COLOUR(uint32_t r, uint32_t g, uint32_t b, [OutAttribute] uint32_t% pR, [OutAttribute] uint32_t% pG, [OutAttribute] uint32_t% pB)
			{
				uint32_t _r, _g, _b;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_CORRECTED_COLOUR, r, g, b, &_r, &_g, &_b);
				pR = _r;
				pG = _g;
				pB = _b;
			}
			static void SETTIMERA(unsigned int value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SETTIMERA, value); }
			static void SETTIMERB(unsigned int value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SETTIMERB, value); }
			static void SETTIMERC(int Unk1088) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SETTIMERC, Unk1088); }
			//static void WAIT(int timeMS) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_WAIT, timeMS); }
			static void ADD_PICKUP_TO_INTERIOR_ROOM_BY_KEY(Entity pickup, unsigned int room_hash) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ADD_PICKUP_TO_INTERIOR_ROOM_BY_KEY, pickup, room_hash); }
			static void ADD_PICKUP_TO_INTERIOR_ROOM_BY_NAME(Pickup pickup, String^ roomName)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_ADD_PICKUP_TO_INTERIOR_ROOM_BY_NAME, pickup, ctx.marshal_as<const char*>(roomName));
			}
			static void CREATE_MONEY_PICKUP(float x, float y, float z, unsigned int amount, b8 unknownTrue, [OutAttribute] Pickup% pPickup)
			{
				Pickup p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_CREATE_MONEY_PICKUP, x, y, z, amount, unknownTrue, &p);
				pPickup = p;
			}
			static void CREATE_PICKUP(unsigned int model, unsigned int pickupType, float x, float y, float z, [OutAttribute] Pickup% pPickup, b8 unknownFalse)
			{
				Pickup p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_CREATE_PICKUP, model, pickupType, x, y, z, &p, unknownFalse);
				pPickup = p;
			}
			static void CREATE_PICKUP_ROTATE(unsigned int model, unsigned int pickupType, unsigned int unknown, float x, float y, float z, float rX, float rY, float rZ, [OutAttribute] Pickup% pPickup)
			{
				Pickup p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_CREATE_PICKUP_ROTATE, model, pickupType, unknown, x, y, z, rX, rY, rZ, &p);
				pPickup = p;
			}
			static void CREATE_PICKUP_WITH_AMMO(unsigned int model, unsigned int pickupType, unsigned int unknown, float x, float y, float z, [OutAttribute] Pickup% pPickup)
			{
				Pickup p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_CREATE_PICKUP_WITH_AMMO, model, pickupType, unknown, x, y, z, &p);
				pPickup = p;
			}
			static void GET_PICKUP_COORDINATES(Pickup pickup, [OutAttribute] float% pX, [OutAttribute] float% pY, [OutAttribute] float% pZ)
			{
				float x, y, z;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_PICKUP_COORDINATES, pickup, &x, &y, &z);
				pX = x;
				pY = y;
				pZ = z;
			}
			static void GET_ROOM_KEY_FROM_PICKUP(int pickup, [OutAttribute] unsigned int% hash)
			{
				unsigned int p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_ROOM_KEY_FROM_PICKUP, pickup, &p);
				hash = p;
			}
			static void GET_SAFE_PICKUP_COORDS(float pX, float pY, float pZ, [OutAttribute] float% pSafeX, [OutAttribute] float% pSafeY, [OutAttribute] float% pSafeZ)
			{
				float x, y, z;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_SAFE_PICKUP_COORDS, pX, pY, pZ, &x, &y, &z);
				pSafeX = x;
				pSafeY = y;
				pSafeZ = z;
			}
			static void REMOVE_ALL_PICKUPS_OF_TYPE(unsigned int type) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_REMOVE_ALL_PICKUPS_OF_TYPE, type); }
			static void REMOVE_PICKUP(Pickup pickup) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_REMOVE_PICKUP, pickup); }
			static void REMOVE_TEMPORARY_RADAR_BLIPS_FOR_PICKUPS() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_REMOVE_TEMPORARY_RADAR_BLIPS_FOR_PICKUPS); }
			static void RENDER_WEAPON_PICKUPS_BIGGER(b8 value) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_RENDER_WEAPON_PICKUPS_BIGGER, value); }
			static void SET_ALL_PICKUPS_OF_TYPE_COLLECTABLE_BY_CAR(int pickuptype, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_ALL_PICKUPS_OF_TYPE_COLLECTABLE_BY_CAR, pickuptype, set); }
			static void SET_DO_NOT_SPAWN_PARKED_CARS_ON_TOP(int pickup, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_DO_NOT_SPAWN_PARKED_CARS_ON_TOP, pickup, set); }
			static void SET_PICKUPS_FIX_CARS(b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_PICKUPS_FIX_CARS, set); }
			static void SET_PICKUP_COLLECTABLE_BY_CAR(Entity pickup, b8 set) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_PICKUP_COLLECTABLE_BY_CAR, pickup, set); }
			static void SWITCH_ARROW_ABOVE_BLIPPED_PICKUPS(b8 on) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SWITCH_ARROW_ABOVE_BLIPPED_PICKUPS, on); }
			static void ADD_TO_WIDGET_COMBO(ScriptAny Unk1091) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ADD_TO_WIDGET_COMBO, Unk1091); }
			static void ADD_WIDGET_FLOAT_READ_ONLY(ScriptAny Unk1092, ScriptAny Unk1093) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ADD_WIDGET_FLOAT_READ_ONLY, Unk1092, Unk1093); }
			static void ADD_WIDGET_FLOAT_SLIDER(ScriptAny Unk1094, ScriptAny Unk1095, ScriptAny Unk1096, ScriptAny Unk1097, ScriptAny Unk1098) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ADD_WIDGET_FLOAT_SLIDER, Unk1094, Unk1095, Unk1096, Unk1097, Unk1098); }
			static void ADD_WIDGET_READ_ONLY(ScriptAny Unk1099, ScriptAny Unk1100) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ADD_WIDGET_READ_ONLY, Unk1099, Unk1100); }
			static void ADD_WIDGET_SLIDER(ScriptAny Unk1101, ScriptAny Unk1102, ScriptAny Unk1103, ScriptAny Unk1104, ScriptAny Unk1105) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ADD_WIDGET_SLIDER, Unk1101, Unk1102, Unk1103, Unk1104, Unk1105); }
			static void ADD_WIDGET_STRING(ScriptAny Unk1106) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ADD_WIDGET_STRING, Unk1106); }
			static void ADD_WIDGET_TOGGLE(ScriptAny Unk1107, ScriptAny Unk1108) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ADD_WIDGET_TOGGLE, Unk1107, Unk1108); }
			/// <summary>Hey, isn't that Zolika1351?</summary>
			static void CREATE_WIDGET_GROUP(ScriptAny Unk1109) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_CREATE_WIDGET_GROUP, Unk1109); }
			static void DELETE_WIDGET(ScriptAny Unk1110) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DELETE_WIDGET, Unk1110); }
			static void DELETE_WIDGET_GROUP(ScriptAny Unk1111) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DELETE_WIDGET_GROUP, Unk1111); }
			static void END_WIDGET_GROUP() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_END_WIDGET_GROUP); }
			static void FINISH_WIDGET_COMBO(ScriptAny Unk1112, ScriptAny Unk1113) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_FINISH_WIDGET_COMBO, Unk1112, Unk1113); }
			static void SET_CONTENTS_OF_TEXT_WIDGET(ScriptAny Unk1115, ScriptAny Unk1116) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_CONTENTS_OF_TEXT_WIDGET, Unk1115, Unk1116); }
			static void START_NEW_WIDGET_COMBO() { NativeInvoke::Invoke< ScriptVoid>(NATIVE_START_NEW_WIDGET_COMBO); }
			static void ENABLE_DEBUG_CAM(b8 enable) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_ENABLE_DEBUG_CAM, enable); }
			static void GET_DEBUG_CAM([OutAttribute] int% cam)
			{
				int p;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_GET_DEBUG_CAM, &p);
				cam = p;
			}
			static void SET_ROOM_FOR_DUMMY_CHAR_BY_KEY(Ped dummy, int key) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_ROOM_FOR_DUMMY_CHAR_BY_KEY, dummy, key); }
			static void SET_ROOM_FOR_DUMMY_CHAR_BY_NAME(Ped ped, String^ roomname)
			{
				msclr::interop::marshal_context ctx;
				NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_ROOM_FOR_DUMMY_CHAR_BY_NAME, ped, ctx.marshal_as<const char*>(roomname));
			}
			static void SET_SPRITE_HDR_MULTIPLIER(float multiplier) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_SPRITE_HDR_MULTIPLIER, multiplier); }
			static void SET_UP_TRIP_SKIP_FOR_SPECIFIC_VEHICLE(float Unk1124, float Unk1125, float Unk1126, float Unk1127, Vehicle veh) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_UP_TRIP_SKIP_FOR_SPECIFIC_VEHICLE, Unk1124, Unk1125, Unk1126, Unk1127, veh); }
			static void DISABLE_DEBUG_CAM_AND_PLAYER_WARPING(b8 disable) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DISABLE_DEBUG_CAM_AND_PLAYER_WARPING, disable); }
			static void TELEPORT_NETWORK_PLAYER(int player, float x, float y, float z) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_TELEPORT_NETWORK_PLAYER, player, x, y, z); }
			static void SET_PED_STOP_CLONING(Ped ped, b8 stop) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_PED_STOP_CLONING, ped, stop); }
			static b8 ARE_ANY_CHARS_NEAR_CHAR(Ped ped, float radius) { return NativeInvoke::Invoke< b8>(NATIVE_ARE_ANY_CHARS_NEAR_CHAR, ped, radius); }
			static b8 CAN_CHAR_SEE_DEAD_CHAR(Ped ped, Ped pednext) { return NativeInvoke::Invoke< b8>(NATIVE_CAN_CHAR_SEE_DEAD_CHAR, ped, pednext); }
			static b8 CELL_CAM_IS_CHAR_VISIBLE(Ped ped) { return NativeInvoke::Invoke< b8>(NATIVE_CELL_CAM_IS_CHAR_VISIBLE, ped); }
			static b8 CELL_CAM_IS_CHAR_VISIBLE_NO_FACE_CHECK(Ped ped) { return NativeInvoke::Invoke< b8>(NATIVE_CELL_CAM_IS_CHAR_VISIBLE_NO_FACE_CHECK, ped); }
			static b8 DOES_CHAR_EXIST(Ped ped) { return NativeInvoke::Invoke< b8>(NATIVE_DOES_CHAR_EXIST, ped); }
			static uint32_t GET_CHAR_DRAWABLE_VARIATION(Ped ped, int component) { return NativeInvoke::Invoke< ScriptAny>(NATIVE_GET_CHAR_DRAWABLE_VARIATION, ped, component); }
			static uint32_t GET_CHAR_TEXTURE_VARIATION(Ped ped, unsigned int component) { return NativeInvoke::Invoke< uint32_t>(NATIVE_GET_CHAR_TEXTURE_VARIATION, ped, component); }
			static uint32_t GET_NUMBER_OF_CHAR_DRAWABLE_VARIATIONS(Ped ped, unsigned int component) { return NativeInvoke::Invoke< uint32_t>(NATIVE_GET_NUMBER_OF_CHAR_DRAWABLE_VARIATIONS, ped, component); }
			static uint32_t GET_NUMBER_OF_CHAR_TEXTURE_VARIATIONS(Ped ped, unsigned int component, uint32_t unknown1) { return NativeInvoke::Invoke< uint32_t>(NATIVE_GET_NUMBER_OF_CHAR_TEXTURE_VARIATIONS, ped, component, unknown1); }
			static b8 GET_CHAR_ANIM_IS_EVENT(Ped ped, String^ AnimName0, String^ AnimName1, b8 flag)
			{
				msclr::interop::marshal_context ctx;
				return NativeInvoke::Invoke< b8>(NATIVE_GET_CHAR_ANIM_IS_EVENT, ped, ctx.marshal_as<const char*>(AnimName0), ctx.marshal_as<const char*>(AnimName1), flag);
			}
			static b8 GET_CHAR_MELEE_ACTION_FLAG0(Ped ped) { return NativeInvoke::Invoke< b8>(NATIVE_GET_CHAR_MELEE_ACTION_FLAG0, ped); }
			static b8 GET_CHAR_MELEE_ACTION_FLAG1(Ped ped) { return NativeInvoke::Invoke< b8>(NATIVE_GET_CHAR_MELEE_ACTION_FLAG1, ped); }
			static b8 GET_CHAR_MELEE_ACTION_FLAG2(Ped ped) { return NativeInvoke::Invoke< b8>(NATIVE_GET_CHAR_MELEE_ACTION_FLAG2, ped); }
			static b8 GET_CHAR_READY_TO_BE_EXECUTED(Ped ped) { return NativeInvoke::Invoke< b8>(NATIVE_GET_CHAR_READY_TO_BE_EXECUTED, ped); }
			static b8 GET_CHAR_READY_TO_BE_STUNNED(Ped ped) { return NativeInvoke::Invoke< b8>(NATIVE_GET_CHAR_READY_TO_BE_STUNNED, ped); }
			static b8 GET_CHAR_SWIM_STATE(Ped ped, [OutAttribute] int% state)
			{
				int p;
				b8 r = NativeInvoke::Invoke< b8>(NATIVE_GET_CHAR_SWIM_STATE, ped, &p);
				state = p;
				return r;
			}
			static b8 GET_CHAR_WILL_COWER_INSTEAD_OF_FLEEING(Ped ped) { return NativeInvoke::Invoke< b8>(NATIVE_GET_CHAR_WILL_COWER_INSTEAD_OF_FLEEING, ped); }
			static b8 GET_CLOSEST_CHAR(float x, float y, float z, float radius, int unknown1, int unknown2, [OutAttribute] Ped% pPed)
			{
				Ped p;
				b8 r = NativeInvoke::Invoke< b8>(NATIVE_GET_CLOSEST_CHAR, x, y, z, radius, unknown1, unknown2, &p);
				pPed = p;
				return r;
			}
			static b8 GET_GROUP_CHAR_DUCKS_WHEN_AIMED_AT(Ped ped) { return NativeInvoke::Invoke< b8>(NATIVE_GET_GROUP_CHAR_DUCKS_WHEN_AIMED_AT, ped); }
			static b8 HAS_CAR_BEEN_DAMAGED_BY_CHAR(Vehicle vehicle, Ped ped) { return NativeInvoke::Invoke< b8>(NATIVE_HAS_CAR_BEEN_DAMAGED_BY_CHAR, vehicle, ped); }
			static b8 HAS_CHAR_ANIM_FINISHED(Ped ped, String^ AnimName0, String^ AnimName1)
			{
				msclr::interop::marshal_context ctx;
				return NativeInvoke::Invoke< b8>(NATIVE_HAS_CHAR_ANIM_FINISHED, ped, ctx.marshal_as<const char*>(AnimName0), ctx.marshal_as<const char*>(AnimName1));
			}
			static b8 HAS_CHAR_BEEN_ARRESTED(Ped ped) { return NativeInvoke::Invoke< b8>(NATIVE_HAS_CHAR_BEEN_ARRESTED, ped); }
			static b8 HAS_CHAR_BEEN_DAMAGED_BY_CHAR(Ped ped, Ped otherChar, b8 unknownFalse) { return NativeInvoke::Invoke< b8>(NATIVE_HAS_CHAR_BEEN_DAMAGED_BY_CHAR, ped, otherChar, unknownFalse); }
			static b8 HAS_CHAR_BEEN_PHOTOGRAPHED(Ped ped) { return NativeInvoke::Invoke< b8>(NATIVE_HAS_CHAR_BEEN_PHOTOGRAPHED, ped); }
			static b8 HAS_CHAR_SPOTTED_CHAR(Ped ped, Ped otherChar) { return NativeInvoke::Invoke< b8>(NATIVE_HAS_CHAR_SPOTTED_CHAR, ped, otherChar); }
			static b8 HAS_CHAR_SPOTTED_CHAR_IN_FRONT(Ped ped, Ped otherChar) { return NativeInvoke::Invoke< b8>(NATIVE_HAS_CHAR_SPOTTED_CHAR_IN_FRONT, ped, otherChar); }
			static b8 IS_ANY_CHAR_SHOOTING_IN_AREA(float x0, float y0, float z0, float x1, float y1, float z1, b8 flag) { return NativeInvoke::Invoke< b8>(NATIVE_IS_ANY_CHAR_SHOOTING_IN_AREA, x0, y0, z0, x1, y1, z1, flag); }
			static b8 IS_CHAR_ARMED(Ped ped, unsigned int slot) { return NativeInvoke::Invoke< b8>(NATIVE_IS_CHAR_ARMED, ped, slot); }
			static b8 IS_CHAR_DEAD(Ped ped) { return NativeInvoke::Invoke< b8>(NATIVE_IS_CHAR_DEAD, ped); }
			static b8 IS_CHAR_DUCKING(Ped ped) { return NativeInvoke::Invoke< b8>(NATIVE_IS_CHAR_DUCKING, ped); }
			static b8 IS_CHAR_FACING_CHAR(Ped ped, Ped otherChar, float angle) { return NativeInvoke::Invoke< b8>(NATIVE_IS_CHAR_FACING_CHAR, ped, otherChar, angle); }
			static b8 IS_CHAR_FATALLY_INJURED(Ped ped) { return NativeInvoke::Invoke< b8>(NATIVE_IS_CHAR_FATALLY_INJURED, ped); }
			static b8 IS_CHAR_GESTURING(Ped ped) { return NativeInvoke::Invoke< b8>(NATIVE_IS_CHAR_GESTURING, ped); }
			static b8 IS_CHAR_GETTING_IN_TO_A_CAR(Ped ped) { return NativeInvoke::Invoke< b8>(NATIVE_IS_CHAR_GETTING_IN_TO_A_CAR, ped); }
			static b8 IS_CHAR_GETTING_UP(Ped ped) { return NativeInvoke::Invoke< b8>(NATIVE_IS_CHAR_GETTING_UP, ped); }
			static b8 IS_CHAR_HEALTH_GREATER(Ped ped, unsigned int health) { return NativeInvoke::Invoke< b8>(NATIVE_IS_CHAR_HEALTH_GREATER, ped, health); }
			static b8 IS_CHAR_INJURED(Ped ped) { return NativeInvoke::Invoke< b8>(NATIVE_IS_CHAR_INJURED, ped); }
			static b8 IS_CHAR_IN_AIR(Ped ped) { return NativeInvoke::Invoke< b8>(NATIVE_IS_CHAR_IN_AIR, ped); }
			static b8 IS_CHAR_IN_ANGLED_AREA_2D(Ped ped, float x1, float y1, float x2, float y2, float unknown, b8 unknownFalse) { return NativeInvoke::Invoke< b8>(NATIVE_IS_CHAR_IN_ANGLED_AREA_2D, ped, x1, y1, x2, y2, unknown, unknownFalse); }
			static b8 IS_CHAR_IN_ANGLED_AREA_3D(Ped ped, float x1, float y1, float z1, float x2, float y2, float z2, float unknown, b8 unknownFalse) { return NativeInvoke::Invoke< b8>(NATIVE_IS_CHAR_IN_ANGLED_AREA_3D, ped, x1, y1, z1, x2, y2, z2, unknown, unknownFalse); }
			static b8 IS_CHAR_IN_ANY_BOAT(Ped ped) { return NativeInvoke::Invoke< b8>(NATIVE_IS_CHAR_IN_ANY_BOAT, ped); }
			static b8 IS_CHAR_IN_ANY_CAR(Ped ped) { return NativeInvoke::Invoke< b8>(NATIVE_IS_CHAR_IN_ANY_CAR, ped); }
			static b8 IS_CHAR_IN_ANY_HELI(Ped ped) { return NativeInvoke::Invoke< b8>(NATIVE_IS_CHAR_IN_ANY_HELI, ped); }
			static b8 IS_CHAR_IN_ANY_PLANE(Ped ped) { return NativeInvoke::Invoke< b8>(NATIVE_IS_CHAR_IN_ANY_PLANE, ped); }
			static b8 IS_CHAR_IN_ANY_TRAIN(Ped ped) { return NativeInvoke::Invoke< b8>(NATIVE_IS_CHAR_IN_ANY_TRAIN, ped); }
			static b8 IS_CHAR_IN_AREA_2D(Ped ped, float x1, float y1, float x2, float y2, b8 unknownFalse) { return NativeInvoke::Invoke< b8>(NATIVE_IS_CHAR_IN_AREA_2D, ped, x1, y1, x2, y2, unknownFalse); }
			static b8 IS_CHAR_IN_AREA_3D(Ped ped, float x1, float y1, float z1, float x2, float y2, float z2, b8 unknownFalse) { return NativeInvoke::Invoke< b8>(NATIVE_IS_CHAR_IN_AREA_3D, ped, x1, y1, z1, x2, y2, z2, unknownFalse); }
			static b8 IS_CHAR_IN_AREA_ON_FOOT_2D(Ped ped, float x1, float y1, float x2, float y2, b8 unknownFalse) { return NativeInvoke::Invoke< b8>(NATIVE_IS_CHAR_IN_AREA_ON_FOOT_2D, ped, x1, y1, x2, y2, unknownFalse); }
			static b8 IS_CHAR_IN_FLYING_VEHICLE(Ped ped) { return NativeInvoke::Invoke< b8>(NATIVE_IS_CHAR_IN_FLYING_VEHICLE, ped); }
			static b8 IS_CHAR_IN_MELEE_COMBAT(Ped ped) { return NativeInvoke::Invoke< b8>(NATIVE_IS_CHAR_IN_MELEE_COMBAT, ped); }
			static b8 IS_CHAR_IN_TAXI(Ped ped) { return NativeInvoke::Invoke< b8>(NATIVE_IS_CHAR_IN_TAXI, ped); }
			static b8 IS_CHAR_IN_WATER(Ped ped) { return NativeInvoke::Invoke< b8>(NATIVE_IS_CHAR_IN_WATER, ped); }
			static b8 IS_CHAR_MALE(Ped ped) { return NativeInvoke::Invoke< b8>(NATIVE_IS_CHAR_MALE, ped); }
			static b8 IS_CHAR_MODEL(Ped ped, unsigned int model) { return NativeInvoke::Invoke< b8>(NATIVE_IS_CHAR_MODEL, ped, model); }
			static b8 IS_CHAR_ON_ANY_BIKE(Ped ped) { return NativeInvoke::Invoke< b8>(NATIVE_IS_CHAR_ON_ANY_BIKE, ped); }
			static b8 IS_CHAR_ON_FIRE(Ped ped) { return NativeInvoke::Invoke< b8>(NATIVE_IS_CHAR_ON_FIRE, ped); }
			static b8 IS_CHAR_ON_FOOT(Ped ped) { return NativeInvoke::Invoke< b8>(NATIVE_IS_CHAR_ON_FOOT, ped); }
			static b8 IS_CHAR_ON_SCREEN(Ped ped) { return NativeInvoke::Invoke< b8>(NATIVE_IS_CHAR_ON_SCREEN, ped); }
			static b8 IS_CHAR_PLAYING_ANIM(Ped ped, String^ animSet, String^ animName)
			{
				msclr::interop::marshal_context ctx;
				return NativeInvoke::Invoke< b8>(NATIVE_IS_CHAR_PLAYING_ANIM, ped, ctx.marshal_as<const char*>(animSet), ctx.marshal_as<const char*>(animName));
			}
			static b8 IS_CHAR_RESPONDING_TO_ANY_EVENT(Ped ped) { return NativeInvoke::Invoke< b8>(NATIVE_IS_CHAR_RESPONDING_TO_ANY_EVENT, ped); }
			static b8 IS_CHAR_RESPONDING_TO_EVENT(Ped ped, int eventid) { return NativeInvoke::Invoke< b8>(NATIVE_IS_CHAR_RESPONDING_TO_EVENT, ped, eventid); }
			static b8 IS_CHAR_SHOOTING(Ped ped) { return NativeInvoke::Invoke< b8>(NATIVE_IS_CHAR_SHOOTING, ped); }
			static b8 IS_CHAR_SHOOTING_IN_AREA(Ped ped, float x1, float y1, float x2, float y2, b8 unknownFalse) { return NativeInvoke::Invoke< b8>(NATIVE_IS_CHAR_SHOOTING_IN_AREA, ped, x1, y1, x2, y2, unknownFalse); }
			static b8 IS_CHAR_SITTING_IDLE(Ped ped) { return NativeInvoke::Invoke< b8>(NATIVE_IS_CHAR_SITTING_IDLE, ped); }
			static b8 IS_CHAR_SITTING_IN_ANY_CAR(Ped ped) { return NativeInvoke::Invoke< b8>(NATIVE_IS_CHAR_SITTING_IN_ANY_CAR, ped); }
			static b8 IS_CHAR_SITTING_IN_CAR(Ped ped, Vehicle vehicle) { return NativeInvoke::Invoke< b8>(NATIVE_IS_CHAR_SITTING_IN_CAR, ped, vehicle); }
			static b8 IS_CHAR_STOPPED(Ped ped) { return NativeInvoke::Invoke< b8>(NATIVE_IS_CHAR_STOPPED, ped); }
			static b8 IS_CHAR_STUCK_UNDER_CAR(Ped ped) { return NativeInvoke::Invoke< b8>(NATIVE_IS_CHAR_STUCK_UNDER_CAR, ped); }
			static b8 IS_CHAR_SWIMMING(Ped ped) { return NativeInvoke::Invoke< b8>(NATIVE_IS_CHAR_SWIMMING, ped); }
			static b8 IS_CHAR_TOUCHING_CHAR(Ped ped, Ped otherChar) { return NativeInvoke::Invoke< b8>(NATIVE_IS_CHAR_TOUCHING_CHAR, ped, otherChar); }
			static b8 IS_CHAR_TOUCHING_OBJECT(Ped ped, Entity obj) { return NativeInvoke::Invoke< b8>(NATIVE_IS_CHAR_TOUCHING_OBJECT, ped, obj); }
			static b8 IS_CHAR_TOUCHING_OBJECT_ON_FOOT(Ped ped, Entity obj) { return NativeInvoke::Invoke< b8>(NATIVE_IS_CHAR_TOUCHING_OBJECT_ON_FOOT, ped, obj); }
			static b8 IS_CHAR_TRYING_TO_ENTER_A_LOCKED_CAR(Ped ped) { return NativeInvoke::Invoke< b8>(NATIVE_IS_CHAR_TRYING_TO_ENTER_A_LOCKED_CAR, ped); }
			static b8 IS_CHAR_USING_ANY_SCENARIO(Ped ped) { return NativeInvoke::Invoke< b8>(NATIVE_IS_CHAR_USING_ANY_SCENARIO, ped); }
			static b8 IS_CHAR_USING_MAP_ATTRACTOR(Ped ped) { return NativeInvoke::Invoke< b8>(NATIVE_IS_CHAR_USING_MAP_ATTRACTOR, ped); }
			static b8 IS_CHAR_USING_SCENARIO(Ped ped, String^ scenarioName)
			{
				msclr::interop::marshal_context ctx;
				return NativeInvoke::Invoke< b8>(NATIVE_IS_CHAR_USING_SCENARIO, ped, ctx.marshal_as<const char*>(scenarioName));
			}
			static b8 IS_CHAR_VISIBLE(Ped ped) { return NativeInvoke::Invoke< b8>(NATIVE_IS_CHAR_VISIBLE, ped); }
			static b8 IS_CHAR_WAITING_FOR_WORLD_COLLISION(Ped ped) { return NativeInvoke::Invoke< b8>(NATIVE_IS_CHAR_WAITING_FOR_WORLD_COLLISION, ped); }
			static b8 LOCATE_CHAR_ANY_MEANS_2D(Ped ped, float x0, float y0, float x1, float y1, b8 flag) { return NativeInvoke::Invoke< b8>(NATIVE_LOCATE_CHAR_ANY_MEANS_2D, ped, x0, y0, x1, y1, flag); }
			static b8 LOCATE_CHAR_ANY_MEANS_3D(Ped ped, float x0, float y0, float z0, float x1, float y1, float z1, b8 flag) { return NativeInvoke::Invoke< b8>(NATIVE_LOCATE_CHAR_ANY_MEANS_3D, ped, x0, y0, z0, x1, y1, z1, flag); }
			static b8 LOCATE_CHAR_ANY_MEANS_CAR_2D(Ped ped, Vehicle car, float x, float y, b8 flag) { return NativeInvoke::Invoke< b8>(NATIVE_LOCATE_CHAR_ANY_MEANS_CAR_2D, ped, car, x, y, flag); }
			static b8 LOCATE_CHAR_ANY_MEANS_CAR_3D(Ped ped, Vehicle car, float x, float y, float z, b8 flag) { return NativeInvoke::Invoke< b8>(NATIVE_LOCATE_CHAR_ANY_MEANS_CAR_3D, ped, car, x, y, z, flag); }
			static b8 LOCATE_CHAR_ANY_MEANS_CHAR_2D(Ped ped, Ped pednext, float x, float y, b8 flag) { return NativeInvoke::Invoke< b8>(NATIVE_LOCATE_CHAR_ANY_MEANS_CHAR_2D, ped, pednext, x, y, flag); }
			static b8 LOCATE_CHAR_ANY_MEANS_CHAR_3D(Ped ped, Ped pednext, float x, float y, float z, b8 flag) { return NativeInvoke::Invoke< b8>(NATIVE_LOCATE_CHAR_ANY_MEANS_CHAR_3D, ped, pednext, x, y, z, flag); }
			static b8 LOCATE_CHAR_ANY_MEANS_OBJECT_2D(Ped ped, Entity obj, float x, float y, b8 flag) { return NativeInvoke::Invoke< b8>(NATIVE_LOCATE_CHAR_ANY_MEANS_OBJECT_2D, ped, obj, x, y, flag); }
			static b8 LOCATE_CHAR_ANY_MEANS_OBJECT_3D(Ped ped, Entity obj, float x, float y, float z, b8 flag) { return NativeInvoke::Invoke< b8>(NATIVE_LOCATE_CHAR_ANY_MEANS_OBJECT_3D, ped, obj, x, y, z, flag); }
			static b8 LOCATE_CHAR_IN_CAR_2D(Ped ped, float x0, float y0, float x1, float y1, b8 flag) { return NativeInvoke::Invoke< b8>(NATIVE_LOCATE_CHAR_IN_CAR_2D, ped, x0, y0, x1, y1, flag); }
			static b8 LOCATE_CHAR_IN_CAR_3D(Ped ped, float x0, float y0, float z0, float x1, float y1, float z, b8 flag) { return NativeInvoke::Invoke< b8>(NATIVE_LOCATE_CHAR_IN_CAR_3D, ped, x0, y0, z0, x1, y1, z, flag); }
			static b8 LOCATE_CHAR_IN_CAR_CAR_2D(Ped ped, Vehicle car, float x, float y, b8 flag) { return NativeInvoke::Invoke< b8>(NATIVE_LOCATE_CHAR_IN_CAR_CAR_2D, ped, car, x, y, flag); }
			static b8 LOCATE_CHAR_IN_CAR_CAR_3D(Ped ped, Vehicle car, float x, float y, float z, b8 flag) { return NativeInvoke::Invoke< b8>(NATIVE_LOCATE_CHAR_IN_CAR_CAR_3D, ped, car, x, y, z, flag); }
			static b8 LOCATE_CHAR_IN_CAR_CHAR_2D(Ped ped, Ped pednext, float x, float y, b8 flag) { return NativeInvoke::Invoke< b8>(NATIVE_LOCATE_CHAR_IN_CAR_CHAR_2D, ped, pednext, x, y, flag); }
			static b8 LOCATE_CHAR_IN_CAR_CHAR_3D(Ped ped, Vehicle pednext, float x, float y, float z, b8 flag) { return NativeInvoke::Invoke< b8>(NATIVE_LOCATE_CHAR_IN_CAR_CHAR_3D, ped, pednext, x, y, z, flag); }
			static b8 LOCATE_CHAR_IN_CAR_OBJECT_2D(Ped ped, Entity obj, float x, float y, b8 flag) { return NativeInvoke::Invoke< b8>(NATIVE_LOCATE_CHAR_IN_CAR_OBJECT_2D, ped, obj, x, y, flag); }
			static b8 LOCATE_CHAR_IN_CAR_OBJECT_3D(Ped ped, Entity obj, float x, float y, float z, b8 flag) { return NativeInvoke::Invoke< b8>(NATIVE_LOCATE_CHAR_IN_CAR_OBJECT_3D, ped, obj, x, y, z, flag); }
			static b8 LOCATE_CHAR_ON_FOOT_2D(Ped ped, float x0, float y0, float x1, float y1, b8 flag) { return NativeInvoke::Invoke< b8>(NATIVE_LOCATE_CHAR_ON_FOOT_2D, ped, x0, y0, x1, y1, flag); }
			static b8 LOCATE_CHAR_ON_FOOT_3D(Ped ped, float x0, float y0, float z0, float x1, float y1, float z1, b8 flag) { return NativeInvoke::Invoke< b8>(NATIVE_LOCATE_CHAR_ON_FOOT_3D, ped, x0, y0, z0, x1, y1, z1, flag); }
			static b8 LOCATE_CHAR_ON_FOOT_CAR_2D(Ped ped, Vehicle car, float x, float y, b8 flag) { return NativeInvoke::Invoke< b8>(NATIVE_LOCATE_CHAR_ON_FOOT_CAR_2D, ped, car, x, y, flag); }
			static b8 LOCATE_CHAR_ON_FOOT_CAR_3D(Ped ped, Vehicle car, float x, float y, float z, b8 flag) { return NativeInvoke::Invoke< b8>(NATIVE_LOCATE_CHAR_ON_FOOT_CAR_3D, ped, car, x, y, z, flag); }
			static b8 LOCATE_CHAR_ON_FOOT_CHAR_2D(Ped ped, Ped pednext, float x, float y, b8 flag) { return NativeInvoke::Invoke< b8>(NATIVE_LOCATE_CHAR_ON_FOOT_CHAR_2D, ped, pednext, x, y, flag); }
			static b8 LOCATE_CHAR_ON_FOOT_CHAR_3D(Ped ped, Ped pednext, float x, float y, float z, b8 flag) { return NativeInvoke::Invoke< b8>(NATIVE_LOCATE_CHAR_ON_FOOT_CHAR_3D, ped, pednext, x, y, z, flag); }
			static b8 LOCATE_CHAR_ON_FOOT_OBJECT_2D(Ped ped, Entity obj, float x, float y, b8 flag) { return NativeInvoke::Invoke< b8>(NATIVE_LOCATE_CHAR_ON_FOOT_OBJECT_2D, ped, obj, x, y, flag); }
			static b8 LOCATE_CHAR_ON_FOOT_OBJECT_3D(Ped ped, Entity obj, float x, float y, float z, b8 flag) { return NativeInvoke::Invoke< b8>(NATIVE_LOCATE_CHAR_ON_FOOT_OBJECT_3D, ped, obj, x, y, z, flag); }
			static b8 SET_CHAR_ANIM_PLAYING_FLAG(Ped ped, String^ AnimName0, String^ AnimName1, b8 flag)
			{
				msclr::interop::marshal_context ctx;
				return NativeInvoke::Invoke< b8>(NATIVE_SET_CHAR_ANIM_PLAYING_FLAG, ped, ctx.marshal_as<const char*>(AnimName0), ctx.marshal_as<const char*>(AnimName1), flag);
			}
			static b8 CAN_PLAYER_START_MISSION(int player) { return NativeInvoke::Invoke< b8>(NATIVE_CAN_PLAYER_START_MISSION, player); }
			static b8 GET_PLAYER_HAS_TRACKS() { return NativeInvoke::Invoke< b8>(NATIVE_GET_PLAYER_HAS_TRACKS); }
			static b8 HAS_ACHIEVEMENT_BEEN_PASSED(unsigned int achievement) { return NativeInvoke::Invoke< b8>(NATIVE_HAS_ACHIEVEMENT_BEEN_PASSED, achievement); }
			static b8 HAS_PLAYER_COLLECTED_PICKUP(Player playerIndex, Pickup pikcup) { return NativeInvoke::Invoke< b8>(NATIVE_HAS_PLAYER_COLLECTED_PICKUP, playerIndex, pikcup); }
			static b8 HAS_PLAYER_DAMAGED_AT_LEAST_ONE_PED(Player playerIndex) { return NativeInvoke::Invoke< b8>(NATIVE_HAS_PLAYER_DAMAGED_AT_LEAST_ONE_PED, playerIndex); }
			static b8 HAS_PLAYER_DAMAGED_AT_LEAST_ONE_VEHICLE(Player playerIndex) { return NativeInvoke::Invoke< b8>(NATIVE_HAS_PLAYER_DAMAGED_AT_LEAST_ONE_VEHICLE, playerIndex); }
			static b8 IS_PLACE_CAR_BOMB_ACTIVE() { return NativeInvoke::Invoke< b8>(NATIVE_IS_PLACE_CAR_BOMB_ACTIVE); }
			static b8 IS_PLAYER_BEING_ARRESTED() { return NativeInvoke::Invoke< b8>(NATIVE_IS_PLAYER_BEING_ARRESTED); }
			static b8 IS_PLAYER_CLIMBING(Player playerIndex) { return NativeInvoke::Invoke< b8>(NATIVE_IS_PLAYER_CLIMBING, playerIndex); }
			static b8 IS_PLAYER_CONTROL_ON(Player playerIndex) { return NativeInvoke::Invoke< b8>(NATIVE_IS_PLAYER_CONTROL_ON, playerIndex); }
			static b8 IS_PLAYER_DEAD(Player playerIndex) { return NativeInvoke::Invoke< b8>(NATIVE_IS_PLAYER_DEAD, playerIndex); }
			static b8 IS_PLAYER_FREE_AIMING_AT_CHAR(Player playerIndex, Ped ped) { return NativeInvoke::Invoke< b8>(NATIVE_IS_PLAYER_FREE_AIMING_AT_CHAR, playerIndex, ped); }
			static b8 IS_PLAYER_FREE_FOR_AMBIENT_TASK(Player playerIndex) { return NativeInvoke::Invoke< b8>(NATIVE_IS_PLAYER_FREE_FOR_AMBIENT_TASK, playerIndex); }
			static b8 IS_PLAYER_IN_REMOTE_MODE(int player) { return NativeInvoke::Invoke< b8>(NATIVE_IS_PLAYER_IN_REMOTE_MODE, player); }
			static b8 IS_PLAYER_ONLINE() { return NativeInvoke::Invoke< b8>(NATIVE_IS_PLAYER_ONLINE); }
			static b8 IS_PLAYER_PERFORMING_STOPPIE(int player) { return NativeInvoke::Invoke< b8>(NATIVE_IS_PLAYER_PERFORMING_STOPPIE, player); }
			static b8 IS_PLAYER_PERFORMING_WHEELIE(int player) { return NativeInvoke::Invoke< b8>(NATIVE_IS_PLAYER_PERFORMING_WHEELIE, player); }
			static b8 IS_PLAYER_PLAYING(Player playerIndex) { return NativeInvoke::Invoke< b8>(NATIVE_IS_PLAYER_PLAYING, playerIndex); }
			static b8 IS_PLAYER_PRESSING_HORN(Player playerIndex) { return NativeInvoke::Invoke< b8>(NATIVE_IS_PLAYER_PRESSING_HORN, playerIndex); }
			static b8 IS_PLAYER_READY_FOR_CUTSCENE(int player) { return NativeInvoke::Invoke< b8>(NATIVE_IS_PLAYER_READY_FOR_CUTSCENE, player); }
			static b8 IS_PLAYER_SCRIPT_CONTROL_ON(int player) { return NativeInvoke::Invoke< b8>(NATIVE_IS_PLAYER_SCRIPT_CONTROL_ON, player); }
			static b8 IS_PLAYER_SIGNED_IN_LOCALLY() { return NativeInvoke::Invoke< b8>(NATIVE_IS_PLAYER_SIGNED_IN_LOCALLY); }
			static b8 IS_PLAYER_TARGETTING_ANYTHING(Player playerIndex) { return NativeInvoke::Invoke< b8>(NATIVE_IS_PLAYER_TARGETTING_ANYTHING, playerIndex); }
			static b8 IS_PLAYER_TARGETTING_CHAR(Player playerIndex, Ped ped) { return NativeInvoke::Invoke< b8>(NATIVE_IS_PLAYER_TARGETTING_CHAR, playerIndex, ped); }
			static b8 IS_PLAYER_TARGETTING_OBJECT(Player playerIndex, Entity obj) { return NativeInvoke::Invoke< b8>(NATIVE_IS_PLAYER_TARGETTING_OBJECT, playerIndex, obj); }
			static b8 IS_SCORE_GREATER(Player playerIndex, unsigned int score) { return NativeInvoke::Invoke< b8>(NATIVE_IS_SCORE_GREATER, playerIndex, score); }
			static b8 PLAYER_HAS_CHAR(Player playerIndex) { return NativeInvoke::Invoke< b8>(NATIVE_PLAYER_HAS_CHAR, playerIndex); }
			static b8 PLAYER_HAS_FLASHING_STARS_ABOUT_TO_DROP(Player playerIndex) { return NativeInvoke::Invoke< b8>(NATIVE_PLAYER_HAS_FLASHING_STARS_ABOUT_TO_DROP, playerIndex); }
			static b8 PLAYER_HAS_GREYED_OUT_STARS(Player playerIndex) { return NativeInvoke::Invoke< b8>(NATIVE_PLAYER_HAS_GREYED_OUT_STARS, playerIndex); }
			static b8 PLAYER_IS_INTERACTING_WITH_GARAGE() { return NativeInvoke::Invoke< b8>(NATIVE_PLAYER_IS_INTERACTING_WITH_GARAGE); }
			static b8 PLAYER_IS_NEAR_FIRST_PIGEON(float x, float y, float z) { return NativeInvoke::Invoke< b8>(NATIVE_PLAYER_IS_NEAR_FIRST_PIGEON, x, y, z); }
			static b8 PLAYER_IS_PISSED_OFF(int player) { return NativeInvoke::Invoke< b8>(NATIVE_PLAYER_IS_PISSED_OFF, player); }
			static b8 ARE_ENEMY_PEDS_IN_AREA(Ped ped, float x, float y, float z, float radius) { return NativeInvoke::Invoke< b8>(NATIVE_ARE_ENEMY_PEDS_IN_AREA, ped, x, y, z, radius); }
			static b8 CAN_PED_SHIMMY_IN_DIRECTION(Ped ped, int direction) { return NativeInvoke::Invoke< b8>(NATIVE_CAN_PED_SHIMMY_IN_DIRECTION, ped, direction); }
			static b8 CHECK_NM_FEEDBACK(Ped ped, int id, b8 Unk13) { return NativeInvoke::Invoke< b8>(NATIVE_CHECK_NM_FEEDBACK, ped, id, Unk13); }
			static b8 DOES_GROUP_EXIST(Group group) { return NativeInvoke::Invoke< b8>(NATIVE_DOES_GROUP_EXIST, group); }
			static b8 GET_PED_PATH_MAY_DROP_FROM_HEIGHT(Ped ped) { return NativeInvoke::Invoke< b8>(NATIVE_GET_PED_PATH_MAY_DROP_FROM_HEIGHT, ped); }
			static b8 GET_PED_PATH_MAY_USE_CLIMBOVERS(Ped ped) { return NativeInvoke::Invoke< b8>(NATIVE_GET_PED_PATH_MAY_USE_CLIMBOVERS, ped); }
			static b8 GET_PED_PATH_MAY_USE_LADDERS(Ped ped) { return NativeInvoke::Invoke< b8>(NATIVE_GET_PED_PATH_MAY_USE_LADDERS, ped); }
			static b8 GET_PED_PATH_WILL_AVOID_DYNAMIC_OBJECTS(Ped ped) { return NativeInvoke::Invoke< b8>(NATIVE_GET_PED_PATH_WILL_AVOID_DYNAMIC_OBJECTS, ped); }
			static b8 GET_TASK_PLACE_CAR_BOMB_UNSUCCESSFUL() { return NativeInvoke::Invoke< b8>(NATIVE_GET_TASK_PLACE_CAR_BOMB_UNSUCCESSFUL); }
			static b8 HAS_OVERRIDEN_SIT_IDLE_ANIM_FINISHED(Ped ped) { return NativeInvoke::Invoke< b8>(NATIVE_HAS_OVERRIDEN_SIT_IDLE_ANIM_FINISHED, ped); }
			static b8 IS_GROUP_LEADER(Ped ped, Group group) { return NativeInvoke::Invoke< b8>(NATIVE_IS_GROUP_LEADER, ped, group); }
			static b8 IS_GROUP_MEMBER(Ped ped, Group group) { return NativeInvoke::Invoke< b8>(NATIVE_IS_GROUP_MEMBER, ped, group); }
			static b8 IS_PEDS_VEHICLE_HOT(Ped ped) { return NativeInvoke::Invoke< b8>(NATIVE_IS_PEDS_VEHICLE_HOT, ped); }
			static b8 IS_PED_ATTACHED_TO_ANY_CAR(Ped ped) { return NativeInvoke::Invoke< b8>(NATIVE_IS_PED_ATTACHED_TO_ANY_CAR, ped); }
			static b8 IS_PED_ATTACHED_TO_OBJECT(Ped ped, Entity obj) { return NativeInvoke::Invoke< b8>(NATIVE_IS_PED_ATTACHED_TO_OBJECT, ped, obj); }
			static b8 IS_PED_A_MISSION_PED(Ped ped) { return NativeInvoke::Invoke< b8>(NATIVE_IS_PED_A_MISSION_PED, ped); }
			static b8 IS_PED_BEING_JACKED(Ped ped) { return NativeInvoke::Invoke< b8>(NATIVE_IS_PED_BEING_JACKED, ped); }
			static b8 IS_PED_CLIMBING(Ped ped) { return NativeInvoke::Invoke< b8>(NATIVE_IS_PED_CLIMBING, ped); }
			static b8 IS_PED_DOING_DRIVEBY(Ped ped) { return NativeInvoke::Invoke< b8>(NATIVE_IS_PED_DOING_DRIVEBY, ped); }
			static b8 IS_PED_FLEEING(Ped ped) { return NativeInvoke::Invoke< b8>(NATIVE_IS_PED_FLEEING, ped); }
			static b8 IS_PED_HOLDING_AN_OBJECT(Ped ped) { return NativeInvoke::Invoke< b8>(NATIVE_IS_PED_HOLDING_AN_OBJECT, ped); }
			static b8 IS_PED_IN_COMBAT(Ped ped) { return NativeInvoke::Invoke< b8>(NATIVE_IS_PED_IN_COMBAT, ped); }
			static b8 IS_PED_IN_COVER(Ped ped) { return NativeInvoke::Invoke< b8>(NATIVE_IS_PED_IN_COVER, ped); }
			static b8 IS_PED_IN_GROUP(Ped ped) { return NativeInvoke::Invoke< b8>(NATIVE_IS_PED_IN_GROUP, ped); }
			static b8 IS_PED_JACKING(Ped ped) { return NativeInvoke::Invoke< b8>(NATIVE_IS_PED_JACKING, ped); }
			static b8 IS_PED_LOOKING_AT_CAR(Ped ped, Vehicle car) { return NativeInvoke::Invoke< b8>(NATIVE_IS_PED_LOOKING_AT_CAR, ped, car); }
			static b8 IS_PED_LOOKING_AT_OBJECT(Ped ped, Entity obj) { return NativeInvoke::Invoke< b8>(NATIVE_IS_PED_LOOKING_AT_OBJECT, ped, obj); }
			static b8 IS_PED_LOOKING_AT_PED(Ped ped, Ped otherChar) { return NativeInvoke::Invoke< b8>(NATIVE_IS_PED_LOOKING_AT_PED, ped, otherChar); }
			static b8 IS_PED_PINNED_DOWN(Ped ped) { return NativeInvoke::Invoke< b8>(NATIVE_IS_PED_PINNED_DOWN, ped); }
			static b8 IS_PED_RAGDOLL(Ped ped) { return NativeInvoke::Invoke< b8>(NATIVE_IS_PED_RAGDOLL, ped); }
			static b8 IS_PED_RETREATING(Ped ped) { return NativeInvoke::Invoke< b8>(NATIVE_IS_PED_RETREATING, ped); }
			static b8 SWITCH_PED_TO_RAGDOLL(Ped ped, int Unk14, int time, b8 flag0, b8 flag1, b8 flag2, b8 flag3) { return NativeInvoke::Invoke< b8>(NATIVE_SWITCH_PED_TO_RAGDOLL, ped, Unk14, time, flag0, flag1, flag2, flag3); }
			static b8 SWITCH_PED_TO_RAGDOLL_WITH_FALL(Ped ped, int Unk15, int Unk16, int Unk17, float Unk18, float Unk19, int Unk20, float Unk21, float Unk22, float Unk23, float Unk24, float Unk25, float Unk26, float Unk27) { return NativeInvoke::Invoke< b8>(NATIVE_SWITCH_PED_TO_RAGDOLL_WITH_FALL, ped, Unk15, Unk16, Unk17, Unk18, Unk19, Unk20, Unk21, Unk22, Unk23, Unk24, Unk25, Unk26, Unk27); }
			static b8 ARE_TAXI_LIGHTS_ON(Vehicle vehicle) { return NativeInvoke::Invoke< b8>(NATIVE_ARE_TAXI_LIGHTS_ON, vehicle); }
			static b8 CAN_BE_DESCRIBED_AS_A_CAR(Vehicle veh) { return NativeInvoke::Invoke< b8>(NATIVE_CAN_BE_DESCRIBED_AS_A_CAR, veh); }
			static b8 CHECK_STUCK_TIMER(Vehicle car, int timernum, int timeout) { return NativeInvoke::Invoke< b8>(NATIVE_CHECK_STUCK_TIMER, car, timernum, timeout); }
			static b8 CREATE_EMERGENCY_SERVICES_CAR(unsigned int model, float x, float y, float z) { return NativeInvoke::Invoke< b8>(NATIVE_CREATE_EMERGENCY_SERVICES_CAR, model, x, y, z); }
			static b8 CREATE_EMERGENCY_SERVICES_CAR_RETURN_DRIVER(unsigned int model, float x, float y, float z, [OutAttribute] Vehicle% car, [OutAttribute] Ped% cardriver, [OutAttribute] Ped% carpass)
			{
				Vehicle v;
				Ped p1, p2;
				b8 r = NativeInvoke::Invoke<b8>(NATIVE_CREATE_EMERGENCY_SERVICES_CAR_RETURN_DRIVER, model, x, y, z, &v, &p1, &p2);
				car = v;
				cardriver = p1;
				carpass = p2;
				return r;
			}
			static b8 CREATE_EMERGENCY_SERVICES_CAR_THEN_WALK(unsigned int model, float x, float y, float z) { return NativeInvoke::Invoke< b8>(NATIVE_CREATE_EMERGENCY_SERVICES_CAR_THEN_WALK, model, x, y, z); }
			static b8 DOES_CAR_HAVE_HYDRAULICS(Vehicle car) { return NativeInvoke::Invoke< b8>(NATIVE_DOES_CAR_HAVE_HYDRAULICS, car); }
			static b8 DOES_CAR_HAVE_ROOF(Vehicle vehicle) { return NativeInvoke::Invoke< b8>(NATIVE_DOES_CAR_HAVE_ROOF, vehicle); }
			static b8 DOES_CAR_HAVE_STUCK_CAR_CHECK(Vehicle vehicle) { return NativeInvoke::Invoke< b8>(NATIVE_DOES_CAR_HAVE_STUCK_CAR_CHECK, vehicle); }
			static b8 DOES_VEHICLE_EXIST(Vehicle vehicle) { return NativeInvoke::Invoke< b8>(NATIVE_DOES_VEHICLE_EXIST, vehicle); }
			static b8 HAS_CAR_BEEN_DAMAGED_BY_CAR(Vehicle vehicle, Vehicle otherCar) { return NativeInvoke::Invoke< b8>(NATIVE_HAS_CAR_BEEN_DAMAGED_BY_CAR, vehicle, otherCar); }
			static b8 HAS_CAR_BEEN_DAMAGED_BY_WEAPON(Vehicle vehicle, unsigned int weapon) { return NativeInvoke::Invoke< b8>(NATIVE_HAS_CAR_BEEN_DAMAGED_BY_WEAPON, vehicle, weapon); }
			static b8 HAS_CAR_BEEN_DROPPED_OFF(Vehicle car) { return NativeInvoke::Invoke< b8>(NATIVE_HAS_CAR_BEEN_DROPPED_OFF, car); }
			static b8 HAS_CAR_BEEN_RESPRAYED(Vehicle vehicle) { return NativeInvoke::Invoke< b8>(NATIVE_HAS_CAR_BEEN_RESPRAYED, vehicle); }
			static b8 HAS_CAR_RECORDING_BEEN_LOADED(int CarRec) { return NativeInvoke::Invoke< b8>(NATIVE_HAS_CAR_RECORDING_BEEN_LOADED, CarRec); }
			static b8 HAS_CAR_STOPPED_BECAUSE_OF_LIGHT(Vehicle car) { return NativeInvoke::Invoke< b8>(NATIVE_HAS_CAR_STOPPED_BECAUSE_OF_LIGHT, car); }
			static b8 HAS_CHAR_BEEN_DAMAGED_BY_CAR(Ped ped, Vehicle vehicle) { return NativeInvoke::Invoke< b8>(NATIVE_HAS_CHAR_BEEN_DAMAGED_BY_CAR, ped, vehicle); }
			static b8 HAS_OBJECT_BEEN_DAMAGED_BY_CAR(Entity obj, Vehicle vehicle) { return NativeInvoke::Invoke< b8>(NATIVE_HAS_OBJECT_BEEN_DAMAGED_BY_CAR, obj, vehicle); }
			static b8 HAS_RESPRAY_HAPPENED() { return NativeInvoke::Invoke< b8>(NATIVE_HAS_RESPRAY_HAPPENED); }
			static b8 IS_BIG_VEHICLE(Vehicle vehicle) { return NativeInvoke::Invoke< b8>(NATIVE_IS_BIG_VEHICLE, vehicle); }
			static b8 IS_CAR_ATTACHED(Vehicle vehicle) { return NativeInvoke::Invoke< b8>(NATIVE_IS_CAR_ATTACHED, vehicle); }
			static b8 IS_CAR_A_MISSION_CAR(Vehicle vehicle) { return NativeInvoke::Invoke< b8>(NATIVE_IS_CAR_A_MISSION_CAR, vehicle); }
			static b8 IS_CAR_DEAD(Vehicle vehicle) { return NativeInvoke::Invoke< b8>(NATIVE_IS_CAR_DEAD, vehicle); }
			static b8 IS_CAR_DOOR_DAMAGED(Vehicle vehicle, unsigned int door) { return NativeInvoke::Invoke< b8>(NATIVE_IS_CAR_DOOR_DAMAGED, vehicle, door); }
			static b8 IS_CAR_DOOR_FULLY_OPEN(Vehicle vehicle, unsigned int door) { return NativeInvoke::Invoke< b8>(NATIVE_IS_CAR_DOOR_FULLY_OPEN, vehicle, door); }
			static b8 IS_CAR_HEALTH_GREATER(Vehicle car, float health) { return NativeInvoke::Invoke< b8>(NATIVE_IS_CAR_HEALTH_GREATER, car, health); }
			static b8 IS_CAR_IN_AIR_PROPER(Vehicle vehicle) { return NativeInvoke::Invoke< b8>(NATIVE_IS_CAR_IN_AIR_PROPER, vehicle); }
			static b8 IS_CAR_IN_AREA_2D(Vehicle vehicle, float x1, float y1, float x2, float y2, b8 unknownFalse) { return NativeInvoke::Invoke< b8>(NATIVE_IS_CAR_IN_AREA_2D, vehicle, x1, y1, x2, y2, unknownFalse); }
			static b8 IS_CAR_IN_AREA_3D(Vehicle vehicle, float x1, float y1, float z1, float x2, float y2, float z2, unsigned int unknownFalse) { return NativeInvoke::Invoke< b8>(NATIVE_IS_CAR_IN_AREA_3D, vehicle, x1, y1, z1, x2, y2, z2, unknownFalse); }
			static b8 IS_CAR_IN_GARAGE_AREA(String^ garageName, Vehicle vehicle)
			{
				msclr::interop::marshal_context ctx;
				return NativeInvoke::Invoke< b8>(NATIVE_IS_CAR_IN_GARAGE_AREA, ctx.marshal_as<const char*>(garageName), vehicle);
			}
			static b8 IS_CAR_IN_WATER(Vehicle vehicle) { return NativeInvoke::Invoke< b8>(NATIVE_IS_CAR_IN_WATER, vehicle); }
			static b8 IS_CAR_LOW_RIDER(Vehicle car) { return NativeInvoke::Invoke< b8>(NATIVE_IS_CAR_LOW_RIDER, car); }
			static b8 IS_CAR_MODEL(Vehicle vehicle, unsigned int model) { return NativeInvoke::Invoke< b8>(NATIVE_IS_CAR_MODEL, vehicle, model); }
			static b8 IS_CAR_ON_FIRE(Vehicle vehicle) { return NativeInvoke::Invoke< b8>(NATIVE_IS_CAR_ON_FIRE, vehicle); }
			static b8 IS_CAR_ON_SCREEN(Vehicle vehicle) { return NativeInvoke::Invoke< b8>(NATIVE_IS_CAR_ON_SCREEN, vehicle); }
			static b8 IS_CAR_PASSENGER_SEAT_FREE(Vehicle vehicle, unsigned int seatIndex) { return NativeInvoke::Invoke< b8>(NATIVE_IS_CAR_PASSENGER_SEAT_FREE, vehicle, seatIndex); }
			static b8 IS_CAR_PLAYING_ANIM(Vehicle car, String^ animname0, String^ animname1)
			{
				msclr::interop::marshal_context ctx;
				return NativeInvoke::Invoke< b8>(NATIVE_IS_CAR_PLAYING_ANIM, car, ctx.marshal_as<const char*>(animname0), ctx.marshal_as<const char*>(animname1));
			}
			static b8 IS_CAR_SIREN_ON(Vehicle vehicle) { return NativeInvoke::Invoke< b8>(NATIVE_IS_CAR_SIREN_ON, vehicle); }
			static b8 IS_CAR_STOPPED(Vehicle vehicle) { return NativeInvoke::Invoke< b8>(NATIVE_IS_CAR_STOPPED, vehicle); }
			static b8 IS_CAR_STOPPED_AT_TRAFFIC_LIGHTS(Vehicle vehicle) { return NativeInvoke::Invoke< b8>(NATIVE_IS_CAR_STOPPED_AT_TRAFFIC_LIGHTS, vehicle); }
			static b8 IS_CAR_STREET_RACER(Vehicle car) { return NativeInvoke::Invoke< b8>(NATIVE_IS_CAR_STREET_RACER, car); }
			static b8 IS_CAR_STUCK(Vehicle car) { return NativeInvoke::Invoke< b8>(NATIVE_IS_CAR_STUCK, car); }
			static b8 IS_CAR_STUCK_ON_ROOF(Vehicle vehicle) { return NativeInvoke::Invoke< b8>(NATIVE_IS_CAR_STUCK_ON_ROOF, vehicle); }
			static b8 IS_CAR_TOUCHING_CAR(Vehicle vehicle, Vehicle otherCar) { return NativeInvoke::Invoke< b8>(NATIVE_IS_CAR_TOUCHING_CAR, vehicle, otherCar); }
			static b8 IS_CAR_TYRE_BURST(Vehicle vehicle, unsigned int tyre) { return NativeInvoke::Invoke< b8>(NATIVE_IS_CAR_TYRE_BURST, vehicle, tyre); }
			static b8 IS_CAR_UPRIGHT(Vehicle vehicle) { return NativeInvoke::Invoke< b8>(NATIVE_IS_CAR_UPRIGHT, vehicle); }
			static b8 IS_CAR_UPSIDEDOWN(Vehicle vehicle) { return NativeInvoke::Invoke< b8>(NATIVE_IS_CAR_UPSIDEDOWN, vehicle); }
			static b8 IS_CAR_WAITING_FOR_WORLD_COLLISION(Vehicle vehicle) { return NativeInvoke::Invoke< b8>(NATIVE_IS_CAR_WAITING_FOR_WORLD_COLLISION, vehicle); }
			static b8 IS_CHAR_IN_CAR(Ped ped, Vehicle vehicle) { return NativeInvoke::Invoke< b8>(NATIVE_IS_CHAR_IN_CAR, ped, vehicle); }
			static b8 IS_CHAR_IN_MODEL(Ped ped, unsigned int model) { return NativeInvoke::Invoke< b8>(NATIVE_IS_CHAR_IN_MODEL, ped, model); }
			static b8 IS_CHAR_TOUCHING_VEHICLE(Ped ped, Vehicle vehicle) { return NativeInvoke::Invoke< b8>(NATIVE_IS_CHAR_TOUCHING_VEHICLE, ped, vehicle); }
			static b8 IS_EMERGENCY_SERVICES_VEHICLE(Vehicle veh) { return NativeInvoke::Invoke< b8>(NATIVE_IS_EMERGENCY_SERVICES_VEHICLE, veh); }
			static b8 IS_HELI_PART_BROKEN(Vehicle heli, b8 flag0, b8 flag1, b8 flag2) { return NativeInvoke::Invoke< b8>(NATIVE_IS_HELI_PART_BROKEN, heli, flag0, flag1, flag2); }
			static b8 IS_NEXT_STATION_ALLOWED(Vehicle veh) { return NativeInvoke::Invoke< b8>(NATIVE_IS_NEXT_STATION_ALLOWED, veh); }
			static b8 IS_PLAYBACK_GOING_ON_FOR_CAR(Vehicle car) { return NativeInvoke::Invoke< b8>(NATIVE_IS_PLAYBACK_GOING_ON_FOR_CAR, car); }
			static b8 IS_THIS_MODEL_A_BIKE(unsigned int model) { return NativeInvoke::Invoke< b8>(NATIVE_IS_THIS_MODEL_A_BIKE, model); }
			static b8 IS_THIS_MODEL_A_BOAT(unsigned int model) { return NativeInvoke::Invoke< b8>(NATIVE_IS_THIS_MODEL_A_BOAT, model); }
			static b8 IS_THIS_MODEL_A_CAR(unsigned int model) { return NativeInvoke::Invoke< b8>(NATIVE_IS_THIS_MODEL_A_CAR, model); }
			static b8 IS_THIS_MODEL_A_HELI(unsigned int model) { return NativeInvoke::Invoke< b8>(NATIVE_IS_THIS_MODEL_A_HELI, model); }
			static b8 IS_THIS_MODEL_A_PED(unsigned int model) { return NativeInvoke::Invoke< b8>(NATIVE_IS_THIS_MODEL_A_PED, model); }
			static b8 IS_THIS_MODEL_A_PLANE(unsigned int model) { return NativeInvoke::Invoke< b8>(NATIVE_IS_THIS_MODEL_A_PLANE, model); }
			static b8 IS_THIS_MODEL_A_TRAIN(unsigned int model) { return NativeInvoke::Invoke< b8>(NATIVE_IS_THIS_MODEL_A_TRAIN, model); }
			static b8 IS_THIS_MODEL_A_VEHICLE(unsigned int model) { return NativeInvoke::Invoke< b8>(NATIVE_IS_THIS_MODEL_A_VEHICLE, model); }
			static b8 IS_VEHICLE_EXTRA_TURNED_ON(Vehicle vehicle, unsigned int extra) { return NativeInvoke::Invoke< b8>(NATIVE_IS_VEHICLE_EXTRA_TURNED_ON, vehicle, extra); }
			static b8 IS_VEHICLE_ON_ALL_WHEELS(Vehicle vehicle) { return NativeInvoke::Invoke< b8>(NATIVE_IS_VEHICLE_ON_ALL_WHEELS, vehicle); }
			static b8 IS_VEHICLE_TOUCHING_OBJECT(Vehicle veh, Entity obj) { return NativeInvoke::Invoke< b8>(NATIVE_IS_VEHICLE_TOUCHING_OBJECT, veh, obj); }
			static b8 IS_VEH_DRIVEABLE(Vehicle vehicle) { return NativeInvoke::Invoke< b8>(NATIVE_IS_VEH_DRIVEABLE, vehicle); }
			static b8 IS_VEH_STUCK(Vehicle veh, int time, b8 flag0, b8 flag1, b8 flag2) { return NativeInvoke::Invoke< b8>(NATIVE_IS_VEH_STUCK, veh, time, flag0, flag1, flag2); }
			static b8 IS_VEH_WINDOW_INTACT(Vehicle vehicle, unsigned int window) { return NativeInvoke::Invoke< b8>(NATIVE_IS_VEH_WINDOW_INTACT, vehicle, window); }
			static b8 LOCATE_CAR_2D(Vehicle car, float x0, float y0, float xUnk48, float yUnk49, b8 flag) { return NativeInvoke::Invoke< b8>(NATIVE_LOCATE_CAR_2D, car, x0, y0, xUnk48, yUnk49, flag); }
			static b8 LOCATE_CAR_3D(Vehicle car, float x, float y, float z, float xa, float ya, float za, b8 flag) { return NativeInvoke::Invoke< b8>(NATIVE_LOCATE_CAR_3D, car, x, y, z, xa, ya, za, flag); }
			static b8 LOCATE_DEAD_CAR_3D(Vehicle car, float x, float y, float z, float xa, float ya, float za, b8 flag) { return NativeInvoke::Invoke< b8>(NATIVE_LOCATE_DEAD_CAR_3D, car, x, y, z, xa, ya, za, flag); }
			static b8 PLAY_CAR_ANIM(Vehicle car, String^ animname0, String^ animname1, float Unk50, b8 flag0, b8 flag1)
			{
				msclr::interop::marshal_context ctx;
				return NativeInvoke::Invoke< b8>(NATIVE_PLAY_CAR_ANIM, car, ctx.marshal_as<const char*>(animname0), ctx.marshal_as<const char*>(animname1), Unk50, flag0, flag1);
			}
			static b8 DOES_OBJECT_EXIST(Entity obj) { return NativeInvoke::Invoke< b8>(NATIVE_DOES_OBJECT_EXIST, obj); }
			static b8 DOES_OBJECT_HAVE_PHYSICS(Entity obj) { return NativeInvoke::Invoke< b8>(NATIVE_DOES_OBJECT_HAVE_PHYSICS, obj); }
			static b8 DOES_OBJECT_HAVE_THIS_MODEL(Entity obj, unsigned int model) { return NativeInvoke::Invoke< b8>(NATIVE_DOES_OBJECT_HAVE_THIS_MODEL, obj, model); }
			static b8 DOES_OBJECT_OF_TYPE_EXIST_AT_COORDS(float x, float y, float z, float radius, unsigned int model) { return NativeInvoke::Invoke< b8>(NATIVE_DOES_OBJECT_OF_TYPE_EXIST_AT_COORDS, x, y, z, radius, model); }
			static b8 HAS_CLOSEST_OBJECT_OF_TYPE_BEEN_DAMAGED_BY_CAR(float x, float y, float z, float radius, unsigned int type_or_model, Vehicle car) { return NativeInvoke::Invoke< b8>(NATIVE_HAS_CLOSEST_OBJECT_OF_TYPE_BEEN_DAMAGED_BY_CAR, x, y, z, radius, type_or_model, car); }
			static b8 HAS_CLOSEST_OBJECT_OF_TYPE_BEEN_DAMAGED_BY_CHAR(float x, float y, float z, float radius, unsigned int objectModel, Ped ped) { return NativeInvoke::Invoke< b8>(NATIVE_HAS_CLOSEST_OBJECT_OF_TYPE_BEEN_DAMAGED_BY_CHAR, x, y, z, radius, objectModel, ped); }
			static b8 HAS_FRAGMENT_ROOT_OF_CLOSEST_OBJECT_OF_TYPE_BEEN_DAMAGED(float x, float y, float z, float radius, unsigned int Unk70) { return NativeInvoke::Invoke< b8>(NATIVE_HAS_FRAGMENT_ROOT_OF_CLOSEST_OBJECT_OF_TYPE_BEEN_DAMAGED, x, y, z, radius, Unk70); }
			static b8 HAS_OBJECT_BEEN_DAMAGED(Entity obj) { return NativeInvoke::Invoke< b8>(NATIVE_HAS_OBJECT_BEEN_DAMAGED, obj); }
			static b8 HAS_OBJECT_BEEN_DAMAGED_BY_CHAR(Entity obj, Ped ped) { return NativeInvoke::Invoke< b8>(NATIVE_HAS_OBJECT_BEEN_DAMAGED_BY_CHAR, obj, ped); }
			static b8 HAS_OBJECT_BEEN_DAMAGED_BY_WEAPON(Entity obj, int Unk71) { return NativeInvoke::Invoke< b8>(NATIVE_HAS_OBJECT_BEEN_DAMAGED_BY_WEAPON, obj, Unk71); }
			static b8 HAS_OBJECT_BEEN_PHOTOGRAPHED(Entity obj) { return NativeInvoke::Invoke< b8>(NATIVE_HAS_OBJECT_BEEN_PHOTOGRAPHED, obj); }
			static b8 HAS_OBJECT_BEEN_UPROOTED(Entity obj) { return NativeInvoke::Invoke< b8>(NATIVE_HAS_OBJECT_BEEN_UPROOTED, obj); }
			static b8 HAS_OBJECT_COLLIDED_WITH_ANYTHING(Entity obj) { return NativeInvoke::Invoke< b8>(NATIVE_HAS_OBJECT_COLLIDED_WITH_ANYTHING, obj); }
			static b8 HAS_OBJECT_FRAGMENT_ROOT_BEEN_DAMAGED(Entity obj) { return NativeInvoke::Invoke< b8>(NATIVE_HAS_OBJECT_FRAGMENT_ROOT_BEEN_DAMAGED, obj); }
			static b8 HAS_POOL_OBJECT_COLLIDED_WITH_CUSHION(Entity obj) { return NativeInvoke::Invoke< b8>(NATIVE_HAS_POOL_OBJECT_COLLIDED_WITH_CUSHION, obj); }
			static b8 HAS_POOL_OBJECT_COLLIDED_WITH_OBJECT(Entity obj, Entity otherObj) { return NativeInvoke::Invoke< b8>(NATIVE_HAS_POOL_OBJECT_COLLIDED_WITH_OBJECT, obj, otherObj); }
			static b8 IS_CLOSEST_OBJECT_OF_TYPE_SMASHED_OR_DAMAGED(float x, float y, float z, float radius, unsigned int type_or_model, b8 flag0, b8 flag1) { return NativeInvoke::Invoke< b8>(NATIVE_IS_CLOSEST_OBJECT_OF_TYPE_SMASHED_OR_DAMAGED, x, y, z, radius, type_or_model, flag0, flag1); }
			static b8 IS_GARAGE_CLOSED(String^ garageName)
			{
				msclr::interop::marshal_context ctx;
				return NativeInvoke::Invoke< b8>(NATIVE_IS_GARAGE_CLOSED, ctx.marshal_as<const char*>(garageName));
			}
			static b8 IS_GARAGE_OPEN(String^ garageName)
			{
				msclr::interop::marshal_context ctx;
				return NativeInvoke::Invoke< b8>(NATIVE_IS_GARAGE_OPEN, ctx.marshal_as<const char*>(garageName));
			}
			static b8 IS_NON_FRAG_OBJECT_SMASHED(float x, float y, float z, float radius, unsigned int model) { return NativeInvoke::Invoke< b8>(NATIVE_IS_NON_FRAG_OBJECT_SMASHED, x, y, z, radius, model); }
			static b8 IS_OBJECT_ATTACHED(Entity obj) { return NativeInvoke::Invoke< b8>(NATIVE_IS_OBJECT_ATTACHED, obj); }
			static b8 IS_OBJECT_IN_ANGLED_AREA_3D(Entity obj, float x0, float y0, float z0, float x1, float y1, float z1, float Unk72, b8 flag) { return NativeInvoke::Invoke< b8>(NATIVE_IS_OBJECT_IN_ANGLED_AREA_3D, obj, x0, y0, z0, x1, y1, z1, Unk72, flag); }
			static b8 IS_OBJECT_IN_AREA_2D(Entity obj, float x0, float y0, float x1, float y2, b8 flag) { return NativeInvoke::Invoke< b8>(NATIVE_IS_OBJECT_IN_AREA_2D, obj, x0, y0, x1, y2, flag); }
			static b8 IS_OBJECT_IN_AREA_3D(Entity obj, float x0, float y0, float z0, float x1, float y1, float z1, b8 flag) { return NativeInvoke::Invoke< b8>(NATIVE_IS_OBJECT_IN_AREA_3D, obj, x0, y0, z0, x1, y1, z1, flag); }
			static b8 IS_OBJECT_IN_WATER(Entity obj) { return NativeInvoke::Invoke< b8>(NATIVE_IS_OBJECT_IN_WATER, obj); }
			static b8 IS_OBJECT_ON_FIRE(Entity obj) { return NativeInvoke::Invoke< b8>(NATIVE_IS_OBJECT_ON_FIRE, obj); }
			static b8 IS_OBJECT_ON_SCREEN(Entity obj) { return NativeInvoke::Invoke< b8>(NATIVE_IS_OBJECT_ON_SCREEN, obj); }
			static b8 IS_OBJECT_PLAYING_ANIM(Entity obj, String^ animname0, String^ animname1)
			{
				msclr::interop::marshal_context ctx;
				return NativeInvoke::Invoke< b8>(NATIVE_IS_OBJECT_PLAYING_ANIM, obj, ctx.marshal_as<const char*>(animname0), ctx.marshal_as<const char*>(animname1));
			}
			static b8 IS_OBJECT_STATIC(Entity obj) { return NativeInvoke::Invoke< b8>(NATIVE_IS_OBJECT_STATIC, obj); }
			static b8 IS_OBJECT_TOUCHING_OBJECT(Entity obj0, Entity obj1) { return NativeInvoke::Invoke< b8>(NATIVE_IS_OBJECT_TOUCHING_OBJECT, obj0, obj1); }
			static b8 IS_OBJECT_UPRIGHT(Entity obj, float angle) { return NativeInvoke::Invoke< b8>(NATIVE_IS_OBJECT_UPRIGHT, obj, angle); }
			static b8 IS_OBJECT_WITHIN_BRAIN_ACTIVATION_RANGE(Entity obj) { return NativeInvoke::Invoke< b8>(NATIVE_IS_OBJECT_WITHIN_BRAIN_ACTIVATION_RANGE, obj); }
			static b8 IS_SITTING_OBJECT_NEAR(float x, float y, float z, int Unk73) { return NativeInvoke::Invoke< b8>(NATIVE_IS_SITTING_OBJECT_NEAR, x, y, z, Unk73); }
			static b8 LOCATE_OBJECT_2D(Entity obj, float x0, float y0, float x1, float y1, b8 flag) { return NativeInvoke::Invoke< b8>(NATIVE_LOCATE_OBJECT_2D, obj, x0, y0, x1, y1, flag); }
			static b8 LOCATE_OBJECT_3D(Entity obj, float x, float y, float z, float xr, float yr, float zr, b8 flag) { return NativeInvoke::Invoke< b8>(NATIVE_LOCATE_OBJECT_3D, obj, x, y, z, xr, yr, zr, flag); }
			static b8 PLAY_OBJECT_ANIM(Entity obj, String^ animname0, String^ animname1, float Unk74, b8 flag0, b8 flag1)
			{
				msclr::interop::marshal_context ctx;
				return NativeInvoke::Invoke< b8>(NATIVE_PLAY_OBJECT_ANIM, obj, ctx.marshal_as<const char*>(animname0), ctx.marshal_as<const char*>(animname1), Unk74, flag0, flag1);
			}
			static b8 ROTATE_OBJECT(Entity obj, float x, float y, b8 flag) { return NativeInvoke::Invoke< b8>(NATIVE_ROTATE_OBJECT, obj, x, y, flag); }
			static b8 SLIDE_OBJECT(Entity obj, float x, float y, float z, float xs, float ys, float zs, b8 flag) { return NativeInvoke::Invoke< b8>(NATIVE_SLIDE_OBJECT, obj, x, y, z, xs, ys, zs, flag); }
			static b8 SMASH_GLASS_ON_OBJECT(float x, float y, float z, float Unk75, unsigned int model, float Unk76) { return NativeInvoke::Invoke< b8>(NATIVE_SMASH_GLASS_ON_OBJECT, x, y, z, Unk75, model, Unk76); }
			//static b8 LOOK_AT_NEARBY_ENTITY_WITH_SPECIAL_ATTRIBUTE(int Unk98, Vector3* Unk99, float* Unk100, ScriptAny* Unk101, ScriptAny* Unk102, ScriptAny* Unk103) { return NativeInvoke::Invoke< b8>(NATIVE_LOOK_AT_NEARBY_ENTITY_WITH_SPECIAL_ATTRIBUTE, Unk98, Unk99, Unk100, Unk101, Unk102, Unk103); }
			static b8 DOES_SCENARIO_EXIST_IN_AREA(ScriptAny Unk104, ScriptAny Unk105, ScriptAny Unk106, ScriptAny Unk107, ScriptAny Unk108) { return NativeInvoke::Invoke< b8>(NATIVE_DOES_SCENARIO_EXIST_IN_AREA, Unk104, Unk105, Unk106, Unk107, Unk108); }
			static b8 IS_PAIN_PLAYING(Ped ped) { return NativeInvoke::Invoke< b8>(NATIVE_IS_PAIN_PLAYING, ped); }
			static b8 _TASK_SHIMMY_CLIMB_UP(Ped ped) { return NativeInvoke::Invoke< b8>(NATIVE_TASK_SHIMMY_CLIMB_UP, ped); }
			static b8 _TASK_SHIMMY_IN_DIRECTION(Ped ped, ScriptAny Unk109) { return NativeInvoke::Invoke< b8>(NATIVE_TASK_SHIMMY_IN_DIRECTION, ped, Unk109); }
			static b8 _TASK_SHIMMY_LET_GO(Ped ped) { return NativeInvoke::Invoke< b8>(NATIVE_TASK_SHIMMY_LET_GO, ped); }
			static b8 GET_CREATE_RANDOM_COPS() { return NativeInvoke::Invoke< b8>(NATIVE_GET_CREATE_RANDOM_COPS); }
			static b8 IS_CHAR_IN_ANY_POLICE_VEHICLE(Ped ped) { return NativeInvoke::Invoke< b8>(NATIVE_IS_CHAR_IN_ANY_POLICE_VEHICLE, ped); }
			static b8 IS_COP_PED_IN_AREA_3D_NO_SAVE(float x0, float y0, float z0, float x1, float y1, float z1) { return NativeInvoke::Invoke< b8>(NATIVE_IS_COP_PED_IN_AREA_3D_NO_SAVE, x0, y0, z0, x1, y1, z1); }
			static b8 IS_COP_VEHICLE_IN_AREA_3D_NO_SAVE(float x0, float y0, float z0, float x1, float y1, float z1) { return NativeInvoke::Invoke< b8>(NATIVE_IS_COP_VEHICLE_IN_AREA_3D_NO_SAVE, x0, y0, z0, x1, y1, z1); }
			static b8 IS_WANTED_LEVEL_GREATER(Player playerIndex, unsigned int level) { return NativeInvoke::Invoke< b8>(NATIVE_IS_WANTED_LEVEL_GREATER, playerIndex, level); }
			static b8 WANTED_STARS_ARE_FLASHING() { return NativeInvoke::Invoke< b8>(NATIVE_WANTED_STARS_ARE_FLASHING); }
			static b8 IS_PC_VERSION() { return NativeInvoke::Invoke< b8>(NATIVE_IS_PC_VERSION); }
			static b8 IS_XBOX360_VERSION() { return NativeInvoke::Invoke< b8>(NATIVE_IS_XBOX360_VERSION); }
			static b8 ARE_ALL_NAVMESH_REGIONS_LOADED() { return NativeInvoke::Invoke< b8>(NATIVE_ARE_ALL_NAVMESH_REGIONS_LOADED); }
			static b8 ARE_CREDITS_FINISHED() { return NativeInvoke::Invoke< b8>(NATIVE_ARE_CREDITS_FINISHED); }
			static b8 CAN_CREATE_RANDOM_CHAR(b8 flag0, b8 flag1) { return NativeInvoke::Invoke< b8>(NATIVE_CAN_CREATE_RANDOM_CHAR, flag0, flag1); }
			static b8 CAN_FONT_BE_LOADED(int fontid) { return NativeInvoke::Invoke< b8>(NATIVE_CAN_FONT_BE_LOADED, fontid); }
			static b8 CAN_START_MISSION_PASSED_TUNE() { return NativeInvoke::Invoke< b8>(NATIVE_CAN_START_MISSION_PASSED_TUNE); }
			static b8 CHEAT_HAPPENED_RECENTLY(int cheat, int time) { return NativeInvoke::Invoke< b8>(NATIVE_CHEAT_HAPPENED_RECENTLY, cheat, time); }
			static b8 DID_SAVE_COMPLETE_SUCCESSFULLY() { return NativeInvoke::Invoke< b8>(NATIVE_DID_SAVE_COMPLETE_SUCCESSFULLY); }
			static b8 DOES_THIS_MINIGAME_SCRIPT_ALLOW_NON_MINIGAME_HELP_MESSAGES() { return NativeInvoke::Invoke< b8>(NATIVE_DOES_THIS_MINIGAME_SCRIPT_ALLOW_NON_MINIGAME_HELP_MESSAGES); }
			static b8 GET_GFWL_HAS_SAFE_HOUSE() { return NativeInvoke::Invoke< b8>(NATIVE_GET_GFWL_HAS_SAFE_HOUSE); }
			static b8 GET_IS_DEPOSIT_ANIM_RUNNING() { return NativeInvoke::Invoke< b8>(NATIVE_GET_IS_DEPOSIT_ANIM_RUNNING); }
			static b8 GET_MISSION_FLAG() { return NativeInvoke::Invoke< b8>(NATIVE_GET_MISSION_FLAG); }
			static b8 HAS_DEATHARREST_EXECUTED() { return NativeInvoke::Invoke< b8>(NATIVE_HAS_DEATHARREST_EXECUTED); }
			static b8 IS_AREA_OCCUPIED(float x1, float y1, float z1, float x2, float y2, float z2, b8 unknownFalse1, b8 unknownTrue, b8 unknownFalse2, b8 unknownFalse3, b8 unknownFalse4) { return NativeInvoke::Invoke< b8>(NATIVE_IS_AREA_OCCUPIED, x1, y1, z1, x2, y2, z2, unknownFalse1, unknownTrue, unknownFalse2, unknownFalse3, unknownFalse4); }
			//static b8 IS_AUSSIE_VERSION() { return NativeInvoke::Invoke< b8>(NATIVE_IS_AUSSIE_VERSION); }
			static b8 IS_AUTO_AIMING_ON() { return NativeInvoke::Invoke< b8>(NATIVE_IS_AUTO_AIMING_ON); }
			static b8 IS_AUTO_SAVE_IN_PROGRESS() { return NativeInvoke::Invoke< b8>(NATIVE_IS_AUTO_SAVE_IN_PROGRESS); }
			static b8 IS_BIT_SET(int val, int bitnum) { return NativeInvoke::Invoke< b8>(NATIVE_IS_BIT_SET, val, bitnum); }
			static b8 IS_BULLET_IN_AREA(float x, float y, float z, float radius, b8 unknownTrue) { return NativeInvoke::Invoke< b8>(NATIVE_IS_BULLET_IN_AREA, x, y, z, radius, unknownTrue); }
			static b8 IS_BULLET_IN_BOX(float x1, float y1, float z1, float x2, float y2, float z2, b8 unknown) { return NativeInvoke::Invoke< b8>(NATIVE_IS_BULLET_IN_BOX, x1, y1, z1, x2, y2, z2, unknown); }
			static b8 IS_EPISODE_AVAILABLE(int episode) { return NativeInvoke::Invoke< b8>(NATIVE_IS_EPISODE_AVAILABLE, episode); }
			static b8 IS_FONT_LOADED(unsigned int font) { return NativeInvoke::Invoke< b8>(NATIVE_IS_FONT_LOADED, font); }
			static b8 IS_FRONTEND_FADING() { return NativeInvoke::Invoke< b8>(NATIVE_IS_FRONTEND_FADING); }
			static b8 IS_GAME_IN_CONTROL_OF_MUSIC() { return NativeInvoke::Invoke< b8>(NATIVE_IS_GAME_IN_CONTROL_OF_MUSIC); }
			//static b8 IS_GERMAN_VERSION() { return NativeInvoke::Invoke< b8>(NATIVE_IS_GERMAN_VERSION); }
			static b8 IS_HELP_MESSAGE_BEING_DISPLAYED() { return NativeInvoke::Invoke< b8>(NATIVE_IS_HELP_MESSAGE_BEING_DISPLAYED); }
			static b8 IS_HINT_RUNNING() { return NativeInvoke::Invoke< b8>(NATIVE_IS_HINT_RUNNING); }
			static b8 IS_HUD_PREFERENCE_SWITCHED_ON() { return NativeInvoke::Invoke< b8>(NATIVE_IS_HUD_PREFERENCE_SWITCHED_ON); }
			static b8 IS_HUD_RETICULE_COMPLEX() { return NativeInvoke::Invoke< b8>(NATIVE_IS_HUD_RETICULE_COMPLEX); }
			static b8 IS_INTERIOR_SCENE() { return NativeInvoke::Invoke< b8>(NATIVE_IS_INTERIOR_SCENE); }
			static b8 IS_IN_LAN_MODE() { return NativeInvoke::Invoke< b8>(NATIVE_IS_IN_LAN_MODE); }
			static b8 IS_IN_PLAYER_SETTINGS_MENU() { return NativeInvoke::Invoke< b8>(NATIVE_IS_IN_PLAYER_SETTINGS_MENU); }
			static b8 IS_IN_SPECTATOR_MODE() { return NativeInvoke::Invoke< b8>(NATIVE_IS_IN_SPECTATOR_MODE); }
			static b8 IS_JAPANESE_VERSION() { return NativeInvoke::Invoke< b8>(NATIVE_IS_JAPANESE_VERSION); }
			static b8 IS_LAZLOW_STATION_LOCKED() { return NativeInvoke::Invoke< b8>(NATIVE_IS_LAZLOW_STATION_LOCKED); }
			static b8 IS_LOOK_INVERTED() { return NativeInvoke::Invoke< b8>(NATIVE_IS_LOOK_INVERTED); }
			static b8 IS_MEMORY_CARD_IN_USE() { return NativeInvoke::Invoke< b8>(NATIVE_IS_MEMORY_CARD_IN_USE); }
			static b8 IS_MESSAGE_BEING_DISPLAYED() { return NativeInvoke::Invoke< b8>(NATIVE_IS_MESSAGE_BEING_DISPLAYED); }
			static b8 IS_MINIGAME_IN_PROGRESS() { return NativeInvoke::Invoke< b8>(NATIVE_IS_MINIGAME_IN_PROGRESS); }
			static b8 IS_MISSION_COMPLETE_PLAYING() { return NativeInvoke::Invoke< b8>(NATIVE_IS_MISSION_COMPLETE_PLAYING); }
			static b8 IS_PAUSE_MENU_ACTIVE() { return NativeInvoke::Invoke< b8>(NATIVE_IS_PAUSE_MENU_ACTIVE); }
			static b8 IS_PAY_N_SPRAY_ACTIVE() { return NativeInvoke::Invoke< b8>(NATIVE_IS_PAY_N_SPRAY_ACTIVE); }
			static b8 IS_POINT_OBSCURED_BY_A_MISSION_ENTITY(float pX, float pY, float pZ, float sizeX, float sizeY, float sizeZ) { return NativeInvoke::Invoke< b8>(NATIVE_IS_POINT_OBSCURED_BY_A_MISSION_ENTITY, pX, pY, pZ, sizeX, sizeY, sizeZ); }
			static b8 IS_PROJECTILE_IN_AREA(float x0, float y0, float z0, float x1, float y1, float z1) { return NativeInvoke::Invoke< b8>(NATIVE_IS_PROJECTILE_IN_AREA, x0, y0, z0, x1, y1, z1); }
			static b8 IS_RADIO_HUD_ON() { return NativeInvoke::Invoke< b8>(NATIVE_IS_RADIO_HUD_ON); }
			static b8 IS_RADIO_RETUNING() { return NativeInvoke::Invoke< b8>(NATIVE_IS_RADIO_RETUNING); }
			static b8 IS_RELATIONSHIP_SET(int Unk493, int Unk494, int Unk495) { return NativeInvoke::Invoke< b8>(NATIVE_IS_RELATIONSHIP_SET, Unk493, Unk494, Unk495); }
			static b8 IS_REPLAY_SAVING() { return NativeInvoke::Invoke< b8>(NATIVE_IS_REPLAY_SAVING); }
			static b8 IS_REPLAY_SYSTEM_SAVING() { return NativeInvoke::Invoke< b8>(NATIVE_IS_REPLAY_SYSTEM_SAVING); }
			static b8 IS_SCREEN_FADED_IN() { return NativeInvoke::Invoke< b8>(NATIVE_IS_SCREEN_FADED_IN); }
			static b8 IS_SCREEN_FADED_OUT() { return NativeInvoke::Invoke< b8>(NATIVE_IS_SCREEN_FADED_OUT); }
			static b8 IS_SCREEN_FADING() { return NativeInvoke::Invoke< b8>(NATIVE_IS_SCREEN_FADING); }
			static b8 IS_SCREEN_FADING_IN() { return NativeInvoke::Invoke< b8>(NATIVE_IS_SCREEN_FADING_IN); }
			static b8 IS_SCREEN_FADING_OUT() { return NativeInvoke::Invoke< b8>(NATIVE_IS_SCREEN_FADING_OUT); }
			static b8 IS_SNIPER_INVERTED() { return NativeInvoke::Invoke< b8>(NATIVE_IS_SNIPER_INVERTED); }
			static b8 IS_SYSTEM_UI_SHOWING() { return NativeInvoke::Invoke< b8>(NATIVE_IS_SYSTEM_UI_SHOWING); }
			static b8 IS_THIS_A_MINIGAME_SCRIPT() { return NativeInvoke::Invoke< b8>(NATIVE_IS_THIS_A_MINIGAME_SCRIPT); }
			static b8 SECUROM_SPOT_CHECK1() { return NativeInvoke::Invoke< b8>(NATIVE_SECUROM_SPOT_CHECK1); }
			static b8 SECUROM_SPOT_CHECK2() { return NativeInvoke::Invoke< b8>(NATIVE_SECUROM_SPOT_CHECK2); }
			static b8 SECUROM_SPOT_CHECK3() { return NativeInvoke::Invoke< b8>(NATIVE_SECUROM_SPOT_CHECK3); }
			static b8 SECUROM_SPOT_CHECK4() { return NativeInvoke::Invoke< b8>(NATIVE_SECUROM_SPOT_CHECK4); }
			static b8 STRING_TO_INT(String^ str, [OutAttribute] int% intval)
			{
				msclr::interop::marshal_context ctx;
				int v;
				b8 r = NativeInvoke::Invoke<b8>(NATIVE_STRING_TO_INT, ctx.marshal_as<const char*>(str), &v);
				intval = v;
				return r;
			}
			static b8 HAS_SOUND_FINISHED(unsigned int sound) { return NativeInvoke::Invoke< b8>(NATIVE_HAS_SOUND_FINISHED, sound); }
			static b8 IS_AMBIENT_SPEECH_DISABLED(Ped ped) { return NativeInvoke::Invoke< b8>(NATIVE_IS_AMBIENT_SPEECH_DISABLED, ped); }
			static b8 IS_AMBIENT_SPEECH_PLAYING(Ped ped) { return NativeInvoke::Invoke< b8>(NATIVE_IS_AMBIENT_SPEECH_PLAYING, ped); }
			static b8 IS_ANY_SPEECH_PLAYING(Ped ped) { return NativeInvoke::Invoke< b8>(NATIVE_IS_ANY_SPEECH_PLAYING, ped); }
			static b8 IS_SCRIPTED_CONVERSATION_ONGOING() { return NativeInvoke::Invoke< b8>(NATIVE_IS_SCRIPTED_CONVERSATION_ONGOING); }
			static b8 IS_SCRIPTED_SPEECH_PLAYING(Ped ped) { return NativeInvoke::Invoke< b8>(NATIVE_IS_SCRIPTED_SPEECH_PLAYING, ped); }
			static b8 REQUEST_AMBIENT_AUDIO_BANK(String^ name)
			{
				msclr::interop::marshal_context ctx;
				return NativeInvoke::Invoke< b8>(NATIVE_REQUEST_AMBIENT_AUDIO_BANK, ctx.marshal_as<const char*>(name));
			}
			static b8 REQUEST_MISSION_AUDIO_BANK(String^ name)
			{
				msclr::interop::marshal_context ctx;
				return NativeInvoke::Invoke< b8>(NATIVE_REQUEST_MISSION_AUDIO_BANK, ctx.marshal_as<const char*>(name));
			}
			static b8 ENABLE_SCRIPT_CONTROLLED_MICROPHONE() { return NativeInvoke::Invoke< b8>(NATIVE_ENABLE_SCRIPT_CONTROLLED_MICROPHONE); }
			static b8 HAS_CUTSCENE_FINISHED() { return NativeInvoke::Invoke< b8>(NATIVE_HAS_CUTSCENE_FINISHED); }
			static b8 HAS_CUTSCENE_LOADED() { return NativeInvoke::Invoke< b8>(NATIVE_HAS_CUTSCENE_LOADED); }
			static b8 WAS_CUTSCENE_SKIPPED() { return NativeInvoke::Invoke< b8>(NATIVE_WAS_CUTSCENE_SKIPPED); }
			static b8 CAM_IS_SPHERE_VISIBLE(Camera camera, float pX, float pY, float pZ, float radius) { return NativeInvoke::Invoke< b8>(NATIVE_CAM_IS_SPHERE_VISIBLE, camera, pX, pY, pZ, radius); }
			static b8 DOES_CAM_EXIST(int camera) { return NativeInvoke::Invoke< b8>(NATIVE_DOES_CAM_EXIST, camera); }
			static b8 DOES_VIEWPORT_EXIST(int viewportid) { return NativeInvoke::Invoke< b8>(NATIVE_DOES_VIEWPORT_EXIST, viewportid); }
			static b8 GET_VIEWPORT_POSITION_OF_COORD(float pX, float pY, float pZ, int viewportid, [OutAttribute] float% vY, [OutAttribute] float% vZ)
			{
				float y, z;
				b8 r = NativeInvoke::Invoke<b8>(NATIVE_GET_VIEWPORT_POSITION_OF_COORD, pX, pY, pZ, viewportid, &y, &z);
				vY = y;
				vZ = z;
				return r;
			}
			static b8 IS_CAM_ACTIVE(Camera camera) { return NativeInvoke::Invoke< b8>(NATIVE_IS_CAM_ACTIVE, camera); }
			static b8 IS_CAM_HAPPY(int cam) { return NativeInvoke::Invoke< b8>(NATIVE_IS_CAM_HAPPY, cam); }
			static b8 IS_CAM_INTERPOLATING() { return NativeInvoke::Invoke< b8>(NATIVE_IS_CAM_INTERPOLATING); }
			static b8 IS_CAM_PROPAGATING(Camera camera) { return NativeInvoke::Invoke< b8>(NATIVE_IS_CAM_PROPAGATING, camera); }
			static b8 IS_CAM_SEQUENCE_COMPLETE(int Unk535) { return NativeInvoke::Invoke< b8>(NATIVE_IS_CAM_SEQUENCE_COMPLETE, Unk535); }
			static b8 IS_CAM_SHAKING() { return NativeInvoke::Invoke< b8>(NATIVE_IS_CAM_SHAKING); }
			static b8 IS_FOLLOW_VEHICLE_CAM_OFFSET_ACTIVE() { return NativeInvoke::Invoke< b8>(NATIVE_IS_FOLLOW_VEHICLE_CAM_OFFSET_ACTIVE); }
			static b8 IS_SPECIFIC_CAM_INTERPOLATING(int cam) { return NativeInvoke::Invoke< b8>(NATIVE_IS_SPECIFIC_CAM_INTERPOLATING, cam); }
			static b8 IS_VIEWPORT_ACTIVE(int viewportid) { return NativeInvoke::Invoke< b8>(NATIVE_IS_VIEWPORT_ACTIVE, viewportid); }
			static b8 GET_AMMO_IN_CLIP(Ped ped, unsigned int weapon, [OutAttribute] unsigned int% pAmmo)
			{
				unsigned int p;
				b8 r = NativeInvoke::Invoke< b8>(NATIVE_GET_AMMO_IN_CLIP, ped, weapon, &p);
				pAmmo = p;
				return r;
			}
			static b8 GET_CURRENT_CHAR_WEAPON(Ped ped, [OutAttribute] unsigned int% pWeapon)
			{
				unsigned int p;
				b8 r = NativeInvoke::Invoke< b8>(NATIVE_GET_CURRENT_CHAR_WEAPON, ped, &p);
				pWeapon = p;
				return r;
			}
			static b8 GET_MAX_AMMO(Ped ped, unsigned int weapon, [OutAttribute] unsigned int% pMaxAmmo)
			{
				unsigned int p;
				b8 r = NativeInvoke::Invoke< b8>(NATIVE_GET_MAX_AMMO, ped, weapon, &p);
				pMaxAmmo = p;
				return r;
			}
			static Texture GET_TEXTURE_FROM_STREAMED_TXD(String^ txdName, String^ textureName)
			{
				msclr::interop::marshal_context ctx;
				return NativeInvoke::Invoke< Texture>(NATIVE_GET_TEXTURE_FROM_STREAMED_TXD, ctx.marshal_as<const char*>(txdName), ctx.marshal_as<const char*>(textureName));
			}
			static b8 HAS_CHAR_BEEN_DAMAGED_BY_WEAPON(Ped ped, unsigned int weapon) { return NativeInvoke::Invoke< b8>(NATIVE_HAS_CHAR_BEEN_DAMAGED_BY_WEAPON, ped, weapon); }
			static b8 HAS_CHAR_GOT_WEAPON(Ped ped, unsigned int weapon) { return NativeInvoke::Invoke< b8>(NATIVE_HAS_CHAR_GOT_WEAPON, ped, weapon); }
			static b8 HAS_COLLISION_FOR_MODEL_LOADED(unsigned int model) { return NativeInvoke::Invoke< b8>(NATIVE_HAS_COLLISION_FOR_MODEL_LOADED, model); }
			static b8 HAS_MODEL_LOADED(int model) { return NativeInvoke::Invoke< b8>(NATIVE_HAS_MODEL_LOADED, model); }
			static b8 HAS_STREAMED_TXD_LOADED(String^ txdName)
			{
				msclr::interop::marshal_context ctx;
				return NativeInvoke::Invoke< b8>(NATIVE_HAS_STREAMED_TXD_LOADED, ctx.marshal_as<const char*>(txdName));
			}
			static b8 HAS_THIS_ADDITIONAL_TEXT_LOADED(String^ textName, unsigned int textIndex)
			{
				msclr::interop::marshal_context ctx;
				return NativeInvoke::Invoke< b8>(NATIVE_HAS_THIS_ADDITIONAL_TEXT_LOADED, ctx.marshal_as<const char*>(textName), textIndex);
			}
			static b8 HAVE_ANIMS_LOADED(String^ animName)
			{
				msclr::interop::marshal_context ctx;
				return NativeInvoke::Invoke< b8>(NATIVE_HAVE_ANIMS_LOADED, ctx.marshal_as<const char*>(animName));
			}
			static b8 HAVE_REQUESTED_PATH_NODES_BEEN_LOADED(unsigned int requestId) { return NativeInvoke::Invoke< b8>(NATIVE_HAVE_REQUESTED_PATH_NODES_BEEN_LOADED, requestId); }
			static b8 IS_MODEL_IN_CDIMAGE(int model) { return NativeInvoke::Invoke< b8>(NATIVE_IS_MODEL_IN_CDIMAGE, model); }
			static b8 IS_STREAMING_ADDITIONAL_TEXT(unsigned int textIndex) { return NativeInvoke::Invoke< b8>(NATIVE_IS_STREAMING_ADDITIONAL_TEXT, textIndex); }
			static b8 IS_STREAMING_PRIORITY_REQUESTS() { return NativeInvoke::Invoke< b8>(NATIVE_IS_STREAMING_PRIORITY_REQUESTS); }
			static b8 IS_STREAMING_THIS_ADDITIONAL_TEXT(String^ str0, int Unk597, int Unk598)
			{
				msclr::interop::marshal_context ctx;
				return NativeInvoke::Invoke< b8>(NATIVE_IS_STREAMING_THIS_ADDITIONAL_TEXT, ctx.marshal_as<const char*>(str0), Unk597, Unk598);
			}
			static b8 PRELOAD_STREAM(String^ name)
			{
				msclr::interop::marshal_context ctx;
				return NativeInvoke::Invoke< b8>(NATIVE_PRELOAD_STREAM, ctx.marshal_as<const char*>(name));
			}
			static b8 PRELOAD_STREAM_WITH_START_OFFSET(String^ StreamName, int StartOffset)
			{
				msclr::interop::marshal_context ctx;
				return NativeInvoke::Invoke< b8>(NATIVE_PRELOAD_STREAM_WITH_START_OFFSET, ctx.marshal_as<const char*>(StreamName), StartOffset);
			}
			static b8 REMOVE_NAVMESH_REQUIRED_REGION(float Unk599, float Unk600) { return NativeInvoke::Invoke< b8>(NATIVE_REMOVE_NAVMESH_REQUIRED_REGION, Unk599, Unk600); }
			static b8 UPDATE_LOAD_SCENE() { return NativeInvoke::Invoke< b8>(NATIVE_UPDATE_LOAD_SCENE); }
			static b8 DOES_SCRIPT_EXIST(String^ name)
			{
				msclr::interop::marshal_context ctx;
				return NativeInvoke::Invoke< b8>(NATIVE_DOES_SCRIPT_EXIST, ctx.marshal_as<const char*>(name));
			}
			static b8 HAS_SCRIPT_LOADED(String^ scriptName)
			{
				msclr::interop::marshal_context ctx;
				return NativeInvoke::Invoke< b8>(NATIVE_HAS_SCRIPT_LOADED, ctx.marshal_as<const char*>(scriptName));
			}
			static b8 IS_THREAD_ACTIVE(unsigned int threadId) { return NativeInvoke::Invoke< b8>(NATIVE_IS_THREAD_ACTIVE, threadId); }
			static b8 DOES_BLIP_EXIST(Blip blip) { return NativeInvoke::Invoke< b8>(NATIVE_DOES_BLIP_EXIST, blip); }
			static b8 DOES_TEXT_LABEL_EXIST(String^ gxtentry)
			{
				msclr::interop::marshal_context ctx;
				return NativeInvoke::Invoke< b8>(NATIVE_DOES_TEXT_LABEL_EXIST, ctx.marshal_as<const char*>(gxtentry));
			}
			static b8 HAS_ADDITIONAL_TEXT_LOADED(unsigned int textIndex) { return NativeInvoke::Invoke< b8>(NATIVE_HAS_ADDITIONAL_TEXT_LOADED, textIndex); }
			static b8 IS_BLIP_SHORT_RANGE(Blip blip) { return NativeInvoke::Invoke< b8>(NATIVE_IS_BLIP_SHORT_RANGE, blip); }
			static b8 IS_STRING_NULL(String^ str)
			{
				msclr::interop::marshal_context ctx;
				return NativeInvoke::Invoke< b8>(NATIVE_IS_STRING_NULL, ctx.marshal_as<const char*>(str));
			}
			static b8 IS_THIS_HELP_MESSAGE_BEING_DISPLAYED(String^ gxtentry)
			{ 
				msclr::interop::marshal_context ctx;
				return NativeInvoke::Invoke< b8>(NATIVE_IS_THIS_HELP_MESSAGE_BEING_DISPLAYED, ctx.marshal_as<const char*>(gxtentry));
			}
			static b8 IS_THIS_HELP_MESSAGE_WITH_NUMBER_BEING_DISPLAYED(String^ gxtentry, int number)
			{
				msclr::interop::marshal_context ctx;
				return NativeInvoke::Invoke< b8>(NATIVE_IS_THIS_HELP_MESSAGE_WITH_NUMBER_BEING_DISPLAYED, ctx.marshal_as<const char*>(gxtentry), number);
			}
			static b8 IS_THIS_HELP_MESSAGE_WITH_STRING_BEING_DISPLAYED(String^ gxtentry, String^ str) 
			{ 
				msclr::interop::marshal_context ctx;
				return NativeInvoke::Invoke< b8>(NATIVE_IS_THIS_HELP_MESSAGE_WITH_STRING_BEING_DISPLAYED, ctx.marshal_as<const char*>(gxtentry), ctx.marshal_as<const char*>(str));
			}
			static b8 ARE_WIDESCREEN_BORDERS_ACTIVE() { return NativeInvoke::Invoke< b8>(NATIVE_ARE_WIDESCREEN_BORDERS_ACTIVE); }
			static b8 GET_IS_HIDEF() { return NativeInvoke::Invoke< b8>(NATIVE_GET_IS_HIDEF); }
			static b8 GET_IS_WIDESCREEN() { return NativeInvoke::Invoke< b8>(NATIVE_GET_IS_WIDESCREEN); }
			static b8 CAN_THE_STAT_HAVE_STRING(int stat) { return NativeInvoke::Invoke< b8>(NATIVE_CAN_THE_STAT_HAVE_STRING, stat); }
			static b8 GET_STAT_FRONTEND_VISIBILITY(int stat) { return NativeInvoke::Invoke< b8>(NATIVE_GET_STAT_FRONTEND_VISIBILITY, stat); }
			static b8 IS_WORLD_POINT_WITHIN_BRAIN_ACTIVATION_RANGE() { return NativeInvoke::Invoke< b8>(NATIVE_IS_WORLD_POINT_WITHIN_BRAIN_ACTIVATION_RANGE); }
			static b8 CAN_PHONE_BE_SEEN_ON_SCREEN() { return NativeInvoke::Invoke< b8>(NATIVE_CAN_PHONE_BE_SEEN_ON_SCREEN); }
			static b8 CODE_WANTS_MOBILE_PHONE_REMOVED() { return NativeInvoke::Invoke< b8>(NATIVE_CODE_WANTS_MOBILE_PHONE_REMOVED); }
			static b8 CODE_WANTS_MOBILE_PHONE_REMOVED_FOR_WEAPON_SWITCHING() { return NativeInvoke::Invoke< b8>(NATIVE_CODE_WANTS_MOBILE_PHONE_REMOVED_FOR_WEAPON_SWITCHING); }
			static b8 GET_MOBILE_PHONE_TASK_SUB_TASK(Ped ped, [OutAttribute] int% Unk798)
			{
				int p;
				b8 r = NativeInvoke::Invoke< b8>(NATIVE_GET_MOBILE_PHONE_TASK_SUB_TASK, ped, &p);
				Unk798 = p;
				return r;
			}
			static b8 IS_MOBILE_PHONE_CALL_ONGOING() { return NativeInvoke::Invoke< b8>(NATIVE_IS_MOBILE_PHONE_CALL_ONGOING); }
			static b8 IS_MOBILE_PHONE_RADIO_ACTIVE() { return NativeInvoke::Invoke< b8>(NATIVE_IS_MOBILE_PHONE_RADIO_ACTIVE); }
			static b8 DOES_WEB_PAGE_EXIST(String^ webaddress) 
			{ 
				msclr::interop::marshal_context ctx;
				return NativeInvoke::Invoke< b8>(NATIVE_DOES_WEB_PAGE_EXIST, ctx.marshal_as<const char*>(webaddress));
			}
			static b8 GET_CLOSEST_CAR_NODE(float pX, float pY, float pZ, [OutAttribute] float% pResX, [OutAttribute] float% pResY, [OutAttribute] float% pResZ)
			{ 
				float x, y, z;
				b8 r = NativeInvoke::Invoke< b8>(NATIVE_GET_CLOSEST_CAR_NODE, pX, pY, pZ, &x, &y, &z); 
				pResX = x;
				pResY = y;
				pResZ = z;
				return r;
			}
			static b8 GET_CLOSEST_NETWORK_RESTART_NODE(Vector3 v, [OutAttribute] Vector3% ret, [OutAttribute] float% heading) 
			{ 
				Vector3 v2;
				float f;
				b8 r = NativeInvoke::Invoke< b8>(NATIVE_GET_CLOSEST_NETWORK_RESTART_NODE, v, &v2, &f);
				ret = v2;
				heading = f;
				return r;
			}
			static b8 GET_CLOSEST_CAR_NODE_FAVOUR_DIRECTION(int Unk802, float pX, float pY, float pZ, [OutAttribute] float% rX, [OutAttribute] float% rY, [OutAttribute] float% rZ, [OutAttribute] float% rHeading)
			{ 
				float x, y, z, h;
				b8 r = NativeInvoke::Invoke< b8>(NATIVE_GET_CLOSEST_CAR_NODE_FAVOUR_DIRECTION, Unk802, pX, pY, pZ, &x, &y, &z, &h); 
				rX = x;
				rY = y;
				rZ = z;
				rHeading = h;
				return r;
			}
			static b8 GET_CLOSEST_CAR_NODE_WITH_HEADING(float pX, float pY, float pZ, [OutAttribute] float% pResX, [OutAttribute] float% pResY, [OutAttribute] float% pResZ, [OutAttribute] float% pHeading)
			{ 
				float x, y, z, h;
				b8 r = NativeInvoke::Invoke< b8>(NATIVE_GET_CLOSEST_CAR_NODE_WITH_HEADING, pX, pY, pZ, &x, &y, &z, &h);
				pResX = x;
				pResY = y;
				pResZ = z;
				pHeading = h;
				return r;
			}
			static b8 GET_CLOSEST_MAJOR_CAR_NODE(float pX, float pY, float pZ, [OutAttribute] float% pResX, [OutAttribute] float% pResY, [OutAttribute] float% pResZ)
			{ 
				float x, y, z;
				b8 r = NativeInvoke::Invoke< b8>(NATIVE_GET_CLOSEST_MAJOR_CAR_NODE, pX, pY, pZ, &x, &y, &z); 
				pResX = x;
				pResY = y;
				pResZ = z;
				return r;
			}
			static b8 GET_CLOSEST_ROAD(float pX, float pY, float pZ, float Unk803, int Unk804, [OutAttribute] Vector3% Unk805, [OutAttribute] Vector3% Unk806, [OutAttribute] float% Unk807, [OutAttribute] float% Unk808, [OutAttribute] float% Unk809)
			{
				Vector3 ve, ve2;
				float x, y, z;
				b8 r = NativeInvoke::Invoke< b8>(NATIVE_GET_CLOSEST_ROAD, pX, pY, pZ, Unk803, Unk804, &ve, &ve2, &x, &y, &z); 
				Unk805 = ve;
				Unk806 = ve2;
				Unk807 = x;
				Unk808 = y;
				Unk809 = z;
				return r;
			}
			static b8 GET_NEXT_CLOSEST_CAR_NODE(float pX, float pY, float pZ, [OutAttribute] float% pRetX, [OutAttribute] float% pRetY, [OutAttribute] float% pRetZ)
			{ 
				float x, y, z;
				b8 r = NativeInvoke::Invoke< b8>(NATIVE_GET_NEXT_CLOSEST_CAR_NODE, pX, pY, pZ, &x, &y, &z); 
				pRetX = x;
				pRetY = y;
				pRetZ = z;
				return r;
			}
			static b8 GET_NEXT_CLOSEST_CAR_NODE_FAVOUR_DIRECTION(float pX, float pY, float pZ, [OutAttribute] float% pRetX, [OutAttribute] float% pRetY, [OutAttribute] float% pRetZ, [OutAttribute] float% pRetDirection)
			{ 
				float x, y, z, h;
				b8 r = NativeInvoke::Invoke< b8>(NATIVE_GET_NEXT_CLOSEST_CAR_NODE_FAVOUR_DIRECTION, pX, pY, pZ, &x, &y, &z, &h);
				pRetX = x;
				pRetY = y;
				pRetZ = z;
				pRetDirection = h;
				return r;
			}
			static b8 GET_NEXT_CLOSEST_CAR_NODE_WITH_HEADING(float pX, float pY, float pZ, [OutAttribute] float% pRetX, [OutAttribute] float% pRetY, [OutAttribute] float% pRetZ, [OutAttribute] float% pRetHeading)
			{ 
				float x, y, z, h;
				b8 r = NativeInvoke::Invoke< b8>(NATIVE_GET_NEXT_CLOSEST_CAR_NODE_WITH_HEADING, pX, pY, pZ, &x, &y, &z, &h); 
				pRetX = x;
				pRetY = y;
				pRetZ = z;
				pRetHeading = h;
				return r;
			}
			static b8 GET_NEXT_CLOSEST_CAR_NODE_WITH_HEADING_ON_ISLAND(float pX, float pY, float pZ, [OutAttribute] float% pRetX, [OutAttribute] float% pRetY, [OutAttribute] float% pRetZ, [OutAttribute] float% pRetHeading)
			{ 
				float x, y, z, h;
				b8 r = NativeInvoke::Invoke< b8>(NATIVE_GET_NEXT_CLOSEST_CAR_NODE_WITH_HEADING_ON_ISLAND, pX, pY, pZ, &x, &y, &z, &h); 
				pRetX = x;
				pRetY = y;
				pRetZ = z;
				pRetHeading = h;
				return r;
			}
			static b8 GET_NTH_CLOSEST_CAR_NODE(float pX, float pY, float pZ, int pN, [OutAttribute] float% pRetX, [OutAttribute] float% pRetY, [OutAttribute] float% pRetZ)
			{ 
				float x, y, z;
				b8 r = NativeInvoke::Invoke< b8>(NATIVE_GET_NTH_CLOSEST_CAR_NODE, pX, pY, pZ, pN, &x, &y, &z); 
				pRetX = x;
				pRetY = y;
				pRetZ = z;
				return r;
			}
			static b8 GET_NTH_CLOSEST_CAR_NODE_FAVOUR_DIRECTION(int Unk810, float pX, float pY, float pZ, int pN, [OutAttribute] float% pRetX, [OutAttribute] float% pRetY, [OutAttribute] float% pRetZ, [OutAttribute] float% pRetDirection)
			{
				float x, y, z, h;
				b8 r = NativeInvoke::Invoke< b8>(NATIVE_GET_NTH_CLOSEST_CAR_NODE_FAVOUR_DIRECTION, Unk810, pX, pY, pZ, pN, &x, &y, &z, &h);
				pRetX = x;
				pRetY = y;
				pRetZ = z;
				pRetDirection = h;
				return r;
			}
			static b8 GET_NTH_CLOSEST_CAR_NODE_WITH_HEADING(float pX, float pY, float pZ, unsigned int nodeNum, [OutAttribute] float% pResX, [OutAttribute] float% pResY, [OutAttribute] float% pResZ, [OutAttribute] float% pHeading)
			{
				float x, y, z, h;
				b8 r = NativeInvoke::Invoke< b8>(NATIVE_GET_NTH_CLOSEST_CAR_NODE_WITH_HEADING, pX, pY, pZ, nodeNum, &x, &y, &z, &h);
				pResX = x;
				pResY = y;
				pResZ = z;
				pHeading = h;
				return r;
			}
			static b8 GET_NTH_CLOSEST_CAR_NODE_WITH_HEADING_ON_ISLAND(float pX, float pY, float pZ, unsigned int pNodeNum, unsigned int pAreaId, [OutAttribute] float% pResX, [OutAttribute] float% pResY, [OutAttribute] float% pResZ, [OutAttribute] float% pHeading, [OutAttribute] unsigned int% pUnknownMaybeAreaId)
			{ 
				float x, y, z, h;
				unsigned int areaId;
				b8 r = NativeInvoke::Invoke< b8>(NATIVE_GET_NTH_CLOSEST_CAR_NODE_WITH_HEADING_ON_ISLAND, pX, pY, pZ, pNodeNum, pAreaId, &x, &y, &z, &h, &areaId);
				pResX = x;
				pResY = y;
				pResZ = z;
				pHeading = h;
				pUnknownMaybeAreaId = areaId;
				return r;
			}
			static b8 GET_RANDOM_CAR_NODE(float pX, float pY, float pZ, float pRadius, b8 flag0, b8 flag1, b8 flag2, [OutAttribute] float% pRetX, [OutAttribute] float% pRetY, [OutAttribute] float% pRetZ, [OutAttribute] float% pRetHeading)
			{ 
				float x, y, z, h;
				b8 r = NativeInvoke::Invoke< b8>(NATIVE_GET_RANDOM_CAR_NODE, pX, pY, pZ, pRadius, flag0, flag1, flag2, &x, &y, &z, &h); 
				pRetX = x;
				pRetY = y;
				pRetZ = z;
				pRetHeading = h;
				return r;
			}
			static b8 GET_RANDOM_CAR_NODE_INCLUDE_SWITCHED_OFF_NODES(float pX, float pY, float pZ, float pRadius, b8 flag0, b8 flag1, b8 flag2, [OutAttribute] float% pRetX, [OutAttribute] float% pRetY, [OutAttribute] float% pRetZ, [OutAttribute] float% pRetHeading)
			{
				float x, y, z, h;
				b8 r = NativeInvoke::Invoke< b8>(NATIVE_GET_RANDOM_CAR_NODE_INCLUDE_SWITCHED_OFF_NODES, pX, pY, pZ, pRadius, flag0, flag1, flag2, &x, &y, &z, &h);
				pRetX = x;
				pRetY = y;
				pRetZ = z;
				pRetHeading = h;
				return r;
			}
			static b8 GET_SAFE_POSITION_FOR_CHAR(float pX, float pY, float pZ, b8 unknownTrue, [OutAttribute] float% pSafeX, [OutAttribute] float% pSafeY, [OutAttribute] float% pSafeZ)
			{
				float x, y, z;
				b8 r = NativeInvoke::Invoke< b8>(NATIVE_GET_SAFE_POSITION_FOR_CHAR, pX, pY, pZ, unknownTrue, &x, &y, &z);
				pSafeX = x;
				pSafeY = y;
				pSafeZ = z;
				return r;
			}
			static b8 GET_ASCII_PRESSED(int key, [OutAttribute] int% Unk820)
			{
				int p;
				b8 r = NativeInvoke::Invoke< b8>(NATIVE_GET_ASCII_PRESSED, key, &p);
				Unk820 = p;
				return r;
			}
			static b8 GET_BUFFERED_ASCII(int key, [OutAttribute] int% Unk821)
			{
				int p;
				b8 r = NativeInvoke::Invoke< b8>(NATIVE_GET_BUFFERED_ASCII, key, &p);
				Unk821 = p;
				return r;
			}
			static b8 GET_PAD_PITCH_ROLL(unsigned int padIndex, [OutAttribute] float% pPitch, [OutAttribute] float% pRoll)
			{
				float p1, p2;
				b8 r = NativeInvoke::Invoke< b8>(NATIVE_GET_PAD_PITCH_ROLL, padIndex, &p1, &p2);
				pPitch = p1;
				pRoll = p2;
				return r;
			}
			static b8 HAS_RELOADED_WITH_MOTION_CONTROL(int ukn0, [OutAttribute] b8% ukn)
			{
				b8 p1;
				b8 r = NativeInvoke::Invoke< b8>(NATIVE_HAS_RELOADED_WITH_MOTION_CONTROL, ukn0, &p1);
				ukn = p1;
				return r;
			}
			static b8 IS_BUTTON_JUST_PRESSED(unsigned int padIndex, unsigned int button) { return NativeInvoke::Invoke< b8>(NATIVE_IS_BUTTON_JUST_PRESSED, padIndex, button); }
			static b8 IS_BUTTON_PRESSED(unsigned int padIndex, unsigned int button) { return NativeInvoke::Invoke< b8>(NATIVE_IS_BUTTON_PRESSED, padIndex, button); }
			static b8 IS_CONTROL_JUST_PRESSED(int Unk822, int controlid) { return NativeInvoke::Invoke< b8>(NATIVE_IS_CONTROL_JUST_PRESSED, Unk822, controlid); }
			static b8 IS_CONTROL_PRESSED(int Unk823, int controlid) { return NativeInvoke::Invoke< b8>(NATIVE_IS_CONTROL_PRESSED, Unk823, controlid); }
			static b8 IS_GAME_KEYBOARD_KEY_JUST_PRESSED(int key) { return NativeInvoke::Invoke< b8>(NATIVE_IS_GAME_KEYBOARD_KEY_JUST_PRESSED, key); }
			static b8 IS_GAME_KEYBOARD_KEY_PRESSED(int key) { return NativeInvoke::Invoke< b8>(NATIVE_IS_GAME_KEYBOARD_KEY_PRESSED, key); }
			static b8 IS_GAME_KEYBOARD_NAV_DOWN_PRESSED(b8 Unk824) { return NativeInvoke::Invoke< b8>(NATIVE_IS_GAME_KEYBOARD_NAV_DOWN_PRESSED, Unk824); }
			static b8 IS_GAME_KEYBOARD_NAV_LEFT_PRESSED(b8 Unk825) { return NativeInvoke::Invoke< b8>(NATIVE_IS_GAME_KEYBOARD_NAV_LEFT_PRESSED, Unk825); }
			static b8 IS_GAME_KEYBOARD_NAV_RIGHT_PRESSED(b8 Unk826) { return NativeInvoke::Invoke< b8>(NATIVE_IS_GAME_KEYBOARD_NAV_RIGHT_PRESSED, Unk826); }
			static b8 IS_GAME_KEYBOARD_NAV_UP_PRESSED(b8 Unk827) { return NativeInvoke::Invoke< b8>(NATIVE_IS_GAME_KEYBOARD_NAV_UP_PRESSED, Unk827); }
			static b8 IS_IN_CAR_FIRE_BUTTON_PRESSED() { return NativeInvoke::Invoke< b8>(NATIVE_IS_IN_CAR_FIRE_BUTTON_PRESSED); }
			static b8 IS_KEYBOARD_KEY_JUST_PRESSED(int key) { return NativeInvoke::Invoke< b8>(NATIVE_IS_KEYBOARD_KEY_JUST_PRESSED, key); }
			static b8 IS_KEYBOARD_KEY_PRESSED(int key) { return NativeInvoke::Invoke< b8>(NATIVE_IS_KEYBOARD_KEY_PRESSED, key); }
			static b8 IS_MOUSE_BUTTON_JUST_PRESSED(int Unk828) { return NativeInvoke::Invoke< b8>(NATIVE_IS_MOUSE_BUTTON_JUST_PRESSED, Unk828); }
			static b8 IS_MOUSE_BUTTON_PRESSED(int Unk829) { return NativeInvoke::Invoke< b8>(NATIVE_IS_MOUSE_BUTTON_PRESSED, Unk829); }
			static b8 IS_MOUSE_USING_VERTICAL_INVERSION() { return NativeInvoke::Invoke< b8>(NATIVE_IS_MOUSE_USING_VERTICAL_INVERSION); }
			static b8 IS_NUMLOCK_ENABLED() { return NativeInvoke::Invoke< b8>(NATIVE_IS_NUMLOCK_ENABLED); }
			static b8 IS_PC_USING_JOYPAD() { return NativeInvoke::Invoke< b8>(NATIVE_IS_PC_USING_JOYPAD); }
			static b8 IS_USING_CONTROLLER() { return NativeInvoke::Invoke< b8>(NATIVE_IS_USING_CONTROLLER); }
			static b8 USING_STANDARD_CONTROLS() { return NativeInvoke::Invoke< b8>(NATIVE_USING_STANDARD_CONTROLS); }
			static b8 DOES_SCRIPT_FIRE_EXIST(int fire) { return NativeInvoke::Invoke< b8>(NATIVE_DOES_SCRIPT_FIRE_EXIST, fire); }
			static b8 IS_EXPLOSION_IN_AREA(int expnum, float x0, float y0, float z0, float x1, float y1, float z1) { return NativeInvoke::Invoke< b8>(NATIVE_IS_EXPLOSION_IN_AREA, expnum, x0, y0, z0, x1, y1, z1); }
			static b8 IS_EXPLOSION_IN_SPHERE(int expnum, float x, float y, float z, float radius) { return NativeInvoke::Invoke< b8>(NATIVE_IS_EXPLOSION_IN_SPHERE, expnum, x, y, z, radius); }
			static b8 IS_SCRIPT_FIRE_EXTINGUISHED(FireId fire) { return NativeInvoke::Invoke< b8>(NATIVE_IS_SCRIPT_FIRE_EXTINGUISHED, fire); }
			static b8 DOES_DECISION_MAKER_EXIST(DecisionMaker dm) { return NativeInvoke::Invoke< b8>(NATIVE_DOES_DECISION_MAKER_EXIST, dm); }
			static b8 IS_CHAR_IN_ZONE(Ped ped, String^ zonename)
			{
				msclr::interop::marshal_context ctx;
				return NativeInvoke::Invoke< b8>(NATIVE_IS_CHAR_IN_ZONE, ped, ctx.marshal_as<const char*>(zonename));
			}
			static b8 GET_WATER_HEIGHT(float x, float y, float z, [OutAttribute] float% pheight)
			{
				float p;
				b8 r = NativeInvoke::Invoke< b8>(NATIVE_GET_WATER_HEIGHT, x, y, z, &p);
				pheight = p;
				return r;
			}
			static b8 GET_WATER_HEIGHT_NO_WAVES(float x, float y, float z, [OutAttribute] float% height)
			{ 
				float p;
				b8 r = NativeInvoke::Invoke< b8>(NATIVE_GET_WATER_HEIGHT_NO_WAVES, x, y, z, &p); 
				height = p;
				return r;
			}
			static b8 SYNCH_RECORDING_WITH_WATER() { return NativeInvoke::Invoke< b8>(NATIVE_SYNCH_RECORDING_WITH_WATER); }
			static b8 IS_NETWORK_PLAYER_ACTIVE(int playerIndex) { return NativeInvoke::Invoke< b8>(NATIVE_IS_NETWORK_PLAYER_ACTIVE, playerIndex); }
			static b8 CAN_REGISTER_MISSION_OBJECT() { return NativeInvoke::Invoke< b8>(NATIVE_CAN_REGISTER_MISSION_OBJECT); }
			static b8 CAN_REGISTER_MISSION_PED() { return NativeInvoke::Invoke< b8>(NATIVE_CAN_REGISTER_MISSION_PED); }
			static b8 CAN_REGISTER_MISSION_VEHICLE() { return NativeInvoke::Invoke< b8>(NATIVE_CAN_REGISTER_MISSION_VEHICLE); }
			static b8 DOES_GAME_CODE_WANT_TO_LEAVE_NETWORK_SESSION() { return NativeInvoke::Invoke< b8>(NATIVE_DOES_GAME_CODE_WANT_TO_LEAVE_NETWORK_SESSION); }
			static b8 DOES_OBJECT_EXIST_WITH_NETWORK_ID(int netid) { return NativeInvoke::Invoke< b8>(NATIVE_DOES_OBJECT_EXIST_WITH_NETWORK_ID, netid); }
			static b8 DOES_PED_EXIST_WITH_NETWORK_ID(int netid) { return NativeInvoke::Invoke< b8>(NATIVE_DOES_PED_EXIST_WITH_NETWORK_ID, netid); }
			static b8 DOES_PLAYER_HAVE_CONTROL_OF_NETWORK_ID(int player, int id) { return NativeInvoke::Invoke< b8>(NATIVE_DOES_PLAYER_HAVE_CONTROL_OF_NETWORK_ID, player, id); }
			static b8 DOES_VEHICLE_EXIST_WITH_NETWORK_ID(int nedid) { return NativeInvoke::Invoke< b8>(NATIVE_DOES_VEHICLE_EXIST_WITH_NETWORK_ID, nedid); }
			static b8 GET_CELLPHONE_RANKED() { return NativeInvoke::Invoke< b8>(NATIVE_GET_CELLPHONE_RANKED); }
			static b8 GET_FILTER_MENU_ON() { return NativeInvoke::Invoke< b8>(NATIVE_GET_FILTER_MENU_ON); }
			static Blip GET_FIRST_BLIP_INFO_ID(int type) { return NativeInvoke::Invoke< Blip>(NATIVE_GET_FIRST_BLIP_INFO_ID, type); }
			static b8 GET_GFWL_IS_RETURNING_TO_SINGLE_PLAYER() { return NativeInvoke::Invoke< b8>(NATIVE_GET_GFWL_IS_RETURNING_TO_SINGLE_PLAYER); }
			static b8 GET_HOST_MATCH_ON() { return NativeInvoke::Invoke< b8>(NATIVE_GET_HOST_MATCH_ON); }
			static b8 GET_NETWORK_JOIN_FAIL() { return NativeInvoke::Invoke< b8>(NATIVE_GET_NETWORK_JOIN_FAIL); }
			static b8 GET_RETURN_TO_FILTER_MENU() { return NativeInvoke::Invoke< b8>(NATIVE_GET_RETURN_TO_FILTER_MENU); }
			static b8 HAS_CONTROL_OF_NETWORK_ID(int netid) { return NativeInvoke::Invoke< b8>(NATIVE_HAS_CONTROL_OF_NETWORK_ID, netid); }
			static b8 HAS_GAMER_CHANGED_NETWORK_MODEL_SETTINGS() { return NativeInvoke::Invoke< b8>(NATIVE_HAS_GAMER_CHANGED_NETWORK_MODEL_SETTINGS); }
			static b8 HAS_NETWORK_PLAYER_LEFT_GAME(Player playerIndex) { return NativeInvoke::Invoke< b8>(NATIVE_HAS_NETWORK_PLAYER_LEFT_GAME, playerIndex); }
			static b8 IS_DAMAGE_TRACKER_ACTIVE_ON_NETWORK_ID(ScriptAny Unk882) { return NativeInvoke::Invoke< b8>(NATIVE_IS_DAMAGE_TRACKER_ACTIVE_ON_NETWORK_ID, Unk882); }
			static b8 IS_NETWORK_GAME_PENDING() { return NativeInvoke::Invoke< b8>(NATIVE_IS_NETWORK_GAME_PENDING); }
			static b8 IS_NETWORK_GAME_RUNNING() { return NativeInvoke::Invoke< b8>(NATIVE_IS_NETWORK_GAME_RUNNING); }
			static b8 IS_NETWORK_SESSION() { return NativeInvoke::Invoke< b8>(NATIVE_IS_NETWORK_SESSION); }
			static b8 IS_OBJECT_REASSIGNMENT_IN_PROGRESS() { return NativeInvoke::Invoke< b8>(NATIVE_IS_OBJECT_REASSIGNMENT_IN_PROGRESS); }
			static b8 IS_OUR_PLAYER_HIGHER_PRIORITY_FOR_CAR_GENERATION(Player playerIndex) { return NativeInvoke::Invoke< b8>(NATIVE_IS_OUR_PLAYER_HIGHER_PRIORITY_FOR_CAR_GENERATION, playerIndex); }
			static b8 IS_PARTY_MODE() { return NativeInvoke::Invoke< b8>(NATIVE_IS_PARTY_MODE); }
			static b8 IS_THIS_MACHINE_THE_SERVER() { return NativeInvoke::Invoke< b8>(NATIVE_IS_THIS_MACHINE_THE_SERVER); }
			static b8 LOCAL_PLAYER_IS_READY_TO_START_PLAYING() { return NativeInvoke::Invoke< b8>(NATIVE_LOCAL_PLAYER_IS_READY_TO_START_PLAYING); }
			static b8 NETWORK_ALL_PARTY_MEMBERS_PRESENT() { return NativeInvoke::Invoke< b8>(NATIVE_NETWORK_ALL_PARTY_MEMBERS_PRESENT); }
			static b8 NETWORK_AM_I_BLOCKED_BY_PLAYER(Player playerIndex) { return NativeInvoke::Invoke< b8>(NATIVE_NETWORK_AM_I_BLOCKED_BY_PLAYER, playerIndex); }
			static b8 NETWORK_AM_I_MUTED_BY_PLAYER(Player playerIndex) { return NativeInvoke::Invoke< b8>(NATIVE_NETWORK_AM_I_MUTED_BY_PLAYER, playerIndex); }
			static b8 NETWORK_CHANGE_GAME_MODE_PENDING() { return NativeInvoke::Invoke< b8>(NATIVE_NETWORK_CHANGE_GAME_MODE_PENDING); }
			static b8 NETWORK_CHANGE_GAME_MODE_SUCCEEDED() { return NativeInvoke::Invoke< b8>(NATIVE_NETWORK_CHANGE_GAME_MODE_SUCCEEDED); }
			static b8 NETWORK_CHECK_INVITE_ARRIVAL() { return NativeInvoke::Invoke< b8>(NATIVE_NETWORK_CHECK_INVITE_ARRIVAL); }
			static b8 NETWORK_DID_INVITE_FRIEND(String^ FRIENDNAME)
			{
				msclr::interop::marshal_context ctx;
				return NativeInvoke::Invoke< b8>(NATIVE_NETWORK_DID_INVITE_FRIEND, ctx.marshal_as<const char*>(FRIENDNAME));
			}
			static b8 NETWORK_END_SESSION_PENDING() { return NativeInvoke::Invoke< b8>(NATIVE_NETWORK_END_SESSION_PENDING); }
			static b8 NETWORK_FIND_GAME_PENDING() { return NativeInvoke::Invoke< b8>(NATIVE_NETWORK_FIND_GAME_PENDING); }
			static b8 NETWORK_GET_LAN_SESSION() { return NativeInvoke::Invoke< b8>(NATIVE_NETWORK_GET_LAN_SESSION); }
			static b8 NETWORK_HAS_STRICT_NAT() { return NativeInvoke::Invoke< b8>(NATIVE_NETWORK_HAS_STRICT_NAT); }
			static b8 NETWORK_HAVE_ACCEPTED_INVITE() { return NativeInvoke::Invoke< b8>(NATIVE_NETWORK_HAVE_ACCEPTED_INVITE); }
			static b8 NETWORK_HAVE_ONLINE_PRIVILEGES() { return NativeInvoke::Invoke< b8>(NATIVE_NETWORK_HAVE_ONLINE_PRIVILEGES); }
			static b8 NETWORK_HAVE_SUMMONS() { return NativeInvoke::Invoke< b8>(NATIVE_NETWORK_HAVE_SUMMONS); }
			static b8 NETWORK_HOST_GAME_PENDING() { return NativeInvoke::Invoke< b8>(NATIVE_NETWORK_HOST_GAME_PENDING); }
			static b8 NETWORK_HOST_GAME_SUCCEEDED() { return NativeInvoke::Invoke< b8>(NATIVE_NETWORK_HOST_GAME_SUCCEEDED); }
			static b8 NETWORK_IS_BEING_KICKED() { return NativeInvoke::Invoke< b8>(NATIVE_NETWORK_IS_BEING_KICKED); }
			static b8 NETWORK_IS_COMMON_EPISODE(int id) { return NativeInvoke::Invoke< b8>(NATIVE_NETWORK_IS_COMMON_EPISODE, id); }
			static b8 NETWORK_IS_FIND_RESULT_UPDATED(int ukn0) { return NativeInvoke::Invoke< b8>(NATIVE_NETWORK_IS_FIND_RESULT_UPDATED, ukn0); }
			static b8 NETWORK_IS_FIND_RESULT_VALID(int Unk883) { return NativeInvoke::Invoke< b8>(NATIVE_NETWORK_IS_FIND_RESULT_VALID, Unk883); }
			static b8 NETWORK_IS_FRIEND_IN_SAME_TITLE(unsigned int friendid) { return NativeInvoke::Invoke< b8>(NATIVE_NETWORK_IS_FRIEND_IN_SAME_TITLE, friendid); }
			static b8 NETWORK_IS_GAME_RANKED() { return NativeInvoke::Invoke< b8>(NATIVE_NETWORK_IS_GAME_RANKED); }
			static b8 NETWORK_IS_INVITEE_ONLINE() { return NativeInvoke::Invoke< b8>(NATIVE_NETWORK_IS_INVITEE_ONLINE); }
			static b8 NETWORK_IS_NETWORK_AVAILABLE() { return NativeInvoke::Invoke< b8>(NATIVE_NETWORK_IS_NETWORK_AVAILABLE); }
			static b8 NETWORK_IS_OPERATION_PENDING() { return NativeInvoke::Invoke< b8>(NATIVE_NETWORK_IS_OPERATION_PENDING); }
			static b8 NETWORK_IS_PLAYER_BLOCKED_BY_ME(Player playerIndex) { return NativeInvoke::Invoke< b8>(NATIVE_NETWORK_IS_PLAYER_BLOCKED_BY_ME, playerIndex); }
			static b8 NETWORK_IS_PLAYER_MUTED_BY_ME(Player playerIndex) { return NativeInvoke::Invoke< b8>(NATIVE_NETWORK_IS_PLAYER_MUTED_BY_ME, playerIndex); }
			static b8 NETWORK_IS_PLAYER_TALKING(Player playerIndex) { return NativeInvoke::Invoke< b8>(NATIVE_NETWORK_IS_PLAYER_TALKING, playerIndex); }
			static b8 NETWORK_IS_PLAYER_TYPING(Player playerIndex) { return NativeInvoke::Invoke< b8>(NATIVE_NETWORK_IS_PLAYER_TYPING, playerIndex); }
			static b8 NETWORK_IS_RENDEZVOUS() { return NativeInvoke::Invoke< b8>(NATIVE_NETWORK_IS_RENDEZVOUS); }
			static b8 NETWORK_IS_RENDEZVOUS_HOST() { return NativeInvoke::Invoke< b8>(NATIVE_NETWORK_IS_RENDEZVOUS_HOST); }
			static b8 NETWORK_IS_ROCKSTART_SESSION_ID_VALID() { return NativeInvoke::Invoke< b8>(NATIVE_NETWORK_IS_ROCKSTART_SESSION_ID_VALID); }
			//static b8 NETWORK_IS_SESSION_ADVERTISED() { return NativeInvoke::Invoke< b8>(NATIVE_NETWORK_IS_SESSION_ADVERTISED); }
			static b8 NETWORK_IS_SESSION_ADVERTISE() { return NativeInvoke::Invoke< b8>(NATIVE_NETWORK_IS_SESSION_ADVERTISE); }
			static b8 NETWORK_IS_SESSION_INVITABLE() { return NativeInvoke::Invoke< b8>(NATIVE_NETWORK_IS_SESSION_INVITABLE); }
			static b8 NETWORK_IS_SESSION_STARTED() { return NativeInvoke::Invoke< b8>(NATIVE_NETWORK_IS_SESSION_STARTED); }
			static b8 NETWORK_IS_TVT() { return NativeInvoke::Invoke< b8>(NATIVE_NETWORK_IS_TVT); }
			static b8 NETWORK_JOIN_GAME_PENDING() { return NativeInvoke::Invoke< b8>(NATIVE_NETWORK_JOIN_GAME_PENDING); }
			static b8 NETWORK_JOIN_GAME_SUCCEEDED() { return NativeInvoke::Invoke< b8>(NATIVE_NETWORK_JOIN_GAME_SUCCEEDED); }
			static b8 NETWORK_JOIN_SUMMONS() { return NativeInvoke::Invoke< b8>(NATIVE_NETWORK_JOIN_SUMMONS); }
			static b8 NETWORK_LEAVE_GAME_PENDING() { return NativeInvoke::Invoke< b8>(NATIVE_NETWORK_LEAVE_GAME_PENDING); }
			static b8 NETWORK_PLAYER_HAS_COMM_PRIVS() { return NativeInvoke::Invoke< b8>(NATIVE_NETWORK_PLAYER_HAS_COMM_PRIVS); }
			static b8 NETWORK_PLAYER_HAS_DIED_RECENTLY(Player playerIndex) { return NativeInvoke::Invoke< b8>(NATIVE_NETWORK_PLAYER_HAS_DIED_RECENTLY, playerIndex); }
			static b8 NETWORK_PLAYER_HAS_HEADSET(ScriptAny Unk884) { return NativeInvoke::Invoke< b8>(NATIVE_NETWORK_PLAYER_HAS_HEADSET, Unk884); }
			static b8 NETWORK_PLAYER_HAS_KEYBOARD(Player playerIndex) { return NativeInvoke::Invoke< b8>(NATIVE_NETWORK_PLAYER_HAS_KEYBOARD, playerIndex); }
			static b8 NETWORK_RESULT_MATCHES_SEARCH_CRITERIA(int result) { return NativeInvoke::Invoke< b8>(NATIVE_NETWORK_RESULT_MATCHES_SEARCH_CRITERIA, result); }
			static b8 NETWORK_RETURN_TO_RENDEZVOUS() { return NativeInvoke::Invoke< b8>(NATIVE_NETWORK_RETURN_TO_RENDEZVOUS); }
			static b8 NETWORK_RETURN_TO_RENDEZVOUS_PENDING() { return NativeInvoke::Invoke< b8>(NATIVE_NETWORK_RETURN_TO_RENDEZVOUS_PENDING); }
			static b8 NETWORK_RETURN_TO_RENDEZVOUS_SUCCEEDED() { return NativeInvoke::Invoke< b8>(NATIVE_NETWORK_RETURN_TO_RENDEZVOUS_SUCCEEDED); }
			static b8 NETWORK_START_SESSION_PENDING() { return NativeInvoke::Invoke< b8>(NATIVE_NETWORK_START_SESSION_PENDING); }
			static b8 NETWORK_START_SESSION_SUCCEEDED() { return NativeInvoke::Invoke< b8>(NATIVE_NETWORK_START_SESSION_SUCCEEDED); }
			static b8 NETWORK_STRING_VERIFY_PENDING() { return NativeInvoke::Invoke< b8>(NATIVE_NETWORK_STRING_VERIFY_PENDING); }
			static b8 NETWORK_STRING_VERIFY_SUCCEEDED() { return NativeInvoke::Invoke< b8>(NATIVE_NETWORK_STRING_VERIFY_SUCCEEDED); }
			static b8 PLAYER_WANTS_TO_JOIN_NETWORK_GAME(int Unk885) { return NativeInvoke::Invoke< b8>(NATIVE_PLAYER_WANTS_TO_JOIN_NETWORK_GAME, Unk885); }
			static b8 REQUEST_CONTROL_OF_NETWORK_ID(int netid) { return NativeInvoke::Invoke< b8>(NATIVE_REQUEST_CONTROL_OF_NETWORK_ID, netid); }
			static b8 NETWORK_INVITE_FRIEND(String^ friendname)
			{
				msclr::interop::marshal_context ctx;
				return NativeInvoke::Invoke< b8>(NATIVE_NETWORK_INVITE_FRIEND, (char*)ctx.marshal_as<const char*>(friendname));
			}
			static b8 NETWORK_SET_PLAYER_MUTED(int playerIndex, b8 value) { return NativeInvoke::Invoke< b8>(NATIVE_NETWORK_SET_PLAYER_MUTED, playerIndex, value); }
			static b8 TRIGGER_PTFX(String^ name, float x, float y, float z, float Unk1062, float Unk1063, float Unk1064, unsigned int flags) 
			{ 
				msclr::interop::marshal_context ctx;
				return NativeInvoke::Invoke< b8>(NATIVE_TRIGGER_PTFX, ctx.marshal_as<const char*>(name), x, y, z, Unk1062, Unk1063, Unk1064, flags);
			}
			static b8 TRIGGER_PTFX_ON_OBJ(String^ name, Entity obj, float x, float y, float z, float Unk1065, float Unk1066, float Unk1067, unsigned int flags) 
			{ 
				msclr::interop::marshal_context ctx;
				return NativeInvoke::Invoke< b8>(NATIVE_TRIGGER_PTFX_ON_OBJ, ctx.marshal_as<const char*>(name), obj, x, y, z, Unk1065, Unk1066, Unk1067, flags);
			}
			static b8 TRIGGER_PTFX_ON_OBJ_BONE(String^ name, Entity obj, float x, float y, float z, float Unk1068, float Unk1069, float Unk1070, int objbone, unsigned int flags) 
			{ 
				msclr::interop::marshal_context ctx;
				return NativeInvoke::Invoke< b8>(NATIVE_TRIGGER_PTFX_ON_OBJ_BONE, ctx.marshal_as<const char*>(name), obj, x, y, z, Unk1068, Unk1069, Unk1070, objbone, flags);
			}
			static b8 TRIGGER_PTFX_ON_PED(String^ name, Ped ped, float x, float y, float z, float Unk1071, float Unk1072, float Unk1073, unsigned int flags)
			{
				msclr::interop::marshal_context ctx;
				return NativeInvoke::Invoke< b8>(NATIVE_TRIGGER_PTFX_ON_PED, ctx.marshal_as<const char*>(name), ped, x, y, z, Unk1071, Unk1072, Unk1073, flags);
			}
			static b8 TRIGGER_PTFX_ON_PED_BONE(String^ name, Ped ped, float x, float y, float z, float Unk1074, float Unk1075, float Unk1076, int pedbone, unsigned int flags)
			{
				msclr::interop::marshal_context ctx;
				return NativeInvoke::Invoke< b8>(NATIVE_TRIGGER_PTFX_ON_PED_BONE, ctx.marshal_as<const char*>(name), ped, x, y, z, Unk1074, Unk1075, Unk1076, pedbone, flags);
			}
			static b8 TRIGGER_PTFX_ON_VEH(String^ name, Vehicle veh, float x, float y, float z, float Unk1077, float Unk1078, float Unk1079, float Unk1080)
			{
				msclr::interop::marshal_context ctx;
				return NativeInvoke::Invoke< b8>(NATIVE_TRIGGER_PTFX_ON_VEH, ctx.marshal_as<const char*>(name), veh, x, y, z, Unk1077, Unk1078, Unk1079, Unk1080);
			}
			static b8 ALLOW_ONE_TIME_ONLY_COMMANDS_TO_RUN() { return NativeInvoke::Invoke< b8>(NATIVE_ALLOW_ONE_TIME_ONLY_COMMANDS_TO_RUN); }
			static b8 GET_TEXT_INPUT_ACTIVE() { return NativeInvoke::Invoke< b8>(NATIVE_GET_TEXT_INPUT_ACTIVE); }
			static b8 DOES_PICKUP_EXIST(Pickup pickup) { return NativeInvoke::Invoke< b8>(NATIVE_DOES_PICKUP_EXIST, pickup); }
			static b8 HAS_PICKUP_BEEN_COLLECTED(Pickup pickup) { return NativeInvoke::Invoke< b8>(NATIVE_HAS_PICKUP_BEEN_COLLECTED, pickup); }
			static b8 IS_ANY_PICKUP_AT_COORDS(float x, float y, float z) { return NativeInvoke::Invoke< b8>(NATIVE_IS_ANY_PICKUP_AT_COORDS, x, y, z); }
			static b8 IS_MONEY_PICKUP_AT_COORDS(float x, float y, float z) { return NativeInvoke::Invoke< b8>(NATIVE_IS_MONEY_PICKUP_AT_COORDS, x, y, z); }
			static b8 DOES_WIDGET_GROUP_EXIST(ScriptAny Unk1114) { return NativeInvoke::Invoke< b8>(NATIVE_DOES_WIDGET_GROUP_EXIST, Unk1114); }
			static b8 IS_DEBUG_CAMERA_ON() { return NativeInvoke::Invoke< b8>(NATIVE_IS_DEBUG_CAMERA_ON); }
			static int ROUND(float value) { return NativeInvoke::Invoke<int>(NATIVE_ROUND, value); }
			static String^ GET_PLAYER_NAME(Player playerIndex)
			{
				return gcnew String(NativeInvoke::Invoke<const ch*>(NATIVE_GET_PLAYER_NAME, playerIndex));
			}
			static String^ NETWORK_GET_NEXT_TEXT_CHAT()
			{
				return gcnew String(NativeInvoke::Invoke< const ch*>(NATIVE_NETWORK_GET_NEXT_TEXT_CHAT));
			}
			static uint32_t GET_PLAYER_ID() { return NativeInvoke::Invoke<uint32_t>(NATIVE_GET_PLAYER_ID); }
			static uint32_t GET_HOST_ID() { return NativeInvoke::Invoke<uint32_t>(NATIVE_GET_HOST_ID); }
			static Player CONVERT_INT_TO_PLAYERINDEX(uint32_t playerId) { return NativeInvoke::Invoke< Player>(NATIVE_CONVERT_INT_TO_PLAYERINDEX, playerId); }
			static int GET_HASH_KEY(String^ value)
			{
				msclr::interop::marshal_context ctx;
				return NativeInvoke::Invoke<ScriptAny>(NATIVE_GET_HASH_KEY, ctx.marshal_as<const char*>(value));
			}
			static float COS(float value) { return NativeInvoke::Invoke< float>(NATIVE_COS, value); }
			static float SIN(float value) { return NativeInvoke::Invoke< float>(NATIVE_SIN, value); }
			static uint32_t START_NEW_SCRIPT(String^ scriptName, unsigned int stacksize)
			{
				msclr::interop::marshal_context ctx;
				return NativeInvoke::Invoke<uint32_t>(NATIVE_START_NEW_SCRIPT, ctx.marshal_as<const char*>(scriptName), stacksize);
			}
			static uint32_t START_PTFX_ON_OBJ(String^ name, Entity obj, float x, float y, float z, float yaw, float pitch, float roll, float scale)
			{
				msclr::interop::marshal_context ctx;
				return NativeInvoke::Invoke<uint32_t>(NATIVE_START_PTFX_ON_OBJ, ctx.marshal_as<const char*>(name), obj, x, y, z, yaw, pitch, roll, scale);
			}

			static void DISABLE_LOCAL_PLAYER_PICKUPS(b8 b1) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_DISABLE_LOCAL_PLAYER_PICKUPS, b1); }
			static void LOOP_RACE_TRACK(b8 b1) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_LOOP_RACE_TRACK, b1); }
			static void SET_BLOCK_CAMERA_TOGGLE(b8 b1) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_BLOCK_CAMERA_TOGGLE, b1); }
			static void SET_FOV_CHANNEL_SCRIPT(b8 b1) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_FOV_CHANNEL_SCRIPT, b1); }
			static void SET_TIME_CYCLE_FAR_CLIP_DISABLED(b8 b1) { NativeInvoke::Invoke< ScriptVoid>(NATIVE_SET_TIME_CYCLE_FAR_CLIP_DISABLED, b1); }

			static b8 GET_IS_AUTOSAVE_OFF() { return NativeInvoke::Invoke< b8>(NATIVE_GET_IS_AUTOSAVE_OFF); }
			static b8 GET_IS_DISPLAYINGSAVEMESSAGE() { return NativeInvoke::Invoke< b8>(NATIVE_GET_IS_DISPLAYINGSAVEMESSAGE); }
			static b8 IS_EPISODIC_DISC_BUILD() { return NativeInvoke::Invoke< b8>(NATIVE_IS_EPISODIC_DISC_BUILD); }
			static b8 IS_LCPD_DATA_VALID() { return NativeInvoke::Invoke< b8>(NATIVE_IS_LCPD_DATA_VALID); }
			static b8 SPOT_CHECK5() { return NativeInvoke::Invoke< b8>(NATIVE_SPOT_CHECK5); }
			static b8 SPOT_CHECK6() { return NativeInvoke::Invoke< b8>(NATIVE_SPOT_CHECK6); }
			static b8 SPOT_CHECK7() { return NativeInvoke::Invoke< b8>(NATIVE_SPOT_CHECK7); }
			static b8 SPOT_CHECK8() { return NativeInvoke::Invoke< b8>(NATIVE_SPOT_CHECK8); }

			static uint32_t GET_PLAYER_TEAM(int player) { return NativeInvoke::Invoke<uint32_t>(NATIVE_GET_PLAYER_TEAM, player); }
			static uint32_t COUNT_SCRIPT_CAMS() { return NativeInvoke::Invoke<uint32_t>(NATIVE_COUNT_SCRIPT_CAMS); }
			static uint32_t FIND_MAX_NUMBER_OF_GROUP_MEMBERS() { return NativeInvoke::Invoke<uint32_t>(NATIVE_FIND_MAX_NUMBER_OF_GROUP_MEMBERS); }
			static uint32_t GET_ACCEPT_BUTTON() { return NativeInvoke::Invoke<uint32_t>(NATIVE_GET_ACCEPT_BUTTON); }
			static uint32_t GET_AUDIO_ROOM_ID() { return NativeInvoke::Invoke<uint32_t>(NATIVE_GET_AUDIO_ROOM_ID); }
			static uint32_t GET_CONSOLE_COMMAND_TOKEN() { return NativeInvoke::Invoke<uint32_t>(NATIVE_GET_CONSOLE_COMMAND_TOKEN); }
			static uint32_t GET_CURRENT_DAY_OF_WEEK() { return NativeInvoke::Invoke<uint32_t>(NATIVE_GET_CURRENT_DAY_OF_WEEK); }
			static uint32_t GET_CURRENT_EPISODE() { return NativeInvoke::Invoke<uint32_t>(NATIVE_GET_CURRENT_EPISODE); }
			static uint32_t GET_CURRENT_LANGUAGE() { return NativeInvoke::Invoke<uint32_t>(NATIVE_GET_CURRENT_LANGUAGE); }
			static uint32_t GET_CURRENT_POPULATION_ZONE_TYPE() { return NativeInvoke::Invoke<uint32_t>(NATIVE_GET_CURRENT_POPULATION_ZONE_TYPE); }
			static uint32_t GET_CURRENT_SCRIPTED_CONVERSATION_LINE() { return NativeInvoke::Invoke<uint32_t>(NATIVE_GET_CURRENT_SCRIPTED_CONVERSATION_LINE); }
			static uint32_t GET_CURRENT_STACK_SIZE() { return NativeInvoke::Invoke<uint32_t>(NATIVE_GET_CURRENT_STACK_SIZE); }
			static uint32_t GET_CURRENT_ZONE_SCUMMINESS() { return NativeInvoke::Invoke<uint32_t>(NATIVE_GET_CURRENT_ZONE_SCUMMINESS); }
			static uint32_t GET_CUTSCENE_AUDIO_TIME_MS() { return NativeInvoke::Invoke<uint32_t>(NATIVE_GET_CUTSCENE_AUDIO_TIME_MS); }
			static uint32_t GET_CUTSCENE_SECTION_PLAYING() { return NativeInvoke::Invoke<uint32_t>(NATIVE_GET_CUTSCENE_SECTION_PLAYING); }
			static uint32_t GET_CUTSCENE_TIME() { return NativeInvoke::Invoke<uint32_t>(NATIVE_GET_CUTSCENE_TIME); }
			static uint32_t GET_EPISODE_INDEX_FROM_SUMMONS() { return NativeInvoke::Invoke<uint32_t>(NATIVE_GET_EPISODE_INDEX_FROM_SUMMONS); }
			static uint32_t GET_FRAME_COUNT() { return NativeInvoke::Invoke<uint32_t>(NATIVE_GET_FRAME_COUNT); }
			static uint32_t GET_HOURS_OF_DAY() { return NativeInvoke::Invoke<uint32_t>(NATIVE_GET_HOURS_OF_DAY); }
			static uint32_t GET_ID_OF_THIS_THREAD() { return NativeInvoke::Invoke<uint32_t>(NATIVE_GET_ID_OF_THIS_THREAD); }
			static uint32_t GET_LATEST_CONSOLE_COMMAND() { return NativeInvoke::Invoke<uint32_t>(NATIVE_GET_LATEST_CONSOLE_COMMAND); }
			static uint32_t GET_LOCAL_GAMERLEVEL_FROM_PROFILESETTINGS() { return NativeInvoke::Invoke<uint32_t>(NATIVE_GET_LOCAL_GAMERLEVEL_FROM_PROFILESETTINGS); }
			static uint32_t GET_LOCAL_PLAYER_MP_CASH() { return NativeInvoke::Invoke<uint32_t>(NATIVE_GET_LOCAL_PLAYER_MP_CASH); }
			static uint32_t GET_MINUTES_OF_DAY() { return NativeInvoke::Invoke<uint32_t>(NATIVE_GET_MINUTES_OF_DAY); }
			static uint32_t GET_NO_LAW_VEHICLES_DESTROYED_BY_LOCAL_PLAYER() { return NativeInvoke::Invoke<uint32_t>(NATIVE_GET_NO_LAW_VEHICLES_DESTROYED_BY_LOCAL_PLAYER); }
			static uint32_t GET_NUMBER_OF_PLAYERS() { return NativeInvoke::Invoke<uint32_t>(NATIVE_GET_NUMBER_OF_PLAYERS); }
			static uint32_t GET_NUMBER_OF_INSTANCES_OF_STREAMED_SCRIPT(String^ scriptName)
			{
				msclr::interop::marshal_context ctx;
				return NativeInvoke::Invoke<uint32_t>(NATIVE_GET_NUMBER_OF_INSTANCES_OF_STREAMED_SCRIPT, ctx.marshal_as<const char*>(scriptName));
			}
			static uint32_t GET_NUM_STREAMING_REQUESTS() { return NativeInvoke::Invoke<uint32_t>(NATIVE_GET_NUM_STREAMING_REQUESTS); }
			static uint32_t GET_ONLINE_LAN() { return NativeInvoke::Invoke<uint32_t>(NATIVE_GET_ONLINE_LAN); }
			static uint32_t GET_PLAYERSETTINGS_MODEL_CHOICE() { return NativeInvoke::Invoke<uint32_t>(NATIVE_GET_PLAYERSETTINGS_MODEL_CHOICE); }
			static uint32_t GET_PLAYER_RADIO_MODE() { return NativeInvoke::Invoke<uint32_t>(NATIVE_GET_PLAYER_RADIO_MODE); }
			static uint32_t GET_PLAYER_RADIO_STATION_INDEX() { return NativeInvoke::Invoke<uint32_t>(NATIVE_GET_PLAYER_RADIO_STATION_INDEX); }
			static String^ GET_PLAYER_RADIO_STATION_NAME()
			{
				return gcnew String(NativeInvoke::Invoke<char*>(NATIVE_GET_PLAYER_RADIO_STATION_NAME));
			}
			static uint32_t GET_ROUTE_SIZE() { return NativeInvoke::Invoke<uint32_t>(NATIVE_GET_ROUTE_SIZE); }
			static uint32_t GET_SCREEN_FADE_ALPHA() { return NativeInvoke::Invoke<uint32_t>(NATIVE_GET_SCREEN_FADE_ALPHA); }
			static uint32_t GET_SIMPLE_BLIP_ID() { return NativeInvoke::Invoke<uint32_t>(NATIVE_GET_SIMPLE_BLIP_ID); }
			static uint32_t GET_SOUND_ID() { return NativeInvoke::Invoke<uint32_t>(NATIVE_GET_SOUND_ID); }
			static uint32_t GET_STREAM_PLAYTIME() { return NativeInvoke::Invoke<uint32_t>(NATIVE_GET_STREAM_PLAYTIME); }
			static uint32_t GET_TIME_SINCE_LAST_ARREST() { return NativeInvoke::Invoke<uint32_t>(NATIVE_GET_TIME_SINCE_LAST_ARREST); }
			static uint32_t GET_TIME_SINCE_LAST_DEATH() { return NativeInvoke::Invoke<uint32_t>(NATIVE_GET_TIME_SINCE_LAST_DEATH); }
			static uint32_t GET_TOTAL_NUMBER_OF_STATS() { return NativeInvoke::Invoke<uint32_t>(NATIVE_GET_TOTAL_NUMBER_OF_STATS); }
			static uint32_t NETWORK_GET_FRIEND_COUNT() { return NativeInvoke::Invoke<uint32_t>(NATIVE_NETWORK_GET_FRIEND_COUNT); }
			static uint32_t NETWORK_GET_GAME_MODE() { return NativeInvoke::Invoke<uint32_t>(NATIVE_NETWORK_GET_GAME_MODE); }
			static uint32_t NETWORK_GET_MAX_PRIVATE_SLOTS() { return NativeInvoke::Invoke<uint32_t>(NATIVE_NETWORK_GET_MAX_PRIVATE_SLOTS); }
			static uint32_t NETWORK_GET_MAX_SLOTS() { return NativeInvoke::Invoke<uint32_t>(NATIVE_NETWORK_GET_MAX_SLOTS); }
			static uint32_t NETWORK_GET_NUMBER_OF_GAMES() { return NativeInvoke::Invoke<uint32_t>(NATIVE_NETWORK_GET_NUMBER_OF_GAMES); }
			static uint32_t NETWORK_GET_NUM_OPEN_PUBLIC_SLOTS() { return NativeInvoke::Invoke<uint32_t>(NATIVE_NETWORK_GET_NUM_OPEN_PUBLIC_SLOTS); }
			static uint32_t NETWORK_GET_NUM_PARTY_MEMBERS() { return NativeInvoke::Invoke<uint32_t>(NATIVE_NETWORK_GET_NUM_PARTY_MEMBERS); }
			static uint32_t NETWORK_GET_NUM_PLAYERS_MET() { return NativeInvoke::Invoke<uint32_t>(NATIVE_NETWORK_GET_NUM_PLAYERS_MET); }
			static uint32_t NETWORK_GET_NUM_UNACCEPTED_INVITES() { return NativeInvoke::Invoke<uint32_t>(NATIVE_NETWORK_GET_NUM_UNACCEPTED_INVITES); }
			static uint32_t NETWORK_GET_NUM_UNFILLED_RESERVATIONS() { return NativeInvoke::Invoke<uint32_t>(NATIVE_NETWORK_GET_NUM_UNFILLED_RESERVATIONS); }
			static uint32_t NETWORK_GET_PLAYER_ID_OF_NEXT_TEXT_CHAT() { return NativeInvoke::Invoke<uint32_t>(NATIVE_NETWORK_GET_PLAYER_ID_OF_NEXT_TEXT_CHAT); }
			static uint32_t NETWORK_GET_RENDEZVOUS_HOST_PLAYER_ID() { return NativeInvoke::Invoke<uint32_t>(NATIVE_NETWORK_GET_RENDEZVOUS_HOST_PLAYER_ID); }
			static uint32_t READ_KILL_FRENZY_STATUS() { return NativeInvoke::Invoke<uint32_t>(NATIVE_READ_KILL_FRENZY_STATUS); }
			static uint32_t TIMERA() { return NativeInvoke::Invoke<uint32_t>(NATIVE_TIMERA); }
			static uint32_t TIMERB() { return NativeInvoke::Invoke<uint32_t>(NATIVE_TIMERB); }
			static uint32_t TIMERC() { return NativeInvoke::Invoke<uint32_t>(NATIVE_TIMERC); }
			static uint32_t TIMESTEP() { return NativeInvoke::Invoke<uint32_t>(NATIVE_TIMESTEP); }

			static uint32_t NETWORK_CHANGE_GAME_MODE(int a1, int a2, int a3, int a4) { return NativeInvoke::Invoke<uint32_t>(NATIVE_NETWORK_CHANGE_GAME_MODE, a1, a2, a3, a4); }

			static uint32_t GET_LENGTH_OF_LITERAL_STRING(String^ str)
			{
				msclr::interop::marshal_context ctx;
				return NativeInvoke::Invoke<uint32_t>(NATIVE_GET_LENGTH_OF_LITERAL_STRING, (char*)ctx.marshal_as<const char*>(str));
			}

			// msclr::interop::marshal_context ctx;
			// ctx.marshal_as<const char*>(

		};
	}
}

