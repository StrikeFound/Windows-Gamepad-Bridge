#pragma once
// Build identity and immutable family boundary for this separate product.
// This header is also directly testable outside the kernel.
#define IC_PRODUCT_SERVICE L"WindowsGamepadBridge"
#define IC_PRODUCT_XUSB_HID_PARENT_VALUE L"WindowsGamepadBridgeXusbHidParent"
#define IC_PRODUCT_XUSB_PARENT_VALUE L"WindowsGamepadBridgeXusbParent"
#define IC_PRODUCT_CONTROL_HWID L"ROOT\\WindowsGamepadBridgeControl"
#define IC_PRODUCT_NT_DEVICE L"\\Device\\WindowsGamepadBridge"
#define IC_PRODUCT_DOS_DEVICE L"\\DosDevices\\WindowsGamepadBridge"
#define IC_PRODUCT_TRIAL_SLOT 2u
#define IC_PRODUCT_TRIAL_KEY L"\\Registry\\Machine\\HARDWARE\\WindowsGamepadBridgeTrial"
#ifndef IC_PRODUCT_INPUT_MASK
#define IC_PRODUCT_INPUT_MASK 0u
#endif
#ifndef IC_PRODUCT_CONTROLLER_MASK
#define IC_PRODUCT_CONTROLLER_MASK 15u
#endif
#ifndef IC_PRODUCT_HAS_KEYBOARD_MOUSE
#define IC_PRODUCT_HAS_KEYBOARD_MOUSE 0
#endif
#ifndef IC_PRODUCT_HAS_CONTROLLERS
#define IC_PRODUCT_HAS_CONTROLLERS 1
#endif
#define IC_PRODUCT_STREAM_MASK (IC_PRODUCT_INPUT_MASK | (IC_PRODUCT_CONTROLLER_MASK << 2))
#define IC_PRODUCT_HID_GUID {0x059053c3,0x46be,0x51ab,{0xb9,0x49,0x74,0xe3,0xe5,0x34,0xba,0xc6}}
#define IC_PRODUCT_XUSB_GUID {0x04ad07e4,0xfa15,0x511e,{0xa6,0x24,0x9d,0x0d,0xeb,0x15,0x57,0x93}}
#define IC_PRODUCT_XINPUTHID_GUID {0x6079ce0f,0xd2cf,0x54e1,{0xb6,0x3f,0x08,0xa4,0x08,0xf8,0x1a,0xb5}}
#define IC_PRODUCT_GIP_GUID {0x1f5a79d8,0x14a0,0x5813,{0xb8,0x3d,0xb7,0x57,0x68,0x1f,0xbc,0x87}}
#define IC_PRODUCT_XUSB_MIRROR_GUID {0x852f2ed0,0xe82c,0x5419,{0xbf,0xca,0x4e,0xde,0x38,0x06,0x37,0x0c}}
static __inline int IcProductTypeAllowed(unsigned int type) {
    return type>=1 && type<=6 && (IC_PRODUCT_STREAM_MASK & (1u<<(type-1)))!=0;
}
static __inline int IcProductCreateMasksAllowed(unsigned int input,unsigned int controllers) {
    return !(input & ~IC_PRODUCT_INPUT_MASK) && !(controllers & ~IC_PRODUCT_CONTROLLER_MASK);
}
// Function numbers are the pointer-free protocol's CTL_CODE function field.
// Unknown/common functions keep the normal control dispatch validation.
static __inline int IcProductIoctlFunctionAllowed(unsigned int fn) {
    switch(fn) {
    case 0xA01:case 0xA03:case 0xA07:
        return (IC_PRODUCT_INPUT_MASK & 1u)!=0;
    case 0xA02:case 0xA04:case 0xA08:
        return (IC_PRODUCT_INPUT_MASK & 2u)!=0;
    case 0xA09:case 0xA0A:case 0xA0B:case 0xA0C:case 0xA0D:
        return (IC_PRODUCT_CONTROLLER_MASK & 1u)!=0;
    case 0xA10:case 0xA11:case 0xA12:case 0xA13:case 0xA14:case 0xA15:
        return (IC_PRODUCT_CONTROLLER_MASK & 2u)!=0;
    case 0xA17:case 0xA18:case 0xA19:case 0xA1A:case 0xA1B:
        return (IC_PRODUCT_CONTROLLER_MASK & 4u)!=0;
    case 0xA20:case 0xA21:case 0xA22:case 0xA23:case 0xA24:case 0xA25:
    case 0xA29:case 0xA2A:case 0xA2B:
        return (IC_PRODUCT_CONTROLLER_MASK & 8u)!=0;
    case 0xA30:case 0xA31:case 0xA32:case 0xA33:
        return IC_PRODUCT_HAS_CONTROLLERS;
    default:return 1;
    }
}

