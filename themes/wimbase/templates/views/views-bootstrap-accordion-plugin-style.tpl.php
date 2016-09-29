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
    <div class="panel panel-default">
      <div class="panel-heading">
        <h4 class="panel-title">
          <a class="accordion-toggle collapsed"
             data-toggle="collapse"
             data-parent="#views-bootstrap-accordion-<?php print $id ?>"
             href="#collapse<?php print $key ?>">
            <?php print $titles[$key] ?>
          </a>
        </h4>
      </div>

      <div id="collapse<?php print $key ?>" class="panel-collapse collapse">
        <div class="panel-body">
          <?php print $row ?>
        </div>
      </div>
    </div>
  <?php endforeach ?>
</div>
