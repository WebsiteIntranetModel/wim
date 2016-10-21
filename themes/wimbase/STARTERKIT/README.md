## WIM theming guidelines

We set up the current theme architecture to provide maximal flexibility and sustainability for future theme developers. We use Bootstrap to provide an accessible and robust front-end, but we only compile the Bootstrap css that we actually need in the wimbase theme. You can choose to make use of our default WIM theme or pick one of the  approaches that fits your needs. Read the guidelines carefully to make sure you gain all the advantages of future distribution updates.

### Prerequisites
- Basic knowledge of using the command line
- Node and Node Package Manager installed
- Have an understanding of what taskrunners do
- Have an understanding of the atomic design pattern

### Theme architecture
1. **core**
- Contains the default Drupal templates
2. **bootstrap**
- Contains the default Bootstrap templates
- Implements Bootstrap logic
3. **wimbase**
- Overrides both core and Bootstrap templates
- Contains WIM theme logic
- Contains necessary Bootstrap styles
- Contains a sub theme STARTERKIT
4. **wim (enabled and default, but optional)**
- Contains WIM default styles
- Contains gulp taskrunner
- Contains styleguide

### IMPORTANT! Make sure WIM stays updatable
It is important to not change the scss files (except for some) provided in the wim sub theme itself. These files can be updated in future releases and start conflicting with the work you’ve done.

### Approach 1: Change some color and font settings
Use the wim default theme and make some small changes before recompiling the styles. Follow these steps to make wim align with your brand design:

1. Navigate to the root of the wim theme
```sh
$ cd profiles/wim/themes/wim/
```
2. Install packages
```sh
$ npm install
```
5. Run gulp watch task that will compile your css
```sh
$ gulp
```
7. Change variables in _theme.scss
```sh
$ open components/_theme.scss
```

**Notes:** New WIM releases will come with a newly compiled CSS file. You need to recompile the CSS with gulp after merging the latest code, so your custom variables are implemented again.

### Approach 2: Create a custom theme with the WIM starterkit
Use the starterkit provided in the wimbase theme to create a highly customized sub theme.

1. Navigate to the root of the wim theme
```sh
$ cd profiles/wim/themes/wimbase/
```
2. Copy and rename the starterkit to the themes folder of your installation
```sh
$ cp -R STARTERKIT ../../../../sites/all/themes/YOURTHEME
```
3. navigate to your theme and rename .info file
```sh
$ cd ../../../../sites/all/themes/YOURTHEME
$ mv STARTERKIT.info.txt YOURTHEME.info
```
4. Rename value in template.php
```sh
open template.php (change the STARTERKIT value)
```
5. Enable YOURTHEME and set as default
```
Go to /admin/appearance/ and set YOURTHEME as your default theme
```

**Notes:** We advice to follow the atomic design principles while expanding your scss base. For more information visit: http://bradfrost.com/blog/post/atomic-web-design/
