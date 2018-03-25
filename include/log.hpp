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

#ifndef __INCLUDE_LOG_HPP__
#define __INCLUDE_LOG_HPP__

// TODO(jessepinnell) add more levels

#ifdef G3LOG_FOUND
// Get g3log: https://github.com/KjellKod/g3log
# include <g3log/g2log.hpp>
# include <g3log/logworker.hpp>
# include <memory>
# include <iostream>
# define LOG_INFO(x) do { LOG(INFO) << x; } while(0)
# define LOG_ERROR(x) do { LOG(ERROR) << x; } while(0)
#else
# include <iostream>
# ifdef LOG_INFO
#  undef LOG_INFO
# endif
# ifdef LOG_ERROR
#  undef LOG_ERROR
# endif
# define LOG_INFO(x) do { std::cout << "INFO: " << x << std::endl; } while(0)
# define LOG_ERROR(x) do { std::cerr << "ERROR: " << x << std::endl; } while(0)
#endif

namespace driver_sample
{
#ifdef G3LOG_FOUND
class Log
{
   public:
      class LogSink
      {
         public:
            LogSink() {}
            virtual ~LogSink() {}
            void ReceiveLogMessage(g3::LogMessageMover message)
            {
               std::cout << message.get().toString() << std::flush;
            }
      };

      Log() : log_worker_(g3::LogWorker::createLogWorker())
      {
         // File version
#if 0
         auto handle = log_worker_->addDefaultLogger(
               DRIVER_SAMPLE_BUILD_TARGET_NAME, "/tmp");
#else
         auto sinkHandle = log_worker_->addSink(std::make_unique<LogSink>(),
                                                &LogSink::ReceiveLogMessage);
#endif
         g3::initializeLogging(log_worker_.get());
      }

      Log(const Log &) = delete;
      Log &operator=(const Log &) = delete;

      virtual ~Log()
      {
      }
   private:
      std::unique_ptr<g3::LogWorker> log_worker_;
};
#else
class Log
{
   public:
      Log() {}
      virtual ~Log() {}
};
#endif
}  // namespace driver_sample

#endif  // __INCLUDE_LOG_HPP__
