# MS8607 Driver for use with Linux and C/C++

## Origin

This is used with permission and the MIT license from

https://github.com/TEConnectivity/MS8607_Generic_C_Driver

## Changes

I modified the original source a bit to be used in C and C++ applications. Otherwise, it is as is from the original.

## TODO

There is still a need to implement the wait_no_stop i2c function. For now, that does not impact general use
of the device on a Raspberry pi

## Testing

This makes use of Google Test to provide a short test implementation. If you would like to build this with
testing enabled

```
# mkdir build
# cd build
# cmake -DBUILD_TESTS=ON ..
```

To run the tests, simply

```
cd build
./ms8607-test
```

## Building

This uses cmake to build, and can be built as a static or shared library on any modern linux distribution.

```
# mkdir build
# cd build
# cmake ..
# make
# sudo make install
```

Or, if you want a static library

```
# mkdir build
# cd build
# cmake -DPROJECT_BUILD_SHARED=OFF ..
# make
# sudo make install
```

## Usage

You can use the test object as an example, but it's a mix of C and C++.

Straight C11
```
#include <ms8607.h>

int main(int argc, char *argv[])
{
    float t;
    float p;
    float h;
    float rh;

    ms8607_init("/dev/i2c-1");
    ms8607_status status = ms8607_read_temperature_pressure_humidity(&t, &p, &h);
    if (status == ms8607_status_ok) {
        ms8607_get_compensated_humidity(t, h, &rh);
        t = (t * 1.8) + 32;
    }
}
```
