#!/bin/sh

# Install script for in the docker container.
cd /var/www/html/;

if [ ${1:-"install"} = "reinstall" ]; then
  # We received an argument to re-install the site.
  drush sql-drop -y;
  rm -f sites/default/settings.php;
  rm -f sites/default/settings.local.php;
  rm -rf sites/default/files;
  echo "Database dropped, files folder and settings.php removed"
fi

if [ ${2:-"exclude"} = "include" ]; then
  # We received an argument to re-install the site.
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
