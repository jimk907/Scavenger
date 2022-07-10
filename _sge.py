
# based on code by 'progrematic' Hippo engine

import sys, os
import subprocess

TOOLS_DIR =	"tools"


def RunCommand(cmd):
    ret = 0
    script = "{}/{}/{}.py".format(os.getcwd(), TOOLS_DIR, cmd)
    if os.path.exists(script):
        ret = subprocess.call(["python3", script])
    else:
        print("Invalid command: ", cmd)
        ret = -1
    
    return ret

ret = 0
for i in range(1, len(sys.argv)):
	cmd = sys.argv[i]

	print("\n----------------------------------")
	print("Executing: ", cmd)
	ret = RunCommand(cmd)
	print("----------------------------------\n")
	if ret != 0:
		break
