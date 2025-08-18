#include <Windows.h>
#include <d2d1.h>
#include <map>
#include <chrono>
#include <vector>
#include <wincodec.h>
#include <chrono>
#include <math.h>
#include <d2d1effects.h>
#include <d2d1_1.h>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <random>
#include <unordered_map>
#include <thread>
#include <unordered_set>
#include <mutex>
#include <mmsystem.h>
#include <set>
#include <ctime>

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "windowscodecs.lib")
#pragma comment(lib, "winmm.lib") 

#define VK_L 0x4C
#define VK_Q 0x51
#define VK_S 0x53
#define pi 3.141592653589793238462643383279502884197

void TripErrorMissingFile(LPCWSTR file);


//---------
// Globals
//---------

// Filenames
// Contains all filenames necessary for the game to run. Condensed into variables to improve readability in later code.
// Made a struct just so I can collapse when I have more files later
struct {
    LPCWSTR playerFrame1 = L"Sprites\\Ship\\Ship1.png";
    LPCWSTR playerFrame2 = L"Sprites\\Ship\\Ship2.png";
    LPCWSTR background = L"Sprites\\Background\\Background.png";
    LPCWSTR playerRedLightffect1 = L"Sprites\\Ship\\Ship Effects\\Red_Light_1.png";
    LPCWSTR playerRedLightffect2 = L"Sprites\\Ship\\Ship Effects\\Red_Light_2.png";
    LPCWSTR playerRedLightffect3 = L"Sprites\\Ship\\Ship Effects\\Red_Light_3.png";
    LPCWSTR playerRedLightffect4 = L"Sprites\\Ship\\Ship Effects\\Red_Light_4.png";
    LPCWSTR playerRedLightffect5 = L"Sprites\\Ship\\Ship Effects\\Red_Light_5.png";
    LPCWSTR playerRedLightffect6 = L"Sprites\\Ship\\Ship Effects\\Red_Light_6.png";
    LPCWSTR playerRedLightffect7 = L"Sprites\\Ship\\Ship Effects\\Red_Light_7.png";
    LPCWSTR playerRedLightffect8 = L"Sprites\\Ship\\Ship Effects\\Red_Light_8.png";
    LPCWSTR playerRedLightffect9 = L"Sprites\\Ship\\Ship Effects\\Red_Light_9.png";
    LPCWSTR asteroid1 = L"Sprites\\Environment\\Asteroid_1.png";
    LPCWSTR pause = L"Sprites\\Menu\\Pause.png";
    LPCWSTR pauseBackground = L"Sprites\\Menu\\Pause_Background.png";
    LPCWSTR basicShotEffect1 = L"Sprites\\Ship\\Ship Effects\\Basic_Shot_Effect_1.png";
    LPCWSTR basicShotEffect2 = L"Sprites\\Ship\\Ship Effects\\Basic_Shot_Effect_2.png";
    LPCWSTR basicShotEffect3 = L"Sprites\\Ship\\Ship Effects\\Basic_Shot_Effect_3.png";
    LPCWSTR basicShotEffect4 = L"Sprites\\Ship\\Ship Effects\\Basic_Shot_Effect_4.png";
    LPCWSTR basicShotEffect5 = L"Sprites\\Ship\\Ship Effects\\Basic_Shot_Effect_5.png";
    LPCWSTR basicShotEffectBlue1 = L"Sprites\\Ship\\Ship Effects\\Basic_Shot_Effect_Blue_1.png";
    LPCWSTR basicShotEffectBlue2 = L"Sprites\\Ship\\Ship Effects\\Basic_Shot_Effect_Blue_2.png";
    LPCWSTR basicShotEffectBlue3 = L"Sprites\\Ship\\Ship Effects\\Basic_Shot_Effect_Blue_3.png";
    LPCWSTR basicShotEffectBlue4 = L"Sprites\\Ship\\Ship Effects\\Basic_Shot_Effect_Blue_4.png";
    LPCWSTR basicShotEffectBlue5 = L"Sprites\\Ship\\Ship Effects\\Basic_Shot_Effect_Blue_5.png";
    LPCWSTR basicShotEffectPurple1 = L"Sprites\\Ship\\Ship Effects\\Basic_Shot_Effect_Purple_1.png";
    LPCWSTR basicShotEffectPurple2 = L"Sprites\\Ship\\Ship Effects\\Basic_Shot_Effect_Purple_2.png";
    LPCWSTR basicShotEffectPurple3 = L"Sprites\\Ship\\Ship Effects\\Basic_Shot_Effect_Purple_3.png";
    LPCWSTR basicShotEffectPurple4 = L"Sprites\\Ship\\Ship Effects\\Basic_Shot_Effect_Purple_4.png";
    LPCWSTR basicShotEffectPurple5 = L"Sprites\\Ship\\Ship Effects\\Basic_Shot_Effect_Purple_5.png";
    LPCWSTR basicShotDefault = L"Sprites\\Projectiles\\Basic_Shot_Default.png";
    LPCWSTR basicShotPurple = L"Sprites\\Projectiles\\Basic_Shot_Purple.png";
    LPCWSTR basicShotBlue = L"Sprites\\Projectiles\\Basic_Shot_Blue.png";
    LPCWSTR hitBox = L"Sprites\\Utilities\\hitBox.png";
    LPCWSTR hurtBox = L"Sprites\\Utilities\\hurtBox.png";
    LPCWSTR enemyShip1 = L"Sprites\\Enemies\\Enemy_Ship_1.png";
    LPCWSTR enemyShip1Damaged = L"Sprites\\Enemies\\Enemy_Ship_1_Damaged.png";
    LPCWSTR explosion1 = L"Sprites\\Effects\\Explosion_1.png";
    LPCWSTR explosion2 = L"Sprites\\Effects\\Explosion_2.png";
    LPCWSTR explosion3 = L"Sprites\\Effects\\Explosion_3.png";
    LPCWSTR explosion4 = L"Sprites\\Effects\\Explosion_4.png";
    LPCWSTR doubleShotPickup = L"Sprites\\Pickups\\Double_Shot_Icon.png";
    LPCWSTR base = L"Sprites\\Enemies\\Base_Outside_1.png";
    LPCWSTR brody_the_toad = L"Sprites\\Enemies\\Brody the Toad.png";
    LPCWSTR brody_the_toad_pain = L"Sprites\\Enemies\\Brody the Toad pain.png";
    LPCWSTR turret = L"Sprites\\Enemies\\Turret.png";
    LPCWSTR turret_Shader = L"Sprites\\Enemies\\Turret_Shader.png";
    LPCWSTR turret_Damaged = L"Sprites\\Enemies\\Turret_Damaged.png";
    LPCWSTR shield_Generator = L"Sprites\\Enemies\\Shield_Generator.png";
    LPCWSTR shield_Generator_Damaged = L"Sprites\\Enemies\\Shield_Generator_Damaged.png";
    LPCWSTR base_Door = L"Sprites\\Environment\\Base_Door.png";
    LPCWSTR base_Interior = L"Sprites\\Environment\\Base_Interior.png";
    LPCWSTR base_Core = L"Sprites\\Environment\\Base_Core.png";
    LPCWSTR entrance = L"Sprites\\Environment\\Entrance.png";
    LPCWSTR status_Bar = L"Sprites\\Menu\\Status_Bar.png";
    LPCWSTR health_Bar_Top = L"Sprites\\Menu\\Health_Bar_Top.png";
    LPCWSTR health_Bar_Bottom = L"Sprites\\Menu\\Health_Bar_Bottom.png";
    LPCWSTR boost_Bar_top = L"Sprites\\Menu\\Boost_Bar_Top.png";
    LPCWSTR boost_Bar_bottom = L"Sprites\\Menu\\Boost_Bar_Bottom.png";
    LPCWSTR player_Death_Animation_1 = L"Sprites\\Ship\\Player_Death_Animation_1.png";
    LPCWSTR player_Death_Animation_2 = L"Sprites\\Ship\\Player_Death_Animation_2.png";
    LPCWSTR player_Death_Animation_3 = L"Sprites\\Ship\\Player_Death_Animation_3.png";
    LPCWSTR jewel_Blue = L"Sprites\\Pickups\\Jewel_Blue.png";
    LPCWSTR jewel_Green = L"Sprites\\Pickups\\Jewel_Green.png";
    LPCWSTR jewel_Purple = L"Sprites\\Pickups\\Jewel_Purple.png";
    LPCWSTR jewel_Red = L"Sprites\\Pickups\\Jewel_Red.png";
    LPCWSTR jewel_Silver = L"Sprites\\Pickups\\Jewel_Silver.png";
    LPCWSTR jewel_Yellow = L"Sprites\\Pickups\\Jewel_Yellow.png";
    LPCWSTR font_0 = L"Sprites\\Fonts\\font_0.png";
    LPCWSTR font_1 = L"Sprites\\Fonts\\font_1.png";
    LPCWSTR font_2 = L"Sprites\\Fonts\\font_2.png";
    LPCWSTR font_3 = L"Sprites\\Fonts\\font_3.png";
    LPCWSTR font_4 = L"Sprites\\Fonts\\font_4.png";
    LPCWSTR font_5 = L"Sprites\\Fonts\\font_5.png";
    LPCWSTR font_6 = L"Sprites\\Fonts\\font_6.png";
    LPCWSTR font_7 = L"Sprites\\Fonts\\font_7.png";
    LPCWSTR font_8 = L"Sprites\\Fonts\\font_8.png";
    LPCWSTR font_9 = L"Sprites\\Fonts\\font_9.png";
    LPCWSTR hp_pickup_1 = L"Sprites\\Pickups\\Health_Pickup_1.png";
    LPCWSTR hp_pickup_2 = L"Sprites\\Pickups\\Health_Pickup_2.png";
    LPCWSTR hp_pickup_3 = L"Sprites\\Pickups\\Health_Pickup_3.png";
    LPCWSTR bomber_drone = L"Sprites\\Enemies\\Bomber_Drone_1.png";
    LPCWSTR drone_Shot_1 = L"Sprites\\Projectiles\\Bomber_Drone_Shot_1.png";
    LPCWSTR drone_Shot_2 = L"Sprites\\Projectiles\\Bomber_Drone_Shot_2.png";
    LPCWSTR drone_Shot_3 = L"Sprites\\Projectiles\\Bomber_Drone_Shot_3.png";
    LPCWSTR drone_Shot_4 = L"Sprites\\Projectiles\\Bomber_Drone_Shot_4.png";
    LPCWSTR drone_Shot_5 = L"Sprites\\Projectiles\\Bomber_Drone_Shot_5.png";
    LPCWSTR drone_Shot_6 = L"Sprites\\Projectiles\\Bomber_Drone_Shot_6.png";
    LPCWSTR drone_Shot_7 = L"Sprites\\Projectiles\\Bomber_Drone_Shot_7.png";
    LPCWSTR asteroid_2 = L"Sprites\\Environment\\Asteroid_2.png";
    LPCWSTR map_frame = L"Sprites\\Menu\\Map_Frame.png";
    LPCWSTR base_icon = L"Sprites\\Menu\\Base_Icon.png";
    LPCWSTR boss_icon = L"Sprites\\Menu\\Boss_Icon.png";
    LPCWSTR player_tilt_left = L"Sprites\\Ship\\Player_Tilt_Left.png";
    LPCWSTR player_tilt_right = L"Sprites\\Ship\\Player_Tilt_Right.png";
    LPCWSTR player_sideways_l = L"Sprites\\Ship\\Player_Sideways_L.png";
    LPCWSTR player_sideways_r = L"Sprites\\Ship\\Player_Sideways_R.png";
    LPCWSTR player_upside_tilted_l = L"Sprites\\Ship\\Player_upside_tilted_L.png";
    LPCWSTR player_upside_tilted_r = L"Sprites\\Ship\\Player_upside_tilted_R.png";
    LPCWSTR title_screen = L"Sprites\\Menu\\Title_Screen.png";
    LPCWSTR save_file_panel = L"Sprites\\Menu\\Save_File_Panel.png";
    LPCWSTR shrunken_repair_screen = L"Sprites\\Menu\\Shrunken_Repair_Screen.png";
    LPCWSTR lower_a = L"Sprites\\Fonts\\lower_a.png";
    LPCWSTR lower_b = L"Sprites\\Fonts\\lower_b.png";
    LPCWSTR lower_c = L"Sprites\\Fonts\\lower_c.png";
    LPCWSTR lower_d = L"Sprites\\Fonts\\lower_d.png";
    LPCWSTR lower_e = L"Sprites\\Fonts\\lower_e.png";
    LPCWSTR lower_f = L"Sprites\\Fonts\\lower_f.png";
    LPCWSTR lower_g = L"Sprites\\Fonts\\lower_g.png";
    LPCWSTR lower_h = L"Sprites\\Fonts\\lower_h.png";
    LPCWSTR lower_i = L"Sprites\\Fonts\\lower_i.png";
    LPCWSTR lower_j = L"Sprites\\Fonts\\lower_j.png";
    LPCWSTR lower_k = L"Sprites\\Fonts\\lower_k.png";
    LPCWSTR lower_l = L"Sprites\\Fonts\\lower_l.png";
    LPCWSTR lower_m = L"Sprites\\Fonts\\lower_m.png";
    LPCWSTR lower_n = L"Sprites\\Fonts\\lower_n.png";
    LPCWSTR lower_o = L"Sprites\\Fonts\\lower_o.png";
    LPCWSTR lower_p = L"Sprites\\Fonts\\lower_p.png";
    LPCWSTR lower_q = L"Sprites\\Fonts\\lower_q.png";
    LPCWSTR lower_r = L"Sprites\\Fonts\\lower_r.png";
    LPCWSTR lower_s = L"Sprites\\Fonts\\lower_s.png";
    LPCWSTR lower_t = L"Sprites\\Fonts\\lower_t.png";
    LPCWSTR lower_u = L"Sprites\\Fonts\\lower_u.png";
    LPCWSTR lower_v = L"Sprites\\Fonts\\lower_v.png";
    LPCWSTR lower_w = L"Sprites\\Fonts\\lower_w.png";
    LPCWSTR lower_x = L"Sprites\\Fonts\\lower_x.png";
    LPCWSTR lower_y = L"Sprites\\Fonts\\lower_y.png";
    LPCWSTR lower_z = L"Sprites\\Fonts\\lower_z.png";
    LPCWSTR upper_a = L"Sprites\\Fonts\\Capital_A.png";
    LPCWSTR upper_b = L"Sprites\\Fonts\\Capital_B.png";
    LPCWSTR upper_c = L"Sprites\\Fonts\\Capital_C.png";
    LPCWSTR upper_d = L"Sprites\\Fonts\\Capital_D.png";
    LPCWSTR upper_e = L"Sprites\\Fonts\\Capital_E.png";
    LPCWSTR upper_f = L"Sprites\\Fonts\\Capital_F.png";
    LPCWSTR upper_g = L"Sprites\\Fonts\\Capital_G.png";
    LPCWSTR upper_h = L"Sprites\\Fonts\\Capital_H.png";
    LPCWSTR upper_i = L"Sprites\\Fonts\\Capital_I.png";
    LPCWSTR upper_j = L"Sprites\\Fonts\\Capital_J.png";
    LPCWSTR upper_k = L"Sprites\\Fonts\\Capital_K.png";
    LPCWSTR upper_l = L"Sprites\\Fonts\\Capital_L.png";
    LPCWSTR upper_m = L"Sprites\\Fonts\\Capital_M.png";
    LPCWSTR upper_n = L"Sprites\\Fonts\\Capital_N.png";
    LPCWSTR upper_o = L"Sprites\\Fonts\\Capital_O.png";
    LPCWSTR upper_p = L"Sprites\\Fonts\\Capital_P.png";
    LPCWSTR upper_q = L"Sprites\\Fonts\\Capital_Q.png";
    LPCWSTR upper_r = L"Sprites\\Fonts\\Capital_R.png";
    LPCWSTR upper_s = L"Sprites\\Fonts\\Capital_S.png";
    LPCWSTR upper_t = L"Sprites\\Fonts\\Capital_T.png";
    LPCWSTR upper_u = L"Sprites\\Fonts\\Capital_U.png";
    LPCWSTR upper_v = L"Sprites\\Fonts\\Capital_V.png";
    LPCWSTR upper_w = L"Sprites\\Fonts\\Capital_W.png";
    LPCWSTR upper_x = L"Sprites\\Fonts\\Capital_X.png";
    LPCWSTR upper_y = L"Sprites\\Fonts\\Capital_Y.png";
    LPCWSTR upper_z = L"Sprites\\Fonts\\Capital_Z.png";
    LPCWSTR semicolon = L"Sprites\\Fonts\\semicolon.png";
    LPCWSTR selec_arrow = L"Sprites\\Menu\\Selection_Arrow.png";
    LPCWSTR save_station_1 = L"Sprites\\Environment\\Save Station_1.png";
    LPCWSTR save_station_2 = L"Sprites\\Environment\\Save Station_2.png";
    LPCWSTR save_station_3 = L"Sprites\\Environment\\Save Station_3.png";
    LPCWSTR save_station_4 = L"Sprites\\Environment\\Save Station_4.png";
    LPCWSTR save_station_5 = L"Sprites\\Environment\\Save Station_5.png";
    LPCWSTR save_station_6 = L"Sprites\\Environment\\Save Station_6.png";
    LPCWSTR save_station_7 = L"Sprites\\Environment\\Save Station_7.png";
    LPCWSTR save_station_8 = L"Sprites\\Environment\\Save Station_8.png";
    LPCWSTR save_station_9 = L"Sprites\\Environment\\Save Station_9.png";
    LPCWSTR save_station_10 = L"Sprites\\Environment\\Save Station_10.png";
    LPCWSTR save_station_11 = L"Sprites\\Environment\\Save Station_11.png";
    LPCWSTR save_station_12 = L"Sprites\\Environment\\Save Station_12.png";
    LPCWSTR save_station_13 = L"Sprites\\Environment\\Save Station_13.png";
    LPCWSTR save_station_14 = L"Sprites\\Environment\\Save Station_14.png";
    LPCWSTR save_station_15 = L"Sprites\\Environment\\Save Station_15.png";
    LPCWSTR player_descending_1 = L"Sprites\\Ship\\Player_Descending_1.png";
    LPCWSTR player_descending_2 = L"Sprites\\Ship\\Player_Descending_2.png";
    LPCWSTR player_descending_3 = L"Sprites\\Ship\\Player_Descending_3.png";
    LPCWSTR player_descending_4 = L"Sprites\\Ship\\Player_Descending_4.png";
    LPCWSTR player_descending_5 = L"Sprites\\Ship\\Player_Descending_5.png";
    LPCWSTR player_descending_6 = L"Sprites\\Ship\\Player_Descending_6.png";
    LPCWSTR repair_station_menu = L"Sprites\\Menu\\Repair_Station_Menu.png";
    LPCWSTR invalid_char = L"Sprites\\Fonts\\Invalid_Char.png";
    LPCWSTR repair_station_bar_shell = L"Sprites\\Menu\\Repair_Station_Bar_Shell.png";
    LPCWSTR repair_station_blasters_filling = L"Sprites\\Menu\\Repair_Station_Blasters_Filling.png";
    LPCWSTR repair_station_thruster_filling = L"Sprites\\Menu\\Repair_Station_Thruster_Filling.png";
    LPCWSTR repair_station_hull_filling = L"Sprites\\Menu\\Repair_Station_Hull_Filling.png";
    LPCWSTR repair_station_utilities_filling = L"Sprites\\Menu\\Repair_Station_Utilities_Filling.png";
    LPCWSTR period = L"Sprites\\Fonts\\period.png";
    LPCWSTR repair_Selection_1 = L"Sprites\\Menu\\Repair_Selection_1.png";
    LPCWSTR repair_Selection_2 = L"Sprites\\Menu\\Repair_Selection_2.png";
    LPCWSTR repair_Selection_3 = L"Sprites\\Menu\\Repair_Selection_3.png";
    LPCWSTR repair_Selection_4 = L"Sprites\\Menu\\Repair_Selection_4.png";
    LPCWSTR repair_Selection_5 = L"Sprites\\Menu\\Repair_Selection_5.png";
    LPCWSTR repair_station_info_box = L"Sprites\\Menu\\Repair_Station_Info_Panel.png";
    LPCWSTR upgrade_button = L"Sprites\\Menu\\Repair_Station_Upgrade_Button.png";
    LPCWSTR upgrade_button_pressed = L"Sprites\\Menu\\Repair_Station_Upgrade_Button_Pressed.png";
    LPCWSTR apostrophe = L"Sprites\\Fonts\\apostrophe.png";
    LPCWSTR comma = L"Sprites\\Fonts\\comma.png";
} files;

void LoadFilePathsToVector(std::vector<LPCWSTR>& spriteFilePaths) {
    // Filenames vector
    spriteFilePaths.emplace_back(files.playerFrame1);
    spriteFilePaths.emplace_back(files.playerFrame2);
    spriteFilePaths.emplace_back(files.playerRedLightffect1);
    spriteFilePaths.emplace_back(files.playerRedLightffect2);
    spriteFilePaths.emplace_back(files.playerRedLightffect3);
    spriteFilePaths.emplace_back(files.playerRedLightffect4);
    spriteFilePaths.emplace_back(files.playerRedLightffect5);
    spriteFilePaths.emplace_back(files.playerRedLightffect6);
    spriteFilePaths.emplace_back(files.playerRedLightffect7);
    spriteFilePaths.emplace_back(files.playerRedLightffect8);
    spriteFilePaths.emplace_back(files.playerRedLightffect9);
    spriteFilePaths.emplace_back(files.asteroid1);
    spriteFilePaths.emplace_back(files.pause);
    spriteFilePaths.emplace_back(files.pauseBackground);
    spriteFilePaths.emplace_back(files.basicShotEffect1);
    spriteFilePaths.emplace_back(files.basicShotEffect2);
    spriteFilePaths.emplace_back(files.basicShotEffect3);
    spriteFilePaths.emplace_back(files.basicShotEffect4);
    spriteFilePaths.emplace_back(files.basicShotEffect5);
    spriteFilePaths.emplace_back(files.basicShotDefault);
    spriteFilePaths.emplace_back(files.basicShotPurple);
    spriteFilePaths.emplace_back(files.basicShotBlue);
    spriteFilePaths.emplace_back(files.hitBox);
    spriteFilePaths.emplace_back(files.hurtBox);
    spriteFilePaths.emplace_back(files.enemyShip1);
    spriteFilePaths.emplace_back(files.basicShotEffectBlue1);
    spriteFilePaths.emplace_back(files.basicShotEffectBlue2);
    spriteFilePaths.emplace_back(files.basicShotEffectBlue3);
    spriteFilePaths.emplace_back(files.basicShotEffectBlue4);
    spriteFilePaths.emplace_back(files.basicShotEffectBlue5);
    spriteFilePaths.emplace_back(files.basicShotEffectPurple1);
    spriteFilePaths.emplace_back(files.basicShotEffectPurple2);
    spriteFilePaths.emplace_back(files.basicShotEffectPurple3);
    spriteFilePaths.emplace_back(files.basicShotEffectPurple4);
    spriteFilePaths.emplace_back(files.basicShotEffectPurple5);
    spriteFilePaths.emplace_back(files.enemyShip1Damaged);
    spriteFilePaths.emplace_back(files.explosion1);
    spriteFilePaths.emplace_back(files.explosion2);
    spriteFilePaths.emplace_back(files.explosion3);
    spriteFilePaths.emplace_back(files.explosion4);
    spriteFilePaths.emplace_back(files.doubleShotPickup);
    spriteFilePaths.emplace_back(files.base);
    spriteFilePaths.emplace_back(files.brody_the_toad);
    /*spriteFilePaths.emplace_back(files.brody_the_toad_pain);*/
    spriteFilePaths.emplace_back(files.turret);
    spriteFilePaths.emplace_back(files.turret_Shader);
    spriteFilePaths.emplace_back(files.turret_Damaged);
    spriteFilePaths.emplace_back(L"Sprites\\Menu\\How_To_Play_Screen.png");
    spriteFilePaths.emplace_back(files.shield_Generator);
    spriteFilePaths.emplace_back(files.shield_Generator_Damaged);
    spriteFilePaths.emplace_back(files.base_Door);
    spriteFilePaths.emplace_back(files.base_Interior);
    spriteFilePaths.emplace_back(files.entrance);
    spriteFilePaths.emplace_back(files.status_Bar);
    spriteFilePaths.emplace_back(files.health_Bar_Top);
    spriteFilePaths.emplace_back(files.health_Bar_Bottom);
    spriteFilePaths.emplace_back(files.player_Death_Animation_1);
    spriteFilePaths.emplace_back(files.player_Death_Animation_2);
    spriteFilePaths.emplace_back(files.player_Death_Animation_3);
    spriteFilePaths.emplace_back(files.jewel_Blue);
    spriteFilePaths.emplace_back(files.jewel_Green);
    spriteFilePaths.emplace_back(files.jewel_Purple);
    spriteFilePaths.emplace_back(files.jewel_Red);
    spriteFilePaths.emplace_back(files.jewel_Silver);
    spriteFilePaths.emplace_back(files.jewel_Yellow);
    spriteFilePaths.emplace_back(files.boost_Bar_top);
    spriteFilePaths.emplace_back(files.boost_Bar_bottom);
    spriteFilePaths.emplace_back(files.font_0);
    spriteFilePaths.emplace_back(files.font_1);
    spriteFilePaths.emplace_back(files.font_2);
    spriteFilePaths.emplace_back(files.font_3);
    spriteFilePaths.emplace_back(files.font_4);
    spriteFilePaths.emplace_back(files.font_5);
    spriteFilePaths.emplace_back(files.font_6);
    spriteFilePaths.emplace_back(files.font_7);
    spriteFilePaths.emplace_back(files.font_8);
    spriteFilePaths.emplace_back(files.font_9);
    spriteFilePaths.emplace_back(files.hp_pickup_1);
    spriteFilePaths.emplace_back(files.hp_pickup_2);
    spriteFilePaths.emplace_back(files.hp_pickup_3);
    spriteFilePaths.emplace_back(files.bomber_drone);
    spriteFilePaths.emplace_back(files.drone_Shot_1);
    spriteFilePaths.emplace_back(files.drone_Shot_2);
    spriteFilePaths.emplace_back(files.drone_Shot_3);
    spriteFilePaths.emplace_back(files.drone_Shot_4);
    spriteFilePaths.emplace_back(files.drone_Shot_5);
    spriteFilePaths.emplace_back(files.drone_Shot_6);
    spriteFilePaths.emplace_back(files.drone_Shot_7);
    spriteFilePaths.emplace_back(files.asteroid_2);
    spriteFilePaths.emplace_back(files.map_frame);
    spriteFilePaths.emplace_back(files.base_icon);
    spriteFilePaths.emplace_back(files.boss_icon);
    spriteFilePaths.emplace_back(files.player_tilt_left);
    spriteFilePaths.emplace_back(files.player_tilt_right);
    spriteFilePaths.emplace_back(files.player_sideways_l);
    spriteFilePaths.emplace_back(files.player_sideways_r);
    spriteFilePaths.emplace_back(files.player_upside_tilted_l);
    spriteFilePaths.emplace_back(files.player_upside_tilted_r);
    spriteFilePaths.emplace_back(files.title_screen);
    spriteFilePaths.emplace_back(files.save_file_panel);
    spriteFilePaths.emplace_back(files.shrunken_repair_screen);
    spriteFilePaths.emplace_back(files.lower_a);
    spriteFilePaths.emplace_back(files.lower_b);
    spriteFilePaths.emplace_back(files.lower_c);
    spriteFilePaths.emplace_back(files.lower_d);
    spriteFilePaths.emplace_back(files.lower_e);
    spriteFilePaths.emplace_back(files.lower_f);
    spriteFilePaths.emplace_back(files.lower_g);
    spriteFilePaths.emplace_back(files.lower_h);
    spriteFilePaths.emplace_back(files.lower_i);
    spriteFilePaths.emplace_back(files.lower_j);
    spriteFilePaths.emplace_back(files.lower_k);
    spriteFilePaths.emplace_back(files.lower_l);
    spriteFilePaths.emplace_back(files.lower_m);
    spriteFilePaths.emplace_back(files.lower_n);
    spriteFilePaths.emplace_back(files.lower_o);
    spriteFilePaths.emplace_back(files.lower_p);
    spriteFilePaths.emplace_back(files.lower_q);
    spriteFilePaths.emplace_back(files.lower_r);
    spriteFilePaths.emplace_back(files.lower_s);
    spriteFilePaths.emplace_back(files.lower_t);
    spriteFilePaths.emplace_back(files.lower_u);
    spriteFilePaths.emplace_back(files.lower_v);
    spriteFilePaths.emplace_back(files.lower_w);
    spriteFilePaths.emplace_back(files.lower_x);
    spriteFilePaths.emplace_back(files.lower_y);
    spriteFilePaths.emplace_back(files.lower_z);
    spriteFilePaths.emplace_back(files.upper_a);
    spriteFilePaths.emplace_back(files.upper_b);
    spriteFilePaths.emplace_back(files.upper_c);
    spriteFilePaths.emplace_back(files.upper_d);
    spriteFilePaths.emplace_back(files.upper_e);
    spriteFilePaths.emplace_back(files.upper_f);
    spriteFilePaths.emplace_back(files.upper_g);
    spriteFilePaths.emplace_back(files.upper_h);
    spriteFilePaths.emplace_back(files.upper_i);
    spriteFilePaths.emplace_back(files.upper_j);
    spriteFilePaths.emplace_back(files.upper_k);
    spriteFilePaths.emplace_back(files.upper_l);
    spriteFilePaths.emplace_back(files.upper_m);
    spriteFilePaths.emplace_back(files.upper_n);
    spriteFilePaths.emplace_back(files.upper_o);
    spriteFilePaths.emplace_back(files.upper_p);
    spriteFilePaths.emplace_back(files.upper_q);
    spriteFilePaths.emplace_back(files.upper_r);
    spriteFilePaths.emplace_back(files.upper_s);
    spriteFilePaths.emplace_back(files.upper_t);
    spriteFilePaths.emplace_back(files.upper_u);
    spriteFilePaths.emplace_back(files.upper_v);
    spriteFilePaths.emplace_back(files.upper_w);
    spriteFilePaths.emplace_back(files.upper_x);
    spriteFilePaths.emplace_back(files.upper_y);
    spriteFilePaths.emplace_back(files.upper_z);
    spriteFilePaths.emplace_back(files.semicolon);
    spriteFilePaths.emplace_back(files.selec_arrow);
    spriteFilePaths.emplace_back(files.save_station_1);
    spriteFilePaths.emplace_back(files.save_station_2);
    spriteFilePaths.emplace_back(files.save_station_3);
    spriteFilePaths.emplace_back(files.save_station_4);
    spriteFilePaths.emplace_back(files.save_station_5);
    spriteFilePaths.emplace_back(files.save_station_6);
    spriteFilePaths.emplace_back(files.save_station_7);
    spriteFilePaths.emplace_back(files.save_station_8);
    spriteFilePaths.emplace_back(files.save_station_9);
    spriteFilePaths.emplace_back(files.save_station_10);
    spriteFilePaths.emplace_back(files.save_station_11);
    spriteFilePaths.emplace_back(files.save_station_12);
    spriteFilePaths.emplace_back(files.save_station_13);
    spriteFilePaths.emplace_back(files.save_station_14);
    spriteFilePaths.emplace_back(files.save_station_15);
    spriteFilePaths.emplace_back(files.player_descending_1);
    spriteFilePaths.emplace_back(files.player_descending_2);
    spriteFilePaths.emplace_back(files.player_descending_3);
    spriteFilePaths.emplace_back(files.player_descending_4);
    spriteFilePaths.emplace_back(files.player_descending_5);
    spriteFilePaths.emplace_back(files.player_descending_6);
    spriteFilePaths.emplace_back(files.repair_station_menu);
    spriteFilePaths.emplace_back(files.invalid_char);
    spriteFilePaths.emplace_back(files.repair_station_bar_shell);
    spriteFilePaths.emplace_back(files.repair_station_blasters_filling);
    spriteFilePaths.emplace_back(files.repair_station_thruster_filling);
    spriteFilePaths.emplace_back(files.repair_station_hull_filling);
    spriteFilePaths.emplace_back(files.repair_station_utilities_filling);
    spriteFilePaths.emplace_back(files.period);
    spriteFilePaths.emplace_back(files.repair_Selection_1);
    spriteFilePaths.emplace_back(files.repair_Selection_2);
    spriteFilePaths.emplace_back(files.repair_Selection_3);
    spriteFilePaths.emplace_back(files.repair_Selection_4);
    spriteFilePaths.emplace_back(files.repair_Selection_5);
    spriteFilePaths.emplace_back(files.repair_station_info_box);
    spriteFilePaths.emplace_back(files.upgrade_button);
    spriteFilePaths.emplace_back(files.upgrade_button_pressed);
    spriteFilePaths.emplace_back(files.apostrophe);
    spriteFilePaths.emplace_back(files.comma);
}

// The starting point for using Direct2D; it's what you use to create other Direct2D resources
ID2D1Factory* D2DFactory = NULL;

// Represents an object that can receive drawing commands.
ID2D1HwndRenderTarget* renderTarget = NULL;

// A map of bitmaps that will be used for rendering
std::map<LPCWSTR, ID2D1Bitmap*> bitmaps;

// System screen horizontal and vertical resolution
int screenX = GetSystemMetrics(SM_CXSCREEN);
int screenY = GetSystemMetrics(SM_CYSCREEN);

// Art style is 256x224 resolution, so this helps with scaling later
double scalerX = double(screenX) / ((double(screenX) / double(screenY)) * 224);
double scalerY = double(screenY) / 224;

// Art style is 4:3, so this helps with boundaries later
double leftBoundary = (screenX / 2) - (128 * scalerX);
double rightBoundary = (screenX / 2) + (128 * scalerX);

std::chrono::steady_clock::time_point lastLogicUpdate = std::chrono::steady_clock::now();

bool paused = false;

std::chrono::steady_clock::time_point pauseBuffer = std::chrono::steady_clock::now();

bool modulatorTicker = true;
bool splashscreen = false;

std::mt19937 generator(std::random_device{}());
int mapSizeX = 3000;
int mapSizeY = 3000;

std::chrono::steady_clock::time_point mapTick = std::chrono::steady_clock::now();
bool displayMap;

bool isMultiCore = std::thread::hardware_concurrency() > 1;

std::chrono::milliseconds menuInputBuffer = std::chrono::milliseconds(150);
std::chrono::steady_clock::time_point menuLastInput = std::chrono::steady_clock::now();

LPCWSTR fontArray[255]{
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.apostrophe,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.comma,
    files.invalid_char,
    files.period,
    files.invalid_char,
    files.font_0,
    files.font_1,
    files.font_2,
    files.font_3,
    files.font_4,
    files.font_5,
    files.font_6,
    files.font_7,
    files.font_8,
    files.font_9,
    files.semicolon,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.upper_a,
    files.upper_b,
    files.upper_c,
    files.upper_d,
    files.upper_e,
    files.upper_f,
    files.upper_g,
    files.upper_h,
    files.upper_i,
    files.upper_j,
    files.upper_k,
    files.upper_l,
    files.upper_m,
    files.upper_n,
    files.upper_o,
    files.upper_p,
    files.upper_q,
    files.upper_r,
    files.upper_s,
    files.upper_t,
    files.upper_u,
    files.upper_v,
    files.upper_w,
    files.upper_x,
    files.upper_y,
    files.upper_z,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.lower_a,
    files.lower_b,
    files.lower_c,
    files.lower_d,
    files.lower_e,
    files.lower_f,
    files.lower_g,
    files.lower_h,
    files.lower_i,
    files.lower_j,
    files.lower_k,
    files.lower_l,
    files.lower_m,
    files.lower_n,
    files.lower_o,
    files.lower_p,
    files.lower_q,
    files.lower_r,
    files.lower_s,
    files.lower_t,
    files.lower_u,
    files.lower_v,
    files.lower_w,
    files.lower_x,
    files.lower_y,
    files.lower_z,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.apostrophe,
    files.apostrophe,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
    files.invalid_char,
};



struct hash_function {
    std::size_t operator()(const std::pair<int, int>& p) const {
        std::size_t h1 = std::hash<size_t>{}(p.first);
        std::size_t h2 = std::hash<size_t>{}(p.second);
        return h1 ^ (h2 + 0x9e3779b9 + (h1 << 6) + (h1 >> 2));
    }
};

// Booleans for key inputs
struct
{
    bool left = false;
    bool right = false;
    bool up = false;
    bool down = false;
    bool space = false;
    bool lShift = false;
    bool escape = false;
    bool q = false;
    bool s = false;
    bool l = false;
    bool directionPressed = false;
    bool ctrl = false;
    bool f = false;
} keys;

void GetDirectionalInput(int& xDir, int& yDir, bool right, bool left, bool down, bool up) {
    xDir = (right ? 1 : 0) - (left ? 1 : 0);
    yDir = (down ? 1 : 0) - (up ? 1 : 0);
}



//---------
// Classes
//---------

class Object
{
public:
    double xPos = 1280;
    double yPos = 720;
    double xVel = 0;
    double yVel = 0;
    LPCWSTR currentFramePath = nullptr;
    double angleRadians = 0;
    double modulator = 0;
    double modulatorDelta = 0;
    bool modulatorPositiveDelta = true;
    bool damaged = false;
    std::chrono::steady_clock::time_point damageBegins;
    float power;
    float health;
    float maxHP;
    bool collided = false;
    std::chrono::steady_clock::time_point explosionBegin;
    LPCWSTR name;
    bool destructible = false;
    unsigned int renderOrder;
    LPCWSTR damagedFrame;
    LPCWSTR defaultFrame;
    bool rotatable = false;
    bool visible = false;
    double turnRadius;
    std::chrono::steady_clock::time_point lastShotTime = std::chrono::steady_clock::now() - std::chrono::hours(1);
    std::chrono::nanoseconds shotSpeed;
    bool canFire;
    LPCWSTR shotFrame = nullptr;
    double shotVelocity;
    LPCWSTR shotType;
    LPCWSTR defaultShotEffect;
    std::chrono::steady_clock::time_point lastDeathFrameUpdate = std::chrono::steady_clock::now();
    bool dead = false;
    LPCWSTR deathFrame;
    bool reverseDeathAnimation = false;
    bool pickup = false;
    std::chrono::steady_clock::time_point genericFrameMarker = std::chrono::steady_clock::now() - std::chrono::seconds(10);
    std::chrono::steady_clock::time_point timesinceInception = std::chrono::steady_clock::now();
    bool exploding = false;
    bool pulsating = false;
    bool randomSpawner = false;
    bool burstFire = false;
    bool burstAvailable = false;
    std::chrono::steady_clock::time_point timeSinceBurst = std::chrono::steady_clock::now();
    int shotsInBurst = 0;


    struct {
        double left;
        double right;
        double up;
        double down;
    } hitbox;

    Object() {}

    Object(LPCWSTR objName, double xPosition, double yPosition, float HP, LPCWSTR filepath,
        bool canKill, unsigned int order, LPCWSTR dmgedFrame, LPCWSTR defltFrame, double xVelocity,
        double yVelocity, bool canRotate, bool canSee, bool canShoot) {
        name = objName;
        xPos = xPosition;
        yPos = yPosition;
        health = HP;
        currentFramePath = filepath;
        destructible = canKill;
        renderOrder = order;
        damagedFrame = dmgedFrame;
        xVel = xVelocity;
        yVel = yVelocity;
        defaultFrame = defltFrame;
        rotatable = canRotate;
        visible = canSee;
        canFire = canShoot;
    }

    Object(LPCWSTR fileName) {
        currentFramePath = fileName;
    }

    void UpdateHitBox() {
        ID2D1Bitmap* object = bitmaps[currentFramePath];

        D2D1_SIZE_F size = object->GetSize();

        hitbox.left = xPos - (size.width / 2);
        hitbox.right = xPos + (size.width / 2);
        hitbox.up = yPos - (size.height / 2);
        hitbox.down = yPos + (size.height / 2);
    }

    void UpdateHurtBox() {
        int later = 0;
    }

    bool CheckCollision(Object& object) {
        if (hitbox.left < object.hitbox.left + (object.hitbox.right - object.hitbox.left) &&
            hitbox.left + (hitbox.right - hitbox.left) > object.hitbox.left &&
            hitbox.up < object.hitbox.up + (object.hitbox.down - object.hitbox.up) &&
            hitbox.up + (hitbox.down - hitbox.up) > object.hitbox.up)
        {
            return true;
        }
        return false;
    }
};

class SaveStation : public Object {
public:
    unsigned __int8 id;
    bool closed = true;
    std::chrono::milliseconds doorInterval = std::chrono::milliseconds(66);
    std::chrono::steady_clock::time_point lastFrame = std::chrono::steady_clock::now();
    LPCWSTR frames[15] = {
        files.save_station_1,
        files.save_station_2,
        files.save_station_3,
        files.save_station_4,
        files.save_station_5,
        files.save_station_6,
        files.save_station_7,
        files.save_station_8,
        files.save_station_9,
        files.save_station_10,
        files.save_station_11,
        files.save_station_12,
        files.save_station_13,
        files.save_station_14,
        files.save_station_15,
    };
    __int8 currFrame = 0;

    SaveStation() {
        currentFramePath = frames[0];
    }

    void PlayOpenAnimation(double deltaTime) {
        if (currFrame == 0) {
            lastFrame = std::chrono::steady_clock::now();
            currentFramePath = frames[1];
            currFrame = 1;
            return;
        }
        if (std::chrono::steady_clock::now() - lastFrame <= doorInterval) return;
        lastFrame = std::chrono::steady_clock::now();
        currFrame = min(14, currFrame + 1);
        currentFramePath = (frames[currFrame]);
        if (currFrame == 14) {
            closed = false;
        }
    }

    void PlayCloseAnimation(double deltaTime) {
        if (currFrame == 14) {
            lastFrame = std::chrono::steady_clock::now();
            currentFramePath = frames[13];
            currFrame = 13;
            return;
        }
        if (std::chrono::steady_clock::now() - lastFrame <= doorInterval) return;
        lastFrame = std::chrono::steady_clock::now();
        currFrame = max(0, currFrame - 1);
        currentFramePath = (frames[currFrame]);
        if (currFrame == 0) {
            closed = true;
        }
    }
};

class Player : public Object {
public:
    float directionX, directionY;
    std::vector<Object> bullets;
    LPCWSTR redLightFrame = files.playerRedLightffect1;
    LPCWSTR basicShotFrame = nullptr;
    std::chrono::steady_clock::time_point lastFrameChange = std::chrono::steady_clock::now();
    std::chrono::nanoseconds frameInterval = std::chrono::nanoseconds(166666666); // closest I can get to 1/6th of a second
    std::chrono::steady_clock::time_point lastThrusterTime = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point lastRedLightTime = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point fullBrightStart = std::chrono::steady_clock::now();
    std::chrono::steady_clock::time_point lastShotEffectTime = std::chrono::steady_clock::now();
    bool loadBullet = false;
    bool doubleShot = false;
    bool dead = false;
    int currency = 0;
    float boost = 100;
    std::chrono::steady_clock::time_point runoutTime = std::chrono::steady_clock::now() - std::chrono::seconds(10);
    std::chrono::steady_clock::time_point currencyAcquired = std::chrono::steady_clock::now() - std::chrono::seconds(10);
    LPCWSTR lastFrame = files.playerFrame1;
    bool rolling = false;
    std::chrono::steady_clock::time_point rollTime = std::chrono::steady_clock::now();
    bool sideMode;
    float speed = 1.5;
    bool alreadyOnStation = true;
    unsigned __int8 stationTouchingID = 0;
    bool inDockingSequence = false;
    bool descending = false;
    std::chrono::milliseconds descendingInterval = std::chrono::milliseconds(250);
    LPCWSTR descentFrames[6] = {
        files.player_descending_1,
        files.player_descending_2,
        files.player_descending_3,
        files.player_descending_4,
        files.player_descending_5,
        files.player_descending_6,
    };
    __int8 currDescentFrame = 0;
    bool approaching = false;
    bool adjustingForEntry = false;
    bool inAscendingSequence = false;
    bool ascending = true;
    bool inModifiedDockingAngle = false;
    __int8 tweakBarLength[4];


    Player() {
        currentFramePath = files.playerFrame1;
        std::ifstream inFile((L"Save Files\\Save.txt"));
        if (inFile.is_open()) {
            std::string line;
            int i = 0;
            while (std::getline(inFile, line)) {
                if (i > 3) {
                    tweakBarLength[i - 4] = stoi(line);
                }
                i++;
            }
            inFile.close();
        }
    }

    void UpdateHitBox() {
        ID2D1Bitmap* object = bitmaps[currentFramePath];

        D2D1_SIZE_F size = object->GetSize();

        hitbox.left = xPos - (size.width / 2) + 4;
        hitbox.right = xPos + (size.width / 2) - 4;
        hitbox.up = yPos - (size.height / 2) + 4;
        hitbox.down = yPos + (size.height / 2) - 4;
    }

    void ApplyDirectionalInput(double deltaTime) {
        // Apply Player Inputs
        float velocity = speed;
        if (keys.lShift && keys.directionPressed && !keys.f) {
            if (boost > 0 && ((std::chrono::steady_clock::now() - runoutTime) >= std::chrono::seconds(2))) {
                velocity *= 2;
                boost -= 1 * deltaTime;
                if (boost <= 0) {
                    boost = 0;
                    runoutTime = std::chrono::steady_clock::now();
                }
            }
            else {
                if ((std::chrono::steady_clock::now() - runoutTime) >= std::chrono::seconds(1)) {
                    boost += 0.5 * deltaTime;
                }
            }
        }
        else {
            if ((std::chrono::steady_clock::now() - runoutTime) >= std::chrono::seconds(1)) {
                boost += 0.5 * deltaTime;
            }
            if (boost > 100) {
                boost = 100;
            }
            if (keys.f) {
                velocity *= 0.66;
            }
        }
        if (keys.up) {
            yPos -= (velocity * deltaTime);
        }
        if (keys.down) {
            yPos += (velocity * deltaTime);
        }
        if (sideMode) {
            xPos += 1.5 * deltaTime;
        }
        else {
            if (keys.right) {
                xPos += (velocity * deltaTime);
            }
            if (keys.left) {
                xPos -= (velocity * deltaTime);
            }
        }

        lastFrame = currentFramePath;
        if (sideMode) {
            xVel = 1;
            directionX = 1;
            directionY = 0;
            if (keys.up) {
                currentFramePath = files.player_upside_tilted_l;
            }
            else if (keys.down) {
                currentFramePath = files.player_tilt_left;
            }
            else {
                currentFramePath = files.player_sideways_l;
            }
        }
        else {
            if (keys.right || keys.left || keys.up || keys.down) {
                if (!keys.f) {
                    directionX = keys.right - keys.left;
                    directionY = keys.down - keys.up;
                    angleRadians = atan2(directionY, directionX) / 2;
                }
                else {
                    if (abs(directionX) > 0 && directionY == 0) {
                        if (!(keys.right && !keys.down && !keys.up)) {
                            if ((keys.up || keys.down) && !(keys.up && keys.down) && !(keys.right || keys.left)) {
                                bool inverse = (directionX > 0) ? false : true;
                                keys.up = (inverse) ? !keys.up : keys.up;
                                keys.down = (inverse) ? !keys.down : keys.down;
                                if (keys.up) {
                                    if (lastFrame == files.playerFrame1 || lastFrame == files.playerFrame2) {
                                        rolling = true;
                                        currentFramePath = files.player_tilt_left;
                                        rollTime = std::chrono::steady_clock::now();
                                    }
                                    else if (rolling) {
                                        if (std::chrono::steady_clock::now() - rollTime >= std::chrono::milliseconds(100)) {
                                            rolling = false;
                                        }
                                    }
                                    else {
                                        currentFramePath = files.player_sideways_l;
                                    }
                                }
                                else if (keys.down) {
                                    if (lastFrame == files.playerFrame1 || lastFrame == files.playerFrame2) {
                                        rolling = true;
                                        currentFramePath = files.player_tilt_right;
                                        rollTime = std::chrono::steady_clock::now();
                                    }
                                    else if (rolling) {
                                        if (std::chrono::steady_clock::now() - rollTime >= std::chrono::milliseconds(100)) {
                                            rolling = false;
                                        }
                                    }
                                    else {
                                        currentFramePath = files.player_sideways_r;
                                    }
                                }
                                else {
                                    currentFramePath = files.player_sideways_r;
                                }
                                keys.up = (inverse) ? !keys.up : keys.up;
                                keys.down = (inverse) ? !keys.down : keys.down;
                            }
                            else if (keys.down && !keys.up) {
                                if (std::chrono::steady_clock::now() - rollTime >= std::chrono::milliseconds(100)) {
                                    rolling = false;
                                    currentFramePath = (directionX > 0) ? files.player_tilt_right : files.player_tilt_left;
                                }
                            }
                            else if (keys.up && !keys.down) {
                                if (std::chrono::steady_clock::now() - rollTime >= std::chrono::milliseconds(100)) {
                                    rolling = false;
                                    currentFramePath = (directionX > 0) ? files.player_tilt_left : files.player_tilt_right;
                                }
                            }
                            else {
                                currentFramePath = files.playerFrame1;
                            }
                        }
                        else {
                            currentFramePath = files.playerFrame1;
                        }
                    }
                    else if (abs(directionY) > 0 && directionX == 0) {
                        //
                        if (!(keys.up && !keys.right && !keys.left)) {                  //
                            if ((keys.left || keys.right) && !(keys.left && keys.right) && !(keys.up || keys.down)) {
                                bool inverse = (directionY > 0) ? false : true;
                                keys.left = (inverse) ? !keys.left : keys.left;
                                keys.right = (inverse) ? !keys.right : keys.right;
                                if (keys.left) {
                                    if (lastFrame == files.playerFrame1 || lastFrame == files.playerFrame2) {
                                        rolling = true;
                                        currentFramePath = files.player_tilt_left;
                                        rollTime = std::chrono::steady_clock::now();
                                    }
                                    else if (rolling) {
                                        if (std::chrono::steady_clock::now() - rollTime >= std::chrono::milliseconds(100)) {
                                            rolling = false;
                                        }
                                    }
                                    else {
                                        currentFramePath = files.player_sideways_l;
                                    }
                                }
                                else if (keys.right) {
                                    if (lastFrame == files.playerFrame1 || lastFrame == files.playerFrame2) {
                                        rolling = true;
                                        currentFramePath = files.player_tilt_right;
                                        rollTime = std::chrono::steady_clock::now();
                                    }
                                    else if (rolling) {
                                        if (std::chrono::steady_clock::now() - rollTime >= std::chrono::milliseconds(100)) {
                                            rolling = false;
                                        }
                                    }
                                    else {
                                        currentFramePath = files.player_sideways_r;
                                    }
                                }
                                else {
                                    currentFramePath = files.player_sideways_r;
                                }
                                keys.left = (inverse) ? !keys.left : keys.left;
                                keys.right = (inverse) ? !keys.right : keys.right;
                            }
                            else if (keys.right && !keys.left) {
                                if (std::chrono::steady_clock::now() - rollTime >= std::chrono::milliseconds(100)) {
                                    rolling = false;
                                    currentFramePath = (directionY > 0) ? files.player_tilt_right : files.player_tilt_left;
                                }
                            }
                            else if (keys.left && !keys.right) {
                                if (std::chrono::steady_clock::now() - rollTime >= std::chrono::milliseconds(100)) {
                                    rolling = false;
                                    currentFramePath = (directionY > 0) ? files.player_tilt_left : files.player_tilt_right;
                                }
                            }
                            else {
                                currentFramePath = files.playerFrame1;
                            }
                        }
                        else {
                            currentFramePath = files.playerFrame1;
                        }
                    }
                    else if (abs(directionX) > 0 && directionY > 0) {
                        if ((keys.left && keys.up) && directionX > 0) {
                            currentFramePath = files.player_sideways_l;
                        }
                        else if ((keys.right && keys.up) && directionX < 0) {
                            currentFramePath = files.player_sideways_r;
                        }
                        else if ((keys.down && keys.left && directionX < 0) || (keys.down && keys.right && directionX > 0)) {
                            if (directionX > 0) {
                                currentFramePath = files.player_sideways_r;
                            }
                            else if (directionX < 0) {
                                currentFramePath = files.player_sideways_l;
                            }
                        }
                        else if ((keys.down && keys.left && directionX > 0) || (keys.down && keys.right && directionX < 0)) {
                            currentFramePath = files.playerFrame1;
                        }
                        else if ((keys.up && (keys.right || keys.left)))
                        {
                            currentFramePath = files.playerFrame1;
                        }
                        else if (keys.up && !(keys.left || keys.right)) {
                            if (directionX > 0) {
                                currentFramePath = files.player_tilt_left;
                            }
                            else if (directionX < 0) {
                                currentFramePath = files.player_tilt_right;
                            }
                        }
                        else if (((keys.left && directionX < 0) || (keys.right && directionX > 0)) && !keys.up) {
                            if (directionX > 0) {
                                currentFramePath = files.player_tilt_right;
                            }
                            else if (directionX < 0) {
                                currentFramePath = files.player_tilt_left;
                            }
                        }
                        else if (((keys.right && directionX < 0) || (keys.left && directionX > 0)) && !keys.up) {
                            if (directionX > 0) {
                                currentFramePath = files.player_tilt_left;
                            }
                            else if (directionX < 0) {
                                currentFramePath = files.player_tilt_right;
                            }
                        }
                        else if (keys.down) {
                            if (directionX > 0) {
                                currentFramePath = files.player_tilt_right;
                            }
                            else if (directionX < 0) {
                                currentFramePath = files.player_tilt_left;
                            }
                        }
                    }
                    else if (abs(directionX) > 0 && directionY < 0) {
                        if ((keys.left && keys.down) && directionX > 0) {
                            currentFramePath = files.player_sideways_r;
                        }
                        else if ((keys.right && keys.down) && directionX < 0) {
                            currentFramePath = files.player_sideways_l;
                        }
                        else if ((keys.up && keys.left && directionX < 0) || (keys.up && keys.right && directionX > 0)) {
                            if (directionX > 0) {
                                currentFramePath = files.player_sideways_l;
                            }
                            else if (directionX < 0) {
                                currentFramePath = files.player_sideways_r;
                            }
                        }
                        else if ((keys.up && keys.left && directionX > 0) || (keys.up && keys.right && directionX < 0)) {
                            currentFramePath = files.playerFrame1;
                        }
                        else if ((keys.down && (keys.right || keys.left)))
                        {
                            currentFramePath = files.playerFrame1;
                        }
                        else if (keys.down && !(keys.left || keys.right)) {
                            if (directionX > 0) {
                                currentFramePath = files.player_tilt_right;
                            }
                            else if (directionX < 0) {
                                currentFramePath = files.player_tilt_left;
                            }
                        }
                        else if (((keys.left && directionX < 0) || (keys.right && directionX > 0)) && !keys.up) {
                            if (directionX > 0) {
                                currentFramePath = files.player_tilt_left;
                            }
                            else if (directionX < 0) {
                                currentFramePath = files.player_tilt_right;
                            }
                        }
                        else if (((keys.right && directionX < 0) || (keys.left && directionX > 0)) && !keys.up) {
                            if (directionX > 0) {
                                currentFramePath = files.player_tilt_right;
                            }
                            else if (directionX < 0) {
                                currentFramePath = files.player_tilt_left;
                            }
                        }
                        else if (keys.up) {
                            if (directionX > 0) {
                                currentFramePath = files.player_tilt_left;
                            }
                            else if (directionX < 0) {
                                currentFramePath = files.player_tilt_right;
                            }
                        }
                    }
                    else {
                        lastFrame = currentFramePath;
                        currentFramePath = files.playerFrame1;
                    }
                }
            }
            else if (keys.f) { // If pressing f with no directional input
                if (lastFrame == files.player_sideways_l || lastFrame == files.player_sideways_r) {
                    rolling = true;
                    lastFrame = currentFramePath;
                    if (lastFrame == files.player_sideways_l) {
                        currentFramePath = files.player_tilt_left;
                    }
                    else if (lastFrame == files.player_sideways_r) {
                        currentFramePath = files.player_tilt_right;
                    }
                    rollTime = std::chrono::steady_clock::now();
                }
                else if (rolling) {
                    if (std::chrono::steady_clock::now() - rollTime >= std::chrono::milliseconds(100)) {
                        rolling = false;
                        lastFrame = currentFramePath;
                        currentFramePath = files.playerFrame1;
                    }
                }
                else {
                    lastFrame = currentFramePath;
                    currentFramePath = files.playerFrame1;
                }
            }

            if (!dead && !keys.f) {
                // Cycle Thruster Animation
                if (std::chrono::steady_clock::now() - lastThrusterTime >= std::chrono::milliseconds(100)) {
                    lastThrusterTime = std::chrono::steady_clock::now();
                    if (currentFramePath == files.playerFrame1) {
                        currentFramePath = files.playerFrame2;
                    }
                    else {
                        currentFramePath = files.playerFrame1;
                    }
                }
            }
        }
    }

    void UpdateRedLightEffect(double deltaTime) {
        // Cycle Ship's Red Lights effects
        if ((std::chrono::steady_clock::now() - lastRedLightTime) >= std::chrono::milliseconds(100)) {
            lastRedLightTime = std::chrono::steady_clock::now();
            if (redLightFrame == files.playerRedLightffect1) {
                redLightFrame = files.playerRedLightffect2;
            }
            else if (redLightFrame == files.playerRedLightffect2) {
                redLightFrame = files.playerRedLightffect3;
            }
            else if (redLightFrame == files.playerRedLightffect3) {
                redLightFrame = files.playerRedLightffect4;
            }
            else if (redLightFrame == files.playerRedLightffect4) {
                redLightFrame = files.playerRedLightffect5;
            }
            else if (redLightFrame == files.playerRedLightffect5) {
                redLightFrame = files.playerRedLightffect6;
            }
            else if (redLightFrame == files.playerRedLightffect6) {
                redLightFrame = files.playerRedLightffect7;
                fullBrightStart = std::chrono::steady_clock::now();
            }
            else if (std::chrono::steady_clock::now() - fullBrightStart >= std::chrono::milliseconds(500)) {
                redLightFrame = files.playerRedLightffect1;
            }
        }
    }

    void ApplyShootingLogic(double deltaTime) {
        // Apply Ship's Shooting Logic
        if (keys.space && !basicShotFrame && (std::chrono::steady_clock::now() - lastShotEffectTime >= std::chrono::milliseconds(250))) {

            lastShotEffectTime = std::chrono::steady_clock::now();
            double xPosition, yPosition;
            double angle = (angleRadians * 2) + pi / 2;

            if (doubleShot) {
                double xOffset(0), yOffset(0);
                xOffset = (-1.8 * sin(angleRadians * 2)) - 4;
                yOffset = 4 - ((4 / sin(pi / 4)) * sin(angleRadians));
                if (angleRadians > -pi / 6 && angleRadians < pi / 6) {
                    xOffset = -4;
                    yOffset = 4;
                }
                else if (angleRadians > (pi / 6) && angleRadians < (pi / 3)) {
                    xOffset = -5.6568542494923801952067548968388;
                    yOffset = 0;
                }
                else if (angleRadians > (pi / 3) && angleRadians < (2 * pi / 3)) {
                    xOffset = -4;
                    yOffset = 4;
                }
                else if (angleRadians > (2 * pi / 3) && angleRadians < (5 * pi / 6)) {
                    xOffset = 0;
                    yOffset = -5.6568542494923801952067548968388;
                }
                else if (angleRadians > (5 * pi / 6) && angleRadians < (7 * pi / 6)) {
                    xOffset = 4;
                    yOffset = -4;
                }
                else if (angleRadians > (-5 * pi / 6) && angleRadians < (-2 * pi / 3)) {
                    xOffset = 5.6568542494923801952067548968388;
                    yOffset = 0;
                }
                else if (angleRadians > (-2 * pi / 3) && angleRadians < (-pi / 3)) {
                    xOffset = 4;
                    yOffset = 4;
                }
                else if (angleRadians > (-pi / 3) && angleRadians < 0) {
                    xOffset = 0;
                    yOffset = 5.6568542494923801952067548968388;
                }
                bullets.emplace_back(files.basicShotDefault);
                bullets.back().xPos = xPos + xOffset + (11 * sin(angleRadians));
                bullets.back().yPos = yPos + yOffset - (11 * cos(angleRadians));
                bullets.back().power = power;
                bullets.back().UpdateHitBox();
                bullets.back().angleRadians = angleRadians;
                bullets.back().yVel = round(-cos(angleRadians) * 100) / 100;
                if (abs(bullets.back().yVel) < 0.0001) {
                    bullets.back().yVel = 0;
                }
                bullets.back().xVel = round(sin(angleRadians) * 100) / 100;
                if (abs(bullets.back().xVel) < 0.0001) {
                    bullets.back().xVel = 0;
                }

                float angle = angleRadians;
                if (angleRadians > -pi / 6 && angleRadians < pi / 6) {
                    xOffset = 4;
                    yOffset = 4;
                }
                else if (angleRadians > (pi / 6) && angleRadians < (pi / 3)) {
                    xOffset = 0;
                    yOffset = 5.6568542494923801952067548968388;
                }
                else if (angleRadians > (pi / 3) && angleRadians < (2 * pi / 3)) {
                    xOffset = -4;
                    yOffset = -4;
                }
                else if (angleRadians > (2 * pi / 3) && angleRadians < (5 * pi / 6)) {
                    xOffset = -5.6568542494923801952067548968388;
                    yOffset = 0;
                }
                else if (angleRadians > (5 * pi / 6) && angleRadians < (7 * pi / 6)) {
                    xOffset = -4;
                    yOffset = -4;
                }
                else if (angleRadians > (-5 * pi / 6) && angleRadians < (-2 * pi / 3)) {
                    xOffset = 0;
                    yOffset = -5.6568542494923801952067548968388;
                }
                else if (angleRadians > (-2 * pi / 3) && angleRadians < (-pi / 3)) {
                    xOffset = 4;
                    yOffset = -4;
                }
                else if (angleRadians > (-pi / 3) && angleRadians < 0) {
                    xOffset = 5.6568542494923801952067548968388;
                    yOffset = 0;
                }
                xPosition = xPos + xOffset + (11 * sin(angleRadians));
                yPosition = yPos + yOffset - (11 * cos(angleRadians));
            }
            else {
                xPosition = xPos + (11 * sin(angle));
                yPosition = yPos - (11 * cos(angle));
            }


            // Create new bullet, position it with player, give it its velocities
            bullets.emplace_back(files.basicShotDefault);
            bullets.back().xPos = xPosition;
            bullets.back().yPos = yPosition;
            bullets.back().UpdateHitBox();
            bullets.back().power = power;
            bullets.back().angleRadians = angle;
            bullets.back().yVel = round(-cos(angle) * 100) / 100;
            bullets.back().modulator = double((rand() % 628)) / 100;
            bullets.back().modulatorDelta = double((rand() % 5) + 15) / 100;
            int result = (rand() % 2);
            if (modulatorTicker == true) {
                modulatorTicker = false;
                bullets.back().modulatorPositiveDelta = false;
            }
            else {
                modulatorTicker = true;
                bullets.back().modulatorPositiveDelta = true;
            }
            if (abs(bullets.back().yVel) < 0.0001) {
                bullets.back().yVel = 0;
            }
            bullets.back().xVel = round(sin(angle) * 100) / 100;
            if (abs(bullets.back().xVel) < 0.0001) {
                bullets.back().xVel = 0;
            }

            basicShotFrame = files.basicShotEffect1;
        }
        else if (basicShotFrame == files.basicShotEffect1 &&
            (std::chrono::steady_clock::now() - lastShotEffectTime >= std::chrono::nanoseconds(16666666))) {
            lastShotEffectTime = std::chrono::steady_clock::now();
            basicShotFrame = files.basicShotEffect2;
        }
        else if (basicShotFrame == files.basicShotEffect2 &&
            (std::chrono::steady_clock::now() - lastShotEffectTime >= std::chrono::nanoseconds(16666666))) {
            lastShotEffectTime = std::chrono::steady_clock::now();
            basicShotFrame = files.basicShotEffect3;
        }
        else if (basicShotFrame == files.basicShotEffect3 &&
            (std::chrono::steady_clock::now() - lastShotEffectTime >= std::chrono::nanoseconds(16666666))) {
            lastShotEffectTime = std::chrono::steady_clock::now();
            basicShotFrame = files.basicShotEffect4;
        }
        else if (basicShotFrame == files.basicShotEffect4 &&
            (std::chrono::steady_clock::now() - lastShotEffectTime >= std::chrono::nanoseconds(16666666))) {
            lastShotEffectTime = std::chrono::steady_clock::now();
            basicShotFrame = files.basicShotEffect5;
        }
        else if ((basicShotFrame == files.basicShotEffect5) &&
            (std::chrono::steady_clock::now() - lastShotEffectTime >= std::chrono::nanoseconds(16666666))) {
            basicShotFrame = nullptr;
        }
    }

    void UpdateBullets(double deltaTime, std::vector<Object>& objects) {
        // Bullet logic
        if (!bullets.empty()) {
            for (auto it = bullets.begin(); it != bullets.end(); ) {
                if (it->collided && std::chrono::steady_clock::now() - it->explosionBegin > std::chrono::nanoseconds(16666666 * 6)) {
                    it = bullets.erase(it);
                }
                else if (!it->collided) {

                    for (auto& object : objects) {
                        if (object.destructible && !object.dead) {
                            if (it->CheckCollision(object)) {
                                object.damaged = true;
                                object.damageBegins = std::chrono::steady_clock::now();
                                object.currentFramePath = object.damagedFrame;
                                object.health -= it->power;
                                it->currentFramePath = files.explosion1;
                                it->collided = true;
                                it->explosionBegin = std::chrono::steady_clock::now();
                            }
                        }
                    }

                    if (!it->collided) {
                        it->xPos += 7 * (deltaTime * it->xVel);
                        it->yPos += 7 * (deltaTime * it->yVel);
                    }
                    it->UpdateHitBox();
                }
                if (it != bullets.end()) {
                    ++it;
                }
            }
        }
    }

    void MovePlayerForward(double deltaTime, float vel) {
        float x = cos(angleRadians * 2);
        float y = sin(angleRadians * 2);
        directionX = x;
        directionY = y;
        xPos += (x * vel * deltaTime);
        yPos += (y * vel * deltaTime);
    }

    void PlayDescendingAnimation(double deltaTime) {
        if (currentFramePath == files.playerFrame1 || currentFramePath == files.playerFrame2) {
            currentFramePath = descentFrames[0];
            currDescentFrame = 0;
            lastFrameChange = std::chrono::steady_clock::now();
        }
        if ((std::chrono::steady_clock::now() - lastFrameChange) <= descendingInterval) return;
        lastFrameChange = std::chrono::steady_clock::now();
        currDescentFrame = min(5, currDescentFrame + 1);
        currentFramePath = descentFrames[currDescentFrame];
        if (currDescentFrame == 5) {
            descending = false;
        }
    }

    void PlayDockingAnimation(double deltaTime, SaveStation& s) {
        if (approaching) {
            ID2D1Bitmap* pbmp = bitmaps[currentFramePath];
            if (!pbmp) TripErrorMissingFile(currentFramePath);
            D2D1_SIZE_F size = pbmp->GetSize();
            D2D1_POINT_2F pcenter = D2D1::Point2F(xPos + (size.width / 2) + 8, yPos + (size.height / 2) + 8);

            ID2D1Bitmap* obmp = bitmaps[s.currentFramePath];
            if (!obmp) TripErrorMissingFile(s.currentFramePath);
            size = obmp->GetSize();
            D2D1_POINT_2F ocenter = D2D1::Point2F(s.xPos + (size.width / 2), s.yPos + (size.height / 2));

            if ((abs(pcenter.x - ocenter.x) >= 0.1) || (abs(pcenter.y - ocenter.y) >= 0.1)) {
                inModifiedDockingAngle = true;
                angleRadians = atan2(ocenter.y - pcenter.y, ocenter.x - pcenter.x) / 2;
                MovePlayerForward(deltaTime, speed / 2.5);
            }
            else {
                approaching = false;
                if (angleRadians != 0) adjustingForEntry = true;
            }
        }
        else {
            if (s.closed) {
                s.PlayOpenAnimation(deltaTime);
                if (!s.closed) {
                    descending = true;
                }
            }
            else if (currDescentFrame < 2) {
                PlayDescendingAnimation(deltaTime);
            }
            else {
                if (currDescentFrame < 6) {
                    PlayDescendingAnimation(deltaTime);
                }
                s.PlayCloseAnimation(deltaTime);
                if (s.currentFramePath == s.frames[0]) {
                    currDescentFrame = 0;
                    inDockingSequence = false;
                }
            }
        }

    }

    void PlayAscendingAnimation(double deltaTime) {
        if (currentFramePath == descentFrames[5]) {
            currentFramePath = descentFrames[4];
            currDescentFrame = 4;
            lastFrameChange = std::chrono::steady_clock::now();
        }
        if ((std::chrono::steady_clock::now() - lastFrameChange) <= descendingInterval) return;
        lastFrameChange = std::chrono::steady_clock::now();
        if (currDescentFrame == 0) {
            currentFramePath = files.playerFrame1;
            inAscendingSequence = false;
            ascending = false;
            inModifiedDockingAngle = false;
            return;
        }
        currDescentFrame = max(0, currDescentFrame - 1);
        currentFramePath = descentFrames[currDescentFrame];
    }

    void PlayAscendingSequence(double deltaTime, SaveStation& s) {
        s.PlayOpenAnimation(deltaTime);
        PlayAscendingAnimation(deltaTime);
    }
};

class Enemy : public Object {
public:
};

class Turret : public Object {
public:
    Turret() {
        currentFramePath = files.turret;
    }

};

class Star : public Object {
public:
    float r, g, b, a, rate;
    Star(int x, int y, int red, int green, int blue, float alpha) {
        xPos = x;
        yPos = y;
        r = red;
        g = green;
        b = blue;
        a = alpha;
        std::uniform_real_distribution<float> range(0.00125, 0.00375);
        float roll = range(generator);
        std::uniform_int_distribution<int> range1(0, 1);
        rate = range1(generator) ? roll : -roll;
    }
    void Pulsate(double deltaTime) {
        a += rate * deltaTime;
        if ((a >= 1.0) || (a <= 0)) {
            rate *= -1;
        }
    }
};

class Asteroid : public Object {
public:
    Asteroid(int x, int y) {
        xPos = x;
        yPos = y;
        currentFramePath = files.asteroid_2;
    }
};

class Door : public Object {
public:
    float destX, destY;
    unsigned __int8 destID;

    Door(float l, float r, float u, float d, float toX, float toY, unsigned __int8 toID, LPCWSTR file) {
        hitbox.left = l;
        hitbox.right = r;
        hitbox.up = u;
        hitbox.down = d;
        destX = toX;
        destY = toY;
        destID = toID;
        currentFramePath = file;
    }

    void UpdateHitBox() {
        ID2D1Bitmap* object = bitmaps[currentFramePath];

        D2D1_SIZE_F size = object->GetSize();

        hitbox.left = xPos - (size.width / 2);
        hitbox.right = xPos + (size.width / 2);
        hitbox.up = yPos - (size.height / 2);
        hitbox.down = yPos + (size.height / 2);
    }
};

class Environment {
public:
    unsigned __int8 id;
    LPCWSTR frame;
    std::vector<Door> doors;
    bool overworld = false;
    bool idSideMap[4] = { false, true, true, true };
    bool side;


    Environment(LPCWSTR file, unsigned __int8 ident, bool ow) {
        frame = file;
        id = ident;
        overworld = ow;
        side = idSideMap[id];
    }

    void AddDoor(float l, float r, float u, float d, float toX, float toY, unsigned __int8 toID, LPCWSTR file) {
        doors.emplace_back(l, r, u, d, toX, toY, toID, file);
    }
};

class Stopwatch {
public:
    std::chrono::steady_clock::time_point startTime;
    unsigned int duration;

    Stopwatch() {
        duration = 0;
    }

    void Start() {
        startTime = std::chrono::steady_clock::now();
    }

    void Stop() {
        duration = duration + int(std::chrono::duration<double>(std::chrono::steady_clock::now() - startTime).count());
    }
};


//-------------------------------
// Resource Management Functions
//-------------------------------
void ReleaseD2DResourcesFromMemory()
{
    // cleanup
    if (renderTarget)
    {
        renderTarget->Release();
        renderTarget = NULL;
    }

    for (auto& pair : bitmaps)
    {
        ID2D1Bitmap* bitmap = pair.second;
        if (bitmap)
        {
            bitmap->Release();
        }
    }
    bitmaps.clear();
}

void LoadSpritesToMemory(HWND hWnd, std::vector<LPCWSTR> spriteFilePaths) {
    HRESULT hr = S_OK;

    // If no render target yet
    if (!renderTarget) {

        // make a windows render target based on screen dimensions
        D2D1_SIZE_U size = D2D1::SizeU(screenX, screenY);
        hr = D2DFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(hWnd, size), &renderTarget);
    }

    if (FAILED(hr)) {
        return;
    }

    // used to convert PNGs to ID2D1Bitmaps
    IWICImagingFactory* bitmapFactory = NULL;
    hr = CoCreateInstance(CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory, reinterpret_cast<void**>(&bitmapFactory));

    if (FAILED(hr)) {
        return;
    }

    // convert each file from the vector of filepaths
    for (LPCWSTR filePath : spriteFilePaths) {

        // If the file path isn't already in the map
        if (bitmaps.find(filePath) == bitmaps.end()) {

            // creates decoder that reads image from filepath
            IWICBitmapDecoder* decoder = NULL;
            hr = bitmapFactory->CreateDecoderFromFilename(filePath, NULL, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &decoder);

            if (FAILED(hr)) {
                if (D2DFactory) D2DFactory->Release();
                bitmapFactory->Release();
                ReleaseD2DResourcesFromMemory();
                // Display a top-most, foreground error message box
                MessageBox(
                    NULL, // parent: NULL for desktop-level, or hWnd if you want relative to your window
                    (std::wstring(L"Sprite Missing: ") + filePath).c_str(),
                    L"Error",
                    MB_ICONERROR | MB_OK | MB_TOPMOST | MB_SETFOREGROUND | MB_SERVICE_NOTIFICATION
                );
                exit(EXIT_FAILURE);  // or use abort(); or return 1;
                return;
            }

            // PNGs will always have 1 frame, but a frame must be specified for converter->Initialize to work
            IWICBitmapFrameDecode* source = NULL;
            hr = decoder->GetFrame(0, &source);

            if (FAILED(hr)) {
                bitmapFactory->Release();
                decoder->Release();
                return;
            }

            // creating the converter
            IWICFormatConverter* converter = NULL;
            hr = bitmapFactory->CreateFormatConverter(&converter);

            if (FAILED(hr)) {
                bitmapFactory->Release();
                decoder->Release();
                source->Release();
                return;
            }

            // converts source image format to 32-bit RGB image with Alpha transparency
            hr = converter->Initialize(source, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, NULL, 0.0, WICBitmapPaletteTypeMedianCut);

            if (FAILED(hr)) {
                bitmapFactory->Release();
                decoder->Release();
                source->Release();
                converter->Release();
                return;
            }

            // Use converted file to ID2D1Bitmap that can be stored in our map
            ID2D1Bitmap* bitmap = NULL;
            hr = renderTarget->CreateBitmapFromWicBitmap(converter, NULL, &bitmap);

            if (SUCCEEDED(hr)) {
                bitmaps[filePath] = bitmap;
            }

            // Cleanup
            decoder->Release();
            source->Release();
            converter->Release();
        }
    }
    bitmapFactory->Release();
}

void TripErrorMissingFile(LPCWSTR file) {
    if (D2DFactory) D2DFactory->Release();
    ReleaseD2DResourcesFromMemory();
    // Display a top-most, foreground error message box
    MessageBox(
        NULL, // parent: NULL for desktop-level, or hWnd if you want relative to your window
        (std::wstring(L"Sprite Missing: ") + file).c_str(),
        L"Error",
        MB_ICONERROR | MB_OK | MB_TOPMOST | MB_SETFOREGROUND | MB_SERVICE_NOTIFICATION
    );
    exit(EXIT_FAILURE);  // or use abort(); or return 1;
    return;
}

//--------------
// Declarations
//--------------

std::vector<LPCWSTR> spriteFilePaths;
std::vector<Object> enemyBullets;
Player player;
Object pickup;
std::vector<Object> bases;
std::vector<Object> objects;
std::vector<Object> pickups;
Object background;
std::chrono::steady_clock::time_point timeSinceSpawn = std::chrono::steady_clock::now() - std::chrono::seconds(10);
std::unordered_map<std::pair<int, int>, std::vector<Star>, hash_function> starGrid;
std::unordered_map<std::pair<int, int>, std::vector<Asteroid>, hash_function> asteroids;
std::unordered_set<std::pair<int, int>, hash_function> pendingChunks;
std::mutex chunkInProgress;
std::vector<Environment> environments;
unsigned __int8 currEnvID(0);
std::vector<Object> UI;
float camPosX = 0;
Stopwatch stopwatch;
SaveStation saveStations[3];
int gameState = 1;


//-------------------------
// Consolidatory Functions 
//-------------------------

void InitializeAssets() {
    player.power = 2;
    player.health = 100;
    player.maxHP = 100;
    player.inAscendingSequence = true;
    player.currentFramePath = player.descentFrames[5];
    player.angleRadians = -pi / 4;

    environments.emplace_back(nullptr, 1, true);

    background.currentFramePath = files.background;

    // Initializations
    std::pair <double, double> turretOffsets[12];
    turretOffsets[0].first = -130.5;
    turretOffsets[1].first = -151.5;
    turretOffsets[2].first = -109.5;
    turretOffsets[3].first = 128.5;
    turretOffsets[4].first = 149.5;
    turretOffsets[5].first = 107.5;
    turretOffsets[6].first = -130.5;
    turretOffsets[7].first = -151.5;
    turretOffsets[8].first = -109.5;
    turretOffsets[9].first = 128.5;
    turretOffsets[10].first = 149.5;
    turretOffsets[11].first = 107.5;

    turretOffsets[0].second = -153.5;
    turretOffsets[1].second = -111.5;
    turretOffsets[2].second = -111.5;
    turretOffsets[3].second = -153.5;
    turretOffsets[4].second = -111.5;
    turretOffsets[5].second = -111.5;
    turretOffsets[6].second = 100.5;
    turretOffsets[7].second = 142.5;
    turretOffsets[8].second = 142.5;
    turretOffsets[9].second = 98.5;
    turretOffsets[10].second = 140.5;
    turretOffsets[11].second = 140.5;

    bases.emplace_back(files.base);
    bases.at(0).xPos = .3 * mapSizeX;
    bases.at(0).yPos = .2 * mapSizeY;
    bases.emplace_back(files.base);
    bases.at(1).xPos = .5 * mapSizeX;
    bases.at(1).yPos = .8 * mapSizeY;
    bases.emplace_back(files.base);
    bases.at(2).xPos = .75 * mapSizeX;
    bases.at(2).yPos = .5 * mapSizeY;
    std::pair <double, double> shieldOffsets[12];
    shieldOffsets[0].first = -130.5;
    shieldOffsets[1].first = -130.5;
    shieldOffsets[2].first = 128.5;
    shieldOffsets[3].first = 128.5;
    shieldOffsets[0].second = -127.5;
    shieldOffsets[1].second = 126.5;
    shieldOffsets[2].second = -127.5;
    shieldOffsets[3].second = 124.5;
    for (int i = 0; i < bases.size(); i++) {
        for (int j = 0; j <= 11; j++) {
            objects.emplace_back(
                L"Turret",
                bases.at(i).xPos + turretOffsets[j].first,
                bases.at(i).yPos + turretOffsets[j].second,
                3,
                files.turret,
                true,
                0,
                files.turret_Damaged,
                files.turret,
                0,
                0,
                false,
                true,
                false
            );
            objects[j + (i * 17)].turnRadius = pi / 4;
            objects[j + (i * 17)].shotSpeed = std::chrono::milliseconds(1250);
            objects[j + (i * 17)].shotVelocity = 5;
            objects[j + (i * 17)].shotType = files.basicShotBlue;
            objects[j + (i * 17)].defaultShotEffect = files.basicShotEffectBlue1;
            objects[j + (i * 17)].power = 10;
        }
        for (int j = 0; j <= 3; j++) {
            objects.emplace_back(
                L"Shield Generator",
                bases.at(i).xPos + shieldOffsets[j].first,
                bases.at(i).yPos + shieldOffsets[j].second,
                5,
                files.shield_Generator,
                true,
                0,
                files.shield_Generator_Damaged,
                files.shield_Generator,
                0,
                0,
                false,
                true,
                false
            );
        }
        objects.emplace_back(
            L"Base Door",
            bases.at(i).xPos - 181.5,
            bases.at(i).yPos - 0.5,
            -1,
            files.base_Door,
            false,
            0,
            nullptr,
            files.base_Door,
            0,
            0,
            false,
            true,
            false
        );
        D2D1_SIZE_F size = bitmaps[files.base_Door]->GetSize();
        float width = float(size.width) / 2;
        float height = float(size.height) / 2;
        float hboxL = bases.at(i).xPos - 181.5;
        float hboxU = bases.at(i).yPos - 0.5;
        environments.at(0).AddDoor(hboxL - width, hboxL + width, hboxU - height, hboxU + height, 6, 112, i + 1, files.base_Door);
        environments.emplace_back(files.base_Interior, i + 2, false);
        environments.at(i + 1).AddDoor(0, 2, 22, 187, hboxL - 40, hboxU, 0, nullptr);
    }

    UI.emplace_back(L"Status_Bar", leftBoundary + (4 * scalerX), 4 * scalerY, 0,
        files.status_Bar, false, 0, nullptr, files.status_Bar, 0, 0, false, false, false);

    UI.emplace_back(L"Health_Bar_Bottom", leftBoundary + (6 * scalerX), (6 * scalerY), 0,
        files.health_Bar_Bottom, false, 0, nullptr, files.health_Bar_Bottom, 0, 0, false, false, false);

    UI.emplace_back(L"Health_Bar_Top", leftBoundary + (6 * scalerX), (5 * scalerY), 0,
        files.health_Bar_Top, false, 0, nullptr, files.health_Bar_Top, 0, 0, false, false, false);

    UI.emplace_back(L"Boost_Bar_Top", leftBoundary + (6.05 * scalerX), (11 * scalerY), 0,
        files.boost_Bar_top, false, 0, nullptr, files.boost_Bar_top, 0, 0, false, false, false);

    UI.emplace_back(L"Boost_Bar_Bottom", leftBoundary + (6.05 * scalerX), (13 * scalerY), 0,
        files.boost_Bar_bottom, false, 0, nullptr, files.boost_Bar_bottom, 0, 0, false, false, false);
}

void CycleShotEffect(Object& object) {
    if (object.defaultShotEffect == files.basicShotEffectBlue1) {
        if (object.shotFrame == files.basicShotEffectBlue1 &&
            (std::chrono::steady_clock::now() - object.lastShotTime >= std::chrono::nanoseconds(16666666 * 2))) {
            object.lastShotTime = std::chrono::steady_clock::now();
            object.shotFrame = files.basicShotEffectBlue2;
        }
        else if (object.shotFrame == files.basicShotEffectBlue2 &&
            (std::chrono::steady_clock::now() - object.lastShotTime >= std::chrono::nanoseconds(16666666 * 2))) {
            object.lastShotTime = std::chrono::steady_clock::now();
            object.shotFrame = files.basicShotEffectBlue3;
        }
        else if (object.shotFrame == files.basicShotEffectBlue3 &&
            (std::chrono::steady_clock::now() - object.lastShotTime >= std::chrono::nanoseconds(16666666 * 2))) {
            object.lastShotTime = std::chrono::steady_clock::now();
            object.shotFrame = files.basicShotEffectBlue4;
        }
        else if (object.shotFrame == files.basicShotEffectBlue4 &&
            (std::chrono::steady_clock::now() - object.lastShotTime >= std::chrono::nanoseconds(16666666 * 2))) {
            object.lastShotTime = std::chrono::steady_clock::now();
            object.shotFrame = files.basicShotEffectBlue5;
        }
        else if ((object.shotFrame == files.basicShotEffectBlue5) &&
            (std::chrono::steady_clock::now() - object.lastShotTime >= std::chrono::nanoseconds(16666666 * 2))) {
            object.shotFrame = nullptr;
        }
    }
    else if (object.defaultShotEffect == files.basicShotEffectPurple1) {
        if (object.shotFrame == files.basicShotEffectPurple1 &&
            (std::chrono::steady_clock::now() - object.lastShotTime >= std::chrono::nanoseconds(16666666 * 2))) {
            object.lastShotTime = std::chrono::steady_clock::now();
            object.shotFrame = files.basicShotEffectPurple2;
        }
        else if (object.shotFrame == files.basicShotEffectPurple2 &&
            (std::chrono::steady_clock::now() - object.lastShotTime >= std::chrono::nanoseconds(16666666 * 2))) {
            object.lastShotTime = std::chrono::steady_clock::now();
            object.shotFrame = files.basicShotEffectPurple3;
        }
        else if (object.shotFrame == files.basicShotEffectPurple3 &&
            (std::chrono::steady_clock::now() - object.lastShotTime >= std::chrono::nanoseconds(16666666 * 2))) {
            object.lastShotTime = std::chrono::steady_clock::now();
            object.shotFrame = files.basicShotEffectPurple4;
        }
        else if (object.shotFrame == files.basicShotEffectPurple4 &&
            (std::chrono::steady_clock::now() - object.lastShotTime >= std::chrono::nanoseconds(16666666 * 2))) {
            object.lastShotTime = std::chrono::steady_clock::now();
            object.shotFrame = files.basicShotEffectPurple5;
        }
        else if ((object.shotFrame == files.basicShotEffectPurple5) &&
            (std::chrono::steady_clock::now() - object.lastShotTime >= std::chrono::nanoseconds(16666666 * 2))) {
            object.shotFrame = nullptr;
        }
    }
}

void UpdateBackgroundElements(double deltaTime) {
    int rightBound = (int(player.xPos) / 256) + 2;
    int lowBound = (int(player.yPos) / 224) + 2;

    int leftBound = ((int(player.xPos) - 128) / 256) - 1;
    int upBound = (int(player.yPos) / 224) - 1;

    for (int y = upBound; y <= lowBound; ++y) {
        for (int x = leftBound; x <= rightBound; ++x) {
            std::pair<int, int> cell = { x, y };
            auto it = starGrid.find(cell);
            if (it != starGrid.end()) {
                for (Star& star : it->second) {
                    star.Pulsate(deltaTime);
                }
            }
            else {
                if (pendingChunks.count(cell)) {
                    continue;
                }
                else {
                    pendingChunks.insert(cell);
                }

                if (false) {//isMultiCore) {
                    std::lock_guard<std::mutex> lock(chunkInProgress);
                    std::thread([cell, x, y]() mutable {
                        std::vector<std::pair<int, int>> chunks = { cell };
                    std::uniform_int_distribution<int> range(1, 100000);

                    for (int i = y * 224; i <= ((y * 224) + 224); i++) {
                        for (int j = x * 256; j <= ((x * 256) + 256); j++) {
                            int roll = range(generator);
                            if (roll <= 250) {
                                bool starFound = false;
                                auto it = starGrid.find(cell);
                                if (it != starGrid.end()) {
                                    for (const auto& star : it->second) {
                                        if (std::abs(star.xPos - j) <= 1 || std::abs(star.yPos - i) <= 1) {
                                            starFound = true;
                                            break;
                                        }
                                    }
                                }
                                if (!starFound) {
                                    int r, g, b;
                                    roll = range(generator);
                                    if (roll <= 92000) {
                                        r = g = b = 200;
                                    }
                                    else if (roll <= 94660) {
                                        r = 102;
                                        g = 138;
                                        b = 200;
                                    }
                                    else if (roll <= 97320) {
                                        r = 200;
                                        g = 200;
                                        b = 200;
                                    }
                                    else {
                                        r = 200;
                                        g = 53;
                                        b = 46;
                                    }
                                    roll = range(generator);
                                    float alpha = max(float(roll) / 100000.0, 0.01);

                                    std::lock_guard<std::mutex> lock(chunkInProgress);
                                    starGrid[cell].emplace_back(j, i, r, g, b, alpha);
                                }
                            }
                            roll = range(generator);
                            if (roll <= 2) {
                                std::lock_guard<std::mutex> lock(chunkInProgress);
                                asteroids[cell].emplace_back(j, i);
                            }
                        }
                    }

                    std::lock_guard<std::mutex> lock(chunkInProgress);
                    pendingChunks.erase(cell);
                        }).detach();

                }
                else {
                    std::uniform_int_distribution<int> range(1, 100000);
                    for (int i = y * 224; i <= ((y * 224) + 224); i++) {
                        for (int j = x * 256; j <= ((x * 256) + 256); j++) {
                            int roll = range(generator);
                            if (roll <= 250) {
                                bool starFound = false;
                                auto it = starGrid.find(cell);
                                if (it != starGrid.end()) {
                                    for (const auto& star : it->second) {
                                        if (std::abs(star.xPos - j) <= 1 || std::abs(star.yPos - i) <= 1) {
                                            starFound = true;
                                            break;
                                        }
                                    }
                                }
                                if (!starFound) {
                                    int r, g, b;
                                    roll = range(generator);
                                    if (roll <= 92000) {
                                        r = g = b = 200;
                                    }
                                    else if (roll <= 94660) {
                                        r = 102;
                                        g = 138;
                                        b = 200;
                                    }
                                    else if (roll <= 97320) {
                                        r = 200;
                                        g = 200;
                                        b = 200;
                                    }
                                    else {
                                        r = 200;
                                        g = 53;
                                        b = 46;
                                    }
                                    roll = range(generator);
                                    float alpha = max(float(roll) / 100000.0, 0.01);
                                    starGrid[cell].emplace_back(j, i, r, g, b, alpha);
                                }
                            }
                            roll = range(generator);
                            if (roll <= 2) {
                                asteroids[cell].emplace_back(j, i);
                            }
                        }
                    }
                    pendingChunks.erase(cell);
                }
            }

            auto it2 = asteroids.find(cell);
            if (it2 != asteroids.end()) {
                for (int i = 0; i < it2->second.size(); i++) {
                    it2->second.at(i).UpdateHitBox();
                    int j = 0;
                    for (auto& b : player.bullets) {
                        if (b.CheckCollision(it2->second.at(i))) {
                            float x = it2->second.at(i).xPos;
                            float y = it2->second.at(i).yPos;
                            it2->second.erase(it2->second.begin() + i);
                            b.currentFramePath = files.explosion1;
                            b.collided = true;
                            b.explosionBegin = std::chrono::steady_clock::now();

                            std::uniform_int_distribution<int> distribution(1, 2);
                            int qty = distribution(generator);
                            float percentage = player.health / player.maxHP;
                            for (int j = 0; j < qty; j++) {
                                float percentage = player.health / player.maxHP;
                                std::uniform_int_distribution<int> distribution(1, 100);
                                int rng = distribution(generator);
                                bool rollHP = false;
                                std::uniform_real_distribution<float> fdistribution(-pi, pi);
                                float angle = fdistribution(generator);
                                float xOffset = 2 * sin(angle);
                                angle = fdistribution(generator);
                                float yOffset = 2 * sin(angle);
                                if (((percentage <= 0.75) && rng >= 90) || ((percentage <= 0.5) && rng >= 80) || ((percentage <= 0.33) && rng >= 50)) {
                                    rollHP = true;
                                }
                                if (rollHP) {
                                    objects.emplace_back(L"Health Pickup", x + xOffset, y + yOffset, 0, files.hp_pickup_2, false, 0, nullptr, files.hp_pickup_2, 0, 0, false, true, false);
                                    objects.back().genericFrameMarker = std::chrono::steady_clock::now();
                                    objects.back().pickup = true;
                                }
                                else {
                                    rng = distribution(generator);
                                    if (rng <= 85) {
                                        objects.emplace_back(L"Red Jewel", x + xOffset, y + yOffset, 0, files.jewel_Red, false, 0, nullptr, files.jewel_Red, 0, 0, false, true, false);
                                    }
                                    else if (rng <= 94) {
                                        objects.emplace_back(L"Blue Jewel", x + xOffset, y + yOffset, 0, files.jewel_Blue, false, 0, nullptr, files.jewel_Blue, 0, 0, false, true, false);
                                    }
                                    else if (rng <= 98) {
                                        objects.emplace_back(L"Purple Jewel", x + xOffset, y + yOffset, 0, files.jewel_Purple, false, 0, nullptr, files.jewel_Purple, 0, 0, false, true, false);
                                    }
                                    else {
                                        objects.emplace_back(L"Yellow Jewel", x + xOffset, y + yOffset, 0, files.jewel_Yellow, false, 0, nullptr, files.jewel_Yellow, 0, 0, false, true, false);
                                    }
                                    objects.back().UpdateHitBox();
                                    objects.back().pickup = true;
                                }
                            }
                            break;
                        }
                        j++;
                    }
                }
            }
        }
    }
}

void HandleEnemySpawns(double deltaTime, bool spawnEnemies, bool spawnsExist) {
    for (int i = 0; i < objects.size(); i++) {
        if (objects.at(i).randomSpawner) {
            if ((abs(objects.at(i).xPos - player.xPos) > 256) || (abs(objects.at(i).yPos - player.yPos) > 224)) {
                objects.erase(objects.begin() + i);
                i--;
                timeSinceSpawn = std::chrono::steady_clock::now();
                continue;
            }
            spawnEnemies = false;
            spawnsExist = true;
        }
        //debug mode
        spawnEnemies = false;
    }
    if (!player.sideMode && (spawnEnemies && (std::chrono::steady_clock::now() - timeSinceSpawn >= std::chrono::seconds(10)))) {
        for (int i = 0; i < 3; i++) {
            std::uniform_int_distribution<int> distribution(0, 1);
            bool binary = distribution(generator);
            std::uniform_int_distribution<int> fdistribution(0, 960);
            int placement = fdistribution(generator);
            int xOffset = 0;
            int yOffset = 0;
            if (placement <= 256) {
                xOffset = placement / 2;
                yOffset = -124;
            }
            else if (placement >= 480 && placement <= 736) {
                xOffset - (placement - 480) / 2;
                yOffset = 124;
            }
            else if (placement > 256 && placement < 480) {
                yOffset = (placement - 256) / 2;
                xOffset = 140;
            }
            else {
                yOffset = (placement - 736) / 2;
                xOffset = -140;
            }
            if (binary) {
                objects.emplace_back(L"Bomber Drone",
                    player.xPos + xOffset,
                    player.yPos + yOffset,
                    2,
                    files.bomber_drone,
                    true,
                    0,
                    files.bomber_drone,
                    files.bomber_drone,
                    0.25,
                    0.25,
                    true,
                    true,
                    true
                );
                objects.back().turnRadius = pi / 4;
                objects.back().shotSpeed = std::chrono::milliseconds(6000);
                objects.back().shotVelocity = 2;
                objects.back().shotType = files.drone_Shot_1;
                objects.back().defaultShotEffect = files.basicShotEffectPurple1;
                objects.back().power = 10;
                objects.back().randomSpawner = true;
                objects.back().angleRadians = atan2(objects.back().yPos - player.yPos, objects.back().xPos - player.xPos) + pi;
            }
            else {
                objects.emplace_back(L"Enemy Ship 1",
                    player.xPos + xOffset,
                    player.yPos + yOffset,
                    2,
                    files.enemyShip1,
                    true,
                    0,
                    files.enemyShip1,
                    files.enemyShip1,
                    0.75,
                    0.75,
                    true,
                    true,
                    true
                );
                objects.back().turnRadius = pi / 2;
                objects.back().shotSpeed = std::chrono::milliseconds(50);
                objects.back().shotVelocity = 4;
                objects.back().shotType = files.basicShotPurple;
                objects.back().defaultShotEffect = files.basicShotEffectPurple1;
                objects.back().power = 10;
                objects.back().randomSpawner = true;
                objects.back().angleRadians = atan2(objects.back().yPos - player.yPos, objects.back().xPos - player.xPos) + pi;
                objects.back().burstFire = true;
            }
        }
    }
}

void UpdateMasterObjectLogic(double deltaTime, int& spawnerCounter) {
    // Master Object logic
    if (!objects.empty()) {
        for (int i = 0; i < objects.size(); i++) {
            if (objects[i].currentFramePath != nullptr) {
                if (objects[i].destructible) {
                    if (objects[i].health <= 0) {
                        if (objects[i].dead == false) {
                            std::uniform_int_distribution<int> distribution(3, 5);
                            int qty = distribution(generator);
                            float percentage = player.health / player.maxHP;
                            for (int j = 0; j < qty; j++) {
                                std::uniform_int_distribution<int> distribution(1, 100);
                                int rng = distribution(generator);
                                bool rollHP = false;
                                std::uniform_real_distribution<float> fdistribution(-pi, pi);
                                float angle = fdistribution(generator);
                                float xOffset = 8 * sin(angle);
                                angle = fdistribution(generator);
                                float yOffset = 8 * sin(angle);
                                if (((percentage <= 0.75) && rng >= 90) || ((percentage <= 0.5) && rng >= 80) || ((percentage <= 0.33) && rng >= 50)) {
                                    rollHP = true;
                                }
                                if (rollHP) {
                                    objects.emplace_back(L"Health Pickup", objects.at(i).xPos + xOffset, objects.at(i).yPos + yOffset, 0, files.hp_pickup_2, false, 0, nullptr, files.hp_pickup_2, 0, 0, false, true, false);
                                    objects.back().genericFrameMarker = std::chrono::steady_clock::now();
                                    objects.back().pickup = true;
                                }
                                else {
                                    rng = distribution(generator);
                                    if (rng <= 85) {
                                        objects.emplace_back(L"Red Jewel", objects.at(i).xPos + xOffset, objects.at(i).yPos + yOffset, 0, files.jewel_Red, false, 0, nullptr, files.jewel_Red, 0, 0, false, true, false);
                                    }
                                    else if (rng <= 94) {
                                        objects.emplace_back(L"Blue Jewel", objects.at(i).xPos + xOffset, objects.at(i).yPos + yOffset, 0, files.jewel_Blue, false, 0, nullptr, files.jewel_Blue, 0, 0, false, true, false);
                                    }
                                    else if (rng <= 98) {
                                        objects.emplace_back(L"Purple Jewel", objects.at(i).xPos + xOffset, objects.at(i).yPos + yOffset, 0, files.jewel_Purple, false, 0, nullptr, files.jewel_Purple, 0, 0, false, true, false);
                                    }
                                    else {
                                        objects.emplace_back(L"Yellow Jewel", objects.at(i).xPos + xOffset, objects.at(i).yPos + yOffset, 0, files.jewel_Yellow, false, 0, nullptr, files.jewel_Yellow, 0, 0, false, true, false);
                                    }
                                    objects.back().UpdateHitBox();
                                    objects.back().pickup = true;
                                }
                            }
                            objects[i].dead = true;
                            objects[i].currentFramePath = files.explosion1;
                            objects[i].lastDeathFrameUpdate = std::chrono::steady_clock::now();
                        }
                        bool updated(false);
                        std::chrono::nanoseconds elapsedTime = std::chrono::steady_clock::now() - objects[i].lastDeathFrameUpdate;
                        if (objects[i].currentFramePath == files.explosion1 && !objects[i].reverseDeathAnimation && elapsedTime >= std::chrono::nanoseconds(66666666)) {
                            objects[i].currentFramePath = files.explosion2;
                            updated = true;
                        }
                        else if (objects[i].currentFramePath == files.explosion2 && !objects[i].reverseDeathAnimation && elapsedTime >= std::chrono::nanoseconds(66666666)) {
                            objects[i].currentFramePath = files.explosion3;
                            updated = true;
                        }
                        else if (objects[i].currentFramePath == files.explosion3 && !objects[i].reverseDeathAnimation && elapsedTime >= std::chrono::nanoseconds(66666666)) {
                            objects[i].currentFramePath = files.explosion4;
                            updated = true;
                        }
                        else if (objects[i].currentFramePath == files.explosion4 && !objects[i].reverseDeathAnimation && elapsedTime >= std::chrono::nanoseconds(66666666)) {
                            objects[i].currentFramePath = files.explosion3;
                            updated = true;
                            objects[i].reverseDeathAnimation = true;
                        }
                        else if (objects[i].currentFramePath == files.explosion3 && objects[i].reverseDeathAnimation && elapsedTime >= std::chrono::nanoseconds(66666666)) {
                            objects[i].currentFramePath = files.explosion2;
                            updated = true;
                        }
                        else if (objects[i].currentFramePath == files.explosion2 && objects[i].reverseDeathAnimation && elapsedTime >= std::chrono::nanoseconds(66666666)) {
                            objects[i].currentFramePath = files.explosion1;
                            updated = true;
                        }
                        else if (objects[i].currentFramePath == files.explosion1 && objects[i].reverseDeathAnimation && elapsedTime >= std::chrono::nanoseconds(33333333)) {
                            objects.erase(objects.begin() + i);
                            i--;
                            continue;
                        }
                        if (updated) {
                            objects[i].lastDeathFrameUpdate = std::chrono::steady_clock::now();
                        }
                    }
                    if (!objects[i].dead) {
                        if (std::chrono::steady_clock::now() - objects[i].damageBegins >= std::chrono::nanoseconds(16666666 * 4)) {
                            objects[i].damaged = false;
                        }
                        if (objects[i].damaged) {
                            objects[i].currentFramePath = objects[i].damagedFrame;
                        }
                        else {
                            objects[i].currentFramePath = objects[i].defaultFrame;
                        }
                    }
                }
                if (!objects[i].dead) {
                    if (objects[i].rotatable) {
                        double newAngle = atan2(player.yPos - objects[i].yPos, player.xPos - objects[i].xPos);
                        double angleDelta = newAngle - objects[i].angleRadians;
                        if (angleDelta > pi) {
                            angleDelta -= (2 * pi);
                        }
                        else if (angleDelta < -pi) {
                            angleDelta += (2 * pi);
                        }
                        if (angleDelta > 0) {
                            objects[i].angleRadians += objects[i].turnRadius * ((deltaTime / 50) / 1);
                        }
                        else {
                            objects[i].angleRadians -= objects[i].turnRadius * ((deltaTime / 50) / 1);
                        }

                        objects[i].xPos += objects[i].xVel * deltaTime * cos(objects[i].angleRadians);
                        objects[i].yPos += objects[i].yVel * deltaTime * sin(objects[i].angleRadians);
                    }
                    if (objects[i].canFire && abs(objects[i].xPos - player.xPos) < 192 && abs(objects[i].yPos - player.yPos) < 168) {
                        double newAngle = atan2(player.yPos - objects[i].yPos, player.xPos - objects[i].xPos);
                        double angleDelta = newAngle - objects[i].angleRadians;
                        if (angleDelta > pi) {
                            angleDelta -= (2 * pi);
                        }
                        else if (angleDelta < -pi) {
                            angleDelta += (2 * pi);
                        }
                        if (objects[i].burstFire && !objects[i].burstAvailable && (std::chrono::steady_clock::now() - objects[i].timeSinceBurst >= std::chrono::seconds(2))) {
                            objects[i].burstAvailable = true;
                            objects[i].shotsInBurst = 0;
                        }
                        if (abs(angleDelta) <= pi / 12 && !objects[i].shotFrame && std::chrono::steady_clock::now() - objects[i].lastShotTime >= objects[i].shotSpeed
                            && ((objects[i].burstFire && objects[i].burstAvailable) || !objects[i].burstFire)) {
                            // Create new bullet, position it with player, give it its velocities
                            if (objects[i].burstFire) {
                                objects[i].shotsInBurst++;
                                if (objects[i].shotsInBurst >= 3) {
                                    objects[i].burstAvailable = false;
                                }
                                else if (objects[i].shotsInBurst == 1) {
                                    objects[i].timeSinceBurst = std::chrono::steady_clock::now();
                                }
                            }
                            enemyBullets.emplace_back(objects[i].shotType);
                            enemyBullets.back().xPos = objects[i].xPos;
                            enemyBullets.back().yPos = objects[i].yPos;
                            enemyBullets.back().shotVelocity = objects[i].shotVelocity;
                            enemyBullets.back().power = objects[i].power;
                            enemyBullets.back().defaultFrame = objects.at(i).shotType;
                            enemyBullets.back().UpdateHitBox();
                            enemyBullets.back().angleRadians = objects[i].angleRadians + pi / 2;
                            enemyBullets.back().yVel = round(-cos(enemyBullets.back().angleRadians) * 100) / 100;
                            if (abs(enemyBullets.back().yVel) < 0.0001) {
                                enemyBullets.back().yVel = 0;
                            }
                            enemyBullets.back().xVel = round(sin(enemyBullets.back().angleRadians) * 100) / 100;
                            if (abs(enemyBullets.back().xVel) < 0.0001) {
                                enemyBullets.back().xVel = 0;
                            }

                            //enemyBullets.back().modulator = double((rand() % 628)) / 100;
                            //bullets.back().modulatorDelta = double((rand() % 5) + 15) / 100;
                            //int result = (rand() % 2);
                            //if (modulatorTicker == true) {
                            //    modulatorTicker = false;
                            //    bullets.back().modulatorPositiveDelta = false;
                            //}
                            //else {
                            //    modulatorTicker = true;
                            //    bullets.back().modulatorPositiveDelta = true;
                            //}
                            objects[i].shotFrame = objects[i].defaultShotEffect;
                        }
                        else {
                            CycleShotEffect(objects[i]);
                        }
                    }
                    objects[i].UpdateHitBox();
                }
                if (objects.at(i).pickup) {
                    if (std::chrono::steady_clock::now() - objects.at(i).timesinceInception >= std::chrono::milliseconds(750)) {
                        float dx = (player.xPos - objects.at(i).xPos) / 35;
                        float dy = (player.yPos - objects.at(i).yPos) / 35;
                        double length = sqrt(dx * dx + dy * dy);
                        objects.at(i).xVel = (dx / length) * 5;
                        objects.at(i).yVel = (dy / length) * 5;
                        objects.at(i).xPos += objects.at(i).xVel * deltaTime;
                        objects.at(i).yPos += objects.at(i).yVel * deltaTime;
                    }
                    if (objects.at(i).name == L"Health Pickup") {
                        if (player.CheckCollision(objects.at(i))) {
                            player.health = min(player.health + 10, player.maxHP);
                            objects.erase(objects.begin() + i);
                            i--;
                            continue;
                        }
                        if (std::chrono::steady_clock::now() - objects.at(i).genericFrameMarker >= std::chrono::seconds(2)) {
                            objects.at(i).genericFrameMarker = std::chrono::steady_clock::now();
                            objects.at(i).currentFramePath = files.hp_pickup_2;
                        }
                        else if (std::chrono::steady_clock::now() - objects.at(i).genericFrameMarker >= std::chrono::milliseconds(700)) {
                            objects.at(i).currentFramePath = files.hp_pickup_3;
                        }
                        else if (std::chrono::steady_clock::now() - objects.at(i).genericFrameMarker >= std::chrono::milliseconds(500)) {
                            objects.at(i).currentFramePath = files.hp_pickup_2;
                        }
                        else if (std::chrono::steady_clock::now() - objects.at(i).genericFrameMarker >= std::chrono::milliseconds(250)) {
                            objects.at(i).currentFramePath = files.hp_pickup_1;
                        }
                    }
                }
                if (objects.at(i).randomSpawner) {
                    spawnerCounter++;
                }
            }
        }
    }
}

void UpdateEnemyShootingLogic(double deltaTime) {
    // Enemy Bullet Logic
    if (!enemyBullets.empty()) {
        for (int i = 0; i < enemyBullets.size(); i++) {

            if (enemyBullets.at(i).collided && std::chrono::steady_clock::now() - enemyBullets.at(i).explosionBegin > std::chrono::nanoseconds(16666666 * 6)) {
                if (enemyBullets.at(i).defaultFrame != files.drone_Shot_1) {
                    enemyBullets.erase(enemyBullets.begin() + i);
                    i--;
                    continue;
                }
            }
            else if (!enemyBullets.at(i).collided) {
                if (enemyBullets.at(i).defaultFrame == files.drone_Shot_1) {
                    if (std::chrono::steady_clock::now() - enemyBullets.at(i).timesinceInception >= std::chrono::seconds(6)) {
                        enemyBullets.erase(enemyBullets.begin() + i);
                        i--;
                        continue;
                    }
                    Player playerWithRadius = player;
                    int buffer = 20;
                    playerWithRadius.hitbox.right += buffer;
                    playerWithRadius.hitbox.left -= buffer;
                    playerWithRadius.hitbox.up -= buffer;
                    playerWithRadius.hitbox.down += buffer;
                    if (std::chrono::steady_clock::now() - enemyBullets.at(i).timesinceInception >= std::chrono::seconds(2) || enemyBullets.at(i).CheckCollision(playerWithRadius) || enemyBullets.at(i).exploding) {
                        enemyBullets.at(i).xVel = 0;
                        enemyBullets.at(i).yVel = 0;
                        if (!enemyBullets.at(i).exploding) {
                            enemyBullets.at(i).exploding = true;
                            enemyBullets.at(i).genericFrameMarker = std::chrono::steady_clock::now();
                        }
                        if (std::chrono::steady_clock::now() - enemyBullets.at(i).genericFrameMarker >= std::chrono::milliseconds(550) || enemyBullets.at(i).pulsating) {
                            if (!enemyBullets.at(i).pulsating) {
                                enemyBullets.at(i).pulsating = true;
                                enemyBullets.at(i).genericFrameMarker = std::chrono::steady_clock::now();
                            }
                            if (std::chrono::steady_clock::now() - enemyBullets.at(i).genericFrameMarker >= std::chrono::milliseconds(333)) {
                                if (enemyBullets.at(i).currentFramePath == files.drone_Shot_6) {
                                    enemyBullets.at(i).currentFramePath = files.drone_Shot_7;
                                    enemyBullets.at(i).genericFrameMarker = std::chrono::steady_clock::now();
                                }
                                else {
                                    enemyBullets.at(i).currentFramePath = files.drone_Shot_6;
                                    enemyBullets.at(i).genericFrameMarker = std::chrono::steady_clock::now();
                                }
                            }
                        }
                        else if (std::chrono::steady_clock::now() - enemyBullets.at(i).genericFrameMarker >= std::chrono::milliseconds(300)) {
                            enemyBullets.at(i).currentFramePath = files.drone_Shot_6;
                        }
                        else if (std::chrono::steady_clock::now() - enemyBullets.at(i).genericFrameMarker >= std::chrono::milliseconds(150)) {
                            enemyBullets.at(i).currentFramePath = files.drone_Shot_5;
                        }
                        else {
                            enemyBullets.at(i).currentFramePath = files.drone_Shot_4;
                        }
                    }
                    else {
                        if (std::chrono::steady_clock::now() - enemyBullets.at(i).genericFrameMarker >= std::chrono::milliseconds(800)) {
                            enemyBullets.at(i).currentFramePath = files.drone_Shot_1;
                            enemyBullets.at(i).genericFrameMarker = std::chrono::steady_clock::now();
                        }
                        else if (std::chrono::steady_clock::now() - enemyBullets.at(i).genericFrameMarker >= std::chrono::milliseconds(600)) {
                            enemyBullets.at(i).currentFramePath = files.drone_Shot_2;
                        }
                        else if (std::chrono::steady_clock::now() - enemyBullets.at(i).genericFrameMarker >= std::chrono::milliseconds(400)) {
                            enemyBullets.at(i).currentFramePath = files.drone_Shot_3;
                        }
                        else if (std::chrono::steady_clock::now() - enemyBullets.at(i).genericFrameMarker >= std::chrono::milliseconds(300)) {
                            enemyBullets.at(i).currentFramePath = files.drone_Shot_2;
                        }
                    }

                }
                if (!player.dead) {
                    if (enemyBullets.at(i).CheckCollision(player)) {
                        if (enemyBullets.at(i).defaultFrame == files.drone_Shot_1 && (enemyBullets.at(i).exploding || enemyBullets.at(i).pulsating)) {
                            enemyBullets.at(i).power = 1;
                        }
                        else {
                            //object.damageBegins = std::chrono::steady_clock::now();
                            //object.currentFramePath = object.damagedFrame;
                            enemyBullets.at(i).currentFramePath = files.explosion1;
                            enemyBullets.at(i).collided = true;
                            enemyBullets.at(i).explosionBegin = std::chrono::steady_clock::now();
                        }
                        player.damaged = true;
                        player.health -= enemyBullets.at(i).power * deltaTime;
                        if (player.health <= 0) {
                            player.dead = true;
                            player.currentFramePath = files.player_Death_Animation_1;
                            player.lastDeathFrameUpdate = std::chrono::steady_clock::now();
                        }
                    }
                }
                if (!enemyBullets.at(i).collided) {
                    enemyBullets.at(i).xPos += enemyBullets.at(i).shotVelocity * (deltaTime * enemyBullets.at(i).xVel);
                    enemyBullets.at(i).yPos += enemyBullets.at(i).shotVelocity * (deltaTime * enemyBullets.at(i).yVel);
                }
                enemyBullets.at(i).UpdateHitBox();
            }
        }
    }
}

void UpdateOverworldAssets() {
    if (environments.at(currEnvID).overworld) {
        bool shieldGeneratorFound = false;
        for (auto object : objects) {
            if (object.name == L"Shield Generator") {
                shieldGeneratorFound = true;
                break;
            }
        }

        if (!shieldGeneratorFound) {
            for (auto object = objects.begin(); object != objects.end(); ) {
                if (object->name == L"Base Door") {
                    object = objects.erase(object);
                    break;
                }
                if (object != objects.end()) {
                    ++object;
                }
            }
        }

        bool baseDoorFound = false;
        for (auto object : objects) {
            if (object.name == L"Base Door") {
                //baseDoorFound = true;
                break;
            }
        }
    }
}

void CheckPickupCollision() {
    if (pickup.currentFramePath) {
        if (player.CheckCollision(pickup)) {
            player.doubleShot = true;
            pickup.xPos = 0;
            pickup.yPos = 0;
            pickup.currentFramePath = nullptr;
        }
    }
    for (int i = 0; i < objects.size(); i++) {
        if (objects.at(i).pickup) {
            if (player.CheckCollision(objects.at(i))) {
                if (objects.at(i).name == L"Health Pickup") {
                    player.health = min(player.health + 10, player.maxHP);
                }
                player.currencyAcquired = std::chrono::steady_clock::now();
                if (objects.at(i).name == L"Red Jewel") {
                    player.currency += 1;
                }
                else if (objects.at(i).name == L"Purple Jewel") {
                    player.currency += 5;
                }
                else if (objects.at(i).name == L"Yellow Jewel") {
                    player.currency += 10;
                }
                else if (objects.at(i).name == L"Blue Jewel") {
                    player.currency += 2;
                }
                objects.erase(objects.begin() + i);
                i--;
                continue;
            }
        }
    }
}

void CheckEnvironmentCollisions(std::vector<Environment> envs) {
    for (auto door : envs.at(currEnvID).doors) {
        if (player.CheckCollision(door)) {
            std::set<int> interiodIds = { 1, 2, 3 };
            if (interiodIds.count(door.destID) > 0) {
                camPosX = 128;
            }
            currEnvID = door.destID;
            player.xPos = door.destX;
            player.yPos = door.destY;
            player.angleRadians = 0;
            background = envs.at(currEnvID).frame;
            player.sideMode = envs.at(currEnvID).side;
            return;
        }
    }
}

void UpdateSideViewCamera() {
    if (player.xPos < 128) {
        camPosX = 128;
    }
    else if (player.xPos > 1920) {
        camPosX = 1920;
    }
    else {
        camPosX = player.xPos;
    }
}

void UpdateSaveStationLogic(double deltaTime) {
    if (player.alreadyOnStation) {
        if (!player.CheckCollision(saveStations[player.stationTouchingID])) {
            player.alreadyOnStation = false;
        }
    }
    for (auto& s : saveStations) {
        if (!player.alreadyOnStation && player.CheckCollision(s)) {
            player.alreadyOnStation = true;
            player.inDockingSequence = true;
            player.approaching = true;
            player.stationTouchingID = s.id;
            return;
        }
        if (!s.closed) {
            s.PlayCloseAnimation(deltaTime);
        }
    }

}


//--------------------
// Rendering Functions
//--------------------

void RenderTextLeft(std::string text, unsigned __int8 x, unsigned __int8 y) {
    __int8 spacerX(0), spacerY(0);
    for (char c : text) {
        unsigned __int8 i = unsigned __int8(c);

        if (c == ' ') {
            spacerX += 2;
            continue;
        }
        ID2D1Bitmap* symbol = bitmaps[fontArray[i]];
        D2D1_SIZE_F size = symbol->GetSize();

        if (c == 'p' || c == 'g' || c == 'q' || c == 'y') {
            spacerY = 3;
        }
        else if (c == 'j') {
            spacerY = 1;
            spacerX -= 2;
        }
        else {
            spacerY = max(0, 9 - size.height);
        }
        D2D1_RECT_F destRect = D2D1::RectF(
            ((x + spacerX) * scalerX) + leftBoundary,
            (y + spacerY) * scalerY,
            ((x + size.width + spacerX) * scalerX) + leftBoundary,
            (y + size.height + spacerY) * scalerY);
        renderTarget->DrawBitmap(symbol, destRect, 1.0F, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR);

        spacerX += (size.width);
    }
    return;
}

int RenderTextMid(std::string text, unsigned __int8 x, unsigned __int8 y) {
    __int8 spacerX(0), spacerY(0);
    for (char c : text) {
        unsigned __int8 i = unsigned __int8(c);
        if (c == ' ') {
            spacerX += 2;
            continue;
        }
        ID2D1Bitmap* symbol = bitmaps[fontArray[i]];
        D2D1_SIZE_F size = symbol->GetSize();
        spacerX += (size.width);
    }

    float xPos = x - (spacerX / 2);
    for (char c : text) {
        unsigned __int8 i = unsigned __int8(c);
        if (c == ' ') {
            xPos += 2;
            continue;
        }
        ID2D1Bitmap* symbol = bitmaps[fontArray[i]];
        D2D1_SIZE_F size = symbol->GetSize();

        if (c == 'p' || c == 'g' || c == 'q' || c == 'y') {
            spacerY = 3;
        }
        else if (c == 'j') {
            spacerY = 1;
        }
        else {
            spacerY = 9 - size.height;
        }
        D2D1_RECT_F destRect = D2D1::RectF(
            ((xPos)*scalerX) + leftBoundary,
            (y + spacerY) * scalerY,
            ((size.width + xPos) * scalerX) + leftBoundary,
            (y + size.height + spacerY) * scalerY);
        renderTarget->DrawBitmap(symbol, destRect, 1.0F, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR);

        xPos += (size.width);
    }
    return spacerX;
}

void RenderObjectLeft(LPCWSTR file, double x, double y) {
    ID2D1Bitmap* bmp = bitmaps[file];
    if (bmp) {
        D2D1_SIZE_F size = bmp->GetSize();

        D2D1_RECT_F position = D2D1::RectF(
            (x * scalerX) + leftBoundary,
            (y * scalerX),
            ((x + size.width) * scalerX) + leftBoundary,
            ((y + size.height) * scalerY)
        );
        renderTarget->DrawBitmap(bmp, position, 1.0F, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR);
    }
}

void RenderObjectRight(LPCWSTR file, double x, double y) {
    ID2D1Bitmap* bmp = bitmaps[file];
    if (bmp) {
        D2D1_SIZE_F size = bmp->GetSize();

        D2D1_RECT_F position = D2D1::RectF(
            ((x - size.width) * scalerX) + leftBoundary,
            (y * scalerX),
            (x * scalerX) + leftBoundary,
            ((y + size.height) * scalerY)
        );
        renderTarget->DrawBitmap(bmp, position, 1.0F, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR);
    }
}

void RenderWorldObject(LPCWSTR file, double x, double y) {
    ID2D1Bitmap* bmp = bitmaps[file];
    if (bmp) {
        D2D1_SIZE_F size = bmp->GetSize();

        D2D1_RECT_F position = D2D1::RectF(
            ((screenX / 2) + ((x - player.xPos) * scalerX)) - ((size.width / 2) * scalerX),
            ((screenY / 2) + ((y - player.yPos) * scalerY)) - ((size.height / 2) * scalerY),
            ((screenX / 2) + ((x - player.xPos) * scalerX)) + ((size.width / 2) * scalerX),
            ((screenY / 2) + ((y - player.yPos) * scalerY)) + ((size.height / 2) * scalerY)
        );

        renderTarget->DrawBitmap(bmp, position, 1.0F, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR);
    }
}

void RenderObjectandTextMid(LPCWSTR file, std::string text, double x, double y) {
    __int8 spacerX(0), spacerY(0);
    ID2D1Bitmap* bmp = bitmaps[file];
    if (!bmp) TripErrorMissingFile(file);
    D2D1_SIZE_F osize = bmp->GetSize();
    spacerX += osize.width;
    for (char c : text) {
        unsigned __int8 i = unsigned __int8(c);
        if (c == ' ') {
            spacerX += 2;
            continue;
        }
        ID2D1Bitmap* symbol = bitmaps[fontArray[i]];
        D2D1_SIZE_F tsize = symbol->GetSize();
        spacerX += (tsize.width);
    }

    double xPos = double(x) - (spacerX / 2);

    D2D1_RECT_F position = { D2D1::RectF(
        (xPos * scalerX) + leftBoundary,
        (y + 2 + spacerY) * scalerY,
        (((osize.width + xPos) * scalerX) + leftBoundary),
        (y + 2 + osize.height + spacerY) * scalerY
    ) };
    renderTarget->DrawBitmap(bmp, position, 1.0F, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR);
    xPos += osize.width + 1;

    for (char c : text) {
        unsigned __int8 i = unsigned __int8(c);
        if (c == ' ') {
            xPos += 2;
            continue;
        }
        ID2D1Bitmap* symbol = bitmaps[fontArray[i]];
        D2D1_SIZE_F size = symbol->GetSize();

        if (c == 'p' || c == 'g' || c == 'q' || c == 'y') {
            spacerY = 3;
        }
        else if (c == 'j') {
            spacerY = 1;
        }
        else {
            spacerY = 9 - size.height;
        }
        D2D1_RECT_F destRect = D2D1::RectF(
            ((xPos)*scalerX) + leftBoundary,
            (y + spacerY) * scalerY,
            ((size.width + xPos) * scalerX) + leftBoundary,
            (y + size.height + spacerY) * scalerY);
        renderTarget->DrawBitmap(symbol, destRect, 1.0F, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR);

        xPos += (size.width);
    }
}



//--------------
// Game Menus
//--------------

class MenuElement : public Object {
public:
    MenuElement(LPCWSTR path, int x, int y) {
        currentFramePath = path;
        xPos = x;
        yPos = y;
    }
};

class Menu {
public:
    __int8 selection = 0;
    __int8 selecSize = 2;
    unsigned __int8 state = 0;
    std::vector<MenuElement> elements;
    bool holdU = false;
    bool holdD = false;

    void ChangeSelection(bool up, bool down) {
        if (up) {
            holdU = true;
            menuLastInput = std::chrono::steady_clock::now();
            selection = max(0, selection - 1);
        }
        else {
            holdU = false;
        }
        if (down) {
            holdD = true;
            menuLastInput = std::chrono::steady_clock::now();
            selection = min(selecSize - 1, selection + 1);
        }
        else {
            holdD = false;
        }
    }
};

class SaveMenu : public Menu {
public:
    std::vector<MenuElement> elements;


    SaveMenu() {
        elements.emplace_back(files.save_file_panel, 16, 17);
        elements.emplace_back(files.save_file_panel, 16, 87);
        elements.emplace_back(files.save_file_panel, 16, 157);
        selecSize = 3;
    }

    void UpdateLogic() {
        if (std::chrono::steady_clock::now() - menuLastInput <= menuInputBuffer) return;
        if (keys.space) {
            std::ifstream inFile((L"Save Files\\Save.txt"));
            if (inFile.is_open()) {

                std::string line;
                for (int i = 0; i <= 4; i++) {
                    std::getline(inFile, line);
                    switch (i) {
                        // Currency
                    case 1:
                        player.currency = stoi(line);
                        break;
                        // Time
                    case 2:
                        stopwatch.duration = stoi(line);
                        stopwatch.Start();
                        break;
                        // Save Station ID
                    case 3:
                        player.xPos = saveStations[stoi(line)].xPos;
                        player.yPos = saveStations[stoi(line)].yPos;
                        break;
                    }
                }

                gameState = 0;
                InitializeAssets();
                inFile.close();
                paused = false;
            }
        }
        if (keys.escape) {
            menuLastInput = std::chrono::steady_clock::now();
            state = 1;
            selecSize = 2;
            return;
        }
        ChangeSelection(keys.up, keys.down);
        if (keys.right && gameState == 2) {
            menuLastInput = std::chrono::steady_clock::now();
            gameState = 3;
        }
    }

    void Render() {
        ID2D1Bitmap* bmp;
        bmp = bitmaps[files.save_file_panel];
        D2D1_SIZE_F size = bmp->GetSize();
        if (!bmp) return;
        for (const auto& elem : elements) {
            D2D1_RECT_F position = D2D1::RectF(
                leftBoundary + (elem.xPos * scalerX),
                0 + (elem.yPos * scalerY),
                leftBoundary + ((elem.xPos + size.width) * scalerX),
                (elem.yPos + size.height) * scalerY
            );
            renderTarget->DrawBitmap(bmp, position, 1.0F, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR);
        }
        std::ifstream inFile((L"Save Files\\Save.txt"));
        if (inFile.is_open()) {
            std::string line;
            int yOffset = 0;

            std::string name;
            std::string curr;
            std::string time;

            // File Name
            if (std::getline(inFile, line)) {
                yOffset += 17 + ((std::stoi(line) - 1) * 70);
                name = "File " + line;
            }

            // Currency amount
            if (std::getline(inFile, line)) {
                curr = line;
            }

            // Time Played
            if (std::getline(inFile, line)) {
                time = line;
            }

            RenderTextLeft(name, 69, 23);
            RenderTextLeft(curr, 77, 45);
            RenderTextLeft(time, 69, 57);
            RenderObjectLeft(files.jewel_Red, 69, 47);

            if (std::chrono::steady_clock::now() - player.lastFrameChange >= player.frameInterval) {
                player.lastFrameChange = std::chrono::steady_clock::now();
                if (player.currentFramePath == files.playerFrame2) {
                    player.currentFramePath = files.playerFrame1;
                }
                else {
                    player.currentFramePath = files.playerFrame2;
                }
            }
            RenderObjectLeft(player.currentFramePath, 35, 36 + (selection * 69));

            inFile.close();
        }
    }
};

SaveMenu saveMenu;

class TitleMenu : public Menu {
public:
    bool startPressed = false;
    std::chrono::milliseconds heldInputBuffer = std::chrono::milliseconds(150);

    TitleMenu() {}

    void UpdateLogic() {
        // Start Screen
        if (state == 0) {
            if (std::chrono::steady_clock::now() - menuLastInput <= menuInputBuffer) return;
            if (keys.space) {
                menuLastInput = std::chrono::steady_clock::now();
                state = 1;
            }
            return;
        }

        // New Game/Load Screen
        if (state == 1) {
            if (std::chrono::steady_clock::now() - menuLastInput <= menuInputBuffer) return;
            ChangeSelection(keys.up, keys.down);
            if (keys.escape) {
                menuLastInput = std::chrono::steady_clock::now();
                state = 0;
                return;
            }
            if (!keys.space) return;
            menuLastInput = std::chrono::steady_clock::now();
            switch (selection) {
                // New Game
            case 0:
                player.xPos = saveStations[0].xPos;
                player.yPos = saveStations[0].yPos;
                InitializeAssets();
                gameState = 0;
                paused = false;
                break;

                // Load
            case 1:
                elements.emplace_back(files.save_file_panel, 16, 17);
                elements.emplace_back(files.save_file_panel, 16, 87);
                elements.emplace_back(files.save_file_panel, 16, 157);
                selection = 0;
                selecSize = 3;
                state = 2;
                break;
            }
            return;
        }

        // Save/Load Menu
        if (state == 2) {
            saveMenu.UpdateLogic();
        }
        return;
    }

    void Render() {
        ID2D1Bitmap* bmp;
        int x, y;
        switch (state) {
        case 0: // title screen
            bmp = bitmaps[files.title_screen];

            if (bmp) {
                D2D1_RECT_F position = D2D1::RectF(
                    leftBoundary,
                    0,
                    leftBoundary + (256 * scalerX),
                    224 * scalerY
                );

                renderTarget->DrawBitmap(bmp, position, 1.0F, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR);
            }
            RenderTextMid("Press Space", 128, 190);
            RenderTextMid("NEODYUM", 128, 40);
            break;

        case 1: // new game, load game select
            bmp = bitmaps[files.title_screen];
            y = 192 + (selection * 12);

            if (bmp) {
                D2D1_RECT_F position = D2D1::RectF(
                    leftBoundary,
                    0,
                    leftBoundary + (256 * scalerX),
                    224 * scalerY
                );

                renderTarget->DrawBitmap(bmp, position, 1.0F, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR);
            }
            if (selection == 0) {
                x = RenderTextMid("New Game", 127, 190);
                RenderTextMid("Load Game", 127, 202);
            }
            else {
                RenderTextMid("New Game", 127, 190);
                x = RenderTextMid("Load Game", 127, 202);
            }
            x = 117 - (x / 2);
            RenderObjectLeft(files.selec_arrow, x, y);

            break;

        case 2: // load game screen
            saveMenu.Render();
            break;
        }
        return;
    }
};

class RepairStation : public Menu {
public:
    unsigned __int8 xSelec = 7, ySelec = 26;
    std::chrono::milliseconds selecAnimationInterval = std::chrono::milliseconds(150);
    std::chrono::steady_clock::time_point lastSelectButtonInterval = std::chrono::steady_clock::now();
    LPCWSTR selecFrames[5];
    __int8 currFrame = 0;
    bool animForward = true;
    bool componentSelected = false;
    __int8 panelSelected = 0;
    __int8 displayLength[4];
    bool componentModified = false;
    std::chrono::steady_clock::time_point lastButtonChange = std::chrono::steady_clock::now();
    std::chrono::milliseconds buttonInterval = std::chrono::milliseconds(500);
    LPCWSTR currentButtonFile = files.upgrade_button;
    int cost = 0;


    RepairStation() {
        selecSize = 4;
        selecFrames[0] = files.repair_Selection_1;
        selecFrames[1] = files.repair_Selection_2;
        selecFrames[2] = files.repair_Selection_3;
        selecFrames[3] = files.repair_Selection_4;
        selecFrames[4] = files.repair_Selection_5;
        currFrame = 0;
        for (int i = 0; i <= 3; i++) {
            displayLength[i] = player.tweakBarLength[i];
        }
    }

    void ChangeCost(int i, bool increase) {
        if (increase) {
            switch (i) {
            case 1:
                cost += 80;
                break;
            case 2:
                cost += 200;
                break;
            case 3:
                cost += 450;
                break;
            case 4:
                cost += 1000;
                break;
            case 5:
                cost += 1600;
                break;
            }
        }
        else {
            switch (i) {
            case 0:
                cost -= 80;
                break;
            case 1:
                cost -= 200;
                break;
            case 2:
                cost -= 450;
                break;
            case 3:
                cost -= 1000;
                break;
            case 4:
                cost -= 1600;
                break;
            }
        }
    }

    void ProcessKeyInputs() {
        if (std::chrono::steady_clock::now() - menuLastInput <= menuInputBuffer) return;
        if ((keys.escape && !componentSelected) || (keys.left && selection == 0 && !componentSelected)) {
            menuLastInput = std::chrono::steady_clock::now();
            gameState = 2;
            return;
        }
        else if (keys.escape && componentSelected) {
            menuLastInput = std::chrono::steady_clock::now();
            componentSelected = false;
            for (int i = 0; i <= 3; i++) {
                displayLength[i] = player.tweakBarLength[i];
            }
            cost = 0;
            componentModified = false;
            return;
        }
        if (keys.space) {
            menuLastInput = std::chrono::steady_clock::now();
            componentSelected = true;
            switch (selection) {
            case 0:
                panelSelected = 0;
                break;
            case 1:
                panelSelected = 2;
                break;
            case 2:
                panelSelected = 2;
                break;
            case 3:
                panelSelected = 3;
                break;
            }
            return;
        }
        if (!componentSelected) {
            if (keys.right) {
                menuLastInput = std::chrono::steady_clock::now();
                if (selection == 0) { // Plating
                    selection = 1;
                }
            }
            else if (keys.left) {
                menuLastInput = std::chrono::steady_clock::now();
                if (selection == 1) { // Ionizer
                    selection = 0;
                }
                else if (selection == 2) { // E. Coil
                    selection = 0;
                }
                else if (selection == 3) { // Injectors
                    selection = 0;
                }
            }
            else if (keys.up) {
                menuLastInput = std::chrono::steady_clock::now();
                if (selection == 3) { // Injectors
                    selection = 2;
                }
                else if (selection == 2) { // E. Coil
                    selection = 1;
                }
                else if (selection == 1) {
                    selection = 0;
                }
            }
            else if (keys.down) {
                menuLastInput = std::chrono::steady_clock::now();
                if (selection == 0) {
                    selection = 1;
                }
                else if (selection == 1) {
                    selection = 2;
                }
                else if (selection == 2) {
                    selection = 3;
                }
            }
        }
        else {
            if (keys.right) {
                menuLastInput = std::chrono::steady_clock::now();
                int delta = displayLength[selection];
                displayLength[selection] = min(5, displayLength[selection] + 1);
                delta = delta - displayLength[selection];
                if (delta != 0) ChangeCost(displayLength[selection], true);
                componentModified = true;
            }
            else if (keys.left) {
                menuLastInput = std::chrono::steady_clock::now();
                int delta = displayLength[selection];
                displayLength[selection] = max(player.tweakBarLength[selection], displayLength[selection] - 1);
                delta = delta - displayLength[selection];
                if (delta != 0) ChangeCost(displayLength[selection], false);
                if (displayLength[selection] == player.tweakBarLength[selection]) {
                    componentModified = false;
                }
            }

        }

        switch (selection) {
        case 0:
            xSelec = 7;
            ySelec = 25;
            break;
        case 1:
            xSelec = 180;
            ySelec = 25;
            break;
        case 2:
            xSelec = 180;
            ySelec = 37;
            break;
        case 3:
            xSelec = 180;
            ySelec = 115;
            break;
        }
    }

    void CycleSelectionAnimation() {
        if (std::chrono::steady_clock::now() - lastSelectButtonInterval < selecAnimationInterval) return;
        lastSelectButtonInterval = std::chrono::steady_clock::now();
        int sign;
        animForward ? sign = 1 : sign = -1;
        currFrame += sign;
        if (currFrame > 4) {
            currFrame = 4;
            animForward = false;
        }
        else if (currFrame < 0) {
            currFrame = 0;
            animForward = true;
        }
    }

    void UpdateLogic() {
        ProcessKeyInputs();
        CycleSelectionAnimation();
    }

    void RenderComponentFilling(LPCWSTR file, __int8 qty, double x, double y) {
        if (qty == 0) return;
        __int8 spacerX = 1;
        for (__int8 i = 0; i < qty; i++) {
            RenderObjectLeft(file, x + spacerX, y);
            spacerX += 3;
        }
    }

    void Render() {
        RenderObjectLeft(files.repair_station_menu, 0, 0);
        if (componentModified) {
            if (std::chrono::steady_clock::now() - lastButtonChange >= buttonInterval) {
                lastButtonChange = std::chrono::steady_clock::now();
                if (currentButtonFile == files.upgrade_button) {
                    currentButtonFile = files.upgrade_button_pressed;
                }
                else {
                    currentButtonFile = files.upgrade_button;
                }
            }
        }
        if (!componentSelected) {
            RenderObjectLeft(selecFrames[currFrame], xSelec, ySelec);
            RenderTextLeft("Plating", 9, 27);
            RenderTextLeft("Ionizers", 182, 27);
            RenderTextLeft("E. Coil", 182, 39);
            RenderTextLeft("Injectors", 182, 117);
            RenderObjectRight(files.repair_station_bar_shell, 76, 26);
            RenderComponentFilling(files.repair_station_hull_filling, player.tweakBarLength[0], 59, 26.995);
            RenderObjectRight(files.repair_station_bar_shell, 248, 26);
            RenderComponentFilling(files.repair_station_blasters_filling, player.tweakBarLength[1], 231, 26.995);
            RenderObjectRight(files.repair_station_bar_shell, 248, 38);
            RenderComponentFilling(files.repair_station_blasters_filling, player.tweakBarLength[2], 231, 39);
            RenderObjectRight(files.repair_station_bar_shell, 248, 116);
            RenderComponentFilling(files.repair_station_thruster_filling, player.tweakBarLength[3], 231, 117.005);

        }
        else {
            int yOffset;
            switch (panelSelected) {
            case 0:
                RenderObjectLeft(selecFrames[currFrame], xSelec, 25);
                RenderObjectRight(files.repair_station_bar_shell, 76, 26);
                RenderComponentFilling(files.repair_station_hull_filling, displayLength[0], 59, 26.995);
                RenderObjectRight(files.repair_station_bar_shell, 248, 26);
                RenderComponentFilling(files.repair_station_blasters_filling, displayLength[1], 231, 26.995);
                RenderObjectRight(files.repair_station_bar_shell, 248, 38);
                RenderComponentFilling(files.repair_station_blasters_filling, displayLength[2], 231, 39);
                RenderObjectRight(files.repair_station_bar_shell, 248, 116);
                RenderComponentFilling(files.repair_station_thruster_filling, displayLength[3], 231, 117.005);
                RenderTextLeft("Plating", 9, 27);
                RenderObjectLeft(files.repair_station_info_box, 8, 40);
                RenderTextLeft("Ionizers", 182, 27);
                RenderTextLeft("E. Coil", 182, 39);
                RenderTextLeft("Injectors", 182, 117);

                RenderTextLeft("Reinforces the", 9, 42);
                RenderTextLeft("ship's hull, ", 9, 53);
                RenderTextLeft("reducing DMG.", 9, 64);
                if (componentModified) {
                    RenderObjectLeft(currentButtonFile, 22, 76);
                    (currentButtonFile == files.upgrade_button_pressed) ? yOffset = 2 : yOffset = 0;
                    RenderObjectandTextMid(files.jewel_Red, std::to_string(cost), 43, 78 + yOffset);
                }
                break;
            case 1:
                RenderObjectLeft(files.repair_station_info_box, 8, 40);
                if (componentModified) {
                    RenderObjectLeft(currentButtonFile, 195, 76);
                    (currentButtonFile == files.upgrade_button_pressed) ? yOffset = 2 : yOffset = 0;
                    RenderObjectandTextMid(files.jewel_Red, std::to_string(cost), 216, 78 + yOffset);
                }
                break;
            case 2:
                RenderObjectLeft(selecFrames[currFrame], xSelec, 25);
                RenderObjectRight(files.repair_station_bar_shell, 76, 26);
                RenderComponentFilling(files.repair_station_hull_filling, displayLength[0], 59, 26.995);
                RenderObjectRight(files.repair_station_bar_shell, 248, 26);
                RenderObjectRight(files.repair_station_bar_shell, 248, 116);
                RenderComponentFilling(files.repair_station_thruster_filling, displayLength[3], 231, 117.005);
                if (selection == 1) {
                    RenderTextLeft("Ionizers", 182, 27);
                    RenderComponentFilling(files.repair_station_blasters_filling, displayLength[1], 231, 26.995);
                }
                else {
                    RenderTextLeft("E. Coil", 182, 27);
                    RenderComponentFilling(files.repair_station_blasters_filling, displayLength[2], 231, 26.995);
                }
                RenderObjectLeft(files.repair_station_info_box, 181, 40);
                RenderTextLeft("Plating", 9, 27);
                RenderTextLeft("Injectors", 182, 117);
                if (componentModified) {
                    RenderObjectLeft(currentButtonFile, 195, 75);
                    (currentButtonFile == files.upgrade_button_pressed) ? yOffset = 2 : yOffset = 0;
                    RenderObjectandTextMid(files.jewel_Red, std::to_string(cost), 216, 77 + yOffset);
                }
                break;
            case 3:
                RenderObjectLeft(selecFrames[currFrame], xSelec, 115);
                RenderObjectRight(files.repair_station_bar_shell, 76, 26);
                RenderComponentFilling(files.repair_station_hull_filling, displayLength[0], 59, 26.995);
                RenderObjectRight(files.repair_station_bar_shell, 248, 26);
                RenderComponentFilling(files.repair_station_blasters_filling, displayLength[1], 231, 26.995);
                RenderObjectRight(files.repair_station_bar_shell, 248, 38);
                RenderComponentFilling(files.repair_station_blasters_filling, displayLength[2], 231, 39);
                RenderObjectRight(files.repair_station_bar_shell, 248, 116);
                RenderComponentFilling(files.repair_station_thruster_filling, displayLength[3], 231, 117.005);
                RenderTextLeft("Injectors", 182, 117);
                RenderObjectLeft(files.repair_station_info_box, 181, 130);
                RenderTextLeft("Plating", 9, 27);
                RenderTextLeft("Ionizers", 182, 27);
                RenderTextLeft("E. Coil", 182, 39);
                if (componentModified) {
                    RenderObjectLeft(currentButtonFile, 195, 187);
                    (currentButtonFile == files.upgrade_button_pressed) ? yOffset = 2 : yOffset = 0;
                    RenderObjectandTextMid(files.jewel_Red, std::to_string(cost), 216, 189 + yOffset);
                }
                break;
            }
        }
    }
};

TitleMenu titleMenu;
RepairStation repairStation;



//---------------------
// Game Loop Functions 
//---------------------

void Render() {

    renderTarget->BeginDraw();

    renderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));

    if (gameState == 1) titleMenu.Render();
    else if (gameState == 2) saveMenu.Render();
    else if (gameState == 3) repairStation.Render();
    else if (!paused && !splashscreen) {
        // Keeps stuff from being rendered outside boundaries
        D2D1_RECT_F aspectEnforcer = D2D1::RectF(leftBoundary, 0, rightBoundary, screenY);

        // Push the clipping rectangle onto the render target
        renderTarget->PushAxisAlignedClip(aspectEnforcer, D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);

        float bgWidth(0), bgHeight(0);
        if (background.currentFramePath == files.base_Interior) {
            // Pulls bitmap for background
            ID2D1Bitmap* backgroundBitmap = bitmaps[background.currentFramePath];
            D2D1_SIZE_F size = backgroundBitmap->GetSize();
            bgWidth = size.width;
            bgHeight = size.height;

            float left = max(0.0, max(camPosX - 128, 0.0));
            float right = min(max(0.0, camPosX + 128), double(size.width));
            if (left == 0) {
                right = 256;
            }
            if (right - left < 256) {
                left = right - 256;
            }

            // Camera position
            D2D1_RECT_F cameraPos = D2D1::RectF(left, 0, right, 224);

            if (backgroundBitmap) {
                D2D1_RECT_F screen = D2D1::RectF(leftBoundary, 0, rightBoundary, screenY);
                // Render a slice of the background equal to the camera coords, with no interpolation or transparency, to the defined display bounds
                renderTarget->DrawBitmap(backgroundBitmap, screen, 1.0F, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, cameraPos);
            }
        }
        else {
            ID2D1SolidColorBrush* brush;
            renderTarget->CreateSolidColorBrush(D2D1::ColorF(0, 0, 0), &brush);
            int rightBound = (int(player.xPos + 128) / 256) + 1;
            int lowBound = (int(player.yPos + 112) / 224) + 1;

            int leftBound = (int(player.xPos) - 128) / 256;
            int upBound = (int(player.yPos) - 112) / 224;

            for (int y = upBound; y <= lowBound; ++y) {
                for (int x = leftBound; x <= rightBound; ++x) {
                    auto it = starGrid.find({ x, y });
                    if (it != starGrid.end()) {
                        for (const Star& star : it->second) {
                            D2D1_RECT_F pixel = D2D1::RectF(
                                (star.xPos - player.xPos) * scalerX,
                                (star.yPos - player.yPos) * scalerY,
                                ((star.xPos - player.xPos) * scalerX) + scalerX,
                                ((star.yPos - player.yPos) * scalerY) + scalerY);

                            float red = float(star.r) / 255.0;
                            float green = float(star.g) / 255.0;
                            float blue = float(star.b) / 255.0;
                            /*renderTarget->CreateSolidColorBrush(D2D1::ColorF(
                                float(star.r) / 255.0,
                                float(star.g) / 255.0,
                                float(star.b) / 255.0,
                                star.a));*/
                            brush->SetColor(D2D1::ColorF(
                                float(star.r) / 255.0,
                                float(star.g) / 255.0,
                                float(star.b) / 255.0,
                                star.a));
                            renderTarget->FillRectangle(pixel, brush);
                        }
                    }
                }
            }
            brush->Release();
            for (int y = upBound; y <= lowBound; ++y) {
                for (int x = leftBound; x <= rightBound; ++x) {
                    auto it2 = asteroids.find({ x, y });
                    if (it2 != asteroids.end()) {
                        for (const Asteroid& asteroid : it2->second) {
                            ID2D1Bitmap* asteroidBmp = bitmaps[asteroid.currentFramePath];
                            D2D1_SIZE_F size = asteroidBmp->GetSize();
                            D2D1_RECT_F position = D2D1::RectF(
                                ((screenX / 2) + ((asteroid.xPos - player.xPos) * scalerX)) - ((size.width / 2) * scalerX),
                                ((screenY / 2) + ((asteroid.yPos - player.yPos) * scalerY)) - ((size.height / 2) * scalerY),
                                ((screenX / 2) + ((asteroid.xPos - player.xPos) * scalerX)) + ((size.width / 2) * scalerX),
                                ((screenY / 2) + ((asteroid.yPos - player.yPos) * scalerY)) + ((size.height / 2) * scalerY)
                            );

                            renderTarget->DrawBitmap(asteroidBmp, position, 1.0F, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR);
                        }
                    }
                }
            }
        }

        int length = sizeof(saveStations) / sizeof(saveStations[0]);
        for (int i = 0; i < length; i++) {
            RenderWorldObject(saveStations[i].currentFramePath, saveStations[i].xPos, saveStations[i].yPos);
        }

        ID2D1Bitmap* bPickup = bitmaps[pickup.currentFramePath];
        if (bPickup) {
            D2D1_SIZE_F size = bPickup->GetSize();

            D2D1_RECT_F position = D2D1::RectF(
                ((screenX / 2) + ((pickup.xPos - player.xPos) * scalerX)) - ((size.width / 2) * scalerX),
                ((screenY / 2) + ((pickup.yPos - player.yPos) * scalerY)) - ((size.height / 2) * scalerY),
                ((screenX / 2) + ((pickup.xPos - player.xPos) * scalerX)) + ((size.width / 2) * scalerX),
                ((screenY / 2) + ((pickup.yPos - player.yPos) * scalerY)) + ((size.height / 2) * scalerY)
            );

            renderTarget->DrawBitmap(bPickup, position, 1.0F, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR);
        }

        for (int i = 0; i < bases.size(); i++) {
            ID2D1Bitmap* baseBitmap = bitmaps[files.base];

            if (baseBitmap) {
                D2D1_SIZE_F size = baseBitmap->GetSize();

                D2D1_RECT_F position = D2D1::RectF(
                    ((screenX / 2) + ((bases.at(i).xPos - player.xPos) * scalerX)) - ((size.width / 2) * scalerX),
                    ((screenY / 2) + ((bases.at(i).yPos - player.yPos) * scalerY)) - ((size.height / 2) * scalerY),
                    ((screenX / 2) + ((bases.at(i).xPos - player.xPos) * scalerX)) + ((size.width / 2) * scalerX),
                    ((screenY / 2) + ((bases.at(i).yPos - player.yPos) * scalerY)) + ((size.height / 2) * scalerY)
                );

                renderTarget->DrawBitmap(baseBitmap, position, 1.0F, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR);
            }
        }

        if (!objects.empty()) {
            for (const auto& object : objects) {
                if (object.visible) {
                    ID2D1Bitmap* bitmap = bitmaps[object.currentFramePath];
                    if (bitmap) {
                        D2D1_SIZE_F size = bitmap->GetSize();
                        D2D1_RECT_F position = D2D1::RectF(
                            ((screenX / 2) + ((object.xPos - player.xPos) * scalerX)) - ((size.width / 2) * scalerX),
                            ((screenY / 2) + ((object.yPos - player.yPos) * scalerY)) - ((size.height / 2) * scalerY),
                            ((screenX / 2) + ((object.xPos - player.xPos) * scalerX)) + ((size.width / 2) * scalerX),
                            ((screenY / 2) + ((object.yPos - player.yPos) * scalerY)) + ((size.height / 2) * scalerY)
                        );

                        if (object.rotatable) {
                            double xOffset(0), yOffset(0);
                            if (object.name == L"Turret") {
                                yOffset = 1;
                            }

                            double angleDegrees = (object.angleRadians + pi / 2) * (180.0 / pi);
                            D2D1_POINT_2F center = D2D1::Point2F(((position.right + position.left) / 2) + (xOffset * scalerX), ((position.top + position.bottom) / 2) + (yOffset * scalerY));

                            // Rotates sprite. Makes art less consistent but saves time
                            D2D1_MATRIX_3X2_F rotation = D2D1::Matrix3x2F::Rotation(angleDegrees, center);

                            // Rotates bitmap based on rotation calculations
                            renderTarget->SetTransform(rotation);

                            renderTarget->DrawBitmap(bitmap, position, 1.0F, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR);

                            // Resets the rotation transformation on renderTarget
                            renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

                        }
                        if (object.canFire) {
                            if (object.shotFrame) {
                                ID2D1Bitmap* shotEffectBitmap = bitmaps[object.shotFrame];
                                D2D1_SIZE_F size = shotEffectBitmap->GetSize();

                                D2D1_RECT_F displayPos = D2D1::RectF(
                                    (screenX / 2) + (((object.xPos - player.xPos) * scalerX) - ((size.width / 2) * scalerX)),
                                    (screenY / 2) + (((object.yPos - player.yPos) * scalerY) - (((size.height / 2) + 8) * scalerY)),
                                    (screenX / 2) + (((object.xPos - player.xPos) * scalerX) + ((size.width / 2) * scalerX)),
                                    (screenY / 2) + (((object.yPos - player.yPos) * scalerY) + (((size.height / 2) - 8) * scalerY))
                                );

                                double angleDegrees = (object.angleRadians + pi / 2) * (180.0 / pi);
                                D2D1_POINT_2F center = D2D1::Point2F((position.right + position.left) / 2, (position.top + position.bottom) / 2);

                                // Rotates sprite. Makes art less consistent but saves time
                                D2D1_MATRIX_3X2_F rotation = D2D1::Matrix3x2F::Rotation(angleDegrees, center);

                                // Rotates bitmap based on rotation calculations
                                renderTarget->SetTransform(rotation);

                                renderTarget->DrawBitmap(shotEffectBitmap, displayPos, 1.0F, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR);

                                // Resets the rotation transformation on renderTarget
                                renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
                            }
                        }
                        else {
                            renderTarget->DrawBitmap(bitmap, position, 1.0F, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR);
                        }
                    }
                }
            }
        }
        float xOffset(0), yOffset(0);
        if (!player.dead) {
            // Pulls bitmap for player ship
            ID2D1Bitmap* playerBitmap = bitmaps[player.currentFramePath];


            if (playerBitmap) {
                D2D1_SIZE_F size = playerBitmap->GetSize();
                // Correct ship size basd on scale and screen position
                D2D1_RECT_F shipDisplayPosition;
                if (background.currentFramePath == files.base_Interior) {
                    if (player.xPos < 128) {
                        xOffset = player.xPos - 128;
                    }
                    else if (player.xPos > (bgWidth - 128)) {
                        xOffset = player.xPos - (bgWidth - 128);
                    }

                    if (player.yPos < 112) {
                        yOffset = player.yPos - 112;
                    }
                    else if (player.yPos > (bgHeight - 112)) {
                        yOffset = player.yPos - (bgHeight - 112);
                    }
                    //xOffset *= cos(player.angleRadians);
                    //yOffset *= sin(player.angleRadians);
                    // Correct ship size basd on scale and screen position
                    /*shipDisplayPosition = D2D1::RectF(
                        leftBoundary + ((player.xPos - (size.width / 2)) * scalerX),
                        (player.yPos) - ((size.height / 2) * scalerY),
                        leftBoundary + ((player.xPos + (size.width / 2)) * scalerX),
                        (player.yPos) + ((size.height / 2) * scalerY)
                    );*/
                }
                // Ship and and effects will need to have uniform rotation, so setting that upfront...
                // Finds direction angle based on inputs
                double angleDegrees;
                if (player.inModifiedDockingAngle) {
                    angleDegrees = ((player.angleRadians + pi / 4) / pi) * 360;
                }
                else {
                    angleDegrees = ((player.angleRadians + pi / 4) / pi) * 360;
                }
                D2D1_POINT_2F center = D2D1::Point2F(screenX / 2, screenY / 2);


                // Rotates bitmap based on rotation calculations, translates position with respect to scrollable areas
                D2D1::Matrix3x2F rotation = D2D1::Matrix3x2F::Rotation(angleDegrees, D2D1::Point2F(screenX / 2, screenY / 2));
                D2D1::Matrix3x2F translation = D2D1::Matrix3x2F::Translation(xOffset * scalerX, yOffset * scalerY);
                D2D1::Matrix3x2F fullTransform = rotation * translation;
                renderTarget->SetTransform(fullTransform);
                shipDisplayPosition = D2D1::RectF(
                    (screenX / 2) - (((size.width / 2)) * scalerX),
                    (screenY / 2) - (((size.height / 2)) * scalerY),
                    (screenX / 2) + (((size.width / 2)) * scalerX),
                    (screenY / 2) + (((size.height / 2)) * scalerY)
                );

                // Render bitmap at display position with no transparency or interpolation
                renderTarget->DrawBitmap(playerBitmap, shipDisplayPosition, 1.0F, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR);
            }

            ID2D1Bitmap* redLightBitmap = bitmaps[player.redLightFrame];

            if (redLightBitmap && !(player.inDockingSequence && !saveStations[player.stationTouchingID].closed) && !player.inAscendingSequence) {
                D2D1_SIZE_F size = redLightBitmap->GetSize();
                int xOff1(0), xOff2(0), yOff1(0), yOff2(0);
                if (player.currentFramePath == files.player_tilt_left || player.currentFramePath == files.player_tilt_right) {
                    xOff1 = -1;
                    xOff2 = 1;
                }
                else if (player.currentFramePath == files.player_sideways_l || player.currentFramePath == files.player_sideways_r) {
                    bool inverse;
                    if (player.sideMode) {
                        xOff1 = -2, xOff2 = 99999999;
                    }
                    else if (player.directionX == 0) {
                        inverse = (player.directionY > 0) ? false : true;
                        keys.right = inverse ? !keys.right : keys.right;
                        keys.right ? (xOff1 = 999999, xOff2 = 2) : (xOff1 = -2, xOff2 = 999999);
                        keys.right = inverse ? !keys.right : keys.right;
                    }
                    else {
                        inverse = (player.directionX > 0) ? false : true;
                        inverse ? keys.up = !keys.up : keys.up;
                        keys.up ? (xOff1 = -2, xOff2 = 9999999) : (xOff1 = 999999, xOff2 = 2);
                        inverse ? keys.up = !keys.up : keys.up;
                    }
                }
                else if (player.sideMode && player.currentFramePath == files.player_upside_tilted_l) {
                    xOff1 = -1, xOff2 = 1;
                }
                D2D1_RECT_F displayPos1 = D2D1::RectF(
                    (screenX / 2) - (((size.width / 2) - 4 - xOff1) * scalerX),
                    (screenY / 2) - (((size.height / 2) + 2) * scalerY),
                    (screenX / 2) + (((size.width / 2) + 4 + xOff1) * scalerX),
                    (screenY / 2) + (((size.height / 2) - 2) * scalerY)
                );

                D2D1_RECT_F displayPos2 = D2D1::RectF(
                    (screenX / 2) - (((size.width / 2) + 4 - xOff2) * scalerX),
                    (screenY / 2) - (((size.height / 2) + 2) * scalerY),
                    (screenX / 2) + (((size.width / 2) - 4 + xOff2) * scalerX),
                    (screenY / 2) + (((size.height / 2) - 2) * scalerY)
                );

                renderTarget->DrawBitmap(redLightBitmap, displayPos1, 1.0F, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR);

                renderTarget->DrawBitmap(redLightBitmap, displayPos2, 1.0F, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR);
            }
        }
        else {
            if (player.currentFramePath == files.player_Death_Animation_1 && (std::chrono::steady_clock::now() - player.lastDeathFrameUpdate) >= std::chrono::nanoseconds(16666666)) {
                player.currentFramePath = files.player_Death_Animation_2;
                player.lastDeathFrameUpdate = std::chrono::steady_clock::now();
            }
            else if (player.currentFramePath == files.player_Death_Animation_2 && (std::chrono::steady_clock::now() - player.lastDeathFrameUpdate) >= std::chrono::nanoseconds(16666666)) {
                player.currentFramePath = files.player_Death_Animation_3;
                player.lastDeathFrameUpdate = std::chrono::steady_clock::now();
            }

            ID2D1Bitmap* deathBitmap = bitmaps[player.currentFramePath];
            if (deathBitmap) {
                D2D1_SIZE_F size = deathBitmap->GetSize();

                // Correct ship size basd on scale and screen position
                D2D1_RECT_F shipDisplayPosition = D2D1::RectF(
                    (screenX / 2) - ((size.width / 2) * scalerX),
                    (screenY / 2) - ((size.height / 2) * scalerY),
                    (screenX / 2) + ((size.width / 2) * scalerX),
                    (screenY / 2) + ((size.height / 2) * scalerY)
                );

                // Render bitmap at display position with no transparency or interpolation
                renderTarget->DrawBitmap(deathBitmap, shipDisplayPosition, 1.0F, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR);
            }
        }


        ID2D1Bitmap* basicShotEffectBitmap = bitmaps[player.basicShotFrame];

        if (basicShotEffectBitmap) {
            D2D1_SIZE_F size = basicShotEffectBitmap->GetSize();
            D2D1_RECT_F displayPos;
            if (player.sideMode) {
                float xOffset(0), yOffset(0);
                if (player.xPos < 128) {
                    xOffset = sin(player.angleRadians) * (player.xPos - 128);
                }
                else if (player.xPos > (bgWidth - 128)) {
                    xOffset = sin(player.angleRadians) * (player.xPos - (bgWidth - 128));
                }

                if (player.yPos < 112) {
                    yOffset = sin(player.angleRadians) * (player.yPos - 112);
                }
                else if (player.yPos > (bgHeight - 112)) {
                    yOffset = sin(player.angleRadians) * (player.yPos - (bgHeight - 112));
                }
                displayPos = D2D1::RectF(
                    screenX / 2 - ((size.width / 2) * scalerX) + (xOffset * scalerX),
                    screenY / 2 - ((8 + size.height / 2 + yOffset) * scalerY),
                    screenX / 2 + ((size.width / 2 + xOffset) * scalerX),
                    screenY / 2 + ((size.height / 2 + yOffset - 8) * scalerY)
                );
            }
            else {
                displayPos = D2D1::RectF(
                    (screenX / 2) - ((size.width / 2) * scalerX),
                    (screenY / 2) - (((size.height / 2) + 8) * scalerY),
                    (screenX / 2) + ((size.width / 2) * scalerX),
                    (screenY / 2) + (((size.height / 2) - 8) * scalerY)
                );
            }

            renderTarget->DrawBitmap(basicShotEffectBitmap, displayPos, 1.0F, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR);
        }
        // Resets the rotation transformation on renderTarget
        renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());



        for (auto bullet : player.bullets) {

            ID2D1Bitmap* basicShotBitmap = bitmaps[bullet.currentFramePath];

            if (basicShotBitmap) {
                D2D1_SIZE_F size = basicShotBitmap->GetSize();

                D2D1_RECT_F position;
                if (player.sideMode) {
                    if (player.xPos < 128) {
                        xOffset = player.xPos - 128;
                    }
                    else if (player.xPos > (bgWidth - 128)) {
                        xOffset = player.xPos - (bgWidth - 128);
                    }

                    if (player.yPos < 112) {
                        yOffset = player.yPos - 112;
                    }
                    else if (player.yPos > (bgHeight - 112)) {
                        yOffset = player.yPos - (bgHeight - 112);
                    }
                    position = D2D1::RectF(
                        screenX / 2 + (xOffset + bullet.xPos - player.xPos - size.width / 2) * scalerX,
                        screenY / 2 + (yOffset + bullet.yPos - player.yPos - size.height / 2) * scalerY,
                        screenX / 2 + (xOffset + bullet.xPos - player.xPos + size.width / 2) * scalerX,
                        screenY / 2 + (yOffset + bullet.yPos - player.yPos + size.height / 2) * scalerY
                    );
                }
                else {
                    position = D2D1::RectF(
                        ((screenX / 2) + ((bullet.xPos - player.xPos) * scalerX)) - ((size.width / 2) * scalerX),
                        ((screenY / 2) + ((bullet.yPos - player.yPos) * scalerY)) - ((size.height / 2) * scalerY),
                        ((screenX / 2) + ((bullet.xPos - player.xPos) * scalerX)) + ((size.width / 2) * scalerX),
                        ((screenY / 2) + ((bullet.yPos - player.yPos) * scalerY)) + ((size.height / 2) * scalerY)
                    );
                }

                double angleDegrees = bullet.angleRadians * (180.0 / 3.14159265359);
                D2D1_POINT_2F center = D2D1::Point2F((position.right + position.left) / 2, (position.top + position.bottom) / 2);

                // Rotates sprite. Makes art less consistent but saves time
                D2D1_MATRIX_3X2_F rotation = D2D1::Matrix3x2F::Rotation(angleDegrees, center);

                // Rotates bitmap based on rotation calculations
                renderTarget->SetTransform(rotation);

                // 
                renderTarget->DrawBitmap(basicShotBitmap, position, 1.0F, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR);


                // Resets the rotation transformation on renderTarget
                renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

                //ID2D1Bitmap* hitBox = bitmaps[files.hitBox];

                //if (hitBox) {
                //    D2D1_RECT_F perimeter = D2D1::RectF(
                //        ((screenX / 2) + ((bullet.hitbox.left - player.xPos) * scalerX)),
                //        ((screenY / 2) + ((bullet.hitbox.up - player.yPos) * scalerY)),
                //        ((screenX / 2) + ((bullet.hitbox.right - player.xPos) * scalerX)),
                //        ((screenY / 2) + ((bullet.hitbox.down - player.yPos) * scalerY))
                //    );

                //    // Rotates bitmap based on rotation calculations
                //    renderTarget->SetTransform(rotation);

                //    // 
                //    renderTarget->DrawBitmap(hitBox, perimeter, 1.0F, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR);
                //    
                //    // Resets the rotation transformation on renderTarget
                //    renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
                //}
            }
        }

        for (auto bullet : enemyBullets) {

            ID2D1Bitmap* basicShotBitmap = bitmaps[bullet.currentFramePath];

            if (basicShotBitmap) {
                D2D1_SIZE_F size = basicShotBitmap->GetSize();

                D2D1_RECT_F position = D2D1::RectF(
                    ((screenX / 2) + ((bullet.xPos - player.xPos) * scalerX)) - ((size.width / 2) * scalerX),
                    ((screenY / 2) + ((bullet.yPos - player.yPos) * scalerY)) - ((size.height / 2) * scalerY),
                    ((screenX / 2) + ((bullet.xPos - player.xPos) * scalerX)) + ((size.width / 2) * scalerX),
                    ((screenY / 2) + ((bullet.yPos - player.yPos) * scalerY)) + ((size.height / 2) * scalerY)
                );

                double angleDegrees = bullet.angleRadians * (180.0 / pi);
                D2D1_POINT_2F center = D2D1::Point2F((position.right + position.left) / 2, (position.top + position.bottom) / 2);

                // Rotates sprite. Makes art less consistent but saves time
                D2D1_MATRIX_3X2_F rotation = D2D1::Matrix3x2F::Rotation(angleDegrees, center);

                // Rotates bitmap based on rotation calculations
                renderTarget->SetTransform(rotation);

                // 
                renderTarget->DrawBitmap(basicShotBitmap, position, 1.0F, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR);

                //ID2D1Bitmap* hitBox = bitmaps[files.hitBox];

                //if (hitBox) {
                //    D2D1_RECT_F perimeter = D2D1::RectF(
                //        ((screenX / 2) + ((bullet.hitbox.left - player.xPos) * scalerX)),
                //        ((screenY / 2) + ((bullet.hitbox.up - player.yPos) * scalerY)),
                //        ((screenX / 2) + ((bullet.hitbox.right - player.xPos) * scalerX)),
                //        ((screenY / 2) + ((bullet.hitbox.down - player.yPos) * scalerY))
                //    );

                //    // 
                //    renderTarget->DrawBitmap(hitBox, perimeter, 1.0F, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR);
                //}
                // Resets the rotation transformation on renderTarget
                renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
            }
        }

        //ID2D1Bitmap* hurtBox = bitmaps[files.hurtBox];

        //if (hurtBox) {
        //    D2D1_RECT_F perimeter = D2D1::RectF(
        //        (screenX / 2) - ((player.xPos - player.hitbox.left) * scalerX), 
        //        (screenY / 2) - ((player.yPos - player.hitbox.up) * scalerY),
        //        (screenX / 2) + ((player.hitbox.right - player.xPos) * scalerX),
        //        (screenY / 2) + ((player.hitbox.down - player.yPos) * scalerY)
        //    );

        //    // Rotates bitmap based on rotation calculations
        //    //renderTarget->SetTransform(rotation);

        //    // 
        //    renderTarget->DrawBitmap(hurtBox, perimeter, 1.0F, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR);

        //    // Resets the rotation transformation on renderTarget
        //    //renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
        //}

        ID2D1Bitmap* currencyIconBitmap = bitmaps[files.jewel_Red];
        if (currencyIconBitmap) {
            D2D1_SIZE_F size = currencyIconBitmap->GetSize();
            D2D1_RECT_F position = D2D1::RectF(
                (3 * scalerX) + leftBoundary,
                19 * scalerY,
                (3 * scalerX) + (size.width * scalerX) + leftBoundary,
                (19 * scalerY) + (size.height * scalerY)
            );
            renderTarget->DrawBitmap(currencyIconBitmap, position, 1.0F, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR);
        }

        std::string digits = std::to_string(player.currency);
        int spaces = 0;
        for (int i = 0; i < digits.length(); i++) {
            LPCWSTR filename;
            switch (digits[i]) {
            case '0':
                filename = files.font_0;
                break;
            case '1':
                filename = files.font_1;
                break;
            case '2':
                filename = files.font_2;
                break;
            case '3':
                filename = files.font_3;
                break;
            case '4':
                filename = files.font_4;
                break;
            case '5':
                filename = files.font_5;
                break;
            case '6':
                filename = files.font_6;
                break;
            case '7':
                filename = files.font_7;
                break;
            case '8':
                filename = files.font_8;
                break;
            case '9':
                filename = files.font_9;
                break;
            }
            ID2D1Bitmap* digitBitmap = bitmaps[filename];
            if (digitBitmap) {
                D2D1_SIZE_F size = digitBitmap->GetSize();
                D2D1_RECT_F position = D2D1::RectF(
                    (10 * scalerX) + (spaces * scalerX) + leftBoundary,
                    18 * scalerY,
                    (10 * scalerX) + (spaces * scalerX) + (size.width * scalerX) + leftBoundary,
                    (18 * scalerY) + (size.height * scalerY)
                );
                renderTarget->DrawBitmap(digitBitmap, position, 1.0F, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR);
                spaces += size.width + 1;
            }
        }

        double hp_bottom_width = 0;
        double boost_top_width = 0;
        for (auto elem : UI) {
            ID2D1Bitmap* bitmap = bitmaps[elem.currentFramePath];
            if (bitmap) {
                if (elem.name == L"Status_Bar") {
                    ID2D1Bitmap* statusBarBitmap = bitmaps[elem.currentFramePath];
                    if (statusBarBitmap) {
                        D2D1_SIZE_F size = statusBarBitmap->GetSize();
                        D2D1_RECT_F position = D2D1::RectF(
                            elem.xPos, elem.yPos,
                            elem.xPos + (size.width * scalerX), elem.yPos + (size.height * scalerY)
                        );
                        renderTarget->DrawBitmap(statusBarBitmap, position, 1.0F, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR);
                    }
                    continue;
                }
                if (elem.name == L"Health_Bar_Bottom") {
                    ID2D1Bitmap* healthBarBitmap = bitmaps[elem.currentFramePath];
                    if (healthBarBitmap) {
                        D2D1_SIZE_F size = healthBarBitmap->GetSize();
                        hp_bottom_width = size.width;
                        D2D1_RECT_F portion = D2D1::RectF(
                            elem.xPos, elem.yPos,
                            elem.xPos + ((size.width * scalerX) * (double(player.health) / double(player.maxHP))), elem.yPos + (size.height * scalerY)
                        );
                        D2D1_RECT_F source = D2D1::RectF(
                            0, 0,
                            size.width * (double(player.health) / double(player.maxHP)),
                            size.height
                        );

                        renderTarget->DrawBitmap(healthBarBitmap, portion, 1.0F, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, source);
                    }
                    continue;
                }
                if (elem.name == L"Health_Bar_Top") {
                    ID2D1Bitmap* healthBarBitmap = bitmaps[elem.currentFramePath];
                    if (healthBarBitmap) {
                        D2D1_SIZE_F size = healthBarBitmap->GetSize();
                        D2D1_RECT_F portion = D2D1::RectF(
                            elem.xPos, elem.yPos,
                            elem.xPos + ((size.width * scalerX) * min(1.0, (double(player.health) / ((size.width / hp_bottom_width) * double(player.maxHP))))), elem.yPos + (size.height * scalerY)
                        );
                        D2D1_RECT_F source = D2D1::RectF(
                            0, 0,
                            size.width * (double(player.health) / double(player.maxHP)),
                            size.height
                        );

                        renderTarget->DrawBitmap(healthBarBitmap, portion, 1.0F, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, source);
                    }
                    continue;
                }
                if (elem.name == L"Boost_Bar_Top") {
                    ID2D1Bitmap* boostBarBitmap = bitmaps[elem.currentFramePath];
                    if (boostBarBitmap) {
                        D2D1_SIZE_F size = boostBarBitmap->GetSize();
                        boost_top_width = size.width;
                        D2D1_RECT_F portion = D2D1::RectF(
                            elem.xPos, elem.yPos,
                            elem.xPos + ((size.width * scalerX) * (double(player.boost) / 100.0)), elem.yPos + ((size.height + .1) * scalerY)
                        );
                        D2D1_RECT_F source = D2D1::RectF(
                            0, 0,
                            size.width * (double(player.boost) / 100.0),
                            size.height
                        );

                        renderTarget->DrawBitmap(boostBarBitmap, portion, 1.0F, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, source);
                    }
                    continue;
                }
                if (elem.name == L"Boost_Bar_Bottom") {
                    ID2D1Bitmap* boostBarBitmap = bitmaps[elem.currentFramePath];
                    if (boostBarBitmap) {
                        D2D1_SIZE_F size = boostBarBitmap->GetSize();
                        D2D1_RECT_F portion = D2D1::RectF(
                            elem.xPos, elem.yPos,
                            elem.xPos + ((size.width * scalerX) * min(1.0, double(player.boost / ((size.width / boost_top_width) * 100.0)))), elem.yPos + (size.height * scalerY)
                        );
                        D2D1_RECT_F source = D2D1::RectF(
                            0, 0,
                            size.width * (double(player.boost) / 100.0),
                            size.height
                        );

                        renderTarget->DrawBitmap(boostBarBitmap, portion, 1.0F, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, source);
                    }
                    continue;
                }
            }
        }


        /*if (std::chrono::steady_clock::now() - mapTick >= std::chrono::nanoseconds(16666666)) {
            if (displayMap == true) {
                displayMap = false;
            }
            else {
                displayMap = true;
            }
            mapTick = std::chrono::steady_clock::now();
        }*/


        if (true) {
            ID2D1Bitmap* mapBmp = bitmaps[files.map_frame];
            if (mapBmp) {
                D2D1_SIZE_F mapFrameSize = mapBmp->GetSize();
                D2D1_RECT_F position = D2D1::RectF(
                    screenX - leftBoundary - ((mapFrameSize.width + 4) * scalerX),
                    screenY - ((mapFrameSize.height + 4) * scalerY),
                    screenX - leftBoundary - (4 * scalerX),
                    screenY - (4 * scalerY)
                );
                renderTarget->DrawBitmap(mapBmp, position, 1.0F, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR);

                ID2D1SolidColorBrush* brush;
                renderTarget->CreateSolidColorBrush(D2D1::ColorF(156 / 255.0f, 148 / 255.0f, 0), &brush);

                float proportionX;
                float proportionY;
                int length = sizeof(saveStations) / sizeof(saveStations[0]);
                for (int i = 0; i <= (length - 1); i++) {
                    proportionX = saveStations[i].xPos / mapSizeX;
                    proportionY = saveStations[i].yPos / mapSizeY;
                    D2D1_RECT_F saveStationIcon = D2D1::RectF(
                        screenX - leftBoundary - (int(mapFrameSize.width + 4 - (mapFrameSize.width * proportionX)) * scalerX),
                        screenY - (int(mapFrameSize.height + 4 - (mapFrameSize.height * proportionY)) * scalerY),
                        screenX - leftBoundary - (int(mapFrameSize.width + 5 - (mapFrameSize.width * proportionX)) * scalerX),
                        screenY - (int(mapFrameSize.height + 5 - (mapFrameSize.height * proportionY)) * scalerY)
                    );
                    renderTarget->FillRectangle(saveStationIcon, brush);
                }

                ID2D1Bitmap* baseIconBMP = bitmaps[files.base_icon];
                if (baseIconBMP) {
                    D2D1_SIZE_F size = baseIconBMP->GetSize();
                    for (auto base : bases) {
                        proportionX = base.xPos / mapSizeX;
                        proportionY = base.yPos / mapSizeY;
                        position = D2D1::RectF(
                            screenX - leftBoundary - (int(mapFrameSize.width + 4 + (size.width / 2) - (mapFrameSize.width * proportionX)) * scalerX),
                            screenY - (int(mapFrameSize.height + 4 + (size.height / 2) - (mapFrameSize.height * proportionY)) * scalerY),
                            screenX - leftBoundary - (int(mapFrameSize.width + 4 - (size.width / 2) - (mapFrameSize.width * proportionX)) * scalerX),
                            screenY - (int(mapFrameSize.height + 4 - (size.height / 2) - (mapFrameSize.height * proportionY)) * scalerY)
                        );
                        renderTarget->DrawBitmap(baseIconBMP, position, 1.0F, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR);
                    }
                }

                brush->SetColor(D2D1::ColorF(153 / 255.0F, 213 / 255.0F, 234 / 255.0F));
                proportionX = player.xPos / mapSizeX;
                proportionY = player.yPos / mapSizeY;
                D2D1_RECT_F playerIcon = D2D1::RectF(
                    screenX - leftBoundary - (int(mapFrameSize.width + 4 - (mapFrameSize.width * proportionX)) * scalerX),
                    screenY - (int(mapFrameSize.height + 4 - (mapFrameSize.height * proportionY)) * scalerY),
                    screenX - leftBoundary - (int(mapFrameSize.width + 5 - (mapFrameSize.width * proportionX)) * scalerX),
                    screenY - (int(mapFrameSize.height + 5 - (mapFrameSize.height * proportionY)) * scalerY)
                );
                renderTarget->FillRectangle(playerIcon, brush);
                brush->Release();
            }
        }


        //ID2D1Bitmap* asteroid = bitmaps[files.asteroid1];
        //if (asteroid) {
        //    D2D1_SIZE_F size = asteroid->GetSize();

        //    D2D1_RECT_F shipDisplayPosition = D2D1::RectF(
        //        (player.xPos) - ((size.width / 2) * scalerX),
        //        (player.yPos) - ((size.height / 2) * scalerY),
        //        (player.xPos) + ((size.width / 2) * scalerX),
        //        (player.yPos) + ((size.height / 2) * scalerY)
        //    );

        //    renderTarget->DrawBitmap(asteroid, shipDisplayPosition, 1.0F, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR);
        //}

        // Pop the clipping rectangle off the render target
        renderTarget->PopAxisAlignedClip();
    }
    else if (paused) {
        RenderTextMid("Paused", 128, 112);
    }
    else if (splashscreen) {
        // Pulls bitmap for background
        ID2D1Bitmap* splashscreenBitmap = bitmaps[L"Sprites\\Menu\\How_To_Play_Screen.png"];

        if (splashscreenBitmap) {

            // Gets the size of the background 
            D2D1_SIZE_F size = splashscreenBitmap->GetSize();
            D2D1_RECT_F screen = D2D1::RectF(leftBoundary, 0, rightBoundary, screenY);

            // Render a slice of the background equal to the camera coords, with no interpolation or transparency, to the defined display bounds
            renderTarget->DrawBitmap(splashscreenBitmap, screen, 1.0F, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR);
        }
    }

    HRESULT hr = S_OK;
    hr = renderTarget->EndDraw();
    if (hr == D2DERR_RECREATE_TARGET) {
        ReleaseD2DResourcesFromMemory();
    }
}

void UpdateGameLogic(double deltaTime) {

    if (gameState == 1) titleMenu.UpdateLogic();
    else if (gameState == 2) saveMenu.UpdateLogic();
    else if (gameState == 3) repairStation.UpdateLogic();
    else if (!paused && !splashscreen) {
        player.UpdateHitBox();
        for (auto& object : objects) {
            object.UpdateHitBox();
        }
        UpdateBackgroundElements(deltaTime);


        player.UpdateRedLightEffect(deltaTime);

        player.UpdateBullets(deltaTime, objects);
        CheckEnvironmentCollisions(environments);

        if (player.inAscendingSequence) {
            player.PlayAscendingSequence(deltaTime, saveStations[player.stationTouchingID]);
        }
        else if (player.inDockingSequence) {
            player.PlayDockingAnimation(deltaTime, saveStations[player.stationTouchingID]);
            if (!player.inDockingSequence) {
                gameState = 2;
            }
        }
        else {
            player.ApplyDirectionalInput(deltaTime);
            player.ApplyShootingLogic(deltaTime);
            UpdateSaveStationLogic(deltaTime);
        }

        bool spawnEnemies = true;
        bool spawnsExist = false;
        HandleEnemySpawns(deltaTime, spawnEnemies, spawnsExist);

        int spawnerCounter = 0;
        UpdateMasterObjectLogic(deltaTime, spawnerCounter);
        if ((spawnerCounter == 0) && spawnsExist) {
            timeSinceSpawn = std::chrono::steady_clock::now();
        }

        UpdateEnemyShootingLogic(deltaTime);
        CheckPickupCollision();
        UpdateOverworldAssets();
        UpdateSideViewCamera();

    }
}

void LoadEssentialData() {
    saveStations[0].id = 0;
    saveStations[0].xPos = mapSizeX * .25;
    saveStations[0].yPos = mapSizeY * .3;

    saveStations[1].id = 1;
    saveStations[1].xPos = mapSizeX * .5;
    saveStations[1].yPos = mapSizeY * .5;

    saveStations[2].id = 2;
    saveStations[2].xPos = mapSizeX * .85;
    saveStations[2].yPos = mapSizeY * .5;

    saveStations[0].UpdateHitBox();
    saveStations[1].UpdateHitBox();
    saveStations[2].UpdateHitBox();
}

LRESULT CALLBACK ProcessMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, int nCmdShow) {
    HRESULT hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &D2DFactory);
    if (SUCCEEDED(hr)) {
        WNDCLASSEX wc = { sizeof(WNDCLASSEX) };
        wc.style = CS_HREDRAW | CS_VREDRAW;
        wc.lpfnWndProc = ProcessMessage;
        wc.cbClsExtra = 0;
        wc.cbWndExtra = 0;
        wc.hInstance = hInstance;
        wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);
        wc.hbrBackground = NULL;
        wc.lpszMenuName = NULL;
        wc.lpszClassName = L"CSS 385 Program 1";
        wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

        if (RegisterClassEx(&wc)) {
            HWND hWnd = CreateWindowEx(0, L"CSS 385 Program 1", L"CSS 385 Program 1", WS_POPUP | WS_VISIBLE, 0, 0,
                screenX, screenY, NULL, NULL, hInstance, NULL);

            if (hWnd) {
                LoadFilePathsToVector(spriteFilePaths);
                LoadSpritesToMemory(hWnd, spriteFilePaths);
                LoadEssentialData();
                ShowWindow(hWnd, nCmdShow);
                //PlaySound(L"Music\\Neodyum Overworld Idea.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

                MSG msg;
                while (GetMessage(&msg, NULL, 0, 0)) {
                    std::chrono::duration<double> cDeltaTime = std::chrono::steady_clock::now() - lastLogicUpdate;
                    double deltaTime = cDeltaTime.count() * 50;
                    lastLogicUpdate = std::chrono::steady_clock::now();
                    /*for (auto obj : objects)
                    {
                        if ((abs(obj.xPos - player.xPos) > 256) || (abs(obj.yPos - player.yPos) > 224))
                        {
                            spriteFilePaths.erase(remove(spriteFilePaths.begin(), spriteFilePaths.end(), obj.currentFramePath), spriteFilePaths.end());
                        }
                        else
                        {
                            if (find(spriteFilePaths.begin(), spriteFilePaths.end(), obj.currentFramePath) == spriteFilePaths.end()) {
                                spriteFilePaths.emplace_back(obj.currentFramePath);
                            }
                        }
                    }*/
                    UpdateGameLogic(deltaTime);

                    TranslateMessage(&msg);
                    DispatchMessage(&msg);
                }
            }

            D2DFactory->Release();
        }
    }
    return 0;
}

LRESULT CALLBACK ProcessMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message)
    {
    case WM_KEYDOWN:
    {
        switch (wParam)
        {
        case VK_LEFT:
            keys.left = true;
            keys.directionPressed = true;
            break;
        case VK_RIGHT:
            keys.right = true;
            keys.directionPressed = true;
            break;
        case VK_UP:
            keys.up = true;
            keys.directionPressed = true;
            break;
        case VK_DOWN:
            keys.down = true;
            keys.directionPressed = true;
            break;
        case VK_SPACE:
            keys.space = true;
            break;
        case VK_SHIFT:
            keys.lShift = true;
            break;
        case VK_ESCAPE:
            keys.escape = true;
            break;
        case VK_Q:
            keys.q = true;
            break;
        case VK_S:
            keys.s = true;
            keys.down = true;
            keys.directionPressed = true;
            break;
        case VK_L:
            keys.l = true;
            break;
        case VK_CONTROL:
            keys.ctrl = true;
            break;
        case 'F':
            keys.f = true;
            break;
        case 'W':
            keys.up = true;
            keys.directionPressed = true;
            break;
        case 'A':
            keys.left = true;
            keys.directionPressed = true;
            break;
        case 'D':
            keys.right = true;
            keys.directionPressed = true;
            break;
        case 'J':
            keys.f = true;
            break;
        }
        break;
    }
    case WM_KEYUP:
    {
        switch (wParam)
        {
        case VK_LEFT:
            keys.left = false;
            if (!keys.right && !keys.up && !keys.down) {
                keys.directionPressed = false;
            }
            break;
        case VK_RIGHT:
            keys.right = false;
            if (!keys.left && !keys.up && !keys.down) {
                keys.directionPressed = false;
            }
            break;
        case VK_UP:
            keys.up = false;
            if (!keys.right && !keys.left && !keys.down) {
                keys.directionPressed = false;
            }
            break;
        case VK_DOWN:
            keys.down = false;
            if (!keys.right && !keys.up && !keys.left) {
                keys.directionPressed = false;
            }
            break;
        case VK_SPACE:
            keys.space = false;
            break;
        case VK_SHIFT:
            keys.lShift = false;
            break;
        case VK_ESCAPE:
            keys.escape = false;
            break;
        case VK_Q:
            keys.q = false;
            break;
        case VK_S:
            keys.s = false;
            keys.down = false;
            if (!keys.right && !keys.up && !keys.left) {
                keys.directionPressed = false;
            }
            break;
        case VK_L:
            keys.l = false;
            break;
        case VK_CONTROL:
            keys.ctrl = false;
            break;
        case 'F':
            keys.f = false;
            break;
        case 'W':
            keys.up = false;
            if (!keys.right && !keys.left && !keys.down) {
                keys.directionPressed = false;
            }
            break;
        case 'A':
            keys.left = false;
            if (!keys.right && !keys.up && !keys.down) {
                keys.directionPressed = false;
            }
            break;
        case 'D':
            keys.right = false;
            if (!keys.left && !keys.up && !keys.down) {
                keys.directionPressed = false;
            }
            break;
        case 'J':
            keys.f = false;
            break;
        }
        break;
    }
    case WM_PAINT:
    case WM_DISPLAYCHANGE:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);

        Render();

        EndPaint(hWnd, &ps);
        InvalidateRect(hWnd, NULL, FALSE);
    } break;
    case WM_DESTROY: {
        ReleaseD2DResourcesFromMemory();
        PostQuitMessage(0);
    } break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    if (keys.q && paused) {
        ReleaseD2DResourcesFromMemory();
        PostQuitMessage(0);
    }
    else if (keys.s && paused) {
        std::ofstream outFile(L"Save Files\\Save.txt");
        if (outFile.is_open()) {
            outFile << player.xPos << "\n" << player.yPos << "\n" << player.doubleShot << "\n";
        }
        paused = false;
    }
    else if (keys.l && paused) {
        std::ifstream inFile((L"Save Files\\Save.txt"));
        if (inFile.is_open()) {
            std::string line;

            if (std::getline(inFile, line)) {
                player.xPos = std::stod(line);
            }

            if (std::getline(inFile, line)) {
                player.yPos = std::stod(line);
            }

            if (std::getline(inFile, line)) {
                player.doubleShot = std::stoi(line);
            }

            player.bullets.clear();
            inFile.close();
            paused = false;
        }
    }
    if (keys.escape && (std::chrono::steady_clock::now() - pauseBuffer >= std::chrono::milliseconds(250))) {
        pauseBuffer = std::chrono::steady_clock::now();
        paused ? paused = false : paused = true;
    }

    return 0;
}
