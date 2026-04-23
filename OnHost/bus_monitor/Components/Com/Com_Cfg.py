from Components.Com.Com_Types import ComIpduType, ComConfigType

BUFFER_SIZE = 256

ComIpdu = [
    ComIpduType(0x000, 1, 0, 0),
    ComIpduType(0x001, 1, 1, 1),
    ComIpduType(0x002, 7, 2, 2),
    ComIpduType(0x003, 7, 9, 9),
    ComIpduType(0x004, 1, 16, 16),
    ComIpduType(0x005, 1, 17, 17),
    ComIpduType(0x006, 1, 18, 18),
    ComIpduType(0x007, 1, 19, 19),
    ComIpduType(0x008, 1, 20, 20),
    ComIpduType(0x009, 2, 21, 21),
    ComIpduType(0x00A, 2, 23, 23),
    ComIpduType(0x00B, 2, 25, 25),
    ComIpduType(0x00C, 1, 27, 27),
]

Com_PCConfig = ComConfigType(
    PduList=ComIpdu,
    NumIpdus=len(ComIpdu),
    TxBufferSize=BUFFER_SIZE,
    RxBufferSize=BUFFER_SIZE,
)
