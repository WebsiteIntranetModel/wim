<?php

/**
 * @file
 * Template for Readspeaker webReader.
 *
 * Available variables:
 * @var string $customer_id
 *   Readspeaker customer id.
 * @var string $lang
 *   Readspeaker language code (e.g. en_uk, nl_nl).
 * @var string $title
 *   Readspeaker popup title.
 * @var string $readfrom_id
 *   ID in html where readspeaker will start
 * @var url $url
 *   Current page absolute url.
 * @var string $button
 *   Listen button text.
 */
?>

<div>
  <div id="readspeaker_button" class="rs_skip rsbtn rs_preserve">
    <a title="<?php print $title; ?>" href="//app-eu.readspeaker.com/cgi-bin/rsent?customerid=<?php print $customer_id; ?>&lang=<?php print $lang; ?>&readid=<?php print $readfrom_id; ?>&url=" rel="nofollow" class="rsbtn_play" accesskey="L" aria-expanded="false">
      <span class="rsbtn_left rsimg rspart">
        <span class="rsbtn_text">
          <span><?php print $button; ?></span>
        </span>
      </span>
      <span class="rsbtn_right rsimg rsplay rspart"></span>
    </a>
  </div>
</div>
