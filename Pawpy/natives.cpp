/*==============================================================================


	Pawpy - Python Utility for Pawn

		Copyright (C) 2016 Barnaby "Southclaw" Keene

		This program is free software: you can redistribute it and/or modify it
		under the terms of the GNU General Public License as published by the
		Free Software Foundation, either version 3 of the License, or (at your
		option) any later version.

		This program is distributed in the hope that it will be useful, but
		WITHOUT ANY WARRANTY; without even the implied warranty of
		MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
		See the GNU General Public License for more details.

		You should have received a copy of the GNU General Public License along
		with this program.  If not, see <http://www.gnu.org/licenses/>.

	Note:
		This file contains the actual definitions of the functions exported to
		the SA:MP server. When those exported functions are called from a Pawn
		script (AMX instance actually) this is the code that will run. I've done
		what most logical programmers would do and separated my actual
		implementation code into another module so all these functions do is
		process the input and call the implementation functions with the
		sanitised and processed input.

		Talking about input, parameters come in from Pawn as a simple pointer
		which must be "decoded" into the original intended parameters and their
		types (as much as Pawn has "types"...) which isn't much different to
		extracting parameters from **argv if you're familiar with that.

		Luckily, the SDK has provided some helper functions to extract the data
		from parameters. It's important the "native" declarations in Pawn match
		the parameter extraction perfectly, if you specify too little parameters
		in a "native" declaration, the code here will extract garbage data and
		potentially crash horribly. If you try to send too many parameters, it
		should be freed fine and not cause issue but is very pointless!


==============================================================================*/


#include <string>

using std::string;

#include "natives.hpp"
#include "pawpy.hpp"


cell Native::RunPython(AMX* amx, cell* params)
{
	debug("Native::RunPython called");

	string
		module,
		function,
		callback;

	module = amx_GetCppString(amx, params[1]);
	function = amx_GetCppString(amx, params[2]);
	callback = "";

	Pawpy::run_python(module, function, callback);

	return 0;
}

cell Native::RunPythonThreaded(AMX* amx, cell* params)
{
	debug("Native::RunPythonThreaded called");

	string
		module,
		function,
		callback;

	module = amx_GetCppString(amx, params[1]);
	function = amx_GetCppString(amx, params[2]);
	callback = amx_GetCppString(amx, params[3]);
	debug("Native::RunPythonThreaded optained parameters");

	Pawpy::run_python_threaded(module, function, callback);
	debug("Native::RunPythonThreaded finished");

	return 0;
}
