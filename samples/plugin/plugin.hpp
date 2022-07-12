#include "sdk.hpp"

#include <iostream>

using namespace ung::sdk;

extern "C" auto load_plugin() -> std::unique_ptr<Plugin>;

struct TestSystem : public System {
    TestSystem() {}
    ~TestSystem() {}
    virtual auto init(entt::registry &) -> void override {}
    virtual auto execute(entt::registry &, float) -> void override {
        // POC
        std::cout << "Hello from plugin system\n";
    }
};