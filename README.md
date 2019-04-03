# game-of-life

### Documentation
You can find the **polish** language documantation in the `docs` directory, written in [LATEX](https://www.latex-project.org/) syntax. To compile, run `make -B docs`.


## Warning!
This project contains [submodules](https://git-scm.com/book/en/v2/Git-Tools-Submodules).

To fully clone with submodules, use:
* **ssh:** `git clone --recurse-submodules git@github.com:k-piekarczyk/game-of-life.git`
* **https:** `git clone --recurse-submodules https://github.com/k-piekarczyk/game-of-life.git`

### Tools:
* [make](https://www.gnu.org/software/make/)
* [CMake](https://cmake.org/)
* [CLion](https://www.jetbrains.com/clion/)

### Libraries:
 _imported as submodules_
* [gifenc](https://github.com/lecram/gifenc)
* [lodepng](https://github.com/lvandeve/lodepng)

## Important macros
Some parts of the code use macros as predefined configuration. Here's a list of them:
* _MOORES_NEIGHBORHOOD_  `src/game_functions.c`
    * if defined, the simulation will use [Moore's neighborhood](https://en.wikipedia.org/wiki/Moore_neighborhood), otherwise [Von Neumann's neighborhood](https://en.wikipedia.org/wiki/Von_Neumann_neighborhood) will be used.
* _TIMEBAR_HEIGHT_  `src/game_space_display.c`
    * __integer__, sets the height of the generated gifs timebar height
* _LIVE_DIVIDEND_ and _LIVE_DIVIDER_  `src/game_space_management.c`
    * sets the probability of a cell being a __LIVE__ cell when randomly populating the game space [`P = dividend / divider`]

## Usage

    ./gol <config_file> 
    
Folder `out/` **must** exist for the program to work properly.

## Config file formatting
Configuration is based on `key>value` pairs.

Example configuration files can be found in the `demo-conf` directory.

### Dimensions
- `width` - width of the game space
- `height` - height of the game space

or 

- `png` - route to a PNG file from which the game space dimensions will be derived

### Cell state
- `alive` - can be used multiple times, every row contains `x,y` of an alive cell

or

- `png` - if used, the fully black pixels of the png will be used as live cells

### Output type
- `freq` - frequency of png simulation snapshots eg: freq>50 means that a snapshot will be taken every 50 iterations

or

- `fps` - how many iterations per second should be in an output gif

### Other
- `max_iter` - number of iterations the simulation has to make