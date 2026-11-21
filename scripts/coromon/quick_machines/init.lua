-- Quick Machines! For Coromon 1.5.4. Toggle shortening of steps needed for the Potentiflator, the Traitformator, the Soft Resetinator, and swapping spinners.

local EFFECT_PATH = "classes.world.effects.world."
local BASE = EFFECT_PATH .. "abstractUpgradeMonsterAfterPlayerStepsWorldEffect"

local DEFAULT = 0 -- "Use game default"
local QUICK = 1   -- "1 step", also the number of steps to wait

local OPTIONS = {
  { value = DEFAULT, label = "Use game default" },
  { value = QUICK, label = "1 step" },
}

local MACHINES = {
  { name = "Potentiflator",    key = "potentiflator",   module = EFFECT_PATH .. "potentialRerollWorldEffect" },
  { name = "Traitformator",    key = "traitformator",   module = EFFECT_PATH .. "traitRerollWorldEffect" },
  { name = "Soft Resetinator", key = "softResetinator", module = EFFECT_PATH .. "potentialStatSoftResetWorldEffect" },
  { name = "Spinner Swap",     key = "spinnerSwap",     module = EFFECT_PATH .. "spinnerSwapWorldEffect" },
}

local definitions = {}
local starting

for i, machine in ipairs(MACHINES) do
  definitions[i] = {
    key = machine.key,
    label = machine.name .. " steps",
    type = "choice",
    default = DEFAULT,
    options = OPTIONS,
    description = ("How many steps the %s needs to finish."):format(machine.name),
  }

  -- Runs when the game creates a machine's job: identifies the machine
  hooks.add(machine.module, function(class)
    detour(class, "new", function(original, ...)
      starting = machine
      return original(...)
    end)
  end)
end

local config = settings.define(definitions)

-- Runs a moment later, when the machine's code passes the number of steps to the shared code
hooks.add(BASE, function(base)
  detour(base, "new", function(original, self, options, monster, amount, ...)
	-- Clear immediately post-usage so calls cannot reuse stale state
    if starting and config[starting.key] == QUICK then
      amount = QUICK
    end
    starting = nil
    return original(self, options, monster, amount, ...)
  end)
end)

return {
  name        = "Quick Machines",
  description = "Set the Potentiflator, Traitformator, Soft Resetinator and Spinner Swap waits to 1 step! Off by default.",
  author      = "ERSXS",
  version     = "v1.0",
}
