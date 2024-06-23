from os import makedirs
from pathlib import PureWindowsPath
from shutil import rmtree
from subprocess import check_output
import platform

Import("env")

env.Append(CCFLAGS=["-isystem", "lib/matiec/lib/C"])

env.Append(CFLAGS=["-Wmissing-prototypes",
                   "-Wstrict-prototypes"])

env.Append(CFLAGS=["-DRAM_SIZE=131072"])

def skip_from_build(node):
    n = node.get_path()
    if platform.system() == "Windows":
        n = PureWindowsPath(n).as_posix()

    # filter UIP src and matiec dir
    skip = ["lib/matiec"]
    if any(s in n for s in skip):
        return None

    # filter freertos src
    keep = ["port","heap_4"]
    if "freertos/portable" in n:
        if not any(s in n for s in keep):
            return None

    # otherwise allow all
    return node

def fix_pous_c(node):
    # don't compile POUS.c
    if "POUS" not in node.name:
        return node

env.AddBuildMiddleware(skip_from_build, "*")
env.AddBuildMiddleware(fix_pous_c)


print("Compiling plc_prog.st ...")

gdir = f"src/generated"
rmtree(gdir, ignore_errors=True)
makedirs(gdir, exist_ok=True)

path = env.PioPlatform().get_package_dir("tool-matiec")
# cmd = "iec2c.exe" if platform.system() == "Windows" else "iec2c"

check_output(f"{path}/bin/iec2c.exe -I lib/matiec/lib -T src/generated plc_prog.st", shell=True)
