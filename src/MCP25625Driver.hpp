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
namespace MCP25625
{

class Log;

/** 
 * @brief Exception class indicating device initialization failure
 */
class InitializationError : public std::runtime_error
{
   public:
      explicit InitializationError(const std::string &message) : std::runtime_error(message) {}
      virtual ~InitializationError() {}
};

/** 
 * @brief Exception class indicating a method is unimplemented
 */
class UnimplementedException : public std::logic_error
{
   public:
      explicit UnimplementedException(const std::string &function) :
         std::logic_error(function + " is unimplemented") {}
      virtual ~UnimplementedException() {}
};

/** 
 * @brief Exception class indicating device communication failure
 */
class CommunicationError : public std::runtime_error
{
   public:
      explicit CommunicationError(const std::string &message) : std::runtime_error(message) {}
      virtual ~CommunicationError() {}
};

/** 
 * @brief Exception class indicating invalid operation or address
 */
class InvalidArgumentError : public std::runtime_error
{
   public:
      explicit InvalidArgumentError(const std::string &message) : std::runtime_error(message) {}
      virtual ~InvalidArgumentError() {}
};

struct Status
{
   bool rx0if_ = false,  // RX0IF (CANINTF Register)
      rx1if_ = false,    // RX1IF (CANINTF Register)
      tx0req_ = false,   // TXREQ (TXB0CTRL Register)
      tx0if_ = false,    // TX0IF (CANINTF Register)
      tx1req_ = false,   // TXREQ (TXB1CTRL Register)
      tx1if_ = false,    // TX1IF (CANINTF Register)
      tx2req_ = false,   // TXREQ (TXB2CTRL Register)
      tx2if_ = false;    // TX2IF (CANINTF Register)
};

enum class ReceiveMessage
{
   NO_RX_MESSAGE,
   MESSAGE_RXB0,
   MESSAGE_RXB1,
   MESSAGE_BOTH
};

enum class MessageType
{
   STANDARD_DATA_FRAME,
   STANDARD_REMOTE_FRAME,
   EXTENDED_DATA_FRAME,
   EXTENDED_REMOTE_FRAME
};

enum class FilterMatch
{
   RXF0,
   RXF1,
   RXF2,
   RXF3,
   RXF4,
   RXF5,
   RXF0_ROLLOVER_RXB1,
   RXF1_ROLLOVER_RXB1
};

struct ReceiveStatus
{
   ReceiveMessage receive_message_;
   MessageType message_status_;
   FilterMatch filter_match_;
};

class Driver
{
   public:
      Driver();
      Driver(const Driver &) = delete;
      Driver &operator=(const Driver &) = delete;
      virtual ~Driver();

      /** 
       * @brief Reset internal registers to default state and set configuration mode
       */
      void reset();

      /** 
       * @brief Read data from register at address
       * 
       * @param address The address from which to read
       * 
       * @return The data read from the register
       */
      uint8_t read(const uint8_t address);

      /** 
       * @brief Read data from receive buffer
       * This is faster than a read() call because the rx buffer address
       * is part of the command
       * 
       * @param receive_buffer The receive buffer address (0x0-0x3)
       * 
       * @return The data read from the register
       */
      uint8_t readReceiveBuffer(const uint8_t receive_buffer);

      /** 
       * @brief Write data to the register at address
       * 
       * @param address The address to which to write
       * @param data The data to write to the register
       */
      void write(const uint8_t address, const uint8_t data);

      /** 
       * @brief Write data to a transmit buffer
       * 
       * @param address The address to which to write (0x0-0x5)
       * @param data The data to write to the register
       */
      void writeTransmitBuffer(const uint8_t address, const uint8_t data);

      /** 
       * @brief Instruct the controller to begin the message transmission of the transmit buffers
       * 
       * @param rts_txb0 Do request-to-send for TXB0
       * @param rts_txb1 Do request-to-send for TXB1
       * @param rts_tbx2 Do request-to-send for TXB2
       */
      void requestToSend(const bool rts_txb0, const bool rts_txb1, const bool rts_tbx2);

      /** 
       * @brief Read the message reception and transmission status
       * 
       * @return The current message reception and transmission status
       */
      MCP25625::Status readStatus();

      /** 
       * @brief Read the receive status
       * 
       * @return The receive status
       */
      MCP25625::ReceiveStatus readReceiveStatus();

   private:
};

}  // namespace MCP25625
}  // namespace driver_sample
#endif  // __SRC_MCP25625DRIVER_HPP__
