# hiiiiiiiiiiive.py utf8
# Hive extractor
import struct
import datetime
import sys
import json
import os
def filetime_to_dt(filetime_bytes):
    # filetime_bytes: 8 bytes, little-endian FILETIME from the registry
    filetime_int = struct.unpack('<Q', filetime_bytes)[0]  # unpack unsigned long long (64-bit)
    # FILETIME counts 100-nanosecond intervals since 1601-01-01
    # Convert to seconds:
    seconds_since_1601 = filetime_int / 10_000_000
    # Windows epoch starts at 1601-01-01, Unix epoch 1970-01-01
    epoch_as_filetime = 11644473600  # seconds difference between 1601 and 1970
    unix_timestamp = seconds_since_1601 - epoch_as_filetime
    # Convert to datetime
    return datetime.datetime.utcfromtimestamp(unix_timestamp)
flnm=input("File name: ")
fl=open(flnm,'rb')
dat=fl.read()
if dat[0:4]!=bytes("regf","utf8"):
    print("Invalid Signature")
    sys.exit(1)
os.mkdir(f"{flnm}.reg")
os.chdir(f"{flnm}.reg")
os.mkdir("Heders")