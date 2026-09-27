#include "constants/abilities.h"
#include "constants/teaching_types.h"
#include "species_info/shared_dex_text.h"
#include "species_info/shared_front_pic_anims.h"

// Macros for ease of use.

#define EVOLUTION(...) (const struct Evolution[]) { __VA_ARGS__, { EVOLUTIONS_END }, }
#define CONDITIONS(...) ((const struct EvolutionParam[]) { __VA_ARGS__, {CONDITIONS_END} })

#define ANIM_FRAMES(...) (const union AnimCmd *const[]) { sAnim_GeneralFrame0, (const union AnimCmd[]) { __VA_ARGS__ ANIMCMD_END, }, }

#if P_FOOTPRINTS
#define FOOTPRINT(sprite) .footprint = gMonFootprint_## sprite,
#else
#define FOOTPRINT(sprite)
#endif

#if B_ENEMY_MON_SHADOW_STYLE >= GEN_4 && P_GBA_STYLE_SPECIES_GFX == FALSE
#define SHADOW(x, y, size)  .enemyShadowXOffset = x, .enemyShadowYOffset = y, .enemyShadowSize = size,
#define NO_SHADOW           .suppressEnemyShadow = TRUE,
#else
#define SHADOW(x, y, size)  .enemyShadowXOffset = 0, .enemyShadowYOffset = 0, .enemyShadowSize = 0,
#define NO_SHADOW           .suppressEnemyShadow = FALSE,
#endif

#define SIZE_32x32 1
#define SIZE_64x64 0

// Set .compressed = OW_GFX_COMPRESS
#define COMP OW_GFX_COMPRESS

#if OW_POKEMON_OBJECT_EVENTS
#if OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE
#define OVERWORLD_PAL(...)                                  \
    .overworldPalette = DEFAULT(NULL, __VA_ARGS__),         \
    .overworldShinyPalette = DEFAULT_2(NULL, __VA_ARGS__),
#if P_GENDER_DIFFERENCES
#define OVERWORLD_PAL_FEMALE(...)                                 \
    .overworldPaletteFemale = DEFAULT(NULL, __VA_ARGS__),         \
    .overworldShinyPaletteFemale = DEFAULT_2(NULL, __VA_ARGS__),
#else
#define OVERWORLD_PAL_FEMALE(...)
#endif //P_GENDER_DIFFERENCES
#else
#define OVERWORLD_PAL(...)
#define OVERWORLD_PAL_FEMALE(...)
#endif //OW_PKMN_OBJECTS_SHARE_PALETTES == FALSE

#define OVERWORLD_DATA(picTable, _size, shadow, _tracks, _anims)                                                                     \
{                                                                                                                                       \
    .tileTag = TAG_NONE,                                                                                                                \
    .paletteTag = OBJ_EVENT_PAL_TAG_DYNAMIC,                                                                                            \
    .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,                                                                                     \
    .size = (_size == SIZE_32x32 ? 512 : 2048),                                                                                         \
    .width = (_size == SIZE_32x32 ? 32 : 64),                                                                                           \
    .height = (_size == SIZE_32x32 ? 32 : 64),                                                                                          \
    .paletteSlot = PALSLOT_NPC_1,                                                                                                       \
    .shadowSize = shadow,                                                                                                               \
    .inanimate = FALSE,                                                                                                                 \
    .compressed = COMP,                                                                                                                 \
    .tracks = _tracks,                                                                                                                  \
    .oam = (_size == SIZE_32x32 ? &gObjectEventBaseOam_32x32 : &gObjectEventBaseOam_64x64),                                             \
    .subspriteTables = (_size == SIZE_32x32 ? sOamTables_32x32 : sOamTables_64x64),                                                     \
    .anims = _anims,                                                                                                                    \
    .images = picTable,                                                                                                                 \
}

#define OVERWORLD(objEventPic, _size, shadow, _tracks, _anims, ...)                                 \
    .overworldData = OVERWORLD_DATA(objEventPic, _size, shadow, _tracks, _anims),                   \
    OVERWORLD_PAL(__VA_ARGS__)

#if P_GENDER_DIFFERENCES
#define OVERWORLD_FEMALE(objEventPic, _size, shadow, _tracks, _anims, ...)                          \
    .overworldDataFemale = OVERWORLD_DATA(objEventPic, _size, shadow, _tracks, _anims),             \
    OVERWORLD_PAL_FEMALE(__VA_ARGS__)
#else
#define OVERWORLD_FEMALE(...)
#endif //P_GENDER_DIFFERENCES

#else
#define OVERWORLD(...)
#define OVERWORLD_FEMALE(...)
#define OVERWORLD_PAL(...)
#define OVERWORLD_PAL_FEMALE(...)
#endif //OW_POKEMON_OBJECT_EVENTS

// Maximum value for a female Pokémon is 254 (MON_FEMALE) which is 100% female.
// 255 (MON_GENDERLESS) is reserved for genderless Pokémon.
#define PERCENT_FEMALE(percent) min(254, ((percent * 255) / 100))

#define MON_TYPES(type1, ...) { type1, DEFAULT(type1, __VA_ARGS__) }
#define MON_EGG_GROUPS(group1, ...) { group1, DEFAULT(group1, __VA_ARGS__) }

#define FLIP    0
#define NO_FLIP 1

const struct SpeciesInfo gSpeciesInfo[] =
{
    [SPECIES_NONE] =
    {
        .speciesName = _("??????????"),
        .cryId = CRY_PORYGON,
        .natDexNum = NATIONAL_DEX_NONE,
        .categoryName = _("Unknown"),
        .height = 0,
        .weight = 0,
        .description = gFallbackPokedexText,
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_CircledQuestionMark,
        .frontPicSize = MON_COORDS_SIZE(40, 40),
        .frontPicYOffset = 12,
        .frontAnimFrames = sAnims_TwoFramePlaceHolder,
        .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_CircledQuestionMark,
        .backPicSize = MON_COORDS_SIZE(40, 40),
        .backPicYOffset = 12,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_CircledQuestionMark,
        .shinyPalette = gMonShinyPalette_CircledQuestionMark,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        .pokemonJumpType = PKMN_JUMP_TYPE_NONE,
        FOOTPRINT(QuestionMark)
        SHADOW(-1, 0, SHADOW_SIZE_M)
    #if OW_POKEMON_OBJECT_EVENTS
        .overworldData = {
            .tileTag = TAG_NONE,
            .paletteTag = OBJ_EVENT_PAL_TAG_SUBSTITUTE,
            .reflectionPaletteTag = OBJ_EVENT_PAL_TAG_NONE,
            .size = 512,
            .width = 32,
            .height = 32,
            .paletteSlot = PALSLOT_NPC_1,
            .shadowSize = SHADOW_SIZE_M,
            .inanimate = FALSE,
            .compressed = COMP,
            .tracks = TRACKS_FOOT,
            .oam = &gObjectEventBaseOam_32x32,
            .subspriteTables = sOamTables_32x32,
            .anims = sAnimTable_Following,
            .images = sPicTable_Substitute,
        },
    #endif
        .levelUpLearnset = sNoneLevelUpLearnset,
        .teachableLearnset = sNoneTeachableLearnset,
        .eggMoveLearnset = sNoneEggMoveLearnset,
    },

    #include "species_info/gen_1_families.h"
    #include "species_info/gen_2_families.h"
    #include "species_info/gen_3_families.h"
    #include "species_info/gen_4_families.h"
    #include "species_info/gen_5_families.h"
    #include "species_info/gen_6_families.h"
    #include "species_info/gen_7_families.h"
    #include "species_info/gen_8_families.h"
    #include "species_info/gen_9_families.h"

    [SPECIES_EGG] =
    {
        .frontPic = gMonFrontPic_Egg,
        .frontPicSize = MON_COORDS_SIZE(24, 24),
        .frontPicYOffset = 20,
        .backPic = gMonFrontPic_Egg,
        .backPicSize = MON_COORDS_SIZE(24, 24),
        .backPicYOffset = 20,
        .palette = gMonPalette_Egg,
        .shinyPalette = gMonPalette_Egg,
        .iconSprite = gMonIcon_Egg,
        .iconPalIndex = 1,
    },

    /* You may add any custom species below this point based on the following structure: */

    /*
    [SPECIES_NONE] =
    {
        .baseHP        = 1,
        .baseAttack    = 1,
        .baseDefense   = 1,
        .baseSpeed     = 1,
        .baseSpAttack  = 1,
        .baseSpDefense = 1,
        .types = MON_TYPES(TYPE_MYSTERY),
        .catchRate = 255,
        .expYield = 67,
        .evYield_HP = 1,
        .evYield_Defense = 1,
        .evYield_SpDefense = 1,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
        .abilities = { ABILITY_NONE, ABILITY_CURSED_BODY, ABILITY_DAMP },
        .bodyColor = BODY_COLOR_BLACK,
        .speciesName = _("??????????"),
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_NONE,
        .categoryName = _("Unknown"),
        .height = 0,
        .weight = 0,
        .description = COMPOUND_STRING(
            "This is a newly discovered Pokémon.\n"
            "It is currently under investigation.\n"
            "No detailed information is available\n"
            "at this time."),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_CircledQuestionMark,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_None,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_CircledQuestionMark,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 7,
#if P_GENDER_DIFFERENCES
        .frontPicFemale = gMonFrontPic_CircledQuestionMark,
        .frontPicSizeFemale = MON_COORDS_SIZE(64, 64),
        .backPicFemale = gMonBackPic_CircledQuestionMarkF,
        .backPicSizeFemale = MON_COORDS_SIZE(64, 64),
        .paletteFemale = gMonPalette_CircledQuestionMarkF,
        .shinyPaletteFemale = gMonShinyPalette_CircledQuestionMarkF,
        .iconSpriteFemale = gMonIcon_QuestionMarkF,
        .iconPalIndexFemale = 1,
#endif //P_GENDER_DIFFERENCES
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_CircledQuestionMark,
        .shinyPalette = gMonShinyPalette_CircledQuestionMark,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        FOOTPRINT(QuestionMark)
        .levelUpLearnset = sNoneLevelUpLearnset,
        .teachableLearnset = sNoneTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 100, SPECIES_NONE},
                                {EVO_ITEM, ITEM_MOOMOO_MILK, SPECIES_NONE}),
        //.formSpeciesIdTable = sNoneFormSpeciesIdTable,
        //.formChangeTable = sNoneFormChangeTable,
        //.perfectIVCount = NUM_STATS,
    },
    */
    


const struct EggData gEggDatas[EGG_ID_COUNT] =
{
#include "egg_data.h"
};

    [SPECIES_CAPILLAURO] =
        {
            .baseHP        = 75,
            .baseAttack    = 45,
            .baseDefense   = 77,
            .baseSpeed     = 25,
            .baseSpAttack  = 137,
            .baseSpDefense = 109,
            .types = MON_TYPES(TYPE_ICE, TYPE_POISON),
            .catchRate = 60,
            .expYield = 67,
            .evYield_HP = 1,
            .evYield_SpDefense = 1,
            .genderRatio = PERCENT_FEMALE(50),
            .eggCycles = 20,
            .friendship = STANDARD_FRIENDSHIP,
            .growthRate = GROWTH_SLOW,
            .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
            .abilities = { ABILITY_ICE_BODY, ABILITY_HEATPROOF, ABILITY_SNOW_WARNING },
            .bodyColor = BODY_COLOR_BLUE,
            .speciesName = _("Capillauro"),
            .cryId = CRY_ARAQUANID,
            .natDexNum = NATIONAL_DEX_CAPILLAURO,
            .categoryName = _("Frozen Jelly"),
            .height = 196,
            .weight = 9070,
            .description = COMPOUND_STRING(
                "The potent neurotoxin in its tentacles.\n"
                "causes its victim to freeze from the.\n"
                "inside out. One sting can incapacitate\n"
                "a Wailord in a matter of seconds."),
            .pokemonScale = 256,
            .pokemonOffset = 0,
            .trainerScale = 448,
            .trainerOffset = 12,
            .frontPic = gMonFrontPic_Capillauro,
            .frontPicSize = MON_COORDS_SIZE(64, 64),
            .frontPicYOffset = 0,
            .frontAnimFrames = ANIM_FRAMES(
                ANIMCMD_FRAME(0, 19),
                ANIMCMD_FRAME(1, 35),
                ANIMCMD_FRAME(0, 19),
                ANIMCMD_FRAME(1, 19),
                ANIMCMD_FRAME(0, 8),
            ),
            .frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
            .backPic = gMonBackPic_Capillauro,
            .backPicSize = MON_COORDS_SIZE(64, 64),
            .backPicYOffset = 7,
            .backAnimId = BACK_ANIM_H_SLIDE,
            .palette = gMonPalette_Capillauro,
            .shinyPalette = gMonShinyPalette_Capillauro,
            .iconSprite = gMonIcon_Capillauro,
            .iconPalIndex = 0,
            FOOTPRINT(Capillauro)
            .levelUpLearnset = sCapillauroLevelUpLearnset,
            .teachableLearnset = sCapillauroTeachableLearnset,
        },

        [SPECIES_FABLIDA] =
    {
        .baseHP        = 160,
        .baseAttack    = 70,
        .baseDefense   = 125,
        .baseSpeed     = 50,
        .baseSpAttack  = 150,
        .baseSpDefense = 125,
        .types = MON_TYPES(TYPE_NORMAL, TYPE_FAIRY),
        .catchRate = 3,
        .expYield = 340,
        .evYield_HP = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 20,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
        .abilities = { ABILITY_MISTY_SURGE, ABILITY_NONE, ABILITY_NONE },
        .bodyColor = BODY_COLOR_WHITE,
        .speciesName = _("Fablida"),
        .cryId = CRY_FROSMOTH,
        .natDexNum = NATIONAL_DEX_FABLIDA,
        .categoryName = _("Storywriter"),
        .height = 10,
        .weight = 65,
        .description = COMPOUND_STRING(
            "It knows every possible event that\n"
            "could ever happen. As the first creation\n"
            "of the Original One, it shoulders the\n"
            "task of recording all of history."),
        .pokemonScale = 422,
        .pokemonOffset = 12,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Fablida,
        .frontPicSize = MON_COORDS_SIZE(32, 48),
        .frontPicYOffset = 0,
        .frontAnimFrames = ANIM_FRAMES(
            ANIMCMD_FRAME(0, 15),
            ANIMCMD_FRAME(1, 45),
            ANIMCMD_FRAME(0, 15),
            ANIMCMD_FRAME(1, 10),
            ANIMCMD_FRAME(0, 15),
            ANIMCMD_FRAME(1, 10),
            ANIMCMD_FRAME(0, 15),
        ),
        .frontAnimId = ANIM_GROW_VIBRATE,
        .backPic = gMonBackPic_Fablida,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 7,
        .backAnimId = BACK_ANIM_SHRINK_GROW,
        .palette = gMonPalette_Fablida,
        .shinyPalette = gMonShinyPalette_Fablida,
        .iconSprite = gMonIcon_Fablida,
        .iconPalIndex = 0,
        FOOTPRINT(Fablida)
        .isLegendary = TRUE,
        .perfectIVCount = LEGENDARY_PERFECT_IV_COUNT,
        .levelUpLearnset = sFablidaLevelUpLearnset,
        .teachableLearnset = sFablidaTeachableLearnset,
        .formSpeciesIdTable = sFablidaFormSpeciesIdTable,
        .formChangeTable = sFablidaFormChangeTable,
    },

    [SPECIES_IRACOR] =
    {
        .baseHP        = 160,
        .baseAttack    = 130,
        .baseDefense   = 140,
        .baseSpeed     = 103,
        .baseSpAttack  = 62,
        .baseSpDefense = 85,
        .types = MON_TYPES(TYPE_DRAGON, TYPE_GHOST),
        .catchRate = 3,
        .expYield = 340,
        .evYield_HP = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 20,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
        .abilities = { ABILITY_DEFIANT, ABILITY_NONE, ABILITY_NONE },
        .bodyColor = BODY_COLOR_BLACK,
        .speciesName = _("Iracor"),
        .cryId = CRY_NECROZMA_ULTRA,
        .natDexNum = NATIONAL_DEX_IRACOR,
        .categoryName = _("Frenzy"),
        .height = 190,
        .weight = 7500,
        .description = COMPOUND_STRING(
            "The only thing that fuels this pokemon\n"
            "is its pure, unadulterated rage and\n"
            "hatred towards all that exists,\n"
            "including itself."),
        .pokemonScale = 230,
        .pokemonOffset = 0,
        .trainerScale = 550,
        .trainerOffset = 8,
        .frontPic = gMonFrontPic_Iracor,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = ANIM_BACK_AND_LUNGE,
        .backPic = gMonBackPic_Iracor,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 7,
        .backAnimId = BACK_ANIM_H_VIBRATE,
        .palette = gMonPalette_Iracor,
        .shinyPalette = gMonShinyPalette_Iracor,
        .iconSprite = gMonIcon_Iracor,
        .iconPalIndex = 0,
        FOOTPRINT(Eternatus)
        .levelUpLearnset = sIracorLevelUpLearnset,
        .teachableLearnset = sIracorTeachableLearnset,
        .formSpeciesIdTable = sIracorFormSpeciesIdTable,
        .formChangeTable = sIracorFormChangeTable,
    },

    [SPECIES_FABLIDA_GENESIS] =
    {
        .baseHP        = 160,
        .baseAttack    = 60,
        .baseDefense   = 150,
        .baseSpeed     = 45,
        .baseSpAttack  = 215,
        .baseSpDefense = 150,
        .types = MON_TYPES(TYPE_NORMAL, TYPE_FAIRY),
        .catchRate = 3,
        .expYield = 340,
        .evYield_HP = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 20,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
        .abilities = { ABILITY_ETHEREAL_STAGE, ABILITY_NONE, ABILITY_NONE },
        .bodyColor = BODY_COLOR_WHITE,
        .speciesName = _("Fablida"),
        .cryId = CRY_FROSMOTH,
        .natDexNum = NATIONAL_DEX_FABLIDA,
        .categoryName = _("Storywriter"),
        .height = 6,
        .weight = 65,
        .description = COMPOUND_STRING(
            "At the beginning of time, a pure child of\n"
            "the Original One was born. Using the stars\n"
            "their pen and the sky their canvas they\n"
            "paint the immemorial fable known as history"),
        .pokemonScale = 422,
        .pokemonOffset = 12,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_FablidaGenesis,
        .frontPicSize = MON_COORDS_SIZE(32, 48),
        .frontPicYOffset = 0,
        .frontAnimFrames = ANIM_FRAMES(
            ANIMCMD_FRAME(0, 15),
            ANIMCMD_FRAME(1, 45),
            ANIMCMD_FRAME(0, 15),
            ANIMCMD_FRAME(1, 10),
            ANIMCMD_FRAME(0, 15),
            ANIMCMD_FRAME(1, 10),
            ANIMCMD_FRAME(0, 15),
        ),
        .frontAnimId = ANIM_GROW_VIBRATE,
        .backPic = gMonBackPic_FablidaGenesis,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 7,
        .backAnimId = BACK_ANIM_SHRINK_GROW,
        .palette = gMonPalette_FablidaGenesis,
        .shinyPalette = gMonShinyPalette_FablidaGenesis,
        .iconSprite = gMonIcon_FablidaGenesis,
        .iconPalIndex = 0,
        FOOTPRINT(Fablida)
        .isLegendary = TRUE,
        .perfectIVCount = LEGENDARY_PERFECT_IV_COUNT,
        .levelUpLearnset = sFablidaLevelUpLearnset,
        .teachableLearnset = sFablidaTeachableLearnset,
        .formSpeciesIdTable = sFablidaFormSpeciesIdTable,
        .formChangeTable = sFablidaFormChangeTable,
    },

    [SPECIES_IRACOR_GENESIS] =
    {
        .baseHP        = 160,
        .baseAttack    = 170,
        .baseDefense   = 150,
        .baseSpeed     = 145,
        .baseSpAttack  = 70,
        .baseSpDefense = 100,
        .types = MON_TYPES(TYPE_DRAGON, TYPE_GHOST),
        .catchRate = 3,
        .expYield = 340,
        .evYield_HP = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 20,
        .friendship = 0,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
        .abilities = { ABILITY_RAGE_OF_FRENZY, ABILITY_NONE, ABILITY_NONE },
        .bodyColor = BODY_COLOR_BLACK,
        .speciesName = _("Iracor"),
        .cryId = CRY_ETERNATUS_ETERNAMAX,
        .natDexNum = NATIONAL_DEX_IRACOR,
        .categoryName = _("Frenzy"),
        .height = 1000,
        .weight = 9999,
        .description = COMPOUND_STRING(
            "As the last star breathes its final\n"
            "farewell, the Frenzied One will end\n"
            "all of creation. In the silence, It\n"
            "will be judged in the final act of history."),
        .pokemonScale = 230,
        .pokemonOffset = 0,
        .trainerScale = 4852,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_IracorGenesis,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 3,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = ANIM_BACK_AND_LUNGE,
        .backPic = gMonBackPic_IracorGenesis,
        .backPicSize = MON_COORDS_SIZE(64, 56),
        .backPicYOffset = 7,
        .backAnimId = BACK_ANIM_H_VIBRATE,
        .palette = gMonPalette_IracorGenesis,
        .shinyPalette = gMonShinyPalette_IracorGenesis,
        .iconSprite = gMonIcon_IracorGenesis,
        .iconPalIndex = 2,
        FOOTPRINT(Eternatus)
        .levelUpLearnset = sIracorLevelUpLearnset,
        .teachableLearnset = sIracorTeachableLearnset,
        .formSpeciesIdTable = sIracorFormSpeciesIdTable,
        .formChangeTable = sIracorFormChangeTable,
    },

    [SPECIES_TAPU_PELE] =
    {
        .baseHP        = 70,
        .baseAttack    = 75,
        .baseDefense   = 85,
        .baseSpeed     = 115,
        .baseSpAttack  = 130,
        .baseSpDefense = 95,
        .types = MON_TYPES(TYPE_FIRE, TYPE_FAIRY),
        .catchRate = 3,
        .expYield = 285,
        .evYield_SpAttack = 3,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 15,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
        .abilities = { ABILITY_DROUGHT, ABILITY_NONE, ABILITY_TELEPATHY },
        .bodyColor = BODY_COLOR_RED,
        .speciesName = _("Tapu Pele"),
        .cryId = CRY_TAPU_LELE,
        .natDexNum = NATIONAL_DEX_TAPU_PELE,
        .categoryName = _("Land Spirit"),
        .height = 12,
        .weight = 186,
        .description = COMPOUND_STRING(
            "Originally a Cosmog who couldn’t evolve,\n"
            "it adapted by copying the form of its\n"
            "caretaker. It lives in a volcano where\n"
            "it works to create a new Alolan island."),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 294,
        .trainerOffset = 3,
        .frontPic = gMonFrontPic_TapuPele,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = ANIM_V_SLIDE_WOBBLE_SMALL,
        .backPic = gMonBackPic_TapuPele,
        .backPicSize = MON_COORDS_SIZE(48, 56),
        .backPicYOffset = 6,
        .backAnimId = BACK_ANIM_SHRINK_GROW_VIBRATE,
        .palette = gMonPalette_TapuPele,
        .shinyPalette = gMonShinyPalette_TapuPele,
        .iconSprite = gMonIcon_TapuPele,
        .iconPalIndex = 5,
        FOOTPRINT(TapuLele)
        .isLegendary = TRUE,
        .perfectIVCount = LEGENDARY_PERFECT_IV_COUNT,
        .levelUpLearnset = sTapuPeleLevelUpLearnset,
        .teachableLearnset = sTapuPeleTeachableLearnset,
    },

    [SPECIES_ARNGRIM] =
    {
        .baseHP        = 44,
        .baseAttack    = 92,
        .baseDefense   = 60,
        .baseSpeed     = 54,
        .baseSpAttack  = 30,
        .baseSpDefense = 40,
        .types = MON_TYPES(TYPE_POISON),
        .catchRate = 45,
        .expYield = 67,
        .evYield_Attack = 1,
        .evYield_Defense = 1,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
        .abilities = { ABILITY_CORROSION, ABILITY_POISON_TOUCH, ABILITY_POISON_POINT },
        .bodyColor = BODY_COLOR_GRAY,
        .speciesName = _("Arngrim"),
        .cryId = CRY_KLINK,
        .natDexNum = NATIONAL_DEX_ARNGRIM,
        .categoryName = _("Corruption"),
        .height = 12,
        .weight = 333,
        .description = COMPOUND_STRING(
            "Formed from a sort of crystalized venom,\n"
            "these humanoid Pokemon seek to spread\n"
            "their corrosive venom to infect other\n"
            "people and Pokemon."),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Arngrim,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Arngrim,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 7,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Arngrim,
        .shinyPalette = gMonShinyPalette_Arngrim,
        .iconSprite = gMonIcon_Arngrim,
        .iconPalIndex = 1,
        FOOTPRINT(Arngrim)
        .levelUpLearnset = sArngrimLevelUpLearnset,
        .teachableLearnset = sArngrimTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 28, SPECIES_TERVINGI}),
    },

    [SPECIES_TERVINGI] =
    {
        .baseHP        = 68,
        .baseAttack    = 118,
        .baseDefense   = 70,
        .baseSpeed     = 64,
        .baseSpAttack  = 45,
        .baseSpDefense = 55,
        .types = MON_TYPES(TYPE_POISON),
        .catchRate = 45,
        .expYield = 67,
        .evYield_Attack = 1,
        .evYield_Defense = 1,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
        .abilities = { ABILITY_CORROSION, ABILITY_POISON_TOUCH, ABILITY_POISON_POINT },
        .bodyColor = BODY_COLOR_GRAY,
        .speciesName = _("Tervingi"),
        .cryId = CRY_KLANG,
        .natDexNum = NATIONAL_DEX_TERVINGI,
        .categoryName = _("Corruption"),
        .height = 20,
        .weight = 485,
        .description = COMPOUND_STRING(
            "The sharp stinger on its arm can double\n"
            "as a blade. It mindlessly follows\n"
            "the orders of allied Ichorbod."),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Tervingi,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Tervingi,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 7,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Tervingi,
        .shinyPalette = gMonShinyPalette_Tervingi,
        .iconSprite = gMonIcon_Tervingi,
        .iconPalIndex = 1,
        FOOTPRINT(Tervingi)
        .levelUpLearnset = sTervingiLevelUpLearnset,
        .teachableLearnset = sTervingiTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 46, SPECIES_ICHORBOD},
                                {EVO_ITEM, ITEM_DAWN_STONE, SPECIES_LOKASENNA, CONDITIONS({IF_GENDER, MON_FEMALE})}),
    },

    [SPECIES_ICHORBOD] =
    {
        .baseHP        = 92,
        .baseAttack    = 130,
        .baseDefense   = 115,
        .baseSpeed     = 88,
        .baseSpAttack  = 50,
        .baseSpDefense = 95,
        .types = MON_TYPES(TYPE_POISON, TYPE_DARK),
        .catchRate = 45,
        .expYield = 67,
        .evYield_Attack = 1,
        .evYield_Defense = 1,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
        .abilities = { ABILITY_CORROSION, ABILITY_DAUNTLESS_SHIELD, ABILITY_BAD_DREAMS },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("Ichorbod"),
        .cryId = CRY_ABOMASNOW,
        .natDexNum = NATIONAL_DEX_ICHORBOD,
        .categoryName = _("Dark Knight"),
        .height = 35,
        .weight = 1125,
        .description = COMPOUND_STRING(
            "Having finally gained a consciousness,\n"
            "it parades under the guise of a knight,\n"
            "leading its mindless brethren in combat.\n"
            "Its shield contains its commanding power."),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 612,
        .trainerOffset = 2,
        .frontPic = gMonFrontPic_Ichorbod,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = ANIM_H_SHAKE,
        .backPic = gMonBackPic_Ichorbod,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 7,
        .backAnimId = BACK_ANIM_V_SHAKE_LOW,
        .palette = gMonPalette_Ichorbod,
        .shinyPalette = gMonShinyPalette_Ichorbod,
        .iconSprite = gMonIcon_Ichorbod,
        .iconPalIndex = 4,
        FOOTPRINT(Ichorbod)
        .levelUpLearnset = sIchorbodLevelUpLearnset,
        .teachableLearnset = sIchorbodTeachableLearnset,
        .formSpeciesIdTable = sIchorbodFormSpeciesIdTable,
        .formChangeTable = sIchorbodFormChangeTable,
    },

    [SPECIES_LOKASENNA] =
    {
        .baseHP        = 77,
        .baseAttack    = 81,
        .baseDefense   = 70,
        .baseSpeed     = 127,
        .baseSpAttack  = 135,
        .baseSpDefense = 80,
        .types = MON_TYPES(TYPE_POISON, TYPE_FAIRY),
        .catchRate = 45,
        .expYield = 67,
        .evYield_Attack = 1,
        .evYield_Defense = 1,
        .genderRatio = MON_FEMALE,
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
        .abilities = { ABILITY_CORROSION, ABILITY_PIXILATE, ABILITY_CUTE_CHARM },
        .bodyColor = BODY_COLOR_BLACK,
        .speciesName = _("Lokasenna"),
        .cryId = CRY_GARDEVOIR,
        .natDexNum = NATIONAL_DEX_LOKASENNA,
        .categoryName = _("Deceiver"),
        .height = 18,
        .weight = 498,
        .description = COMPOUND_STRING(
            "While they have no definitive form,\n"
            "Lokasenna will commonly take the\n"
            "guise of a human female in order to\n"
            "lure prey and spread their corruption."),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 306,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Lokasenna,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_Lokasenna,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 7,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Lokasenna,
        .shinyPalette = gMonShinyPalette_Lokasenna,
        .iconSprite = gMonIcon_Lokasenna,
        .iconPalIndex = 4,
        FOOTPRINT(Lokasenna)
        .levelUpLearnset = sLokasennaLevelUpLearnset,
        .teachableLearnset = sLokasennaTeachableLearnset,
        .formSpeciesIdTable = sLokasennaFormSpeciesIdTable,
        .formChangeTable = sLokasennaFormChangeTable,
    },

    [SPECIES_ICHORBOD_MEGA] =
    {
        .baseHP        = 92,
        .baseAttack    = 170,
        .baseDefense   = 150,
        .baseSpeed     = 78,
        .baseSpAttack  = 50,
        .baseSpDefense = 130,
        .types = MON_TYPES(TYPE_POISON, TYPE_DARK),
        .catchRate = 45,
        .expYield = 67,
        .evYield_Attack = 1,
        .evYield_Defense = 1,
        .genderRatio = PERCENT_FEMALE(12.5),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
        .abilities = { ABILITY_LAST_STAND, ABILITY_LAST_STAND, ABILITY_LAST_STAND },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("Ichorbod"),
        .cryId = CRY_ABOMASNOW_MEGA,
        .natDexNum = NATIONAL_DEX_ICHORBOD,
        .categoryName = _("Dark Knight"),
        .height = 70,
        .weight = 2655,
        .description = COMPOUND_STRING(
            "Converting its shield into a thick\n"
            "layer of armor, it unleashes its\n"
            "full power. It will never surrender\n"
            "a fight to anybody."),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 1012,
        .trainerOffset = 2,
        .frontPic = gMonFrontPic_IchorbodMega,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = ANIM_H_SHAKE,
        .backPic = gMonBackPic_IchorbodMega,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 7,
        .backAnimId = BACK_ANIM_V_SHAKE_LOW,
        .palette = gMonPalette_IchorbodMega,
        .shinyPalette = gMonShinyPalette_IchorbodMega,
        .iconSprite = gMonIcon_IchorbodMega,
        .iconPalIndex = 4,
        FOOTPRINT(IchorbodMega)
        .levelUpLearnset = sIchorbodLevelUpLearnset,
        .teachableLearnset = sIchorbodTeachableLearnset,
        .formSpeciesIdTable = sIchorbodFormSpeciesIdTable,
        .formChangeTable = sIchorbodFormChangeTable,
    },

    [SPECIES_LOKASENNA_MEGA] =
    {
        .baseHP        = 77,
        .baseAttack    = 70,
        .baseDefense   = 100,
        .baseSpeed     = 151,
        .baseSpAttack  = 177,
        .baseSpDefense = 90,
        .types = MON_TYPES(TYPE_POISON, TYPE_FAIRY),
        .catchRate = 45,
        .expYield = 67,
        .evYield_Attack = 1,
        .evYield_Defense = 1,
        .genderRatio = MON_FEMALE,
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
        .abilities = { ABILITY_LAST_STAND, ABILITY_LAST_STAND, ABILITY_LAST_STAND },
        .bodyColor = BODY_COLOR_BLACK,
        .speciesName = _("Lokasenna"),
        .cryId = CRY_GARDEVOIR_MEGA,
        .natDexNum = NATIONAL_DEX_LOKASENNA,
        .categoryName = _("Deceiver"),
        .height = 18,
        .weight = 498,
        .description = COMPOUND_STRING(
            "Upon Mega Evolving, it releases a\n"
            "powerful airborne toxin to poison\n"
            "its enemies. If you are reading this,\n"
            "you are probably also now poisoned."),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 712,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_LokasennaMega,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        //.frontAnimId = ANIM_V_SQUISH_AND_BOUNCE,
        .backPic = gMonBackPic_LokasennaMega,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 7,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_LokasennaMega,
        .shinyPalette = gMonShinyPalette_LokasennaMega,
        .iconSprite = gMonIcon_LokasennaMega,
        .iconPalIndex = 4,
        FOOTPRINT(LokasennaMega)
        .levelUpLearnset = sLokasennaLevelUpLearnset,
        .teachableLearnset = sLokasennaTeachableLearnset,
        .formSpeciesIdTable = sLokasennaFormSpeciesIdTable,
        .formChangeTable = sLokasennaFormChangeTable,
    },

    [SPECIES_KITSOKAMI] =
    {
        .baseHP        = 1,
        .baseAttack    = 117,
        .baseDefense   = 30,
        .baseSpeed     = 136,
        .baseSpAttack  = 117,
        .baseSpDefense = 45,
        .types = MON_TYPES(TYPE_GHOST, TYPE_STEEL),
        .catchRate = 3,
        .expYield = 300,
        .evYield_Attack = 1,
        .evYield_SpAttack = 1,
        .evYield_Speed = 1,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_MEDIUM_FAST,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
        .abilities = { ABILITY_WONDER_GUARD, ABILITY_NONE, ABILITY_NONE },
        .bodyColor = BODY_COLOR_BLACK,
        .speciesName = _("Kitsokami"),
        .cryId = CRY_COSMOEM,
        .natDexNum = NATIONAL_DEX_KITSOKAMI,
        .categoryName = _("Twin Moon"),
        .height = 10,
        .weight = 13,
        .description = COMPOUND_STRING(
            "A reclusive and incoporeal duo, they\n"
            "travel the world, ensuring the cycle\n"
            "of life and death proceeds unfettered.\n"
            "They're the children of the Storywriter"),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 338,
        .trainerOffset = 1,
        .frontPic = gMonFrontPic_Kitsokami,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = ANIM_GLOW_BLACK,
        .backPic = gMonBackPic_Kitsokami,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 7,
        .backAnimId = BACK_ANIM_SHRINK_GROW_VIBRATE,
        .palette = gMonPalette_Kitsokami,
        .shinyPalette = gMonShinyPalette_Kitsokami,
        .iconSprite = gMonIcon_Kitsokami,
        .iconPalIndex = 4,
        FOOTPRINT(Kitsokami)
        .levelUpLearnset = sKitsokamiLevelUpLearnset,
        .teachableLearnset = sKitsokamiTeachableLearnset,
    },

    [SPECIES_BLAZE_BRUSH] =
    {
        .baseHP        = 113,
        .baseAttack    = 130,
        .baseDefense   = 130,
        .baseSpeed     = 82,
        .baseSpAttack  = 50,
        .baseSpDefense = 65,
        .types = MON_TYPES(TYPE_FIRE, TYPE_GRASS),
        .catchRate = 30,
        .expYield = 285,
        .evYield_HP = 1,
        .evYield_Attack = 1,
        .evYield_Defense = 1,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
        .abilities = { ABILITY_PROTOSYNTHESIS, ABILITY_NONE, ABILITY_CHLOROPHYLL },
        .bodyColor = BODY_COLOR_BROWN,
        .speciesName = _("Blaze Brush"),
        .cryId = CRY_FLAREON,
        .natDexNum = NATIONAL_DEX_BLAZE_BRUSH,
        .categoryName = _("Paradox"),
        .height = 10,
        .weight = 255,
        .description = COMPOUND_STRING(
            "The only record of this Pokemon comes\n"
            "from a paranormal magazine where it is\n"
            "said to perform controlled burns in\n"
            "dry, arid climates."),
        .pokemonScale = 305,
        .pokemonOffset = 8,
        .trainerScale = 257,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_BlazeBrush,
        .frontPicSize = MON_COORDS_SIZE(56, 48),
        .frontPicYOffset = 9,
        .frontAnimFrames = ANIM_FRAMES(
            ANIMCMD_FRAME(0, 10),
            ANIMCMD_FRAME(1, 20),
            ANIMCMD_FRAME(0, 5),
        ),
        .frontAnimId = ANIM_SHRINK_GROW,
        .backPic = gMonBackPic_BlazeBrush,
        .backPicSize = MON_COORDS_SIZE(48, 64),
        .backPicYOffset = 0,
        .backAnimId = BACK_ANIM_SHRINK_GROW_VIBRATE,
        .palette = gMonPalette_BlazeBrush,
        .shinyPalette = gMonShinyPalette_BlazeBrush,
        .iconSprite = gMonIcon_BlazeBrush,
        .iconPalIndex = 3,
        FOOTPRINT(BlazeBrush)
        .levelUpLearnset = sBlazeBrushLevelUpLearnset,
        .teachableLearnset = sBlazeBrushTeachableLearnset,
    },

    [SPECIES_SUNKEN_STAR] =
    {
        .baseHP        = 130,
        .baseAttack    = 65,
        .baseDefense   = 82,
        .baseSpeed     = 50,
        .baseSpAttack  = 113,
        .baseSpDefense = 130,
        .types = MON_TYPES(TYPE_WATER, TYPE_FAIRY),
        .catchRate = 30,
        .expYield = 285,
        .evYield_HP = 1,
        .evYield_SpAttack = 1,
        .evYield_SpDefense = 1,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
        .abilities = { ABILITY_PROTOSYNTHESIS, ABILITY_NONE, ABILITY_LIQUID_VOICE },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("Sunken Star"),
        .cryId = CRY_VAPOREON,
        .natDexNum = NATIONAL_DEX_SUNKEN_STAR,
        .categoryName = _("Paradox"),
        .height = 13,
        .weight = 340,
        .description = COMPOUND_STRING(
            "The only record of this Pokemon comes\n"
            "from a paranormal magazine where it is\n"
            "said to lure saliors and fishermen to\n"
            "drown in the depths with its songs."),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_SunkenStar,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = ANIM_GLOW_BLUE,
        .backPic = gMonBackPic_SunkenStar,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 7,
        .backAnimId = BACK_ANIM_SHAKE_GLOW_BLUE,
        .palette = gMonPalette_SunkenStar,
        .shinyPalette = gMonShinyPalette_SunkenStar,
        .iconSprite = gMonIcon_SunkenStar,
        .iconPalIndex = 0,
        FOOTPRINT(SunkenStar)
        .levelUpLearnset = sSunkenStarLevelUpLearnset,
        .teachableLearnset = sSunkenStarTeachableLearnset,
    },

    [SPECIES_IRON_ECHO] =
    {
        .baseHP        = 65,
        .baseAttack    = 82,
        .baseDefense   = 113,
        .baseSpeed     = 130,
        .baseSpAttack  = 130,
        .baseSpDefense = 50,
        .types = MON_TYPES(TYPE_ICE, TYPE_ELECTRIC),
        .catchRate = 30,
        .expYield = 285,
        .evYield_Defense = 1,
        .evYield_SpAttack = 1,
        .evYield_Speed = 1,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
        .abilities = { ABILITY_QUARK_DRIVE, ABILITY_NONE, ABILITY_BATTERY },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("Iron Echo"),
        .cryId = CRY_JOLTEON,
        .natDexNum = NATIONAL_DEX_IRON_ECHO,
        .categoryName = _("Paradox"),
        .height = 8,
        .weight = 259,
        .description = COMPOUND_STRING(
            "It resembles a Pokemon mentioned in\n"
            "a paranormal magazine, described as\n"
            "a battery used by future generations\n"
            "of arctic explorers."),
        .pokemonScale = 366,
        .pokemonOffset = 10,
        .trainerScale = 257,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_IronEcho,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = ANIM_V_STRETCH,
        .backPic = gMonBackPic_IronEcho,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 7,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_IronEcho,
        .shinyPalette = gMonShinyPalette_IronEcho,
        .iconSprite = gMonIcon_IronEcho,
        .iconPalIndex = 0,
        FOOTPRINT(IronEcho)
        .levelUpLearnset = sIronEchoLevelUpLearnset,
        .teachableLearnset = sIronEchoTeachableLearnset,
    },

    [SPECIES_IRON_SIGNAL] =
    {
        .baseHP        = 82,
        .baseAttack    = 50,
        .baseDefense   = 65,
        .baseSpeed     = 113,
        .baseSpAttack  = 130,
        .baseSpDefense = 130,
        .types = MON_TYPES(TYPE_PSYCHIC, TYPE_DARK),
        .catchRate = 30,
        .expYield = 285,
        .evYield_SpAttack = 1,
        .evYield_SpDefense = 1,
        .evYield_Speed = 1,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
        .abilities = { ABILITY_QUARK_DRIVE, ABILITY_NONE, ABILITY_AIR_LOCK },
        .bodyColor = BODY_COLOR_BLACK,
        .speciesName = _("Iron Signal"),
        .cryId = CRY_UMBREON,
        .natDexNum = NATIONAL_DEX_IRON_SIGNAL,
        .categoryName = _("Paradox"),
        .height = 9,
        .weight = 935,
        .description = COMPOUND_STRING(
            "A paranormal magazine describes it as\n"
            "an exploratory drone used for observing\n"
            "celestial bodies. It desperately tries\n"
            "signalling home, but with little luck."),
        .pokemonScale = 363,
        .pokemonOffset = 14,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_IronSignal,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = ANIM_GROW_VIBRATE,
        .backPic = gMonBackPic_IronSignal,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 7,
        .backAnimId = BACK_ANIM_SHRINK_GROW_VIBRATE,
        .palette = gMonPalette_IronSignal,
        .shinyPalette = gMonShinyPalette_IronSignal,
        .iconSprite = gMonIcon_IronSignal,
        .iconPalIndex = 0,
        FOOTPRINT(IronSignal)
        .levelUpLearnset = sIronSignalLevelUpLearnset,
        .teachableLearnset = sIronSignalTeachableLearnset,
    },
    [SPECIES_KRYPE] =
    {
        .baseHP        = 20,
        .baseAttack    = 20,
        .baseDefense   = 55,
        .baseSpeed     = 80,
        .baseSpAttack  = 10,
        .baseSpDefense = 15,
        .types = MON_TYPES(TYPE_ROCK),
        .catchRate = 45,
        .expYield = 189,
        .evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
        .abilities = { ABILITY_STURDY, ABILITY_STURDY, ABILITY_SAND_VEIL },
        .bodyColor = BODY_COLOR_BROWN,
        .speciesName = _("Krype"),
        .cryId = CRY_NACLI,
        .natDexNum = NATIONAL_DEX_KRYPE,
        .categoryName = _("Crawler"),
        .height = 4,
        .weight = 160,
        .description = COMPOUND_STRING(
            "This Pokemon's crystaline shell helps\n"
            "to contain its unstable core. When hit,\n"
            "it is highly prone to explode, so it's\n"
            "best to keep your distance."),
        .pokemonScale = 356,
        .pokemonOffset = 17,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_Krype,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 1,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = ANIM_GROW_VIBRATE,
        .backPic = gMonBackPic_Krype,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 4,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Krype,
        .shinyPalette = gMonShinyPalette_Krype,
        .iconSprite = gMonIcon_Krype,
        .iconPalIndex = 2,
        FOOTPRINT(Krype)
        .tmIlliterate = TRUE,
        .levelUpLearnset = sKrypeLevelUpLearnset,
        .teachableLearnset = sKrypeTeachableLearnset,
        .evolutions = EVOLUTION({EVO_LEVEL, 0, SPECIES_REISANDE, CONDITIONS({IF_HOLD_ITEM, ITEM_KINGS_ROCK})},
                                {EVO_ITEM, ITEM_KINGS_ROCK, SPECIES_REISANDE}),
    },
    [SPECIES_REISANDE] =
    {
        .baseHP        = 100,
        .baseAttack    = 136,
        .baseDefense   = 110,
        .baseSpeed     = 19,
        .baseSpAttack  = 90,
        .baseSpDefense = 100,
        .types = MON_TYPES(TYPE_ROCK, TYPE_DRAGON),
        .catchRate = 45,
        .expYield = 189,
        .evYield_Attack = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
        .abilities = { ABILITY_SAND_STREAM, ABILITY_SAND_SPIT, ABILITY_NOMAD },
        .bodyColor = BODY_COLOR_BROWN,
        .speciesName = _("Reisande"),
        .cryId = CRY_TYRANTRUM,
        .natDexNum = NATIONAL_DEX_REISANDE,
        .categoryName = _("Nomad"),
        .height = 291,
        .weight = 9799,
        .description = COMPOUND_STRING(
            "This gigantic wandering Pokemon is\n"
            "powered by a nuclear fission core.\n"
            "Despite its appearance, its quite\n"
            "friendly and lets people ride on it."),
        .pokemonScale = 230,
        .pokemonOffset = 0,
        .trainerScale = 7020,
        .trainerOffset = 18,
        .frontPic = gMonFrontPic_Reisande,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 1,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = ANIM_GROW_VIBRATE,
        .backPic = gMonBackPic_Reisande,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 4,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_Reisande,
        .shinyPalette = gMonShinyPalette_Reisande,
        .iconSprite = gMonIcon_Reisande,
        .iconPalIndex = 5,
        FOOTPRINT(Reisande)
        .levelUpLearnset = sReisandeLevelUpLearnset,
        .teachableLearnset = sReisandeTeachableLearnset,
    },

    [SPECIES_JETRAGON] =
    {
        .baseHP        = 100,
        .baseAttack    = 70,
        .baseDefense   = 90,
        .baseSpeed     = 200,
        .baseSpAttack  = 130,
        .baseSpDefense = 90,
        .types = MON_TYPES(TYPE_DRAGON, TYPE_FAIRY),
        .catchRate = 3,
        .expYield = 499,
        .evYield_SpAttack = 1,
        .evYield_Speed = 2,
        .genderRatio = PERCENT_FEMALE(50),
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
        .abilities = { ABILITY_LEVITATE, ABILITY_NONE, ABILITY_DRAGONS_MAW },
        .bodyColor = BODY_COLOR_BLUE,
        .speciesName = _("Jetragon"),
        .cryId = CRY_NONE,
        .natDexNum = NATIONAL_DEX_JETRAGON,
        .categoryName = _("Celestial"),
        .height = 90,
        .weight = 1130,
        .description = COMPOUND_STRING(
            "A visitor from a strange world beyond\n"
            "the skies. It is destined to strike\n"
            "down any calamity in a flash of total\n"
            "destruction.\n"),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_CircledQuestionMark,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = ANIM_GROW_VIBRATE,
        .backPic = gMonBackPic_CircledQuestionMark,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 7,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_CircledQuestionMark,
        .shinyPalette = gMonShinyPalette_CircledQuestionMark,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        FOOTPRINT(QuestionMark)
        .levelUpLearnset = sNoneLevelUpLearnset,
        .teachableLearnset = sNoneTeachableLearnset,
        //.perfectIVCount = NUM_STATS,
    },

    [SPECIES_KYUREM_ULTRA] =
    {
        .baseHP        = 125,
        .baseAttack    = 170,
        .baseDefense   = 90,
        .baseSpeed     = 129,
        .baseSpAttack  = 170,
        .baseSpDefense = 90,
        .types = MON_TYPES(TYPE_DRAGON, TYPE_ICE),
        .catchRate = 3,
        .expYield = 499,
        .evYield_Attack = 1,
        .evYield_SpAttack = 1,
        .evYield_Speed = 1,
        .genderRatio = MON_GENDERLESS,
        .eggCycles = 20,
        .friendship = STANDARD_FRIENDSHIP,
        .growthRate = GROWTH_SLOW,
        .eggGroups = MON_EGG_GROUPS(EGG_GROUP_NO_EGGS_DISCOVERED),
        .abilities = { ABILITY_CRYOGENIAN, ABILITY_CRYOGENIAN, ABILITY_CRYOGENIAN },
        .bodyColor = BODY_COLOR_WHITE,
        .speciesName = _("Ultra Kyurem"),
        .cryId = CRY_KYUREM,
        .natDexNum = NATIONAL_DEX_KYUREM,
        .categoryName = _("Boundary"),
        .height = 75,
        .weight = 2300,
        .description = COMPOUND_STRING(
            "A visitor from a strange world beyond\n"
            "the skies. It is destined to strike\n"
            "down any calamity in a flash of total\n"
            "destruction.\n"),
        .pokemonScale = 256,
        .pokemonOffset = 0,
        .trainerScale = 256,
        .trainerOffset = 0,
        .frontPic = gMonFrontPic_CircledQuestionMark,
        .frontPicSize = MON_COORDS_SIZE(64, 64),
        .frontPicYOffset = 0,
        .frontAnimFrames = sAnims_SingleFramePlaceHolder,
        .frontAnimId = ANIM_GROW_VIBRATE,
        .backPic = gMonBackPic_CircledQuestionMark,
        .backPicSize = MON_COORDS_SIZE(64, 64),
        .backPicYOffset = 7,
        .backAnimId = BACK_ANIM_NONE,
        .palette = gMonPalette_CircledQuestionMark,
        .shinyPalette = gMonShinyPalette_CircledQuestionMark,
        .iconSprite = gMonIcon_QuestionMark,
        .iconPalIndex = 0,
        FOOTPRINT(QuestionMark)
        .levelUpLearnset = sKyuremLevelUpLearnset,
        .teachableLearnset = sKyuremTeachableLearnset,
    },
};
