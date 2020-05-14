#include "Loader.h"
#include "Renderer.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <algorithm>
#include <iostream>

void Loader::loadModels() {
    std::vector<std::string> modelDirs{
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
    for (int i = 0; i < modelDirs.size(); i++)
        Renderer::models[i + 10] = std::make_shared<Model>("models/" + modelDirs[i]);
}

void Loader::loadShaders() {
    Renderer::polyShader = std::make_shared<Shader>("shaders/poly.vs", "shaders/poly.fs");
}