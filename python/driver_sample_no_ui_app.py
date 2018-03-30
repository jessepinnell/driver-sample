#!/usr/bin/env python
# MIT License
#
# Copyright (c) 2018 Jesse Pinnell
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

""" Simple script to illustrate SWIG bindings """
# pylint: disable=import-error

import sys
sys.path.append("../lib")
sys.path.append("lib")
sys.path.append("../python")
sys.path.append("python")

import py_driver_sample

if __name__ == "__main__":
    LOG = py_driver_sample.Log()
    def run():
        """ Run in subroutine so Log is destroyed after driver """
        driver = py_driver_sample.Driver()
        driver.reset()
        driver.read(0x12)
        driver.readReceiveBuffer(0)
        driver.readReceiveBuffer(1)
        driver.readReceiveBuffer(2)
        driver.readReceiveBuffer(3)

        driver.write(0xde, 0xbe)

        driver.writeTransmitBuffer(3, 0xef)

        driver.requestToSend(False, False, True)
        driver.requestToSend(True, False, True)
        driver.requestToSend(False, True, True)

        status = driver.readStatus()

        receive_status = driver.readReceiveStatus()

    run()
