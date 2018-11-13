#ifndef ACID_TEST_ENTITY_H
#define ACID_TEST_ENTITY_H
#include <gtest/gtest.h>
#include <framework/node.h>
#include "entity.h"
class FakeComponent: public IComponent {
 public:
    FakeComponent() : IComponent() {}
};

class SetupTestEntity : public ::testing::Test {
 protected:
    void SetUp() final {
        ent = new Entity;
    }
    void TearDown() final {
        delete ent;
    }
    Entity* ent;
};

#endif //ACID_TEST_ENTITY_H
