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

#include "log.hpp"
#include "MCP25625Driver.hpp"

namespace ds = driver_sample;

class MCP25625DriverFixture : public ::testing::Test
{
public:
    MCP25625DriverFixture() : log_("/tmp"), driver_(nullptr) {}
    MCP25625DriverFixture(const MCP25625DriverFixture &) = delete;
    MCP25625DriverFixture &operator=(const MCP25625DriverFixture&) = delete;
    virtual ~MCP25625DriverFixture() {}

protected:
    ds::Log log_;
    std::unique_ptr<ds::MCP25625Driver> driver_;
};


TEST_F(MCP25625DriverFixture, TestInstantiation)
{
   driver_ = std::make_unique<ds::MCP25625Driver>();
}