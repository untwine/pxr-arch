#include <archTest/util.h>

int main(int argc, char** argv)
{
    archTest::CrashArgParse(argc, argv);
    archTest::Crash(archTest::CrashMode::Error);

    return 0;
}
