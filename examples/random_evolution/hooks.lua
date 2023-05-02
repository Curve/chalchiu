hooks.add("classes.interface.settingObjects.CustomDifficultyScreen.RandomizeEvolutionsModeEnumButton",
  function(module)
    detour(module, "shouldBeRendered", function()
      return true
    end)
  end)
