from WtFileUtils.vromfs.VROMFs import VROMFs
from backup.WtFileUtils.FileSystem.File import VROMFs_File

x = VROMFs("D:\SteamLibrary\steamapps\common\War Thunder\gaces.vromfs.bin")
d = x.get_directory()
#file: VROMFs_File = d["lang"]["units.csv"]
file: VROMFs_File = d["darg"]["darg_libaray.nut"]
file.get_data()
