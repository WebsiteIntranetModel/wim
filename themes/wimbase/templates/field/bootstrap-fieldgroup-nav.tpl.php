<?php
/**
 * @file
 * Displays a Bootstrap-style nav for tabs/pills.
 *
 * Available variables:
 * - $is_empty: Boolean: any content to render at all?
 * - $wrapper_classes: The classes set on the wrapping div.
 * - $nav_classes: The classes set on the nav ul.
 * - $navs: An array of nav elements (tabs, pills)
 * - $nav_role: Role for nav wrapper element.
 * - $pane_classes: The classes set on the panes containing content.
 * - $panes: An array of panes containing content.
 * - $pane_role: Role for pane elements.
 * - $index: The index of the active tab/pane.
 *
 * @ingroup themeable
 */
?>

<?php if (!$is_empty) : ?>

    <div class="<?php print $wrapper_classes; ?>">

    <?php if ($flip) : ?>
      <div class="tab-content <?php print $pane_classes; ?>">
        <?php foreach ($panes as $index => $pane) : ?>
          <?php $active_class = $index === $active ? 'active' : ''; ?>
          <div id="<?php print $pane['id']; ?>" class="tab-pane <?php print $active_class; ?>">
            <?php print $pane['content']; ?>
          </div>
        <?php endforeach; ?>
      </div>
    <?php endif; ?>

    <?php if (!$is_single) : ?>
      <ul class="nav <?php print $nav_classes; ?>" role="<?php print $nav_role; ?>">
        <?php foreach ($navs as $index => $nav) : ?>
            <?php $active_class = $index === $active ? 'active' : '';?>
            <li class="<?php print $nav['classes']; ?> <?php print $active_class; ?>">
            <?php print $nav['content']; ?>
          </li>
        <?php endforeach; ?>
      </ul>
    <?php endif; ?>

    <?php if (!$flip) : ?>
      <div class="tab-content <?php print $pane_classes; ?>">
        <?php foreach ($panes as $index => $pane) : ?>
            <?php $active_class = $index === $active ? 'active' : ''; ?>
            <div id="<?php print $pane['id']; ?>" class="tab-pane <?php print $active_class; ?>" role="<?php print $pane_role; ?>">
            <?php print $pane['content']; ?>
          </div>
        <?php endforeach; ?>
      </div>
    <?php endif; ?>

  </div>

<?php endif; ?>
