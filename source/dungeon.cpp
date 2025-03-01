#include "dungeon.hpp"

#include "category.hpp"
#include "item_list.hpp"
#include "item_location.hpp"
#include "pool_functions.hpp"

namespace Dungeon {

DungeonInfo::DungeonInfo(std::string name_, Item* map_, Item* compass_,
                         Item* smallKey_, Item* bossKey_, u8 vanillaKeyCount_, u8 mqKeyCount_,
                         std::vector<ItemLocation*> vanillaLocations_,
                         std::vector<ItemLocation*> mqLocations_,
                         std::vector<ItemLocation*> sharedLocations_)
  : name(std::move(name_)),
    map(map_),
    compass(compass_),
    smallKey(smallKey_),
    bossKey(bossKey_),
    vanillaKeyCount(vanillaKeyCount_),
    mqKeyCount(mqKeyCount_),
    vanillaLocations(std::move(vanillaLocations_)),
    mqLocations(std::move(mqLocations_)),
    sharedLocations(std::move(sharedLocations_)) {}

DungeonInfo::~DungeonInfo() = default;

const Item& DungeonInfo::GetSmallKey() const {
  return *smallKey;
}

const Item& DungeonInfo::GetMap() const {
  return *map;
}

const Item& DungeonInfo::GetCompass() const {
  return *compass;
}

const Item& DungeonInfo::GetBossKey() const {
  return *bossKey;
}

void DungeonInfo::PlaceVanillaMap() {
  if (*map == NoItem) {
    return;
  }

  auto dungeonLocations = GetDungeonLocations();
  auto mapLocation = FilterFromPool(dungeonLocations, [](const ItemLocation* loc){ return loc->IsCategory(Category::cVanillaMap); })[0];
  PlaceItemInLocation(mapLocation, *map);
}

void DungeonInfo::PlaceVanillaCompass() {
  if (*compass == NoItem) {
    return;
  }

  auto dungeonLocations = GetDungeonLocations();
  auto compassLocation = FilterFromPool(dungeonLocations, [](const ItemLocation* loc){ return loc->IsCategory(Category::cVanillaCompass); })[0];
  PlaceItemInLocation(compassLocation, *compass);
}

void DungeonInfo::PlaceVanillaBossKey() {
  if (*bossKey == NoItem) {
    return;
  }

  auto dungeonLocations = GetDungeonLocations();
  auto bossKeyLocation = FilterFromPool(dungeonLocations, [](const ItemLocation* loc){ return loc->IsCategory(Category::cVanillaBossKey); })[0];
  PlaceItemInLocation(bossKeyLocation, *bossKey);
}

void DungeonInfo::PlaceVanillaSmallKeys() {
  if (*smallKey == NoItem) {
    return;
  }

  auto dungeonLocations = GetDungeonLocations();
  auto smallKeyLocations = FilterFromPool(dungeonLocations, [](const ItemLocation* loc){ return loc->IsCategory(Category::cVanillaSmallKey); });
  for (auto location : smallKeyLocations) {
      PlaceItemInLocation(location, *smallKey);
  }
}

//Gets the chosen dungeon locations for a playthrough (so either MQ or Vanilla)
std::vector<ItemLocation*> DungeonInfo::GetDungeonLocations() const {
  auto locations = masterQuest ? mqLocations : vanillaLocations;
  AddElementsToPool(locations, sharedLocations);
  return locations;
}

//Gets all dungeon locations (MQ + Vanilla)
std::vector<ItemLocation*> DungeonInfo::GetEveryLocation() const {
  auto locations = vanillaLocations;
  AddElementsToPool(locations, mqLocations);
  AddElementsToPool(locations, sharedLocations);
  return locations;
}

  DungeonInfo DekuTree = DungeonInfo("Deku Tree", &DekuTree_Map, &DekuTree_Compass, &NoItem, &NoItem, 0, 0, {
                            //Vanilla Locations
                            &DekuTree_MapChest,
                            &DekuTree_CompassChest,
                            &DekuTree_CompassRoomSideChest,
                            &DekuTree_BasementChest,
                            &DekuTree_SlingshotChest,
                            &DekuTree_SlingshotRoomSideChest,
                            &DekuTree_GS_BasementBackRoom,
                            &DekuTree_GS_BasementGate,
                            &DekuTree_GS_BasementVines,
                            &DekuTree_GS_CompassRoom,
                          }, {
                            //MQ Locations
                            &DekuTree_MQ_MapChest,
                            &DekuTree_MQ_CompassChest,
                            &DekuTree_MQ_SlingshotChest,
                            &DekuTree_MQ_SlingshotRoomBackChest,
                            &DekuTree_MQ_BasementChest,
                            &DekuTree_MQ_BeforeSpinningLogChest,
                            &DekuTree_MQ_AfterSpinningLogChest,
                            &DekuTree_MQ_DekuScrub,
                            &DekuTree_MQ_GS_Lobby,
                            &DekuTree_MQ_GS_CompassRoom,
                            &DekuTree_MQ_GS_BasementGravesRoom,
                            &DekuTree_MQ_GS_BasementBackRoom,
                          }, {
                            //Shared Locations
                            &DekuTree_QueenGohmaHeart,
                            &QueenGohma,
                          });

  DungeonInfo DodongosCavern = DungeonInfo("Dodongo's Cavern", &DodongosCavern_Map, &DodongosCavern_Compass, &NoItem, &NoItem, 0, 0, {
                            //Vanilla Locations
                            &DodongosCavern_MapChest,
                            &DodongosCavern_CompassChest,
                            &DodongosCavern_BombFlowerPlatformChest,
                            &DodongosCavern_BombBagChest,
                            &DodongosCavern_EndOfBridgeChest,
                            &DodongosCavern_DekuScrubLobby,
                            &DodongosCavern_DekuScrubSideRoomNearDodongos,
                            &DodongosCavern_DekuScrubNearBombBagLeft,
                            &DodongosCavern_DekuScrubNearBombBagRight,
                            &DodongosCavern_GS_VinesAboveStairs,
                            &DodongosCavern_GS_Scarecrow,
                            &DodongosCavern_GS_AlcoveAboveStairs,
                            &DodongosCavern_GS_BackRoom,
                            &DodongosCavern_GS_SideRoomNearLowerLizalfos,
                          }, {
                            //MQ Locations
                            &DodongosCavern_MQ_MapChest,
                            &DodongosCavern_MQ_BombBagChest,
                            &DodongosCavern_MQ_CompassChest,
                            &DodongosCavern_MQ_LarvaeRoomChest,
                            &DodongosCavern_MQ_TorchPuzzleRoomChest,
                            &DodongosCavern_MQ_UnderGraveChest,
                            &DodongosCavern_MQ_DekuScrubLobbyRear,
                            &DodongosCavern_MQ_DekuScrubLobbyFront,
                            &DodongosCavern_MQ_DekuScrubStaircase,
                            &DodongosCavern_MQ_DekuScrubSideRoomNearLowerLizalfos,
                            &DodongosCavern_MQ_GS_ScrubRoom,
                            &DodongosCavern_MQ_GS_SongOfTimeBlockRoom,
                            &DodongosCavern_MQ_GS_LizalfosRoom,
                            &DodongosCavern_MQ_GS_LarvaeRoom,
                            &DodongosCavern_MQ_GS_BackRoom,
                          }, {
                            //Shared Locations
                            &DodongosCavern_BossRoomChest,
                            &DodongosCavern_KingDodongoHeart,
                            &KingDodongo,
                          });

  DungeonInfo JabuJabusBelly = DungeonInfo("Jabu Jabu's Belly", &JabuJabusBelly_Map, &JabuJabusBelly_Compass, &NoItem, &NoItem, 0, 0, {
                            //Vanilla Locations
                            &JabuJabusBelly_MapChest,
                            &JabuJabusBelly_CompassChest,
                            &JabuJabusBelly_BoomerangChest,
                            &JabuJabusBelly_DekuScrub,
                            &JabuJabusBelly_GS_LobbyBasementLower,
                            &JabuJabusBelly_GS_LobbyBasementUpper,
                            &JabuJabusBelly_GS_NearBoss,
                            &JabuJabusBelly_GS_WaterSwitchRoom,
                          }, {
                            //MQ Locations
                            &JabuJabusBelly_MQ_FirstRoomSideChest,
                            &JabuJabusBelly_MQ_MapChest,
                            &JabuJabusBelly_MQ_SecondRoomLowerChest,
                            &JabuJabusBelly_MQ_CompassChest,
                            &JabuJabusBelly_MQ_SecondRoomUpperChest,
                            &JabuJabusBelly_MQ_BasementNearSwitchesChest,
                            &JabuJabusBelly_MQ_BasementNearVinesChest,
                            &JabuJabusBelly_MQ_NearBossChest,
                            &JabuJabusBelly_MQ_FallingLikeLikeRoomChest,
                            &JabuJabusBelly_MQ_BoomerangRoomSmallChest,
                            &JabuJabusBelly_MQ_BoomerangChest,
                            &JabuJabusBelly_MQ_Cow,
                            &JabuJabusBelly_MQ_GS_TailPasaranRoom,
                            &JabuJabusBelly_MQ_GS_InvisibleEnemiesRoom,
                            &JabuJabusBelly_MQ_GS_BoomerangChestRoom,
                            &JabuJabusBelly_MQ_GS_NearBoss,
                          }, {
                            //Shared Locations
                            &JabuJabusBelly_BarinadeHeart,
                            &Barinade,
                          });

  DungeonInfo ForestTemple = DungeonInfo("Forest Temple", &ForestTemple_Map, &ForestTemple_Compass, &ForestTemple_SmallKey, &ForestTemple_BossKey, 5, 6, {
                            //Vanilla Locations
                            &ForestTemple_FirstRoomChest,
                            &ForestTemple_FirstStalfosChest,
                            &ForestTemple_RaisedIslandCourtyardChest,
                            &ForestTemple_MapChest,
                            &ForestTemple_WellChest,
                            &ForestTemple_FallingCeilingRoomChest,
                            &ForestTemple_EyeSwitchChest,
                            &ForestTemple_BossKeyChest,
                            &ForestTemple_FloormasterChest,
                            &ForestTemple_BowChest,
                            &ForestTemple_RedPoeChest,
                            &ForestTemple_BluePoeChest,
                            &ForestTemple_BasementChest,
                            &ForestTemple_GS_RaisedIslandCourtyard,
                            &ForestTemple_GS_FirstRoom,
                            &ForestTemple_GS_LevelIslandCourtyard,
                            &ForestTemple_GS_Lobby,
                            &ForestTemple_GS_Basement,
                          }, {
                            //MQ Locations
                            &ForestTemple_MQ_FirstRoomChest,
                            &ForestTemple_MQ_WolfosChest,
                            &ForestTemple_MQ_BowChest,
                            &ForestTemple_MQ_RaisedIslandCourtyardLowerChest,
                            &ForestTemple_MQ_RaisedIslandCourtyardUpperChest,
                            &ForestTemple_MQ_WellChest,
                            &ForestTemple_MQ_MapChest,
                            &ForestTemple_MQ_CompassChest,
                            &ForestTemple_MQ_FallingCeilingRoomChest,
                            &ForestTemple_MQ_BasementChest,
                            &ForestTemple_MQ_RedeadChest,
                            &ForestTemple_MQ_BossKeyChest,
                            &ForestTemple_MQ_GS_FirstHallway,
                            &ForestTemple_MQ_GS_BlockPushRoom,
                            &ForestTemple_MQ_GS_RaisedIslandCourtyard,
                            &ForestTemple_MQ_GS_LevelIslandCourtyard,
                            &ForestTemple_MQ_GS_Well,
                          }, {
                            //Shared Locations
                            &ForestTemple_PhantomGanonHeart,
                            &PhantomGanon,
                          });

  DungeonInfo FireTemple = DungeonInfo("Fire Temple", &FireTemple_Map, &FireTemple_Compass, &FireTemple_SmallKey, &FireTemple_BossKey, 8, 5, {
                            //Vanilla Locations
                            &FireTemple_NearBossChest,
                            &FireTemple_FlareDancerChest,
                            &FireTemple_BossKeyChest,
                            &FireTemple_BigLavaRoomBlockedDoorChest,
                            &FireTemple_BigLavaRoomLowerOpenDoorChest,
                            &FireTemple_BoulderMazeLowerChest,
                            &FireTemple_BoulderMazeUpperChest,
                            &FireTemple_BoulderMazeSideRoomChest,
                            &FireTemple_BoulderMazeShortcutChest,
                            &FireTemple_ScarecrowChest,
                            &FireTemple_MapChest,
                            &FireTemple_CompassChest,
                            &FireTemple_HighestGoronChest,
                            &FireTemple_MegatonHammerChest,
                            &FireTemple_GS_SongOfTimeRoom,
                            &FireTemple_GS_BossKeyLoop,
                            &FireTemple_GS_BoulderMaze,
                            &FireTemple_GS_ScarecrowTop,
                            &FireTemple_GS_ScarecrowClimb,
                          }, {
                            //MQ Locations
                            &FireTemple_MQ_NearBossChest,
                            &FireTemple_MQ_MegatonHammerChest,
                            &FireTemple_MQ_CompassChest,
                            &FireTemple_MQ_LizalfosMazeLowerChest,
                            &FireTemple_MQ_LizalfosMazeUpperChest,
                            &FireTemple_MQ_ChestOnFire,
                            &FireTemple_MQ_MapRoomSideChest,
                            &FireTemple_MQ_MapChest,
                            &FireTemple_MQ_BossKeyChest,
                            &FireTemple_MQ_BigLavaRoomBlockedDoorChest,
                            &FireTemple_MQ_LizalfosMazeSideRoomChest,
                            &FireTemple_MQ_FreestandingKey,
                            &FireTemple_MQ_GS_AboveFireWallMaze,
                            &FireTemple_MQ_GS_FireWallMazeCenter,
                            &FireTemple_MQ_GS_BigLavaRoomOpenDoor,
                            &FireTemple_MQ_GS_FireWallMazeSideRoom,
                            &FireTemple_MQ_GS_SkullOnFire,
                          }, {
                            //Shared Locations
                            &FireTemple_VolvagiaHeart,
                            &Volvagia,
                          });

  DungeonInfo WaterTemple = DungeonInfo("Water Temple", &WaterTemple_Map, &WaterTemple_Compass, &WaterTemple_SmallKey, &WaterTemple_BossKey, 6, 2, {
                            //Vanilla Locations
                            &WaterTemple_MapChest,
                            &WaterTemple_CompassChest,
                            &WaterTemple_TorchesChest,
                            &WaterTemple_DragonChest,
                            &WaterTemple_CentralBowTargetChest,
                            &WaterTemple_CentralPillarChest,
                            &WaterTemple_CrackedWallChest,
                            &WaterTemple_BossKeyChest,
                            &WaterTemple_LongshotChest,
                            &WaterTemple_RiverChest,
                            &WaterTemple_GS_BehindGate,
                            &WaterTemple_GS_FallingPlatformRoom,
                            &WaterTemple_GS_CentralPillar,
                            &WaterTemple_GS_NearBossKeyChest,
                            &WaterTemple_GS_River,
                          }, {
                            //MQ Locations
                            &WaterTemple_MQ_CentralPillarChest,
                            &WaterTemple_MQ_BossKeyChest,
                            &WaterTemple_MQ_LongshotChest,
                            &WaterTemple_MQ_CompassChest,
                            &WaterTemple_MQ_MapChest,
                            &WaterTemple_MQ_FreestandingKey,
                            &WaterTemple_MQ_GS_BeforeUpperWaterSwitch,
                            &WaterTemple_MQ_GS_FreestandingKeyArea,
                            &WaterTemple_MQ_GS_LizalfosHallway,
                            &WaterTemple_MQ_GS_River,
                            &WaterTemple_MQ_GS_TripleWallTorch,
                          }, {
                            //Shared Locations
                            &WaterTemple_MorphaHeart,
                            &Morpha,
                          });

  DungeonInfo SpiritTemple = DungeonInfo("Spirit Temple", &SpiritTemple_Map, &SpiritTemple_Compass, &SpiritTemple_SmallKey, &SpiritTemple_BossKey, 5, 7, {
                            //Vanilla Locations
                            &SpiritTemple_ChildBridgeChest,
                            &SpiritTemple_ChildEarlyTorchesChest,
                            &SpiritTemple_CompassChest,
                            &SpiritTemple_EarlyAdultRightChest,
                            &SpiritTemple_FirstMirrorLeftChest,
                            &SpiritTemple_FirstMirrorRightChest,
                            &SpiritTemple_MapChest,
                            &SpiritTemple_ChildClimbNorthChest,
                            &SpiritTemple_ChildClimbEastChest,
                            &SpiritTemple_SunBlockRoomChest,
                            &SpiritTemple_StatueRoomHandChest,
                            &SpiritTemple_StatueRoomNortheastChest,
                            &SpiritTemple_NearFourArmosChest,
                            &SpiritTemple_HallwayLeftInvisibleChest,
                            &SpiritTemple_HallwayRightInvisibleChest,
                            &SpiritTemple_BossKeyChest,
                            &SpiritTemple_TopmostChest,
                            &SpiritTemple_GS_HallAfterSunBlockRoom,
                            &SpiritTemple_GS_BoulderRoom,
                            &SpiritTemple_GS_Lobby,
                            &SpiritTemple_GS_SunOnFloorRoom,
                            &SpiritTemple_GS_MetalFence,
                          }, {
                            //MQ Locations
                            &SpiritTemple_MQ_EntranceFrontLeftChest,
                            &SpiritTemple_MQ_EntranceBackRightChest,
                            &SpiritTemple_MQ_EntranceFrontRightChest,
                            &SpiritTemple_MQ_EntranceBackLeftChest,
                            &SpiritTemple_MQ_ChildHammerSwitchChest,
                            &SpiritTemple_MQ_MapChest,
                            &SpiritTemple_MQ_MapRoomEnemyChest,
                            &SpiritTemple_MQ_ChildClimbNorthChest,
                            &SpiritTemple_MQ_ChildClimbSouthChest,
                            &SpiritTemple_MQ_CompassChest,
                            &SpiritTemple_MQ_StatueRoomLullabyChest,
                            &SpiritTemple_MQ_StatueRoomInvisibleChest,
                            &SpiritTemple_MQ_SilverBlockHallwayChest,
                            &SpiritTemple_MQ_SunBlockRoomChest,
                            &SpiritTemple_MQ_SymphonyRoomChest,
                            &SpiritTemple_MQ_LeeverRoomChest,
                            &SpiritTemple_MQ_BeamosRoomChest,
                            &SpiritTemple_MQ_ChestSwitchChest,
                            &SpiritTemple_MQ_BossKeyChest,
                            &SpiritTemple_MQ_MirrorPuzzleInvisibleChest,
                            &SpiritTemple_MQ_GS_SymphonyRoom,
                            &SpiritTemple_MQ_GS_LeeverRoom,
                            &SpiritTemple_MQ_GS_NineThronesRoomWest,
                            &SpiritTemple_MQ_GS_NineThronesRoomNorth,
                            &SpiritTemple_MQ_GS_SunBlockRoom,
                          }, {
                            //Shared Locations
                            &SpiritTemple_SilverGauntletsChest,
                            &SpiritTemple_MirrorShieldChest,
                            &SpiritTemple_TwinrovaHeart,
                            &Twinrova,
                          });

  DungeonInfo ShadowTemple = DungeonInfo("Shadow Temple", &ShadowTemple_Map, &ShadowTemple_Compass, &ShadowTemple_SmallKey, &ShadowTemple_BossKey, 5, 6, {
                            //Vanilla Locations
                            &ShadowTemple_MapChest,
                            &ShadowTemple_HoverBootsChest,
                            &ShadowTemple_CompassChest,
                            &ShadowTemple_EarlySilverRupeeChest,
                            &ShadowTemple_InvisibleBladesVisibleChest,
                            &ShadowTemple_InvisibleBladesInvisibleChest,
                            &ShadowTemple_FallingSpikesLowerChest,
                            &ShadowTemple_FallingSpikesUpperChest,
                            &ShadowTemple_FallingSpikesSwitchChest,
                            &ShadowTemple_InvisibleSpikesChest,
                            &ShadowTemple_WindHintChest,
                            &ShadowTemple_AfterWindEnemyChest,
                            &ShadowTemple_AfterWindHiddenChest,
                            &ShadowTemple_SpikeWallsLeftChest,
                            &ShadowTemple_BossKeyChest,
                            &ShadowTemple_InvisibleFloormasterChest,
                            &ShadowTemple_FreestandingKey,
                            &ShadowTemple_GS_SingleGiantPot,
                            &ShadowTemple_GS_FallingSpikesRoom,
                            &ShadowTemple_GS_TripleGiantPot,
                            &ShadowTemple_GS_LikeLikeRoom,
                            &ShadowTemple_GS_NearShip,
                          }, {
                            //MQ Locations
                            &ShadowTemple_MQ_CompassChest,
                            &ShadowTemple_MQ_HoverBootsChest,
                            &ShadowTemple_MQ_EarlyGibdosChest,
                            &ShadowTemple_MQ_MapChest,
                            &ShadowTemple_MQ_BeamosSilverRupeesChest,
                            &ShadowTemple_MQ_FallingSpikesSwitchChest,
                            &ShadowTemple_MQ_FallingSpikesLowerChest,
                            &ShadowTemple_MQ_FallingSpikesUpperChest,
                            &ShadowTemple_MQ_InvisibleSpikesChest,
                            &ShadowTemple_MQ_BossKeyChest,
                            &ShadowTemple_MQ_SpikeWallsLeftChest,
                            &ShadowTemple_MQ_StalfosRoomChest,
                            &ShadowTemple_MQ_InvisibleBladesInvisibleChest,
                            &ShadowTemple_MQ_InvisibleBladesVisibleChest,
                            &ShadowTemple_MQ_BombFlowerChest,
                            &ShadowTemple_MQ_WindHintChest,
                            &ShadowTemple_MQ_AfterWindHiddenChest,
                            &ShadowTemple_MQ_AfterWindEnemyChest,
                            &ShadowTemple_MQ_NearShipInvisibleChest,
                            &ShadowTemple_MQ_FreestandingKey,
                            &ShadowTemple_MQ_GS_FallingSpikesRoom,
                            &ShadowTemple_MQ_GS_WindHintRoom,
                            &ShadowTemple_MQ_GS_AfterWind,
                            &ShadowTemple_MQ_GS_AfterShip,
                            &ShadowTemple_MQ_GS_NearBoss,
                          }, {
                            //Shared Locations
                            &ShadowTemple_BongoBongoHeart,
                            &BongoBongo,
                          });

  DungeonInfo BottomOfTheWell = DungeonInfo("Bottom of the Well", &BottomOfTheWell_Map, &BottomOfTheWell_Compass, &BottomOfTheWell_SmallKey, &NoItem, 3, 2, {
                            //Vanilla Locations
                            &BottomOfTheWell_FrontLeftFakeWallChest,
                            &BottomOfTheWell_FrontCenterBombableChest,
                            &BottomOfTheWell_RightBottomFakeWallChest,
                            &BottomOfTheWell_CompassChest,
                            &BottomOfTheWell_CenterSkulltulaChest,
                            &BottomOfTheWell_BackLeftBombableChest,
                            &BottomOfTheWell_LensOfTruthChest,
                            &BottomOfTheWell_InvisibleChest,
                            &BottomOfTheWell_UnderwaterFrontChest,
                            &BottomOfTheWell_UnderwaterLeftChest,
                            &BottomOfTheWell_MapChest,
                            &BottomOfTheWell_FireKeeseChest,
                            &BottomOfTheWell_LikeLikeChest,
                            &BottomOfTheWell_FreestandingKey,
                            &BottomOfTheWell_GS_LikeLikeCage,
                            &BottomOfTheWell_GS_EastInnerRoom,
                            &BottomOfTheWell_GS_WestInnerRoom,
                          }, {
                            //MQ Locations
                            &BottomOfTheWell_MQ_MapChest,
                            &BottomOfTheWell_MQ_LensOfTruthChest,
                            &BottomOfTheWell_MQ_CompassChest,
                            &BottomOfTheWell_MQ_DeadHandFreestandingKey,
                            &BottomOfTheWell_MQ_EastInnerRoomFreestandingKey,
                            &BottomOfTheWell_MQ_GS_Basement,
                            &BottomOfTheWell_MQ_GS_CoffinRoom,
                            &BottomOfTheWell_MQ_GS_WestInnerRoom,
                          }, {});

  DungeonInfo IceCavern = DungeonInfo("Ice Cavern", &IceCavern_Map, &IceCavern_Compass, &NoItem, &NoItem, 0, 0, {
                            //Vanilla Locations
                            &IceCavern_MapChest,
                            &IceCavern_CompassChest,
                            &IceCavern_IronBootsChest,
                            &IceCavern_FreestandingPoH,
                            &IceCavern_GS_PushBlockRoom,
                            &IceCavern_GS_SpinningScytheRoom,
                            &IceCavern_GS_HeartPieceRoom,
                          }, {
                            //MQ Locations
                            &IceCavern_MQ_IronBootsChest,
                            &IceCavern_MQ_CompassChest,
                            &IceCavern_MQ_MapChest,
                            &IceCavern_MQ_FreestandingPoH,
                            &IceCavern_MQ_GS_Scarecrow,
                            &IceCavern_MQ_GS_IceBlock,
                            &IceCavern_MQ_GS_RedIce,
                          }, {
                            //Shared Locations
                            &SheikInIceCavern,
                          });

  DungeonInfo GerudoTrainingGrounds = DungeonInfo("Gerudo Training Grounds", &NoItem, &NoItem, &GerudoTrainingGrounds_SmallKey, &NoItem, 9, 3, {
                            //Vanilla Locations
                            &GerudoTrainingGrounds_LobbyLeftChest,
                            &GerudoTrainingGrounds_LobbyRightChest,
                            &GerudoTrainingGrounds_StalfosChest,
                            &GerudoTrainingGrounds_BeamosChest,
                            &GerudoTrainingGrounds_HiddenCeilingChest,
                            &GerudoTrainingGrounds_MazePathFirstChest,
                            &GerudoTrainingGrounds_MazePathSecondChest,
                            &GerudoTrainingGrounds_MazePathThirdChest,
                            &GerudoTrainingGrounds_MazePathFinalChest,
                            &GerudoTrainingGrounds_MazeRightCentralChest,
                            &GerudoTrainingGrounds_MazeRightSideChest,
                            &GerudoTrainingGrounds_UnderwaterSilverRupeeChest,
                            &GerudoTrainingGrounds_HammerRoomClearChest,
                            &GerudoTrainingGrounds_HammerRoomSwitchChest,
                            &GerudoTrainingGrounds_EyeStatueChest,
                            &GerudoTrainingGrounds_NearScarecrowChest,
                            &GerudoTrainingGrounds_BeforeHeavyBlockChest,
                            &GerudoTrainingGrounds_HeavyBlockFirstChest,
                            &GerudoTrainingGrounds_HeavyBlockSecondChest,
                            &GerudoTrainingGrounds_HeavyBlockThirdChest,
                            &GerudoTrainingGrounds_HeavyBlockFourthChest,
                            &GerudoTrainingGrounds_FreestandingKey,
                          }, {
                            //MQ Locations
                            &GerudoTrainingGrounds_MQ_LobbyRightChest,
                            &GerudoTrainingGrounds_MQ_LobbyLeftChest,
                            &GerudoTrainingGrounds_MQ_FirstIronKnuckleChest,
                            &GerudoTrainingGrounds_MQ_BeforeHeavyBlockChest,
                            &GerudoTrainingGrounds_MQ_EyeStatueChest,
                            &GerudoTrainingGrounds_MQ_FlameCircleChest,
                            &GerudoTrainingGrounds_MQ_SecondIronKnuckleChest,
                            &GerudoTrainingGrounds_MQ_DinolfosChest,
                            &GerudoTrainingGrounds_MQ_IceArrowsChest,
                            &GerudoTrainingGrounds_MQ_MazeRightCentralChest,
                            &GerudoTrainingGrounds_MQ_MazePathFirstChest,
                            &GerudoTrainingGrounds_MQ_MazeRightSideChest,
                            &GerudoTrainingGrounds_MQ_MazePathThirdChest,
                            &GerudoTrainingGrounds_MQ_MazePathSecondChest,
                            &GerudoTrainingGrounds_MQ_HiddenCeilingChest,
                            &GerudoTrainingGrounds_MQ_UnderwaterSilverRupeeChest,
                            &GerudoTrainingGrounds_MQ_HeavyBlockChest,
                          }, {});

  DungeonInfo GanonsCastle = DungeonInfo("Ganon's Castle", &NoItem, &NoItem, &GanonsCastle_SmallKey, &GanonsCastle_BossKey, 2, 3, {
                            //Vanilla Locations
                            &GanonsCastle_ForestTrialChest,
                            &GanonsCastle_WaterTrialLeftChest,
                            &GanonsCastle_WaterTrialRightChest,
                            &GanonsCastle_ShadowTrialFrontChest,
                            &GanonsCastle_ShadowTrialGoldenGauntletsChest,
                            &GanonsCastle_SpiritTrialCrystalSwitchChest,
                            &GanonsCastle_SpiritTrialInvisibleChest,
                            &GanonsCastle_LightTrialFirstLeftChest,
                            &GanonsCastle_LightTrialSecondLeftChest,
                            &GanonsCastle_LightTrialThirdLeftChest,
                            &GanonsCastle_LightTrialFirstRightChest,
                            &GanonsCastle_LightTrialSecondRightChest,
                            &GanonsCastle_LightTrialThirdRightChest,
                            &GanonsCastle_LightTrialInvisibleEnemiesChest,
                            &GanonsCastle_LightTrialLullabyChest,
                            &GanonsCastle_DekuScrubLeft,
                            &GanonsCastle_DekuScrubCenterLeft,
                            &GanonsCastle_DekuScrubCenterRight,
                            &GanonsCastle_DekuScrubRight,
                          }, {
                            //MQ Locations
                            &GanonsCastle_MQ_WaterTrialChest,
                            &GanonsCastle_MQ_ForestTrialEyeSwitchChest,
                            &GanonsCastle_MQ_ForestTrialFrozenEyeSwitchChest,
                            &GanonsCastle_MQ_LightTrialLullabyChest,
                            &GanonsCastle_MQ_ShadowTrialBombFlowerChest,
                            &GanonsCastle_MQ_ShadowTrialEyeSwitchChest,
                            &GanonsCastle_MQ_SpiritTrialGoldenGauntletsChest,
                            &GanonsCastle_MQ_SpiritTrialSunBackRightChest,
                            &GanonsCastle_MQ_SpiritTrialSunBackLeftChest,
                            &GanonsCastle_MQ_SpiritTrialSunFrontLeftChest,
                            &GanonsCastle_MQ_SpiritTrialFirstChest,
                            &GanonsCastle_MQ_SpiritTrialInvisibleChest,
                            &GanonsCastle_MQ_ForestTrialFreestandingKey,
                            &GanonsCastle_MQ_DekuScrubRight,
                            &GanonsCastle_MQ_DekuScrubCenterLeft,
                            &GanonsCastle_MQ_DekuScrubCenter,
                            &GanonsCastle_MQ_DekuScrubCenterRight,
                            &GanonsCastle_MQ_DekuScrubLeft,
                          }, {
                            //Shared Locations
                            &GanonsCastle_BossKeyChest,
                            &Ganon,
                          });

  const DungeonArray dungeonList = {
    &DekuTree,
    &DodongosCavern,
    &JabuJabusBelly,
    &ForestTemple,
    &FireTemple,
    &WaterTemple,
    &SpiritTemple,
    &ShadowTemple,
    &BottomOfTheWell,
    &IceCavern,
    &GerudoTrainingGrounds,
    &GanonsCastle,
  };

} //namespace Dungeon
