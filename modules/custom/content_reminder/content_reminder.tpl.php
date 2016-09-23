<?php
/**
 * @file
 * Email template.
 */
?>
<html>
  <head>
    <meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
    <title>Nodes die updates nodig hebben</title>
  </head>

  <body style="background-color: #FFFFFF">
    <p><?php print $content_reminder_text; ?></p>
    <ul>
      <?php foreach ($nodes as $node): ?>
        <li><strong><?php print $node->type; ?></strong>: <?php print $node->url; ?> <?php print ($node->status == 1 ? 'Published' : 'Unpublished'); ?></li>
      <?php endforeach; ?>
    </ul>
  </body>
</html>
