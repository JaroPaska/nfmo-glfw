#include "Get.h"
#include "Stage.h"
#include <fstream>
#include <iostream>

Stage::Stage() {}

Stage::Stage(std::string path) {
    std::string string;
    std::ifstream reader(path);
    while (getline(reader, string)) {
        if (string.rfind("snap(", 0) == 0)
            snap = getvec3(string);
        if (string.rfind("sky(", 0) == 0)
            sky = getvec3(string);
        if (string.rfind("fog(", 0) == 0)
            fog = getvec3(string);
        if (string.rfind("ground(", 0) == 0)
            grnd = getvec3(string);
        if (string.rfind("fadefrom(", 0) == 0)
            fadefrom = getfloat(string, 0);
        if (string.rfind("lightson(") == 0)
            lightson = true;
        if (string.rfind("nlaps(", 0) == 0)
            nlaps = getint(string, 0);
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
            } else if (string.rfind("chk("), 0 == 0 && type == ROLLERCOASTER_CHECKPOINT) {
                xz = getfloat(string, 3);
                y = getfloat(string, 4);
            } else {
                xz = getfloat(string, 3);
                y = GROUND;
            }
            std::shared_ptr<StagePart> stagePart(new StagePart(type, x, y, z, xz));
            stageParts.push_back(stagePart);
            if (string.rfind("chk(", 0) == 0)
                checkPoints.push_back(stagePart);
            if (string.rfind("fix(", 0) == 0)
                fixPoints.push_back(stagePart);
        }
    }
    reader.close();
}