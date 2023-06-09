local battleDialogOverlayBuilder = globals.require("classes.interface.dialog.battleDialogOverlayBuilder")

local _M = {}

local function message(...)
  local text = { ... }

  local dialog = battleDialogOverlayBuilder:new(true)

  for _, v in ipairs(text) do
    dialog:addText(v)
  end
end

_M.mods = {
  { "numPad+", "Increase Game Speed", function()
    message("Increasing Game Speed")

    local timeScale = globals.timer.timeScale
    globals.timer.timeScale = timeScale + 0.5

    timeScale = globals.transition.timeScale
    globals.transition.timeScale = timeScale + 0.5

    timeScale = globals.display.timeScale
    globals.display.timeScale = timeScale + 0.5
  end
  },
  { "numPad-", "Decrease Game Speed", function()
    message("Decreasing Game Speed")

    local timeScale = globals.timer.timeScale
    globals.timer.timeScale = timeScale - 0.5

    timeScale = globals.transition.timeScale
    globals.transition.timeScale = timeScale - 0.5

    timeScale = globals.display.timeScale
    globals.display.timeScale = timeScale - 0.5
  end
  },
  { "numPad*", "Reset Game Speed", function()
    message("Resetting Game Speed")

    globals.timer.timeScale = 1
    globals.display.timeScale = 1
    globals.transition.timeScale = 1
  end
  },
  { "numPad/", "Toggle Noclip", function()
    message("NoClip: " .. (globals.debugSettings.noClipMode and "[off]" or "[on]"))
    globals.debugSettings.noClipMode = not globals.debugSettings.noClipMode
  end
  },
  { "numPad1", "Catch All Coromon", function()
    message("CatchEmAll: " .. (globals.debugSettings.alwaysCatchSuccessfully and "[off]" or "[on]"))
    globals.debugSettings.alwaysCatchSuccessfully = not globals.debugSettings.alwaysCatchSuccessfully
  end
  },
  { "numPad2", "Skip Wild Battles", function()
    message("Skip Battles: " .. (globals.debugSettings.skipWildBattles and "[off]" or "[on]"))
    globals.debugSettings.skipWildBattles = not globals.debugSettings.skipWildBattles
  end
  },
  { "numPad3", "Max Out Coromon", function()
    -- Sometimes noclip can cause issues with interactive dialogues
    globals.debugSettings.noClipMode = false

    local dialog = battleDialogOverlayBuilder:new(false)
    local squad = globals.playerMonsters:getSquad()

    for _, v in ipairs(squad) do
      dialog:addText("Would you like to max out " .. v:getDisplayName() .. "?")
      dialog:addQuestion({ { yes = "Yes" }, { no = "No" } }, function(answer)
        if answer == "yes" then
          dialog:addText("Maxing out " .. v:getDisplayName())
          v:tryIncreaseLevel(100)
          v:setPotential(21)
          v:setHealthToMaxHealth()
          v:setEnergyToMaxOverchargedEnergy()
        end
      end)
    end
  end
  },
  { "numPad4", "Add 5000 Gold", function()
    message("Adding Gold")
    globals.playerCurrency:addGold(5000)
  end
  },
}

hooks.add("classes.interface.screens.titleScreen", function(module)
  detour(module, "new", function(original, ...)
    local ret = original(...)

    globals.eventManager:listen("key", function(event)
      local key = event.keyName

      if event.phase ~= "down" then
        return
      end

      for _, v in ipairs(_M.mods) do
        if key == v[1] then
          v[3]()
        end
      end

      return false
    end)

    return ret
  end)
end)

return _M
