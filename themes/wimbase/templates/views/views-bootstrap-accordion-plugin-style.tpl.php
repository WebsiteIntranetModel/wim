<?php
/**
 * @file
 * Override default bootstrap accordion views template for the Wim theme.
 *
 * Added 'collapsed' class for all items by default.
 *
 * @see template_preprocess_views_bootstrap_accordion_plugin_style()
 *
 * @ingroup templates
 */
?>
<div id="views-bootstrap-accordion-<?php print $id ?>"
     class="<?php print $classes ?>">
  <?php foreach ($rows as $key => $row): ?>
    <fieldset class="panel panel-default">
      <legend class="panel-heading">
        <a class="accordion-toggle collapsed"
           data-toggle="collapse"
           data-parent="#views-bootstrap-accordion-<?php print $id ?>"
           aria-controls="panel-<?php print $id ?>-<?php print $key ?>"
           id="control-panel-<?php print $id ?>-<?php print $key ?>"
           href="#panel-<?php print $id ?>-<?php print $key ?>">
          <?php print $titles[$key] ?>
        </a>
      </legend>

      <div id="panel-<?php print $id ?>-<?php print $key ?>"
           class="panel-collapse collapse"
           aria-labelledby="control-panel-<?php print $id ?>-<?php print $key ?>">
        <div class="panel-body">
          <?php print $row ?>
        </div>
      </div>
    </fieldset>
  <?php endforeach ?>
</div>
