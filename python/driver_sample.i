%module driver_sample

%include "std_except.i"
%include "exception.i"
%include "std_string.i"

%{
#include "../src/MCP25625Driver.hpp"
%}

%exception
{ 
   try
   {
      $action
   }
   catch (std::exception &e)
   {
      SWIG_exception(SWIG_RuntimeError, e.what());
   }
   catch (...)
   {
      SWIG_exception(SWIG_RuntimeError, "unexpected exception");
   }
}

%include "../src/MCP25625Driver.hpp"
