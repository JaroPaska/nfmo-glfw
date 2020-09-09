#ifndef RESOURCE_HPP
#define RESOURCE_HPP

#include "Wheels.hpp"
#include <string>
#include <unordered_map>
#include <vector>

struct Resource {
    const std::vector<std::string> carnames{
        "2000tornados", "formula7", "canyenaro",  "lescrab",    "nimi",    "maxrevenge",
        "leadoxide",    "koolkat",  "drifter",    "policecops", "mustang", "king",
        "audir8",       "masheen",  "radicalone", "drmonster"};
    const std::vector<std::string> partnames{
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
    static std::unordered_map<std::string, Wheels *> wheelses;

    static Wheels *wheels(std::string folder) {
        if (wheelses.count(folder))
            return wheelses[folder];
        return wheelses[folder] = Wheels::fromFile(folder);
    }
};

#endif