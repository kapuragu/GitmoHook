#pragma once

struct ChangeLocationMenuParameter {
    unsigned short LocationId;
    unsigned short MissionId;
    unsigned char paddingA[0x4];
    unsigned long long FreeMissionName;
    unsigned char Flags;
    unsigned char MbStageBaseId;
    unsigned char paddingB[0x6];
};

struct MotherBaseMissionCommonData {
    unsigned char paddingA[0x111];
    unsigned char ChangeLocationMenuParamCount;
    unsigned char paddingB[0x6];
    ChangeLocationMenuParameter ChangeLocationMenuParams[12];
    unsigned char paddingC[0x88];
};

ChangeLocationMenuParameter* __thiscall GetChangeLocationMenuParameterByLocationIdHook(MotherBaseMissionCommonData* This, unsigned short locationCode);

void AddLocationIdToChangeLocationMenu(unsigned short locationId);