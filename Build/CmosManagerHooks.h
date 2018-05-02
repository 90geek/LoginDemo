#define CMOS_BATTERY_TEST_MAPPING CmosMgrBatteryIsGood,
#define CMOS_IS_FIRST_BOOT_MAPPING CmosMgrIsFirstBoot,
#define CMOS_IS_BSP_MAPPING CmosMgrIsBsp,
#define CMOS_IS_COLD_BOOT_MAPPING CmosMgrIsColdBoot,
#define CMOS_IS_USABLE_MAPPING CmosIsUsable,
#define CMOS_PORT_MAPPING {0, 0, 0, 127, ReadWriteStandardRange}, {0, 0, 0x80, 0xff, ReadWriteCmosBank2},

