#!/bin/sh

REPORT=--report=summary

if [ ${1:-"summary"} = "full" ]; then
  REPORT=--report-full
fi

# Run PHP Code Sniffer.
echo "Running PHP Code Sniffer."
phpcs $REPORT --standard=Drupal --extensions=php,module,inc,install,test,profile,theme --ignore=*/vendor/* /var/www/html/profiles/wim
