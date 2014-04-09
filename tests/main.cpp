
#include <cstdlib>
#include <iostream>
#include <exception>
#include <memory>
#include <ctime>

#include <gtest/gtest.h>

uint64_t gRandomSeed = 0;

int main(int argc, char** argv)
{
  // Add a global test environment that initializes an OpenGL batch renderer.
  ::testing::InitGoogleTest(&argc, argv);
  int ret = RUN_ALL_TESTS();
  return ret;
}

