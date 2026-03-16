--GzUi.lua
local this={}

this.MISSIONS={
    [20010]=true,
    [20020]=true,
    [20030]=true,
    [20040]=true,
    [20050]=true,
    [20060]=true,
    [20070]=true,
}

function this.IsEnableForMission(missionCode)
    missionCode = missionCode or vars.missionCode
    if this.MISSIONS[missionCode]~=nil then
        return this.MISSIONS[missionCode]
    end
    return false
end

this.registerIvars={
    "gzHkEnableGzUi",
}

this.gzHkEnableGzUi={
	save=IvarProc.CATEGORY_EXTERNAL,
    settings={"OFF","ON","GNTN","FORCE"},
    default=1,
    settingNames="gzHkEnableGzUiSettingNames",
}

function this.IsEnableGzUi()
    if Ivars.gzHkEnableGzUi:Is(1) then
        return true
    end
    return false
end

function this.IsGntnGzUi()
    if Ivars.gzHkEnableGzUi:Is(2) then
        return true
    end
    return false
end

function this.IsForceGzUi()
    if Ivars.gzHkEnableGzUi:Is(3) then
        return true
    end
    return false
end

this.registerMenus={
    "gzHkUiMenu"
}

this.gzHkUiMenu={
	parentRefs={
        "GntnIvars.GuantanamoSafeSpaceMenu",
    },
    options={
        "Ivars.gzHkEnableGzUi",
    }
}

this.langStrings={
	eng={
		gzHkUiMenu="UI hook menu",
		gzHkEnableGzUi="Enable UI GZ textures",
        gzHkEnableGzUiSettingNames={"Off","On (GZ missions)", "On (Guantanamo)","On"},
	},
	help={
		eng={
			gzHkUiMenu="Change options related to Guantanamo and Ground Zeroes UI hooks.",
			gzHkEnableGzUi="Enable GZ textures in the UI, including the logo on the loading screen, game over screen, and equip background.",
		},
	},
}

function this.SetEnableGzUi(isEnable)
    if not GitmoHook then
        InfCore.Log("GzUi: GitmoHook not found")
        return
    end
    if not GitmoHook.SetEnableGzUi then
        InfCore.Log("GzUi: SetEnableGzUi not found")
        return
    end
    GitmoHook.SetEnableGzUi(isEnable)
end

function this.PreMissionLoad(missionCode,prevMissionCode)
    local isEnableForGz = this.IsEnableGzUi()
    local isGzMission = this.IsEnableForMission(missionCode)
    local IsGntnUi = this.IsGntnGzUi()
    local isGntn = GntnMain.IsGuantanamoMission(missionCode)
    local isForce = this.IsForceGzUi()
    InfCore.Log("GzUi: for GZ: "..tostring(isEnableForGz)..", is GZ:"..tostring(isGzMission))
    InfCore.Log("GzUi: is for gntn: "..tostring(IsGntnUi)..", is gntn:"..tostring(isGntn))
    InfCore.Log("GzUi: is Force: "..tostring(isForce))

    local isEnable = (isEnableForGz and isGzMission) or (IsGntnUi and isGntn) or isForce
    this.SetEnableGzUi(isEnable)
end

return this