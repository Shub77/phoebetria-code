#ifndef PROFILES_H
#define PROFILES_H

#include <QString>

class FanControllerProfile
{
public:
    FanControllerProfile();

    const QString& name(void) const;

    bool load();
    bool save(const char* filename);

private:

};

#endif // PROFILES_H
