<?php

/**
 * @file
 * Default theme implementation for a single paragraph item.
 *
 * Available variables:
 * - $content: An array of content items. Use render($content) to print them
 *   all, or print a subset such as render($content['field_example']). Use
 *   hide($content['field_example']) to temporarily suppress the printing of a
 *   given element.
 * - $classes: String of classes that can be used to style contextually through
 *   CSS. It can be manipulated through the variable $classes_array from
 *   preprocess functions. By default the following classes are available, where
 *   the parts enclosed by {} are replaced by the appropriate values:
 *   - entity
 *   - entity-paragraphs-item
 *   - paragraphs-item-{bundle}
 *
 * Other variables:
 * - $classes_array: Array of html class attribute values. It is flattened into
 *   a string within the variable $classes.
 *
 * @see template_preprocess()
 * @see template_preprocess_entity()
 * @see template_process()
 */
?>
<div class="panel panel-default">
  <div class="panel-heading">
    <h2 class="panel-title">
      <button aria-expanded="false" data-toggle="collapse" data-parent="#<?php print $id; ?>" href="#<?php print $panel['id'] ?>-<?php print $index; ?>">
        <?php print render($content['field_title']); ?>
      </button>
    </h2>
    <div hidden class="panel-collapse panel-content"<?php print $content_attributes; ?>>
      <?php hide($content['field_title']); ?>
      <?php print render($content); ?>
    </div>
  </div>
</div>
