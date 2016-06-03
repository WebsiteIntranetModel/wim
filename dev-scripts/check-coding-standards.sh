#!/bin/sh

REPORT=--report-summary

if [ ${1:-"summary"} = "full" ]; then
  REPORT=--report-full
fi

# Run PHP Code Sniffer on WIM profile.
echo "Running PHP Code Sniffer on /profiles/wim."
phpcs $REPORT --standard=Drupal --extensions=php,module,inc,install,test,profile,theme /var/www/html/profiles/wim

# Run PHP Code Sniffer on custom themes folder.
echo "Running PHP Code Sniffer on /sites/all/themes."
phpcs $REPORT --standard=Drupal --extensions=php,module,inc,install,test,profile,theme --ignore=*/contrib/bootstrap/* /var/www/html/sites/all/themes
