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
#include "include/log.hpp"
#include "MCP25625Driver.hpp"

namespace driver_sample
{
namespace MCP25625
{

Driver::Driver()
{
   LOG_INFO("Initializing driver...");
   // TODO(jessepinnell)
   LOG_INFO("Initialized");
}

Driver::~Driver()
{
   LOG_INFO("Shutting down driver...");
   // TODO(jessepinnell)
   LOG_INFO("Shut down");
}

void Driver::reset()
{
   // TODO(jessepinnell)
   throw UnimplementedException(__PRETTY_FUNCTION__);
}

uint8_t Driver::read(const uint8_t /*address*/)
{
   // TODO(jessepinnell)
   throw UnimplementedException(__PRETTY_FUNCTION__);
   return 0x0;
}

uint8_t Driver::readReceiveBuffer(const uint8_t /*receive_buffer*/)
{
   // TODO(jessepinnell)
   throw UnimplementedException(__PRETTY_FUNCTION__);
   return 0x0;
}

void Driver::write(const uint8_t /*address*/, const uint8_t /*data*/)
{
   // TODO(jessepinnell)
   throw UnimplementedException(__PRETTY_FUNCTION__);
}

void Driver::writeTransmitBuffer(const uint8_t /*address*/, const uint8_t /*data*/)
{
   // TODO(jessepinnell)
   throw UnimplementedException(__PRETTY_FUNCTION__);
}

void Driver::requestToSend(const bool /*rts_txb0*/, const bool /*rts_txb1*/, const bool /*rts_tbx2*/)
{
   // TODO(jessepinnell)
   throw UnimplementedException(__PRETTY_FUNCTION__);
}

MCP25625::Status Driver::readStatus()
{
   // TODO(jessepinnell)
   throw UnimplementedException(__PRETTY_FUNCTION__);
   return MCP25625::Status();
}

MCP25625::ReceiveStatus Driver::readReceiveStatus()
{
   // TODO(jessepinnell)
   throw UnimplementedException(__PRETTY_FUNCTION__);
   return MCP25625::ReceiveStatus();
}

}  // namespace MCP25625
}  // namespace driver_sample
