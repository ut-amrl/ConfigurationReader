# Configuration Reader
Configuration Reader for use in AMRL projects.

For specification details, see the [Wiki](https://github.com/umass-amrl/ConfigurationReader/wiki)

## TODO
- [ ] Provide an implementation for extracting config values from the vector in which they're stored
- [ ] Add support for `Eigen::Vector2f`
- [ ] Fix the auto-update to work for multiple updates (use `poll()` instead of `read()`)
- [ ] Implement bounds
    - [ ] Update macros to use bounds
- [ ] Implement the reader.cpp file as a proper class with constructor
    - [ ] Add the ability to read in configuration variables from multiple files
- [ ] Fix the auto-update so that it works on multiple files
- [ ] Add checks to ensure that negative numbers aren't cast to `unsigned int` using a lua function