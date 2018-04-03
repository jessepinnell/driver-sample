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

// On Pi:
#include <bcm2835.h>
#include <unistd.h>

#include <memory>
#include <iomanip>
#include "include/log.hpp"
#include "MCP25625Driver.hpp"


namespace driver_sample
{
namespace MCP25625
{

Driver::Driver() : device_mutex_()
{
   LOG_INFO("Initializing driver...");
   if (!bcm2835_init())
   {
      throw InitializationError("bcm2835_spi_init() failed");
   }

   if (!bcm2835_spi_begin())
   {
      if (geteuid() == 0)
      {
         throw InitializationError("bcm2835_spi_begin() failed");
      }
      else
      {
         LOG_INFO("Not running as root, bcm2835_spi_begin() unavailable");
      }
   }
   bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_16384);

   LOG_INFO("Initialized");
}

Driver::~Driver()
{
   LOG_INFO("Shutting down driver...");
   bcm2835_spi_end();
   LOG_INFO("Shut down");
}

void Driver::reset()
{
   std::lock_guard<std::mutex> mutex_(device_mutex_);
   LOG_INFO("Reset");
   bcm2835_spi_transfer(0b1100'0000);
}

uint8_t Driver::read(const uint8_t address)
{
   std::lock_guard<std::mutex> mutex_(device_mutex_);
   char buffer[3] = { 0b0000'0011, address, 0xff };
   bcm2835_spi_transfern(buffer, 3);
   uint8_t return_value = buffer[2];

   LOG_INFO("Read 0x" << std::setfill('0') << std::hex << static_cast<uint16_t>(return_value)
         << " from 0x" << std::setw(2) << static_cast<uint16_t>(address));

   return return_value;
}

uint8_t Driver::readReceiveBuffer(const uint8_t receive_buffer)
{
   std::lock_guard<std::mutex> mutex_(device_mutex_);
   if (receive_buffer > 3)
   {
      throw InvalidArgumentError("Address buffer must be in [0..3]");
   }

   const uint8_t command = 0b0110'1000 | ((receive_buffer & 0x3) << 1);
   char buffer[2] = { command, 0x0 };
   bcm2835_spi_transfern(buffer, 2);
   uint8_t return_value = buffer[1];

   LOG_INFO("Read 0x" << std::setfill('0') << std::hex << static_cast<uint16_t>(return_value)
         << " from 0x" << std::setw(2) << static_cast<uint16_t>(receive_buffer)
         << " (command byte: 0x" << std::setw(2) << static_cast<uint16_t>(command) << ")");

   return return_value;
}

void Driver::write(const uint8_t address, const uint8_t data)
{
   std::lock_guard<std::mutex> mutex_(device_mutex_);
   char command[] = { 0b0000'0010, static_cast<char>(address), static_cast<char>(data) };
   bcm2835_spi_transfern(command, 3);

   LOG_INFO("Wrote 0x" << std::setfill('0') << std::hex << static_cast<uint16_t>(data)
         << " to 0x" << std::setw(2) << static_cast<uint16_t>(address));
}

void Driver::writeTransmitBuffer(const uint8_t address, const uint8_t data)
{
   std::lock_guard<std::mutex> mutex_(device_mutex_);
   if (address > 6)
   {
      throw InvalidArgumentError("Address buffer must be in [0..5]");
   }

   char command[] = { static_cast<char>(0b0100'0000 | address), static_cast<char>(data) };
   bcm2835_spi_transfern(command, 2);

   LOG_INFO("Wrote 0x" << std::setfill('0') << std::hex << static_cast<uint16_t>(data)
         << " to 0x" << std::setw(2) << static_cast<uint16_t>(address));
}

void Driver::requestToSend(const bool rts_txb0, const bool rts_txb1, const bool rts_txb2)
{
   std::lock_guard<std::mutex> mutex_(device_mutex_);
   uint8_t command(0b1000'000 | (rts_txb0 << 2) | (rts_txb1 << 1) | rts_txb2);
   bcm2835_spi_write(command);

   LOG_INFO("Wrote RTS values txb0(" << std::boolalpha << rts_txb0
         << "), txb1(" << rts_txb1 << "), txb2(" << rts_txb2
         << "), command: 0x" << std::setw(2) << static_cast<uint16_t>(command));
}

MCP25625::Status Driver::readStatus()
{
   std::lock_guard<std::mutex> mutex_(device_mutex_);
   bcm2835_spi_transfer(0b1010'0000);
   uint8_t return_value = bcm2835_spi_transfer(0xff);

   MCP25625::Status status {
      return_value & 0b0000'0001,
      return_value & 0b0000'0010,
      return_value & 0b0000'0100,
      return_value & 0b0000'1000,
      return_value & 0b0001'0000,
      return_value & 0b0010'0000,
      return_value & 0b0100'0000,
      return_value & 0b1000'0000
   };

   LOG_INFO("Read read status " << status);
   return status;
}

MCP25625::ReceiveStatus Driver::readReceiveStatus()
{
   std::lock_guard<std::mutex> mutex_(device_mutex_);
   bcm2835_spi_transfer(0b1011'0000);
   uint8_t return_value = bcm2835_spi_transfer(0xff);

   ReceiveMessage receive_message(ReceiveMessage::NO_RX_MESSAGE);
   switch (return_value & 0b1100'0000)
   {
      case 0b0000'0000:
         receive_message = ReceiveMessage::NO_RX_MESSAGE;
         break;
      case 0b0100'0000:
         receive_message = ReceiveMessage::MESSAGE_RXB0;
         break;
      case 0b1000'0000:
         receive_message = ReceiveMessage::MESSAGE_RXB1;
         break;
      case 0b1100'0000:
         receive_message = ReceiveMessage::MESSAGE_BOTH;
         break;
      default:
         throw CommunicationError("Invalid receive message value");
         break;
   }

   MessageType message_status(MessageType::STANDARD_DATA_FRAME);
   switch (return_value & 0b0011'0000)
   {
      case 0b0000'0000:
         message_status = MessageType::STANDARD_DATA_FRAME;
         break;
      case 0b0001'0000:
         message_status = MessageType::STANDARD_REMOTE_FRAME;
         break;
      case 0b0010'0000:
         message_status = MessageType::EXTENDED_DATA_FRAME;
         break;
      case 0b0011'0000:
         message_status = MessageType::EXTENDED_REMOTE_FRAME;
         break;
      default:
         throw CommunicationError("Invalid message status value");
         break;
   }

   FilterMatch filter_match(FilterMatch::RXF0);
   switch (return_value & 0b0000'0111)
   {
      case 0b0000'0000:
         filter_match = FilterMatch::RXF0;
         break;
      case 0b0000'0001:
         filter_match = FilterMatch::RXF1;
         break;
      case 0b0000'0010:
         filter_match = FilterMatch::RXF2;
         break;
      case 0b0000'0011:
         filter_match = FilterMatch::RXF3;
         break;
      case 0b0000'0100:
         filter_match = FilterMatch::RXF4;
         break;
      case 0b0000'0101:
         filter_match = FilterMatch::RXF5;
         break;
      case 0b0000'0110:
         filter_match = FilterMatch::RXF0_ROLLOVER_RXB1;
         break;
      case 0b0000'0111:
         filter_match = FilterMatch::RXF1_ROLLOVER_RXB1;
         break;
      default:
         throw CommunicationError("Invalid filter match value");
         break;
   }

   MCP25625::ReceiveStatus status {
      receive_message,
      message_status,
      filter_match
   };

   LOG_INFO("Read receive status " << status);
   return status;
}

}  // namespace MCP25625
}  // namespace driver_sample
