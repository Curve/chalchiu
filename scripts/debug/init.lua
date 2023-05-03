local inspect = require("inspect")

detour(globals, "require", function(original, module)
	local ret = original(module)
	print(module, inspect(ret))
	return ret
end)

return {
	description = 'Gather Information on Game Modules (Debugging)',
	name        = 'Dump Tables',
	author      = 'Curve',
	version     = 'v1.0',
}
