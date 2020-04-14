#include "Get.h"
#include "Stage.h"
#include <fstream>

Stage::Stage() {}

Stage::Stage(int stage) {
    std::string string;
    std::ifstream reader("stages/" + std::to_string(stage) + ".txt");
    while (getline(reader, string)) {
        if (string.rfind("snap(", 0) == 0)
            snap = getvec3(string);
        if (string.rfind("sky(", 0) == 0)
            osky = getvec3(string);
        if (string.rfind("fog(", 0) == 0)
            ofog = getvec3(string);
        if (string.rfind("ground(", 0) == 0)
            ogrnd = getvec3(string);
        if (string.rfind("fadefrom(", 0) == 0)
            fadefrom = getfloat(string, 0);
        if (string.rfind("nlaps(", 0) == 0)
            nlaps = getint(string, 0);
        if (string.rfind("snap(", 0) == 0)
            snap = getvec3(string) / 100.f;
        if (string.rfind("set(", 0) == 0 || string.rfind("chk(", 0) == 0 ||
            string.rfind("fix(", 0) == 0) {
            int type = getint(string, 0);
            if (!scenery && StagePart::isScenery(type))
                continue;
            if (string.rfind("chk(", 0) == 0 && !StagePart::isCheckpoint(type))
                continue;
            if (string.rfind("fix(", 0) == 0 && !StagePart::isFixpoint(type))
                continue;
            float x, y, z, xz;
            x = getfloat(string, 1);
            z = getfloat(string, 2);
            if (string.rfind("fix(", 0) == 0) {
                y = getfloat(string, 3);
                xz = getfloat(string, 4);
            } else {
                y = GROUND;
                xz = getfloat(string, 3);
            }
            std::shared_ptr<StagePart> stagepart(new StagePart(type, x, y, z, xz));
            stageparts.push_back(stagepart);
            if (string.rfind("chk(", 0) == 0)
                checkpoints.push_back(stagepart);
            if (string.rfind("fix(", 0) == 0)
                fixpoints.push_back(stagepart);
        }
    }
    sky = osky * (glm::vec3(1) + snap);
    fog = ofog * (glm::vec3(1) + snap);
    grnd = ogrnd * (glm::vec3(1) + snap);
}