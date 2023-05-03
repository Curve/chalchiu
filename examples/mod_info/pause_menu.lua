local popup = require("popup")

local abstractOuterTopBarButtonBuilder = globals.require(
  "classes.interface.topBarObjects.abstractOuterTopBarButtonBuilder")

local function makeButton()
  local parentGroup, modsButton = abstractOuterTopBarButtonBuilder:new(globals.UIContainerStyle.blue)
  local icon = (globals.imageHelper:new(modsButton, "images/interface/icons/itemIcons/HOLD_EXTRA_XP.png"))

  globals.magnet:center(icon, 0, 0, modsButton)

  globals.inputHelper:addTouchable(modsButton, globals.inputHelper:onReleaseWithinBounds(
    function(event)
      globals.soundHelper:playSound("menuSelect")
      globals.transition.press(event.target,
        function()
          popup:new()
        end
      )
    end)
  )

  return parentGroup
end

local once = false

hooks.add("classes.interface.screens.pauseMenuScreen", function(table)
  detour(table, "new", function(original, ...)
    once = false

    local restore = detour(globals.pauseMenuScreenBuilder, "new", function(original, ...)
      local rtn = original(...)

      if not once then
        rtn:addTopBarObject(makeButton())
        once = true
      end

      return rtn
    end)

    local ret = original(...)
    restore()

    return ret
  end)
end)
