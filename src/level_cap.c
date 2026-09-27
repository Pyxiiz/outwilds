#include "global.h"
#include "event_data.h"
#include "constants/flags.h"
#include "constants/vars.h"
#include "field_message_box.h"
#include "string_util.h"
#include "level_cap.h"
#include "caps.h"

static const u8 sText_LevelCapIncreased[] =
    _("Your Level Cap has increased\n"
      "to Lv. {STR_VAR_1}!");

void TryAnnounceLevelCapIncrease(void)
{
    u8 currentCap = GetCurrentLevelCap();
    u8 lastCap = VarGet(VAR_LAST_LEVEL_CAP);

    if (currentCap > lastCap)
    {
        VarSet(VAR_LAST_LEVEL_CAP, currentCap);

        ConvertIntToDecimalStringN(gStringVar1, currentCap, STR_CONV_MODE_LEFT_ALIGN, 3);
        StringExpandPlaceholders(gStringVar4, sText_LevelCapIncreased);
        ShowFieldMessage(gStringVar4);
    }
}