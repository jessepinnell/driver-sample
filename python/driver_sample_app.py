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
# pylint: disable=too-many-ancestors
# pylint: disable=no-self-use

import sys
sys.path.append("../lib")
sys.path.append("lib")
sys.path.append("../python")
sys.path.append("python")

import wx
import wx.grid
import py_driver_sample

ID_ABOUT = 2323
ID_QUIT = 2324
ID_RESET = 2325
ID_READ = 2326
ID_WRITE = 2327

NUM_ROWS = 16
NUM_COLUMNS = 8

def get_cell_by_address(address):
    """ get the cell address from a memory address """
    return (address // NUM_COLUMNS, address % NUM_COLUMNS)

def get_address_by_cell(row, column):
    """ get the memory address from a cell address """
    return (row * NUM_COLUMNS) + column

class Simulator(object):
    """ loopback simulator for when driver fails to talk to hardware """
    def __init__(self):
        self.data = [0] * (NUM_ROWS * NUM_COLUMNS)

    def write(self, address, value):
        """ shove a value into the fake memory """
        print "setting 0x{0:x} to 0x{1:x}".format(address, value)
        self.data[address] = value

    def read(self, address):
        """ increment a value in the fake memory and return it """
        self.data[address] = min(self.data[address] + 1, 0xff)
        return self.data[address]

    def reset(self):
        """ pretend to reset """
        print "reset"

class RegisterGrid(wx.grid.Grid):
    """ Grid matching Table 4.1 in http://ww1.microchip.com/downloads/en/DeviceDoc/20005282B.pdf """
    def __init__(self, parent):
        super(RegisterGrid, self).__init__(parent, size=(300, 400))
        self.CreateGrid(NUM_ROWS, NUM_COLUMNS)

        grid_font = wx.Font(9, wx.FONTFAMILY_DEFAULT, wx.FONTSTYLE_NORMAL, wx.FONTWEIGHT_NORMAL, False, "Terminus")
        self.SetDefaultCellFont(grid_font)
        self.SetDefaultRowSize(19)
        self.SetDefaultColSize(30)
        self.SetFont(grid_font)
        self.SetRowLabelSize(30)

        self.skip_cell = None

        for row in xrange(NUM_ROWS):
            self.SetRowLabelValue(row, "{0:04b}".format(row))

        for col in xrange(NUM_COLUMNS):
            self.SetColLabelValue(col, "{0:04b}".format(col))


    def set_value(self, address, value):
        """ update a value in the grid """
        cell = get_cell_by_address(address)
        self.SetCellValue(cell[0], cell[1], "{0:02x}".format(value))


class DriverSampleApp(wx.Frame):
    """
    Application for illustrating accessing SWIG bindings
    """

    def __init__(self, parent, title):
        """
        Create the frame, lay out controls, and set up event handlers
        """
        wx.Frame.__init__(self, parent, wx.ID_ANY, title, size=(400, 480), style=(wx.CLOSE_BOX))

        main_sizer = wx.BoxSizer(wx.VERTICAL)

        reset_button = wx.Button(self, ID_RESET, "Reset", size=wx.Size(120, 20))
        main_sizer.Add(reset_button, 0, wx.CENTER, 0)

        register_sizer = wx.BoxSizer(wx.VERTICAL)
        self.register_grid = RegisterGrid(self)
        register_sizer.Add(self.register_grid, 0, wx.CENTER, 0)
        main_sizer.Add(register_sizer, 0, wx.CENTER, 0)


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
        self.register_grid.Bind(wx.grid.EVT_GRID_CELL_CHANGE, self.on_grid_changed)
        self.register_grid.Bind(wx.grid.EVT_GRID_SELECT_CELL, self.on_grid_cell_selected)
        self.register_grid.Bind(wx.grid.EVT_GRID_LABEL_LEFT_CLICK, self.on_grid_edited)

        self.skip_cell = None

        self.timer = wx.Timer(self)
        self.Bind(wx.EVT_TIMER, self.on_poll_timer)

        try:
            self.log = py_driver_sample.Log()
            self.driver = py_driver_sample.Driver()
            self.timer.Start(5000)
        except Exception as ex:
            dialog = wx.MessageDialog(self, "Failed to initialize:\n" + str(ex)\
                + "\n\n*** Using simulator ***", "Error", wx.ICON_EXCLAMATION)
            dialog.ShowModal()
            dialog.Destroy()
            self.driver = Simulator()
            self.timer.Start(2500)

        self.on_poll_timer(None)
        self.Show(True)

    def on_grid_changed(self, event):
        """ handle a value in the grid being changed """
        try:
            value = int(self.register_grid.GetCellValue(event.Row, event.Col).encode("ascii", "ignore"), 16)
            if value > 0xff:
                raise Exception("Value must be in [0x0..0xff]")
            address = get_address_by_cell(event.Row, event.Col)

            self.driver.write(address, value)
        except Exception as ex:
            dialog = wx.MessageDialog(self, "Invalid entry: " + str(ex), "Error", wx.ICON_EXCLAMATION)
            dialog.ShowModal()
            dialog.Destroy()
        self.skip_cell = None
        event.Skip()

    def on_grid_cell_selected(self, event):
        """ a cell has been selected so skip updating it """
        self.skip_cell = (event.Row, event.Col)

    def on_grid_edited(self, event):
        """ ignore handling changes until enter is pressed """
        event.Skip()

    def on_poll_timer(self, event):
        """ read all the register values and update them in the grid """
        for i in range(0, NUM_ROWS * NUM_COLUMNS):
            cell = get_cell_by_address(i)
            if cell != self.skip_cell:
                self.register_grid.set_value(i, self.driver.read(i))
            else:
                print "editing " + str(cell) + ", skipping update"

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
