
#include <cstddef>
#include <cstring>
#include <bserialize/BSerialize.hpp>
#include <gtest/gtest.h>
#include <memory>

namespace bs = CPM_BSERIALIZE_NS;

namespace {

TEST(BSerialize, BasicSerialization)
{
  const size_t bufferSize = 1024;
  char* buffer = static_cast<char*>(std::malloc(bufferSize));
  bs::BSerialize serializeOut(buffer, bufferSize);  

  uint8_t magicBytes[4];
  magicBytes[0] = 'T';
  magicBytes[1] = 'M';
  magicBytes[2] = 198;
  magicBytes[3] = 3;

  const char* nullTermString = "My null terminated string.";

  uint8_t   u8  =  248;
  int8_t    i8  = -34;

  uint16_t  u16 =  8329;
  int16_t   i16 = -298;

  uint32_t  u32 =  983287;
  int32_t   i32 = -1898223;

  uint64_t  u64 =  9182304812340712;
  int64_t   i64 = -328989777;

  float     f   =  389.082;
  double    d   = -89723.098;

  std::string str = "My string";

  // Write to buffer.
  serializeOut.writeBytes(reinterpret_cast<char*>(magicBytes), 4);
  serializeOut.writeNullTermString(nullTermString);
  serializeOut.write<uint8_t>(u8);
  serializeOut.write<int8_t>(i8);

  serializeOut.write(u16);
  serializeOut.write(i16);

  serializeOut.write(u32);
  serializeOut.write(i32);

  serializeOut.write(u64);
  serializeOut.write(i64);

  serializeOut.write<float>(f);
  serializeOut.write<double>(d);

  serializeOut.write(str);

  // Read from buffer
  bs::BSerialize serializeIn(buffer, bufferSize);  

  uint8_t* inMagicBytes = reinterpret_cast<uint8_t*>(serializeIn.readBytes(4));
  EXPECT_EQ('T', inMagicBytes[0]);
  EXPECT_EQ('M', inMagicBytes[1]);
  EXPECT_EQ(198, inMagicBytes[2]);
  EXPECT_EQ(3,   inMagicBytes[3]);

  const char* inStr = serializeIn.readNullTermString();
  EXPECT_EQ(std::string(inStr), std::string(nullTermString));

  EXPECT_EQ(u8, serializeIn.read<uint8_t>());
  EXPECT_EQ(i8, serializeIn.read<int8_t>());

  EXPECT_EQ(u16, serializeIn.read<uint16_t>());
  EXPECT_EQ(i16, serializeIn.read<int16_t>());

  EXPECT_EQ(u32, serializeIn.read<uint32_t>());
  EXPECT_EQ(i32, serializeIn.read<int32_t>());

  EXPECT_EQ(u64, serializeIn.read<uint64_t>());
  EXPECT_EQ(i64, serializeIn.read<int64_t>());

  EXPECT_EQ(f, serializeIn.read<float>());
  EXPECT_EQ(d, serializeIn.read<double>());

  EXPECT_EQ(str, serializeIn.read<std::string>());

  std::free(buffer);
}

TEST(BSerialize, FailWriteSerialization)
{
  const size_t bufferSize = 10;
  char* buffer = static_cast<char*>(std::malloc(bufferSize));
  bs::BSerialize serialize(buffer, bufferSize);  


  std::free(buffer);
}

TEST(BSerialize, FailReadSerialization)
{
  const size_t bufferSize = 10;
  char* buffer = static_cast<char*>(std::malloc(bufferSize));
  bs::BSerialize serialize(buffer, bufferSize);  



  std::free(buffer);
}

}

