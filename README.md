# Parameter Tool Box
[![Linux Build](https://github.com/hansen-audio/param-tool-box/actions/workflows/cmake_linux.yml/badge.svg)](https://github.com/hansen-audio/param-tool-box/actions/workflows/cmake_linux.yml) [![macOS Build](https://github.com/hansen-audio/param-tool-box/actions/workflows/cmake_macos.yml/badge.svg)](https://github.com/hansen-audio/param-tool-box/actions/workflows/cmake_macos.yml) [![Windows Build](https://github.com/hansen-audio/param-tool-box/actions/workflows/cmake_windows.yml/badge.svg)](https://github.com/hansen-audio/param-tool-box/actions/workflows/cmake_windows.yml)

A tool box for parameter and value processing.

## Building the project

Execute the following commands on cli.

```
git clone /path/to/param-tool-box.git
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug ../param-tool-box
cmake --build .
```

> Linux: ```cmake -DCMAKE_BUILD_TYPE=[Debug|Release] ../param-tool-box```
> macOS:```cmake -GXcode ../param-tool-box```
> Windows 10: ```cmake -G"Visual Studio 16 2019" -A x64 ..\param-tool-box```

## Using the tools and examples

### Ramp processor

The ```ptb::ramp_processor``` can take a list of automation curve points and interpolate between them. This allows sample accurate automation curve processing. By providing it a lambda function to retrieve the automation curve points, the class is not bound to any list implementation.

In order to use it with ```Vst::IParamValueQueue```, do as follows:

```
Steinberg::tresult MyPlugin::process(Vst::ProcessData & data)
{
    auto* queue = findParamValueQueue(kParamGainId, data.inputParameterChanges);
    ptb::ramp_processor gainProc(
        [queue](int index, int& offset, float& value) -> bool {
            if (index < queue->getPointCount())
            {
                if (queue->getPoint(index, offset, value) != kResultOk)
                    return false;
            }
            return true;
        },
        gainValue);

    if (!data.outputs || !data.inputs)
        return kResultOk;

    for (...)
    {
        (*output)++ = (*input)++ * gainProc.getValue();

        gainProc.advance();
    }
}
```

## License

Copyright 2021 Hansen Audio

Licensed under the MIT: https://mit-license.org/
