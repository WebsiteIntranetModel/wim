#!/bin/sh

drush en testing -y;

# Run simple tests for WIM.
php /var/www/html/scripts/run-tests.sh WIM
