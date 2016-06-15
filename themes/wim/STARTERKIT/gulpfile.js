// ===================================================
// Required packages
// ===================================================

var gulp          = require('gulp'),
    postcss       = require('gulp-postcss'),
    sass          = require('gulp-sass'),
    sourcemaps    = require('gulp-sourcemaps'),
    gulpignore    = require('gulp-ignore'),
    autoprefixer  = require('autoprefixer'),
    mqpacker      = require('css-mqpacker'),
    precss        = require('precss'),
    lost          = require('lost'),
    rucksack      = require('gulp-rucksack'),
    path          = require('path'),
    fs            = require('fs'),
    concat        = require('gulp-concat'),
    notify        = require('gulp-notify'),
    gutil         = require('gulp-util'),
    uglify        = require('gulp-uglify'),
    nano          = require('gulp-cssnano'),
    connect       = require('gulp-connect'),
    plumber       = require('gulp-plumber');

// ===================================================
// Config
// ===================================================

var folder = {
  css: 'css',
  scss: 'css/src',
}

var glob = {
  css: folder.css + '/*.css',
  scss: folder.css + '/src/**/*.scss',
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
// Watch dev tasks
// ===================================================

gulp.task('watch', function() {
  gulp.watch([
    glob.scss
  ], ['css']);
});


// ===================================================
// Run this task and start theming. Make sure to read the readme!
// ===================================================
gulp.task('default', ['watch']);
