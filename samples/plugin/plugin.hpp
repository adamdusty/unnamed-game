#include "sdk.hpp"

#include <iostream>

using namespace ung::sdk;

extern "C" auto load_plugin() -> Plugin;

struct TestSystem : public System {
    TestSystem() {}
    ~TestSystem() override {}
    auto init(entt::registry &) -> void override {}
    auto execute(entt::registry &, float) -> void override {
        // POC
        std::cout << "Hello from plugin system\n";
    }
};