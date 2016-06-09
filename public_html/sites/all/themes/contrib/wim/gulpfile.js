// ===================================================
// Required packages
// ===================================================

var gulp          = require('gulp'),
    postcss       = require('gulp-postcss'),
    sass          = require('gulp-sass'),
    sourcemaps    = require('gulp-sourcemaps'),
    autoprefixer  = require('autoprefixer'),
    mqpacker      = require('css-mqpacker'),
    precss        = require('precss'),
    lost          = require('lost'),
    rucksack      = require('gulp-rucksack'),
    jade          = require('gulp-jade'),
    path          = require('path'),
    fs            = require('fs'),
    concat        = require('gulp-concat'),
    notify        = require('gulp-notify'),
    gutil         = require('gulp-util'),
    uglify        = require('gulp-uglify'),
    nano          = require('gulp-cssnano'),
    connect       = require('gulp-connect'),
    plumber       = require('gulp-plumber');
    // deploy        = require('gulp-gh-pages');

// ===================================================
// Config
// ===================================================

var folder = {
  css: 'css',
  scss: 'css/src',
  js: 'js',
  jade: 'jade',
  dist: 'dist',
  font: 'fonts',
  bootstrap_font: 'node_modules/bootstrap/dist/fonts/',
  bootstrap_css: 'node_modules/bootstrap/dist/css/',
  bootstrap_js: 'node_modules/bootstrap/dist/js/',
  jquery_js: 'node_modules/jquery/dist/',
}

var glob = {
  css: folder.css + '/*.css',
  scss: folder.css + '/src/**/*.scss',
  js: folder.js + '/**/*.js',
  jade: folder.jade + '/*.jade',
  images: 'images/**/*',
  libs: 'libs/**/*'
};

var onError = function(err) {
  notify.onError({
    title:    "Gulp error in " + err.plugin,
    message:  "<%= error.message %>",
    sound: "Beep"
  })(err);
  this.emit('end');
};

// ===================================================
// Styles
// ===================================================

gulp.task('css', function () {

  var processors = [
    autoprefixer({browsers: ['last 2 versions']}),
    mqpacker({sort: true}),
    lost()
  ];

  var stream = gulp.src(folder.scss + '/*.scss')
    .pipe(plumber({
      errorHandler: onError
    }))
    .pipe( sourcemaps.init() )
    .pipe( sass() )
    .pipe( nano( {
      mergeRules: true
    }) )
    .pipe( postcss(processors) )
    .pipe( rucksack() )
    .pipe( sourcemaps.write('.') )
    .pipe( gulp.dest(folder.css) )
    .pipe( gulp.dest(folder.dist + '/css') )
    .pipe( connect.reload() );
  return stream;

});

// ===================================================
// Scripts
// ===================================================

//copy vendor scripts from drupal to make them available for the styleguide
gulp.task('script-drupal', function() {
  return gulp.src([
    folder.js_drupal + '/misc/drupal.js',
    folder.js_drupal + '/misc/forms.js',
  ])
  .pipe( concat('drupal-core.js') )
  .pipe( gulp.dest(folder.dist + '/js') );
});

// ===================================================
// Import jQuery JS
// ===================================================

gulp.task('jquery-js', function() {
  stream = gulp.src(folder.jquery_js + '/jquery.min.js')
    .pipe( gulp.dest(folder.js) )
    .pipe( gulp.dest(folder.dist + '/js/')  )
  return stream;
});

// ===================================================
// Import Bootstrap assets
// ===================================================

gulp.task('bootstrap-css', function() {
  stream = gulp.src(folder.bootstrap_css + '/bootstrap.min.css')
    .pipe( gulp.dest(folder.css) )
    .pipe( gulp.dest(folder.dist + '/css/')  )
  return stream;
});

gulp.task('bootstrap-js', function() {
  stream = gulp.src(folder.bootstrap_js + '/bootstrap.min.js')
    .pipe( gulp.dest(folder.js) )
    .pipe( gulp.dest(folder.dist + "/js") )
  return stream;
});

gulp.task('bootstrap-font', function() {
  stream = gulp.src(folder.bootstrap_font + '/*')
    .pipe( gulp.dest(folder.font) )
    .pipe( gulp.dest(folder.dist + "/fonts") )
  return stream;
});

// ===================================================
// Template file (Jade)
// ===================================================

gulp.task('jade', function() {

  return gulp.src(glob.jade)
    .pipe(plumber({
      handleError: onError
    }))
    .pipe(jade({
      pretty: true
    })) // pipe to jade plugin
    .pipe(gulp.dest(folder.dist)); // tell gulp our output folder
});

// ===================================================
// Images
// ===================================================

gulp.task('images', function() {
  stream = gulp.src(glob.images)
    .pipe( gulp.dest(folder.dist + '/images') )
    .pipe( connect.reload() );
  return stream;
});

// ===================================================
// Extras
// ===================================================

gulp.task('libs', function() {
  stream = gulp.src(glob.libs)
    .pipe( gulp.dest(folder.dist + '/libs') )
  return stream;
});

// ===================================================
// Set up a server
// ===================================================

gulp.task('connect', function() {
  connect.server({
    root: [folder.dist],
    livereload: true,
    port: 5000
  });
});


// ===================================================
// Watch dev tasks
// ===================================================

gulp.task('watch', function() {
  gulp.watch([
    glob.scss
  ], ['css']);

  gulp.watch([
    folder.jade + '/**/*'
  ], ['jade']);

  gulp.watch([
    glob.images
  ], ['images']);

});

// ===================================================
// Deploy to github pages branch
// ===================================================

gulp.task('deploy', ['build'], function() {
  return gulp.src([folder.dist + '/**/*'])
    .pipe( deploy() );
});


// ===================================================
// Run this one time when you install the project so you have all files in the dist folder
// ===================================================
gulp.task('init', ['images', 'libs', 'jquery-js', 'bootstrap-css', 'bootstrap-font', 'bootstrap-js']);
gulp.task('build', ['css', 'jade', 'images']);
gulp.task('default', ['css', 'jade', 'connect', 'watch']);
