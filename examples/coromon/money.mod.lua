return {
	name        = 'Infinite Money',
	description = 'Gives you unlimited money',
	target      = 'classes.modules.playerCurrency',
	hook        = function(table)
		local original = table.onLoadSaveslotData

		table.onLoadSaveslotData = function(self, data)
			data.gold = 2 ^ 52
			return original(self, data)
		end
	end
}
