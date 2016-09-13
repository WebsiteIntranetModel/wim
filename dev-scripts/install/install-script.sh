#!/bin/sh

# Install script for in the docker container.
cd /var/www/html/;
PROFILE_PATH=profiles/wim;

# Check if first argument given is "reinstall". In that case we drop the database,
# remove settings.php and the files folder.
if [ "$BUILD_ENVIRONMENT" = "travis" ]; then
  echo "I'm here, all is fine";
  PROFILE_PATH=/var/wim/profiles/wim;

  cd ${PROFILE_PATH};
  ls -la;

  cd /var/wim;
  ls -la;
fi

# Check if first argument given is "reinstall". In that case we drop the database,
# remove settings.php and the files folder.
if [ ${1:-"install"} = "reinstall" ]; then
  drush sql-drop -y;
  find . -maxdepth 1 ! -name "." -name ".." -name "profiles" | xargs rm -rf
  cd profiles
  find . -maxdepth 1 ! -name "." -name ".." -name "wim" | xargs rm -rf
  cd -
  echo "Database dropped, files folder and settings.php removed"
fi

# Check if second argument is "include", defaults to "exclude". We copy the
# local settings.php to the place where it will be included in settings.php.
if [ ${2:-"exclude"} = "include" ]; then
  cp sites/default/example.settings.local.php sites/default/settings.local.php
  echo "Moved settings.local.php so it can be included in the settings.php file."
fi

apt-get update -qq && apt-get install -y unzip
# Build the site using drush make
#drush make ${PROFILE_PATH}/build-wim.make .

# Check if third argument is "develop". In that case we download the develop
# modules.
#if [ ${3:-"default"} = "develop" ]; then
#  drush make --no-core ${PROFILE_PATH}/drupal-org-dev.make .
#fi
echo "Drush make complete"

# Install the site using the WIM installation profile.
drush -y site-install wim --db-url=mysql://root:root@db:3306/wim --account-pass=admin install_configure_form.site_name='WIM';
echo "Drupal installation complete"

# Set ownership for data folder.
chown -R www-data:www-data /var/www/html/
echo "Correct ownership of the docroot has been set"

# Set correct permission for the settings.php file.
chmod 444 sites/default/settings.php
echo "Restored read-only permissions for settings.php"

# Check if third argument is "develop" then enable develop modules.
if [ ${3:-"default"} = "develop" ]; then
  drush dis toolbar -y
  drush en devel, field_ui, diff, views_ui, context_ui, felix_ui, dblog, hansel_ui -y
fi

# Revert all features
drush fra -y

# Clear drush cache.
drush cc drush
