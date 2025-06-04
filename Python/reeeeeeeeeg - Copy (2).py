import winreg
def read_lsa_key(key_name: str) -> bytes:
    #"""Reads a binary registry value from HKLM\\SYSTEM\\CurrentControlSet\\Control\\Lsa\\<key_name>"""
    path = r"SYSTEM\CurrentControlSet\Control\Lsa"
    with winreg.ConnectRegistry(None, winreg.HKEY_LOCAL_MACHINE) as hklm:
        with winreg.OpenKey(hklm, path) as key:
            value, val_type = winreg.QueryValueEx(key, key_name)
            if val_type != winreg.REG_BINARY:
                raise ValueError(f"{key_name} is not a binary registry value")
            return value
def reconstruct_boot_key(jd: bytes, skew1: bytes, gbg: bytes, data: bytes) -> bytes:
    if not all(len(x) == 16 for x in (jd, skew1, gbg, data)):
        raise ValueError("All inputs must be 16 bytes long")
    concat = jd + skew1 + gbg + data
    permutation = [0x8,0x5,0x4,0x2,0xb,0x9,0xd,0x3,0x0,0x6,0x1,0xc,0xe,0xa,0xf,0x7]
    boot_key = bytearray(16)
    for i in range(16):
        boot_key[i] = concat[permutation[i]]
    return bytes(boot_key)
reconstruct_boot_key(bytes.fromhex("FAADD40DAB8F"),bytes.fromhex("F4927BDC929107B09A0E49F4ECC49C0D"),bytes.fromhex("8DB9D663D9D8B79221"),bytes.fromhex("CE88177868E89A76A561B4A3A920AA33"))
if __name__ == "__main__":
    try:
        jd = read_lsa_key("JD")
        skew1 = read_lsa_key("Skew1")
        gbg = read_lsa_key("GBG")
        data = read_lsa_key("Data")
        boot_key = reconstruct_boot_key(jd, skew1, gbg, data)
        print("Boot Key:", boot_key.hex())
    except Exception as e:
        print("Error:", e)
