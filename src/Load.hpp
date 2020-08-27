#ifndef LOAD_HPP
#define LOAD_HPP

#include "DynamicModel.hpp"
#include "Wheels.hpp"
#include <vector>

struct Load {
    static std::vector<DynamicModel> carModels;
    static std::vector<Wheels> wheelData;
    static std::vector<DynamicModel> partModels;

    static void cars() {
        std::vector<std::string> carNames{
            "2000tornados", "formula7", "canyenaro",  "lescrab",    "nimi",    "maxrevenge",
            "leadoxide",    "koolkat",  "drifter",    "policecops", "mustang", "king",
            "audir8",       "masheen",  "radicalone", "drmonster",  "lmp"};
        Load::carModels.resize(carNames.size());
        for (int i = 0; i < carNames.size(); i++) {
            std::string folder = "cars/" + carNames[i];
            Load::carModels[i] = DynamicModel::fromFile(folder);
            Load::wheelData[i] = Wheels::fromFile(folder);
        }
    }

    static void parts() {
        std::vector<std::string> partNames{
            "road",          "froad",    "twister2",      "twister1", "turn",      "offroad",
            "bumproad",      "offturn",  "nroad",         "nturn",    "roblend",   "noblend",
            "rnblend",       "roadend",  "offroadend",    "hpground", "ramp30",    "cramp35",
            "dramp15",       "dhilo15",  "slide10",       "takeoff",  "sramp22",   "offbump",
            "offramp",       "sofframp", "halfpipe",      "spikes",   "rail",      "thewall",
            "checkpoint",    "fixpoint", "offcheckpoint", "sideoff",  "bsideoff",  "uprise",
            "riseroad",      "sroad",    "soffroad",      "tside",    "launchpad", "thenet",
            "speedramp",     "offhill",  "slider",        "uphill",   "roll1",     "roll2",
            "roll3",         "roll4",    "roll5",         "roll6",    "opile1",    "opile2",
            "aircheckpoint", "tree1",    "tree2",         "tree3",    "tree4",     "tree5",
            "tree6",         "tree7",    "tree8",         "cac1",     "cac2",      "cac3",
            "8sroad",        "8soffroad"};
        Load::partModels.resize(partNames.size());
        for (int i = 0; i < partNames.size(); i++)
            Load::partModels[i] = DynamicModel::fromFile("parts/" + partNames[i]);
    }
};

#endif