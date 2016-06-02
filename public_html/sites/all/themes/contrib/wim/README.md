## Introduction ##


## Do's & Don'ts ##
1. **Sustainability**

Do not change files in this theme!

2. **Personalization**

Create a new sub theme dependent on the WIM theme with the provided STARTERKIT to make sure you get default theming for new features in future updates.

3. ** Writing CSS **

Use the CSS selectors as provided by the WIM theme to override CSS in a healthy way. *Never use !important overrides*, since this will risk unforseen regression in future updates.


## Steps ##

1.  Enable the jquery_update module, since Bootstrap depends on a higher version than is included in Drupal core.
    ```
    $ drush en jquery_update
    ```

2.  Enable the WIM subtheme
    ```
    $ drush en wim
    ```

3.  Navigate into the WIM subtheme folder
    ```
    $ cd public_html/sites/all/themes/contrib/wim/
    ```

4.  Install necessary node packages defined in package.json
    ```
    $ npm install
    ```

5.  Start the gulp init task.

    __This will download the latest bootstrap-sass files and move it from node_modules folder to your theme's sass base.__

    ```
    $ gulp init
    ```

6.  Start the default gulp task and start theming!
    ```
    $ gulp
    ```

7.  View the accessibility styleguide locally on `http://localhost:5000`
