FROM php:5.6-apache
MAINTAINER devel@goalgorilla.com

RUN a2enmod rewrite

# install the PHP extensions we need
RUN apt-get update && apt-get install -y \
  libpng12-dev \
  libjpeg-dev \
  libpq-dev \
  php-pclzip \
  mysql-client \
  git \
  ssmtp \
  nano \
  vim \
  && apt-get clean \
  && rm -rf /var/lib/apt/lists/* \
  && docker-php-ext-configure gd --with-png-dir=/usr --with-jpeg-dir=/usr \
  && docker-php-ext-install gd mbstring pdo pdo_mysql pdo_pgsql zip

WORKDIR /var/www/html

ADD docker_build/mailcatcher-ssmtp.conf /etc/ssmtp/ssmtp.conf

RUN echo "hostname=goalgorilla.com" >> /etc/ssmtp/ssmtp.conf
RUN echo 'sendmail_path = "/usr/sbin/ssmtp -t"' > /usr/local/etc/php/conf.d/mail.ini

ADD docker_build/php.ini /usr/local/etc/php/php.ini

RUN docker-php-ext-install zip

# Install bcmath
RUN docker-php-ext-install bcmath

# Xdebug.
RUN pecl install xdebug
RUN docker-php-ext-enable xdebug
RUN sed -i '1 a xdebug.remote_autostart=true' /usr/local/etc/php/conf.d/docker-php-ext-xdebug.ini
RUN sed -i '1 a xdebug.remote_mode=req' /usr/local/etc/php/conf.d/docker-php-ext-xdebug.ini
RUN sed -i '1 a xdebug.remote_handler=dbgp' /usr/local/etc/php/conf.d/docker-php-ext-xdebug.ini
RUN sed -i '1 a xdebug.remote_connect_back=1 ' /usr/local/etc/php/conf.d/docker-php-ext-xdebug.ini
RUN sed -i '1 a xdebug.remote_port=9000' /usr/local/etc/php/conf.d/docker-php-ext-xdebug.ini
RUN sed -i '1 a xdebug.remote_host=127.0.0.1' /usr/local/etc/php/conf.d/docker-php-ext-xdebug.ini
RUN sed -i '1 a xdebug.remote_enable=1' /usr/local/etc/php/conf.d/docker-php-ext-xdebug.ini

# Install Composer.
RUN curl -sS https://getcomposer.org/installer | php
RUN mv composer.phar /usr/local/bin/composer

# Install composer dependencies.
ADD docker_build/composer.json /root/.composer/composer.json
ADD docker_build/composer.lock /root/.composer/composer.lock
RUN composer global install --prefer-dist

# Unfortunately, adding the composer vendor dir to the PATH doesn't seem to work. So:
RUN ln -s /root/.composer/vendor/bin/drush /usr/local/bin/drush
RUN ln -s /root/.composer/vendor/bin/behat /usr/local/bin/behat
RUN ln -s /root/.composer/vendor/bin/phpunit /usr/local/bin/phpunit

ADD public_html/ /var/www/html/
RUN chown -R www-data:www-data *

# Install Drupal console
RUN curl https://drupalconsole.com/installer -L -o drupal.phar
RUN mv drupal.phar /usr/local/bin/drupal
RUN chmod +x /usr/local/bin/drupal

RUN if [ ! -f /root/.composer/vendor/drush/drush/lib/Console_Table-1.1.3/Table.php ]; then pear install Console_Table; fi

# Fix shell.
RUN echo "export TERM=xterm" >> ~/.bashrc

# Contains the Mac hack to get the permissions to work for development.
# Set user 1000 and group staff to www-data, enables write permission.
# https://github.com/boot2docker/boot2docker/issues/581#issuecomment-114804894
RUN usermod -u 1000 www-data
RUN usermod -G staff www-data
