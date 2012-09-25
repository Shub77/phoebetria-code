#ifndef BUILDDETAILS_H
#define BUILDDETAILS_H

#include <QString>

#define PHOEBETRIA_VERSION  1
#define PHOEBETRIA_MAJOR_REVISION   2
#define PHOEBETRIA_MINOR_REVISION   0
#define PHOEBETRIA_STATUS_STR       "(PRE-RELEASE!)"

class BuildDetails
{
public:
    BuildDetails();

    static QString versionStr(void);
    static QString buildDateTimeStr(void);

};

#endif // BUILDDETAILS_H
