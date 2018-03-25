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
# False positive
# pylint: disable=wrong-import-position

import sys
sys.path.append("../lib")

import wx
# TODO(jessepinnell) sort out the import issue
# import driver_sample


ID_ABOUT = 2323
ID_QUIT = 2324
ID_DO_SOMETHING = 2325

class DriverSampleApp(wx.Frame):
    """
    Application for illustrating accessing SWIG bindings
    """

    def __init__(self, parent, title):
        """
        Create the frame, lay out controls, and set up event handlers
        """
        wx.Frame.__init__(self, parent, wx.ID_ANY, title, size=(200, 120), style=(wx.CLOSE_BOX))

        main_sizer = wx.BoxSizer(wx.VERTICAL)

        self.do_something_button = wx.Button(self, ID_DO_SOMETHING,\
            "Do Something", size=wx.Size(170, 42))
        main_sizer.Add(self.do_something_button, 0, wx.CENTER, 0)

        self.SetSizer(main_sizer)
        self.Center()

        file_menu = wx.Menu()
        file_menu.Append(ID_ABOUT, "&About", "Information")
        file_menu.AppendSeparator()
        file_menu.Append(ID_QUIT, "&Q&uit", "Quit the program")

        menu_bar = wx.MenuBar()
        menu_bar.Append(file_menu, "&File")

        self.SetMenuBar(menu_bar)

        wx.EVT_BUTTON(self, ID_DO_SOMETHING, self.on_do_something)
        wx.EVT_MENU(self, ID_ABOUT, self.on_about)
        wx.EVT_MENU(self, ID_QUIT, self.on_quit)

        self.Show(True)

        # driver = driver_sample
        # print dir(driver)

    def on_do_something(self, event):
        """
        Does something
        """
        pass

    def on_about(self, event):
        """
        Open a simple about dialog
        """
        dialog = wx.MessageDialog(self, "About", "Driver app test for python bindings", wx.OK)
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
