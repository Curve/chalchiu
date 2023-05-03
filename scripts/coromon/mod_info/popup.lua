local AbstractSelectPopup = globals.require("classes.interface.overlays.AbstractSelectPopup")

local _M = {}

local always = function()
    return true
end

local function escape(text)
    return text:gsub("<", "("):gsub(">", ")")
end

function _M:new()
    local mods  = chalchiu:mods()
    local title = "Loaded Mods"
    local items = {}

    for i = 1, #mods do
        table.insert(items, {
            shouldBeShown = always,
            --
            name = mods[i]:name(),
            author = mods[i]:author(),
            version = mods[i]:version(),
            description = mods[i]:description(),
        })
    end

    local header_params = AbstractSelectPopup:newParams(title, items,
        function(container, item)
            local name_label = (globals.textHelper:new(container, "outline_8", item.name))
            globals.magnet:centerLeft(name_label, 2, 0, container)

            local author_label = (globals.textHelper:new(container, "outline_8", "(by " .. item.author .. ")"))
            globals.magnet:centerRight(author_label, 2, 0, container)

            local version_label = (globals.textHelper:new(container, "outline_8", item.version))
            globals.magnet:center(version_label, 2, 0, container)
        end
    )

    header_params:setGetDescriptionFunction(function(item, _width)
        return globals.textHelper:newPrepared("outline_8", {
            text = escape(item.description),
            width = _width,
        })
    end)

    header_params:setConvertToCategoryFunction(function()
    end)

    header_params:setConfirmButton(
        function(_button)
            local icon = globals.imageHelper:new(_button, "images/interface/icons/otherIcons/confirm.png")
            globals.magnet:center(icon, 0, -1, _button)
        end,
        function(_, closePopup)
            closePopup()
        end
    )

    header_params:setCancellable()
    AbstractSelectPopup:new(header_params):open(function()
    end)
end

return _M
