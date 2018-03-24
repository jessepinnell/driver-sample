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

#ifndef __SRC_MCP25625DRIVER_HPP__
#define __SRC_MCP25625DRIVER_HPP__

#include <stdexcept>
#include <string>
#include <memory>

namespace driver_sample
{

class Log;
class MCP25625Driver
{
   public:
      /** 
       * @brief Exception class indicating device initialization failure
       */
      class InitializationError : public std::runtime_error
      {
         explicit InitializationError(const std::string &message) : std::runtime_error(message) {}
         virtual ~InitializationError() {}
      };

      /** 
       * @brief Exception class indicating device communication failure
       */
      class CommunicationError : public std::runtime_error
      {
         explicit CommunicationError(const std::string &message) : std::runtime_error(message) {}
         virtual ~CommunicationError() {}
      };

      /** 
       * @brief Exception class indicating invalid operation or address
       */
      class InvalidArgumentError : public std::runtime_error
      {
         explicit InvalidArgumentError(const std::string &message) : std::runtime_error(message) {}
         virtual ~InvalidArgumentError() {}
      };

      MCP25625Driver();
      MCP25625Driver(const MCP25625Driver &) = delete;
      MCP25625Driver &operator=(const MCP25625Driver &) = delete;
      virtual ~MCP25625Driver();

      // TODO(jessepinnell)
   private:
};

}  // namespace driver_sample
#endif  // __SRC_MCP25625DRIVER_HPP__
