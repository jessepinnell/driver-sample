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

#include <memory>
#include <iostream>
#include "log.hpp"
#include "MCP25625Driver.hpp"

namespace ds = driver_sample;

int main()
{
   ds::Log log;
   LOG_INFO("**************** Simple Driver App ****************");
   LOG_INFO(DRIVER_SAMPLE_BUILD_TARGET_NAME
      << " built " << DRIVER_SAMPLE_BUILD_TIME
      << " on " << DRIVER_SAMPLE_BUILD_HOST);
   LOG_INFO("Kernel build rev. " << DRIVER_SAMPLE_BUILD_KERNEL_RELEASE);
   LOG_INFO("Source build rev. " << DRIVER_SAMPLE_BUILD_GIT_REVISION);
   LOG_INFO("***************************************************");

   auto driver = std::make_shared<ds::MCP25625::Driver>();

   driver->reset();
   driver->read(0x12);
   driver->readReceiveBuffer(0);
   driver->readReceiveBuffer(1);
   driver->readReceiveBuffer(2);
   driver->readReceiveBuffer(3);

   driver->write(0xde, 0xbe);

   driver->writeTransmitBuffer(3, 0xef);

   driver->requestToSend(false, false, true);
   driver->requestToSend(true, false, true);
   driver->requestToSend(false, true, true);

   auto status = driver->readStatus();
   (void)status;

   auto receive_status = driver->readReceiveStatus();
   (void)receive_status;
   return 0;
}
