#include "Get.h"
#include "Loader.h"
#include "Stage.h"
#include <fstream>
#include <iostream>

Stage::Stage() {}

Stage::Stage(std::string path) {
    std::string string;
    std::ifstream reader(path + "/stageInfo");
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
        if (string.rfind("lightson(", 0) == 0)
            lightson = true;
        if (string.rfind("nlaps(", 0) == 0)
            nlaps = getint(string, 0);
        if (string.rfind("set(", 0) == 0 || string.rfind("chk(", 0) == 0 ||
            string.rfind("fix(", 0) == 0 && nfix > 0) {
            int type = getint(string, 0);
            if (!scenery && StageObject::isScenery(type))
                continue;
            if (string.rfind("chk(", 0) == 0 && !StageObject::isCheckpoint(type))
                continue;
            if (string.rfind("fix(", 0) == 0 && !StageObject::isFixpoint(type))
                continue;
            float x, y, z, xz;
            x = getfloat(string, 1);
            z = getfloat(string, 2);
            if (string.rfind("fix(", 0) == 0) {
                y = getfloat(string, 3);
                xz = getfloat(string, 4);
            } else if (string.rfind("chk(", 0) == 0 && type == ROLLERCOASTER_CHECKPOINT) {
                xz = getfloat(string, 3);
                y = getfloat(string, 4);
            } else {
                xz = getfloat(string, 3);
                y = GROUND;
            }
            std::unique_ptr<StageObject> stageObject =
                std::make_unique<StageObject>(type, x, y, z, xz);
            stageObjects[nextID] = std::move(stageObject);
            if (string.rfind("chk(", 0) == 0)
                checkPoints.push_back(nextID);
            if (string.rfind("fix(", 0) == 0)
                fixPoints.push_back(nextID);
            nextID++;
        }
        if (string.rfind("maxr(", 0) == 0) {
            int n = getint(string, 0);
            float x = getfloat(string, 1);
            float sz = getfloat(string, 2);
            for (int i = 0; i < n; i++) {
                std::unique_ptr<StageObject> stageObject =
                    std::make_unique<StageObject>(THE_WALL, x, GROUND, sz + i * 4800, 0);
                stageObjects[nextID++] = std::move(stageObject);
            }
        }
        if (string.rfind("maxl(", 0) == 0) {
            int n = getint(string, 0);
            float x = getfloat(string, 1);
            float sz = getfloat(string, 2);
            for (int i = 0; i < n; i++) {
                std::unique_ptr<StageObject> stageObject =
                    std::make_unique<StageObject>(THE_WALL, x, GROUND, sz + i * 4800, 180);
                stageObjects[nextID++] = std::move(stageObject);
            }
        }
        if (string.rfind("maxt(", 0) == 0) {
            int n = getint(string, 0);
            float z = getfloat(string, 1);
            float sx = getfloat(string, 2);
            for (int i = 0; i < n; i++) {
                std::unique_ptr<StageObject> stageObject =
                    std::make_unique<StageObject>(THE_WALL, sx + i * 4800, GROUND, z, 90);
                stageObjects[nextID++] = std::move(stageObject);
            }
        }
        if (string.rfind("maxb(", 0) == 0) {
            int n = getint(string, 0);
            float z = getfloat(string, 1);
            float sx = getfloat(string, 2);
            for (int i = 0; i < n; i++) {
                std::unique_ptr<StageObject> stageObject =
                    std::make_unique<StageObject>(THE_WALL, sx + i * 4800, GROUND, z, -90);
                stageObjects[nextID++] = std::move(stageObject);
            }
        }
    }
    reader.close();
    groundModel = std::make_unique<Model>(path + "/ground");
    polys1Model = std::make_unique<Model>(path + "/polys1");
    polys2Model = std::make_unique<Model>(path + "/polys2");
    cloudsModel = std::make_unique<Model>(path + "/clouds");
    mountainsModel = std::make_unique<Model>(path + "/mountains");
}