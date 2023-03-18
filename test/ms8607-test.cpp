#include <gtest/gtest.h>
#include <ctime>
#include <string>
#include <sstream>
#include <math.h>
#include <iostream>

#include "ms8607.h"
#include "i2c.h"

namespace
{
    TEST(DeviceTests, Connected)
    {
        ms8607_init("/dev/i2c-1");
        EXPECT_EQ(ms8607_is_connected(), true) << "Unable to verify device is present";
        ms8607_close();
    }

    TEST(DeviceTests, ReadValues)
    {
        float t;
        float p;
        float h;

        int fd = ms8607_init("/dev/i2c-1");
        EXPECT_GT(fd, 2) << "FD: " << fd;
        ms8607_status status = ms8607_read_temperature_pressure_humidity(&t, &p, &h);
        ASSERT_EQ(status, ms8607_status_ok) << "Status is: " << status;
        std::cout << "Temp: " << t << ", Pressure: " << p << ", Humidity: " << h << std::endl;
    }

    TEST(DeviceTests, CompensatedHumidity)
    {
        float t;
        float p;
        float h;
        float rh;

        int fd = ms8607_init("/dev/i2c-1");
        EXPECT_GT(fd, 2) << "FD: " << fd;
        ms8607_status status = ms8607_read_temperature_pressure_humidity(&t, &p, &h);
        ASSERT_EQ(status, ms8607_status_ok) << "Status is: " << status;
        status = ms8607_get_compensated_humidity(t, h, &rh);
        ASSERT_EQ(status, ms8607_status_ok) << "Status is: " << status;
        std::cout << "Compensated Humidity: " << rh << std::endl;
    }
}
