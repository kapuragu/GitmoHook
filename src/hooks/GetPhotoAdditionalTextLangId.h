#pragma once

enum PHOTO_TYPE : unsigned char {
    photo_type_h = 0,
    photo_type_v = 1,
    photo_type_v2 = 2,//??? ASSUMPTION
};
enum PHOTO_TEXT : unsigned char {
    target_type_rescue = 1,
    target_type_recovery = 2,
    target_type_exclusion = 3,
    target_type_destruction = 4,
    target_type_tracking = 5,
    target_type_tailing = 6,
};

struct PhotoInfo {
    unsigned short MissionCode;
    unsigned char PhotoId;
    PHOTO_TYPE PhotoType;
    unsigned long long TargetTypeLangId;
};

void AddPhotoAdditionalText(unsigned short missionCode, unsigned char photoId, unsigned char photoType, const char* targetTypeLangIdStr);