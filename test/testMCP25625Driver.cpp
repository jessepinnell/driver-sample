// MIT License

// Copyright (c) 2018 Jesse Pinnell

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include "gtest/gtest.h"
#pragma GCC diagnostic pop
#endif

#include <memory>
#include "log.hpp"
#include "MCP25625Driver.hpp"

namespace ds = driver_sample;

class MCP25625DriverFixture : public ::testing::Test
{
public:
    MCP25625DriverFixture() : log_(), driver_(nullptr) {}
    void SetUp() override
    {
       driver_ = std::make_unique<ds::MCP25625::Driver>();
       ASSERT_NE(driver_, nullptr);
    }
    MCP25625DriverFixture(const MCP25625DriverFixture &) = delete;
    MCP25625DriverFixture &operator=(const MCP25625DriverFixture&) = delete;
    virtual ~MCP25625DriverFixture() {}

protected:
    ds::Log log_;
    std::unique_ptr<ds::MCP25625::Driver> driver_;
};


TEST_F(MCP25625DriverFixture, TestReset)
{
   // Write a value and verify it
   uint8_t value;
   ASSERT_NO_THROW({ driver_->write(0x0, 0x11); });
   ASSERT_NO_THROW({ value = driver_->read(0x0); });
   EXPECT_EQ(value, 0x11);

   // Write reset it
   EXPECT_NO_THROW(driver_->reset());

   // Write read from the same address and expect a 0x0
   ASSERT_NO_THROW({ value = driver_->read(0x0); });
   EXPECT_EQ(value, 0x00);
}

TEST_F(MCP25625DriverFixture, TestRead)
{
   const uint8_t TRANSMIT_ERROR_COUNTER_CAN_ADDRESS = 0x1c;
   ASSERT_NO_THROW(driver_->read(TRANSMIT_ERROR_COUNTER_CAN_ADDRESS));
}

TEST_F(MCP25625DriverFixture, TestReadRecieveBuffer)
{
   // TODO(jessepinnell) precondition test
   const uint8_t ADDRESS = 0x12;
   ASSERT_NO_THROW(driver_->readReceiveBuffer(ADDRESS));
   // TODO(jessepinnell) postcondition test
}

TEST_F(MCP25625DriverFixture, TestWrite)
{
   // Write a value, read it and compare to written value, repeat with different value
   const uint8_t ADDRESS = 0x0;
   uint8_t value(0x0);
   EXPECT_NO_THROW({ driver_->write(ADDRESS, 0x11); });
   ASSERT_NO_THROW({ value = driver_->read(ADDRESS); });
   EXPECT_EQ(value, 0x11);

   EXPECT_NO_THROW({ driver_->write(ADDRESS, 0xdd); });
   ASSERT_NO_THROW({ value = driver_->read(ADDRESS); });
   EXPECT_EQ(value, 0xdd);
}

TEST_F(MCP25625DriverFixture, TestWriteTransmitBuffer)
{
   const uint8_t ADDRESS = 0x12;
   const uint8_t DATA_IN = 0xde;
   // TODO(jessepinnell) precondition test
   EXPECT_NO_THROW({ driver_->writeTransmitBuffer(ADDRESS, DATA_IN); });
   // TODO(jessepinnell) postcondition test
}

TEST_F(MCP25625DriverFixture, TestInvalidWriteTransmitBufferAddress)
{
   const uint8_t INVALID_ADDRESS = 0x12;
   EXPECT_THROW(driver_->writeTransmitBuffer(INVALID_ADDRESS, 0x0), ds::MCP25625::InvalidArgumentError);
}

TEST_F(MCP25625DriverFixture, TestRequestToSend)
{
   const bool RTS_TXB0 = false, RTS_TXB1 = false, RTS_TBX2 = false;
   // TODO(jessepinnell) precondition test
   EXPECT_NO_THROW({ driver_->requestToSend(RTS_TXB0, RTS_TXB1, RTS_TBX2); });
   // TODO(jessepinnell) postcondition test
}

TEST_F(MCP25625DriverFixture, TestReadStatus)
{
   ds::MCP25625::Status starting_status;
   EXPECT_NO_THROW({ starting_status = driver_->readStatus(); });
   // TODO(jessepinnell) force status flag change
   EXPECT_NO_THROW({ starting_status = driver_->readStatus(); });
   // TODO(jessepinnell) postcondition test
}

TEST_F(MCP25625DriverFixture, TestReceiveStatus)
{
   ds::MCP25625::ReceiveStatus starting_status;
   EXPECT_NO_THROW({ starting_status = driver_->readReceiveStatus(); });
   // TODO(jessepinnell) force status flag change
   EXPECT_NO_THROW({ starting_status = driver_->readReceiveStatus(); });
   // TODO(jessepinnell) postcondition test
}
