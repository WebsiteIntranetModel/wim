FROM goalgorilla/wim:latest
MAINTAINER devel@goalgorilla.com

ADD php.ini /usr/local/etc/php/php.ini

# Install composer dependencies.
ADD composer.json /root/.composer/composer.json
ADD composer.lock /root/.composer/composer.lock
RUN composer global install --prefer-dist

# Unfortunately, adding the composer vendor dir to the PATH doesn't seem to work. So:
RUN ln -s /root/.composer/vendor/bin/behat /usr/local/bin/behat
RUN ln -s /root/.composer/vendor/bin/phpunit /usr/local/bin/phpunit
RUN ln -s /root/.composer/vendor/bin/phpcs /usr/local/bin/phpcs

# Register the Drupal and DrupalPractice Standard with PHPCS.
RUN phpcs --config-set installed_paths /root/.composer/vendor/drupal/coder/coder_sniffer

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

# Contains the Mac hack to get the permissions to work for development.
# Set user 1000 and group staff to www-data, enables write permission.
# https://github.com/boot2docker/boot2docker/issues/581#issuecomment-114804894
RUN usermod -u 1000 www-data
RUN usermod -G staff www-data

# Work around a Debian bug that prevents the Java installation
# https://bugs.debian.org/cgi-bin/bugreport.cgi?bug=863199
RUN mkdir -p /usr/share/man/man1

# Install JAVA
RUN apt-get update && apt-get install -y default-jre

# Download Tike jar
RUN mkdir -p /var/lib/tika && \
  cd /var/lib/tika && \
  curl -O http://apache.claz.org/tika/tika-app-1.16.jar
