local this = {}

if rawget(_G, "GntnHook") then
    return _G.GntnHook
end

local ok, GitmoHookOrErr = pcall(require, "GitmoHook")
if not ok then
    error("GntnHook: failed to require GitmoHook: " .. tostring(GitmoHookOrErr))
end

local VFW = GitmoHookOrErr

_G.VFW = VFW
_G.GitmoHook = VFW
_G.GntnHook = this

this.GitmoHook = VFW

return this