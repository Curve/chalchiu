return {
	name   		= 'Pimp My Coromon!',
	description = 'Buffs all your coromon to max level!',
	
	target 		= 'classes.modules.playerMonsters',
	hook   		= function (table)
		local original = table.onLoadSaveslotData

		table.onLoadSaveslotData = function(self, data)
			local rtn = original(self, data)
			
			local squad = self:getSquad()
			
			for i = 1, #squad do
				squad[i]:tryIncreaseLevel(100)
				print("Pimped", squad[i]:getDisplayName())
			end
			
			return rtn
		end
	end
}
