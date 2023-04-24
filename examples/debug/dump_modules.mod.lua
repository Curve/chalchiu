return {
    name        = 'Dump Tables',
    description = 'Gather Information on Game Modules (Debugging)',
    script      = function()
        local inspect = req("inspect")
        local original = require

        require = function(module)
            local ret = original(module)
            print(module, inspect(ret))
            return ret
        end
    end
}
