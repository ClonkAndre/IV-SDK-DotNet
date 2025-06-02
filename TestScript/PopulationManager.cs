using CCL.GTAIV;

using IVSDKDotNet.Native;

namespace TestScript
{
    internal class PopulationManager
    {

        public static void AllowAllSpawning()
        {
            AllowAllTraffic();
            SetPedDensity(1.0f);
        }
        public static void AllowAllTraffic()
        {
            SetParkedCarDensity(1.0f);
            SetRandomCarDensity(1.0f);
            SetAllowEmergencyServices(true);
            SetAllowGarbageTrucks(true);
            SetAllowRandomBoats(true);
            SetAllowRandomTrains(true);
        }

        public static void BlockAllSpawning()
        {
            BlockAllTraffic();
            SetPedDensity(0.0f);
        }
        public static void BlockAllTraffic()
        {
            SetParkedCarDensity(0.0f);
            SetRandomCarDensity(0.0f);
            SetAllowEmergencyServices(false);
            SetAllowGarbageTrucks(false);
            SetAllowRandomBoats(false);
            SetAllowRandomTrains(false);
        }

        public static void DisableCityServices()
        {
            SetAllowEmergencyServices(false);
            SetAllowGarbageTrucks(false);
            SetAllowRandomTrains(false);
        }
        public static void EnableCityServices()
        {
            SetAllowEmergencyServices(true);
            SetAllowGarbageTrucks(true);
            SetAllowRandomTrains(true);
        }

        public static void SetAllowEmergencyServices(bool value)
        {
            NativeGame.AllowEmergencyServices = value;
        }

        public static void SetAllowGarbageTrucks(bool value)
        {
            Natives.SWITCH_GARBAGE_TRUCKS(value);
        }

        public static void SetAllowRandomBoats(bool value)
        {
            Natives.SWITCH_RANDOM_BOATS(value);
        }

        public static void SetAllowRandomTrains(bool value)
        {
            // For some reason, the game code creates trains when this flag is set to false.
            Natives.SWITCH_RANDOM_TRAINS(!value);
        }

        public static void SetParkedCarDensity(float density)
        {
            Natives.SET_PARKED_CAR_DENSITY_MULTIPLIER(density);
        }

        public static void SetRandomCarDensity(float density)
        {
            Natives.SET_RANDOM_CAR_DENSITY_MULTIPLIER(density);
        }

        public static void SetPedDensity(float density)
        {
            Natives.SET_PED_DENSITY_MULTIPLIER(density);
        }

    }
}
