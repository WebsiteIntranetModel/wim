<?php

/**
 * @file
 * Display the progress bar for multipage forms.
 *
 * Available variables:
 * - $node: The webform node.
 * - $progressbar_page_number: TRUE if the actual page number should be
 *   displayed.
 * - $progressbar_percent: TRUE if the percentage complete should be displayed.
 * - $progressbar_bar: TRUE if the bar should be displayed.
 * - $progressbar_pagebreak_labels: TRUE if the page break labels shoud be
 *   displayed.

 * - $page_num: The current page number.
 * - $page_count: The total number of pages in this form.
 * - $page_labels: The labels for the pages. This typically includes a label for
 *   the starting page (index 0), each page in the form based on page break
 *   labels, and then the confirmation page (index number of pages + 1).
 * - $percent: The percentage complete.
 */
?>

<div class="webform-progressbar">
  <?php if ($progressbar_bar): ?>
    <span><?php print t('Current step: @name', array('@name' => check_plain($page_labels[$page_num - 1])));?></span>
    <div class="progress">
      <?php
      $value_text = t('Step @num: @name', array('@num' => $page_num, '@name' => check_plain($page_labels[$page_num - 1])));
      $percent_round = number_format($percent, 0);
      if ($percent_round != 33 && $percent_round != 66) {
        $percent_round = substr($percent_round, 0, -1) . '0';
      }
      ?>
      <div class="progress-bar completed_<?php print $percent_round; ?>" role="progressbar" aria-valuenow="<?php print number_format($percent, 0); ?>" aria-valuemin="0" aria-valuemax="100" aria-valuetext="<?php print $value_text;?>">
        <?php if ($percent = number_format($percent, 0)):?>
          <?php print $percent; ?>%
        <?php else:?>
          <span class="sr-only">0%</span>
        <?php endif;?>
      </div>
    </div>
  <?php endif; ?>

  <?php if ($progressbar_page_number): ?>
    <div class="webform-progressbar-number">
      <?php print t('Step @start of @end', array('@start' => $page_num, '@end' => $page_count)); ?>
      <?php if ($progressbar_percent): ?>
        <span class="webform-progressbar-number">
          (<?php print t('Completed @num%', array('@num' => number_format($percent, 0)));?>)
        </span>
      <?php endif; ?>
    </div>
  <?php endif; ?>

  <?php if (!$progressbar_page_number && $progressbar_percent): ?>
    <span class="webform-progressbar-number">
      (<?php print t('Completed @num%', array('@num' => number_format($percent, 0)));?>)
    </span>
  <?php endif; ?>
</div>
