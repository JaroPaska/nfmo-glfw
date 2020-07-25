#ifndef STAGEOBJECT_H
#define STAGEOBJECT_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

const glm::vec3 X_AXIS = glm::vec3(1, 0, 0);
const glm::vec3 Y_AXIS = glm::vec3(0, -1, 0);
const glm::vec3 Z_AXIS = glm::vec3(0, 0, 1);

const int NORMAL_ROAD = 10;
const int NORMAL_ROAD_EDGED = 11;
const int NORMAL_ROAD_TWISTED_LEFT = 12;
const int NORMAL_ROAD_TWISTED_RIGHT = 13;
const int NORMAL_ROAD_TURN = 14;
const int OFFROAD = 15;
const int OFFROAD_BUMPY_GREEN = 16;
const int OFFROAD_TURN = 17;
const int HALFPIPE_ROAD = 18;
const int HALFPIPE_ROAD_TURN = 19;
const int NORMAL_OFFROAD_BLEND = 20;
const int OFF_HALFPIPE_ROAD_BLEND = 21;
const int HALFPIPE_NORMAL_ROAD_BLEND = 22;
const int NORMAL_ROAD_END = 23;
const int OFFROAD_END = 24;
const int HALFPIPE_ROAD_RAMP_FILLER = 25;
const int BASIC_RAMP = 26;
const int CRASH_RAMP = 27;
const int TWO_WAY_RAMP = 28;
const int TWO_WAY_HIGH_LOW_RAMP = 29;
const int LANDING_RAMP = 30;
const int BIG_TAKEOFF_RAMP = 31;
const int SMALL_RAMP = 32;
const int OFFROAD_BUMP_RAMP = 33;
const int OFFROAD_BIG_RAMP = 34;
const int OFFROAD_RAMP = 35;
const int HALFPIPE = 36;
const int SPIKY_PILLARS = 37;
const int RAIL_DOORWAY = 38;
const int THE_WALL = 39;
const int CHECKPOINT = 40;
const int FIXING_HOOP = 41;
const int OFFROAD_CHECKPOINT = 42;
const int OFFROAD_BUMPY_SIDES = 43;
const int OFFROAD_BUMPY_SIDES_START = 44;
const int NORMAL_ROAD_RAISED_RAMP = 45;
const int NORMAL_ROAD_RAISED = 46;
const int NORMAL_ROAD_START = 47;
const int OFFROAD_START = 48;
const int TUNNEL_SIDE_RAMP = 49;
const int LAUNCH_PAD_RAMP = 50;
const int THE_NET = 51;
const int SPEED_RAMP = 52;
const int OFFROAD_HILL_RAMP = 53;
const int BUMP_SLIDE = 54;
const int OFFROAD_BIG_HILL_RAMP = 55;
const int ROLLERCOASTER_START_END = 56;
const int ROLLERCOASTER_CHECKPOINT = 64;

struct StageObject {
    int type;
    glm::vec3 pos;
    glm::quat rot;
    glm::vec3 scale;
    StageObject();
    StageObject(int type, float x, float y, float z, float xz);
    static bool isScenery(int type);
    static bool isCheckpoint(int type);
    static bool isFixpoint(int type);
};
#endif