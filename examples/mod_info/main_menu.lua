local popup = require("popup")

local once = false

hooks.add("classes.interface.screens.titleScreen", function(module)
    detour(module, "new", function(original, ...)
        local ret = original(...)

        if not once then
            popup:new()
            once = true
        end

        return ret
    end)
end)
