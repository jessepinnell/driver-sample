#!/usr/bin/env python
# XXX wx doesn't work well with python3 yet
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
# Disable for event handlers
# pylint: disable=unused-argument
# TODO(jessepinnell)
# pylint: disable=broad-except

# pylint: disable=bad-option-value
# pylint: disable=import-error
# pylint: disable=too-many-public-methods

import sys
sys.path.append("../lib")
sys.path.append("lib")
sys.path.append("../python")
sys.path.append("python")

import wx
import py_driver_sample

ID_ABOUT = 2323
ID_QUIT = 2324
ID_RESET = 2325
ID_READ = 2326
ID_WRITE = 2327

class DriverSampleApp(wx.Frame):
    """
    Application for illustrating accessing SWIG bindings
    """

    def __init__(self, parent, title):
        """
        Create the frame, lay out controls, and set up event handlers
        """
        wx.Frame.__init__(self, parent, wx.ID_ANY, title, size=(200, 220), style=(wx.CLOSE_BOX))

        main_sizer = wx.BoxSizer(wx.VERTICAL)

        reset_button = wx.Button(self, ID_RESET, "Reset", size=wx.Size(170, 42))
        main_sizer.Add(reset_button, 0, wx.CENTER, 0)

        read_sizer = wx.BoxSizer(wx.VERTICAL)
        read_button = wx.Button(self, ID_READ, "Read", size=wx.Size(170, 42))
        read_sizer.Add(read_button, 0, wx.CENTER, 0)
        main_sizer.Add(read_sizer, 0, wx.CENTER, 0)

        write_sizer = wx.BoxSizer(wx.VERTICAL)
        write_button = wx.Button(self, ID_WRITE, "Write", size=wx.Size(170, 42))
        write_sizer.Add(write_button, 0, wx.CENTER, 0)
        main_sizer.Add(write_sizer, 0, wx.CENTER, 0)


        self.SetSizer(main_sizer)
        self.Center()

        file_menu = wx.Menu()
        file_menu.Append(ID_ABOUT, "&About", "Information")
        file_menu.AppendSeparator()
        file_menu.Append(ID_QUIT, "&Q&uit", "Quit the program")

        menu_bar = wx.MenuBar()
        menu_bar.Append(file_menu, "&File")

        self.SetMenuBar(menu_bar)

        wx.EVT_BUTTON(self, ID_RESET, self.on_reset)
        wx.EVT_MENU(self, ID_ABOUT, self.on_about)
        wx.EVT_MENU(self, ID_QUIT, self.on_quit)

        self.Show(True)

        try:
            self.log = py_driver_sample.Log()
            self.driver = py_driver_sample.Driver()
        except Exception as ex:
            dialog = wx.MessageDialog(self, "Failed to initialize:\n" + str(ex), "Error", wx.ICON_EXCLAMATION)
            dialog.ShowModal()
            dialog.Destroy()
            self.Close()


    def on_reset(self, event):
        """
        Trigger a reset
        """
        try:
            self.driver.reset()
        except Exception as ex:
            dialog = wx.MessageDialog(self, "Failed to reset:\n" + str(ex), "Error", wx.ICON_EXCLAMATION)
            dialog.ShowModal()
            dialog.Destroy()
            self.Close()

    def on_about(self, event):
        """
        Open a simple about dialog
        """
        dialog = wx.MessageDialog(self, "Driver app test for python bindings", "About", wx.OK)
        dialog.ShowModal()
        dialog.Destroy()

    def on_quit(self, event):
        """
        Quit the application
        """
        self.Close()

if __name__ == "__main__":
    # pylint: disable=invalid-name
    application = wx.App(False)
    main_frame = DriverSampleApp(None, "Driver Sample App")
    application.MainLoop()
