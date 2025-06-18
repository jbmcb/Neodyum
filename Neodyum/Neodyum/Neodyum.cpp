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

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "windowscodecs.lib")

#undef min
#undef max
#define VK_L 0x4C
#define VK_Q 0x51
#define VK_S 0x53
#define pi 3.141592653589793238462643383279502884197

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
    LPCWSTR health_Bar = L"Sprites\\Menu\\Health_Bar.png";
    LPCWSTR boost_Bar = L"Sprites\\Menu\\Boost_Bar.png";
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

} files;

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
int mapSizeX = 5000;
int mapSizeY = 5000;

std::chrono::steady_clock::time_point mapTick = std::chrono::steady_clock::now();
bool displayMap;

bool isMultiCore = std::thread::hardware_concurrency() > 1;



struct hash_function {
    std::size_t operator()(const std::pair<int, int>& p) const {
        return std::hash<int>{}(p.first)* (std::hash<int>{}(p.second) << 1);
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


// Represents any visible entity
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

class Player : public Object {
public:
    int directionX, directionY;
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


    Player() {
        currentFramePath = files.playerFrame1;
    }

    void UpdateHitBox() {
        ID2D1Bitmap* object = bitmaps[currentFramePath];

        D2D1_SIZE_F size = object->GetSize();

        hitbox.left = xPos - (size.width / 2) + 4;
        hitbox.right = xPos + (size.width / 2) - 4;
        hitbox.up = yPos - (size.height / 2) + 4;
        hitbox.down = yPos + (size.height / 2) - 4;
    }

    //void PlayerIdle()
    //{
    //    // cycle through a basic animation
    //    if ((std::chrono::steady_clock::now() - lastFrameChange) >= frameInterval)
    //    {
    //        lastFrameChange = std::chrono::steady_clock::now();
    //        if (currentFramePath == files.playerFrame1)
    //        {
    //            currentFramePath = files.playerFrame2;
    //        }
    //        else
    //        {
    //            currentFramePath = files.playerFrame1;
    //        }
    //    }
    //}

    //void MovePlayer(double xDir, double yDir) {
    //    xPos += xDir;
    //    yPos += yDir;
    //    angle = -1 * atan2(xDir, xDir);
    //}
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
    bool direction;
    Star(int x, int y, int red, int green, int blue, float alpha) {
        xPos = x;
        yPos = y;
        r = red;
        g = green;
        b = blue;
        a = alpha;
        std::uniform_int_distribution<int> range(25, 75);
        int roll = range(generator);
        rate = (float(roll) / 20000.0);
        std::uniform_int_distribution<int> range1(0, 1);
        direction = range1(generator);
    }
    void Pulsate(double deltaTime) {
        if (direction) {
            a += rate * deltaTime;
            if (a >= 1.0) {
                a = 1.0;
                direction = false;
            }
        }
        else {
            a -= rate * deltaTime;
            if (a <= 0) {
                a = 0;
                direction = true;
            }
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
                bitmapFactory->Release();
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

LRESULT CALLBACK ProcessMessage(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

// Declarations
std::vector<LPCWSTR> spriteFilePaths;
std::vector<Object> bullets;
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

void Render() {

    renderTarget->BeginDraw();

    renderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));

    if (!paused && !splashscreen) {
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

            float left = std::max(0.0, std::max(player.xPos - 128, 0.0));
            float right = std::min(std::max(0.0, player.xPos + 128), double(size.width));
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

                            renderTarget->CreateSolidColorBrush(D2D1::ColorF(
                                star.r / 255.0,
                                star.g / 255.0,
                                star.b / 255.0,
                                star.a),
                                &brush);
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
        if (!player.dead) {
            // Pulls bitmap for player ship
            ID2D1Bitmap* playerBitmap = bitmaps[player.currentFramePath];
            float xOffset(0), yOffset(0);

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
                double angleRadians = 0;
                double angleDegrees = (player.angleRadians * pi) / 180;
                angleRadians = atan2(player.directionX, player.directionY);
                angleDegrees = angleRadians * (180.0 / 3.14159265359);
                player.angleRadians = angleRadians;
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

            if (redLightBitmap) {
                D2D1_SIZE_F size = redLightBitmap->GetSize();
                int xOff1(0), xOff2(0), yOff1(0), yOff2(0);
                if (player.currentFramePath == files.player_tilt_left || player.currentFramePath == files.player_tilt_right) {
                    xOff1 = -1;
                    xOff2 = 1;
                }
                else if (player.currentFramePath == files.player_sideways_l || player.currentFramePath == files.player_sideways_r) {
                    bool inverse;
                    if (player.directionX == 0) {
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

            D2D1_RECT_F displayPos = D2D1::RectF(
                (screenX / 2) - ((size.width / 2) * scalerX),
                (screenY / 2) - (((size.height / 2) + 8) * scalerY),
                (screenX / 2) + ((size.width / 2) * scalerX),
                (screenY / 2) + (((size.height / 2) - 8) * scalerY)
            );

            renderTarget->DrawBitmap(basicShotEffectBitmap, displayPos, 1.0F, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR);
        }

        // Resets the rotation transformation on renderTarget
        renderTarget->SetTransform(D2D1::Matrix3x2F::Identity());

        for (auto bullet : bullets) {

            ID2D1Bitmap* basicShotBitmap = bitmaps[bullet.currentFramePath];

            if (basicShotBitmap) {
                D2D1_SIZE_F size = basicShotBitmap->GetSize();

                D2D1_RECT_F position = D2D1::RectF(
                    ((screenX / 2) + ((bullet.xPos - player.xPos) * scalerX)) - ((size.width / 2) * scalerX),
                    ((screenY / 2) + ((bullet.yPos - player.yPos) * scalerY)) - ((size.height / 2) * scalerY),
                    ((screenX / 2) + ((bullet.xPos - player.xPos) * scalerX)) + ((size.width / 2) * scalerX),
                    ((screenY / 2) + ((bullet.yPos - player.yPos) * scalerY)) + ((size.height / 2) * scalerY)
                );

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

        for (auto object : objects) {
            if (object.name == L"Status_Bar") {
                ID2D1Bitmap* statusBarBitmap = bitmaps[object.currentFramePath];
                if (statusBarBitmap) {
                    D2D1_SIZE_F size = statusBarBitmap->GetSize();
                    D2D1_RECT_F position = D2D1::RectF(
                        object.xPos, object.yPos,
                        object.xPos + (size.width * scalerX), object.yPos + (size.height * scalerY)
                    );
                    renderTarget->DrawBitmap(statusBarBitmap, position, 1.0F, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR);
                }
            }
            if (object.name == L"Health_Bar") {
                ID2D1Bitmap* healthBarBitmap = bitmaps[object.currentFramePath];
                if (healthBarBitmap) {
                    D2D1_SIZE_F size = healthBarBitmap->GetSize();
                    D2D1_RECT_F portion = D2D1::RectF(
                        object.xPos, object.yPos,
                        object.xPos + ((size.width * scalerX) * (double(player.health) / double(player.maxHP))), object.yPos + (size.height * scalerY)
                    );
                    D2D1_RECT_F source = D2D1::RectF(
                        0, 0,
                        size.width * (double(player.health) / double(player.maxHP)),
                        size.height
                    );

                    renderTarget->DrawBitmap(healthBarBitmap, portion, 1.0F, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, source);
                }
            }
            if (object.name == L"Boost_Bar") {
                ID2D1Bitmap* boostBarBitmap = bitmaps[object.currentFramePath];
                if (boostBarBitmap) {
                    D2D1_SIZE_F size = boostBarBitmap->GetSize();
                    D2D1_RECT_F portion = D2D1::RectF(
                        object.xPos, object.yPos,
                        object.xPos + ((size.width * scalerX) * (double(player.boost) / 100.0)), object.yPos + (size.height * scalerY)
                    );
                    D2D1_RECT_F source = D2D1::RectF(
                        0, 0,
                        size.width * (double(player.health) / double(player.maxHP)),
                        size.height
                    );

                    renderTarget->DrawBitmap(boostBarBitmap, portion, 1.0F, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, source);
                }
            }
        }

        ID2D1Bitmap* currencyIconBitmap = bitmaps[files.jewel_Red];
        if (currencyIconBitmap) {
            D2D1_SIZE_F size = currencyIconBitmap->GetSize();
            D2D1_RECT_F position = D2D1::RectF(
                (4 * scalerX) + leftBoundary,
                25 * scalerY,
                (4 * scalerX) + (size.width * scalerX) + leftBoundary,
                (25 * scalerY) + (size.height * scalerY)
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
                    (11 * scalerX) + (spaces * scalerX) + leftBoundary,
                    24 * scalerY,
                    (11 * scalerX) + (spaces * scalerX) + (size.width * scalerX) + leftBoundary,
                    (24 * scalerY) + (size.height * scalerY)
                );
                renderTarget->DrawBitmap(digitBitmap, position, 1.0F, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR);
                spaces += size.width + 1;
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
                renderTarget->CreateSolidColorBrush(D2D1::ColorF(153 / 255.0F, 213 / 255.0F, 234 / 255.0F), &brush);

                float proportionX = player.xPos / mapSizeX;
                float proportionY = player.yPos / mapSizeY;
                D2D1_RECT_F playerIcon = D2D1::RectF(
                    screenX - leftBoundary - (int(mapFrameSize.width + 4 - (mapFrameSize.width * proportionX)) * scalerX),
                    screenY - (int(mapFrameSize.height + 4 - (mapFrameSize.height * proportionY)) * scalerY),
                    screenX - leftBoundary - (int(mapFrameSize.width + 5 - (mapFrameSize.width * proportionX)) * scalerX),
                    screenY - (int(mapFrameSize.height + 5 - (mapFrameSize.height * proportionY)) * scalerY)
                );
                renderTarget->FillRectangle(playerIcon, brush);
                brush->Release();

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

        ID2D1Bitmap* pauseBackground = bitmaps[files.pauseBackground];
        if (pauseBackground) {
            D2D_RECT_F position = D2D1::RectF(leftBoundary, 0, rightBoundary, screenY);
            renderTarget->DrawBitmap(pauseBackground, position, 1.0F, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR);
        }

        ID2D1Bitmap* pause = bitmaps[files.pause];
        if (pause) {
            D2D1_SIZE_F size = pause->GetSize();

            D2D_RECT_F position = D2D1::RectF(
                (screenX / 2) - ((size.width / 2) * scalerX),
                (screenY / 2) - ((size.height / 2) * scalerY),
                (screenX / 2) + ((size.width / 2) * scalerX),
                (screenY / 2) + ((size.height / 2) * scalerY)
            );

            renderTarget->DrawBitmap(pause, position, 1.0F, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR);
        }
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

void UpdateGameLogic(double deltaTime) {

    if (!paused && !splashscreen) {
        for (auto& object : objects) {
            object.UpdateHitBox();
        }

        int rightBound = (int(player.xPos + 128) / 256) + 1;
        int lowBound = (int(player.yPos + 112) / 224) + 1;

        int leftBound = ((int(player.xPos) - 128) / 256);
        int upBound = ((int(player.yPos) - 112) / 224);

        for (int y = upBound; y <= lowBound; ++y) {
            for (int x = leftBound; x <= rightBound; ++x) {
                auto it = starGrid.find({ x, y });
                if (it != starGrid.end()) {
                    for (Star& star : it->second) {
                        star.Pulsate(deltaTime);
                    }
                }
                else {
                    std::pair<int, int> cell = { x, y };

                    std::lock_guard<std::mutex> lock(chunkInProgress);
                    if (pendingChunks.count(cell)) {
                        continue;
                    }
                    else {
                        pendingChunks.insert(cell);
                    }

                    if (isMultiCore) {
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
                                            float alpha = std::max(float(roll) / 100000.0, 0.01);

                                            std::lock_guard<std::mutex> lock(chunkInProgress);
                                            starGrid[cell].emplace_back(j, i, r, g, b, alpha);
                                        }
                                    }
                                    roll = range(generator);
                                    if (roll <= 5) {
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
                        int rightBound = (int(player.xPos + 128) / 256) + 1;
                        int lowBound = (int(player.yPos + 112) / 224) + 1;

                        int leftBound = ((int(player.xPos) - 128) / 256);
                        int upBound = ((int(player.yPos) - 112) / 224);

                        for (int y = upBound; y <= lowBound; ++y) {
                            for (int x = leftBound; x <= rightBound; ++x) {
                                auto it = starGrid.find({ x, y });
                                if (it != starGrid.end()) {
                                    for (Star& star : it->second) {
                                        star.Pulsate(deltaTime);
                                    }
                                }
                                else {
                                    std::pair<int, int> cell = { x, y };
                                    std::vector<std::pair<int, int>> chunks = { cell };
                                    std::uniform_int_distribution<int> range(1, 100000);
                                    bool updated = false;
                                    for (int i = y * 224; i <= ((y * 224) + 224); i++) {
                                        for (int j = x * 256; j <= ((x * 256) + 256); j++) {
                                            int roll = range(generator);
                                            if (roll <= 250) {
                                                updated = true;
                                                std::pair<int, int> cell = { x , y };
                                                std::vector<std::pair<int, int>> chunks = { cell };

                                                bool starFound = false;
                                                for (const auto chunk : chunks) {
                                                    auto it = starGrid.find(chunk);
                                                    if (it != starGrid.end()) {
                                                        for (const auto& star : it->second) {
                                                            if (std::abs(star.xPos - j) <= 1 || std::abs(star.yPos - i) <= 1) {
                                                                starFound = true;
                                                                break;
                                                            }
                                                        }
                                                    }
                                                    if (starFound) {
                                                        break;
                                                    }
                                                }

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
                                                float alpha = std::max(float(roll) / 100000.0, 0.01);
                                                starGrid[cell].emplace_back(j, i, r, g, b, alpha);
                                            }
                                            roll = range(generator);
                                            if (roll <= 5) {
                                                std::pair<int, int> cell = { x, y };
                                                asteroids[cell].emplace_back(j, i);
                                            }
                                        }
                                    }

                                }
                            }
                        }
                    }
                }
            }
        }

        

        bool spawnEnemies = true;
        bool spawnsExist = false;
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
        }
        if (false/*spawnEnemies && (std::chrono::steady_clock::now() - timeSinceSpawn >= std::chrono::seconds(10))*/) {
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

        // Apply Player Inputs
        double boost = 1;
        if (keys.lShift && keys.directionPressed && !keys.f) {
            if (player.boost > 0 && ((std::chrono::steady_clock::now() - player.runoutTime) >= std::chrono::seconds(2))) {
                boost = 2;
                player.boost -= 1 * deltaTime;
                if (player.boost <= 0) {
                    player.boost = 0;
                    player.runoutTime = std::chrono::steady_clock::now();
                }
            }
            else {
                if ((std::chrono::steady_clock::now() - player.runoutTime) >= std::chrono::seconds(1)) {
                    player.boost += 0.66 * deltaTime;
                }
            }
        }
        else {
            if ((std::chrono::steady_clock::now() - player.runoutTime) >= std::chrono::seconds(1)) {
                player.boost += 0.66 * deltaTime;
            }
            if (player.boost > 100) {
                player.boost = 100;
            }
        }
        if (keys.up) {
            player.yPos -= (boost * deltaTime);
        }
        if (keys.down) {
            player.yPos += (boost * deltaTime);
        }
        if (keys.right) {
            player.xPos += (boost * deltaTime);
        }
        if (keys.left) {
            player.xPos -= (boost * deltaTime);
        }

        if (keys.right || keys.left || keys.up || keys.down) {
            if (!keys.f) {
                player.directionX = keys.right - keys.left;
                player.directionY = keys.up - keys.down;
            }
            else {
                if (abs(player.directionX) > 0 && player.directionY == 0 && !(keys.right && !keys.down && !keys.up && !keys.down)) {
                    if ((keys.up || keys.down) && !(keys.up && keys.down) && !(keys.right || keys.left)) {
                        bool inverse = (player.directionX > 0) ? false : true;
                        keys.up = (inverse) ? !keys.up : keys.up;
                        player.currentFramePath = (keys.up) ? files.player_sideways_l : files.player_sideways_r;
                        keys.up = (inverse) ? !keys.up : keys.up;
                    }
                    else if (keys.down && !keys.up) {
                        player.currentFramePath = (player.directionX > 0) ? files.player_tilt_right : files.player_tilt_left;
                    }
                    else if (keys.up && !keys.down) {
                        player.currentFramePath = (player.directionX > 0) ? files.player_tilt_left : files.player_tilt_right;
                    }
                    else {
                        player.currentFramePath = files.playerFrame1;
                    }
                }
                else if (abs(player.directionY) > 0 && player.directionX == 0 && (keys.left || keys.right)) {
                    if (player.directionY > 0) {
                        if (keys.left && keys.up) {
                            player.currentFramePath = (player.directionY > 0) ? files.player_tilt_left : files.player_tilt_right;
                        }
                        else if (keys.right && keys.up) {
                            player.currentFramePath = (player.directionY > 0) ? files.player_tilt_right : files.player_tilt_left;
                        }
                        else if (keys.left && !keys.up) {
                            player.currentFramePath = (player.directionY > 0) ? files.player_sideways_l : files.player_sideways_r;
                        }
                        else if (keys.right && !keys.up) {
                            player.currentFramePath = (player.directionY > 0) ? files.player_sideways_r : files.player_sideways_l;
                        }
                        else {
                            player.currentFramePath = files.playerFrame1;
                        }
                    }
                    if (player.directionY < 0) {
                        if (keys.left && keys.down) {
                            player.currentFramePath = (player.directionY > 0) ? files.player_tilt_left : files.player_tilt_right;
                        }
                        else if (keys.right && keys.down) {
                            player.currentFramePath = (player.directionY > 0) ? files.player_tilt_right : files.player_tilt_left;
                        }
                        else if (keys.left && !keys.down) {
                            player.currentFramePath = (player.directionY > 0) ? files.player_sideways_l : files.player_sideways_r;
                        }
                        else if (keys.right && !keys.down) {
                            player.currentFramePath = (player.directionY > 0) ? files.player_sideways_r : files.player_sideways_l;
                        }
                        else {
                            player.currentFramePath = files.playerFrame1;
                        }
                    }
                }
                else if (abs(player.directionX) > 0 && player.directionY > 0) {
                    if (player.directionX > 0) {
                        if (keys.right && keys.down) {
                            player.currentFramePath = files.player_sideways_r;
                        }
                        else if (keys.up && keys.left) {
                            player.currentFramePath = files.player_sideways_l;
                        }
                        else if (keys.up && !keys.right) {
                            player.currentFramePath = files.player_tilt_left;
                        }
                        else if (keys.right && !keys.up) {
                            player.currentFramePath = files.player_tilt_right;
                        }
                        else {
                            player.currentFramePath = files.playerFrame1;
                        }
                    }
                    else {
                        if (keys.left && keys.down) {
                            player.currentFramePath = files.player_sideways_l;
                        }
                        else if (keys.up && keys.right) {
                            player.currentFramePath = files.player_sideways_r;
                        }
                        else if (keys.up && !keys.left) {
                            player.currentFramePath = files.player_tilt_right;
                        }
                        else if (keys.left && !keys.up) {
                            player.currentFramePath = files.player_tilt_left;
                        }
                        else {
                            player.currentFramePath = files.playerFrame1;
                        }
                    }
                }
                else if (abs(player.directionX) > 0 && player.directionY < 0) {
                    if (player.directionX > 0) {
                        if (keys.right && keys.up) {
                            player.currentFramePath = files.player_sideways_l;
                        }
                        else if (keys.down && keys.left) {
                            player.currentFramePath = files.player_sideways_r;
                        }
                        else if (keys.down && !keys.right) {
                            player.currentFramePath = files.player_tilt_right;
                        }
                        else if (keys.right && !keys.down) {
                            player.currentFramePath = files.player_tilt_left;
                        }
                        else {
                            player.currentFramePath = files.playerFrame1;
                        }
                    }
                    else {
                        if (keys.left && keys.up) {
                            player.currentFramePath = files.player_sideways_r;
                        }
                        else if (keys.down && keys.right) {
                            player.currentFramePath = files.player_sideways_l;
                        }
                        else if (keys.down && !keys.left) {
                            player.currentFramePath = files.player_tilt_left;
                        }
                        else if (keys.left && !keys.down) {
                            player.currentFramePath = files.player_tilt_right;
                        }
                        else {
                            player.currentFramePath = files.playerFrame1;
                        }
                    }
                }
                else {
                    player.currentFramePath = files.playerFrame1;
                }
                //else if (abs(player.directionY) > 0 && player.directionX == 0) {
                //    player.currentFramePath = (keys.right - keys.left) ? files.player_tilt_right : files.player_tilt_left;
                //}
            }
        }
        else if (keys.f) {
            player.currentFramePath = files.playerFrame1;
        }

        if (!player.dead && !keys.f) {
            // Cycle Thruster Animation
            if (std::chrono::steady_clock::now() - player.lastThrusterTime >= std::chrono::milliseconds(100)) {
                player.lastThrusterTime = std::chrono::steady_clock::now();
                if (player.currentFramePath == files.playerFrame1) {
                    player.currentFramePath = files.playerFrame2;
                }
                else {
                    player.currentFramePath = files.playerFrame1;
                }
            }
        }

        // Cycle Ship's Red Lights effects
        if ((std::chrono::steady_clock::now() - player.lastRedLightTime) >= std::chrono::milliseconds(100)) {
            player.lastRedLightTime = std::chrono::steady_clock::now();
            if (player.redLightFrame == files.playerRedLightffect1) {
                player.redLightFrame = files.playerRedLightffect2;
            }
            else if (player.redLightFrame == files.playerRedLightffect2) {
                player.redLightFrame = files.playerRedLightffect3;
            }
            else if (player.redLightFrame == files.playerRedLightffect3) {
                player.redLightFrame = files.playerRedLightffect4;
            }
            else if (player.redLightFrame == files.playerRedLightffect4) {
                player.redLightFrame = files.playerRedLightffect5;
            }
            else if (player.redLightFrame == files.playerRedLightffect5) {
                player.redLightFrame = files.playerRedLightffect6;
            }
            else if (player.redLightFrame == files.playerRedLightffect6) {
                player.redLightFrame = files.playerRedLightffect7;
                player.fullBrightStart = std::chrono::steady_clock::now();
            }
            else if (std::chrono::steady_clock::now() - player.fullBrightStart >= std::chrono::milliseconds(500)) {
                player.redLightFrame = files.playerRedLightffect1;
            }
        }

        // Apply Ship's Shooting Logic
        if (keys.space && !player.basicShotFrame && (std::chrono::steady_clock::now() - player.lastShotEffectTime >= std::chrono::milliseconds(250))) {

            player.lastShotEffectTime = std::chrono::steady_clock::now();
            double xPosition, yPosition;

            if (player.doubleShot) {
                double xOffset(0), yOffset(0);
                xOffset = (-1.8 * sin(player.angleRadians * 2)) - 4;
                yOffset = 4 - ((4 / sin(pi / 4)) * sin(player.angleRadians));
                if (player.angleRadians > -pi / 6 && player.angleRadians < pi / 6) {
                    xOffset = -4;
                    yOffset = 4;
                }
                else if (player.angleRadians > (pi / 6) && player.angleRadians < (pi / 3)) {
                    xOffset = -5.6568542494923801952067548968388;
                    yOffset = 0;
                }
                else if (player.angleRadians > (pi / 3) && player.angleRadians < (2 * pi / 3)) {
                    xOffset = -4;
                    yOffset = 4;
                }
                else if (player.angleRadians > (2 * pi / 3) && player.angleRadians < (5 * pi / 6)) {
                    xOffset = 0;
                    yOffset = -5.6568542494923801952067548968388;
                }
                else if (player.angleRadians > (5 * pi / 6) && player.angleRadians < (7 * pi / 6)) {
                    xOffset = 4;
                    yOffset = -4;
                }
                else if (player.angleRadians > (-5 * pi / 6) && player.angleRadians < (-2 * pi / 3)) {
                    xOffset = 5.6568542494923801952067548968388;
                    yOffset = 0;
                }
                else if (player.angleRadians > (-2 * pi / 3) && player.angleRadians < (-pi / 3)) {
                    xOffset = 4;
                    yOffset = 4;
                }
                else if (player.angleRadians > (-pi / 3) && player.angleRadians < 0) {
                    xOffset = 0;
                    yOffset = 5.6568542494923801952067548968388;
                }
                bullets.emplace_back(files.basicShotDefault);
                bullets.back().xPos = player.xPos + xOffset + (11 * sin(player.angleRadians));
                bullets.back().yPos = player.yPos + yOffset - (11 * cos(player.angleRadians));
                bullets.back().power = player.power;
                bullets.back().UpdateHitBox();
                bullets.back().angleRadians = player.angleRadians;
                bullets.back().yVel = round(-cos(player.angleRadians) * 100) / 100;
                if (abs(bullets.back().yVel) < 0.0001) {
                    bullets.back().yVel = 0;
                }
                bullets.back().xVel = round(sin(player.angleRadians) * 100) / 100;
                if (abs(bullets.back().xVel) < 0.0001) {
                    bullets.back().xVel = 0;
                }


                if (player.angleRadians > -pi / 6 && player.angleRadians < pi / 6) {
                    xOffset = 4;
                    yOffset = 4;
                }
                else if (player.angleRadians > (pi / 6) && player.angleRadians < (pi / 3)) {
                    xOffset = 0;
                    yOffset = 5.6568542494923801952067548968388;
                }
                else if (player.angleRadians > (pi / 3) && player.angleRadians < (2 * pi / 3)) {
                    xOffset = -4;
                    yOffset = -4;
                }
                else if (player.angleRadians > (2 * pi / 3) && player.angleRadians < (5 * pi / 6)) {
                    xOffset = -5.6568542494923801952067548968388;
                    yOffset = 0;
                }
                else if (player.angleRadians > (5 * pi / 6) && player.angleRadians < (7 * pi / 6)) {
                    xOffset = -4;
                    yOffset = -4;
                }
                else if (player.angleRadians > (-5 * pi / 6) && player.angleRadians < (-2 * pi / 3)) {
                    xOffset = 0;
                    yOffset = -5.6568542494923801952067548968388;
                }
                else if (player.angleRadians > (-2 * pi / 3) && player.angleRadians < (-pi / 3)) {
                    xOffset = 4;
                    yOffset = -4;
                }
                else if (player.angleRadians > (-pi / 3) && player.angleRadians < 0) {
                    xOffset = 5.6568542494923801952067548968388;
                    yOffset = 0;
                }
                xPosition = player.xPos + xOffset + (11 * sin(player.angleRadians));
                yPosition = player.yPos + yOffset - (11 * cos(player.angleRadians));
            }
            else {
                xPosition = player.xPos + (11 * sin(player.angleRadians));
                yPosition = player.yPos - (11 * cos(player.angleRadians));
            }


            // Create new bullet, position it with player, give it its velocities
            bullets.emplace_back(files.basicShotDefault);
            bullets.back().xPos = xPosition;
            bullets.back().yPos = yPosition;
            bullets.back().UpdateHitBox();
            bullets.back().power = player.power;
            bullets.back().angleRadians = player.angleRadians;
            bullets.back().yVel = round(-cos(player.angleRadians) * 100) / 100;
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
            bullets.back().xVel = round(sin(player.angleRadians) * 100) / 100;
            if (abs(bullets.back().xVel) < 0.0001) {
                bullets.back().xVel = 0;
            }

            player.basicShotFrame = files.basicShotEffect1;
        }
        else if (player.basicShotFrame == files.basicShotEffect1 &&
            (std::chrono::steady_clock::now() - player.lastShotEffectTime >= std::chrono::nanoseconds(16666666))) {
            player.lastShotEffectTime = std::chrono::steady_clock::now();
            player.basicShotFrame = files.basicShotEffect2;
        }
        else if (player.basicShotFrame == files.basicShotEffect2 &&
            (std::chrono::steady_clock::now() - player.lastShotEffectTime >= std::chrono::nanoseconds(16666666))) {
            player.lastShotEffectTime = std::chrono::steady_clock::now();
            player.basicShotFrame = files.basicShotEffect3;
        }
        else if (player.basicShotFrame == files.basicShotEffect3 &&
            (std::chrono::steady_clock::now() - player.lastShotEffectTime >= std::chrono::nanoseconds(16666666))) {
            player.lastShotEffectTime = std::chrono::steady_clock::now();
            player.basicShotFrame = files.basicShotEffect4;
        }
        else if (player.basicShotFrame == files.basicShotEffect4 &&
            (std::chrono::steady_clock::now() - player.lastShotEffectTime >= std::chrono::nanoseconds(16666666))) {
            player.lastShotEffectTime = std::chrono::steady_clock::now();
            player.basicShotFrame = files.basicShotEffect5;
        }
        else if ((player.basicShotFrame == files.basicShotEffect5) &&
            (std::chrono::steady_clock::now() - player.lastShotEffectTime >= std::chrono::nanoseconds(16666666))) {
            player.basicShotFrame = nullptr;
        }

        int i = 0;
        if (bullets.size() >= 100) {
            i++;
        }

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

        int spawnerCounter = 0;
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
                                player.health = std::min(player.health + 10, player.maxHP);
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
        if ((spawnerCounter == 0) && spawnsExist) {
            timeSinceSpawn = std::chrono::steady_clock::now();
        }

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

        bool baseEntered = false;
        if (!baseDoorFound) {
            for (auto object : objects) {
                if (object.name == L"Entrance") {
                    if (player.CheckCollision(object)) {
                        background = files.base_Interior;
                        player.xPos = 128;
                        player.yPos = 112;
                        baseEntered = true;
                    }
                }
            }
        }

        player.UpdateHitBox();
        if (pickup.currentFramePath) {
            pickup.UpdateHitBox();
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
                        player.health = std::min(player.health + 10, player.maxHP);
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
    else {
        if (keys.space) {
            splashscreen = false;
        }
    }
}

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE, PWSTR, int nCmdShow) {

    // Filenames vector
    spriteFilePaths.emplace_back(files.background);
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
    spriteFilePaths.emplace_back(files.health_Bar);
    spriteFilePaths.emplace_back(files.player_Death_Animation_1);
    spriteFilePaths.emplace_back(files.player_Death_Animation_2);
    spriteFilePaths.emplace_back(files.player_Death_Animation_3);
    spriteFilePaths.emplace_back(files.jewel_Blue);
    spriteFilePaths.emplace_back(files.jewel_Green);
    spriteFilePaths.emplace_back(files.jewel_Purple);
    spriteFilePaths.emplace_back(files.jewel_Red);
    spriteFilePaths.emplace_back(files.jewel_Silver);
    spriteFilePaths.emplace_back(files.jewel_Yellow);
    spriteFilePaths.emplace_back(files.boost_Bar);
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

    player.power = 1;
    player.health = 100;
    player.maxHP = 100;
    player.xPos = float(mapSizeX) / 2;
    player.yPos = float(mapSizeY) / 2;



    std::uniform_int_distribution<int> range(1, 100000);
    int minY = std::max(int(player.yPos / 224) - 1, 0);
    int minX = std::max(int(player.xPos / 256) - 1, 0);
    int maxY = std::min(int(player.yPos / 224) + 1, int(mapSizeY / 224));
    int maxX = std::min(int(player.xPos / 256) + 2, int(mapSizeY / 256));

    for (int y = minY; y <= maxY; y++) {
        bool updated = false;
        for (int x = minX; x <= maxX; x++) {
            int roll = range(generator);
            if (roll <= 250) {
                updated = true;
                std::pair<int, int> cell = { x / 256, y / 224 };
                std::vector<std::pair<int, int>> chunks = { cell };
                if (x == 0) {
                    chunks.emplace_back( (x - 1) / 256, y / 224 );
                }
                else if (x == 256) {
                    chunks.emplace_back((x + 1) / 256, y / 224);
                }
                if (y == 0) {
                    chunks.emplace_back( x / 256, (y - 1) / 224);
                }
                else if (y == 224) {
                    chunks.emplace_back(x / 256, (y + 1) / 224);
                }

                bool starFound = false;
                for (const auto chunk : chunks) {
                    auto it = starGrid.find(chunk);
                    if (it != starGrid.end()) {
                        for (const auto& star : it->second) {
                            if (std::abs(star.xPos - x) <= 1 || std::abs(star.yPos - y) <= 1) {
                                starFound = true;
                                break;
                            }
                        }
                    }
                    if (starFound) {
                        break;
                    }
                }

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
                float alpha = std::max(float(roll) / 100000.0, 0.01);
                starGrid[cell].emplace_back(x, y, r, g, b, alpha);
            }
            roll = range(generator);
            if (roll <= 5) {
                std::pair<int, int> cell = { x / 256, y / 224 };
                asteroids[cell].emplace_back(x, y);
            }
        }
    }

    // Audio
    // SDL_Init(SDL_INIT_AUDIO);
    // Mix_OpenAudio(32000, MIX_DEFAULT_FORMAT, 2, 2048);
    // Mix_Music* background_Music = Mix_LoadMUS("C:\\Users\\My PC\\source\\repos\\CSS 385 - Program 1 Hello World\\CSS 385 - Program 1 Hello World\\background_music.mp3");

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
    bases.at(0).xPos = .6 * mapSizeX;
    bases.at(0).yPos = .8 * mapSizeY;
    bases.emplace_back(files.base);
    bases.at(1).xPos = .6 * mapSizeX;
    bases.at(1).yPos = .2 * mapSizeY;
    bases.emplace_back(files.base);
    bases.at(2).xPos = .85 * mapSizeX;
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
                true,
                true,
                true
            );
            objects[j + (i * 18)].turnRadius = pi / 4;
            objects[j + (i * 18)].shotSpeed = std::chrono::milliseconds(1250);
            objects[j + (i * 18)].shotVelocity = 5;
            objects[j + (i * 18)].shotType = files.basicShotBlue;
            objects[j + (i * 18)].defaultShotEffect = files.basicShotEffectBlue1;
            objects[j + (i * 18)].power = 10;
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
        objects.emplace_back(
            L"Entrance",
            bases.at(i).xPos - 181.5,
            bases.at(i).yPos - 0.5,
            -1,
            files.entrance,
            false,
            0,
            nullptr,
            files.entrance,
            0,
            0,
            false,
            false,
            false
        );
    }

    objects.emplace_back(L"Status_Bar", leftBoundary + (4 * scalerX), 4 * scalerY, 0,
        files.status_Bar, false, 0, nullptr, files.status_Bar, 0, 0, false, false, false);

    objects.emplace_back(L"Health_Bar", leftBoundary + (6 * scalerX), (5 * scalerY), 0,
        files.health_Bar, false, 0, nullptr, files.health_Bar, 0, 0, false, false, false);

    objects.emplace_back(L"Boost_Bar", leftBoundary + (6 * scalerX), (11 * scalerY), 0,
        files.boost_Bar, false, 0, nullptr, files.boost_Bar, 0, 0, false, false, false);



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
                LoadSpritesToMemory(hWnd, spriteFilePaths);
                ShowWindow(hWnd, nCmdShow);

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

            bullets.clear();
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