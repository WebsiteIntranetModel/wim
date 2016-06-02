#!/bin/sh

# Run PHP Code Sniffer on WIM profile.
echo "Running PHP Code Sniffer on /profiles/wim."
phpcs --standard=Drupal --extensions=php,module,inc,install,test,profile,theme /var/www/html/profiles/wim
