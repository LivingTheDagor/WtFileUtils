import time

from WtFileUtils.new_blk.DataBlock import DataBlock, DBTypes
from WtFileUtils.blk.BlkParser import BlkParser
from io import StringIO
from WtFileUtils.BitStream import BitStream

if __name__ == '__main__':
    with open(r"testFiles\cmngetbin.blk", "rb") as f:
        data = f.read()
    t1 = time.time()
    x = DataBlock('base')
    y = x.DeserializeFromBin(BitStream(data))
    out = y.serializeToDict()
    # out = StringIO()
    t2 = time.time()

    y1 = BlkParser(data).to_dict()
    t3 = time.time()

    print(t2-t1, t3-t2)
    # print()

    # print(out.getvalue())
'''    x = DataBlock('base')
    x.AddParam("Hello", DBTypes.TYPE_STRING, "s1")
    x.AddParam("Hello1", DBTypes.TYPE_STRING, "s2")
    x.AddParam("Hello2", DBTypes.TYPE_STRING, "s3")
    blk2 = DataBlock('base51521', nm=x.nm)
    blk2.AddParam([55, 56, 57], DBTypes.TYPE_IPOINT3, "s4")
    x.AddBlockUnsafe(blk2)
    print(x.serializeToDict())
    out = StringIO()
    x.serializeToText(out, 0)
    print(out.getvalue())'''
