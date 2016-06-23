# Website Intranet Model #
Check [wimgemeenten.nl](http://www.wimgemeenten.nl) for more information. Please note that this website is in Dutch.

Useful links for developers:
- [Github](https://github.com/WebsiteIntranetModel/wim)
- [Travis CI](https://travis-ci.org/WebsiteIntranetModel/wim/builds)
- [Docker Hub](https://hub.docker.com/r/goalgorilla/wim/builds/)

## Introduction ##


## Guidelines ##
1.  **Sustainability**

    Do not change the files in this theme! Updates can no longer be applied if files have changed and development of new features probably comes with new theming.

2.  **Personalization**

    Create a new sub theme based on bootstrap with the provided STARTERKIT to make sure you get default theming for new features in future updates.

3.  **Writing CSS**

    Use the CSS selectors as provided by the WIM theme to override CSS in a healthy way. **Never use !important overrides**, since this will risk regression in future updates of the distribution.


## Steps ##

1.  Install necessary node packages defined in package.json
    ```
    $ npm install
    ```

2.  Initialize the project.

    ```
    $ gulp init
    ```

3.  Fire the default gulp task and start theming!
    ```
    $ gulp
    ```

4.  (Optional) View the accessibility styleguide locally on `http://localhost:5000`
