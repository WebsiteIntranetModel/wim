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

    Create your overrides within the /components/theme folder and keep them there. You will risk breaking the update path when you modify files outside of that folder. 

3.  **Writing SCSS**

    Use the CSS selectors as provided by the WIM theme to override CSS in a healthy way. **Never use !important overrides**, since this will risk regression in future updates of the distribution.


## Steps ##

1.  Navigate into the Drupal root
    ```
    $ cd public_html/
    ```
2.  Navigate into the WIM sub theme folder
    ```
    $ cd profiles/wim/themes/wim/
    ```

3.  Install necessary node packages defined in package.json
    ```
    $ npm install
    ```

4.  Initialize the project.

    *This will download the latest bootstrap-sass files and move it from the node_modules folder to the theme it's SCSS base.*

    ```
    $ gulp init
    ```

5.  Fire the default gulp task and start theming!
    ```
    $ gulp
    ```

6.  (Optional) View the styleguide on `http://localhost:5000`
