# Configuration Reader
Configuration Reader for use in AMRL projects.

For specification details, see the [Wiki](https://github.com/umass-amrl/ConfigurationReader/wiki)

## TODO
- [x] Provide an implementation for extracting config values from the vector in which they're stored
- [x] Add support for `Eigen::Vector2f`
- [x] Fix the auto-update to work for multiple updates
    - [x] Fix bug in which the update appears to occur twice for some reason
- [x] Have the file watch run in a background thread instead of the main thread
- [ ] Implement bounds
    - [ ] Update macros to use bounds
- [x] Add the ability to read in configuration variables from multiple files
- [x] Fix the auto-update so that it works on multiple files
- [ ] Add checks to ensure that negative numbers aren't cast to `unsigned int` using a lua function
