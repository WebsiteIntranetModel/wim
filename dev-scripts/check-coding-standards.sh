#!/bin/sh

# Run PHP Code Sniffer on WIM profile.
echo "Running PHP Code Sniffer on /profiles/wim."
phpcs --report=summary --standard=Drupal --extensions=php,module,inc,install,test,profile,theme /var/www/html/profiles/wim

# Run PHP Code Sniffer on custom themes folder.
echo "Running PHP Code Sniffer on /sites/all/themes."
phpcs --report=summary --standard=Drupal --extensions=php,module,inc,install,test,profile,theme --ignore=*/contrib/bootstrap/* /var/www/html/sites/all/themes
