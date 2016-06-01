#!/bin/sh

# Install script for in the docker container.
cd /var/www/html/;

# Check if first argument given is "reinstall". In that case we drop the database,
# remove settings.php and the files folder.
if [ ${1:-"install"} = "reinstall" ]; then
  drush sql-drop -y;
  rm -f sites/default/settings.php;
  rm -f sites/default/settings.local.php;
  rm -rf sites/default/files;
  echo "Database dropped, files folder and settings.php removed"
fi

# Check if second argument is "include", defaults to "exclude". We copy the
# local settings.php to the place where it will be included in settings.php.
if [ ${2:-"exclude"} = "include" ]; then
  cp sites/default/example.settings.local.php sites/default/settings.local.php
  echo "Moved settings.local.php so it can be included in the settings.php file."
fi

# Install the site using the WIM installation profile.
drush -y site-install wim --db-url=mysql://root:root@db:3306/wim --account-pass=admin install_configure_form.site_name='WIM';
echo "Drupal installation complete"

# Set ownership for data folder.
chown -R www-data:www-data /var/www/html/
echo "Correct ownership of the docroot has been set"

# Set correct permission for the settings.php file.
chmod 444 sites/default/settings.php
echo "Restored read-only permissions for settings.php"

# Clear drush cache.
drush cc drush
