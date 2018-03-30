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
   // TODO(jessepinnell) precondition test
   ASSERT_THROW(driver_->reset(), ds::MCP25625::UnimplementedException);
   // TODO(jessepinnell) postcondition test
}

TEST_F(MCP25625DriverFixture, TestRead)
{
   const uint8_t ADDRESS = 0x12;
   // TODO(jessepinnell) precondition test
   ASSERT_THROW(driver_->read(ADDRESS), ds::MCP25625::UnimplementedException);
   // TODO(jessepinnell) postcondition test
}

TEST_F(MCP25625DriverFixture, TestInvalidReadAddress)
{
   const uint8_t INVALID_ADDRESS = 0xff;
   uint8_t value(0);
   EXPECT_THROW({value = driver_->read(INVALID_ADDRESS);}, ds::MCP25625::UnimplementedException);
   (void)value;
}

TEST_F(MCP25625DriverFixture, TestReadRecieveBuffer)
{
   // TODO(jessepinnell) precondition test
   const uint8_t ADDRESS = 0x12;
   ASSERT_THROW(driver_->readReceiveBuffer(ADDRESS), ds::MCP25625::UnimplementedException);
   // TODO(jessepinnell) postcondition test
}

TEST_F(MCP25625DriverFixture, TestInvalidReadReceiveBufferAddress)
{
   const uint8_t INVALID_ADDRESS = 0xff;
   ASSERT_THROW(driver_->readReceiveBuffer(INVALID_ADDRESS), ds::MCP25625::UnimplementedException);
}

TEST_F(MCP25625DriverFixture, TestWriteTransmitBuffer)
{
   const uint8_t ADDRESS = 0x12;
   const uint8_t DATA_IN = 0xde;
   // TODO(jessepinnell) precondition test
   ASSERT_THROW(driver_->writeTransmitBuffer(ADDRESS, DATA_IN), ds::MCP25625::UnimplementedException);
   // TODO(jessepinnell) postcondition test
}

TEST_F(MCP25625DriverFixture, TestInvalidWriteTransmitBufferAddress)
{
   const uint8_t INVALID_ADDRESS = 0x12;
   ASSERT_THROW(driver_->writeTransmitBuffer(INVALID_ADDRESS, 0x0), ds::MCP25625::UnimplementedException);
}

TEST_F(MCP25625DriverFixture, TestRequestToSend)
{
   const bool RTS_TXB0 = false, RTS_TXB1 = false, RTS_TBX2 = false;
   // TODO(jessepinnell) precondition test
   ASSERT_THROW(driver_->requestToSend(RTS_TXB0, RTS_TXB1, RTS_TBX2), ds::MCP25625::UnimplementedException);
   // TODO(jessepinnell) postcondition test
}

TEST_F(MCP25625DriverFixture, TestReadStatus)
{
   ds::MCP25625::Status starting_status;
   ASSERT_THROW({ starting_status = driver_->readStatus(); }, ds::MCP25625::UnimplementedException);
   // TODO(jessepinnell) force status flag change
   ASSERT_THROW({ starting_status = driver_->readStatus(); }, ds::MCP25625::UnimplementedException);
   // TODO(jessepinnell) postcondition test
}

TEST_F(MCP25625DriverFixture, TestReceiveStatus)
{
   ds::MCP25625::ReceiveStatus starting_status;
   ASSERT_THROW({ starting_status = driver_->readReceiveStatus(); }, ds::MCP25625::UnimplementedException);
   // TODO(jessepinnell) force status flag change
   ASSERT_THROW({ starting_status = driver_->readReceiveStatus(); }, ds::MCP25625::UnimplementedException);
   // TODO(jessepinnell) postcondition test
}
