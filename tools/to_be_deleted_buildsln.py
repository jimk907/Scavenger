import globals
import os, sys, subprocess

args = globals.ProcessArguments(sys.argv)
CONFIG = globals.GetArgumentValue(args, "config", "debug")

print("Building config: " + CONFIG)
print("\n")
ret = 0

if globals.IsWindows():

    # This commented lines were in the sample source but will not work
    # with my VS2022 installation. Instead of using VS_BUILD_PATH in
    # the subprocess.call(), using "msbuild.exe" in its place works well

    #VS_BUILD_PATH = os.environ["VS_BUILD_PATH"][8:-1]
    #VS_BUILD_PATH = "C:\\\\" + VS_BUILD_PATH

    ret = subprocess.call(["cmd.exe", "/c", "msbuild.exe", "{}.sln".format(globals.ENGINE_NAME), "/property:Configuration={}".format(CONFIG)])

if globals.IsLinux():
    ret = subprocess.call(["make", "config={}".format(CONFIG)])

if globals.IsMac():
    ret = subprocess.call(["make", "config={}".format(CONFIG)])

sys.exit(ret)

