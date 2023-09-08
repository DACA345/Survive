#include <gtest/gtest.h>
#include <util/resolution.h>

TEST(UtilTest, ResolutionGenerationTest)
{
    QList<QSize> expectedResolutions;
    expectedResolutions
        << QSize(640, 480)
        << QSize(800, 600)
        << QSize(1024, 768)
        << QSize(1280, 720)
        << QSize(1280, 800)
        << QSize(1366, 768)
        << QSize(1440, 900)
        << QSize(1600, 900)
        << QSize(1680, 1050)
        << QSize(1920, 1080)
        ;

    QList<QSize> resolutions = Resolution::generateResolutions(1920, 1080);
    
    ASSERT_EQ(expectedResolutions, resolutions);

    expectedResolutions.clear();
    resolutions.clear();

    expectedResolutions
        << QSize(640, 480)
        << QSize(800, 600)
        ;

    resolutions = Resolution::generateResolutions(1280, 720);

    ASSERT_EQ(expectedResolutions, resolutions);
}