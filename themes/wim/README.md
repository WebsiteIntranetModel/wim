# Website Intranet Model #
Check [wimgemeenten.nl](http://www.wimgemeenten.nl) for more information. Please note that this website is in Dutch.

Useful links for developers:
- [Github](https://github.com/WebsiteIntranetModel/wim)
- [Travis CI](https://travis-ci.org/WebsiteIntranetModel/wim/builds)
- [Docker Hub](https://hub.docker.com/r/goalgorilla/wim/builds/)

## Introduction ##


## Do's & Don'ts ##
1.  **Sustainability**

    Do not change files in this theme!

2.  **Personalization**

    Create a new sub theme dependent on the WIM theme with the provided STARTERKIT to make sure you get default theming for new features in future updates.

3.  **Writing CSS**

    Use the CSS selectors as provided by the WIM theme to override CSS in a healthy way. **Never use !important overrides**, since this will risk unforseen regression in future updates of the distribution.


## Steps ##

1.  Navigate into the Drupal root
    ```
    $ cd public_html/
    ```

2.  Make sure you've got the jquery_update module enabled, because Bootstrap depends on a higher version than is included in Drupal core.
    ```
    $ drush en jquery_update
    ```

3.  Make sure you've got the magic module enabled, because we want to use the theme settings as provided by wim.info and make use of the CSS and JS aggregation that this module offers.
    ```
    $ drush en magic
    ```

4.  Enable the WIM sub theme (enabling the bootstrap theme is not necessary)
    ```
    $ drush en wim
    ```

5.  Navigate into the WIM sub theme folder
    ```
    $ cd sites/all/themes/contrib/wim/
    ```

6.  Install necessary node packages defined in package.json
    ```
    $ npm install
    ```

7.  Initialize the project.

    *This will download the latest bootstrap-sass files and move it from the node_modules folder to your theme's sass base (./css/src/bootstrap).*

    ```
    $ gulp init
    ```

8.  Fire the default gulp task and start theming!
    ```
    $ gulp
    ```

9.  (Optional) View the accessibility styleguide locally on `http://localhost:5000`
