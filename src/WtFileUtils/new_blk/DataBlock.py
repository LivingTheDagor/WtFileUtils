from __future__ import annotations

import zstandard as zstd

from .NameMap import NameMap
from ..BitStream import BitStream
from .BinaryTypes import FileType
from enum import Enum
from io import IOBase
import struct

"""
This file and alot of the module isnt very pythonic
this is due to it trying to represent how its done by gaijin and the cpp module so they have similarites
"""

class DBTypes(Enum):
    TYPE_NONE = 0
    TYPE_STRING = 1     # < Text string.
    TYPE_INT = 2        # < Integer.
    TYPE_REAL = 3       # <  # real (float).
    TYPE_POINT2 = 4     # < Point2.
    TYPE_POINT3 = 5     # < Point3.
    TYPE_POINT4 = 6     # < Point4.
    TYPE_IPOINT2 = 7    # < IPoint2.
    TYPE_IPOINT3 = 8    # < IPoint3.
    TYPE_BOOL = 9       # < Boolean.
    TYPE_E3DCOLOR = 10  # < E3DCOLOR.
    TYPE_MATRIX = 11    # < TMatrix.
    TYPE_LONG = 12


class Param:
    def __init__(self, value, t: DBTypes, NameIndex: int):
        self.value = value
        self.type_: DBTypes = t
        self.NameIndex = NameIndex


class _DataBlockInfo:
    def __init__(self, bs):
        self.nameId = bs.ReadUleb()
        self.paramCount = bs.ReadUleb()
        self.blocksCount = bs.ReadUleb()
        self.firstBlock = 0
        if self.blocksCount:
            self.firstBlock = bs.ReadUleb()



class DataBlock:
    TYPE_CHECK = True

    def __init__(self, name: str | int, nm: NameMap | None = None):
        """
        Constructor for DataBlock
        @param name: an int or string, if str, sets datablock name, if int, looks up in nm for that index
        @param nm:
        """
        self.nm = nm or NameMap()
        self.params: list[Param] = []
        self.blocks: list[DataBlock] = []
        self.param_count = 0
        self.block_count = 0
        self.__first_block = 0 # only used during bin deserialization
        # no shared params cause thats only use to manage allocations, its not used for data
        if isinstance(name, str):
            self.__name = self.nm.AddName(name) # stores the name index
        else:
            self.__name = name

    def getName(self) -> str:
        return self.nm.GetNameFromIndex(self.__name)

    def getNameIndex(self) -> int:
        return self.__name

    def AddParam(self, value, type_: DBTypes, name: int | str) -> int:
        if isinstance(name, str):
            name = self.nm.AddName(name)
        self.params.append(Param(value, type_, name))
        self.param_count += 1
        return self.param_count - 1

    def GetParam(self, index: int) -> Param:
        return self.params[index]

    def GetParamFromName(self, name: str | int) -> Param:
        name_id = name if isinstance(name, int) else self.nm.GetIndexFromName(name)
        for i in  self.params:
            if i.NameIndex == name_id:
                return i

    def GetParamListFromName(self, name: str | int) -> list[Param]:
        name_id = name if isinstance(name, int) else self.nm.GetIndexFromName(name)
        payload: list[Param] = []
        for i in self.params:
            if i.NameIndex == name_id:
                payload.append(i)
        return payload


    def AddBlock(self, block: DataBlock):
        """
        Adds a DataBlock to this DataBlock, syncs the name map
        """
        self.blocks.append(block)
        self.block_count += 1
        block.SyncNameMap(self.nm)


    def AddBlockUnsafe(self, block: DataBlock) -> int:
        """
        Adds a DataBlock to this DataBlock, DOESNT syncs the name map
        """
        self.blocks.append(block)
        self.block_count += 1
        return self.block_count-1

    def SyncNameMap(self, nm: NameMap):
        if nm == self.nm:
            for p in self.blocks:
                p.SyncNameMap(self.nm)
        else:
            self.__name = nm.AddName(self.nm.GetNameFromIndex(self.__name))
            for p in self.params:
                p.NameIndex = nm.AddName(self.nm.GetNameFromIndex(p.NameIndex))
            for p in self.blocks:
                p.SyncNameMap(nm)
            self.nm = nm

    def serializeToDict(self, base = True):
        payload = {}
        for i in self.params:
            name = self.nm.GetNameFromIndex(i.NameIndex)
            if name in payload:
                if isinstance(payload[name], list):
                    payload[name].append(i.value)
                else:
                    payload[name] = [payload[name], i.value]
            else:
                payload[name] = i.value

        for i in self.blocks:
            name = i.getName()
            data = i.serializeToDict(False)

            if name in payload:
                if name in payload:
                    if isinstance(payload[name], list):
                        payload[name].append(data)
                    else:
                        payload[name] = [payload[name], data]
            else:
                payload[name] = data
        return payload

    @staticmethod
    def __writeIndent(output: IOBase, level: int):
        if level <= 0:
            return
        while level >= 8:
            output.write("        ")
            level -= 8
        while level >= 2:
            output.write("  ")
            level -= 2
        while level >= 1:
            output.write(" ")
            level -= 1


    def serializeToText(self, output: IOBase, level):
        for param in self.params:
            self.__writeIndent(output, level*2)
            output.write(self.nm.GetNameFromIndex(param.NameIndex))
            match param.type_:
                case DBTypes.TYPE_STRING:
                    output.write(f":t=\"{param.value}\"")
                case DBTypes.TYPE_BOOL:
                    output.write(f":b={'yes' if param.value else 'no'}")
                case DBTypes.TYPE_INT:
                    output.write(f":i={param.value}")
                case DBTypes.TYPE_REAL:
                    output.write(f":r={param.value}")
                case DBTypes.TYPE_POINT2:
                    p1, p2 = param.value
                    output.write(f":p2={p1}, {p2}")
                case DBTypes.TYPE_POINT3:
                    p1, p2, p3 = param.value
                    output.write(f":p3={p1}, {p2}, {p3}")
                case DBTypes.TYPE_POINT4:
                    p1, p2, p3, p4 = param.value
                    output.write(f":p4={p1}, {p2}, {p3}, {p4}")
                case DBTypes.TYPE_IPOINT2:
                    p1, p2 = param.value
                    output.write(f":ip2={p1}, {p2}")
                case DBTypes.TYPE_IPOINT3:
                    p1, p2, p3 = param.value
                    output.write(f":ip3={p1}, {p2}, {p3}")
                case DBTypes.TYPE_E3DCOLOR:
                    r, g, b, a = param.value
                    output.write(f":c={r}, {g}, {b}, {a}")
                case DBTypes.TYPE_MATRIX:
                    (p1, p2, p3), (p4, p5, p6),( p7, p8, p9), (p10, p11, p12) = param.value
                    output.write(f":m=[[{p1}, {p2}, {p3}] [{p4}, {p5}, {p6}] [{p7}, {p8}, {p9}] [{p10}, {p11}, {p12}]]")
                case DBTypes.TYPE_LONG:
                    output.write(f":l={param.value}")


            output.write("\n")
        if self.params and self.blocks:
            self.__writeIndent(output, level*2)
            output.write("\n")
        for block in self.blocks:
            self.__writeIndent(output, level*2)
            output.write(block.getName())
            output.write("{\n")
            block.serializeToText(output, level+1)
            output.write("}\n")
            if block == self.blocks[-1]:
                output.write("\n")


    def __Deserialize(self, bs: BitStream, nm: NameMap):
        num_of_blocks = bs.ReadUleb("num_of_blocks")
        num_of_params = bs.ReadUleb("num_of_params")
        params_data_size = bs.ReadUleb("params_data_size")
        param_data = BitStream(bs.ReadBytes(params_data_size))
        start_of_params = bs.GetReadOffset()
        bs.SetReadOffset(start_of_params+num_of_params*8*8)
        blocks: list[DataBlock] = [None] * num_of_blocks
        for i in range(num_of_blocks):
            x = _DataBlockInfo(bs)
            blk = DataBlock(x.nameId, nm)
            blocks[i] = blk
            blk.block_count = x.blocksCount
            blk.param_count = x.paramCount
            blk.__first_block = x.firstBlock
        bs.SetReadOffset(start_of_params)
        for blk in blocks:
            for i in range(blk.param_count):
                blk.__construct_param(bs, param_data)
            for i in range(blk.block_count):
                blk.AddBlockUnsafe(blocks[i+blk.__first_block])
        return blocks[0]


    def __construct_param(self, bs: BitStream, param_data: BitStream) -> Param:
        name_id = bs.ReadBitsInt(24, "param_name_id")
        type_ = bs.ReadU8("param_type")
        payload = None
        match DBTypes(type_):
            case DBTypes.TYPE_STRING:
                data = bs.ReadU32("data")
                in_nm = data >> 31 == 1
                data &= 0x7FFFFFFF
                if in_nm:
                    payload = self.nm.GetNameFromIndex(name_id)
                else:
                    param_data.SetReadOffset(data*8)
                    payload = param_data.ReadCStr().decode("utf-8")
            case DBTypes.TYPE_BOOL:
                data = bs.ReadU32("data")
                payload = data is True # checks truthiness (>0)
            case DBTypes.TYPE_INT:
                payload = bs.ReadU32("data")
            case DBTypes.TYPE_REAL:
                data = bs.ReadFloat("data")
            case DBTypes.TYPE_POINT2:
                data = bs.ReadU32("data")
                param_data.SetReadOffset(data * 8)
                payload = [param_data.ReadFloat(), param_data.ReadFloat()]
            case DBTypes.TYPE_POINT3:
                data = bs.ReadU32("data")
                param_data.SetReadOffset(data * 8)
                payload = [param_data.ReadFloat(), param_data.ReadFloat(), param_data.ReadFloat()]
            case DBTypes.TYPE_POINT4:
                data = bs.ReadU32("data")
                param_data.SetReadOffset(data * 8)
                payload = [param_data.ReadFloat(), param_data.ReadFloat(), param_data.ReadFloat(), param_data.ReadFloat()]
            case DBTypes.TYPE_IPOINT2:
                data = bs.ReadU32("data")
                param_data.SetReadOffset(data * 8)
                payload = [param_data.ReadU32(), param_data.ReadU32()]
            case DBTypes.TYPE_IPOINT3:
                data = bs.ReadU32("data")
                param_data.SetReadOffset(data * 8)
                payload = [param_data.ReadU32(), param_data.ReadU32(), param_data.ReadU32()]
            case DBTypes.TYPE_E3DCOLOR:
                r, g, b, a = bs.ReadU8("data"), bs.ReadU8("data"), bs.ReadU8("data"), bs.ReadU8("data")
                payload = [r, g, b, a]
            case DBTypes.TYPE_MATRIX:
                data = bs.ReadU32("data")
                param_data.SetReadOffset(data * 8)
                payload = [[param_data.ReadFloat(), param_data.ReadFloat(), param_data.ReadFloat()],
                           [param_data.ReadFloat(), param_data.ReadFloat(), param_data.ReadFloat()],
                           [param_data.ReadFloat(), param_data.ReadFloat(), param_data.ReadFloat()],
                           [param_data.ReadFloat(), param_data.ReadFloat(), param_data.ReadFloat()]]
            case DBTypes.TYPE_LONG:
                data = bs.ReadU32("data")
                param_data.SetReadOffset(data * 8)
                payload = param_data.ReadU64()
            case _:
                data = bs.ReadU32("FAILED_DATA") # couldnt determine type, but still read to prevent error
        if payload:
            self.AddParam(payload, DBTypes(type_), name_id)

    def DeserializeFromBin(self, bs: BitStream, nm: NameMap = None, zstd_dict=None):
        f_type = FileType(bs.ReadU8())
        to_use: BitStream = bs
        if f_type == FileType.BBF:
            return # invalid type currently
        if f_type.is_zstd():
            if f_type.needs_dict() and zstd_dict is None:
                raise Exception("zstd dict is required")
            x = zstd.ZstdDecompressor(zstd_dict).stream_reader(to_use) # bitstream doesnt implement RawIO, but it has the needed .read() func
            to_use = BitStream(x.read())
            x.close()
        names_in_name_map = bs.ReadUleb("names_in_name_map")
        if f_type.is_slim():
            if nm is None:
                raise Exception("nm is required for blk of type slim")
        else:
            name_map_size = bs.ReadUleb("name_map_size")
            start_index = bs.GetReadOffset()
            end_index = start_index + name_map_size *8
            nm = NameMap() # python let me PREALLOC
            for x in range(names_in_name_map):
                nm.AddName(bs.ReadCStr("name").decode("utf-8"))
            assert bs.GetReadOffset() == end_index
        return self.__Deserialize(to_use, nm)
