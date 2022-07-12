import sys, subprocess
import globals

ret = 0


if globals.IsWindows():
    ret = subprocess.call(["cmd.exe", "/c", "premake5\\premake5", "vs2022"])


# linux unsupported
if globals.IsLinux():
    ret = subprocess.call(["premake5/premake5.linux", "gmake2"])

# mac unsupported
if globals.IsMac():
    ret = subprocess.call(["premake5/premake5", "gmake2"])
    if ret == 0:
        ret = subprocess.call(["premake5/premake5", "xcode4"])

sys.exit(ret)
