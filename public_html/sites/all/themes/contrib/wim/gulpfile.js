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
  dist: 'dist'
}

var glob = {
  css: folder.css + '/*.css',
  scss: folder.css + '/src/**/*.scss',
  js: folder.js + '/**/*.js',
  jade: folder.jade + '/*.jade',
  font: 'font/**/*',
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
// Fonts
// ===================================================

gulp.task('font', function() {
  stream = gulp.src(glob.font)
    .pipe( gulp.dest(folder.dist + '/font') )
    .pipe( connect.reload() );
  return stream;
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
    glob.font
  ], ['font']);

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
gulp.task('init', ['images', 'libs', 'font']);
gulp.task('build', ['css', 'jade', 'font', 'images']);
gulp.task('default', ['css', 'jade', 'connect', 'watch']);
