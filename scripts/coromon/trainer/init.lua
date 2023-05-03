local hooks = require("hooks")

local function getDescription()
	local rtn = "A Coromon Trainer\n"

	for _, v in ipairs(hooks.mods) do
		rtn = rtn .. string.format("[%s] %s\n", v[1], v[2])
	end

	return rtn
end

return {
	name        = 'Coromon Trainer',
	description = getDescription(),
	author      = 'Curve',
	version     = 'v1.0',
}
